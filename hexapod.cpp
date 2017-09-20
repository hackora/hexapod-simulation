#include"hexapod.h"

Hexapod::Hexapod(GMlib::Point<float, 3> pos){

    makeBody(pos);
    body->setVisible(false);
    makeLegs(pos);
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

void Hexapod::insert(const std::shared_ptr<GMlib::Scene>&scene){

    adjustPositions();
    link();
    scene->insert(body.get());
    scene->insert(this);

}

void Hexapod::adjustPositions(){

    body ->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ) );
    body->rotate( GMlib::Angle(90), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f ) );
    body->rotateGlobal( GMlib::Angle(90), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f ));


    // Moving right legs into position
    legs[0]->getJoints()[0].get()->translateGlobal( GMlib::Vector<float,3>(0.0f, 1.5f, 0.0f));
    legs[2]->getJoints()[0].get()->translateGlobal( GMlib::Vector<float,3>(0.0f, -1.5f, 0.0f));


    // Moving left legs into position
    legs[3]->getJoints()[0].get()->translateGlobal( GMlib::Vector<float,3>(0.0f, 1.5f, 0.0f));
    legs[5]->getJoints()[0].get()->translateGlobal( GMlib::Vector<float,3>(0.0f, -1.5f, 0.0f));


    // Make the legs point, relaxed position
        legs[0]->getJoints()[0].get()->rotate( GMlib::Angle(-45), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f));
        legs[2]->getJoints()[0].get()->rotate( GMlib::Angle(45), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f));
        legs[3]->getJoints()[0].get()->rotate( GMlib::Angle(45), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f));
        legs[5]->getJoints()[0].get()->rotate( GMlib::Angle(-45), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f));


}

void Hexapod::link(){

    for(unsigned int i = 0; i <legs.size(); i++) {

        body->insert(legs[i]->getJoints()[0].get());
    }

}

void Hexapod::forward(double dt){

//    while(std::abs(joints[leg]->getSide()* body->getSide()) > std::cos(45) ){

//        if(leg <= 6) joints[leg]->rotate(GMlib::Angle(dt), GMlib::Vector<float,3>(-1.0f, 0.0f, 0.0f));
//        else if(leg >= 6) joints[leg]->rotate(GMlib::Angle(dt), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f));

//        }

//    if(leg <= 6) joints[leg]->rotate (GMlib::Angle(-45), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f));
//    else if(leg >= 6) joints[leg]->rotate (GMlib::Angle(45), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f));



//    joints[0]->rotate( GMlib::Angle(-45), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f));
//    joints[9]->rotate( GMlib::Angle(45), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f));

    auto oldPos =  legs[1]->getTibia()->getPos();
    auto endpoint = GMlib::Point<float,3>(oldPos(0),oldPos(1),oldPos(2) + 0.5); //half the tibia height
    auto gEndpoint = legs[1]->getTibia()->getMatrixGlobal() * endpoint;

    auto targetPos =  GMlib::Point<float,3>(endpoint(0),dt,endpoint(2));

    auto angles = legs[1]->inverseKinematics(targetPos);

    legs[1]->getJoints()[0]->rotate(angles.alpha,GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f));
    legs[1]->getJoints()[1]->rotate(angles.beta,GMlib::Vector<float,3>(0.0f, 1.0f, 0.0f));
    legs[1]->getJoints()[2]->rotate(angles.gamma,GMlib::Vector<float,3>(0.0f, 1.0f, 0.0f));

     auto test1 =  legs[1]->getTibia()->getMatrixGlobal() * legs[1]->getTibia()->getPos();

//      legs[3]->getJoints()[0]->rotateGlabal(angles.alpha,GMlib::Vector<float,3>(0.0, 0.0f, 1.0f));
//      legs[3]->getJoints()[1]->rotateGlobal(angles.beta,GMlib::Vector<float,3>(0.0, 1.0f, 0.0f));
//      legs[3]->getJoints()[2]->rotateGlobal(angles.gamma,GMlib::Vector<float,3>(0.0, 1.0f, 0.0f));

}

void Hexapod::localSimulate(double dt){

    forward(dt);
}


