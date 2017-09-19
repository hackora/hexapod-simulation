#include "leg.h"



Leg::Leg(GMlib::Point<float, 3> pos, bool orientation)
{
    makeJoints();
    makeCoxa();
    makeFemur();
    makeTibia();

    right = orientation;
    adjustPositions();
    link();


}

void Leg::setMaterial(const GMlib::Material &cm, const GMlib::Material &fm, const GMlib::Material &tm, const GMlib::Material &jm)
{
    for(unsigned int i= 0;i<joints.size();i++){
        joints[i]->setMaterial(jm);
    }
    coxa->setMaterial(cm);
    femur->setMaterial(fm);
    tibia->setMaterial(tm);

}

void Leg::replot(int m1, int m2, int d1, int d2)
{

    //... joints...
    for(unsigned int i= 0; i < joints.size(); i++){
        joints[i]->replot(m1,m2,d1,d2);
    }

    //  ... and legs
    coxa->replot(m1,m2,d1,d2);
    femur->replot(m1,m2,d1,d2);
    tibia->replot(20,100,1,1);

}

void Leg::toggleDefaultVisualizer()
{
    // ... joints...
    for(unsigned int i= 0; i < joints.size(); i++) {
        joints[i]->toggleDefaultVisualizer();

    }
    coxa->toggleDefaultVisualizer();
    femur->toggleDefaultVisualizer();
    tibia->toggleDefaultVisualizer();


}



void Leg::makeCoxa()
{
    coxa = std::make_shared<GMlib::PCylinder<float>>(0.4f,0.4f,1.0f);
}

void Leg::makeFemur()
{
    femur = std::make_shared<GMlib::PCylinder<float>>(0.4f,0.4f,1.6f);

}

void Leg::makeTibia()
{
    tibia = std::make_shared<Tibia>(0.2f,1.0f);
}

void Leg::makeJoints()
{
    for(unsigned int i =0;i<3;i++){
        joints.push_back( std::make_shared<GMlib::PSphere<float>>(0.4));
    }
}

void Leg::adjustPositions()
{

        // Joint between Body and Coxas
        joints[0]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ) );

        // Joint between Coxas and Femur
        joints[1]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.5f ) );

        // Joint between Femur and Tibia
        joints[2]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.8f ) );

        // Rotate Tibia joint - pointing down
        joints[2]->rotate( GMlib::Angle(90), GMlib::Vector<float,3>(0.0f, -1.0f, 0.0f ) );

        coxa->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.5f ) );
        femur->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.8f ));
        tibia->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ));

        if(!right) {

            joints[0]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, -2.0f ) );
            joints[0]->rotate( GMlib::Angle(180), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f ) );

        }
}

void Leg::link()
{

    for( unsigned int j = 0; j <= 2; j++) {

        if( j % 3 == 2) {
            femur->insert( joints[j].get() );
            joints[j]->insert( tibia.get() );
        }
        else if( j % 3 == 1) {
            coxa->insert( joints[j].get() );
            joints[j]->insert( femur.get() );

        }
        else joints[j]->insert( coxa.get() );
    }
}

// Don't need old position, but can be useful to keep for checking distance, too big distance is bad.
// But if dt is small enough, the movements are small enough that they might be fine
// Need to validate the angles, to make sure they are valid
// Add newDirection vector, as the direction of the leg needs to be valid
// Børre suggest generalizing the names of alpha, beta, gamma

Angles Leg::inverseKinematics(GMlib::Point<float, 3> oldPos, GMlib::Point<float, 3> newPos)
{
    auto legLength = std::sqrt( std::pow( (newPos(0) - joints[0]->getPos()(0)), 2) + std::pow( (newPos(2) - joints[0]->getPos()(2)), 2) );
    auto L = std::sqrt( std::pow( legLength - coxa->getHeight(),2 ) + std::pow( (newPos(1) - joints[0]->getPos()(1)), 2)  );

    auto beta1 = std::atan2( (legLength - coxa->getHeight()),(newPos(1) - joints[0]->getPos()(1)) );
    auto beta2 = std::acos( (legLength*legLength - femur->getHeight()*femur->getHeight() - L*L) / (-2 * femur->getHeight() * L) );
    auto tibiaAngle = 90 - beta1 - beta2;   // Beta

    // Gamma
    auto tibiaHeight = tibia->getHeight();
    auto femurHeight = femur->getHeight();

    auto coxaAngle = 90 - std::acos(  (legLength*legLength -  tibiaHeight * tibiaHeight - femurHeight* femurHeight)/(-2 * tibiaHeight*femurHeight) );

    // Alpha
    auto femurAngle = std::atan2( (newPos(2) - joints[0]->getPos()(2)) , (newPos(0) - joints[0]->getPos()(0)) );

    auto angle = Angles(femurAngle, tibiaAngle, coxaAngle);
    return angle;

}

std::vector<std::shared_ptr<GMlib::PSphere<float> > > Leg::getJoints()
{
    return joints;
}


std::shared_ptr<GMlib::PCylinder<float> > Leg::getCoxa()
{
    return coxa;
}


std::shared_ptr<GMlib::PCylinder<float> > Leg::getFemur()
{
    return femur;
}


std::shared_ptr<Tibia >  Leg::getTibia()
{
    return tibia;
}
