# Setting up Ceph cluster
Follow given steps to setup the ceph cluster
> Note: Steps for Ubuntu 18.04.4 LTS

## Setup repository
Clone the repository using git
```
git clone https://github.com/ceph/ceph.git
```
Enter the cloned repository and checkout **nautilus** branch
```
git checkout nautilus
```
Checkout git submodules
```
git submodule update --init --recursive
```

## Installing dependencies
Run this shell script to install the dependencies
```
./install-deps.sh

```
## Building ceph code
Run this script to build code into the build directory
```
./do_cmake.sh

```
Enter the **build** directory and run this script
```
 make vstart -j $(nproc)
```
> -j argument used for speeding up the **make** command.
> nproc denotes the number of installed processing units.
