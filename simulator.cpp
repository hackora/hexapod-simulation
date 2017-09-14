#include "simulator.h"

Simulator::Simulator (GMlib::Scene& scene) : _scene(scene) {}

void Simulator::setupSimulator() {


    _planes.push_back(std::make_unique<Plane>(
                          GMlib::Point<float,3>(-10.0f, -10.0f, 5.0f),
                          GMlib::Vector<float,3>(20.0f, 0.0f, 0.0f),
                          GMlib::Vector<float,3>(0.0f, 0.0f, -5.0f)
                          ));

    _planes.push_back(std::make_unique<Plane>(
                          GMlib::Point<float,3>(10.0f, -10.0f, 5.0f),
                          GMlib::Vector<float,3>(0.0f, 20.0f, 0.0f),
                          GMlib::Vector<float,3>(0.0f, 0.0f, -5.0f)
                          ));

    _planes.push_back(std::make_unique<Plane>(
                          GMlib::Point<float,3>(-10.0f, 10.0f, 5.0f),
                          GMlib::Vector<float,3>(0.0f, -20.0f, 0.0f),
                          GMlib::Vector<float,3>(0.0f, 0.0f, -5.0f)
                          ));

    _planes.push_back(std::make_unique<Plane>(
                          GMlib::Point<float,3>(10.0f, 10.0f, 5.0f),
                          GMlib::Vector<float,3>(-20.0f, 0.0f, 0.0f),
                          GMlib::Vector<float,3>(0.0f, 0.0f, -5.0f)
                          ));

    _planes.push_back(std::make_unique<Plane>(
                                  GMlib::Point<float,3>(-10.0f, -10.0f, 5.0f),
                                  GMlib::Vector<float,3>(20.0f, 0.0f, 0.0f),
                                  GMlib::Vector<float,3>(0.0f, 0.0f, -5.0f)
                                  ));

    _planes.push_back(std::make_unique<Plane>(
                          GMlib::Point<float,3>(-10.0f, -10.0f, 0.0f),
                          GMlib::Vector<float,3>(20.0f, 0.0f, 0.0f),
                          GMlib::Vector<float,3>(0.0f, 20.f, 0.0f)
                          ));

    _planes.push_back(std::make_unique<Plane>(
                          GMlib::Point<float,3>(-10.0f, -10.0f, 5.0f),
                          GMlib::Vector<float,3>(20.0f, 0.0f, 0.0f),
                          GMlib::Vector<float,3>(0.0f, 20.f, 0.0f)
                          ));

//    _dspheres.push_back( std::make_unique<DynSphere>());
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3> (0.0f, 5.0f, 2.0f));
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 0.5f, 0.0f);
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::ruby());

//    _dspheres.push_back( std::make_unique<DynSphere>());
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3> (5.0f, 0.0f, 2.0f));
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 0.5f, 0.0f);
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::sapphire());

//    _dspheres.push_back( std::make_unique<DynSphere>());
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3> (-5.0f, 5.0f, 5.0f));
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (2.0f, 0.0f, 0.0f);
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::obsidian());

//    _dspheres.push_back( std::make_unique<DynSphere>());
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3> (5.0f, 5.0f, 5.0f));
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (-2.0f, 0.0f, 0.0f);
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::gold());

//    _dspheres.push_back( std::make_unique<DynSphere>());
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3> (0.0f, 2.0f, 5.0f));
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (1.0f, 5.0f, 1.0f);
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::emerald());


//    _dspheres.push_back( std::make_unique<DynSphere>());
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3> (0.0f, -4.0f, 5.0f));
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 4.0f, 0.0f);
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::chrome());

//    _dspheres.push_back( std::make_unique<DynSphere>());
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3> (5.0f, 0.0f, 5.0f));
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (6.0f, 0.0f, 0.0f);
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::pearl());

//    _dspheres.push_back( std::make_unique<DynSphere>());
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3> (2.0f, 0.0f, 5.0f));
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (1.0f, 0.0f, 0.0f);
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::snow());

//    _dspheres.push_back( std::make_unique<DynSphere>());
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3> (0.0f, -8.0f, 5.0f));
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 4.0f, 0.0f);
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::chrome());

//    _dspheres.push_back( std::make_unique<DynSphere>());
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3> (-9.0f, 0.0f, 5.0f));
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (6.0f, 0.0f, 0.0f);
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::pearl());

//    _dspheres.push_back( std::make_unique<DynSphere>());
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3> (2.0f, -6.0f, 5.0f));
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (1.0f, 0.0f, 0.0f);
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::snow());




    for( const auto& plane : _planes )
        prepareAndInsert( plane, 2, 2, 1, 1);

    for( const auto& sphere : _dspheres ) {

        sphere->_sphereController = &_controller;
        prepareAndInsert( sphere, 10, 10, 1, 1);
    }

    _scene.insert(&_controller);

}

