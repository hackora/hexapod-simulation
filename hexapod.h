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
    void insert(const std::shared_ptr<GMlib::Scene>&scene);
    std::shared_ptr<GMlib::PCylinder<float>> getBody(){return body;}
    std::vector<std::shared_ptr<Leg>> getLegs(){return legs;}
    void moveForward(double dt);

    IKAngles inverseKinematics(GMlib::Point<float,3> oldPos, GMlib::Point<float,3> newPos);
    GMlib::PSphere<float>* base;

    //For debugging
    int time =0;


protected:
    std::shared_ptr<GMlib::PCylinder<float>> body;
    std::vector<std::shared_ptr<Leg>> legs;    // 6

    GMlib::PCylinder<float>* shape1;
    GMlib::PCylinder<float>*shape2;
    GMlib::PCone<float>* shape3;
    GMlib::PSphere<float>* joint0;
    GMlib::PSphere<float>* joint1;
    GMlib::PSphere<float>* joint2;

    void localSimulate (double dt) override;

private:
    void makeBody(GMlib::Point<float, 3> pos);
    void makeLegs(GMlib::Point<float, 3> pos);

    void adjustPositions();
    void link();
};


#endif // HEXAPOD_H
