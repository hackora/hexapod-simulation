#ifndef TIBIA_H
#define TIBIA_H

#include<gmParametricsModule>
#include<memory>


class Tibia: public GMlib::PCone<float>{

public:
    Tibia(GMlib::Vector<float,3> pos = GMlib::Point<float,3>(0.0f,0.0f,0.0f));
    Tibia(GMlib::Point<float,3>pos , float r, float h);
    virtual ~Tibia() {}
    void setRadius(float);
    void setHeight(float);

};


#endif // TIBIA_H