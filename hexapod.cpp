#include"hexapod.h"

Hexapod::Hexapod(GMlib::Point<float, 3> pos){

    makeBody(pos);
    makeCoxas();
    makeFemurs();
    makeTibias();
    makeJoints();
}

void Hexapod::makeBody(GMlib::Point<float, 3> pos){

    body = std::make_shared<GMlib::PCylinder<float>>(1,2.1,2);
}

void Hexapod::makeCoxas(){

    for(unsigned int i =0;i<6;i++){
        coxas.push_back( std::make_shared<GMlib::PCylinder<float>>(0.4f,0.4f,1.0f));
    }
}

void Hexapod::makeFemurs(){

    for(unsigned int i =0;i<6;i++){
        femurs.push_back( std::make_shared<GMlib::PCylinder<float>>(0.4f,0.4f,1.6f));
    }
}

void Hexapod::makeTibias(){

    for(unsigned int i =0;i<6;i++){
        tibias.push_back( std::make_shared<GMlib::PCone<float>>(0.2f,1.0f));
    }
}

void Hexapod::makeJoints(){

    for(unsigned int i =0;i<18;i++){
        joints.push_back( std::make_shared<GMlib::PSphere<float>>(0.4));
    }
}

void Hexapod::setMaterial(const GMlib::Material &bm,const GMlib::Material &cm,const GMlib::Material &fm,const GMlib::Material &tm,const GMlib::Material &jm){

    body->setMaterial(bm);

    for(unsigned int i= 0;i<joints.size();i++){
        joints[i]->setMaterial(jm);
    }

    for(unsigned int i= 0;i<6;i++){
        coxas[i]->setMaterial(cm);
        femurs[i]->setMaterial(fm);
        tibias[i]->setMaterial(tm);
    }
}

void Hexapod::replot(int m1, int m2, int d1, int d2){

    // Replot for body...
    body->replot(m1,m2,d1,d2);

    //... joints...
    for(unsigned int i= 0; i < joints.size(); i++){
        joints[i]->replot(m1,m2,d1,d2);
    }

    //  ... and legs
    for(unsigned int i= 0;i<6;i++){
        coxas[i]->replot(m1,m2,d1,d2);
        femurs[i]->replot(m1,m2,d1,d2);
        tibias[i]->replot(20,100,1,1);
    }
}

void Hexapod::toggleDefaultVisualizer(){

    // Toggle default visualizer for body...
    body->toggleDefaultVisualizer();

    // ... joints...
    for(unsigned int i= 0; i < joints.size(); i++) {
        joints[i]->toggleDefaultVisualizer();

    }

    // ... and legs
    for(unsigned int i= 0;i<6;i++){
        coxas[i]->toggleDefaultVisualizer();
        femurs[i]->toggleDefaultVisualizer();
        tibias[i]->toggleDefaultVisualizer();
    }

}

void Hexapod::insert(const std::shared_ptr<GMlib::Scene>&scene){

    adjustPositions();
    link();
    scene->insert(body.get());

}

void Hexapod::adjustPositions(){

    body ->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ) );
    body->rotate( GMlib::Angle(90), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f ) );
    body->rotateGlobal( GMlib::Angle(90), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f ));


    joints[0]->translate( GMlib::Vector<float,3>( 0.0f, 1.5f, 1.0f ) );
    joints[3]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ) );
    joints[6]->translate( GMlib::Vector<float,3>( 0.0f, -1.5f, 1.0f ) );
    joints[9]->translate( GMlib::Vector<float,3>( 0.0f, 1.5f, -1.0f ) );
    joints[12]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, -1.0f ) );
    joints[15]->translate( GMlib::Vector<float,3>( 0.0f,-1.5f, -1.0f ) );

    joints[1]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.5f ) );
    joints[4]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.5f ) );
    joints[7]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.5f ) );
    joints[10]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, -0.5f ) );
    joints[13]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, -0.5f ) );
    joints[16]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, -0.5f ) );

    joints[2]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.8f ) );
    joints[5]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.8f ) );
    joints[8]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.8f ) );
    joints[11]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, -0.8f ) );
    joints[14]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, -0.8f ) );
    joints[17]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, -0.8f ) );

    for(unsigned int i= 2; i <= 8; i += 3){
        joints[i]->rotate( GMlib::Angle(90), GMlib::Vector<float,3>(0.0f, -1.0f, 0.0f ) );
    }

    for(unsigned int i = 11; i < joints.size(); i += 3){
        joints[i]->rotate( GMlib::Angle(90), GMlib::Vector<float,3>(0.0f, 1.0f, 0.0f ) );
    }

    float angle = 45.0f;
    joints[0]->rotate( GMlib::Angle(-angle), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f));
    joints[6]->rotate( GMlib::Angle(angle), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f));
    joints[9]->rotate( GMlib::Angle(angle), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f));
    joints[15]->rotate( GMlib::Angle(-angle), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f));


    for(unsigned int i= 0;i<3;i++){
        coxas[i]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.5f ) );
        femurs[i]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 0.8f ));
        tibias[i]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ));
    }

    for(unsigned int i= 3;i<6;i++){
        coxas[i]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, -0.5f ) );
        femurs[i]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, -0.8f ));
        tibias[i]->translate( GMlib::Vector<float,3>( 0.0f, 0.0f, -1.0f ));
        tibias[i]->rotate( GMlib::Angle(180), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f ) );
    }
}

void Hexapod::link(){

    for(unsigned int i = 0; i <joints.size(); i+=3) {

        body->insert(joints[i].get());
    }

    for(unsigned int i = 0; i < 6; i++) {

        for( unsigned int j = 3*i; j <= 3*i + 2; j++) {

            if( j % 3 == 2) {
                femurs[i]->insert( joints[j].get() );
                joints[j]->insert( tibias[i].get() );
            }
            else if( j % 3 == 1) {
                coxas[i]->insert( joints[j].get() );
                joints[j]->insert( femurs[i].get() );

            }
            else joints[j]->insert( coxas[i].get() );
        }
    }

}
