AUTOMAKE_OPTIONS = foreign

# what flags you want to pass to the C compiler & linker
CFLAGS = --pedantic -Wall -std=c99 -O2
LDFLAGS =

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
bin_PROGRAMS = CuteDSCapture
CuteDSCapture_SOURCES = main.cpp dscapture.h dscapture.c

EXTRA_DIST = README.md 95-dscapture.rules
