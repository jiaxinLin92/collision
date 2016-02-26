

/*! \file gmMYPlane.h
 *
 *  Interface for the MYPlane class.
 */

#ifndef __GMWALL_H__
#define __GMWALL_H__

#include "../gmlib/modules/parametrics/src/gmpsurf.h"
#include<parametrics/gmpplane>


//  template <typename T>
  class MP : public GMlib::PPlane<float> {
  GM_SCENEOBJECT(MP)
  public:
   using PPlane::PPlane;
   ~MP(){}


  };





#endif // __gmMYPlane_H__

