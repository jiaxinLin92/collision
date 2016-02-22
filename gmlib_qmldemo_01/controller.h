
#ifndef __GMCONTROLLER_H__
#define __GMCONTROLLER_H__

#include"testsphereball.h"
#include"mp.h"
#include"collision.h"
#include"myplane.h"
#include"myplanenine.h"

class controller: public GMlib::PSphere<float> {
GM_SCENEOBJECT(controller)

private:
  MYPlanenine<float>* _plane;
  GMlib::Array<Testsphere*> _sphereArray;
  GMlib::Array<MP *> _wallArray;
  GMlib::Array<Collison> _collisionArray;

public:
    controller(MYPlanenine<float>* plane)
    {
        this->_plane=plane;
        this->toggleDefaultVisualizer();
        this->replot(20,20,1,1);
        this->setVisible(false);
        this->insert(_plane);

    }
    void addSphere(Testsphere* ball)
    {
        this->insert(ball);
        _sphereArray+=ball;
    }

    void addWall(MP* wall)
    {
        this->insert(wall);
        _wallArray+=wall;
    }


    void findcollisionSW(Testsphere *s,MP *w,GMlib::Array<Collison> &collisionArray)
    {
        GMlib::Point<float,3> positionSphere = s->getPos();

        w->getClosestPoint(this->getPos(),_u,_v);
        GMlib::DMatrix<GMlib::Vector<float,3>> matr = w->evaluate(_u,_v,1,1);



        float radious = s->getRadius();

        GMlib::Vector<float,3> d = matr[0][0]-positionSphere;
        GMlib::Vector<float,3> n = w->getNormal();
        GMlib::Vector<float,3> ds = s->getDs();

        // check if the ball running out the wall

         double x = (radious+(d*n))/(ds*n);
         if(x >0 && x<=1)
            {
             collisionArray.insertAlways(Collison(s,w,x));
            }



    }

    void findcollisionSS(Testsphere *s1,Testsphere *s2,GMlib::Array<Collison> &collisionArray)
    {

        GMlib::Point<float,3> positionSphere1 = s1->getPos();
        GMlib::Point<float,3> positionSphere2 = s2->getPos();
        GMlib::Vector<float,3> ds1 = s1->getDs();
        GMlib::Vector<float,3> ds2 = s2->getDs();
        //formular
        //p1+xds1-(p2+xds2)=p1-p2+x(ds1-ds2)
        //dp=p1-p2
        //ds=ds1-ds2
        double st1,st2;
        st1 = s1->getX();
        st2 = s2->getX();
        GMlib::Vector<float,3> Ds = (1+st1)*ds1 - (1+st2)*ds2;
        GMlib::Vector<float,3> Dp = positionSphere1 - positionSphere2 +st1*ds1 - st2*ds2 ;
        float r = s1->getRadius() + s2->getRadius();

        double a = Ds*Ds;
        double b = 2*Dp*Ds;
        double c = Dp*Dp -r*r;

        double delta = b*b-a*c;
        if(delta < 0){
        }else if(delta == 0){
        }else{
              double x = (-b-sqrt(delta))/a;
              if(x>0 && x<=1){
                collisionArray.insertAlways(Collison(s1,s2,x));
              }
            }
    }


    void collisionSW(Testsphere *s,MP *w, double dt)
    {
        GMlib::Vector<float,3> _vel = s->getVelocity();
        _vel -= 2*(w->getNormal()*_vel)*w->getNormal();
        s->setVelocity(_vel);
        s->computeStep(dt);
    }
    void collisionSS(Testsphere *s1,Testsphere *s2, double dt)
    {

        GMlib::Vector<float,3> newvelocity1 = s1->getVelocity();
        GMlib::UnitVector<float,3> d = s2->getPos() - s1->getPos();
        GMlib::Vector<float,3> v1 = (newvelocity1*d)*d;
        GMlib::Vector<float,3> v1n = newvelocity1 - v1;

        GMlib::Vector<float,3> newvelocity2 = s2->getVelocity();
        GMlib::Vector<float,3> v2 = (newvelocity2*d)*d;
        GMlib::Vector<float,3> v2n = newvelocity2 - v2;


        double M1, M2, M3;
        M1 = (s1->getMass() - s2->getMass()) / (s1->getMass() + s2->getMass());
        M2 = (2*s2->getMass()/(s1->getMass() + s2->getMass()));
        M3 = (2*s1->getMass()/(s1->getMass() + s2->getMass()));
        GMlib::Vector<float,3> v1after = M1*v1 + M2*v2;
        GMlib::Vector<float,3> v2after = -M1*v2 + M3*v1;

        GMlib::Vector<float,3> newvelocityball1 = v1after + v1n;
        GMlib::Vector<float,3> newvelocityball2 = v2after + v2n;


        s1->setVelocity(newvelocityball1);
        s2->setVelocity(newvelocityball2);

        s1->computeStep(dt);
        s2->computeStep(dt);
    }

protected:
  void localSimulate(double dt)
  {

      for(int i=0; i<_sphereArray.getSize(); i++){

        _sphereArray[i]->computeStep(dt);
      }


      for (int i=0;i<_sphereArray.size();i++){
        for(int j=i+1;j<_sphereArray.size();j++){
          findcollisionSS(_sphereArray[i],_sphereArray[j],_collisionArray);
        }
      }

      for (int i=0;i<_sphereArray.size();i++){
        for(int j=0;j<_wallArray.size();j++){
          findcollisionSW(_sphereArray[i],_wallArray[j],_collisionArray);
        }
      }

      while(_collisionArray.getSize()>0)
      {

        _collisionArray.sort();
        _collisionArray.makeUnique();

        auto collison = _collisionArray[0];

        _collisionArray.removeIndex(0);

        if(collison.isSW()){

          collisionSW(collison.getSphere(0), collison.getWall(),(1-collison.getX())*dt);

        }

            else{


                  collisionSS(collison.getSphere(0), collison.getSphere(1),(1-collison.getX())*dt);

            }

      }
    }

};

#endif

