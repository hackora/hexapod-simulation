#ifndef CUBE_H
#define CUBE_H

#include<gmParametricsModule>
#include<memory>
#include"simulator.h"



class Cube: public GMlib::SceneObject{

public:
    Cube();
    Cube(GMlib::Point<float,3>pos , float width, float breadth, float height);
     ~Cube();
    void setWidth(float);
    void setBreadth(float);
    void setHeight(float);

private:
    float width ;
    float breadth;
    float height;
    PlaneVector planes;
    void constructCube();

};


#endif // CUBE_H
