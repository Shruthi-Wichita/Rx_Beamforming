/*
 * First arg is the package prefix.
 * Second arg is the name of the class minus the prefix.
 *
 * This does some behind-the-scenes magic so we can
 * access howto_rxbf_forward2_cc from python as howto.rxbf_forward2_cc
 */
GR_SWIG_BLOCK_MAGIC(howto,rxbf_forward2_cc);

howto_rxbf_forward2_cc_sptr howto_make_rxbf_forward2_cc (double sample_rate, double rx_min_treshold, double rx_max_treshold, double time_delay, double time_cycle, int packet_length, int max_missed_symbols, int nbr_zeros_per_burst);

class howto_rxbf_forward2_cc : public gr_block
{
private:
  howto_rxbf_forward2_cc (double sample_rate, double rx_min_treshold, double rx_max_treshold, double time_delay, double time_cycle, int packet_length, int max_missed_symbols, int nbr_zeros_per_burst);
};
