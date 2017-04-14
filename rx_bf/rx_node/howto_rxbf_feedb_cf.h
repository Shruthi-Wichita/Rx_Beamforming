//Date last modified: March 24, 2012

#ifndef INCLUDED_HOWTO_RXBF_FEEDB_CF_H
#define INCLUDED_HOWTO_RXBF_FEEDB_CF_H

#include <gr_sync_decimator.h>
#include <gr_noise_type.h>
#include <gr_random.h>

class howto_rxbf_feedb_cf;

typedef boost::shared_ptr<howto_rxbf_feedb_cf> howto_rxbf_feedb_cf_sptr;

howto_rxbf_feedb_cf_sptr howto_make_rxbf_feedb_cf (double sampling_rate, double treshold, int decim_factor, int nbr_samples_packet, int nbr_samples_cycle, double delay_security_factor, double time_delay);

class howto_rxbf_feedb_cf : public gr_sync_decimator
{
private:
  friend howto_rxbf_feedb_cf_sptr howto_make_rxbf_feedb_cf(double sampling_rate, double treshold, int decim_factor, int nbr_samples_packet, int nbr_samples_cycle, double delay_security_factor, double time_delay);

  howto_rxbf_feedb_cf (double sampling_rate, double treshold, int decim_factor, int nbr_samples_packet, int nbr_samples_cycle, double delay_security_factor, double time_delay);

  	double d_sampling_rate; 
  	int d_decim_factor;
	double d_treshold;
	int d_nbr_samples_packet;
	int d_nbr_samples_cycle;
	double d_delay_security_factor;
	double d_time_delay;

	int cpt_samples;
	int cpt_samples_packet;
	int packet_number;
	float feedback_symbol;
	double avg_rss;
	double current_rss;
	double last_rss;
	double rss_max;
	double past_rss [4];
	int delay_since_last_rss_meas;
	int last_cpt_samples;

public:

  ~howto_rxbf_feedb_cf ();
  
  int work (int noutput_items,
	    gr_vector_const_void_star &input_items,
	    gr_vector_void_star &output_items);
};

#endif /* INCLUDED_HOWTO_RXBF_FEEDB_CF_H */
