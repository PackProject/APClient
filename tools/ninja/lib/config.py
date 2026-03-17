# ============================================================================#
#                                                                             #
# Project configuration                                                       #
#                                                                             #
# ============================================================================#

from dataclasses import dataclass, field
from os.path import abspath
from os.path import join as pathjoin
from os.path import normpath
from typing import Self

import yaml

from .define import *
from .exceptions import KokeshiException
from .utility import find_directories

# ============================================================================#
# KokeshiConfig                                                               #
# ============================================================================#


@dataclass
class KokeshiConfig:
    """Represents the Kokeshi project configuration file.

    Data members are given values based on the `project.yaml` file.
    """

    PATH = "project.yaml"
    """Path to the Kokeshi project configuration file
    """

    @staticmethod
    def load() -> Self:
        """Attempts to deserialize the config specified in the project config
        file

        Raises:
            KokeshiException: Project config file is missing
        """

        try:
            with open(KokeshiConfig.PATH, "r", encoding="utf-8") as f:
                config_yaml = yaml.safe_load(f)

        except FileNotFoundError:
            raise KokeshiException("Project config file is missing!")

        return KokeshiConfig(**config_yaml)

    # ========================================================================#
    # Variables                                                               #
    # ========================================================================#

    static: int = 0x80001900
    """The memory address at which the Kokeshi loader will be patched in.

    This address must fall within the exception handler table, so take care to
    know how much space you are working with!
    """

    packs: list[str] = field(default_factory=list[str])
    """Game(s) that your mod should build for.
    By default, we try building for Wii Sports.

    You can build for multiple games by writing multiple pack names.

    Valid choices are:
        - `sports` (Wii Sports)
        - `party` (Wii Play)
        - `resort` (WSR)

    To handle this in your code, expect preprocessor definitions of the
    format `PACK_{NAME}`, (i.e. `PACK_SPORTS`, `PACK_PARTY`, `PACK_RESORT`).
    """

    mwcc_ver: str = None
    """The version of the CodeWarrior compiler that should be used.
    This can omitted if you are using a custom compiler anyways.

    The compiler versions should be in the format `OS:VER` (e.g. `Wii:1.7`).
    """

    kamek_ver: str = None
    """The version of the Kamek linker that should be used.
    This can be omitted if you are using a custom linker anyways.

    The release tags line up with the PackProject fork of Kamek.
    """

    wibo_ver: str = None
    """The version of the wibo wrapper that should be used.

    This can be omitted if you are using a custom compiler that can be ran
    natively.

    The release tags line up with the decompals/wibo repository.
    """

    use_git_commit_hash: bool = False
    """Whether to include the latest Git repository commit short hash as a
    preprocessor definition (`GIT_COMMIT_HASH`) when compiling the module.

    NOTE: It is assumed that the Git repository is the current working
    directory, and that command-line Git is installed on the current machine.
    """

    # ========================================================================#
    # Compiler flags                                                          #
    # ========================================================================#

    cflags_common: list[str] = field(default_factory=list[str])
    """Common compiler flags to apply across all code.

    See `_cflags_common_internal` inside KokeshiConfig to see which flags are
    already in use.
    """

    cflags_module: list[str] = field(default_factory=list[str])
    """Compiler flags to apply across all module code.
    """

    cflags_debug: list[str] = field(default_factory=list[str])
    """Compiler flags to apply across all module code in debug builds.
    """

    cflags_release: list[str] = field(default_factory=list[str])
    """Compiler flags to apply across all module code in release builds.
    """

    cflags_include: list[str] = field(default_factory=list[str])
    """Compiler flags to configure include directory searches.
    """

    clangd_flags: list[str] = field(default_factory=list[str])
    """Additional flags to pass to the Clangd language parser.
    """

    # ========================================================================#
    # Directories                                                             #
    # ========================================================================#

    assets_dir: str = "assets"
    """The directory in which module assets are stored.
    These files will be copied to the ROM filesystem after post-processing.
    """

    base_dir: str = "base"
    """The directory in which baserom DOL files and symbol maps are stored.
    """

    docs_dir: str = "docs"
    """The directory in which documentation is stored.
    """

    build_dir: str = "build"
    """The directory in which build artifacts are stored.
    """

    romfs_dir: str = "romfs"
    """The directory in which the ROM filesystems exist.
    """

    romfs_to_assets_dir: str = pathjoin("DATA", "files")
    """The RomFS directory in which the assets exist.

    Kokeshi expects the format from Dolphin's "Extract Entire Disc..." option,
    which creates a folder for the DATA partition.
    """

    modules_dir: str = "modules"
    """The RomFS directory in which code modules (Kamek binaries) are stored.
    """

    include_dir: str = "include"
    """The directory in which all C/C++ header files are stored.
    """

    library_dir: str = "lib"
    """The directory in which all C/C++ library code is stored.

    This includes libkiwi, as well as any third-party code that should be
    vendored into the repository.
    """

    loader_dir: str = "loader"
    """The directory in which the Kokeshi loader source code is stored.
    Kokeshi uses the loader provided by the Kamek linker.
    """

    src_dir: str = "src"
    """The directory in which all module source code is stored.
    """

    tools_dir: str = "tools"
    """The directory in which all build tools are stored.
    """

    src_extensions: list[str] = field(
        default_factory=lambda: [".c", ".cpp", ".cc", ".cxx", ".c++"])
    """All file extensions that signify C/C++ source code files.
    """

    def __post_init__(self):
        """Performs post-constructor initialization.

        This method is mostly reserved for class members that should not be
        configurable through the project YAML.
        """

        self.__validate()

        self.__normalize_paths()
        self.__append_cflags()
        self.__find_tools()

        # Allow 'v' prefix in wibo tags to match Kamek release format
        self.wibo_ver = self.wibo_ver.replace("v", "")

    def __validate(self):
        """Validates the format of this configuration
        """

        if not self.mwcc_ver:
            raise KokeshiException(
                "Please set a compiler version in your project.yaml")

        mwcc_tokens = self.mwcc_ver.split(":")

        if len(mwcc_tokens) != 2:
            raise KokeshiException(
                "Compiler version is not correctly formatted")

        if not self.kamek_ver:
            raise KokeshiException(
                "Please set a linker version in your project.yaml")

    def __normalize_paths(self):
        """Normalizes all filepath members
        """

        self.assets_dir = normpath(self.assets_dir)
        self.base_dir = normpath(self.base_dir)
        self.docs_dir = normpath(self.docs_dir)
        self.build_dir = normpath(self.build_dir)
        self.romfs_dir = normpath(self.romfs_dir)
        self.romfs_to_assets_dir = normpath(self.romfs_to_assets_dir)
        self.modules_dir = normpath(self.modules_dir)
        self.include_dir = normpath(self.include_dir)
        self.library_dir = normpath(self.library_dir)
        self.loader_dir = normpath(self.loader_dir)
        self.src_dir = normpath(self.src_dir)
        self.tools_dir = normpath(self.tools_dir)

    def __append_cflags(self):
        """Appends internal compiler flags
        """

        # Internal compiler flags to apply across all code
        self.cflags_common += [
            # I actually don't remember what this does???
            "-I-",
            # For Kokeshi-specific code (separate from decomp)
            "-D__KOKESHI__",
            # Create flags for the defined pack(s)
            *[f"-DPACK_{pack.upper()}" for pack in self.packs],
            # Auto-inline small functions
            "-inline auto",
            # Gekko processor
            "-proc gekko",
            # Disable C++ exceptions
            "-Cpp_exceptions off",
            # Force 4-byte enumerations
            "-enum int",
            # Apply file-level optimizations
            "-ipa file",
            # Max optimization level, focus on small code size
            "-O4,s",
            # Use lmw/stmw for stack frames to save code size
            "-use_lmw_stmw on",
            # Use compact floating-point instructions to save code size
            "-fp fmadd",
            # Place strings in rodata
            "-rostr",
            # Disable RTTI to save module size
            "-RTTI off",
            # We can't use small data sections in relocatable code
            "-sdata 0",
            # We can't use small data sections in relocatable code
            "-sdata2 0",
            # Enable C++11 features
            "-pragma \"cpp1x on\"",
            # For BTE library
            "-DREVOLUTION",
            "-ir include/revolution/BTE",
        ]

        # Internal compiler flags to apply across all module code
        self.cflags_module += [
            # . . .
        ]

        # Internal compiler flags to apply across all code in release builds
        self.cflags_release += [
            "-DNDEBUG",
        ]

        # Internal compiler flags to apply across all code in debug builds
        self.cflags_debug += [
            # . . .
        ]

        # Include directory priority
        include_dir_order = [
            pathjoin(self.include_dir, "MSL"),
            self.src_dir,
            self.include_dir,
            self.library_dir,
            self.loader_dir,
        ]

        # Create compiler flags for includes
        for dir in include_dir_order:
            for sub_dir in find_directories(dir, recursive=False):
                self.cflags_include.append(f"-i {sub_dir}")

        # Include flags apply to all source files
        self.cflags_common += self.cflags_include

    def __find_tools(self):
        """Resolves filepaths to all tools needed by the project
        """

        # Configure script location
        self._configure: str = abspath(CONFIGURE_SCRIPT)

        # ROM check script location
        self._checkrom: str = abspath(pathjoin(
            self.tools_dir, CHECKROM_SCRIPT))

        # Tool installer script location
        self._install_tool: str = abspath(pathjoin(
            self.tools_dir, INSTALL_TOOL_SCRIPT))

        # Clangd compiler command script location
        self._make_compile_cmds: str = abspath(pathjoin(
            self.tools_dir, MAKE_COMPILE_CMDS_SCRIPT))

        # Compiler location
        cc_os, cc_ver = (*self.mwcc_ver.split(":"),)

        self._compiler_dir: str = abspath(pathjoin(
            self.tools_dir, COMPILER_DIR))

        self._compiler: str = abspath(pathjoin(
            self._compiler_dir, cc_os, cc_ver, COMPILER_NAME))

        # Linker location
        self._linker_dir: str = abspath(pathjoin(
            self.tools_dir, LINKER_DIR))

        self._linker: str = abspath(pathjoin(
            self._linker_dir, LINKER_NAME))

        # wibo location
        self._wibo_dir: str = abspath(pathjoin(
            self.tools_dir, WIBO_DIR))

        self._wibo: str = abspath(pathjoin(
            self._wibo_dir, WIBO_NAME))

        # Python executable location
        self._python = PYTHON
