#ifndef SIMULATOR_H
#define SIMULATOR_H

//#include"collision_library.h"
#include "hexapod_controller.h"
#include<gmParametricsModule>
#include<vector>
#include<memory>

//helper types
//using DynSphere = collision::DynamicPhysObject<GMlib::PSphere<float>>;
//using Plane = collision::StaticPhysObject<GMlib::PPlane<float>>;
//using Bezier = collision::StaticPBezierSurf;
//using DynSpherePtrVector = std::vector<DynSphere*>; //raw pointer
//using PlanePtrVector =  std::vector<Plane*>;        //raw pointer
//using BezierPtrVector =  std::vector<Bezier*>;        //raw pointer
//using DynSphereVector = std::vector<std::unique_ptr<DynSphere>>;
//using PlaneVector =  std::vector<std::unique_ptr<Plane>>;
//using BezierVector = std::vector<std::unique_ptr<Bezier>>;

class Simulator{
public:
    explicit Simulator ( GMlib::Scene& scene);

    void setupSimulator();
    void insert_to_scene(std::shared_ptr<Hexapod> hexapod){ hexapod->insert(_scene);}

private:
    GMlib::Scene&                                      _scene;
    Hexapod_controller                          _hex_controller;
    std::shared_ptr<Hexapod>             _hexapod;

//    collision::collision_controller          _controller;
//    DynSphereVector                               _dspheres;
//    PlaneVector                                          _planes;
//    BezierVector                                        _beziers;


//    template <typename T>
//    void prepareAndInsert(const std::unique_ptr<T>& obj, int m1, int m2, int d1, int d2);

//    template <typename T>
//    void prepareAndInsertNoGravity(const std::unique_ptr<T>& obj, int m1, int m2, int d1, int d2);

};

//template <typename T>
//inline
//void Simulator::prepareAndInsert(const std::unique_ptr<T>& obj, int m1, int m2, int d1, int d2){

//    obj->toggleDefaultVisualizer();
//    obj->replot(m1,m2,d1,d2);
//    _scene.insert(obj.get());
//    _controller.add(obj.get());
//}

//template <typename T>
//inline
//void Simulator::prepareAndInsertNoGravity(const std::unique_ptr<T>& obj, int m1, int m2, int d1, int d2){

//    obj->toggleDefaultVisualizer();
//    obj->replot(m1,m2,d1,d2);
//    _scene.insert(obj.get());
//    _controller.add(obj.get());
//     auto sphere = dynamic_cast<DynSphere*>(obj.get());
//     sphere->environment = &_controller._noGravity;
//}


#endif // SIMULATOR_H
