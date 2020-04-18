
# AWS SDK

Here, there are 2 directories

- sns-adpater: Contains the SNS adapter files and Readme(containing steps to run the sns adapter)
- lambda-adapter: Contains the Lambda adapter files and Readme(for steps to run).

**This Readme contains steps to setup the AWS SDK and how to run a Test application using it.**

# Running a Test Application

First Setup the AWS C++ SDK and then Build the application

# Setting up the AWS C++ SDK

> Note: All steps were performed using Ubuntu 18.04.4 LTS.
> Also, this installation is using command line tools.
> Refer [aws-sdk-cpp Readme](https://github.com/aws/aws-sdk-cpp/blob/master/README.md) for more details.

This Readme contains the steps to setup the AWS C++ SDK.

## Installing dependencies

### Installing header files and Packages required for compiling the SDK:

```
sudo apt-get install libcurl4-openssl-dev libssl-dev uuid-dev zlib1g-dev libpulse-dev
```

### Installing **cmake** (version >= 3.2):

Install dependencies

```
sudo apt-get update
sudo apt-get install apt-transport-https ca-certificates gnupg software-properties-common wget
```

Obtain the signing key

```
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | sudo apt-key add -
```

Add kitware repository to sources list.

```
sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'
sudo apt-get update
```

Install cmake

```
sudo apt-get install cmake
```

> Visit [Kitware apt](https://apt.kitware.com/) for more details on cmake installation.

## Creating an Out-of-source build

This will install aws-sdk as **Release build**

Clone the AWS SDK C++ repository from GitHub

```
git clone https://github.com/aws/aws-sdk-cpp.git
```

Make a seperate build directory(for e.g. build-aws-sdk) and enter it

```
mkdir build-aws-sdk
cd build-aws-sdk
```

Now, build files using cmake

```
cmake <path/to/the/aws-sdk-cpp/directory>
```

Build the SDK binaries

```
sudo make
```

Finally, Install the SDK

```
sudo make install
```

Now, we have AWS SDK installed in the **build-aws-sdk** directory.

# Building an application with cmake

AWS SDK is installed, now build the test application

- Create a directory say **test**. Now, create the **test.cpp** file inside this directory, which will contain the code for application.
- Export environment variable specifying the **build-aws-sdk** path. This path contains the path to build directory which was used in above setup phase.

```
export CMAKE_PREFIX_PATH=/home/manas/gsoc/build-aws-sdk
```

- Create a file named **CMakeLists.txt** which will contain the CMake relevant values. For, example:

```
# Minimal CMakeLists.txt for the AWS SDK for C++.
cmake_minimum_required(VERSION 3.2)

# Use shared libraries, which is the default for the AWS C++ SDK build.
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

project(test)

# Locate the AWS SDK for C++ package required. Like s3 and sns packages.
find_package(AWSSDK REQUIRED COMPONENTS s3 sns)

# The executable name and its sourcefiles.
add_executable(test test.cpp)

# Build using the C++ standard version 11.
target_compile_features(test PUBLIC cxx_std_11)

# The libraries used by your executable.
target_link_libraries(test ${AWSSDK_LINK_LIBRARIES})
```

- Use **CMake** to generate build directory for **test** application

```
cmake ../test
```

- Use **make** to finally build the **test** application

```
make
```

- This will generate the build files and the executable **test** file which was specified in the **CMakeLists.txt**. Run this executable as

```
./test <command line arguments>
```
