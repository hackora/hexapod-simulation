#include"tibia.h"

Tibia::Tibia(GMlib::Vector<float,3> pos){
    // Start values
    _r = 0.2f;
    _h = 1.5f;
    translateGlobal(pos);
}


Tibia::Tibia(float r, float h){

    _r = r;
    _h = h;
}

void Tibia::setRadius(float r)
{
    _r = r;
}

void Tibia::setHeight(float h){

    _h = h;
}

float Tibia::getHeight() {

    return _h;
}
