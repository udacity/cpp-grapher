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
cmake -G "Unix Makefiles" .. -DCMAKE_BUILD_TYPE=Release && cmake --build . --target App
Sources/Modules/App/App
```

### IDE Support
If you are more comfortable with GUI-based development, I recommend taking a look at [JetBrains' CLion](https://www.jetbrains.com/clion/).  It works with C++11/14 with "Intellisense" and refactoring tools, CMake dependency management and has cross-platform (Mac/Linux/Windows) support. 

### License terms for Repository Dependencies
- [any](https://github.com/thelink2012/any/blob/master/LICENSE_1_0.txt)
- [Catch](https://github.com/philsquared/Catch/blob/master/LICENSE_1_0.txt)
- [Optional](https://github.com/akrzemi1/Optional/blob/master/LICENSE_1_0.txt)
- [utfcpp](https://github.com/nemtrif/utfcpp/blob/master/source/utf8.h)
- [variant](https://github.com/tcbrindle/variant/blob/master/variant)
