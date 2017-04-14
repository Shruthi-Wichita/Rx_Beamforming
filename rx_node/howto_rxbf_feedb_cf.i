//Date last modified: March 20, 2012
// ----------------------------------------------------------------

GR_SWIG_BLOCK_MAGIC(howto,rxbf_feedb_cf);

howto_rxbf_feedb_cf_sptr howto_make_rxbf_feedb_cf (double sampling_rate, double treshold, int decim_factor, int nbr_samples_packet, int nbr_samples_cycle, double delay_security_factor, double time_delay);

class howto_rxbf_feedb_cf : public gr_sync_decimator
{
private:
  howto_rxbf_feedb_cf (double sampling_rate, double treshold, int decim_factor, int nbr_samples_packet, int nbr_samples_cycle, double delay_security_factor, double time_delay);
};
