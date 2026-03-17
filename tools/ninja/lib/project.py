# ============================================================================#
#                                                                             #
# Project interface                                                           #
#                                                                             #
# ============================================================================#

import subprocess
from io import StringIO
from os.path import join as pathjoin

from .config import KokeshiConfig
from .define import *
from .ninja_syntax import Writer
from .paths import Asset, CompileUnit, KamekLoader, KamekModule
from .platform import IS_WINDOWS, gen_exec_cmd
from .rules import (
    rule_checkrom,
    rule_clangd_commands,
    rule_compile,
    rule_install_asset,
    rule_install_binary,
    rule_install_tool,
    rule_link,
    rule_reconfigure,
)
from .targets import (
    target_checkrom,
    target_clangd_commands,
    target_compile,
    target_install_asset,
    target_install_binary,
    target_install_tool,
    target_link,
    target_reconfigure,
    target_tools,
)
from .utility import find_files

# ============================================================================#
# Configuration                                                               #
# ============================================================================#


NINJA_REQUIRED_VERSION = "1.13"
"""The minimum required version of Ninja to execute the resulting script
"""

NINJA_SCRIPT_NAME = "build.ninja"
"""Name of the resulting Ninja build script
"""

# ============================================================================#
# KokeshiProject                                                              #
# ============================================================================#


class KokeshiProject:
    """Represents the Kokeshi build process.
    """

    def __init__(self, config: KokeshiConfig):
        """Constructor
        """

        self.config: KokeshiConfig = config

    def emit(self) -> None:
        """Emits the Ninja build script (`build.ninja`)
        """

        # Any behavior necessary before emitting the script
        self._before_emit(self.config)

        output = StringIO()
        writer = Writer(output)

        self._emit_vars(writer, self.config)
        self._emit_rules(writer, self.config)
        self._emit_targets(writer, self.config)

        # Create ninja script
        with open(NINJA_SCRIPT_NAME, "w+", encoding="utf-8") as f:
            f.write(output.getvalue())

        writer.close()

        # Any behavior necessary after emitting the script
        self._after_emit(self.config)

    def _before_emit(self, config: KokeshiConfig) -> None:
        """Performs all necessary behavior before emitting the Ninja build
        script

        Args:
            config (KokeshiConfig): Project configuration
        """

        # Create compiler flag for Git commit hash
        if config.use_git_commit_hash:
            result = subprocess.run(
                ["git", "rev-parse", "--short", "HEAD"],
                capture_output=True,
                check=True
            )

            short_hash = result.stdout.decode("utf-8").replace("\n", "")
            config.cflags_module.append(f"-DGIT_COMMIT_HASH={short_hash}")

    def _after_emit(self, config: KokeshiConfig) -> None:
        """Performs all necessary behavior after emitting the Ninja build
        script

        Args:
            config (KokeshiConfig): Project configuration
        """

        pass

    def _emit_vars(self, writer: Writer, config: KokeshiConfig) -> None:
        """Emits the variables section of the Ninja build script

        Args:
            writer (Writer): Ninja writer
            config (KokeshiConfig): Project configuration
        """

        writer.comment("==================================================")
        writer.comment("Variables")
        writer.comment("==================================================")

        # Ninja requirements
        writer.comment("Ninja")
        writer.variable("ninja_required_version", NINJA_REQUIRED_VERSION)
        writer.newline()

        # Directories
        writer.comment("Directories")
        writer.variable("assets_dir",          config.assets_dir)
        writer.variable("build_dir",           config.build_dir)
        writer.variable("base_dir",            config.base_dir)
        writer.variable("romfs_dir",           config.romfs_dir)
        writer.variable("romfs_to_assets_dir", config.romfs_to_assets_dir)
        writer.variable("modules_dir",         config.modules_dir)
        writer.variable("include_dir",         config.include_dir)
        writer.variable("library_dir",         config.library_dir)
        writer.variable("loader_dir",          config.loader_dir)
        writer.variable("src_dir",             config.src_dir)
        writer.variable("tools_dir",           config.tools_dir)
        writer.variable("compiler_dir",        config._compiler_dir)
        writer.variable("linker_dir",          config._linker_dir)
        writer.variable("wibo_dir",            config._wibo_dir)
        writer.newline()

        # Tools
        writer.comment("Tools")
        writer.variable("wibo",              config._wibo)
        writer.variable("cc",                gen_exec_cmd(config._compiler))
        writer.variable("ld",                gen_exec_cmd(config._linker))
        writer.variable("configure",         config._configure)
        writer.variable("checkrom",          config._checkrom)
        writer.variable("install_tool",      config._install_tool)
        writer.variable("make_compile_cmds", config._make_compile_cmds)
        writer.variable("python",            config._python)
        writer.newline()

        # Files
        writer.variable("ninja_script",     NINJA_SCRIPT_NAME)
        writer.variable("compile_commands", COMPILE_COMMANDS_NAME)

        # Compiler flags
        writer.comment("Compiler flags")
        writer.variable("cflags_common", " ".join(config.cflags_common))
        writer.newline()

        writer.variable("cflags_module", " ".join(config.cflags_module))
        writer.newline()

        writer.variable("cflags_debug", " ".join(config.cflags_debug))
        writer.newline()

        writer.variable("cflags_release", " ".join(config.cflags_release))
        writer.newline()

        writer.variable("cflags_include", " ".join(config.cflags_include))
        writer.newline()

    def _emit_rules(self, writer: Writer, config: KokeshiConfig) -> None:
        """Emits the build rules section of the Ninja build script

        Args:
            writer (Writer): Ninja writer
            config (KokeshiConfig): Project configuration
        """

        writer.comment("==================================================")
        writer.comment("Rules")
        writer.comment("==================================================")

        rule_install_tool(writer, config)
        rule_reconfigure(writer, config)
        rule_checkrom(writer, config)
        rule_compile(writer, config)
        rule_link(writer, config)
        rule_install_binary(writer, config)
        rule_install_asset(writer, config)
        rule_clangd_commands(writer, config)

    def _emit_targets(self, writer: Writer, config: KokeshiConfig) -> None:
        """Emits the build targets section of the Ninja build script

        Args:
            writer (Writer): Ninja writer
            config (KokeshiConfig): Project configuration
        """

        writer.comment("==================================================")
        writer.comment("Targets")
        writer.comment("==================================================")

        target_tools(writer, config)

        target_install_tool(writer, config, "codewarrior", "$compiler_dir")
        target_install_tool(writer, config, "kamek", "$linker_dir")

        if not IS_WINDOWS:
            target_install_tool(writer, config, "wibo", "$wibo_dir")

        target_reconfigure(writer, config)

        # Loader source code
        loader_units = [
            CompileUnit(config, file) for file in
            find_files(config.loader_dir, config.src_extensions)
        ]
        for unit in loader_units:
            target_compile(writer, config, unit, flags="$cflags_common")

        # Module source code
        module_units = [
            *[CompileUnit(config, file) for file in
              find_files(config.library_dir, config.src_extensions)],

            *[CompileUnit(config, file) for file in
              find_files(config.src_dir, config.src_extensions)]
        ]
        for unit in module_units:
            target_compile(writer, config, unit,
                           flags="$cflags_common $cflags_module")

        # Loader/module binaries
        for pack in config.packs:
            target_checkrom(writer, config, pack)

            loader = KamekLoader(config, pack)
            target_link(writer, config, loader, loader_units)
            target_install_binary(writer, config, loader)

            module = KamekModule(config, pack)
            target_link(writer, config, module, module_units)
            target_install_binary(writer, config, module)

        # Project assets
        for pack in config.packs:
            assets = [
                Asset(config, pack, file) for file in
                find_files(pathjoin(config.assets_dir, pack))
            ]

            for asset in assets:
                target_install_asset(writer, config, asset)

        target_clangd_commands(writer, config)
