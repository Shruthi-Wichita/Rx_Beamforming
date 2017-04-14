/*
 * First arg is the package prefix.
 * Second arg is the name of the class minus the prefix.
 *
 * This does some behind-the-scenes magic so we can
 * access howto_rxbf_tx_source_c from python as howto.rxbf_tx_source_c
 */
GR_SWIG_BLOCK_MAGIC(howto,rxbf_tx_source_c);

howto_rxbf_tx_source_c_sptr howto_make_rxbf_tx_source_c (double Fs, double Fp, int N);

class howto_rxbf_tx_source_c : public gr_block
{
private:
  howto_rxbf_tx_source_c (double Fs, double Fp, int N);
};
