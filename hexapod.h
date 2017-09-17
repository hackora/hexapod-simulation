#ifndef HEXAPOD_H
#define HEXAPOD_H

#include<gmParametricsModule>
#include<memory>

#include"cube.h"
#include"tibia.h"


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

protected:
    std::shared_ptr<GMlib::PCylinder<float>> body;
    std::vector<std::shared_ptr< GMlib::PCylinder<float>>> coxas;  //6
    std::vector<std::shared_ptr<GMlib::PCylinder<float>>> femurs; //6
    std::vector<std::shared_ptr<GMlib::PCone<float>>> tibias; //6
    std::vector<std::shared_ptr< GMlib::PSphere<float>>> joints;    // 3*6 = 18

private:
    void makeBody(GMlib::Point<float, 3> pos);
    void makeCoxas();
    void makeFemurs();
    void makeTibias();
    void makeJoints();
    void adjustPositions();
    void link();


};


#endif // HEXAPOD_H
