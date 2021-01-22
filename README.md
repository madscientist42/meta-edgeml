# meta-edgeml
Yocto layer for varying "BSP" items for several different Deep/Machine Learning devices and frameworks

This is a bit of a roll-up of my various efforts into Machine Learning at the "Edge"- specifically
for Mobile/IoT and similarly embedded devices.  It had gotten where all my various pet-projects
were scattered amongst meta-pha and various in-progress and not committed yet stuff- so it needed
a proper layer and home for all of it so people could take advantage of my work to this point.

Currently it hosts Yocto recipes proper for building TensorFlow-Lite for Python3 and C++ as well as
the hooks to let you use one of the USB or PCIe based EdgeTPUs in your Yocto projects.  Future plans
include having General Vision's Neuromorphic chips support and various other FOSS NPU drivers and
libraries so everyone can have a clean one-stop shop for their ML solutions in Yocto.
