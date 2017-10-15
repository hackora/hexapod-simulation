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

void Hexapod_controller::update_target_positions(Gait gait, int i, int j ){

    switch(j){
    case 1:{
        auto z= tip_position[2] + gait.lift_height;
        target_positions[i]  = GMlib::Point<float,3>(tip_position[0] ,tip_position[1] ,z);
        tip_position= target_positions[i];
        break;
    }
    case 2:{
        float y =0.0f ;
        if(legs[i]->isRight() && forward)
            y = tip_position[1] + gait.step_size;
        else
            y = tip_position[1] - gait.step_size;
        auto l = std::sqrt(tip_position[0]*tip_position[0]+tip_position[1]*tip_position[1]);
        auto x = l * std::sin(std::acos(y/l));
        target_positions[i]  = GMlib::Point<float,3>(x , y ,tip_position[2]);
        tip_position= target_positions[i];
        break;
    }
    case 3:{
        auto z=tip_position[2] - gait.lift_height;
        if(std::abs((tip_position[2] - gait.lift_height) - (-2))<=0.1)
            target_positions[i]  = GMlib::Point<float,3>(tip_position[0] ,tip_position[1] ,z);
        else
            target_positions[i]  = GMlib::Point<float,3>(tip_position[0] ,tip_position[1] ,tip_position[2]);
        tip_position= target_positions[i];
        break;
    }
    case 4:{
        auto y = tip_position[1];
        if(legs[i]->isRight() && forward)
            y  -= gait.step_size;
        else
            y += gait.step_size;
        auto l = std::sqrt(tip_position[0]*tip_position[0]+tip_position[1]*tip_position[1]);
        auto x = l * std::sin(std::acos(y/l));
        target_positions[i]  = GMlib::Point<float,3>(x , y ,tip_position[2]);
        tip_position= target_positions[i];
        break;
    }
    }
}
void Hexapod_controller::update_angles(int i,int j){

    auto angle = legs[i]->inverseKinematics(target_positions[i]);
    angles[i][j]= angle ;
}

void Hexapod_controller::walk_backward(Gait gait,double dt){
    forward =false;
    walk_forward(*tripod.get(),dt);
}

void Hexapod_controller::walk_forward(Gait gait, double dt){

    auto var = tick/timespan;

    for(unsigned int i =0;i<6;i++){

        GMlib::Angle angle1= (legs[i]->getJoints()[0]->getGlobalDir())
                .getAngle(legs[i]->leg_base->getGlobalDir());
        GMlib::Angle angle2= (legs[i]->getJoints()[1]->getGlobalDir())
                .getAngle(legs[i]->getJoints()[0]->getGlobalDir());
        GMlib::Angle angle3=  (legs[i]->getJoints()[2]->getGlobalDir())
                .getAngle(legs[i]->getJoints()[1]->getGlobalDir())-6.28319;

        if(gait.id == Tripod){

            auto coxaAngle =  angles[i][tripod_steps[i]-1].coxaAngle;
            auto femurAngle = angles[i][tripod_steps[i]-1].femurAngle;
            auto tibiaAngle = angles[i][tripod_steps[i]-1].tibiaAngle;

            if(i !=0  && i !=5 ){
                legs[i]->getJoints()[0]->rotate((coxaAngle +angle1)*var,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
                legs[i]->getJoints()[1]->rotate((-femurAngle-angle2 )*var, GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
                legs[i]->getJoints()[2]->rotate((tibiaAngle+angle3)*var,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
            }
            else{
                legs[i]->getJoints()[0]->rotate((coxaAngle -angle1)*var,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
                legs[i]->getJoints()[1]->rotate((-femurAngle-angle2 )*var, GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
                legs[i]->getJoints()[2]->rotate(((tibiaAngle+angle3))*var,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
            }

            if(tripod_steps[0] == 2 || tripod_steps[3]==2){
                translation_speed = (tripod->step_size )/(timespan);
                if(forward)
                    body->translate( GMlib::Vector<float,3>(0.0f,-translation_speed*tick/100 , 0.0f));
                else
                    body->translate( GMlib::Vector<float,3>(0.0f,translation_speed*tick/100, 0.0f));

            }
        }

        else if(gait.id == Wave){

            auto coxaAngle =  angles[i][wave_steps[i]-1].coxaAngle;
            auto femurAngle = angles[i][wave_steps[i]-1].femurAngle;
            auto tibiaAngle = angles[i][wave_steps[i]-1].tibiaAngle;

            if(i !=0  && i !=5  ){
                legs[i]->getJoints()[0]->rotate((coxaAngle +angle1)*var,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
                legs[i]->getJoints()[1]->rotate((-femurAngle-angle2 )*var, GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
                legs[i]->getJoints()[2]->rotate((tibiaAngle+angle3)*var,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
            }
            else{
                legs[i]->getJoints()[0]->rotate((coxaAngle -angle1)*var,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
                legs[i]->getJoints()[1]->rotate((-femurAngle-angle2 )*var, GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
                legs[i]->getJoints()[2]->rotate(((tibiaAngle+angle3))*var,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
            }

            if(wave_steps[0] == 2  || wave_steps[2] == 2 ||  wave_steps[3] == 2 || wave_steps[5] == 2){
                translation_speed = (tripod->step_size )/(timespan);
                if(forward)
                    body->translate( GMlib::Vector<float,3>(0.0f,-translation_speed*tick/200 , 0.0f));
                else
                    body->translate( GMlib::Vector<float,3>(0.0f,translation_speed*tick/200 , 0.0f));
            }
        }
    }

    if(tick< timespan-dt){
        tick+=dt;
    }
    else {
        if(gait.id == Tripod){
            if(tripod_steps[0]<4){
                tripod_steps[0]++;
                tripod_steps[2]++;
                tripod_steps[4]++;
            }

            else{
                tripod_steps[0]=1;
                tripod_steps[2]=1;
                tripod_steps[4]=1;
            }
            if(tripod_steps[3]<4){
                tripod_steps[1]++;
                tripod_steps[3]++;
                tripod_steps[5]++;
            }

            else{
                tripod_steps[1]=1;
                tripod_steps[3]=1;
                tripod_steps[5]=1;
            }
        }

        else if(gait.id == Wave){
            if(wave_steps[active_leg] == 3) {

                wave_steps[active_leg] = 4;

                if(active_leg < 5) {
                    active_leg++;
                }
                else active_leg = 0;

                wave_steps[active_leg] = 1;

            }
            else {
            if(wave_steps[active_leg] < 4) wave_steps[active_leg]++;
            else wave_steps[active_leg] = 1;
            }
        }

        tick =0.0;
    }
}

void Hexapod_controller::run(double dt){
    timespan = 0.08;  //dt*5
    forward = true;
    walk_forward(*tripod.get(),dt);
}

void Hexapod_controller::localSimulate(double dt) {

    if(!IK){
        run_inverse_kinematicts(*tripod.get());
        std::cout<<"Inverse Kinematics is run !"<<std::endl;
        IK = true;
    }

    walk_forward(*tripod.get(),dt);

//    walk_backward(*tripod.get(),dt);

//    run(dt);


}

void Hexapod_controller::run_inverse_kinematicts(Gait gait){

    for(unsigned int i =0;i<legs.size();i++){
        tip_position=   legs[i]->get_tip_pos();
        auto count = 0;
        auto index =tripod_steps[i];
        if(gait.id == Wave)
             index =wave_steps[i];
        while(count <4){
            update_target_positions(*(tripod.get()),i,index);
            update_angles(i,index-1);
            count++;
            if(index<4)
                index++;
            else
                index =1;
        }
    }
}

void Hexapod_controller::return_to_start() {

    std::cout<<"Returning the Hexapod to the starting position !"<<std::endl;

}
