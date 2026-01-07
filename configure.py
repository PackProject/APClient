#!/usr/bin/env python3

# =============================================================================#
#                                                                              #
# Kokeshi build script                                                         #
#                                                                              #
# =============================================================================#

from tools.ninja_kokeshi import KokeshiProject

# =============================================================================#
# Project configuration                                                        #
# =============================================================================#
proj = KokeshiProject()

# =============================================================================#
# Game(s) that your mod should build for.
# By default, we try building for Wii Sports.
#
# You can build for multiple games by writing multiple pack names.
# Valid choices are: "sports" (Wii Sports), "play" (Wii Play), "resort" (WSR)
#
# To handle this in your code, expect preprocessor definitions of the format
# PACK_{NAME}, (i.e. PACK_SPORTS, PACK_RESORT).
#
# =============================================================================#
proj.packs = ["resort"]

# =============================================================================#
# Common compiler flags to apply across all code.
#
# See _cflags_common_internal inside 'ninja_kokeshi.py' to see
# which flags are already in use.
#
# =============================================================================#
proj.cflags_common = [
    "-maxerrors 1",
]

# =============================================================================#
# Compiler flags to apply across all module code.
#
# =============================================================================#
proj.cflags_module = []

# =============================================================================#
# Compiler flags to apply across all module code in release builds.
# (We don't support multiple build targets yet, so this goes unused.)
#
# =============================================================================#
proj.cflags_release = []

# =============================================================================#
# Compiler flags to apply across all module code in debug builds.
# (We don't support multiple build targets yet, so this goes unused.)
#
# =============================================================================#
proj.cflags_debug = []

# =============================================================================#
# Whether to include the latest Git repository commit hash (shortened) as a
# preprocessor definition ("GIT_COMMIT_HASH") when compiling the module.
#
# NOTE: It is assumed that the Git repository is the current working directory,
# and that command-line Git is installed on the current machine.
#
# =============================================================================#
proj.use_git_commit_hash = True

# =============================================================================#
# Creates the Ninja build script for your configuration.
#
# To see additional project settings, see KokeshiProject
# inside 'ninja_kokeshi.py'.
#
# =============================================================================#
proj.emit()
