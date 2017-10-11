#include"hexapod.h"
#include <cmath>

Hexapod::Hexapod(GMlib::Point<float, 3> pos){

    makeBody(pos);
//    body->setVisible(false);
    makeLegs(pos);


//    //body frame
//    auto x = new GMlib::PLine<float>(GMlib::Point<float, 3> (0.0,0.0,0.0),GMlib::Point<float, 3> (0.8,0.0,0.0));
//    x->translate(GMlib::Vector<float,3>(0.0,0.0,0.0));
//    x->toggleDefaultVisualizer();
//    x->replot(10,1);
//    x->setColor(GMlib::GMcolor::red());
//    body->insert(x);

//    auto y = new GMlib::PLine<float>(GMlib::Point<float, 3> (0.0,0.0,0.0),GMlib::Point<float, 3> (0.0,0.8,0.0));
//    y->translate(GMlib::Vector<float,3>(0.0,0.0,0.0));
//    y->toggleDefaultVisualizer();
//    y->replot(10,1);
//    y->setColor(GMlib::GMcolor::green());
//    body->insert(y);

//    auto z = new GMlib::PLine<float>(GMlib::Point<float, 3> (0.0,0.0,0.0),GMlib::Point<float, 3> (0.0,0.0,0.8));
//    z->translate(GMlib::Vector<float,3>(0.0,0.0,0.0));
//    z->toggleDefaultVisualizer();
//    z->replot(10,1);
//    z->setColor(GMlib::GMcolor::blue());
//    body->insert(z);

}

void Hexapod::makeBody(GMlib::Point<float, 3> pos){

    body = std::make_shared<GMlib::PCylinder<float>>(1,2.1,2);
}

void Hexapod::makeLegs(GMlib::Point<float, 3> pos) {

    for(unsigned int i = 0; i < 3; i++)  legs.push_back(std::make_shared<Leg> (pos, true));
    for(unsigned int j = 0; j < 3; j++)  legs.push_back(std::make_shared<Leg> (pos, false));
}

void Hexapod::setMaterial(const GMlib::Material &bm,const GMlib::Material &cm,const GMlib::Material &fm,const GMlib::Material &tm,const GMlib::Material &jm){

    body->setMaterial(bm);

    for(unsigned int i = 0; i < legs.size(); i++) {
        legs[i]->setMaterial(cm, fm, tm, jm);
    }
}

void Hexapod::replot(int m1, int m2, int d1, int d2){

    // Replot for body...
    body->replot(m1,m2,d1,d2);

    for(unsigned int i = 0; i < legs.size(); i++) {
        legs[i]->replot(m1,m2,d1,d2);
    }
}

void Hexapod::toggleDefaultVisualizer(){

    // Toggle default visualizer for body...
    body->toggleDefaultVisualizer();

    for(unsigned int i = 0; i < legs.size(); i++) {
        legs[i]->toggleDefaultVisualizer();
    }
}

void Hexapod::insert(GMlib::Scene &scene){

    adjustPositions();
    link();
    scene.insert(body.get());

//    for(unsigned int i=0;i<legs.size();i++){
//        legs[i]->insert(scene);
//    }
//    scene.insert(this);
}

void Hexapod::adjustPositions(){

    body ->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ) );
    body->rotate( GMlib::Angle(90), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f ) );
    body->rotateGlobal( GMlib::Angle(90), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f ));


    // Moving right legs into position
    legs[0]->getJoints()[0].get()->translate( GMlib::Vector<float,3>(0.0f, 1.5f, 0.0f));
    legs[2]->getJoints()[0].get()->translate( GMlib::Vector<float,3>(0.0f, -1.5f, 0.0f));


    // Moving left legs into position
    legs[3]->getJoints()[0].get()->translate( GMlib::Vector<float,3>(0.0f, -1.5, 0.0f));
    legs[5]->getJoints()[0].get()->translate( GMlib::Vector<float,3>(0.0f, 1.5f, 0.0f));


    // Make the legs point, relaxed position
    legs[0]->getJoints()[0].get()->rotate( GMlib::Angle(45), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
    legs[2]->getJoints()[0].get()->rotate( GMlib::Angle(-45), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
    legs[3]->getJoints()[0].get()->rotate( GMlib::Angle(-45), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
    legs[5]->getJoints()[0].get()->rotate( GMlib::Angle(45), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

    //adjust leg_bases
    legs[0]->leg_base->translate(GMlib::Vector<float,3>(0.0f,1.5f,0.0f));
    legs[2]->leg_base->translate( GMlib::Vector<float,3>(0.0f, -1.5f, 0.0f));
    legs[3]->leg_base->translate( GMlib::Vector<float,3>(0.0f, -1.5, 0.0f));
    legs[5]->leg_base->translate( GMlib::Vector<float,3>(0.0f, 1.5f, 0.0f));
}

void Hexapod::link(){

    for(unsigned int i = 0; i <legs.size(); i++) {

        body->insert(legs[i]->getJoints()[0].get());
        body->insert((legs[i]->leg_base).get());
    }

}

void Hexapod::moveForward(double dt){

//    auto tibia_pos = legs[1]->getTibia()->getPos();
//    auto endEffector_pos = GMlib::Point<float,3>(tibia_pos(0)+1,tibia_pos(1),tibia_pos(2));
//    auto endEffector_basePos =  legs[1]->getCoxa()->getMatrix()*
//            legs[1]->getJoints()[1]->getMatrix()*  legs[1]->getFemur()->getMatrix() *
//            legs[1]->getJoints()[2]->getMatrix()* endEffector_pos;

//    auto targetPos =   GMlib::Point<float,3>(3.6,0.0,0.0);  //choose a target position for the endEffector of leg1 to reach

//    auto angles = legs[1]->inverseKinematics(targetPos);

//    auto coxaAngle =  angles.coxaAngle;
//    auto femurAngle = angles.femurAngle;
//    auto tibiaAngle = angles.tibiaAngle;

//    GMlib::Angle angle1= (legs[1]->getJoints()[1]->getGlobalDir())
//            .getAngle(legs[1]->getJoints()[0]->getGlobalDir());
//    GMlib::Angle angle2=  (legs[1]->getJoints()[2]->getGlobalDir())
//            .getAngle(legs[1]->getJoints()[1]->getGlobalDir());


    //        auto goalMark = new GMlib::PSphere<float>(0.1);
    //        goalMark->toggleDefaultVisualizer();
    //        goalMark->replot(10,10,1,1);
    //        goalMark->setMaterial(GMlib::GMmaterial::emerald());
    //        base->insert(goalMark);
    //        goalMark->translate(targetPos);

    //        legs[1]->getJoints()[0]->rotate(coxaAngle,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

    //        legs[1]->getJoints()[1]->rotate(-femurAngle+angle1 , GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

    //        legs[1]->getJoints()[2]->rotate(tibiaAngle+angle2,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

}
void Hexapod::localSimulate(double dt){

//    moveForward(dt);

}
