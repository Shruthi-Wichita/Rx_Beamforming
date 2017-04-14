/* -*- c++ -*- */
/*
 * Copyright 2004,2010 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

/*
 * config.h is generated by configure.  It contains the results
 * of probing for features, options etc.  It should be the first
 * file included in your .cc file.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <howto_rxbf_tx_source_c.h>
#include <gr_io_signature.h>
#include <math.h>
#include <stdio.h>
#include <gr_fxpt.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>



/*
 * Create a new instance of howto_pn_diff_correlator_cc and return
 * a boost shared_ptr.  This is effectively the public constructor.
 */
howto_rxbf_tx_source_c_sptr 
howto_make_rxbf_tx_source_c (double Fs, double Fp, int N)
{
  return gnuradio::get_initial_sptr(new howto_rxbf_tx_source_c (Fs, Fp, N));
}


/*
 * The private constructor
 */
howto_rxbf_tx_source_c::howto_rxbf_tx_source_c (double Fs, double Fp, int N)
  : gr_block ("rxbf_tx_source_c",
	      gr_make_io_signature (0, 0, 0),
	      gr_make_io_signature (1, 1, sizeof (gr_complex))),
	      d_Fs(Fs),
	      d_Fp(Fp),
	      d_N(N)
{	
	/* initialize instance variables */
	cpt_samples = 0;
	periodLength = int(std::ceil(Fs/Fp));
	printf("Fs = %f\n", d_Fs);
	printf("Fp = %f\n", d_Fp);
	printf("N = %d\n", d_N);
	printf("periodLength = %d\n", periodLength);
}

/*
 * Our virtual destructor.
 */
howto_rxbf_tx_source_c::~howto_rxbf_tx_source_c ()
{
}


int 
howto_rxbf_tx_source_c::general_work (int noutput_items,
			       gr_vector_int &ninput_items,
			       gr_vector_const_void_star &input_items,
			       gr_vector_void_star &output_items)
{
  	gr_complex *out = (gr_complex *)output_items[0];

  	for (int i = 0; i < noutput_items; i++) {  
    	if (cpt_samples < d_N) {
			// message
			out[i] = gr_complex(1,0);
		}
		else {
			// TX nothing (silent period)
			out[i] = gr_complex(0,0);
		}
		cpt_samples = int(fmod(++cpt_samples, periodLength));	
	}

  // Tell runtime system how many input items we consumed on
  // each input stream.

  consume_each (noutput_items);

  // Tell runtime system how many output items we produced.
  return noutput_items;
}

void howto_rxbf_tx_source_c::set_N(int N)
{
	d_N = N;
}