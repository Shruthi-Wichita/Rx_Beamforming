/* -*- c++ -*- */

#define HOWTO_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "howto_swig_doc.i"

%{
#include "howto/randphpert.h"
%}


%include "howto/randphpert.h"
GR_SWIG_BLOCK_MAGIC2(howto, randphpert);
