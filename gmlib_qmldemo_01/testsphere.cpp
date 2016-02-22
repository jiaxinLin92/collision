#ifndef AAATESTsphere_H
#define AAATESTsphere_H


#include "testsphere.h"


  Testsphere::~Testsphere() {

  }

  void Testsphere::setVelocity(GMlib::Vector<float,3> velocity)
  {
      _velocity=velocity;
  }

 GMlib::Vector<float,3> Testsphere::getVelocity()
  {
      //_velocity=velocity;
      return _velocity;
  }

  void Testsphere::setMass(int mass)
  {
      _mass=mass;
  }

  int Testsphere::getMass(){
      //_mass=mass;
      return _mass;
  }

 GMlib::Vector<float,3>  Testsphere::getDs()
  {
      return _ds;

  }
  int Testsphere::getv(int v){

      v=(1,0);//x+
      _v=v;
      return _v;
  }
  int Testsphere::getu(int u){
      u=(0,1);//y+
      _u=u;
      return _u;

  }

  void Testsphere::setX(int x){
      _x=x;
  }

  int Testsphere::getX(){
      return _x;
  }

  void Testsphere::updateSphere(int dt){
      const GMlib::Vector<float,3> _g =(0,0,-9.81);
      _ds=((dt * _velocity)+((1/2)*(dt)*(dt)*_g));

      _postion = this->getPos()+_ds;

      _UnderPlane->getClosestPoint(_postion,_u,_v);

      GMlib::DMatrix<GMlib::Vector<float,3> > _m= _UnderPlane->evaluate(_u,_v,1,1);

      _normal= _m[0][1]^_m[1][0];

      GMlib::Vector<float,3> _newpos = _m[0][0] + this->getRadius()*_normal;
      _ds = _newpos - this->getPos();


      _velocity  += dt*_g;
      _velocity  -= (_normal*_velocity)*_normal ;
      double old_velocity = _velocity*_velocity - 2*_g*_ds;

      double new_velocity = _velocity*_velocity;

      if (old_velocity>0)
      {
        if(new_velocity > 0.001)
        _velocity *= sqrt(old_velocity/new_velocity);
      }



  }

  void Testsphere::moveS(int dt,int x){
      const GMlib::Vector<float,3> _g =(0,0,-9.81);
      this->translate((x*dt)*_ds);
      _velocity +=((1-x)*dt)*_g;
      GMlib::Vector<float,3> _normal=_UnderPlane->getNormal();
      _velocity -=(_velocity*_normal)*_normal;
  }
  void Testsphere::setUV(GMlib::PBezierSurf<float> *s){
      s->estimateClpPar(this->getPos(),_u,_v);
  }


  void Testsphere::localSimulate(double dt)  {
      const GMlib::Vector<float,3> _g =(0,0,-9.81);

      _ds=((dt * _velocity)+((1/2)*(dt)*(dt)*_g));
    //rotate( GMlib::Angle(90) * dt, GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f ) );
    //rotate( GMlib::Angle(180) * dt, GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
      //updateSphere(dt);

      this->translate(_ds);
      _x=0;


}






#endif // TESTsphere_H
