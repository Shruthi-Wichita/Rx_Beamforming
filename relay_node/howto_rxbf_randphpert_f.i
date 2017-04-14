//Date last modified: March 24, 2012
// ----------------------------------------------------------------

GR_SWIG_BLOCK_MAGIC(howto,rxbf_randphpert_f);

howto_rxbf_randphpert_f_sptr howto_make_rxbf_randphpert_f (double random_perturbation_size, int bf_flag);

class howto_rxbf_randphpert_f : public gr_sync_block
{
private:
  howto_rxbf_randphpert_f (double random_perturbation_size, int bf_flag);
public:
  //accessors
  int bf_flag () const { return d_bf_flag; }
  gr_complex poll_complex_gain() const { return d_complex_gain; }

  //manipulators
  void set_bf_flag (int bf_flag);
};
