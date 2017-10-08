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
//   for(unsigned int i =0;i<legs.size();i++){


       switch(tripod_steps[0]){
         case 1:{
           auto tip_position = legs[0]->get_tip_pos();
           auto z=tip_position[2] + gait.lift_height;
           target_positions[0]  = GMlib::Point<float,3>(tip_position[0] ,tip_position[1] ,z);
           break;
       }
       case 2:{
           auto tip_position = target_positions[0];
           auto z=tip_position[2] - gait.lift_height;
           if(tip_position[2] - gait.lift_height>=-2)
               target_positions[0]  = GMlib::Point<float,3>(tip_position[0] ,tip_position[1] ,z);
           else
               target_positions[0]  = GMlib::Point<float,3>(tip_position[0] ,tip_position[1] ,tip_position[2]);
           break;
     }
       case 3:{
           auto tip_position = target_positions[0];
           auto y = tip_position[1] + gait.step_size;
           target_positions[0]  = GMlib::Point<float,3>(tip_position[0] , y ,tip_position[2]);
           break;
     }
     case 4:{
           auto tip_position = target_positions[0];
           auto y=tip_position[1] - gait.step_size;
           target_positions[0]  = GMlib::Point<float,3>(tip_position[0] , y ,tip_position[2]);
           break;
   }
       }
//   }

}
void Hexapod_controller::update_angles(){

    for(unsigned int i =0;i<legs.size();i++){
        auto angle = legs[i]->inverseKinematics(target_positions[i]);
        angles[i][tripod_steps[i]]=angle ;
    }
}

void Hexapod_controller::walk_forward(Gait gait, int step, bool stepChanged, double dt){

}

void Hexapod_controller::localSimulate(double dt) {

//    if(time<=15){
//        update_target_positions(Tripod );
//        update_angles();
//    }

////    for(unsigned int i=0;i<legs.size();i++){
//        auto coxaAngle =  angles[0][tripod_steps[0]].coxaAngle;
//        auto femurAngle = angles[0][tripod_steps[0]].femurAngle;
//        auto tibiaAngle = angles[0][tripod_steps[0]].tibiaAngle;

//        GMlib::Angle angle1= (legs[0]->getJoints()[1]->getGlobalDir())
//                .getAngle(legs[0]->getJoints()[0]->getGlobalDir());
//        GMlib::Angle angle2=  (legs[0]->getJoints()[2]->getGlobalDir())
//                .getAngle(legs[0]->getJoints()[1]->getGlobalDir());

//        legs[0]->getJoints()[0]->rotate(coxaAngle/15.0,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

//        legs[0]->getJoints()[1]->rotate((-femurAngle+angle1 )/15.0, GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

//        legs[0]->getJoints()[2]->rotate((tibiaAngle+angle2)/15.0,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));


//        switch(tripod_steps[0]){
//          case 1:{
//            if(time>=15) tripod_steps[0] =3;
//            break;

//        }
//        case 2:{
//            if(time>=15) tripod_steps[0] =4;
//            break;
//      }
//        case 3:{
//            if(time>=15) tripod_steps[0] =2;
//            break;

//      }
//      case 4:{
//            if(time>=15) tripod_steps[0] =1;
//            break;
//    }
//        }



////    }

//    if(time <15)
//        time++;
//    else
//        time =0;

    if(t==50){ //lift
                update_target_positions(Tripod );
                update_angles();

        //    for(unsigned int i=0;i<legs.size();i++){
                auto coxaAngle =  angles[0][tripod_steps[0]].coxaAngle;
                auto femurAngle = angles[0][tripod_steps[0]].femurAngle;
                auto tibiaAngle = angles[0][tripod_steps[0]].tibiaAngle;

                GMlib::Angle angle1= (legs[0]->getJoints()[1]->getGlobalDir())
                        .getAngle(legs[0]->getJoints()[0]->getGlobalDir());
                GMlib::Angle angle2=  (legs[0]->getJoints()[2]->getGlobalDir())
                        .getAngle(legs[0]->getJoints()[1]->getGlobalDir());

                legs[0]->getJoints()[0]->rotate(coxaAngle,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

                legs[0]->getJoints()[1]->rotate((-femurAngle+angle1 ), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

                legs[0]->getJoints()[2]->rotate((tibiaAngle+angle2),GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
    }

    else if(t==200){//forward
        tripod_steps[0] =3;
        update_target_positions(Tripod );
        update_angles();

//    for(unsigned int i=0;i<legs.size();i++){
        auto coxaAngle =  angles[0][tripod_steps[0]].coxaAngle;
        auto femurAngle = angles[0][tripod_steps[0]].femurAngle;
        auto tibiaAngle = angles[0][tripod_steps[0]].tibiaAngle;

        GMlib::Angle angle1= (legs[0]->getJoints()[1]->getGlobalDir())
                .getAngle(legs[0]->getJoints()[0]->getGlobalDir());
        GMlib::Angle angle2=  (legs[0]->getJoints()[2]->getGlobalDir())
                .getAngle(legs[0]->getJoints()[1]->getGlobalDir());

        legs[0]->getJoints()[0]->rotate(coxaAngle,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

        legs[0]->getJoints()[1]->rotate((-femurAngle+angle1 ), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

        legs[0]->getJoints()[2]->rotate((tibiaAngle+angle2),GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
    }
    else if(t==400){//down
        tripod_steps[0] =2;
        update_target_positions(Tripod );
        update_angles();

//    for(unsigned int i=0;i<legs.size();i++){
        auto coxaAngle =  angles[0][tripod_steps[0]].coxaAngle;
        auto femurAngle = angles[0][tripod_steps[0]].femurAngle;
        auto tibiaAngle = angles[0][tripod_steps[0]].tibiaAngle;

        GMlib::Angle angle1= (legs[0]->getJoints()[1]->getGlobalDir())
                .getAngle(legs[0]->getJoints()[0]->getGlobalDir());
        GMlib::Angle angle2=  (legs[0]->getJoints()[2]->getGlobalDir())
                .getAngle(legs[0]->getJoints()[1]->getGlobalDir());

        legs[0]->getJoints()[0]->rotate(coxaAngle,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

        legs[0]->getJoints()[1]->rotate((-femurAngle+angle1 ), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

        legs[0]->getJoints()[2]->rotate((tibiaAngle+angle2),GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
    }
//    else if(t==600){//backward
//        tripod_steps[0] =4;
//        update_target_positions(Tripod );
//        update_angles();

////    for(unsigned int i=0;i<legs.size();i++){
//        auto coxaAngle =  angles[0][tripod_steps[0]].coxaAngle;
//        auto femurAngle = angles[0][tripod_steps[0]].femurAngle;
//        auto tibiaAngle = angles[0][tripod_steps[0]].tibiaAngle;

//        GMlib::Angle angle1= (legs[0]->getJoints()[1]->getGlobalDir())
//                .getAngle(legs[0]->getJoints()[0]->getGlobalDir());
//        GMlib::Angle angle2=  (legs[0]->getJoints()[2]->getGlobalDir())
//                .getAngle(legs[0]->getJoints()[1]->getGlobalDir());

//        legs[0]->getJoints()[0]->rotate(coxaAngle,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

//        legs[0]->getJoints()[1]->rotate((-femurAngle+angle1 ), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

//        legs[0]->getJoints()[2]->rotate((tibiaAngle+angle2),GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

//    }

//    else if(t==800){
//        tripod_steps[0] =1;
//        update_target_positions(Tripod );
//        update_angles();

////    for(unsigned int i=0;i<legs.size();i++){
//        auto coxaAngle =  angles[0][tripod_steps[0]].coxaAngle;
//        auto femurAngle = angles[0][tripod_steps[0]].femurAngle;
//        auto tibiaAngle = angles[0][tripod_steps[0]].tibiaAngle;

//        GMlib::Angle angle1= (legs[0]->getJoints()[1]->getGlobalDir())
//                .getAngle(legs[0]->getJoints()[0]->getGlobalDir());
//        GMlib::Angle angle2=  (legs[0]->getJoints()[2]->getGlobalDir())
//                .getAngle(legs[0]->getJoints()[1]->getGlobalDir());

//        legs[0]->getJoints()[0]->rotate(coxaAngle,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

//        legs[0]->getJoints()[1]->rotate((-femurAngle+angle1 ), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));

//        legs[0]->getJoints()[2]->rotate((tibiaAngle+angle2),GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
//    }
    t++;
}
