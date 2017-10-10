#include "scenario.h"
#include "simulator.h"
#include "hexapod.h"

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



//  auto g= new GMlib::PSphere<float>(0.2);

//  g->toggleDefaultVisualizer();
//  g->setMaterial(GMlib::GMmaterial::polishedBronze());
//  g->translate( GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
////  g->translate(GMlib::Vector<float,3>(0.0f,1.5f,0.0f));


//  auto x = new GMlib::PLine<float>(GMlib::Point<float, 3> (0.0,0.0,0.0),GMlib::Point<float, 3> (0.8,0.0,0.0));
//  x->translate(GMlib::Vector<float,3>(0.0,0.0,0.0));
//  x->toggleDefaultVisualizer();
//  x->replot(10,1);
//  x->setColor(GMlib::GMcolor::red());
//  g->insert(x);

//  auto y = new GMlib::PLine<float>(GMlib::Point<float, 3> (0.0,0.0,0.0),GMlib::Point<float, 3> (0.0,0.8,0.0));
//  y->translate(GMlib::Vector<float,3>(0.0,0.0,0.0));
//  y->toggleDefaultVisualizer();
//  y->replot(10,1);
//  y->setColor(GMlib::GMcolor::green());
//  g->insert(y);

//  auto z = new GMlib::PLine<float>(GMlib::Point<float, 3> (0.0,0.0,0.0),GMlib::Point<float, 3> (0.0,0.0,0.8));
//  z->translate(GMlib::Vector<float,3>(0.0,0.0,0.0));
//  z->toggleDefaultVisualizer();
//  z->replot(10,1);
//  z->setColor(GMlib::GMcolor::blue());
//   g->insert(z);

//  g->translate(GMlib::Vector<float,3>(1.83848f,1.83848f,-2.0f));

//  g->replot(10  ,10,1,1);
//  scene()->insert(g);
  _simulator = std::make_shared<Simulator>(*scene());
  _simulator->setupSimulator();

}

void Scenario::cleanupScenario() {
    _simulator.reset();
}
