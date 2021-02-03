# Armstrap pyVirtualBench
Python wrappers to control NI VirtualBench.  These wrappers call into the official c-driver, allowing you to control VirtualBench from a Python application.

![VirtualBench](https://github.com/armstrap/armstrap-pyvirtualbench/raw/master/images/ni-virtualbench.jpg)
![Python](https://github.com/armstrap/armstrap-pyvirtualbench/raw/master/images/python-logo-and-wordmark.png)

# What is VirtualBench?
Five Instruments. One Device. Radically Practical.

By combining the most essential instruments into one device and integrating with PCs and iPads, the VirtualBench all-in-one instrument is simple, is convenient, and opens up new possibilities for how you can interact with benchtop instruments.

What’s Included?
 1. Mixed-Signal Oscilloscope With Protocol Analysis
 2. Function Generator
 3. Digital I/O, SPI master, I2C master
 4. Programmable DC Power Supply
 5. Digital Multimeter

More information can be found on [ni.com](http://www.ni.com/virtualbench/).

## Requirements (Windows Only)
* [NI VirtualBench hardware](http://www.ni.com/virtualbench/)
* [VirtualBench driver >= 1.1.0](https://www.ni.com/en-us/support/downloads/drivers/download.virtualbench-software.html#324215)
  Be sure to check "ANSI C Support" during installation.
    ![NiInstaller](https://github.com/armstrap/armstrap-pyvirtualbench/raw/master/images/ni-virtualbench-installer.png)
* [Python >= 3.4](https://www.python.org/downloads/).  You will need 32-bit Python support to work with the NI-provided drivers.
* `./examples/hands_free_dmm.py` Requirements
    + [Infinity USB Digital Foot Control with Computer plug (IN-USB2)](http://www.amazon.com/Infinity-Digital-Control-Computer--USB2/dp/B002MY6I7G)
    + pip install pywinusb
    + pip install Pyglet
    + copy `./support/avbin-win32-5.zip/avbin.dll` into your `c:\Windows\System32` directory

## Quickstart Guide
* Run the following on a Windows Command Line terminal
```
mkdir Projects
cd Projects
git clone https://github.com/armstrap/armstrap-pyvirtualbench.git
cd armstrap-pyvirtualbench
python -m pip install .
python examples\ps_example.py
```

## For Developers
* To install in "edit mode" - that is, to use the files directly in the project directory instead of making a read-only installation -
  in the above instructions replace
````
python -m pip install .
````
with
````
python -m pip install -e .
````

## Helpful Resources
* [NI support article on pyVirtualBench](https://knowledge.ni.com/KnowledgeArticleDetails?id=kA00Z000000kHUFSA2)
* VirtualBench C library is found in `C:\Program Files (x86)\National Instruments\Shared\ExternalCompilerSupport\C`
* Examples for the C-API of VirtualBench are found in `C:\Users\Public\Documents\National Instruments\VirtualBench ANSI C Examples`
