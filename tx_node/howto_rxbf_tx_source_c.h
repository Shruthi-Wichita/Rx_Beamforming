/* -*- c++ -*- */
/*
 * Copyright 2004 Free Software Foundation, Inc.
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
#ifndef INCLUDED_howto_rxbf_tx_source_c_H
#define INCLUDED_howto_rxbf_tx_source_c_H

#include <gr_block.h>
#include <iostream>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>

class howto_rxbf_tx_source_c;

/*
 * We use boost::shared_ptr's instead of raw pointers for all access
 * to gr_blocks (and many other data structures).  The shared_ptr gets
 * us transparent reference counting, which greatly simplifies storage
 * management issues.  This is especially helpful in our hybrid
 * C++ / Python system.
 *
 * See http://www.boost.org/libs/smart_ptr/smart_ptr.htm
 *
 * As a convention, the _sptr suffix indicates a boost::shared_ptr
 */
typedef boost::shared_ptr<howto_rxbf_tx_source_c> howto_rxbf_tx_source_c_sptr;

/*!
 * \brief Return a shared_ptr to a new instance of howto_rxbf_tx_source_c.
 *
 * To avoid accidental use of raw pointers, howto_rxbf_tx_source_c's
 * constructor is private.  howto_make_rxbf_tx_source_c is the public
 * interface for creating new instances.
 */
howto_rxbf_tx_source_c_sptr howto_make_rxbf_tx_source_c (double Fs, double Fp, int N);

/*!
 * \brief mpower a stream of floats.
 * \ingroup block
 *
 * \sa howto_mpower2_ff for a version that subclasses gr_sync_block.
 */
class howto_rxbf_tx_source_c : public gr_block
{
private:
  // The friend declaration allows howto_make_rxbf_tx_source_c to
  // access the private constructor.

  friend howto_rxbf_tx_source_c_sptr howto_make_rxbf_tx_source_c (double Fs, double Fp, int N);

  howto_rxbf_tx_source_c (double Fs, double Fp, int N);  	// private constructor
	double d_Fs;
	double d_Fp;
	int d_N;

	int cpt_samples;
	int periodLength;

	

 public:
	// accessors
	int get_N() const {return d_N; }
	
	// manipulator
	void set_N(int N);

	// public destructor
  	~howto_rxbf_tx_source_c ();

  // Where all the action really happens

  int general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
};

#endif /* INCLUDED_howto_rxbf_tx_source_c_H */
