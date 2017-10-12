#ifndef HEXAPOD_H
#define HEXAPOD_H

#include<gmParametricsModule>
#include<memory>

#include"tibia.h"
#include "leg.h"

class Hexapod: public GMlib::SceneObject {
    GM_SCENEOBJECT(Hexapod)

public:
    Hexapod(GMlib::Point<float,3> pos= {0.0f,0.0f,0.0f} );
    Hexapod(const Hexapod &copy){}
    virtual ~Hexapod() {}
    void setMaterial(const GMlib::Material &bm, const GMlib::Material &cm, const GMlib::Material &fm, const GMlib::Material &tm, const GMlib::Material &jm);
    void replot(int m1=20, int m2=20, int d1=1, int d2=1);
    void toggleDefaultVisualizer();
    void insert(GMlib::Scene &scene);
    void moveForward(double dt);
    std::shared_ptr<GMlib::PCylinder<float>> getBody(){return body;}
    std::vector<std::shared_ptr<Leg>> getLegs(){return legs;}

protected:
    std::shared_ptr<GMlib::PCylinder<float>> body;
    std::vector<std::shared_ptr<Leg>> legs;    // 6

private:
    void localSimulate (double dt) override;
    void makeBody(GMlib::Point<float, 3> pos);
    void makeLegs(GMlib::Point<float, 3> pos);
    void adjustPositions();
    void link();


};


#endif // HEXAPOD_H
