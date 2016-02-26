
#ifndef __COLLISIONE_H__
#define __COLLISIONE_H__

#include"testsphereball.h"
#include"mp.h"


class Collison{
// GM_SCENEOBJECT(Collison)

public:
    Collison(){}

    Collison(Testsphere *sphere,MP *wall,double x)
    {
        this->_sphere[0]=sphere;
        this->_wall=wall;
        this->_x=x;
        this->_isSw=true;
    }
    Collison(Testsphere *sphere1,Testsphere *sphere2,double x)
    {
        this->_sphere[0]=sphere1;
        this->_sphere[1]=sphere2;
        this->_x=x;
        this->_isSw=false;
    }

    Testsphere* getSphere(int i)
    {
        return _sphere[i];
    }

    MP* getWall() const
    {
        return _wall;
    }

    double getX()
    {
        return _x;
    }

    bool isSW()
    {
        return _isSw;
    }


    bool operator == (const Collison& other) const
    {
        if(_sphere[0] == other._sphere[0]) return true;
        if(_sphere[1] == other._sphere[0]) return true;
        if(!other._isSw && _sphere[0] == other._sphere[1]) return true;
        if(!other._isSw && _sphere[1] == other._sphere[1]) return true;
        return false;
    }

    bool operator < (const Collison& other) const
    {
        return _x < other._x;
    }
private:
    Testsphere *_sphere[2];
    MP *_wall;
    double _x;
    bool _isSw;
    };



#endif

