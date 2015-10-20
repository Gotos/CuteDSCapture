# What is Cute DS Capture?

Cute DS Capture (CDC) is a DS capturing software for linux and Mac OS X for use with the capture boards by [3dscapture.com](http://3dscapture.com). It is written in C++ and uses [SFML](http://www.sfml-dev.org/).

# How to compile

Install SFML and the SFML-headers (libsfml-dev or similar) as well as libusb-1.0.0 and the headers (libusb-1.0.0-dev). Then, simple do ```./autogen.sh && ./configure && make```.

# How to use

Start CuteDSCapture. You can autoresize the window with 1-0 (1x, 1.5x, 2x,... original size). Press the spacebar to toggel window split.

If CuteDSCapture doesn't detect your DS and you are using linux, ```copy 95-dscapture.rules``` to /etc/udev/rules.d and reload udev-rules with ```udevadm control --reload-rules```.

# Why "Cute" DS Capture?

It was a play on words when I first tried to design a capture software for 3DS with Qt (which is prononced "cute"). Although I didn't stay with Qt, I liked the name Cute 3DS Capture and called the "port" for DS Cute DS Capture. Also, now I can call CDC and C3C (which is a very similar software but designed to work with a 3DS) "Cute Capture", if I refere to both of them.
