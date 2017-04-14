/* -*- c++ -*- */

#define HOWTO_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "howto_swig_doc.i"

%{
#include "howto/rx_bf_gen_fb.h"
%}


%include "howto/rx_bf_gen_fb.h"
GR_SWIG_BLOCK_MAGIC2(howto, rx_bf_gen_fb);
