#!/usr/bin/env python3

# ============================================================================#
#                                                                             #
# Base ROM checker                                                            #
#                                                                             #
# ============================================================================#


from json import load
from os.path import exists
from os.path import join as pathjoin
from textwrap import dedent

from lib.config import KokeshiConfig
from lib.define import CHECKROM_STAMP, DOL_HASHES_NAME
from lib.exceptions import KokeshiException
from lib.utility import calc_sha1


def main():
    """Program entrypoint
    """

    config = KokeshiConfig.load()

    try:
        checkrom(config)
    except KokeshiException as exc:
        print(dedent(str(exc)))
        exit(1)


def checkrom(config: KokeshiConfig):
    """Checks the integrity of the base ROM

    Args:
        config (KokeshiConfig): Project configuration
    """

    with open(pathjoin(config.tools_dir, DOL_HASHES_NAME), "r") as f:
        dol_hashes = load(f)

    for pack in config.packs:
        if pack not in dol_hashes:
            raise KokeshiException(f"Unknown pack: {pack}")

        # Check that the ROM was extracted correctly
        romfs_path = f"{config.romfs_dir}/{pack}"
        partition_root = f"{romfs_path}/{config.romfs_to_assets_dir}"

        must_exist = [
            romfs_path,
            partition_root
        ]

        for path in must_exist:
            if not exists(romfs_path):
                raise KokeshiException(f"""
                    RomFS is missing a required directory: {path}
                    Please use Dolphin's 'Extract Game Disc...' at the following path: {romfs_path}
                """)

        # Check the integrity of the base DOL
        dol_path = f"{config.base_dir}/Static{pack.capitalize()}.dol"
        if not exists(dol_path):
            raise KokeshiException(f"""
                Base DOL file is missing: {dol_path}
                If you have a clean RomFS setup, you can take this from {romfs_path}/sys/main.dol.
            """)

        # TODO(kiwi) Revision is hardcoded until we support multiple (#38)
        dol_hash = calc_sha1(dol_path)
        dol_revision = "us_rev1"

        if dol_hash != dol_hashes[pack][dol_revision]:
            raise KokeshiException(f"""
                Base DOL does not have the correct hash: {dol_path}
            """)

    # Create the dummy file so Ninja won't re-run this script
    with open(pathjoin(config.build_dir, CHECKROM_STAMP), "w+") as f:
        pass


if __name__ == "__main__":
    main()
