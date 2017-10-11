#ifndef CUBE_H
#define CUBE_H

#include<gmParametricsModule>
#include<memory>
//#include<collision_library.h>

using Plane = GMlib::PPlane<float> /*collision::StaticPhysObject<GMlib::PPlane<float>>*/;


  class Cube : public GMlib::SceneObject {
      GM_SCENEOBJECT(Cube)

    public:
        Cube();
        Cube(GMlib::Point<float,3>pos, float width, float breadth, float height);
        Cube(const Cube &copy);
         virtual ~Cube(){};
        void setWidth(float);
        void setBreadth(float);
        void setHeight(float);
        void setMaterial(const GMlib::Material &m);
        void replot(int m1=10, int m2=10, int d1=1, int d2=1);
        void toggleDefaultVisualizer();
        void insertToScene(const std::shared_ptr<GMlib::Scene>&scene);

    protected:
        float width ;
        float breadth;
        float height;
        GMlib::Point<float,3>pos;
        std::vector<std::shared_ptr<Plane>> planes;


    private:
        void makeCube();

    };

#endif // CUBE_H
