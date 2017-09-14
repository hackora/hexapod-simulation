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
    void setMaterial(const GMlib::Material &bm,const GMlib::Material &cm,const GMlib::Material &fm,const GMlib::Material &tm);
    void replot(int m1=10, int m2=10, int d1=1, int d2=1);
    void toggleDefaultVisualizer();
    void insert(const std::shared_ptr<GMlib::Scene>&scene);

protected:
    std::shared_ptr<Cube> body;
    std::vector<std::shared_ptr<Cube>> coxas;  //6
    std::vector<std::shared_ptr<Cube>> femurs; //6
    std::vector<std::shared_ptr<Tibia>> tibias; //6

private:
    void makeBody(GMlib::Point<float, 3> pos);
    void makeCoxas(GMlib::Point<float, 3> pos);
    void makeFemurs(GMlib::Point<float, 3> pos);
    void makeTibias(GMlib::Point<float, 3> pos);


};


#endif // HEXAPOD_H
