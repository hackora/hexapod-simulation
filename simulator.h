#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <collision_library.h>


#include <gmParametricsModule>
#include <vector>
#include <memory>

using DynSphere             = collision::DynamicPhysObject<GMlib::PSphere<float>>;
using StatSphere            = collision::StaticPhysObject<GMlib::PSphere<float>>;
using Plane                 = collision::StaticPhysObject<GMlib::PPlane<float>>;

using Pyramid               = GMlib::PTriangle<float, 3>;

using DynSpherePtrVector    = std::vector<DynSphere* >;
using StatSpherePtrVector   = std::vector<StatSphere* >;
using PlanePtrVector        = std::vector<Plane* >;

using PyramidPtrVector      = std::vector<Pyramid* >;

using DynSphereVector       = std::vector<std::unique_ptr<DynSphere>>;
using StatSphereVector      = std::vector<std::unique_ptr<StatSphere>>;
using PlaneVector           = std::vector<std::unique_ptr<Plane>>;

using PyramidVector         = std::vector<std::unique_ptr<Pyramid>>;

class Simulator {

public:
    explicit Simulator( GMlib::Scene& scene );

    void    setupSimulator();

private:
    GMlib::Scene&               _scene;
    collision::MyController     _controller;
    DynSphereVector             _dspheres;
    StatSphereVector            _S_spheres;
    PlaneVector                 _planes;

    template <typename T>           // m1 & m2 = sections, d1 & d2 = nr. of derivatives
    void prepareAndInsert( const std::unique_ptr<T>& obj, int m1, int m2, int d1, int d2);

};

template <typename T>
inline
void Simulator::prepareAndInsert(const std::unique_ptr<T> &obj, int m1, int m2, int d1, int d2)
{
    obj->toggleDefaultVisualizer();
    obj->replot(m1, m2, d1, d2);
    _scene.insert(obj.get());
    _controller.add(obj.get());
}


#endif // SIMULATOR_H
