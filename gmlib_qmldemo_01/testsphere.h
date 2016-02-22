#ifndef TESTsphere_H
#define TESTsphere_H


#include <parametrics/gmpsphere>

#include<parametrics/gmpbeziersurf>
#include"mp.h"

// GMlib library
#include <gmOpenglModule>
#include <gmSceneModule>
#include <gmParametricsModule>
#include <parametrics/gmpsphere>
#include <parametrics/gmpplane>
// Qt library
#include <QTimerEvent>
#include <QRectF>
#include <QMouseEvent>
#include <QDebug>
// stl library
#include <stdexcept>
#include <thread>
#include <mutex>


class Testsphere : public GMlib::PSphere<float> {

   GM_SCENEOBJECT(Testsphere)
public:


  using PSphere::PSphere;

   Testsphere(GMlib::Vector<float,3> velocity,int mass,float radious,GMlib::PBezierSurf<float>* UnderPlane):GMlib::PSphere<float>(radious)
 {
     this->_velocity=velocity;
     this->_mass = mass;
     this->_UnderPlane=UnderPlane;
     _x=0;
}
  ~Testsphere();

//  void test02() {


//    m_test02 = true;
//  }



  void setVelocity(GMlib::Vector<float,3> velocity);

  GMlib::Vector<float,3> getVelocity();


  void setMass(int mass);


  int getMass();

  GMlib::Vector<float,3> getDs();

  int getv(int v);
  int getu(int u);

  void setX(int x);
  int getX();

  void updateSphere(int dt);
  void moveS(int dt,int x);
  void setUV(GMlib::PBezierSurf<float> *s);
  void localSimulate(double dt) ;
//      const GMlib::Vector<float,3> _g =(0,0,-9.81);

//      _ds=((dt * _velocity)+((1/2)*(dt)*(dt)*_g));
//    //rotate( GMlib::Angle(90) * dt, GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f ) );
//    //rotate( GMlib::Angle(180) * dt, GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
//      //updateSphere(dt);

//      this->translate(_ds);
//      _x=0;



    //translate(dt * GMlib::Vector<float,3>( 0.0f, 3.0f, 0.0f));




private:
 // bool m_test02 {false};
  //std::shared_ptr<Testsphere> test_02_sphere {nullptr};
  GMlib::Vector<float,3> _velocity;
  int _mass;
  GMlib::Vector<float,3> _ds;
  float _u;
  float _v;
  GMlib::UnitVector<float,3> _normal;
  int _x;
  GMlib::Point<float,3> _postion;
  GMlib::PBezierSurf<float>* _UnderPlane;


//  GMlib::UnitVector<float,3> _normal;



}; // END class Testsphere



#endif // TESTsphere_H
