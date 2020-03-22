# Setting up the AWS C++ SDK

> Note: All steps were performed using Ubuntu 18.04.4 LTS.

> Also, this installation is using command line tools.

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

This will build aws-sdk as **Release build**

Clone the AWS SDK C++ repository from GitHub

```
git clone https://github.com/aws/aws-sdk-cpp.git
```

Make a seperate build directory(for e.g. build-aws-sdk) and enter it

```
mkdir build-aws-sdk
cd build-aws-sdk
```

Now, build using cmake

```
cmake <path/to/the/aws-sdk-cpp/directory>
```

Now, we have AWS SDK built in the **build-aws-sdk** directory.
