/**********************************************************************************
**
** Copyright (C) 1994 Narvik University College
** Contact: GMlib Online Portal at http://episteme.hin.no
**
** This file is part of the Geometric Modeling Library, GMlib.
**
** GMlib is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** GMlib is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with GMlib.  If not, see <http://www.gnu.org/licenses/>.
**
**********************************************************************************/



/*! \file gmMYPlanenine.c
 *
 *  Implementation of the MYPlanenine template class.
 */


// for syntaxhighlighting
#include "MYPlanenine.h"




  template <typename T>
  inline
  MYPlanenine<T>::MYPlanenine( const GMlib::DMatrix<GMlib::Vector<T,3>>& m ) {

    _m = m;


   // _n  = u^v;

    this->_dm = GMlib::GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  inline
  MYPlanenine<T>::MYPlanenine( const MYPlanenine<T>& copy ):GMlib::PSurf<T,3>(copy) {

    _m   = copy._m;

//    _u    = copy._u;
//    _v    = copy._v;
  //  _n    = copy._n;
  }


  template <typename T>
  MYPlanenine<T>::~MYPlanenine() {}


//  template <typename T>
//  inline
//  const UnitVector<T,3>& MYPlanenine<T>::getNormal() const {

//    return _n;
//  }

  template <typename T>
  void MYPlanenine<T>::eval(T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    this->_p.setDim( d1+1, d2+1 );

    //this->_p[0][0] = _pt + u*_u + v*_v ;
    //this->_p[0][0]=_p1+u*(_p2-_p1)+v*(_p4-_p1+u*(_p1-_p2+_p3-_p4));
    //this->_p[0][0]=((1-u)^2)
      GMlib::DVector<T> u1(3);
      u1[0]=(1-u)*(1-u);
      u1[1]=2*u*(1-u);
      u1[2]=u*u;
      GMlib::DVector<T> v1(3);
      v1[0]=(1-v)*(1-v);
      v1[1]=2*v*(1-v);
      v1[2]=v*v;

      this->_p[0][0] = u1*(_m^v1);
    if( this->_dm == GMlib::GM_DERIVATION_EXPLICIT ) {



//    u=((1-u)*(1-u),2*u*(1-u),u*u);
//    v=((1-v)*(1-v),2*v*(1-v),v*v);
      // 1st
      GMlib::DVector<T>uu1(3);
      uu1[0]=(-2*(1-u));
      uu1[1]=2-4*u;
      uu1[2]=2*u;
      GMlib::DVector<T>vv(3);
      vv[0]=(-2*(1-v));
      vv[1]=2-4*v;
      vv[2]=2*v;

      if(d1)            this->_p[1][0] = uu1*(_m^v1); // S_u
      if(d2)            this->_p[0][1] = u1*(_m^vv); // S_v
      if(d1>1 && d2>1)  this->_p[1][1] = uu1*(_m^vv); // S_uv

      // 2nd
      if(d1>1)          this->_p[2][0] = GMlib::Vector<T,3>(T(0)); // S_uu
      if(d2>1)          this->_p[0][2] = GMlib::Vector<T,3>(T(0)); // S_vv
      if(d1>1 && d2)    this->_p[2][1] = GMlib::Vector<T,3>(T(0)); // S_uuv
      if(d1   && d2>1)  this->_p[1][2] = GMlib::Vector<T,3>(T(0)); // S_uvv
      if(d1>1 && d2>1)  this->_p[2][2] = GMlib::Vector<T,3>(T(0)); // S_uuvv

      // 3rd
      if(d1>2)          this->_p[3][0] = GMlib::Vector<T,3>(T(0)); // S_uuu
      if(d2>2)          this->_p[0][3] = GMlib::Vector<T,3>(T(0)); // S_vvv
      if(d1>2 && d2)    this->_p[3][1] = GMlib::Vector<T,3>(T(0)); // S_uuuv
      if(d1   && d2>2)  this->_p[1][3] = GMlib::Vector<T,3>(T(0)); // S_uvvv
      if(d1>2 && d2>1)  this->_p[3][2] = GMlib::Vector<T,3>(T(0)); // S_uuuvv
      if(d1>1 && d2>2)  this->_p[2][3] = GMlib::Vector<T,3>(T(0)); // S_uuvvv
      if(d1>2 && d2>2)  this->_p[3][3] = GMlib::Vector<T,3>(T(0)); // S_uuuvvv
    }
  }


  template <typename T>
  inline
  T MYPlanenine<T>::getEndPU()	{

    return T(1);
  }

  template <typename T>
  inline
  T MYPlanenine<T>::getEndPV()	{

    return T(1);
  }


  template <typename T>
  inline
  T MYPlanenine<T>::getStartPU() {

    return T(0);
  }


  template <typename T>
  inline
  T MYPlanenine<T>::getStartPV() {

    return T(0);
  }


//  template <typename T>
//  inline
//  const Vector<T,3>& MYPlanenine<T>::getU() const {

//    return _u;
//  }


//  template <typename T>
//  inline
//  const Vector<T,3>& MYPlanenine<T>::getV() const {

//    return _v;
//  }


//  template <typename T>
//  inline
//  bool MYPlanenine<T>::isClosedU() const {

//    return false;
//  }


//  template <typename T>
//  inline
//  bool MYPlanenine<T>::isClosedV() const {

//    return false;
//  }

//  template <typename T>
//  inline
//  void MYPlanenine<T>::setP( const Point<T,3>& p ) {

//    _pt = p;
//  }

//  template <typename T>
//  inline
//  void MYPlanenine<T>::setU( const Vector<T,3>& u ) {

//    _u = u;
//  }


//  template <typename T>
//  inline
//  void MYPlanenine<T>::setV( const Vector<T,3>& v ) {

//    _v = v;
  //}

