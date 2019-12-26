CMake Error at CMakeLists.txt:49 (find_package):
  By not providing "FindFOO_BAR.cmake" in CMAKE_MODULE_PATH this project has
  asked CMake to find a package configuration file provided by "FOO_BAR", but
  CMake did not find one.

  Could not find a package configuration file provided by "FOO_BAR" with any
  of the following names:

    FOO_BARConfig.cmake
    foo_bar-config.cmake

  Add the installation prefix of "FOO_BAR" to CMAKE_PREFIX_PATH or set
  "FOO_BAR_DIR" to a directory containing one of the above files.  If
  "FOO_BAR" provides a separate development package or SDK, be sure it has
  been installed.


And you're wondering where it tried to find the library, you can use the undocumented CMAKE_FIND_DEBUG_MODE global variable for getting a more verbose output

$ cmake -D CMAKE_FIND_DEBUG_MODE=ON ..

The command has two modes by which it searches for packages: “Module” mode and “Config” mode. 
Module mode is available when the command is invoked with the above reduced signature. 
CMake searches for a file called Find<package>.cmake in the CMAKE_MODULE_PATH followed by the CMake installation. 
If the file is found, it is read and processed by CMake. It is responsible for finding the package, 
checking the version, and producing any needed messages. 
Many find-modules provide limited or no support for versioning; check the module documentation. 
If no module is found and the MODULE option is not given the command proceeds to Config mode.

The CONFIG option may be used to skip Module mode explicitly and switch to Config mode. 
It is synonymous to using NO_MODULE. Config mode is also implied by use of options not specified 
in the reduced signature.

Config mode attempts to locate a configuration file provided by the package to be found. 
A cache entry called <package>_DIR is created to hold the directory containing the file. 
By default the command searches for a package with the name <package>. 
If the NAMES option is given the names following it are used instead of <package>. 
The command searches for a file called <name>Config.cmake or <lower-case-name>-config.cmake 
for each name specified. A replacement set of possible configuration file names may be 
given using the CONFIGS option. The search procedure is specified below. 
Once found, the configuration file is read and processed by CMake. Since the file is provided 
by the package it already knows the location of package contents. The full path to the 
configuration file is stored in the cmake variable <package>_CONFIG.

All configuration files which have been considered by CMake while searching for an installation 
of the package with an appropriate version are stored in the cmake variable <package>_CONSIDERED_CONFIGS, 
the associated versions in <package>_CONSIDERED_VERSIONS.

If the package configuration file cannot be found CMake will generate an error describing the problem 
unless the QUIET argument is specified. If REQUIRED is specified and the package is not found a 
fatal error is generated and the configure step stops executing. If <package>_DIR has been set to 
a directory not containing a configuration file CMake will ignore it and search from scratch.
