# ============================================================================#
#                                                                             #
# Shared constants                                                            #
#                                                                             #
# ============================================================================#

import sys
from os.path import join as pathjoin

PYTHON = sys.executable
"""Path to the Python executable used to invoke this script
"""

CONFIGURE_SCRIPT = "configure.py"
"""Name of the main configure script
"""

CHECKROM_SCRIPT = pathjoin("ninja", "checkrom.py")
"""Name of the ROM check script
"""

CHECKROM_STAMP = "checkrom.stamp"
"""Build directory name of the checkrom Ninja stamp file
"""

INSTALL_TOOL_SCRIPT = pathjoin("ninja", "install_tool.py")
"""Tools directory path to the tool installer script
"""

MAKE_COMPILE_CMDS_SCRIPT = pathjoin("ninja", "make_compile_cmds.py")
"""Tools directory path to the Clangd compile commands script
"""

COMPILE_COMMANDS_NAME = "compile_commands.json"
"""Name of the Clangd compile commands file
"""

LINKER_DIR = "kamek"
"""Name of the tools directory where the linker is stored
"""

LINKER_NAME = "Kamek"
"""Name of the linker executable
"""

COMPILER_DIR = "codewarrior"
"""Name of the tools directory where the compilers are stored
"""

COMPILER_NAME = "mwcceppc.exe"
"""Name of the compiler executable
"""

WIBO_DIR = "wibo"
"""Name of the tools directory where wibo is stored
"""

WIBO_NAME = "wibo"
"""Name of the wibo executable
"""

GITHUB_ORG_URL = "https://github.com/PackProject"
"""URL to the PackProject organization on GitHub
"""

DOL_HASHES_NAME = pathjoin("ninja", "dol_hashes.json")
"""Tools directory path to the known good DOL hashes
"""
