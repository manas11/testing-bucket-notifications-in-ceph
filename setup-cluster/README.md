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
cd ceph
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
 cd build
 make vstart -j $(nproc)
```
> **-j** argument used for speeding up the **make** command.
> **nproc** denotes the number of installed processing units.

## Start the ceph cluster 
Use these commands to start the development ceph cluster.
> Command assuming that inside the **build** directory.

```
OSD=3 MON=1 MDS=0 MGR=1 RGW=1 ../src/vstart.sh -n -d --short
```
**Understanding the above command.**

*Arguments:*

* **-n** : to create a new cluster (**-N** used dor using the old cluster, not create a new one)
* **-d** : to launch in debug mode
* **--short** : for short object names only

*Environment variables:*
* **OSD** -  number of object storage daemon (3)
* **MON** - number of monitors (1)
* **MDS** - metadata server number (0)
* **MGR** - ceph manager (1)
* **RGW** - RADOS gateway number = 1 gateway

## After starting the development cluster,
The following daemon was started :
 **ceph-mgr(1 instance)**, **ceph-mon(1 instance)**, **ceph-osd(3 instances)**

**The cluster started in following steps:**
1. first, mgr dashboard module was started - ceph-mgr
2. for this dashboard credentials were generated as username : admin and password a hash
3. Then, the REST server was started 
4. OSD named 0, 1, 2 were started, using the configuration file in build/ceph.conf
5. Then S3 and Swift users were created
6. The RADOS gateway was started on localhost:8000
7. 2 URL were generated, one for dashboard and other for restful server

