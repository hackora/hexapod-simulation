#include"hexapod.h"

Hexapod::Hexapod(GMlib::Point<float, 3> pos){
    makeBody(pos);
    makeCoxas(pos);
    makeFemurs(pos);
    makeTibias(pos);
    makeJoints(pos);

}

void Hexapod::makeBody(GMlib::Point<float, 3> pos){

    body = std::make_shared< Cube>( pos,1,2,5);
}

void Hexapod::makeCoxas(GMlib::Point<float, 3> pos){ //TODO: use pos later to figure out position

    //Hexapod coxaR1

    coxas.push_back( std::make_shared<GMlib::PLine<float>>( GMlib::Point<float,3>(1.0f,0.0f,2.0f), GMlib::Point<float,3>(1.5f,0.0f,2.0f)));

    //Hexapod coxaR2

    coxas.push_back(std::make_shared<GMlib::PLine<float>>( GMlib::Point<float,3>(1.0f,0.0f,0.0f) ,GMlib::Point<float,3>(1.5f,0.0f,0.0f)));

    //Hexapod coxaR3

    coxas.push_back(std::make_shared<GMlib::PLine<float>>( GMlib::Point<float,3>(1.0f,0.0f,-2.0f) ,GMlib::Point<float,3>(1.5f,0.0f,-2.0f)));

    //Hexapod coxaL1

   coxas.push_back(std::make_shared<GMlib::PLine<float>>( GMlib::Point<float,3>(-1.0f,0.0f,2.0f) ,GMlib::Point<float,3>(-1.5f,0.0f,2.0f)));

    //Hexapod coxaL2

    coxas.push_back(std::make_shared<GMlib::PLine<float>>( GMlib::Point<float,3>(-1.0f,0.0f,0.0f) ,GMlib::Point<float,3>(-1.5f,0.0f,0.0f)));

    //Hexapod coxaL3

    coxas.push_back( std::make_shared<GMlib::PLine<float>>( GMlib::Point<float,3>(-1.0f,0.0f,-2.0f) ,GMlib::Point<float,3>(-1.5f,0.0f,-2.0f)));

}

void Hexapod::makeFemurs(GMlib::Point<float, 3> pos){ //TODO: use pos later to figure out position

    //Hexapod fumurR1

    femurs.push_back( std::make_shared<GMlib::PLine<float>>( GMlib::Point<float,3>(2.25f,0.0f,2.0f) ,GMlib::Point<float,3>(4.25f,0.0f,2.0f)));

    //Hexapod femurR2

    femurs.push_back( std::make_shared<GMlib::PLine<float>>( GMlib::Point<float,3>(2.25f,0.0f,0.0f) , GMlib::Point<float,3>(4.25f,0.0f,0.0f)));

    //Hexapod femurR3

    femurs.push_back( std::make_shared<GMlib::PLine<float>>( GMlib::Point<float,3>(2.25f,0.0f,-2.0f), GMlib::Point<float,3>(4.25f,0.0f,-2.0f)));

    //Hexapod femurL1

    femurs.push_back( std::make_shared<GMlib::PLine<float>>( GMlib::Point<float,3>(-2.25f,0.0f,2.0f), GMlib::Point<float,3>(-4.25f,0.0f,2.0f)));

    //Hexapod femurL2

    femurs.push_back( std::make_shared<GMlib::PLine<float>>( GMlib::Point<float,3>(-2.25f,0.0f,0.0f), GMlib::Point<float,3>(-4.25f,0.0f,0.0f)));

    //Hexapod femurL3

    femurs.push_back( std::make_shared<GMlib::PLine<float>>( GMlib::Point<float,3>(-2.25f,0.0f,-2.0f), GMlib::Point<float,3>(-4.25f,0.0f,-2.0f)));
}

void Hexapod::makeTibias(GMlib::Point<float, 3> pos){ //TODO: use pos later to figure out position, FLIP THESE

    //Hexapod tibiaR1

    tibias.push_back( std::make_shared<Tibia>(GMlib::Point<float,3>(4.75f,0.0f,2.0f)));

    //Hexapod tibiaR2

    tibias.push_back( std::make_shared<Tibia>(GMlib::Point<float,3>(4.75f,0.0f,0.0f)));

    //Hexapod tibiaR3

    tibias.push_back( std::make_shared<Tibia>(GMlib::Point<float,3>(4.75f,0.0f,-2.0f)));

    //Hexapod tibiaL1

    tibias.push_back( std::make_shared<Tibia>(GMlib::Point<float,3>(-4.75f,0.0f,2.0f)));

    //Hexapod tibiaL2

    tibias.push_back( std::make_shared<Tibia>(GMlib::Point<float,3>(-4.75f,0.0f,0.0f)));

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

void Hexapod::makeJoints(GMlib::Point<float, 3> pos){ //TODO: use pos later to figure out position

    // Right

        // Joints for RF leg

            // Joint between Body and CoxisRF
            auto jointRF_BC = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointRF_BC->translateGlobal(GMlib::Vector<float, 3>{0.75f, 0.0f, 2.0f});
            joints.push_back(jointRF_BC);

            // Join between CoxisRF and FemurRF
            auto jointRF_CF = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointRF_CF->translateGlobal(GMlib::Vector<float, 3>{1.25f, 0.0f, 2.0f});
            joints.push_back(jointRF_CF);

            // Join between FemurRF and TibiaRF
            auto jointRF_FT = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointRF_FT->translateGlobal(GMlib::Vector<float, 3>{3.25f, 0.0f, 2.0f});
            joints.push_back(jointRF_FT);

        // Joints for RM leg

            // Joint between Body and CoxisRM
            auto jointRM_BC = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointRM_BC->translateGlobal(GMlib::Vector<float, 3>{0.75f, 0.0f, 0.0f});
            joints.push_back(jointRM_BC);

            // Join between CoxisRM and FemurRM
            auto jointRM_CF = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointRM_CF->translateGlobal(GMlib::Vector<float, 3>{1.25f, 0.0f, 0.0f});
            joints.push_back(jointRM_CF);

            // Join between FemurRM and TibiaRM
            auto jointRM_FT = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointRM_FT->translateGlobal(GMlib::Vector<float, 3>{3.25f, 0.0f, 0.0f});
            joints.push_back(jointRM_FT);

        // Joints for RB leg

            // Joint between Body and CoxisRB
            auto jointRB_BC = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointRB_BC->translateGlobal(GMlib::Vector<float, 3>{0.75f, 0.0f, -2.0f});
            joints.push_back(jointRB_BC);

            // Join between CoxisRB and FemurRB
            auto jointRB_CF = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointRB_CF->translateGlobal(GMlib::Vector<float, 3>{1.25f, 0.0f, -2.0f});
            joints.push_back(jointRB_CF);

            // Join between FemurRB and TibiaRB
            auto jointRB_FT = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointRB_FT->translateGlobal(GMlib::Vector<float, 3>{3.25f, 0.0f, -2.0f});
            joints.push_back(jointRB_FT);

    // Left

        // Joints for LF leg

            // Joint between Body and CoxisLF
            auto jointLF_BC = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointLF_BC->translateGlobal(GMlib::Vector<float, 3>{-0.75f, 0.0f, 2.0f});
            joints.push_back(jointLF_BC);

            // Join between CoxisLF and FemurLF
            auto jointLF_CF = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointLF_CF->translateGlobal(GMlib::Vector<float, 3>{-1.25f, 0.0f, 2.0f});
            joints.push_back(jointLF_CF);

            // Join between FemurLF and TibiaLF
            auto jointLF_FT = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointLF_FT->translateGlobal(GMlib::Vector<float, 3>{-3.25f, 0.0f, 2.0f});
            joints.push_back(jointLF_FT);

        // Joints for LM leg

            // Joint between Body and CoxisLM
            auto jointLM_BC = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointLM_BC->translateGlobal(GMlib::Vector<float, 3>{-0.75f, 0.0f, 0.0f});
            joints.push_back(jointLM_BC);

            // Join between CoxisLM and FemurLM
            auto jointLM_CF = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointLM_CF->translateGlobal(GMlib::Vector<float, 3>{-1.25f, 0.0f, 0.0f});
            joints.push_back(jointLM_CF);

            // Join between FemurLM and TibiaLM
            auto jointLM_FT = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointLM_FT->translateGlobal(GMlib::Vector<float, 3>{-3.25f, 0.0f, 0.0f});
            joints.push_back(jointLM_FT);

        // Joints for LB leg

            // Joint between Body and CoxisLB
            auto jointLB_BC = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointLB_BC->translateGlobal(GMlib::Vector<float, 3>{-0.75f, 0.0f, -2.0f});
            joints.push_back(jointLB_BC);

            // Join between CoxisLB and FemurLB
            auto jointLB_CF = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointLB_CF->translateGlobal(GMlib::Vector<float, 3>{-1.25f, 0.0f, -2.0f});
            joints.push_back(jointLB_CF);

            // Join between FemurLB and TibiaLB
            auto jointLB_FT = std::make_shared< GMlib::PSphere<float> >(0.5);
            jointLB_FT->translateGlobal(GMlib::Vector<float, 3>{-3.25f, 0.0f, -2.0f});
            joints.push_back(jointLB_FT);

}

void Hexapod::link(){

    for(int i = 0; i < 6; i++) {

        body->insert(coxas[i].get());
    }

    for(int i = 0; i < 6; i++) {

        for( int j = 3*i; j <= 3*i + 2; j++) {

            if( j % 3 == 2) {

                joints[j]->insert( tibias[i].get() );
                femurs[i]->insert( joints[j].get() );
            }
            else if( j % 3 == 1) {

                joints[j]->insert( femurs[i].get() );
                coxas[i]->insert( joints[j].get() );

            }
            else joints[j]->insert( coxas[i].get() );
        }
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

    // Replot for body...
    body->replot(m1,m2,d1,d2);

    // ... legs...
    for(unsigned int i= 0;i<6;i++){
        coxas[i]->replot(m1, d1);
        femurs[i]->replot(m1, d1);
        tibias[i]->replot(2,5,1,1);
    }

    // ... and joints
    for(unsigned int i= 0; i < joints.size(); i++){
        joints[i]->replot(20, 20, 1, 1);
    }
}

void Hexapod::toggleDefaultVisualizer(){

    // Toggle default visualizer for body...
    body->toggleDefaultVisualizer();

    // ... legs...
    for(unsigned int i= 0;i<6;i++){
        coxas[i]->toggleDefaultVisualizer();
        femurs[i]->toggleDefaultVisualizer();
        tibias[i]->toggleDefaultVisualizer();
    }

    // ... and joints
    for(unsigned int i= 0; i < joints.size(); i++) {
        joints[i]->toggleDefaultVisualizer();

    }
}

void Hexapod::insert(const std::shared_ptr<GMlib::Scene>&scene){



//    // Insert body...
//    body->insertToScene(scene);

//    // ... legs...
//    for(unsigned int i= 0;i<6;i++){
//        //coxas[i]->insertToScene(scene);
//        //femurs[i]->insertToScene(scene);
//        //scene->insert(tibias[i].get());
//    }

//    // ... and joints
//    for(unsigned int i= 0; i < joints.size(); i += 3){
//        scene->insert(joints[i].get());

//    }
     link();

        for(unsigned int i= 0;i<6;i++){
            //coxas[i]->insertToScene(scene);
            //femurs[i]->insertToScene(scene);
            scene->insert(tibias[i].get());
        }

        for(unsigned int i= 2; i < joints.size(); i += 3){
            scene->insert(joints[i].get());

        }

        for(unsigned int i= 0;i<6;i++){
            //coxas[i]->insertToScene(scene);
            //femurs[i]->insertToScene(scene);
            scene->insert(femurs[i].get());
            //scene->insert(tibias[i].get());
        }

        for(unsigned int i= 1; i < joints.size(); i += 3){
            scene->insert(joints[i].get());

        }

        for(unsigned int i= 0;i<6;i++){
            scene->insert(coxas[i].get());
            //femurs[i]->insertToScene(scene);
            //scene->insert(tibias[i].get());
        }

        for(unsigned int i= 0; i < joints.size(); i += 3){
            scene->insert(joints[i].get());

        }


        body->insertToScene(scene);



}
