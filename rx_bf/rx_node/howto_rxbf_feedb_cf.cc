//Date last modified: March 24, 2012
//beamforming when feedback channel is digital, packetized and asynchronous.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
using namespace std;
#include <gr_fxpt.h>
#include <stdio.h>
#include <math.h>
#include <gr_math.h>
#include <algorithm>
#include <gr_io_signature.h>
#include <howto_rxbf_feedb_cf.h>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

howto_rxbf_feedb_cf_sptr 
howto_make_rxbf_feedb_cf (double sampling_rate, double treshold, int decim_factor, int nbr_samples_packet, int nbr_samples_cycle, double delay_security_factor, double time_delay)
{
  return howto_rxbf_feedb_cf_sptr (new howto_rxbf_feedb_cf (sampling_rate, treshold, decim_factor, nbr_samples_packet, nbr_samples_cycle, delay_security_factor, time_delay));
}

// constructor 
howto_rxbf_feedb_cf::howto_rxbf_feedb_cf (double sampling_rate, double treshold, int decim_factor, int nbr_samples_packet, int nbr_samples_cycle, double delay_security_factor, double time_delay)
  : gr_sync_decimator ("rxbf_feedb_cf",
		       gr_make_io_signature (1, 1, sizeof (gr_complex)),
		       gr_make_io_signature (1, 1, sizeof (float)),
                       decim_factor),
                       d_sampling_rate(sampling_rate),
		       d_treshold(treshold),
                       d_decim_factor(decim_factor), 
		       d_nbr_samples_packet(nbr_samples_packet), 
		       d_nbr_samples_cycle(nbr_samples_cycle),
		       d_delay_security_factor(delay_security_factor),
		       d_time_delay(time_delay)
                          
{ 
	/*d_treshold 		= 0.00025;
	d_nbr_samples_packet 	= 800;
	d_nbr_samples_cycle 	= 10000;
	d_delay_security_factor = 1.5;
	d_time_delay 		= 0.015;*/

	cpt_samples 		= 0;
	cpt_samples_packet 	= 0;
	packet_number 		= 0;
	feedback_symbol 	= 0;
	avg_rss 		= 0;
	current_rss 		= 0;
	last_rss 		= 0;
	rss_max 		= 0;
	past_rss 		= {0,0,0,0};

	delay_since_last_rss_meas = 0;
	last_cpt_samples = 0;
}

// destructor
howto_rxbf_feedb_cf::~howto_rxbf_feedb_cf ()
{
}

// work() function where all the action actually takes place
int 
howto_rxbf_feedb_cf::work (int noutput_items,
	      gr_vector_const_void_star &input_items,
	      gr_vector_void_star &output_items)
{
  const gr_complex *in = (const gr_complex *) input_items[0]; 
  float *out = (float *) output_items[0]; 
 


  int j=0;
  for (int i = 0; i < noutput_items*d_decim_factor; i++){
	cpt_samples++;

    	// Generate output
	// ---------------
	if ( (cpt_samples)%d_nbr_samples_cycle == 0 ){ 		
	    	out[j] = feedback_symbol; 
	    	printf ("Output = %d\n", (int)out[j]); 
	    	j+=1; 
	} // End of if( (cpt_samples)%d_nbr_samples_cycle == 0 )
	
	// Monitor input	
	// -------------
    	if (std::abs(in[i]) > d_treshold){	    
	    cpt_samples_packet++;
	    avg_rss = avg_rss + std::abs(in[i]);
	    // Packet complete
	    if (cpt_samples_packet == d_nbr_samples_packet){
		current_rss = avg_rss/(d_nbr_samples_packet);
		delay_since_last_rss_meas = cpt_samples - last_cpt_samples;
		last_cpt_samples = cpt_samples;
		//printf(" -- Packet complete - RSS = %f \n", current_rss);
		//printf(" -- delay_since_last_rss_meas = %d  \n", delay_since_last_rss_meas);
		//printf(" -- RSS = %f  -- last RSS  %f\n", current_rss, last_rss);
		if ( (delay_since_last_rss_meas < d_time_delay * d_sampling_rate * d_delay_security_factor) && (current_rss > last_rss) ){		
		    if (packet_number<1000) { packet_number +=1; }
        	    else 			{ packet_number = 1; } 
		    //printf(" -- RSS = %f \n", current_rss);
		    rss_max=*max_element(past_rss,past_rss+4);
		    if (current_rss > rss_max){ feedback_symbol = packet_number; }   
        	    else			  { feedback_symbol = -packet_number; }
		    avg_rss=0; 
        	    cpt_samples_packet = 0;
      		    past_rss[3]=past_rss[2]; 
        	    past_rss[2]=past_rss[1];
        	    past_rss[1]=past_rss[0];
        	    past_rss[0]=current_rss;
		} // End of if( delay_since_last_rss_meas < d_time_delay * d_sampling_rate *1.5)
		last_rss = current_rss;
	    } // End of if(cpt_samples_packet == d_nbr_samples_packet)
	} // End of if(std::abs(in[i]) > d_treshold)
	else{
	    cpt_samples_packet = 0;
	    avg_rss = 0;
	} // End of else-statement of if(std::abs(in[i]) > d_treshold)


  } //end of for(int i = 0; i < noutput_items*d_decim_factor; i++)

  return noutput_items;
  //printf("End of work()...\n");

} // end of work()


