#include "scenario.h"

#include "testtorus.h"

#include<collision_library.h>
#include "simulator.h"

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



  //box

  auto b = 2.0f;
  auto w = 1.0f;
  auto h = 5.0f;
  auto com = GMlib::Point<float,3>(0.0f, 0.0f, 0.0f);

     auto plane1 =new Plane(
                com+ GMlib::Vector<float,3>(0.5*b, 0.5*w, -0.5*h),
                 GMlib::Vector<float,3>(0.0f, -w, 0.0f),
                 GMlib::Vector<float,3>(-b, 0.0f, 0.0f));

     plane1->setMaterial(GMlib::GMmaterial::sapphire());

     auto plane2 =new Plane(
                 com+ GMlib::Vector<float,3>(0.5*b, 0.5*w, 0.5*h),
                 GMlib::Vector<float,3>(0.0f, -w, 0.0f),
                 GMlib::Vector<float,3>(-b, 0.0f, 0.0f));

      plane2->setMaterial(GMlib::GMmaterial::sapphire());

      auto plane3 =new Plane(
                  com+ GMlib::Vector<float,3>(0.5*b, 0.5*w, -0.5*h),
                  GMlib::Vector<float,3>(0.0f, -w, 0.0f),
                  GMlib::Vector<float,3>(0.0, 0.0f, h));

      plane3->setMaterial(GMlib::GMmaterial::sapphire());

      auto plane4 =new Plane(
                 com + GMlib::Vector<float,3>(0.5*b, 0.5*w, -0.5*h),
                  GMlib::Vector<float,3>(-b, 0.0f, 0.0f),
                  GMlib::Vector<float,3>(0.0f, 0.0f, h));

      plane4->setMaterial(GMlib::GMmaterial::sapphire());

      auto plane5 = new Plane (
                 com+ GMlib::Vector<float,3>(-0.5*b, -0.5*w, -0.5*h),
                  GMlib::Vector<float,3>(0.0f,w, 0.0f),
                  GMlib::Vector<float,3>(0.0f, 0.0f, h));

      plane5->setMaterial(GMlib::GMmaterial::sapphire());

      auto plane6 = new Plane (
                  com +GMlib::Vector<float,3>(-0.5*b, -0.5*w, -0.5*h),
                  GMlib::Vector<float,3>(b, 0.0f, 0.0f),
                  GMlib::Vector<float,3>(0.0f, 0.0f, h));

      plane6->setMaterial(GMlib::GMmaterial::sapphire());


      plane1->toggleDefaultVisualizer();
      plane1->replot(10,10,1,1);
      scene()->insert(plane1);

      plane2->toggleDefaultVisualizer();
      plane2->replot(10,10,1,1);
      scene()->insert(plane2);

      plane3->toggleDefaultVisualizer();
      plane3->replot(10,10,1,1);
      scene()->insert(plane3);

      plane4->toggleDefaultVisualizer();
      plane4->replot(10,10,1,1);
      scene()->insert(plane4);

      plane5->toggleDefaultVisualizer();
      plane5->replot(10,10,1,1);
      scene()->insert(plane5);

      plane6->toggleDefaultVisualizer();
      plane6->replot(10,10,1,1);
      scene()->insert(plane6);

  //Leg5

    auto joint51 = new GMlib::PSphere<float>(1);
      joint51->toggleDefaultVisualizer();
      joint51->replot(20,20,1,1);
      joint51->translateGlobal(GMlib::Vector<float,3>{5.0f,0.0f,0.0f});
      joint51->setMaterial(GMlib::GMmaterial::emerald());
      scene()->insert(joint51);

   auto coxa5 = new GMlib::PLine<float>(GMlib::Point<float,3>(6.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>(2.0f, 0.0f, 0.0f ));
   coxa5->toggleDefaultVisualizer();
   coxa5->replot(10,10);
   coxa5->setMaterial(GMlib::GMmaterial::ruby());
   scene()->insert(coxa5);

   auto joint52 = new GMlib::PSphere<float>(1);
     joint52->toggleDefaultVisualizer();
     joint52->replot(20,20,1,1);
     joint52->translateGlobal(GMlib::Vector<float,3>{9.0f,0.0f,0.0f});
     joint52->setMaterial(GMlib::GMmaterial::emerald());
     scene()->insert(joint52);

   auto femur5 = new GMlib::PLine<float>(GMlib::Point<float,3>(10.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>(2.0f, 0.0f, 0.0f ));
   femur5->toggleDefaultVisualizer();
   femur5->replot(10,10);
   femur5->setMaterial(GMlib::GMmaterial::ruby());
   scene()->insert(femur5);

   auto joint53 = new GMlib::PSphere<float>(1);
     joint53->toggleDefaultVisualizer();
     joint53->replot(20,20,1,1);
     joint53->translateGlobal(GMlib::Vector<float,3>{13.0f,0.0f,0.0f});
     joint53->setMaterial(GMlib::GMmaterial::emerald());
     scene()->insert(joint53);

   auto tibia5 = new GMlib::PLine<float>(GMlib::Point<float,3>(14.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>(2.0f, 0.0f, 0.0f ));
   tibia5->toggleDefaultVisualizer();
   tibia5->replot(10,10);
   tibia5->setMaterial(GMlib::GMmaterial::ruby());
   scene()->insert(tibia5);


   //Leg2

//     auto joint21 = new GMlib::PSphere<float>(1);
//       joint21->toggleDefaultVisualizer();
//       joint21->replot(20,20,1,1);
//       joint21->translateGlobal(GMlib::Vector<float,3>{-5.0f,0.0f,0.0f});
//       joint21->setMaterial(GMlib::GMmaterial::emerald());
//       scene()->insert(joint21);

//    auto coxa2 = new GMlib::PLine<float>(GMlib::Point<float,3>(-6.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>(-2.0f, 0.0f, 0.0f ));
//    coxa2->toggleDefaultVisualizer();
//    coxa2->replot(10,10);
//    coxa2->setMaterial(GMlib::GMmaterial::ruby());
//    scene()->insert(coxa2);

//    auto joint22 = new GMlib::PSphere<float>(1);
//      joint22->toggleDefaultVisualizer();
//      joint22->replot(20,20,1,1);
//      joint22->translateGlobal(GMlib::Vector<float,3>{-9.0f,0.0f,0.0f});
//      joint22->setMaterial(GMlib::GMmaterial::emerald());
//      scene()->insert(joint22);

//    auto femur2 = new GMlib::PLine<float>(GMlib::Point<float,3>(-10.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>(-2.0f, 0.0f, 0.0f ));
//    femur2->toggleDefaultVisualizer();
//    femur2->replot(10,10);
//    femur2->setMaterial(GMlib::GMmaterial::ruby());
//    scene()->insert(femur2);

//    auto joint23 = new GMlib::PSphere<float>(1);
//      joint23->toggleDefaultVisualizer();
//      joint23->replot(20,20,1,1);
//      joint23->translateGlobal(GMlib::Vector<float,3>{-13.0f,0.0f,0.0f});
//      joint23->setMaterial(GMlib::GMmaterial::emerald());
//      scene()->insert(joint23);

//    auto tibia2 = new GMlib::PLine<float>(GMlib::Point<float,3>(-14.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>(-2.0f, 0.0f, 0.0f ));
//    tibia2->toggleDefaultVisualizer();
//    tibia2->replot(10,10);
//    tibia2->setMaterial(GMlib::GMmaterial::ruby());
//    scene()->insert(tibia2);


    //Leg4

//      auto joint41 = new GMlib::PSphere<float>(1);
//        joint41->toggleDefaultVisualizer();
//        joint41->replot(20,20,1,1);
//        joint41->translateGlobal(GMlib::Vector<float,3>{4.0f,3.0f,0.0f});
//        joint41->setMaterial(GMlib::GMmaterial::emerald());
//        scene()->insert(joint41);

//     auto coxa5 = new GMlib::PLine<float>(GMlib::Point<float,3>(6.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>(2.0f, 0.0f, 0.0f ));
//     coxa5->toggleDefaultVisualizer();
//     coxa5->replot(10,10);
//     coxa5->setMaterial(GMlib::GMmaterial::ruby());
//     scene()->insert(coxa5);

//     auto joint52 = new GMlib::PSphere<float>(1);
//       joint52->toggleDefaultVisualizer();
//       joint52->replot(20,20,1,1);
//       joint52->translateGlobal(GMlib::Vector<float,3>{9.0f,0.0f,0.0f});
//       joint52->setMaterial(GMlib::GMmaterial::emerald());
//       scene()->insert(joint52);

//     auto femur5 = new GMlib::PLine<float>(GMlib::Point<float,3>(10.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>(2.0f, 0.0f, 0.0f ));
//     femur5->toggleDefaultVisualizer();
//     femur5->replot(10,10);
//     femur5->setMaterial(GMlib::GMmaterial::ruby());
//     scene()->insert(femur5);

//     auto joint53 = new GMlib::PSphere<float>(1);
//       joint53->toggleDefaultVisualizer();
//       joint53->replot(20,20,1,1);
//       joint53->translateGlobal(GMlib::Vector<float,3>{13.0f,0.0f,0.0f});
//       joint53->setMaterial(GMlib::GMmaterial::emerald());
//       scene()->insert(joint53);

//     auto tibia5 = new GMlib::PLine<float>(GMlib::Point<float,3>(14.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>(2.0f, 0.0f, 0.0f ));
//     tibia5->toggleDefaultVisualizer();
//     tibia5->replot(10,10);
//     tibia5->setMaterial(GMlib::GMmaterial::ruby());
//     scene()->insert(tibia5);


}

void Scenario::cleanupScenario() {

}
