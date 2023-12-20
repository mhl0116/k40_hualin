## Work with Geant4 visulization using server at trident lab

0. Go to bl0 first, then you could access two servers at trident lab
1. Make sure you could access graphic view of the system (linux/mac could use vncviewer, windows there are alternatitives I am sure)
2. Get this repo
    ```
    mkdir  build
    cd build
    cmake ..
    make 
    cd ..
    ./build main configs/config.yaml configs/optical_properties.yaml
    ```
