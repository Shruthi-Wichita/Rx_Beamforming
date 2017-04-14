//Date last modified: March 24, 2012

#ifndef INCLUDED_HOWTO_RXBF_RANDPHPERT_F_H
#define INCLUDED_HOWTO_RXBF_RANDPHPERT_F_H

#include <gr_sync_block.h>
#include <gr_noise_type.h>
#include <gr_random.h>

class howto_rxbf_randphpert_f;

typedef boost::shared_ptr<howto_rxbf_randphpert_f> howto_rxbf_randphpert_f_sptr;

howto_rxbf_randphpert_f_sptr howto_make_rxbf_randphpert_f (double random_perturbation_size, int bf_flag);

class howto_rxbf_randphpert_f : public gr_sync_block
{
private:
  friend howto_rxbf_randphpert_f_sptr howto_make_rxbf_randphpert_f(double random_perturbation_size, int bf_flag);

  howto_rxbf_randphpert_f (double random_perturbation_size, int bf_flag);

  double d_random_perturbation_size; 
  int d_bf_flag; // a flag to turn beamforming on or off

  double cum_ang;
  gr_complex etojphi;
  double rand_pert_from_prev_iter;
  gr_random d_seed;
  gr_complex d_complex_gain;
  float last_in_i;

public:
  //accessors
  int bf_flag () const { return d_bf_flag; }
 
  //manipulators
  void set_bf_flag (int bf_flag);

  ~howto_rxbf_randphpert_f ();
  
  int work (int noutput_items,
	    gr_vector_const_void_star &input_items,
	    gr_vector_void_star &output_items);

  gr_complex poll_complex_gain() const { return d_complex_gain; }

};

#endif /* INCLUDED_HOWTO_RXBF_RANDPHPERT_F_H */
