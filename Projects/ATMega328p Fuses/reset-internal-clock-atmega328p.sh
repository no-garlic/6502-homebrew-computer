#!/bin/sh

avrdude -C /opt/homebrew/Cellar/avrdude/7.0_2/.bottle/etc/avrdude.conf -v -p atmega328p -c usbtiny -U lfuse:w:0xFF:m

