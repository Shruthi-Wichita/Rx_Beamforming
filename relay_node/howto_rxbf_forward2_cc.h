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
#ifndef INCLUDED_HOWTO_RXBF_FORWARD2_CC_H
#define INCLUDED_HOWTO_RXBF_FORWARD2_CC_H

#include <gr_block.h>
#include <iostream>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>

class howto_rxbf_forward2_cc;

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
typedef boost::shared_ptr<howto_rxbf_forward2_cc> howto_rxbf_forward2_cc_sptr;

/*!
 * \brief Return a shared_ptr to a new instance of howto_rxbf_forward2_cc.
 *
 * To avoid accidental use of raw pointers, howto_rxbf_forward2_cc's
 * constructor is private.  howto_make_rxbf_forward2_cc is the public
 * interface for creating new instances.
 */
howto_rxbf_forward2_cc_sptr howto_make_rxbf_forward2_cc (double sample_rate, double rx_min_treshold, double rx_max_treshold, double time_delay, double time_cycle, int packet_length, int max_missed_symbols, int nbr_zeros_per_burst);

/*!
 * \brief mpower a stream of floats.
 * \ingroup block
 *
 * \sa howto_mpower2_ff for a version that subclasses gr_sync_block.
 */
class howto_rxbf_forward2_cc : public gr_block
{
private:
  // The friend declaration allows howto_make_rxbf_forward2_cc to
  // access the private constructor.

  friend howto_rxbf_forward2_cc_sptr howto_make_rxbf_forward2_cc (double sample_rate, double rx_min_treshold, double rx_max_treshold, double time_delay, double time_cycle, int packet_length, int max_missed_symbols, int nbr_zeros_per_burst);

  howto_rxbf_forward2_cc (double sample_rate, double rx_min_treshold, double rx_max_treshold, double time_delay, double time_cycle, int packet_length, int max_missed_symbols, int nbr_zeros_per_burst);  	// private constructor

	double d_sample_rate;
	double d_rx_min_treshold;
	double d_rx_max_treshold;
 	double d_time_delay; 
	double d_time_cycle; 
	int d_N; 
	int d_max_missed_symbols; 
	int d_nbr_zeros_per_burst;

	double Fs;
	int samples_cycle;
	int nbr_samples_wait_bef_list;
	int state;
	int cpt_samples;
	int cpt_zeros_burst;
	int cpt_missed_symbols;
	int cpt_samples_rx_packet;
	int cpt_samples_tx_packet;
	int cpt_samples_wait_bef_list;
	bool first_burst_of_zeros;
	float out_real;
	float out_imag;
	float power_packet;
	gsl_vector_float* rx_samples_arg;
	gsl_vector_float* rx_samples_real;
	gsl_vector_float* rx_samples_imag;

	double fracs;
	double fracs_rx;
	double fracs_tx;
	double fracs_tx_zeros;
	uint64_t secs;
	uint64_t secs_rx;
	uint64_t secs_tx;
	uint64_t secs_tx_zeros;
	uint64_t offs;
	uint64_t start_time_packet;
	

 public:
  ~howto_rxbf_forward2_cc ();	// public destructor

  void make_time_tag(const uint64_t tag_count);
  void make_time_tag_zeros(const uint64_t tag_count);
  void make_sob_tag(const uint64_t tag_count);
  void make_eob_tag(const uint64_t tag_count);

  // Where all the action really happens
  int general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
};

#endif /* INCLUDED_HOWTO_RXBF_FORWARD2_CC_H */
