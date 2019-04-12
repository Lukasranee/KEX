# KEX
Motion correction for PET imaging

This respiratory contains code developed to read 32-bit list-mode data from a PET acquisition.

32ba_verbose.c
The 32ba_verbose file is dedicated to Siemens PETLINK script, designed to read the binary 32-bit files, but is under modification in order to be able to print information regarding time of flight(TOF) and LOR for every event.


Positionbin.m
The matlab file positionbin.m contains a simple matlab script that uses information about the total number of events within all specific TOF indexes, i.e. all events get marked with a TOFindex between 1-13 that corresponds to the bin where the event accually occurred. With this information the script can calculate a mean value using simple anger logic and determine if a object has been relocated between two PET acquisitions.

