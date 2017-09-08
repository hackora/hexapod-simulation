#ifndef TIBIA_H
#define TIBIA_H

#include<gmParametricsModule>
#include<memory>
#include"simulator.h"



class Tibia{

public:
    Tibia(GMlib::Vector<float,3> pos);
    void insertPyramid(const std::shared_ptr<GMlib::Scene>& s);
    virtual ~Tibia() {}

    void setRadius(float);
    void setHeight(float);

private:
    float radius;
    float height;
    GMlib::Vector<float,3> position;
};


#endif // TIBIA_H
