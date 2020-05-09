# How to Build a large Project using CMakeLists

A typical CMake project will have a build directory in the same place as the top-level CMakeLists.txt. Make a build directory in the /home/workspace/cmake_example folder:

## Build Process
```
cd ....../PhoneDictionary
mkdir build
cd build
cmake ..
make
```

## Run Process
If everything has worked correctly, you should now be able to run your executable from the build folder:
```
cd ......./PhoneDictionary/build
./<your_executable_name>
```
This executable should print the output on terminal.
If you don't remember your executable name then, go to CMakeLists file and check the first argument in add_executable. This first argument is the executable name. `add_executable(your_executable_name  path_to_file_1  path_to_file_2 ...)`

## Recompile

Run only make, don't run cmake .. again otherwise there will be error and you need to remove build directory and redo again.

> ***Note:*** : _If you do re-run CMake, or if you are having problems with your build, it can be helpful to delete your build directory and start from scratch. Otherwise, some environment variables may not be reset correctly._
