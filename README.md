# Armstrap pyVirtualBench
Python wrappers to control NI VirtualBench.  These wrappers call into the official C driver, allowing you to control VirtualBench from a Python application.

![VirtualBench](https://github.com/armstrap/armstrap-pyvirtualbench/raw/master/images/ni-virtualbench.jpg)
![Python](https://github.com/armstrap/armstrap-pyvirtualbench/raw/master/images/python-logo-and-wordmark.png)

# What is VirtualBench?
Five Instruments. One Device. Radically Practical.

By combining the most essential instruments into one device and integrating with PCs and iPads, the VirtualBench all-in-one instrument is simple, is convenient, and opens up new possibilities for how you can interact with benchtop instruments.

What’s Included?
 1. Mixed-Signal Oscilloscope With Protocol Analysis
 2. Function Generator
 3. Digital I/O
 4. Programmable DC Power Supply
 5. Digital Multimeter

More information can be found on [ni.com](http://www.ni.com/virtualbench/).
 
## Requirements (Windows Only)
* [NI VirtualBench hardware](http://www.ni.com/virtualbench/)
* [NI VirtualBench driver >= 1.1.0](http://search.ni.com/nisearch/app/main/p/bot/no/ap/tech/lang/en/pg/1/sn/catnav:du/q/NI-VirtualBench/)
* [Python >= 3.4](https://www.python.org/downloads/)
* Requirements for `./examples/hands_free_dmm.py`:
    + [Infinity USB Digital Foot Control with Computer plug (IN-USB2)](http://www.amazon.com/Infinity-Digital-Control-Computer--USB2/dp/B002MY6I7G)
    + pip install pywinusb
    + pip install Pyglet
    + copy `./support/avbin-win32-5.zip/avbin.dll` into your `c:\Windows\System32` directory
