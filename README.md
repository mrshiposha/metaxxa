# metaxxa
C++17 header-only library for meta programming

## Getting library header
See [releases](https://github.com/MrShiposha/metaxxa/releases)

## Tested compilers
 * **Visual Studio 2017** -- works ✔️
 * **Apple LLVM version 10.0.0 (clang-1000.11.54.4)** -- works ✔️
 * **clang 6.0 with libc++ on Linux** -- works ✔️
 * **GCC** -- unsupported ❌

## How to build tests
**CMake minimum version 3.12 is required**

`git clone https://github.com/MrShiposha/metaxxa.git`

`cd metaxxa`

`mkdir build`

`cd build`

----
### Platform dependent
#### Windows
`cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 15 2017 Win64"`

#### macOS
`cmake .. -DCMAKE_BUILD_TYPE=Debug -GXcode`

### Linux
* Install **clang** and make it visible for CMake
#### Ubuntu
  `sudo update-alternatives --install /usr/bin/c c /usr/bin/clang 200`
  
  `sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 200`
  
  `sudo update-alternatives --install /usr/bin/ld ld /usr/bin/lld 200`

  `cmake .. -DCMAKE_BUILD_TYPE=Debug`

----
`cmake --build .`

## Run tests
`{metaxxa_directory}/build/tests/Debug/metaxxa-tests`

OR `{metaxxa_directory}/build/tests/Release/metaxxa-tests`

OR `{metaxxa_directory}/build/tests/metaxxa-tests`

Actual path depends on CMake generator and CMAKE_BUILD_TYPE value
