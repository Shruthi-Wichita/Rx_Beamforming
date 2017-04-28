 /* -*- c++ -*- */
/*
  * Copyright 2004 Free Software Foundation, Inc.
  * 
  * This file is part of GNU Radio
  * 
  * GNU Radio is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 2, or (at your option)
  * any later version.
  * 
  * GNU Radio is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  * 
  * You should have received a copy of the GNU General Public License
  * along with GNU Radio; see the file COPYING.  If not, write to
  * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
  * Boston, MA 02111-1307, USA.
  */
 
 #ifndef INCLUDED_GR_BLOCK_H
 #define INCLUDED_GR_BLOCK_H
 
 #include <gr_runtime.h>
 #include <string>
 
 class gr_block {
 
  public:
   
   virtual ~gr_block ();
   
   std::string name () const { return d_name; }
   gr_io_signature_sptr input_signature () const  { return d_input_signature; }
   gr_io_signature_sptr output_signature () const { return d_output_signature; }
   long unique_id () const { return d_unique_id; }
 
   // ----------------------------------------------------------------
   //            override these to define your behavior
   // ----------------------------------------------------------------
 
   virtual void forecast (int noutput_items,
                          gr_vector_int &ninput_items_required);
  virtual int general_work (int noutput_items,
                             gr_vector_int &ninput_items,
                             gr_vector_const_void_star &input_items,
                             gr_vector_void_star &output_items) = 0;

   virtual bool check_topology (int ninputs, int noutputs);
 
   // ----------------------------------------------------------------
 
   void set_output_multiple (int multiple);
   int  output_multiple () const { return d_output_multiple; }
 
   void consume (int which_input, int how_many_items);
 
   void consume_each (int how_many_items);
 
   void  set_relative_rate (double relative_rate);
 
   double relative_rate () const { return d_relative_rate; }
 
// ----------------------------------------------------------------------------
 
  private:
 
   std::string           d_name;
   gr_io_signature_sptr  d_input_signature;
  gr_io_signature_sptr  d_output_signature;
   int                   d_output_multiple;
   double                d_relative_rate;        // approx output_rate / input_rate
   gr_block_detail_sptr  d_detail;               // implementation details
   long                  d_unique_id;            // convenient for debugging
   
  protected:
 
   gr_block (const std::string &name,
             gr_io_signature_sptr input_signature,
            gr_io_signature_sptr output_signature);

  void set_input_signature (gr_io_signature_sptr iosig){
     d_input_signature = iosig;
   }

   void set_output_signature (gr_io_signature_sptr iosig){
    d_output_signature = iosig;
  }

   // These are really only for internal use, but leaving them public avoids
 // having to work up an ever-varying list of friends

  public:
  gr_block_detail_sptr detail () const { return d_detail; }
  void set_detail (gr_block_detail_sptr detail) { d_detail = detail; }
 };
 long gr_block_ncurrently_allocated ();
 
 #endif /* INCLUDED_GR_BLOCK_H */

