# Makefile for the ROOT test programs.
# This Makefile shows nicely how to compile and link applications
# using the ROOT libraries on all supported platforms.
#
# Copyright (c) 2000 Rene Brun and Fons Rademakers
#
# Author: Fons Rademakers, 29/2/2000

ARCH          = linux
CXX           =
ObjSuf        = o
SrcSuf        = cpp
ExeSuf        =
DllSuf        = so
OutPutOpt     = -o

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)

# Linux with egcs, gcc 2.9x, gcc 3.x (>= RedHat 5.2)
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared

CXXFLAGS     += $(ROOTCFLAGS)
LIBS          = $(ROOTLIBS) $(SYSLIBS)
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)

#------------------------------------------------------------------------------

RESULTSO        = Results.o
RESULTSS        = Results.cpp ResultsDict.cpp
RESULTSSO       = Results.o ResultsDict.o
RESULTSH        = Results.h ResultsDict.h

OBJS            = usrini.o usrout.o mgdraw.o source.o stuprf.o stupre.o usrrnc.o usrein.o
#OBJS            = usrini.o usrout.o mgdraw.o source.o stuprf.o  usrein.o

#------------------------------------------------------------------------------

all:            libResults.so FluLib.o LaMuon

libResults.so:  $(RESULTSSO) $(RESULTSH)
		$(LD) $(SOFLAGS) $(LDFLAGS) $(RESULTSSO) $(GLIBS) -o libResults.so
		@echo "$@ done"
#
ResultsDict.cpp:Results.h ResultsLinkDef.h
		@echo "Generating dictionary $@..."
		@$(ROOTSYS)/bin/rootcint -f ResultsDict.cpp -c -p Results.h ResultsLinkDef.h

FluLib.o:   Results.h
	    @echo "Generating Library $@..."
	    g++ -c FluLib.cpp $(ROOTCFLAGS)

.f.$(ObjSuf):
	       $(FLUPRO)/flutil/fff $?

LaMuon:     $(OBJS) FluLib.$(ObjSuf) libResults.so
	       $(FLUPRO)/flutil/ldpmqmd -o $@ -m fluka $?


clean:
		@rm -f LaMuon Results.o ResultsDict.o FluLib.o core *.so ResultsDict.cpp $(OBJS) *.FOR

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<
