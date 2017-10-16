#include "hexapod_controller.h"

Hexapod_controller::Hexapod_controller(){

    tripod = std::make_shared<Gait>(gait_type::Tripod);
    wave = std::make_shared<Gait>(gait_type::Wave);
    left_turn = std::make_shared<Gait>(gait_type::LeftTurn);
    right_turn = std::make_shared<Gait>(gait_type::RightTurn);
    for(unsigned int i= 0; i<6;i++){
        walk_target_positions.push_back(GMlib::Vector<float,3>(0.0f,0.0f,0.0f));
        turn_left_target_positions.push_back(GMlib::Vector<float,3>(0.0f,0.0f,0.0f));
        turn_right_target_positions.push_back(GMlib::Vector<float,3>(0.0f,0.0f,0.0f));
        std::vector<IKAngles> temp_angles;
        for(unsigned int j =0; j<4;j++){
            auto angle = IKAngles(0.0f,0.0f,0.0f);
            temp_angles.push_back(angle);
        }
        walk_angles.push_back(temp_angles);
        turn_left_angles.push_back(temp_angles);
        turn_right_angles.push_back(temp_angles);
    }

}

void Hexapod_controller::change_gait(int i) {

    if(i == 1) current_gait = *tripod.get();
    else if(i == 2)
        current_gait = *wave.get();
    else if(i == 3) current_gait = *left_turn.get();
    else if(i == 4) current_gait = *right_turn.get();
}

void Hexapod_controller::addHexapod(std::shared_ptr<Hexapod> hexapod){
    this->hexapod = hexapod;
    body =hexapod->getBody();
    legs = hexapod->getLegs();
}

void Hexapod_controller::update_target_positions(GMlib::APoint<float,3> &tip_position, std::vector<GMlib::Point<float,3>> &target_positions,int i, int j){

    switch(j){
    case 1:{
        auto z= tip_position[2] + current_gait.lift_height;
        target_positions[i]  = GMlib::Point<float,3>(tip_position[0] ,tip_position[1] ,z);
        tip_position= target_positions[i];
        break;
    }
    case 2:{
        float y =0.0f ;
        if(legs[i]->isRight() && forward)
            y = tip_position[1] + current_gait.step_size;
        else
            y = tip_position[1] - current_gait.step_size;
        auto l = std::sqrt(tip_position[0]*tip_position[0]+tip_position[1]*tip_position[1]);
        auto x = l * std::sin(std::acos(y/l));
        target_positions[i]  = GMlib::Point<float,3>(x , y ,tip_position[2]);
        tip_position= target_positions[i];
        break;
    }
    case 3:{
        auto z=tip_position[2] - current_gait.lift_height;
        if(std::abs((tip_position[2] - current_gait.lift_height) - (-2))<=0.1)
            target_positions[i]  = GMlib::Point<float,3>(tip_position[0] ,tip_position[1] ,z);
        else
            target_positions[i]  = GMlib::Point<float,3>(tip_position[0] ,tip_position[1] ,tip_position[2]);
        tip_position= target_positions[i];
        break;
    }
    case 4:{
        auto y = tip_position[1];
        if(legs[i]->isRight() && forward)
            y  -= current_gait.step_size;
        else
            y += current_gait.step_size;
        auto l = std::sqrt(tip_position[0]*tip_position[0]+tip_position[1]*tip_position[1]);
        auto x = l * std::sin(std::acos(y/l));
        target_positions[i]  = GMlib::Point<float,3>(x , y ,tip_position[2]);
        tip_position= target_positions[i];
        break;
    }
    }
}
void Hexapod_controller::update_angles(std::vector<std::vector<IKAngles>> &angles,std::vector<GMlib::Point<float,3>> &target_positions,int i, int j){

    auto angle = legs[i]->inverseKinematics(target_positions[i]);
    angles[i][j]= angle ;
}

void Hexapod_controller::walk_backward(double dt){
    forward =false;
    walk_forward(dt);
}

void Hexapod_controller::walk_forward(double dt){

    reset = false;

    auto var = tick/timespan;

    for(unsigned int i =0;i<6;i++){

        GMlib::Angle angle1= (legs[i]->getJoints()[0]->getGlobalDir())
                .getAngle(legs[i]->leg_base->getGlobalDir());
        GMlib::Angle angle2= (legs[i]->getJoints()[1]->getGlobalDir())
                .getAngle(legs[i]->getJoints()[0]->getGlobalDir());
        GMlib::Angle angle3=  (legs[i]->getJoints()[2]->getGlobalDir())
                .getAngle(legs[i]->getJoints()[1]->getGlobalDir())-6.28319;

        if(current_gait.id == Tripod){

            auto coxaAngle =  walk_angles[i][tripod_steps[i]-1].coxaAngle;
            auto femurAngle = walk_angles[i][tripod_steps[i]-1].femurAngle;
            auto tibiaAngle = walk_angles[i][tripod_steps[i]-1].tibiaAngle;

            if(i !=0  && i !=5){
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
                if(running) translation_speed = translation_speed * 10;

                if(forward)
                    body->translate( GMlib::Vector<float,3>(0.0f,-translation_speed*tick/100 , 0.0f));
                else
                    body->translate( GMlib::Vector<float,3>(0.0f,translation_speed*tick/100, 0.0f));

            }
        }

        else if(current_gait.id == Wave){

            auto coxaAngle =  walk_angles[i][wave_steps[i]-1].coxaAngle;
            auto femurAngle = walk_angles[i][wave_steps[i]-1].femurAngle;
            auto tibiaAngle = walk_angles[i][wave_steps[i]-1].tibiaAngle;

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
        if(current_gait.id == Tripod){
            if(tripod_steps[0]<4){
                tripod_steps[0]++;
                tripod_steps[2]++;
                tripod_steps[4]++;
            }

            else{
                tripod_steps[0]=1;
                tripod_steps[2]=1;
                tripod_steps[4]=1;
                if(walking) walking = false;       // One cycle of movement
                else running = false;
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

        else if(current_gait.id == Wave){

            if(wave_steps[active_leg] == 3)
            {

                wave_steps[active_leg] = 4;

                if(active_leg < 5) {
                    active_leg++;
                }
                else {
                    active_leg = 0;
                    walking = false;        // One cycle of movement
                }

                wave_steps[active_leg] = 1;

            }
            else
            {
                if(wave_steps[active_leg] < 4) wave_steps[active_leg]++;
                else wave_steps[active_leg] = 1;
            }
        }

        tick =0.0;
    }
}

void Hexapod_controller::run(double dt){
    timespan = 0.08;  //dt*5
    walk_forward(dt);
}

void Hexapod_controller::walk(double dt) {
    timespan = 0.16; // dt*10
    walk_forward(dt);
}

void Hexapod_controller::localSimulate(double dt) {

    if(!IK){
        run_inverse_kinematicts();
        std::cout<<"Inverse Kinematics for walking is run !"<<std::endl;
        IK = true;
    }

    if(walking) walk(dt);
    if(running && current_gait.id == Tripod ) run(dt);

    if(turning_left) turn_left(dt);
    if(turning_right) turn_right(dt);


}

void Hexapod_controller::run_inverse_kinematicts(){

        for(unsigned int i =0;i<legs.size();i++){
            walk_tip_position=   legs[i]->get_tip_pos();
            turn_left_tip_position=   legs[i]->get_tip_pos();
            turn_right_tip_position=   legs[i]->get_tip_pos();

            {//left turn
                auto count = 0;
                auto index =tripod_left_turn_steps[i];
                while(count <4){
                    update_target_positions(turn_left_tip_position,turn_left_target_positions, i,index);
                    update_angles(turn_left_angles,turn_left_target_positions,i,index-1);
                    count++;
                    if(index<4)
                        index++;
                    else
                        index =1;
                }

            }
            {//right turn
                auto count = 0;
                forward = false;
                 auto index =tripod_right_turn_steps[i];
                 while(count <4){
                     update_target_positions(turn_right_tip_position,turn_right_target_positions, i,index);
                     update_angles(turn_right_angles,turn_right_target_positions,i,index-1);
                     count++;
                     if(index<4)
                         index++;
                     else
                         index =1;
                 }
                 forward = true;
            }
            {//walk
                auto count = 0;
                auto index =tripod_steps[i];
                if(current_gait.id == Wave)
                     index =wave_steps[i];
                while(count <4){
                    update_target_positions(walk_tip_position,walk_target_positions,i,index);
                    update_angles(walk_angles,walk_target_positions,i,index-1);
                    count++;
                    if(index<4)
                        index++;
                    else
                        index =1;
                }
            }
        }
}

void Hexapod_controller::return_to_start() {

    if(!reset) {

        std::cout<<"Returning the Hexapod to the starting position !"<<std::endl;
        walking = false;

        // Reset position
        auto pos = GMlib::Point<float,3>(0.0f, 0.0f, 0.0f);
        auto dir = GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f);
        auto up = GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f);

        body->set(pos, dir, up);

        // Legs
        for( unsigned int i = 0; i < legs.size(); i++) {


            GMlib::Angle angle1= (legs[i]->getJoints()[0]->getGlobalDir())
                    .getAngle(legs[i]->leg_base->getGlobalDir());
            GMlib::Angle angle2= (legs[i]->getJoints()[1]->getGlobalDir())
                    .getAngle(legs[i]->getJoints()[0]->getGlobalDir());
            GMlib::Angle angle3=  (legs[i]->getJoints()[2]->getGlobalDir())
                    .getAngle(legs[i]->getJoints()[1]->getGlobalDir());

            GMlib::Angle coxaAngle_degrees = 45;
            GMlib::Angle coxaAngle_radians = coxaAngle_degrees.getRad();
            if( i == 1 || i == 4) coxaAngle_radians =  0.0;

            GMlib::Angle femurAngle = 0.0;

            GMlib::Angle tibiaAngle_degrees = -90;
            GMlib::Angle tibiaAngle_radians = tibiaAngle_degrees.getRad();

            if( (i !=0  && i !=2 && legs[i]->isRight()) || (i !=3  && i !=5 && !legs[i]->isRight()) ) {
                legs[i]->getJoints()[0]->rotate((coxaAngle_radians +angle1),GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
                legs[i]->getJoints()[1]->rotate((-femurAngle-angle2 ), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
                legs[i]->getJoints()[2]->rotate((tibiaAngle_radians+angle3),GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
            }
            else{
                legs[i]->getJoints()[0]->rotate((coxaAngle_radians -angle1),GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
                legs[i]->getJoints()[1]->rotate((-femurAngle-angle2 ), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
                legs[i]->getJoints()[2]->rotate(((tibiaAngle_radians+angle3)),GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
            }

            reset = true;
        }
    }
}

void Hexapod_controller::turn_left(double dt){

    reset = false;

    auto var = tick/timespan;

    if(rotate_body_left){
        body->rotateGlobal(0.261799*var/50,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));   // 0.261799 radians = 15 degrees

    }

    else{
        for(unsigned int i =0;i<6;i++){

            GMlib::Angle angle1= (legs[i]->getJoints()[0]->getGlobalDir())
                    .getAngle(legs[i]->leg_base->getGlobalDir());
            GMlib::Angle angle2= (legs[i]->getJoints()[1]->getGlobalDir())
                    .getAngle(legs[i]->getJoints()[0]->getGlobalDir());
            GMlib::Angle angle3=  (legs[i]->getJoints()[2]->getGlobalDir())
                    .getAngle(legs[i]->getJoints()[1]->getGlobalDir())-6.28319;


            auto coxaAngle =  turn_left_angles[i][tripod_left_turn_steps[i]-1].coxaAngle;
            auto femurAngle = turn_left_angles[i][tripod_left_turn_steps[i]-1].femurAngle;
            auto tibiaAngle = turn_left_angles[i][tripod_left_turn_steps[i]-1].tibiaAngle;

            if(angle2.getDeg()==0)
                angle2 = 0.0;

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
        }
    }

    if(tick< timespan-dt){
        tick+=dt;
    }
    else {

        if(rotate_body_left){
            body_rotated_left =true;
            rotate_body_left =false;
            if(tripod_left_turn_steps[0] ==1)
                turning_left = false;
        }
        else if(((tripod_left_turn_steps[0] ==3 && tripod_left_turn_steps[1] ==1) || (tripod_left_turn_steps[0] ==1 && tripod_left_turn_steps[1] ==3)) && !body_rotated_left ){
            rotate_body_left = true;
            body_rotated_left =true;
        }
        else if(tripod_left_turn_steps[0] ==1){
            tripod_left_turn_steps[0] =4;
            tripod_left_turn_steps[2] =4;
            tripod_left_turn_steps[4] =2;
            rotate_body_left = false;
        }
        else if(tripod_left_turn_steps[0] ==4){
            tripod_left_turn_steps[0] =3;
            tripod_left_turn_steps[2] =3;
            tripod_left_turn_steps[4] =3;

            tripod_left_turn_steps[1] =1;
            tripod_left_turn_steps[3] =1;
            tripod_left_turn_steps[5] =1;
            rotate_body_left = false;
            body_rotated_left =false;
        }
        else if(tripod_left_turn_steps[1] ==1){
            tripod_left_turn_steps[1] =4;
            tripod_left_turn_steps[3] =2;
            tripod_left_turn_steps[5] =2;
            rotate_body_left = false;
        }
        else{
            tripod_left_turn_steps[0] =1;
            tripod_left_turn_steps[2] =1;
            tripod_left_turn_steps[4] =1;

            tripod_left_turn_steps[1] =3;
            tripod_left_turn_steps[3] =3;
            tripod_left_turn_steps[5] =3;
            rotate_body_left = false;
            body_rotated_left =false;

        }
        tick =0.0;

    }
}

void Hexapod_controller::turn_right(double dt){

    reset = false;

    auto var = tick/timespan;

    if(rotate_body){
        body->rotateGlobal(-0.261799*var/50,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));   // 0.261799 radians = 15 degrees

    }

    else{
        for(unsigned int i =0;i<6;i++){

            GMlib::Angle angle1= (legs[i]->getJoints()[0]->getGlobalDir())
                    .getAngle(legs[i]->leg_base->getGlobalDir());
            GMlib::Angle angle2= (legs[i]->getJoints()[1]->getGlobalDir())
                    .getAngle(legs[i]->getJoints()[0]->getGlobalDir());
            GMlib::Angle angle3=  (legs[i]->getJoints()[2]->getGlobalDir())
                    .getAngle(legs[i]->getJoints()[1]->getGlobalDir())-6.28319;


            auto coxaAngle =  turn_right_angles[i][tripod_right_turn_steps[i]-1].coxaAngle;
            auto femurAngle = turn_right_angles[i][tripod_right_turn_steps[i]-1].femurAngle;
            auto tibiaAngle = turn_right_angles[i][tripod_right_turn_steps[i]-1].tibiaAngle;

            if(angle2.getDeg()==0)
                angle2 = 0.0;

            if(i !=0  && i !=5 && i !=4){
                legs[i]->getJoints()[0]->rotate((coxaAngle +angle1)*var,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
                legs[i]->getJoints()[1]->rotate((-femurAngle-angle2 )*var, GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
                legs[i]->getJoints()[2]->rotate((tibiaAngle+angle3)*var,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
            }
            else{
                legs[i]->getJoints()[0]->rotate((coxaAngle -angle1)*var,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
                legs[i]->getJoints()[1]->rotate((-femurAngle-angle2 )*var, GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
                legs[i]->getJoints()[2]->rotate(((tibiaAngle+angle3))*var,GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
            }
        }
    }

    if(tick< timespan-dt){
        tick+=dt;
    }
    else {

        if(rotate_body){
            body_rotated =true;
            rotate_body =false;
            if(tripod_right_turn_steps[0] ==1)
                turning_right = false;
        }
        else if(((tripod_right_turn_steps[0] ==3 && tripod_right_turn_steps[1] ==1) || (tripod_right_turn_steps[0] ==1 && tripod_right_turn_steps[1] ==3)) && !body_rotated ){
            rotate_body = true;
            body_rotated =true;
        }
        else if(tripod_right_turn_steps[0] ==1){
            tripod_right_turn_steps[0] =4;
            tripod_right_turn_steps[2] =4;
            tripod_right_turn_steps[4] =2;
            rotate_body = false;
        }
        else if(tripod_right_turn_steps[0] ==4){
            tripod_right_turn_steps[0] =3;
            tripod_right_turn_steps[2] =3;
            tripod_right_turn_steps[4] =3;

            tripod_right_turn_steps[1] =1;
            tripod_right_turn_steps[3] =1;
            tripod_right_turn_steps[5] =1;
            rotate_body = false;
            body_rotated =false;
        }
        else if(tripod_right_turn_steps[1] ==1){
            tripod_right_turn_steps[1] =4;
            tripod_right_turn_steps[3] =2;
            tripod_right_turn_steps[5] =2;
            rotate_body = false;
        }
        else{
            tripod_right_turn_steps[0] =1;
            tripod_right_turn_steps[2] =1;
            tripod_right_turn_steps[4] =1;

            tripod_right_turn_steps[1] =3;
            tripod_right_turn_steps[3] =3;
            tripod_right_turn_steps[5] =3;
            rotate_body = false;
            body_rotated =false;

        }
        tick =0.0;

    }
}
