# RECSBR

RECSBR is a remake of the Cave Story Beta.

## Dependencies

* SDL2 (if `BACKEND_AUDIO` or `BACKEND_PLATFORM` are set to `SDL2`)
* GLFW3 (if `BACKEND_PLATFORM` is set to `GLFW3`)
* FreeType

If these are not found, they will be built locally.

In addition, `pkg-config` is required for builds that require static-linkage.

A list of dependencies for specific platforms could be found [on the CSE2 wiki](https://github.com/Clownacy/Cave-Story-Engine-2/wiki/Dependency-lists).

## Building

This project uses CMake, allowing it to be built with a range of compilers.

Switch to the terminal (Visual Studio users should open the [Developer Command Prompt](https://docs.microsoft.com/en-us/dotnet/framework/tools/developer-command-prompt-for-vs)) and `cd` into this folder. After that, generate the files for your build system with:

```
cmake -B build -DCMAKE_BUILD_TYPE=Release
```

MSYS2 users should append `-G"MSYS Makefiles" -DPKG_CONFIG_STATIC_LIBS=ON` to this command, also.

You can also add the following flags:

Name | Function
--------|--------
`-DJAPANESE=ON` | Enable the Japanese-language build (instead of the unofficial Aeon Genesis English translation [Also, this beta remake doesn't have Japanese support yet])
`-DFIX_BUGS=ON` | Enabled by default - Fix various bugs in the game
`-DDEBUG_SAVE=ON` | Re-enable the ability to drag-and-drop save files onto the window
`-DBACKEND_RENDERER=OpenGL3` | Render with OpenGL 3.2 (hardware-accelerated)
`-DBACKEND_RENDERER=OpenGLES2` | Render with OpenGL ES 2.0 (hardware-accelerated)
`-DBACKEND_RENDERER=SDLTexture` | (Default) Render with SDL2's Texture API (hardware-accelerated) (note: requires `-DBACKEND_PLATFORM=SDL2`)
`-DBACKEND_RENDERER=WiiU` | Render with the Wii U's GX2 API (hardware-accelerated)
`-DBACKEND_RENDERER=Software` | Render with a handwritten software-renderer
`-DBACKEND_AUDIO=SDL2` | (Default) Deliver audio with SDL2 (software-mixer)
`-DBACKEND_AUDIO=miniaudio` | Deliver audio with miniaudio (software-mixer)
`-DBACKEND_AUDIO=WiiU-Hardware` | Deliver audio with Wii U's AXVoice API (hardware-accelerated) (WARNING - currently broken: voices randomly disappear for unknown reasons)
`-DBACKEND_AUDIO=WiiU-Software` | Deliver audio with Wii U's AXVoice API (software-mixer)
`-DBACKEND_AUDIO=Null` | Don't deliver audio at all (WARNING - game will have no audio)
`-DBACKEND_PLATFORM=SDL2` | (Default) Use SDL2 for miscellaneous platform-dependant operations
`-DBACKEND_PLATFORM=GLFW3` | Use GLFW3 for miscellaneous platform-dependant operations
`-DBACKEND_PLATFORM=WiiU` | Use the Wii U's native APIs for miscellaneous platform-dependant operations
`-DBACKEND_PLATFORM=Null` | Don't do platform-dependant operations at all (WARNING - game will have no video or input)
`-DLTO=ON` | Enable link-time optimisation
`-DPKG_CONFIG_STATIC_LIBS=ON` | On platforms with pkg-config, static-link the dependencies (good for Windows builds, so you don't need to bundle DLL files)
`-DMSVC_LINK_STATIC_RUNTIME=ON` | Link the static MSVC runtime library, to reduce the number of required DLL files (Visual Studio only)
`-DFORCE_LOCAL_LIBS=ON` | Compile the built-in versions of SDL2, GLFW3, and FreeType instead of using the system-provided ones
`-DEXTRA_SOUND_FORMATS=ON` | Enable support for alternate music/SFX formats, include Ogg Vorbis, FLAC, and PxTone (not to be confused with PixTone)
`-DCLOWNAUDIO_STB_VORBIS=ON` | Enable support for Ogg Vorbis music/SFX
`-DCLOWNAUDIO_DR_FLAC=ON` | Enable support for FLAC music/SFX
`-DCLOWNAUDIO_LIBXMPLITE=ON` | Enable support for .it, .xm, .mod, .s3m music/SFX
`-DCLOWNAUDIO_PXTONE=ON` | Enable support for PxTone music/SFX (not to be confused with PixTone)
`-DDEVTERM=ON` | Enable support for the ClockworkPi DevTerm

You can pass your own compiler flags with `-DCMAKE_C_FLAGS` and `-DCMAKE_CXX_FLAGS`.

You can then compile CSE2 with this command:

```
cmake --build build --config Release
```

If you're a Visual Studio user, you can open the generated `CSE2.sln` file instead, which can be found in the `build` folder.

Once built, the executables can be found in the `game_english`/`game_japanese` folder, depending on the selected language.

### Building for the Wii U

To target the Wii U, you'll need devkitPro, and WUT.

First, add the devkitPPC tools directory to your PATH (because WUT's CMake support is broken, as of writing):

```
PATH=$PATH:$DEVKITPPC/bin
```

Then, generate the build files with this command:

```
cmake -B buildwiiu -DCMAKE_BUILD_TYPE=Release -DFORCE_LOCAL_LIBS=ON -DBACKEND_PLATFORM=WiiU -DBACKEND_RENDERER=WiiU -DBACKEND_AUDIO=WiiU-Software -DCMAKE_TOOLCHAIN_FILE=$DEVKITPRO/wut/share/wut.toolchain.cmake
```

Finally, build the game with this command:

```
cmake --build buildwiiu
```

This will build a binary, but you still need to convert it to an `.rpx` file that can be ran on your Wii U.

First, we need to strip the binary:

```
powerpc-eabi-strip -g game_english/CSE2
```

Then, we convert it to an `.rpx`:
```
elf2rpl game_english/CSE2 game_english/CSE2.rpx
```

`game_english/CSE2.rpx` is now ready to be ran on your Wii U. This port expects the data folder to be in a folder called `CSE2-enhanced-lite-en`/`CSE2-enhanced-lite-jp` on the root of your SD card.

## Licensing

Being a decompilation, the majority of the code in this project belongs to Daisuke "Pixel" Amaya - not us. This repository is licensed under The GNU General Public License v3.0. I haven't read all of it, so hopefully I'm not doing something ridiculous by licensing code I don't own. 
