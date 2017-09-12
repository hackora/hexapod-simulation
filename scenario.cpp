#include "scenario.h"

#include "testtorus.h"

#include<collision_library.h>
#include "simulator.h"
#include "cube.h"
#include "tibia.h"

//// hidmanager
//#include "hidmanager/defaulthidmanager.h"

// gmlib
#include <gmOpenglModule>
#include <gmSceneModule>
#include <gmParametricsModule>

// qt
#include <QQuickItem>



void Scenario::initializeScenario() {

  // Insert a light
  GMlib::Point<GLfloat,3> init_light_pos( 2.0, 4.0, 10 );
  GMlib::PointLight *light = new GMlib::PointLight(  GMlib::GMcolor::white(), GMlib::GMcolor::white(),
                                                     GMlib::GMcolor::white(), init_light_pos );
  light->setAttenuation(0.8, 0.002, 0.0008);
  scene()->insertLight( light, false );

  // Insert Sun
  scene()->insertSun();

  // Default camera parameters
  int init_viewport_size = 600;
  GMlib::Point<float,3> init_cam_pos(  0.0f, 0.0f, 0.0f );
  GMlib::Vector<float,3> init_cam_dir( 0.0f, 1.0f, 0.0f );
  GMlib::Vector<float,3> init_cam_up(  0.0f, 0.0f, 1.0f );

  // Projection cam
  auto proj_rcpair = createRCPair("Projection");
  proj_rcpair.camera->set(init_cam_pos,init_cam_dir,init_cam_up);
  proj_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  proj_rcpair.camera->rotateGlobal( GMlib::Angle(-45), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
  proj_rcpair.camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -20.0f, 20.0f ) );
  scene()->insertCamera( proj_rcpair.camera.get() );
  proj_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Front cam
  auto front_rcpair = createRCPair("Front");
  front_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( 0.0f, -50.0f, 0.0f ), init_cam_dir, init_cam_up );
  front_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  scene()->insertCamera( front_rcpair.camera.get() );
  front_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Side cam
  auto side_rcpair = createRCPair("Side");
  side_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( -50.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ), init_cam_up );
  side_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  scene()->insertCamera( side_rcpair.camera.get() );
  side_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Top cam
  auto top_rcpair = createRCPair("Top");
  top_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( 0.0f, 0.0f, 50.0f ), -init_cam_up, init_cam_dir );
  top_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  scene()->insertCamera( top_rcpair.camera.get() );
  top_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );



  // Surface visualizers
  auto surface_visualizer = new GMlib::PSurfDefaultVisualizer<float,3>;

  // Surface
//  auto surface = new TestTorus;
//  surface->toggleDefaultVisualizer();
//  surface->insertVisualizer(surface_visualizer);
//  surface->replot(200,200,1,1);
//  scene()->insert(surface);

//  surface->test01();

//  auto sphere = new GMlib::PSphere<float>(4);
//    sphere->toggleDefaultVisualizer();
//    sphere->insertVisualizer(surface_visualizer);
//    sphere->replot(20,20,1,1);
//    sphere->setMaterial(GMlib::GMmaterial::sapphire());
//    scene()->insert(sphere);

   //Hexapod body

   auto body = new Cube( GMlib::Point<float,3>(0.0f,0.0f,0.0f) ,1,2,5);
   body->toggleDefaultVisualizer();
   body->replot(10,10,1,1);
   body->setMaterial(GMlib::GMmaterial::blackRubber());
   body->insert(scene()); // This line inserts cube to the scene; can't do scene()->insert(cube) because cube is not a scene object

   //Hexapod coxaL1

   auto coxaL1 = new Cube( GMlib::Point<float,3>(1.0f,0.0f,2.0f) ,0.5,0.5,0.5);
   coxaL1->toggleDefaultVisualizer();
   coxaL1->replot(10,10,1,1);
   coxaL1->setMaterial(GMlib::GMmaterial::sapphire());
   coxaL1->insert(scene()); // This line inserts cube to the scene; can't do scene()->insert(cube) because cube is not a scene object

   //Hexapod coxaL2

   auto coxaL2 = new Cube( GMlib::Point<float,3>(1.0f,0.0f,0.0f) ,0.5,0.5,0.5);
   coxaL2->toggleDefaultVisualizer();
   coxaL2->replot(10,10,1,1);
   coxaL2->setMaterial(GMlib::GMmaterial::sapphire());
   coxaL2->insert(scene()); // This line inserts cube to the scene; can't do scene()->insert(cube) because cube is not a scene object

   //Hexapod coxaL3

   auto coxaL3 = new Cube( GMlib::Point<float,3>(1.0f,0.0f,-2.0f) ,0.5,0.5,0.5);
   coxaL3->toggleDefaultVisualizer();
   coxaL3->replot(10,10,1,1);
   coxaL3->setMaterial(GMlib::GMmaterial::sapphire());
   coxaL3->insert(scene()); // This line inserts cube to the scene; can't do scene()->insert(cube) because cube is not a scene object

   //Hexapod coxaR1

   auto coxaR1 = new Cube( GMlib::Point<float,3>(-1.0f,0.0f,2.0f) ,0.5,0.5,0.5);
   coxaR1->toggleDefaultVisualizer();
   coxaR1->replot(10,10,1,1);
   coxaR1->setMaterial(GMlib::GMmaterial::sapphire());
   coxaR1->insert(scene()); // This line inserts cube to the scene; can't do scene()->insert(cube) because cube is not a scene object

   //Hexapod coxaR2

   auto coxaR2 = new Cube( GMlib::Point<float,3>(-1.0f,0.0f,0.0f) ,0.5,0.5,0.5);
   coxaR2->toggleDefaultVisualizer();
   coxaR2->replot(10,10,1,1);
   coxaR2->setMaterial(GMlib::GMmaterial::sapphire());
   coxaR2->insert(scene()); // This line inserts cube to the scene; can't do scene()->insert(cube) because cube is not a scene object

   //Hexapod coxaR3

   auto coxaR3 = new Cube( GMlib::Point<float,3>(-1.0f,0.0f,-2.0f) ,0.5,0.5,0.5);
   coxaR3->toggleDefaultVisualizer();
   coxaR3->replot(10,10,1,1);
   coxaR3->setMaterial(GMlib::GMmaterial::sapphire());
   coxaR3->insert(scene()); // This line inserts cube to the scene; can't do scene()->insert(cube) because cube is not a scene object


   //Hexapod fumurL1

   auto fumurL1 = new Cube( GMlib::Point<float,3>(2.25f,0.0f,2.0f) ,0.3,2.0,0.5);
   fumurL1->toggleDefaultVisualizer();
   fumurL1->replot(10,10,1,1);
   fumurL1->setMaterial(GMlib::GMmaterial::ruby());
   fumurL1->insert(scene()); // This line inserts cube to the scene; can't do scene()->insert(cube) because cube is not a scene object

   //Hexapod femurL2

   auto femurL2 = new Cube( GMlib::Point<float,3>(2.25f,0.0f,0.0f) ,0.3,2.0,0.5);
   femurL2->toggleDefaultVisualizer();
   femurL2->replot(10,10,1,1);
   femurL2->setMaterial(GMlib::GMmaterial::ruby());
   femurL2->insert(scene()); // This line inserts cube to the scene; can't do scene()->insert(cube) because cube is not a scene object

   //Hexapod femurL3

   auto femurL3 = new Cube( GMlib::Point<float,3>(2.25f,0.0f,-2.0f) ,0.3,2.0,0.5);
   femurL3->toggleDefaultVisualizer();
   femurL3->replot(10,10,1,1);
   femurL3->setMaterial(GMlib::GMmaterial::ruby());
   femurL3->insert(scene()); // This line inserts cube to the scene; can't do scene()->insert(cube) because cube is not a scene object

   //Hexapod femurR1

   auto femurR1 = new Cube( GMlib::Point<float,3>(-2.25f,0.0f,2.0f) ,0.3,2.0,0.5);
   femurR1->toggleDefaultVisualizer();
   femurR1->replot(10,10,1,1);
   femurR1->setMaterial(GMlib::GMmaterial::ruby());
   femurR1->insert(scene()); // This line inserts cube to the scene; can't do scene()->insert(cube) because cube is not a scene object

   //Hexapod femurR2

   auto femurR2 = new Cube( GMlib::Point<float,3>(-2.25f,0.0f,0.0f) ,0.3,2.0,0.5);
   femurR2->toggleDefaultVisualizer();
   femurR2->replot(10,10,1,1);
   femurR2->setMaterial(GMlib::GMmaterial::ruby());
   femurR2->insert(scene()); // This line inserts cube to the scene; can't do scene()->insert(cube) because cube is not a scene object

   //Hexapod femurR3

   auto femurR3 = new Cube( GMlib::Point<float,3>(-2.25f,0.0f,-2.0f) ,0.3,2.0,0.5);
   femurR3->toggleDefaultVisualizer();
   femurR3->replot(10,10,1,1);
   femurR3->setMaterial(GMlib::GMmaterial::ruby());
   femurR3->insert(scene()); // This line inserts cube to the scene; can't do scene()->insert(cube) because cube is not a scene object


     //Hexapod tibiaL1

     auto tibiaL1 = new Tibia(GMlib::Point<float,3>(4.75f,0.0f,0.0f));
     tibiaL1->toggleDefaultVisualizer();
     tibiaL1->replot(2, 5, 1, 1);                               // 4 vertex gives a pyramid shape
     tibiaL1->setMaterial(GMlib::GMmaterial::jade());
     tibiaL1->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f ) );
     tibiaL1->rotate( GMlib::Angle(45), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f ) );
     scene()->insert(tibiaL1);

     //Hexapod tibiaL2

     auto tibiaL2 = new Tibia(GMlib::Point<float,3>(4.75f,0.0f,2.0f));
     tibiaL2->toggleDefaultVisualizer();
     tibiaL2->replot(2, 5, 1, 1);                               // 4 vertex gives a pyramid shape
     tibiaL2->setMaterial(GMlib::GMmaterial::jade());
     tibiaL2->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f ) );
     tibiaL2->rotate( GMlib::Angle(45), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f ) );
     scene()->insert(tibiaL2);

     //Hexapod tibiaL3

     auto tibiaL3 = new Tibia(GMlib::Point<float,3>(4.75f,0.0f,-2.0f));
     tibiaL3->toggleDefaultVisualizer();
     tibiaL3->replot(2, 5, 1, 1);                               // 4 vertex gives a pyramid shape
     tibiaL3->setMaterial(GMlib::GMmaterial::jade());
     tibiaL3->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f ) );
     tibiaL3->rotate( GMlib::Angle(45), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f ) );
     scene()->insert(tibiaL3);

     //Hexapod tibiaR1

     auto tibiaR1 = new Tibia(GMlib::Point<float,3>(-4.75f,0.0f,0.0f));
     tibiaR1->toggleDefaultVisualizer();
     tibiaR1->replot(2, 5, 1, 1);                               // 4 vertex gives a pyramid shape
     tibiaR1->setMaterial(GMlib::GMmaterial::jade());
     tibiaR1->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, -1.0f, 0.0f ) );
     tibiaR1->rotate( GMlib::Angle(45), GMlib::Vector<float,3>(0.0f, 0.0f, -1.0f ) );
     scene()->insert(tibiaR1);

     //Hexapod tibiaR2

     auto tibiaR2 = new Tibia(GMlib::Point<float,3>(-4.75f,0.0f,2.0f));
     tibiaR2->toggleDefaultVisualizer();
     tibiaR2->replot(2, 5, 1, 1);                               // 4 vertex gives a pyramid shape
     tibiaR2->setMaterial(GMlib::GMmaterial::jade());
     tibiaR2->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, -1.0f, 0.0f ) );
     tibiaR2->rotate( GMlib::Angle(45), GMlib::Vector<float,3>(0.0f, 0.0f, -1.0f ) );
     scene()->insert(tibiaR2);

     //Hexapod tibiaR3

     auto tibiaR3 = new Tibia(GMlib::Point<float,3>(-4.75f,0.0f,-2.0f));
     tibiaR3->toggleDefaultVisualizer();
     tibiaR3->replot(2, 5, 1, 1);                               // 4 vertex gives a pyramid shape
     tibiaR3->setMaterial(GMlib::GMmaterial::jade());
     tibiaR3->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, -1.0f, 0.0f ) );
     tibiaR3->rotate( GMlib::Angle(45), GMlib::Vector<float,3>(0.0f, 0.0f, -1.0f ) );
     scene()->insert(tibiaR3);
}

void Scenario::cleanupScenario() {
}
