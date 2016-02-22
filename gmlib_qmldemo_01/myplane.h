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



/*! \file gmMYPlane.h
 *
 *  Interface for the MYPlane class.
 */

#ifndef __gmMYPlane_H__
#define __gmMYPlane_H__

#include "../gmlib/modules/parametrics/src/gmpsurf.h"
#include<parametrics/gmpplane>



  template <typename T>
  class MYPlane : public GMlib::PSurf<T,3> {
    GM_SCENEOBJECT(MYPlane)
  public:
    MYPlane( const GMlib::Point<T,3>& p1, const GMlib::Point<T,3>& p2, const GMlib::Point<T,3>& p3, const GMlib::Point<T,3>& p4 );
    MYPlane( const MYPlane<T>& copy );
    virtual ~MYPlane();
    GMlib::Point<float,3>& getCornerPoint(){

        return this->_pt;
    }

  protected:
  protected:
    GMlib::Point<T,3>                   _pt;
    GMlib::Point<T,3>		            _p1;
    GMlib::Point<T,3>		            _p2;
    GMlib::Point<T,3>		            _p3;
    GMlib::Point<T,3>		            _p4;

    void                      eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T                         getEndPU();
    T                         getEndPV();
    T                         getStartPU();
    T                         getStartPV();

  }; // END class MYPlane



#endif // __gmMYPlane_H__

