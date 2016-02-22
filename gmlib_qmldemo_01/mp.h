

/*! \file gmMYPlane.h
 *
 *  Interface for the MYPlane class.
 */

#ifndef __GMWALL_H__
#define __GMWALL_H__

#include "../gmlib/modules/parametrics/src/gmpsurf.h"
#include<parametrics/gmpplane>
#include<parametrics/gmpbeziersurf>

//  template <typename T>
  class MP : public GMlib::PPlane<float> {
  GM_SCENEOBJECT(MP)
  public:
   using PPlane::PPlane;
   ~MP(){}

    GMlib::Point<float,3>& getCornerPoint(){

       return this->_pt;

    }
  };





#endif // __gmMYPlane_H__

