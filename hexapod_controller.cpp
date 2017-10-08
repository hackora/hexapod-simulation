#include "hexapod_controller.h"

Hexapod_controller::Hexapod_controller(){

    tripod = std::make_shared<Gait>(gait_type::Tripod);
    wave = std::make_shared<Gait>(gait_type::Wave);
    for(unsigned int i= 0; i<6;i++){
        target_positions.push_back(GMlib::Vector<float,3>(0.0f,0.0f,0.0f));
        std::vector<IKAngles> temp_angles;
        for(unsigned int j =0; j<4;j++){
            auto angle = IKAngles(0.0f,0.0f,0.0f);
            temp_angles.push_back(angle);
        }
        angles.push_back(temp_angles);
    }
}

void Hexapod_controller::addHexapod(std::shared_ptr<Hexapod> hexapod){
    this->hexapod = hexapod;
    body =hexapod->getBody();
    legs = hexapod->getLegs();
}

void Hexapod_controller::update_target_positions(Gait gait){
   for(unsigned int i =0;i<legs.size();i++){

       auto tibia_pos = legs[i]->getTibia()->getPos();
       auto endEffector_pos = GMlib::Point<float,3>(tibia_pos(0)+1,tibia_pos(1),tibia_pos(2));
       auto endEffector_basePos =  legs[i]->getCoxa()->getMatrix()*
       legs[i]->getJoints()[1]->getMatrix()*  legs[i]->getFemur()->getMatrix() *
       legs[i]->getJoints()[2]->getMatrix()* endEffector_pos;

       switch(tripod_steps[i]){
         case 1:{
           target_positions[i]  = endEffector_basePos[2] + gait.lift_height;

       }
       case 2:{
           if(endEffector_basePos[2] - gait.lift_height>=-2)
               target_positions[i]  = endEffector_basePos[2] - gait.lift_height;
     }
       case 3:{
           target_positions[i]  = endEffector_basePos[1] + gait.step_size;;

     }
     case 4:{
           target_positions[i]  = endEffector_basePos[1] - gait.step_size;
   }
       }
   }

}
void Hexapod_controller::update_angles(){

    for(unsigned int i =0;i<legs.size();i++){
        angles[i].push_back(legs[i]->inverseKinematics(target_positions[i])) ;
    }
}

void Hexapod_controller::walk_forward(Gait gait, int step, bool stepChanged, double dt){

}

void Hexapod_controller::localSimulate(double dt) {

//    if(time%15 ==0){
//        update_target_positions(Tripod );
//        update_angles();
//    }

//    for(unsigned int i=0;i<legs.size();i++){
//        auto coxaAngle =  angles[i][step_in_cycle].coxaAngle;
//        auto femurAngle = angles[i][step_in_cycle].femurAngle;
//        auto tibiaAngle = angles[i][step_in_cycle].tibiaAngle;

//        GMlib::Angle angle1= (legs[i]->getJoints()[1]->getGlobalDir())
//                .getAngle(legs[i]->getJoints()[0]->getGlobalDir());
//        GMlib::Angle angle2=  (legs[i]->getJoints()[2]->getGlobalDir())
//                .getAngle(legs[i]->getJoints()[1]->getGlobalDir());

//        legs[0]->getJoints()[0]->rotate(coxaAngle,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

//        legs[0]->getJoints()[1]->rotate((-femurAngle+angle1 )/15.0, GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

//        legs[0]->getJoints()[2]->rotate((tibiaAngle+angle2)/15.0,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));


//        switch(tripod_steps[i]){
//          case 1:{
//            if(time>=15) tripod_steps[i] =3;

//        }
//        case 2:{
//            if(time>=15) tripod_steps[i] =4;
//      }
//        case 3:{
//            if(time>=15) tripod_steps[i] =2;

//      }
//      case 4:{
//            if(time>=15) tripod_steps[i] =1;
//    }
//        }



//    }

//    if(time <15)
//        time++;
//    else
//        time =0;


//    for(unsigned int i =0;i<legs.size();i++){

        auto tibia_pos = legs[1]->getTibia()->getPos();
        auto endEffector_pos = GMlib::Point<float,3>(tibia_pos(0)+1,tibia_pos(1),tibia_pos(2));

        auto tibia_gpos = legs[0]->getTibia()->getGlobalPos();

         auto first = legs[1]->getCoxa()->getMatrix();
         auto second = legs[1]->getJoints()[1]->getMatrix();
         auto third =  legs[1]->getFemur()->getMatrix();
         auto fourth =  legs[1]->getJoints()[2]->getMatrix();
        auto endEffector_basePos =  legs[1]->getCoxa()->getMatrix()*
                legs[1]->getJoints()[1]->getMatrix()* legs[1]->getFemur()->getMatrix() *
                legs[1]->getJoints()[2]->getMatrix()* endEffector_pos;

        auto test =2;
//    }
}
