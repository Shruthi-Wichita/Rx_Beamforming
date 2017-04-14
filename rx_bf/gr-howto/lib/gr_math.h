/* -*- c++ -*- */
/*
* Copyright 2003 Free Software Foundation, Inc.
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
/*
* mathematical odds and ends.
*/
 
#ifndef _GR_MATH_H_
#define _GR_MATH_H_
 
long gr_gcd (long m, long n);
 
// returns a non-zero value if value is "not-a-number" (NaN), and 0 otherwise
int gr_isnan (double value);
 
// returns a non-zero value if the value of x has its sign bit set.
//
// This  is  not  the  same  as `x < 0.0', because IEEE 754 floating point
// allows zero to be signed.  The comparison `-0.0 < 0.0'  is  false,  but
// `gr_signbit (-0.0)' will return a nonzero value. 
 int gr_signbit (double x);
 
 
 #endif /* _GR_MATH_H_ */
