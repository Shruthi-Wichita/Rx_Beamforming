//Date last modified: March 24, 2012
//beamforming when feedback channel is digital, packetized and asynchronous.


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gr_fxpt.h>
#include <stdio.h>
#include <gr_io_signature.h>
#include <howto_rxbf_randphpert_f.h>

howto_rxbf_randphpert_f_sptr 
howto_make_rxbf_randphpert_f (double random_perturbation_size, int bf_flag)
{
  return howto_rxbf_randphpert_f_sptr (new howto_rxbf_randphpert_f (random_perturbation_size, bf_flag));
}

// constructor 
howto_rxbf_randphpert_f::howto_rxbf_randphpert_f (double random_perturbation_size, int bf_flag)
  : gr_sync_block ("rxbf_randphpert_f",
		       gr_make_io_signature (1, 1, sizeof (float)),
		       gr_make_io_signature (0, 0, 0)), 
                       d_random_perturbation_size(random_perturbation_size), 
                       d_bf_flag(bf_flag)
                          
{ 
   cum_ang=0;
   etojphi=(gr_complex)1;
   rand_pert_from_prev_iter=0;
   d_seed=42; // seed value for random number generator
   d_random_perturbation_size = (3.141592654/180)*d_random_perturbation_size; // input angle (i.e., the random phase perturbation to be applied in each time-slot) is converted from degrees to radians. 
   last_in_i = 0;
   d_complex_gain=1;
}

// destructor
howto_rxbf_randphpert_f::~howto_rxbf_randphpert_f ()
{
}

int 
howto_rxbf_randphpert_f::work (int noutput_items,
	      gr_vector_const_void_star &input_items,
	      gr_vector_void_star &output_items)
{

  const float *in = (const float *) input_items[0]; 

  double randp; // holds the random phase perturbation to apply in each time-slot 
  double i_out, q_out;

  //printf("***beamforming flag=%d\n",d_bf_flag);
  //printf("noutput_items=%d\n",noutput_items);
  
for (int i = 0; i < noutput_items; i++){

   if (d_bf_flag==0){
     //printf("No beamforming!\n");
     //out[i]=1;
   }
   else {
      //beamforming
      if ( (in[i] > 0) || (- in[i] > 0) ){ //update the transmitter's phase when actual feedback bit is present at input
	if (in[i] != last_in_i){
	 printf ("Feedback from receiver is: %d\n", (int)in[i]);
	 last_in_i = in[i];
         // generate a uniformly distributed random perturbation in the set {-d_random_perturbation_size, d_random_perturbation_size} where d_random_perturbation_size is the perturbation angle in the radians
         randp = ((float)(d_seed.ran1()))*2;
         if (randp<1){
             randp = -d_random_perturbation_size; }
         else {
             randp =  d_random_perturbation_size; }
         //printf ("random perturbation = %f\n", randp); // for de-bugging purpose
         cum_ang+=randp; 
         //undo previous phase if feedback bit is 0.
         if (  in[i] < 0 ){
            cum_ang-=rand_pert_from_prev_iter;
         }
         //printf ("Feedback from receiver is: %d\n", (int)in[i]);
         //printf ("cumulative angle = %f\n", cum_ang); // for de-bugging purpose
         cum_ang=fmod(cum_ang,6.283185308);//compute modulo-2*pi phase
         i_out=gr_fxpt::cos (gr_fxpt::float_to_fixed(cum_ang)); 
         q_out=gr_fxpt::sin (gr_fxpt::float_to_fixed(cum_ang));
         etojphi=gr_complex (i_out, q_out); 
         rand_pert_from_prev_iter=randp; 
	 d_complex_gain=etojphi;
	}
      }
      //out[i]=etojphi;
   } 
} 

//d_complex_gain=etojphi;

return noutput_items;
//printf("End of work()...\n");

} // end of work()

void
howto_rxbf_randphpert_f::set_bf_flag (int bf_flag)
{
  d_bf_flag = bf_flag;
}

