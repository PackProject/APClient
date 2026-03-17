#!/usr/bin/env python3

# ============================================================================#
#                                                                             #
# Tool installer                                                              #
#                                                                             #
# ============================================================================#

from argparse import ArgumentParser, Namespace
from enum import StrEnum
from io import BytesIO
from zipfile import ZipFile

import requests
from os import makedirs
from os.path import dirname
from lib.config import KokeshiConfig
from lib.define import GITHUB_ORG_URL
from lib.exceptions import KokeshiException
from lib.platform import get_release_os
from lib.utility import chmod_recursive


class ToolName(StrEnum):
    """Tool names supported by this script
    """

    def __repr__(self):
        """String reprsentation operator
        """
        return self.value

    CODEWARRIOR = "codewarrior"
    """The CodeWarrior compiler
    """

    KAMEK = "kamek"
    """The Kamek linker
    """

    WIBO = "wibo"
    """The wibo Windows executable wrapper
    """

    WORKBENCH = "workbench"
    """The WorkBench asset manager
    """


def main():
    """Program entrypoint
    """

    parser = ArgumentParser(
        prog="install_tool",
        description="Kokeshi tool installer"
    )

    parser.add_argument(
        "-t",
        "--tool",
        type=str,
        choices=list(ToolName),
        required=True,
        metavar="<name>",
        help="Name of the tool to install"
    )

    args = parser.parse_args()
    config = KokeshiConfig.load()

    try:
        install_tool(args, config)
    except KokeshiException as exc:
        print(exc)
        exit(1)


def install_tool(args: Namespace, config: KokeshiConfig):
    """Attempts to install the specified tool

    Args:
        args (Namespace): Command-line arguments
        config (KokeshiConfig): Kokeshi project configuration
    """

    install_proc_tbl = {
        ToolName.CODEWARRIOR: install_codewarrior,
        ToolName.KAMEK: install_kamek,
        ToolName.WIBO: install_wibo,
        ToolName.WORKBENCH: install_workbench,
    }

    assert args.tool in install_proc_tbl
    install_proc_tbl[args.tool](config)


def install_codewarrior(config: KokeshiConfig):
    """Attempts to install the CodeWarrior compiler

    Args:
        config (KokeshiConfig): Kokeshi project configuration
    """

    COMPILERS_URL = "/".join([
        "https://files.decomp.dev",
        "compilers_latest.zip",
    ])
    """URL of the latest CodeWarrior compiler set
    """

    download_artifact(COMPILERS_URL, config._compiler_dir)


def install_kamek(config: KokeshiConfig):
    """Attempts to install the Kamek linker

    Args:
        config (KokeshiConfig): Kokeshi project configuration
    """

    KAMEK_URL = "/".join([
        GITHUB_ORG_URL,
        "Kamek/releases/download",
        config.kamek_ver,
        f"kamek_{get_release_os()}.zip"
    ])
    """URL of the Kamek linker release
    """

    download_artifact(KAMEK_URL, config._linker_dir)


def install_wibo(config: KokeshiConfig):
    """Attempts to install the wibo linker

    Args:
        config (KokeshiConfig): Kokeshi project configuration
    """

    # Convert get_release_os result to wibo arch
    release_tbl = {
        "windows": "x86_64",
        "macos": "macos",
        "linux": "i686"
    }

    WIBO_URL = "/".join([
        "https://github.com/decompals",
        "wibo/releases/download",
        config.wibo_ver,
        f"wibo-{release_tbl[get_release_os()]}"
    ])
    """URL of the Kamek linker release
    """

    download_artifact(WIBO_URL, config._wibo)


def install_workbench(config: KokeshiConfig):
    """Attempts to install the WorkBench asset manager

    Args:
        config (KokeshiConfig): Kokeshi project configuration
    """

    raise KokeshiException("WorkBench not supported yet!")


def download_artifact(url: str, path: str):
    """Attempts to download a file over HTTP.

    Args:
        url (str): File download URL
        path (str): Output filepath
    """

    is_zip_file = url.endswith(".zip")

    response = requests.get(
        url,
        headers={"User-Agent": "Mozilla/5.0"},
        timeout=15,
        allow_redirects=True,
        stream=True
    )

    try:
        response.raise_for_status()
    except requests.HTTPError as e:
        raise KokeshiException(f"Failed to download the tool: {e}")

    if is_zip_file:
        stream = BytesIO(response.content)
        file = ZipFile(stream)
        file.extractall(path)
    else:
        makedirs(dirname(path), exist_ok=True)

        with open(path, "wb+") as f:
            f.write(response.content)

    # rwx r-x r-x
    chmod_recursive(path, 0o755)


if __name__ == "__main__":
    main()
