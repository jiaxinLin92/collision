#ifndef TESTsphere_H
#define TESTsphere_H


#include <parametrics/gmpsphere>
//#include "myplane.h"
#include "myplanenine.h"

class Testsphere : public GMlib::PSphere<float> {
  GM_SCENEOBJECT(Testsphere)
public:

  using PSphere::PSphere;
  Testsphere(int mass,GMlib::Vector<float,3> velocity,float radious,MYPlanenine<float>* plane):GMlib::PSphere<float>(radious){

      this->_mass = mass;
      this->_velocity=velocity;
      this->_plane = plane;
      this->_x=0;
//      this->_p=pos;
//      this->translate(_p);

      //this->translateParent(GMlib::Point<float,3>(0,0,0));
  }
  ~Testsphere(){}
  void setVelocity(GMlib::Vector<float,3> velocity)
  {
      _velocity=velocity;
  }

 GMlib::Vector<float,3> getVelocity()
  {

      return _velocity;
  }

  void setMass(int mass)
  {
      _mass=mass;
  }

  int getMass(){

      return _mass;
  }

  double getX(){
    return _x;
  }


  void setX(double x){
    _x = x;
  }
  GMlib::Vector<float,3> getDs()
  {
      return _ds;

  }

  void setUV(MYPlanenine<float>* p){


      p->estimateClpPar(this->getPos(),_u,_v);
  }
  void setPosition(GMlib::Point<float,3> pos){

      _p=pos;

  }

  void computeStep(double dt){

    const GMlib::Vector<float,3> g(0.0, 0.0, -9.81);

    _ds = dt*_velocity + (0.5*dt*dt)*g;

    _plane->getClosestPoint( this->getPos() + _ds, _u, _v );

    GMlib::DMatrix<GMlib::Vector<float,3> > m = _plane->evaluate(_u,_v,1,1);

    GMlib::UnitVector<float,3> normal = m[0][1]^m[1][0];

//
    _ds = m[0][0] +this->getRadius()*normal - this->getPos();

    // the ball move, velocity decrease and stable
    _velocity  += dt*g;
    _velocity  -= (normal*_velocity)*normal ;
  }

  GMlib::Vector<float,3> getsurfnormal()
  {
      _plane->getClosestPoint(this->getPos(),_u,_v);
      GMlib::DMatrix<GMlib::Vector<float,3> > m = _plane->evaluate(_u,_v,1,1);
      GMlib::UnitVector<float,3> normal = m[0][1]^m[1][0];
      return normal;



  }



protected:
  void localSimulate(double dt) override {
      //const GMlib::Vector<float,3> g =(0,0,-9.81);
//      _ds=((dt * _velocity)+((1/2)*(dt)*(dt)*g));
      computeStep(dt);
      rotateGlobal(_ds.getLength(),this->getsurfnormal()^_ds);
      translateGlobal(_ds);


    //translate(dt * GMlib::Vector<float,3>( 0.0f, 3.0f, 0.0f));


  }

private:

  GMlib::Vector<float,3> _velocity;
  int _mass;
  GMlib::Vector<float,3> _ds;
  MYPlanenine<float>* _plane;
  double _x;//time
  float _u;
  float _v;
  GMlib::UnitVector<float,3> _normal;
  GMlib::Point<float,3> _p;


}; // END class Testsphere



#endif // TESTsphere_H
