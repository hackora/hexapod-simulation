#include "scenario.h"
#include "hexapod.h"

#include "testtorus.h"

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

  auto hexapod = new Hexapod();

  hexapod->toggleDefaultVisualizer();
  hexapod->replot();
  hexapod->setMaterial(GMlib::GMmaterial::blackPlastic(),GMlib::GMmaterial::sapphire(),
                                   GMlib::GMmaterial::ruby(),GMlib::GMmaterial::blackRubber(),GMlib::GMmaterial::snow());
  hexapod->insert(scene());
  hexapod->getBody()->translate(GMlib::Vector<float,3>(5.0f,0.0f,0.0f));



//  auto joint0= new  GMlib::PSphere<float>();
//  joint0->toggleDefaultVisualizer();
//  joint0->replot(100  ,100,1,1);
//  scene()->insert(joint0);


//  auto shape1= new   GMlib::PCylinder<float>(1  ,1,6);
//  shape1->translate(GMlib::Vector<float,3>(0,0,3.3));
//  shape1->toggleDefaultVisualizer();
//  shape1->replot(100,100,   1,1);
//  joint0->insert(shape1);


//  auto joint1= new  GMlib::PSphere<float>();
//  joint1->translate(GMlib::Vector<float,3>(0,0,3.3));
//  joint1->toggleDefaultVisualizer();
//  joint1->replot(100  ,100,1,1);
//  shape1->insert(joint1);

//  auto shape2= new   GMlib::PCylinder<float>(1  ,1,6);
//  shape2->translate(GMlib::Vector<float,3>(0,0,3.3));
//  shape2->toggleDefaultVisualizer();
//  shape2->replot(100,100,   1,1);
//  joint1->insert(shape2);

//  auto joint2= new  GMlib::PSphere<float>();
//  joint2->translate(GMlib::Vector<float,3>(0,0,3.3));
//  joint2->toggleDefaultVisualizer();
//  joint2->replot(100  ,100,1,1);
//  shape2->insert(joint2);

//  joint1->rotate(GMlib::Angle(90),GMlib::Vector<float,3>(0,1,0));

// auto  gshape1Pos = shape1->getMatrixGlobal() * shape1->getPos();
// auto  gjoint2Pos = joint2->getMatrixGlobal() *  joint2->getPos();
// auto  gshape2Pos = shape2->getMatrixGlobal() * shape2->getPos();

// auto  nshape1Pos = shape1->getPos();
// auto  njoint2Pos =   joint2->getPos();
// auto  nshape2Pos = shape2->getPos();

}

void Scenario::cleanupScenario() {
}
