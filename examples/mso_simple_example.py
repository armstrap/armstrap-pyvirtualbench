#! /usr/bin/env python3

# The MIT License (MIT)
#
# Copyright (c) 2015 Charles Armstrap <charles@armstrap.org>
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

from pyvirtualbench import PyVirtualBench, PyVirtualBenchException, MsoSamplingMode
from datetime import datetime

# This examples demonstrates how to configure and acquire data from the
# Mixed Signal Oscilloscope (MSO) instrument on a VirtualBench using
# the built in auto setup functionality.

def print_analog_data(analog_data, analog_data_stride, number_of_channels, sample_mode, number_to_print):
    analog_data_size = len(analog_data)
    if (analog_data_size == 0):
        return # Nothing to print if there is no data

    number_of_analog_samples_acquired = analog_data_size / analog_data_stride
    if (number_of_analog_samples_acquired < number_to_print):
        number_to_print = number_of_analog_samples_acquired

    print("Analog Data (%d of %d):" % (number_to_print, number_of_analog_samples_acquired))

    # Print channel header information.
    print("Channel:\t", end='')
    for chan in range(number_of_channels):
        if (chan != 0):
            print("\t\t", end='')
        print("%d" % chan, end='')
        if (sample_mode == MsoSamplingMode.PEAK_DETECT):
            print(" (min)\t\t%d (max)" % chan, end='')
    print("")

    # Print the data itself.
    for sample_index in range(number_to_print):
        print("Sample %d:\t" % samp, end='')
        for channel_index in range(analog_data_stride):
            if (channel_index != 0):
                print("\t", end='')
            print("%4.6f" % analog_data[sample_index * analog_data_stride + channel_index], end='')
        print("")

def print_digital_data(digital_data, timestamps, number_to_print):
    digital_data_size = len(digital_data)
    if (digital_data_size == 0):
        return # Nothing to print if there is no data

    if (digital_data_size < number_to_print):
        number_to_print =  digital_data_size

    print("Digital Data (%d of %d)\t\tTimestamp\tData:", number_to_print, digital_data_size)
    for sample_index in range (number_to_print):
        print("Sample %d", sample_index, timestamps[sample_index], digital_data[sample_index]);

def get_timestamp_difference(a_timestamp, b_timestamp):
    try:
        a_seconds_since_1970, a_fractional_seconds = virtualbench.convert_timestamp_to_values(a_timestamp)
        b_seconds_since_1970, b_fractional_seconds = virtualbench.convert_timestamp_to_values(b_timestamp)
        return (a_seconds_since_1970 - b_seconds_since_1970) + a_fractional_seconds - b_fractional_seconds;
    except PyVirtualBenchException as e:
        return 0.0;

try:
    virtualbench = PyVirtualBench('myVirtualBench')
    mso = virtualbench.acquire_mixed_signal_oscilloscope()

    # Configure the acquisition using auto setup
    mso.auto_setup()

    # Query the configuration that was chosen to properly interpret the data.
    sample_rate, acquisition_time, pretrigger_time, sampling_mode = mso.query_timing()
    channels = mso.query_enabled_analog_channels()
    channels_enabled, number_of_channels = virtualbench.collapse_channel_string(channels)

    # Start the acquisition.  Auto triggering is enabled to catch a misconfigured trigger condition.
    mso.run()

    # Read the data by first querying how big the data needs to be, allocating the memory, and finally performing the read.
    analog_data, analog_data_stride, analog_t0, digital_data, digital_timestamps, digital_t0, trigger_timestamp, trigger_reason = mso.read_analog_digital_u64()

    # Finally, print some information about the data.
    print("Trigger Reason: %s" % trigger_reason)
    trigger_timestamp_seconds_since_1970, trigger_timestamp_fractional_seconds = virtualbench.convert_timestamp_to_values(trigger_timestamp)
    print("Trigger Timestamp: %s UTC\n\t%f fractional seconds" % (datetime.utcfromtimestamp(trigger_timestamp_seconds_since_1970), trigger_timestamp_fractional_seconds));

    if (len(analog_data) != 0):
        print("Analog t0 is %f seconds before trigger" % get_timestamp_difference(trigger_timestamp, analog_t0))

    if (len(digital_data) != 0):
        print("Digital t0 is %f seconds before trigger" % get_timestamp_difference(trigger_timestamp, digital_t0))

    print_analog_data(analog_data, analog_data_stride, number_of_channels, sampling_mode, 10)
    print_digital_data(digital_data, digital_timestamps, 10)

    mso.release()
except PyVirtualBenchException as e:
    print("Error/Warning %d occurred\n%s" % (e.status, e))
finally:
    virtualbench.release()
