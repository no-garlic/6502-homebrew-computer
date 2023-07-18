#!/bin/sh

avrdude -C /opt/homebrew/Cellar/avrdude/7.0_2/.bottle/etc/avrdude.conf -p atmega328p -c usbtiny -U lfuse:r:lfuse.txt:i
avrdude -C /opt/homebrew/Cellar/avrdude/7.0_2/.bottle/etc/avrdude.conf -p atmega328p -c usbtiny -U hfuse:r:hfuse.txt:i

cat lfuse.txt
cat hfuse.txt

rm lfuse.txt
rm hfuse.txt


