# kvantum-on-windows

<p align="center"><img src="https://github.com/ensisoft/kvantum-on-windows/blob/master/screens/preview.png" width= 600"/></p>

Kvantum Qt5 style engine port for Windows. Currently a bit hacky, use at your own risk. The default Kvantum theme is built into the library so in order to use that no runtime (.svg etc file resources) are needed! Qt looks for style plugins inside your applications styles/ folders. You should be able to drop Kvantum.dll there once you've built it then it should just work. There are two ways to ask Qt to use the style.

- Either pass -style command line parameter at your application startup
- Call QApplication::setStyle("kvantum") or QApplication::setStyle("kvantum-dark")

You should also be able to use your preferred svg theme and built it into the library if you prefer to do so. Basically easiest solution should be to copy the themes .kvconfig and .svg file into default/ and overwrite the original files and rebuild the library.

Current TODO:
* Merge new changes from upstream.
* Cleanup PBSKSkin (is this even in upstream??)


Building:
* msvs2019
* cmake
* Qt5 (expected install location is c:/5.15.2/msvc2019_64)

```
$ git clone https://github.com/ensisoft/kvantum-on-windows
$ cd kvantum-on-windows
$ mkdir build
$ cmake -G "Visual Studio 16 2019" ..
$ cmake --build . --config Release
$ cmake --install . --config Release
$ cd ../bin
$ Test.exe


Thanks to @Tsujan for the original Kvantum engine and @celibol for the initial Windows port.

