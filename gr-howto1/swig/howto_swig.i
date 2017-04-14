/* -*- c++ -*- */

#define HOWTO_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "howto_swig_doc.i"

%{
#include "howto/rxbf_tx_source.h"
%}


%include "howto/rxbf_tx_source.h"
GR_SWIG_BLOCK_MAGIC2(howto, rxbf_tx_source);
