#ifndef INCLUDED_GR_RANDOM_H
#define INCLUDED_GR_RANDOM_H
 
#include <gr_complex.h>
 
/*!
00029  * \brief pseudo random number generator
00030  * \ingroup math_blk
00031  */
class gr_random {
 protected:
   static const int NTAB  = 32;
   long  d_seed;
   long  d_iy;
   long  d_iv[NTAB];
   int   d_iset;
   float d_gset;
 
   
 public: 
   gr_random (long seed=3021);
 
   void reseed (long seed);
 
 /*!
00048    * \brief uniform random deviate in the range [0.0, 1.0)
00049    */
  float ran1 ();
 
   /*!
00053    * \brief normally distributed deviate with zero mean and variance 1
00054    */
  float gasdev ();
 
  float laplacian ();
  float impulse (float factor);
  float rayleigh ();
  gr_complex rayleigh_complex ();
 };
 
#endif /* INCLUDED_GR_RANDOM_H */
 
