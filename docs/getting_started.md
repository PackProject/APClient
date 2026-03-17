# Dependencies

## Tools

This repository utilizes Python and C# for many of its tools.

The buildsystem will grab prebuilt versions of most tools, but you will still need to do the following:  

- Install [Python](https://www.python.org/downloads/).
  - If you are on Windows, add Python to your `%PATH%` environment variable.
- Install the required Python packages via `pip`.
  - From the root directory of the repository: `python -m pip install -r requirements.txt`
- Install the [.NET 10.0 Runtime](https://dotnet.microsoft.com/en-us/download/dotnet/10.0).

On non-Windows systems, [wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

> [!NOTE]
> `wibo` is required to run the CodeWarrior compiler, which we must use to maintain interoperability with the base game.

## Building

- Clone the repository:

  ```sh
  git clone https://github.com/PackProject/KaizoWiiPlay.git
  ```

> [!IMPORTANT]
> The tools in this repository expect to be invoked from the repository root.
>
> Please ensure that you are running commands from the root directory.

- For each game that you want to build for, extract a dump of the game disc.
  - In Dolphin Emulator, right-click the game and navigate to `Properties > Filesystem`.
  - Right-click the `Disc` in the file tree, and select `Extract Entire Disc...`
  - Select one of the following directories based on the game you are extracting:
    - Wii Sports: `romfs/sports/`
    - Wii Play: `romfs/party/`
    - Wii Sports Resort: `romfs/resort/`

- For each game that you want to build for, create a base copy of the executable (`.dol`) file.
  - Wii Sports: `romfs/sports/DATA/sys/main.dol` -> `base/StaticSports.dol`
  - Wii Play: `romfs/party/DATA/sys/main.dol` -> `base/StaticParty.dol`
  - Wii Sports Resort: `romfs/resort/DATA/sys/main.dol` -> `base/StaticResort.dol`

- Configure the build script:

  ```sh
  python configure.py
  ```

- Invoke the build script:

  ```sh
  ninja
  ```

## Running

The patched DOL and your code modules are output in the `build/` directory, and are also automatically installed into the `romfs` folder(s) for ease of testing.

> [!CAUTION]
> The Ninja build script cannot yet tell when new source code or asset files are added (see [issue #52](https://github.com/PackProject/KaizoWiiPlay/issues/52)).
>
> When adding new files, please first re-run `configure.py` before invoking `ninja` to ensure that your changes are detected.
