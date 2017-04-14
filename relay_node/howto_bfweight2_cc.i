//------------------------------------

GR_SWIG_BLOCK_MAGIC(howto,bfweight2_cc);

howto_bfweight2_cc_sptr howto_make_bfweight2_cc (gr_complex bf_weight);

class howto_bfweight2_cc : public gr_sync_block
{
private:
  howto_bfweight2_cc (gr_complex bf_weight);
public:
//accessors
  gr_complex bf_weight () const {return d_bf_weight; }
 
  //manipulators
  void set_bf_weight (gr_complex bf_weight);
};
