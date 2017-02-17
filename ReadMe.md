# cpp-grapher

### Installation Instructions
*These instructions work in a Bash environment.  If you are on Windows,
Bash is now officially supported!  (Windows 10 required).
Installation instructions can be found [here](https://msdn.microsoft.com/en-us/commandline/wsl/install_guide).*

- Clone the repository to the desired location on your system
    - `git clone --recursive git@github.com:udacity/cpp-grapher.git`
      
- `cd` into the repository
    - `cd cpp-grapher`

- Your project is ready for use!

### Build project & run tests (assuming you are in the project root folder, as per above instructions)
```
mkdir -p build && cd build
cmake -G "Unix Makefiles" .. && cmake --build . --target Tests -- -j 8
Sources/Tests/Tests
```

### Build project & run application (assuming you are in the project root folder, as per above instructions)
```
mkdir -p build && cd build
cmake -G "Unix Makefiles" .. -DCMAKE_BUILD_TYPE=Release && cmake --build . --target cpp-grapher
Sources/Modules/cpp-grapher/cpp-grapher input_datapoints_file output_graph_filename.png
```

### IDE Support
If you are more comfortable with GUI-based development, I recommend taking a look at [JetBrains' CLion](https://www.jetbrains.com/clion/).  It works with C++11/14 with "Intellisense" and refactoring tools, CMake dependency management and has cross-platform (Mac/Linux/Windows) support. 

### License terms for Repository Submodule Dependencies
- [tinyutf8](https://github.com/bradleygibson/tinyutf8/blob/master/LICENCE)

### License terms for Binary Dependencies
- [ImageMagick (for Magick++)](https://github.com/ImageMagick/ImageMagick/blob/master/LICENSE)
	- Binary installation instructions (OS X): `brew install imagemagick --with-quantum-depth-8`
