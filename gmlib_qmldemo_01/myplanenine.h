
#ifndef __gmMYPlanenine_H__
#define __gmMYPlanenine_H__

#include "../gmlib/modules/parametrics/src/gmpsurf.h"




  template <typename T>
  class MYPlanenine : public GMlib::PSurf<T,3> {
    GM_SCENEOBJECT(MYPlanenine)
  public:
    MYPlanenine( const GMlib::DMatrix<GMlib::Vector<T,3>>& m);
    MYPlanenine( const MYPlanenine<T>& copy );
    virtual ~MYPlanenine();


  protected:
    GMlib::DMatrix<GMlib::Vector<T,3>>	_m;



    void                      eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T                         getEndPU();
    T                         getEndPV();
    T                         getStartPU();
    T                         getStartPV();

  }; // END class MYPlanenine



// Include MYPlanenine class function implementations
#include "MYPlanenine.c"



#endif // __gmMYPlanenine_H__

