#!/usr/bin/env python3

# ============================================================================#
#                                                                             #
# Kokeshi project build script                                                #
#                                                                             #
# ============================================================================#


from tools.ninja.lib.config import KokeshiConfig
from tools.ninja.lib.project import KokeshiProject


def main():
    """Program entrypoint
    """

    config = KokeshiConfig.load()

    proj = KokeshiProject(config)
    proj.emit()


if __name__ == "__main__":
    main()
