#include"tibia.h"

Tibia::Tibia(GMlib::Vector<float,3> pos){
    // Start values
    _r = 0.2f;
    _h = 1.5f;
    translateGlobal(pos);
}


Tibia::Tibia(GMlib::Point<float,3>pos , float r, float h){

    _r = r;
    _h = h;
    translateGlobal(pos);
}

void Tibia::setRadius(float r)
{
    _r = r;
}

void Tibia::setHeight(float h){

    _h = h;
}
