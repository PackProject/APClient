#!/usr/bin/env python3

# ============================================================================#
#                                                                             #
# Clangd compile_commands.json generator                                      #
#                                                                             #
# ============================================================================#

from json import dump
from os import getcwd
from os.path import abspath
from os.path import join as pathjoin

from lib.config import KokeshiConfig
from lib.define import COMPILE_COMMANDS_NAME
from lib.paths import CompileUnit
from lib.utility import find_directories, find_files, unix_path


def main():
    """Program entrypoint
    """

    config = KokeshiConfig.load()
    make_compile_cmds(config)


def make_compile_cmds(config: KokeshiConfig):
    """Creates the compile_commands.json file for the clangd language
    parser
    """

    # Flags used with every source file
    cflags_common = [
        *config.cflags_common,
        *config.clangd_flags,
    ]

    # Flags used with module source files
    cflags_module = [
        *cflags_common,
        *config.cflags_module,
    ]

    # Loader source files
    loader_units = [
        CompileUnit(config, file) for file in
        find_files(config.loader_dir, config.src_extensions)
    ]

    # Module source files
    module_units = [
        *[CompileUnit(config, file) for file in
          find_files(config.library_dir, config.src_extensions)],

        *[CompileUnit(config, file) for file in
          find_files(config.src_dir, config.src_extensions)]
    ]

    commands = [
        *make_commands_impl(config, loader_units, cflags_common),
        *make_commands_impl(config, module_units, cflags_module)
    ]

    with open(COMPILE_COMMANDS_NAME, "w+", encoding="utf-8") as f:
        dump(commands, f, indent=4)


def make_commands_impl(config: KokeshiConfig, units: list[CompileUnit],
                       flags: list[str]) -> list:
    """Creates clangd compilation commands for the specified compilation units

    Args:
        config (KokeshiConfig): Project configuration
        units (list[CompileUnit]): Compilation units
        flags (list[str]): CodeWarrior compiler flags

    Returns:
        list: List of clangd command objects
    """

    # CodeWarrior -> Clang compiler flag conversion table
    mwcc_to_clang = {
        "-Cpp_exceptions off": ["-fno-cxx-exceptions"],
        "-Cpp_exceptions on": ["-fcxx-exceptions"],

        "-RTTI off": ["-fno-rtti"],
        "-RTTI on": ["-frtti"],

        "-lang c": ["--language=c", "--std=c99"],
        "-lang c99": ["--language=c", "--std=c99"],
        "-lang c++": ["--language=c++", "--std=c++03"],
        "-lang cplus": ["--language=c++", "--std=c++03"],

        "-enum min": ["-fshort-enums"],
        "-enum int": ["-fno-short-enums"],
    }

    # Common arguments
    common_args = [
        "clang",
        "-nostdinc",
        "-fno-builtin",
        "-fno-short-enums",
        "-fno-cxx-exceptions",
        "-fno-rtti",
        "-fshort-wchar",
        "-Wno-invalid-offsetof",
        "--target=powerpc-eabi",
        "--language=c++",
        "--std=c++11",
        "-D__MWERKS__",
        "-D__MWCC__",
    ]

    # Need to add BTE directories because they expect recursive search
    bte_dir = pathjoin(config.include_dir, "revolution", "BTE")
    common_args += [
        unix_path(f"-isystem{x}") for x in
        find_directories(bte_dir, recursive=True)
    ]

    cwd = getcwd()
    commands = []

    for unit in units:
        arguments = []
        arguments += common_args

        for flag in flags:
            flag_for_check = flag.strip().lower()

            # Clang equivalent exists
            if flag in mwcc_to_clang:
                arguments += mwcc_to_clang[flag]

            # Pass through all defines
            elif flag_for_check.startswith("-d"):
                arguments.append(flag)

            # Pass through all non-recursive includes
            elif flag_for_check.startswith("-i "):
                # Remove space for clangd
                flag = flag.replace("-i ", "-I")
                # UNIX path required
                arguments.append(unix_path(flag))

        directory = unix_path(cwd)
        file = unix_path(abspath(unit.path()))

        commands.append({
            "directory": directory,
            "file": file,
            "arguments": arguments,
        })

    return commands


if __name__ == "__main__":
    main()
