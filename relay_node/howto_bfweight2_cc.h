
#ifndef INCLUDED_HOWTO_BFWEIGHT2_CC_H
#define INCLUDED_HOWTO_BFWEIGHT2_CC_H

#include <gr_sync_block.h>

class howto_bfweight2_cc;

typedef boost::shared_ptr<howto_bfweight2_cc> howto_bfweight2_cc_sptr;

howto_bfweight2_cc_sptr howto_make_bfweight2_cc (gr_complex bf_weight);

class howto_bfweight2_cc : public gr_sync_block
{
private:

  friend howto_bfweight2_cc_sptr howto_make_bfweight2_cc (gr_complex bf_weight);

  howto_bfweight2_cc (gr_complex bf_weight);  	// private constructor
  
  gr_complex d_bf_weight;

 public:

  //accessors
  gr_complex bf_weight () const {return d_bf_weight; }
 
  //manipulators
  void set_bf_weight (gr_complex bf_weight);

  ~howto_bfweight2_cc ();	// public destructor

  // Where all the action really happens

  int work (int noutput_items,
	    gr_vector_const_void_star &input_items,
	    gr_vector_void_star &output_items);
};

#endif /* INCLUDED_HOWTO_BFWEIGHT2_CC_H */
