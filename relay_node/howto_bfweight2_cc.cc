// Date last modified: March 20, 2012

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <howto_bfweight2_cc.h>
#include <gr_io_signature.h>

howto_bfweight2_cc_sptr 
howto_make_bfweight2_cc (gr_complex bf_weight)
{
  return howto_bfweight2_cc_sptr (new howto_bfweight2_cc (bf_weight));
}

/*
 * The private constructor
 */
howto_bfweight2_cc::howto_bfweight2_cc (gr_complex bf_weight)
  : gr_sync_block ("bfweight2_cc",
	      gr_make_io_signature (1, 1, sizeof (gr_complex)),
	      gr_make_io_signature (1, 1, sizeof (gr_complex))),
              d_bf_weight(bf_weight)
{
  
}

/*
 * Our virtual destructor.
 */
howto_bfweight2_cc::~howto_bfweight2_cc ()
{
  // nothing else required in this example
}

int 
howto_bfweight2_cc::work (int noutput_items,
			       gr_vector_const_void_star &input_items,
			       gr_vector_void_star &output_items)
{
  const gr_complex *in = (const gr_complex *) input_items[0];
  gr_complex *out = (gr_complex *) output_items[0];

  for (int i = 0; i < noutput_items; i++){
    out[i] = d_bf_weight*in[i];
  }

  // Tell runtime system how many output items we produced.
  return noutput_items;
}
void
howto_bfweight2_cc::set_bf_weight (gr_complex bf_weight)
{
  d_bf_weight = bf_weight;
}
