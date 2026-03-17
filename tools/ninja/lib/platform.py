# ============================================================================#
#                                                                             #
# Platform utilies                                                            #
#                                                                             #
# ============================================================================#

import sys

from .exceptions import KokeshiException

# File extension for executables on Windows
WINDOWS_EXE_EXT = ".exe"

# Whether the current operating system is Windows
IS_WINDOWS = sys.platform.startswith("win32")

# Whether the current operating system is Mac OS
IS_MACOS = sys.platform.startswith("darwin")

# Whether the current operating system is Linux
IS_LINUX = sys.platform.startswith("linux")


if not any([IS_WINDOWS, IS_MACOS, IS_LINUX]):
    raise KokeshiException(f"Unknown platform: {sys.platform}")


def get_release_os() -> str:
    """Gets the OS name used for GitHub releases
    """

    if IS_WINDOWS:
        return "windows"

    if IS_MACOS:
        return "macos"

    if IS_LINUX:
        return "linux"

    raise KokeshiException(f"Unknown platform: {sys.platform}")


def gen_copy_cmd(src_path: str, dst_path: str) -> str:
    """Creates a command to copy a file

    Args:
        src_path (str): Source filepath
        dst_path (str): Destination filepath

    Returns:
        str: Copy command string
    """

    # All POSIX systems use Unix copy
    if not IS_WINDOWS:
        return f"cp -f {src_path} {dst_path}"

    return f"xcopy {src_path} {dst_path}* /Q /Y"


def gen_exec_cmd(path: str) -> str:
    """Creates a command to run a Windows executable

    Args:
        path (str): Executable path

    Returns:
        str: Invocation command string
    """

    is_win_exe = path.endswith(WINDOWS_EXE_EXT)

    if IS_WINDOWS:
        if is_win_exe:
            return path

        # Assume Windows version exists
        return f"{path}{WINDOWS_EXE_EXT}"

    # IS_MACOS || IS_LINUX
    else:
        # Non-Windows systems must use wibo to run PE executables
        if is_win_exe:
            return f"$wibo {path}"

        return path


def chain_commands(commands: list[str]) -> str:
    """Chains multiple shell commands into a single command

    Args:
        commands (list[str]): Shell commands to execute

    Returns:
        str: Single command string
    """

    command = " && ".join(commands)

    # Windows also requires a subshell
    if IS_WINDOWS:
        return f"cmd /c {command}"

    return command
