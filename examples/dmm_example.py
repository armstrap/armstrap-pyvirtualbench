#! /usr/bin/env python3

# The MIT License (MIT)
#
# Copyright (c) 2016 Charles Armstrap <charles@armstrap.org>
# If you like this library, consider donating to: http://bit.ly/pyvirtualbench
# Anything helps.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

from pyvirtualbench import PyVirtualBench, PyVirtualBenchException, DmmFunction

# This examples demonstrates how to make measurements using the Digital
# Multimeter (DMM) on a VirtualBench.

try:
    # You will probably need to replace "myVirtualBench" with the name of your device.
    # By default, the device name is the model number and serial number separated by a hyphen; e.g., "VB8012-309738A".
    # You can see the device's name in the VirtualBench Application under File->About
    virtualbench = PyVirtualBench('myVirtualBench')
    dmm = virtualbench.acquire_digital_multimeter();
    dmm.configure_measurement(DmmFunction.DC_VOLTS, True, 10.0)

    for i in range(10):
        print("Measurement %d: %f V" % (i, dmm.read()))

    dmm.release()
except PyVirtualBenchException as e:
    print("Error/Warning %d occurred\n%s" % (e.status, e))
finally:
    virtualbench.release()
