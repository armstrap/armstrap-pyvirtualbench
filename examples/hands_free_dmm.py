#! /usr/bin/env python3

# The MIT License (MIT)
#
# Copyright (c) 2016 Charles Armstrap <charles@armstrap.org>
# If you like this library, consider donating to: https://bit.ly/armstrap-opensource-dev
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


# This application shows the power of NI VirtualBench.  Because it's five instruments in one
# package, we can create an array of "virtual" instruments and use something like a USB foot
# pedal to cycle through each "virtual" instrument, something that is traditionally not possible
# if your instruments were in separate boxes.
#
#  We use the Google text-to-speech API to output measurements to the computer's audio speakers.
#
# This example requires a USB foot pedal to function.  The one used here (note, any
# USB foot pedal can be used with some slight modifications to this code) is below.
#
# Infinity USB Digital Foot Control with Computer plug (IN-USB2)
# This hardware device can be found on amazon.com for approximately $50 USD
# Link: http://www.amazon.com/Infinity-Digital-Control-Computer--USB2/dp/B002MY6I7G

from pyvirtualbench import PyVirtualBench, PyVirtualBenchException, DmmFunction, Status
from time import sleep
from msvcrt import kbhit
import winsound
import pywinusb.hid as hid # pip install pywinusb
import urllib.request
import pyglet # pip install Pyglet
import os.path
from threading import Thread
import math

# This is the example featured on hackaday.com on July 29th, 2015
# https://hackaday.com/2015/07/29/talking-foot-pedal-controlled-bench-probes-for-virtualbench/
# It featured combining multiple instruments onto a single set of probes and using a USB footpedal
# to cycle through the instruments.
# A video demonstation is available here: https://www.youtube.com/watch?v=1NOQRLI39es

# You will probably need to replace "myVirtualBench" with the name of your device.
# By default, the device name is the model number and serial number separated by a hyphen; e.g., "VB8012-309738A".
# You can see the device's name in the VirtualBench Application under File->About
virtualbench = PyVirtualBench('myVirtualBench')
selected_instrument_index = 0 # a global index to reference the currently selected instrument in the global 'instruments' array

def text_to_speech_async(mystr):
    ''' Converts the user input string 'mystr' into audio that is output to the computer speakers.
        Note, this function is asynchronous we return while the audio is still playing.
    '''
    file_cache_dir = os.path.expanduser("~/Desktop/text_to_speech_cache/") # User-defined directory (change this to your liking)
    if (os.path.isdir(file_cache_dir) == False):
        os.makedirs(file_cache_dir)
    file_path = file_cache_dir + mystr + ".mpeg"
    # We only should hit the network if the audio is not in the cache
    if (os.path.isfile(file_path) == False):
        url = "http://translate.google.com/translate_tts?tl=en&q=" + mystr.replace(" ", "%20")
        req = urllib.request.Request(url, data=None, headers={'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0'})
        response_contents = urllib.request.urlopen(req)
        fh = open(file_path, "wb")
        fh.write(response_contents.read())
        fh.close()
    player = pyglet.media.Player()
    source = pyglet.media.load(file_path)
    player.queue(source)
    player.play()

def background_worker(self):
    try:
        self.run_instrument()
    except AttributeError as e:
        pass
    except OSError as e:
        pass
    except Exception as e:
        pass

class VirtualBenchDmmDcVoltageInstrument:
    def __init__(self):
        global virtualbench;
        self.instrument_name = "dmm dc voltage"
        self.dmm = None
    def acquire(self):
        text_to_speech_async(self.instrument_name)
        self.dmm = virtualbench.acquire_digital_multimeter();
        self.dmm.configure_measurement(DmmFunction.DC_VOLTS, True, 10.0)
    def release(self):
        self.dmm.release()
        self.dmm = None
    def run_instrument(self):
        previous_value = -1; # Invalid to force read output
        status = Status.SUCCESS
        while (True):
            try:
                sleep(1)
                current_value = math.fabs(self.dmm.read())
                if (math.fabs(previous_value - current_value) > 1):
                    text_to_speech_async("%.2f volts" % current_value)
                previous_value = current_value
                status = Status.SUCCESS
            except PyVirtualBenchException as e:
                if (status != e.status and e.status == Status.WARNING_DMM_OVERRANGE):
                    previous_value = -1; # Invalid to force read output
                status = e.status
                if (e.status != Status.WARNING_DMM_OVERRANGE):
                    raise PyVirtualBenchException(e)

class VirtualBenchDmmResistanceInstrument:
    def __init__(self):
        global virtualbench;
        self.instrument_name = "dmm resistance"
        self.dmm = None
    def acquire(self):
        text_to_speech_async(self.instrument_name)
        self.dmm = virtualbench.acquire_digital_multimeter();
        self.dmm.configure_measurement(DmmFunction.RESISTANCE)
    def release(self):
        self.dmm.release()
        self.dmm = None
    def run_instrument(self):
        previous_value = -1; # Invalid to force read output
        status = Status.SUCCESS
        while (True):
            try:
                sleep(2)
                current_value = math.fabs(self.dmm.read())
                if (math.fabs(previous_value - current_value) > 1):
                    text_to_speech_async(self.olm_to_str(current_value))
                previous_value = current_value
                status = Status.SUCCESS
            except PyVirtualBenchException as e:
                # Do check so we don't repeat the same error over and over
                if (status != e.status and e.status == Status.WARNING_DMM_OVERRANGE):
                    text_to_speech_async("probes not connected")
                    previous_value = -1; # Invalid to force read output
                status = e.status
                if (e.status != Status.WARNING_DMM_OVERRANGE):
                    raise PyVirtualBenchException(e)
    def olm_to_str(self, value):
        if ((value / 1000000) > 1):
            return "%.2f mega olms" % (value / 1000000);
        if ((value / 1000) > 1):
            return "%.2f kilo olms" % (value / 1000);
        return "%.2f olms" % value

class VirtualBenchContinuityInstrument:
    def __init__(self):
        global virtualbench;
        self.instrument_name = "continuity"
        self.dmm = None
        self.is_beeping = False
    def acquire(self):
        text_to_speech_async(self.instrument_name)
        self.dmm = virtualbench.acquire_digital_multimeter()
        self.dmm.configure_measurement(DmmFunction.RESISTANCE)
    def release(self):
        self.dmm.release()
        self.dmm = None
        self.is_beeping = False
    def run_instrument(self):
        while (True):
            try:
                if (math.fabs(self.dmm.read()) < 100 and self.is_beeping == False): # 100 Ohlms
                    winsound.PlaySound('continuity_beep.wav', winsound.SND_FILENAME | winsound.SND_ASYNC | winsound.SND_LOOP)
                    self.is_beeping = True;
            except PyVirtualBenchException as e:
                winsound.PlaySound(None, 0) # Stops audio from playing
                self.is_beeping = False;
                if (e.status != Status.WARNING_DMM_OVERRANGE):
                    raise PyVirtualBenchException(e)

# global 'instruments' contains the instruments we care about for this application.
# Note: users should change this to instruments that make sense for their application.
instruments = [VirtualBenchDmmDcVoltageInstrument(), VirtualBenchDmmResistanceInstrument(), VirtualBenchContinuityInstrument()]

def footpedal_handler(data):
    global instruments
    global selected_instrument_index

    left_pedal_pressed = data[1] & 1
    middle_pedal_pressed = data[1] & 2
    right_pedal_pressed = data[1] & 4

    if (left_pedal_pressed):
        # Release the currently selected instrument.
        # This will cause the run_instrument background thread for that instrument
        # to exit because the instrument handle will be invalid.
        current_instrument = instruments[selected_instrument_index]
        current_instrument.release();

        # Cycle to the next instrument
        selected_instrument_index = (selected_instrument_index + 1) % len(instruments)

        # Once we have our new instrument, acquire a handle and start using it.
        current_instrument = instruments[selected_instrument_index]
        current_instrument.acquire()
        thread = Thread(target=background_worker, args=(current_instrument,))
        thread.start()
    if (middle_pedal_pressed or right_pedal_pressed) :
        text_to_speech_async("pedal functionality not defined")

# For this application, we use a Infinity USB Digital Foot Control with Computer plug (IN-USB2)
# This hardware device can be found on amazon.com for approximately $50 USD
# Link: http://www.amazon.com/Infinity-Digital-Control-Computer--USB2/dp/B002MY6I7G
def find_vec_usb_footpedal():
    all_hids = hid.find_all_hid_devices()
    for index, device in enumerate(all_hids):
        if (device.vendor_id == 0x05f3 and device.product_id == 0x00ff):
            print("Found VEC USB Footpedal")
            return all_hids[index]
    raise Exception("VEC USB Footpedal not found");

if __name__ == '__main__':
    try:
        footpedal = find_vec_usb_footpedal()

        # When starting the application, we default the instrument to the first
        # instrument in the global 'instruments' list
        current_instrument = instruments[selected_instrument_index]
        current_instrument.acquire()
        thread = Thread(target=background_worker, args=(current_instrument,))
        thread.start()

        footpedal.open()
        footpedal.set_raw_data_handler(footpedal_handler)

        print("\nWaiting for data...\nPress any (system keyboard) key to stop...")
        while not kbhit() and footpedal.is_plugged():
            #just keep the device opened to receive events
            sleep(0.5)

    finally:
        footpedal.close()
        virtualbench.release()
