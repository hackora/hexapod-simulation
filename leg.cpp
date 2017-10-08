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
    auto joint0= joints[0]->getPos();
    this->translate(GMlib::Vector<float,3>(joint0(0),joint0(1),joint0(2)));

    update_tip_position();

    for(unsigned int i = 0; i<3;i++){

        auto x = new GMlib::PLine<float>(GMlib::Point<float, 3> (0.0,0.0,0.0),GMlib::Point<float, 3> (0.8,0.0,0.0));
        x->translate(GMlib::Vector<float,3>(0.0,0.0,0.0));
        x->toggleDefaultVisualizer();
        x->replot(10,1);
        x->setColor(GMlib::GMcolor::red());
        joints[i]->insert(x);

        auto y = new GMlib::PLine<float>(GMlib::Point<float, 3> (0.0,0.0,0.0),GMlib::Point<float, 3> (0.0,0.8,0.0));
        y->translate(GMlib::Vector<float,3>(0.0,0.0,0.0));
        y->toggleDefaultVisualizer();
        y->replot(10,1);
        y->setColor(GMlib::GMcolor::green());
         joints[i]->insert(y);

        auto z = new GMlib::PLine<float>(GMlib::Point<float, 3> (0.0,0.0,0.0),GMlib::Point<float, 3> (0.0,0.0,0.8));
        z->translate(GMlib::Vector<float,3>(0.0,0.0,0.0));
        z->toggleDefaultVisualizer();
        z->replot(10,1);
        z->setColor(GMlib::GMcolor::blue());
         joints[i]->insert(z);
    }

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

        if(right){
            joints[0]->rotate( GMlib::Angle(90), GMlib::Vector<float,3>(0.0f, 1.0f, 0.0f ) );
            joints[0]->rotate( GMlib::Angle(180), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f ) );
            coxa->rotate(GMlib::Angle(90), GMlib::Vector<float,3>(0.0f, 1.0f, 0.0f ));
            joints[1]->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 1.0f, 0.0f,0.0f ) );
            joints[1]->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 0.0f,1.0f ) );
            joints[2]->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 1.0f,0.0f ) );

            // Joint between Coxas and Femur
            joints[1]->translate( GMlib::Vector<float,3>(0.5f, 0.0f, 0.0f ) );
            femur->rotate( GMlib::Angle(-90), GMlib::Vector<float,3>( 0.0f, 1.0f,0.0f ) );
            tibia->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 1.0f,0.0f ) );

            // Joint between Femur and Tibia
            joints[2]->translate( GMlib::Vector<float,3>(0.8f, 0.0f, 0.0f ) );

            // Rotate Tibia joint - pointing down
            joints[2]->rotate( GMlib::Angle(-90), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f ) );

            coxa->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.5f ) );
            femur->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, -0.8f ));
            tibia->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ));
        }

            if(!right) {

                joints[0]->rotate( GMlib::Angle(90), GMlib::Vector<float,3>(0.0f, 1.0f, 0.0f ) );
                joints[0]->translate( GMlib::Vector<float,3>( 2.0f, 0.0f, 0.0f ) );
                coxa->rotate(GMlib::Angle(90), GMlib::Vector<float,3>(0.0f, 1.0f, 0.0f ));
                joints[1]->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 1.0f, 0.0f,0.0f ) );
                joints[1]->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 0.0f,1.0f ) );
                joints[2]->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 1.0f,0.0f ) );

                // Joint between Coxas and Femur
                joints[1]->translate( GMlib::Vector<float,3>(0.5f, 0.0f, 0.0f ) );
                femur->rotate( GMlib::Angle(-90), GMlib::Vector<float,3>( 0.0f, 1.0f,0.0f ) );
                tibia->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 1.0f,0.0f ) );

                // Joint between Femur and Tibia
                joints[2]->translate( GMlib::Vector<float,3>(0.8f, 0.0f, 0.0f ) );

                // Rotate Tibia joint - pointing down
                joints[2]->rotate( GMlib::Angle(-90), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f ) );

                coxa->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.5f ) );
                femur->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, -0.8f ));
                tibia->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ));
            }

//        if(!right) {

//            joints[0]->rotate( GMlib::Angle(90), GMlib::Vector<float,3>(0.0f, 1.0f, 0.0f ) );
//            joints[0]->rotate( GMlib::Angle(90), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f ) );

//            joints[0]->translate( GMlib::Vector<float,3>( 0.0f, -2.0f, 0.0f ) );

//            coxa->rotate(GMlib::Angle(90), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f ));
//            // Joint between Coxas and Femur
//            joints[1]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.5f ) );

//            // Joint between Femur and Tibia
//            joints[2]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.8f ) );

//            // Rotate Tibia joint - pointing down
//            joints[2]->rotate( GMlib::Angle(90), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f ) );

//            coxa->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.5f ) );
//            femur->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.8f ));
//            tibia->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ));

//        }
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

IKAngles Leg::inverseKinematics(GMlib::Point<float, 3> targetPosition){

    auto coxaHeight = coxa->getHeight();
    auto femurHeight = femur->getHeight();
    auto tibiaHeight = tibia->getHeight()*2;
    auto z0 =  targetPosition(2) ;
    auto l1= std::sqrt((targetPosition(0)) * (targetPosition(0)) + (targetPosition(1)) * (targetPosition(1)) );
    auto r= l1-coxaHeight;
    auto l = z0 *z0  +  r*r;

    auto coxaAngle = std::atan2(targetPosition(1),targetPosition(0));
    auto tibiaAngle =  1.5708- std::acos((l-femurHeight*femurHeight-tibiaHeight*tibiaHeight)/(2*femurHeight*tibiaHeight));
//    if(tibiaAngle <=-2 || tibiaAngle>=2)
//        tibiaAngle = 1.5708- tibiaAngle;
    auto femurAngle = std::atan2(r,z0)-std::atan2(femurHeight+tibiaHeight*std::cos(tibiaAngle), tibiaHeight* std::sin(tibiaAngle) );

    auto angles = IKAngles(coxaAngle, femurAngle, tibiaAngle);
    return angles;
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

void Leg::update_tip_position(){
    auto tibia_pos = this->getTibia()->getPos();
    auto femur_matrix = this->getFemur()->getMatrix() ;
    auto femur_global = this->getFemur()->getGlobalPos();
    auto joint1_global = this->getJoints()[1]->getGlobalPos();
    auto endEffector_pos = GMlib::Point<float,3>(tibia_pos(0)+1,tibia_pos(1),tibia_pos(2));
    GMlib::APoint<float,4> endEffector_basePos =  this->getCoxa()->getMatrix()*
            (this->getJoints()[1]->getMatrix()*  ( this->getFemur()->getMatrix() *
            (this->getJoints()[2]->getMatrix()* (endEffector_pos))));
    tip_pos = endEffector_basePos;
}

void Leg::localSimulate(double dt){

}
