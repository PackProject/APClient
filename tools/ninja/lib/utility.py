# ============================================================================#
#                                                                             #
# Utility functions                                                           #
#                                                                             #
# ============================================================================#

from hashlib import sha1
from os import chmod, walk
from os.path import isdir
from os.path import join as pathjoin
from os.path import sep, splitext

from .exceptions import KokeshiException


def find_files(root_path: str, extensions: list[str] = None) -> list[str]:
    """Searches recursively from the root path for all files matching any of
    the specified file extensions.

    If no extensions are specified, all files are allowed.

    Args:
        root_path (str): Root search path
        extensions (list[str]): File extensions

    Returns:
        list[str]: All files matching the specified conditions
    """

    found = []

    for dirpath, _, filenames in walk(root_path):

        for name in filenames:
            # Ignore hidden files
            if name.startswith("."):
                continue

            _, ext = splitext(name)

            if not extensions or ext in extensions:
                found.append(pathjoin(dirpath, name))

    # Alphabetical order
    found.sort()

    return found


def find_directories(root_path: str, recursive: bool) -> list[str]:
    """Searches from the root path for all subdirectories.
    The `recursive` argument controls whether the search recurses into
    subdirectories.

    The root path (`root_path`) is included in the list of results.

    Args:
        root (str): Root search path
        recursive (bool): Whether to recurse into subdirectories

    Returns:
        list[str]: All subdirectories
    """

    found = [root_path]

    for dirpath, dirnames, _ in walk(root_path):
        found += [pathjoin(dirpath, x) for x in dirnames]

        if not recursive:
            break

    return found


def chmod_recursive(path: str, mode: int):
    """Applies a file permissions change to the given path.
    If the path is a directory, the changes are recursively applied.

    Args:
        path (str): Filepath
        mode (int): Permissions
    """

    if not isdir(path):
        chmod(path, mode)
        return

    for root, _, files in walk(path):
        for it in files:
            chmod_recursive(pathjoin(root, it), mode)


def windows_path(path: str) -> str:
    """Converts a given filepath to Windows format

    Args:
        path (str): Filepath

    Returns:
        str: Windows filepath
    """

    return path.replace(sep, "\\")


def unix_path(path: str) -> str:
    """Converts a given filepath to UNIX format

    Args:
        path (str): Filepath

    Returns:
        str: UNIX filepath
    """

    return path.replace(sep, "/")


def calc_sha1(path: str) -> str:
    """Calculates the SHA-1 hash of the specified file

    Args:
        path (str): Filepath

    Returns:
        str: SHA-1 hex digest
    """

    ctx = sha1()

    try:
        with open(path, "rb") as f:
            ctx.update(f.read())
    except OSError as exc:
        raise KokeshiException(f"Can't open file: {path}") from exc

    return ctx.hexdigest()
