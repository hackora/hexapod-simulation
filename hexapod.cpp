#include"hexapod.h"

Hexapod::Hexapod(GMlib::Point<float, 3> pos){
    makeBody(pos);
    makeCoxas(pos);
    makeFemurs(pos);
    makeTibias(pos);
}

void Hexapod::makeBody(GMlib::Point<float, 3> pos){

    body = std::make_shared< Cube>( pos,1,2,5);
}

void Hexapod::makeCoxas(GMlib::Point<float, 3> pos){ //TODO: use pos later to figure out position

    //Hexapod coxaR1

    coxas.push_back( std::make_shared<Cube>( GMlib::Point<float,3>(1.0f,0.0f,2.0f) ,0.5,0.5,0.5));

    //Hexapod coxaR2

    coxas.push_back(std::make_shared<Cube>( GMlib::Point<float,3>(1.0f,0.0f,0.0f) ,0.5,0.5,0.5));

    //Hexapod coxaR3

    coxas.push_back(std::make_shared<Cube>( GMlib::Point<float,3>(1.0f,0.0f,-2.0f) ,0.5,0.5,0.5));

    //Hexapod coxaL1

   coxas.push_back(std::make_shared<Cube>( GMlib::Point<float,3>(-1.0f,0.0f,2.0f) ,0.5,0.5,0.5));

    //Hexapod coxaL2

    coxas.push_back(std::make_shared<Cube>( GMlib::Point<float,3>(-1.0f,0.0f,0.0f) ,0.5,0.5,0.5));

    //Hexapod coxaL3

    coxas.push_back( std::make_shared<Cube>( GMlib::Point<float,3>(-1.0f,0.0f,-2.0f) ,0.5,0.5,0.5));

}

void Hexapod::makeFemurs(GMlib::Point<float, 3> pos){ //TODO: use pos later to figure out position

    //Hexapod fumurR1

    femurs.push_back( std::make_shared<Cube>( GMlib::Point<float,3>(2.25f,0.0f,2.0f) ,0.3,2.0,0.5));

    //Hexapod femurR2

    femurs.push_back( std::make_shared<Cube>( GMlib::Point<float,3>(2.25f,0.0f,0.0f) ,0.3,2.0,0.5));

    //Hexapod femurR3

    femurs.push_back( std::make_shared<Cube>( GMlib::Point<float,3>(2.25f,0.0f,-2.0f) ,0.3,2.0,0.5));

    //Hexapod femurL1

    femurs.push_back( std::make_shared<Cube>( GMlib::Point<float,3>(-2.25f,0.0f,2.0f) ,0.3,2.0,0.5));

    //Hexapod femurL2

    femurs.push_back( std::make_shared<Cube>( GMlib::Point<float,3>(-2.25f,0.0f,0.0f) ,0.3,2.0,0.5));

    //Hexapod femurL3

    femurs.push_back( std::make_shared<Cube>( GMlib::Point<float,3>(-2.25f,0.0f,-2.0f) ,0.3,2.0,0.5));
}

void Hexapod::makeTibias(GMlib::Point<float, 3> pos){ //TODO: use pos later to figure out position

    //Hexapod tibiaR1

    tibias.push_back( std::make_shared<Tibia>(GMlib::Point<float,3>(4.75f,0.0f,0.0f)));

    //Hexapod tibiaR2

    tibias.push_back( std::make_shared<Tibia>(GMlib::Point<float,3>(4.75f,0.0f,2.0f)));

    //Hexapod tibiaR3

    tibias.push_back( std::make_shared<Tibia>(GMlib::Point<float,3>(4.75f,0.0f,-2.0f)));

    //Hexapod tibiaL1

    tibias.push_back( std::make_shared<Tibia>(GMlib::Point<float,3>(-4.75f,0.0f,0.0f)));

    //Hexapod tibiaL2

    tibias.push_back( std::make_shared<Tibia>(GMlib::Point<float,3>(-4.75f,0.0f,2.0f)));

    //Hexapod tibiaL3

    tibias.push_back( std::make_shared<Tibia>(GMlib::Point<float,3>(-4.75f,0.0f,-2.0f)));

    //adjust their orientations
    for(unsigned int i= 0;i<3;i++){ //Right part
       tibias[i] ->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f ) );
       tibias[i]->rotate( GMlib::Angle(45), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f ) );
    }
    for(unsigned int i= 3;i<6;i++){ //Left part
       tibias[i] ->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, -1.0f, 0.0f ) );
       tibias[i]->rotate( GMlib::Angle(45), GMlib::Vector<float,3>(0.0f, 0.0f, -1.0f ) );
    }
}

void Hexapod::setMaterial(const GMlib::Material &bm,const GMlib::Material &cm,const GMlib::Material &fm,const GMlib::Material &tm){

    body->setMaterial(bm);
    for(unsigned int i= 0;i<6;i++){
        coxas[i]->setMaterial(cm);
        femurs[i]->setMaterial(fm);
        tibias[i]->setMaterial(tm);
    }
}

void Hexapod::replot(int m1, int m2, int d1, int d2){ //for the cubic parts{

    body->replot(m1,m2,d1,d2);
    for(unsigned int i= 0;i<6;i++){
        coxas[i]->replot(m1,m2,d1,d2);
        femurs[i]->replot(m1,m2,d1,d2);
        tibias[i]->replot(2,5,1,1);
    }

}

void Hexapod::toggleDefaultVisualizer(){

    body->toggleDefaultVisualizer();
    for(unsigned int i= 0;i<6;i++){
        coxas[i]->toggleDefaultVisualizer();
        femurs[i]->toggleDefaultVisualizer();
        tibias[i]->toggleDefaultVisualizer();
    }
}

void Hexapod::insert(const std::shared_ptr<GMlib::Scene>&scene){

    body->insert(scene);
    for(unsigned int i= 0;i<6;i++){
        coxas[i]->insert(scene);
        femurs[i]->insert(scene);
        scene->insert(tibias[i].get());
    }

}
