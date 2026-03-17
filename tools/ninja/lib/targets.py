# ============================================================================#
#                                                                             #
# Ninja build target templates                                                #
#                                                                             #
# ============================================================================#

from os.path import join as pathjoin

from .config import KokeshiConfig
from .define import CHECKROM_STAMP
from .exceptions import KokeshiException
from .ninja_syntax import Writer
from .paths import Asset, CompileUnit, KamekBinary
from .utility import find_files
from .platform import IS_WINDOWS


def target_tools(writer: Writer, config: KokeshiConfig):
    """Emits a Ninja build target to install all tools

    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
    """

    inputs = ["$compiler_dir", "$linker_dir"]

    # Non-Windows systems must use wibo to run PE executables
    if not IS_WINDOWS:
        inputs.append("$wibo_dir")

    writer.comment("Download and install all tools")
    writer.build(
        outputs="tools",
        rule="phony",  # Phony rule
        inputs=inputs,
    )
    writer.newline()


def target_install_tool(writer: Writer, config: KokeshiConfig, tool_name: str,
                        target_output: str):
    """Emites a Ninja build target to install the specified tool

    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
        tool_file (str): Tool name
        target_output (str): Output file for target
    """

    writer.comment(f"Install {tool_name}")
    writer.build(
        outputs=target_output,
        rule="install_tool",
        variables={
            "name": tool_name
        },
    )
    writer.newline()


def target_reconfigure(writer: Writer, config: KokeshiConfig):
    """Emits a Ninja build target to re-run the configure script

    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
    """

    # Reconfigure when ANY ninja-related script is changed
    ninja_files = find_files(
        pathjoin(config.tools_dir, "ninja"), [".py"])

    writer.comment("Re-run generator script")
    writer.build(
        outputs="$ninja_script",
        rule="reconfigure",
        implicit=["$configure", *ninja_files],
    )
    writer.newline()


def target_checkrom(writer: Writer, config: KokeshiConfig, pack: str):
    """Emits a Ninja build target to check the base ROM integrity

    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
        pack (str): Pack name
    """

    dol_path = pathjoin(config.base_dir, f"Static{pack.capitalize()}.dol")
    stamp_path = pathjoin(config.build_dir, CHECKROM_STAMP)

    writer.comment(f"Check base ROM ({pack})")
    writer.build(
        outputs=stamp_path,
        rule="checkrom",
        variables={
            "pack": pack,
        },
        implicit=["$checkrom", dol_path]
    )
    writer.newline()


def target_compile(writer: Writer, config: KokeshiConfig, unit: CompileUnit,
                   flags: str, precompile: list[str] = []):
    """Emits a Ninja build target to compile the specified source file

    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
        unit (CompileUnit): Source file
        flags (str): Compiler flags
        precompile (list[str]): List of precompiled headers this translation
                                unit depends on
    """

    if precompile:
        raise KokeshiException("Precompiled headers are not yet supported :(")

    implicit = ["$compiler_dir", *precompile]

    # Non-Windows systems must use wibo to run PE executables
    if not IS_WINDOWS:
        implicit.append("$wibo_dir")

    writer.comment(f"Compile {unit.path()}")
    writer.build(
        outputs=unit.object_path(),
        rule="compile",
        inputs=unit.path(),
        variables={
            "depfile": unit.dependency_path(),
            "cflags": flags,
            "outdir": unit.output_directory(),
        },
        implicit=implicit,
    )
    writer.newline()


def target_link(writer: Writer, config: KokeshiConfig, binary: KamekBinary,
                units: list[CompileUnit]):
    """Emits a Ninja build target to link the specified executable

    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
        binary (KamekBinary): Kamek binary
        units (list[CompileUnit]): Translation/compilation units to include in
                                   the binary
    """

    inputs = [unit.object_path() for unit in units]
    outputs = [binary.rel_build_path(), binary.map_build_path()]

    # Some Kamek binaries (like the loader) require DOL patches
    if binary.static_build_path():
        outputs.append(binary.static_build_path())

    writer.comment(f"Link {binary.name()} ({binary.pack()})")
    writer.build(
        outputs=outputs,
        rule="link",
        inputs=inputs,
        variables={
            "ldflags": binary.linker_flags(),
            "name": binary.name(),
            "pack": binary.pack(),
        },
        implicit=["$linker_dir", binary.symbols_path()],
    )
    writer.newline()


def target_install_binary(writer: Writer, config: KokeshiConfig,
                          binary: KamekBinary):
    """Emits a Ninja build target to install the specified executable

    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
        binary (KamekBinary): Kamek binary
    """

    # Some Kamek binaries (like the loader) require DOL patches
    if binary.static_addr() != 0:
        input_bin = binary.static_build_path()
        output_bin = binary.static_install_path()
    else:
        input_bin = binary.rel_build_path()
        output_bin = binary.rel_install_path()

    input_map = binary.map_build_path()
    output_map = binary.map_install_path()

    writer.comment(f"Install {binary.name()} ({binary.pack()})")
    writer.build(
        outputs=[output_bin, output_map],
        rule="install_binary",
        inputs=[input_bin, input_map],
        variables={
            "bin_in": input_bin,
            "bin_out": output_bin,
            "map_in": input_map,
            "map_out": output_map,
            "name": binary.name(),
            "pack": binary.pack(),
        },
    )
    writer.newline()


def target_install_asset(writer: Writer, config: KokeshiConfig, asset: Asset):
    """Emits a Ninja build target to install the specified asset file

    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
        asset (Asset): Project asset
    """

    writer.comment(f"Install {asset.path()}")
    writer.build(
        outputs=asset.install_path(),
        rule="install_asset",
        inputs=asset.path(),
        variables={
            "pack": asset.pack(),
        },
    )
    writer.newline()


def target_clangd_commands(writer: Writer, config: KokeshiConfig):
    """Emits a Ninja build target to create Clangd compilation commands
    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
    """

    writer.comment("Create Clangd commands")
    writer.build(
        outputs="$compile_commands",
        rule="clangd_commands",
        implicit=[KokeshiConfig.PATH],
    )
    writer.newline()
