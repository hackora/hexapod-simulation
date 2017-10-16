#ifndef HEXAPOD_CONTROLLER_H
#define HEXAPOD_CONTROLLER_H

#include<gmParametricsModule>

#include "gait.h"
#include "hexapod.h"
#include <vector>
#include<memory>


class Hexapod_controller: public GMlib::SceneObject {
    GM_SCENEOBJECT (Hexapod_controller)

public:
    Hexapod_controller();
    void walk_forward();
    void walk_backward();
    void turn_right();
    void turn_left();
    void addHexapod(std::shared_ptr<Hexapod> hexapod);
    void move_from_A_to_B();
    void change_gait(int i);

    void return_to_start();

    bool walking = false;
    bool running = false;
    bool forward = true;
    Gait current_gait = gait_type::Tripod;




protected:
    void walk_forward(double dt);
    void walk_backward(double dt);
    void run(double dt);
    void walk(double dt);
    void rotate_in_place();

private:

    void localSimulate(double dt) override;
    void run_inverse_kinematicts();
    void update_target_positions(int i, int j);
    void update_angles(int i, int j);


    std::shared_ptr<Gait> tripod;
    std::shared_ptr<Gait> wave;
    std::shared_ptr<Hexapod> hexapod;
    std::shared_ptr<GMlib::PCylinder<float>> body;
    std::vector<std::shared_ptr<Leg>> legs;
    std::vector<GMlib::Point<float,3>> target_positions;
    GMlib::APoint<float,3> tip_position; // IK variable
    std::vector<std::vector<IKAngles>> angles;  //leg/step (3 angles)


    int wave_steps[6] = {1,3,3,3,3,3};
    int active_leg = 0;
    int tripod_steps[6] = {1,3,1,3,1,3};
    bool IK = false;

    double timespan = 0.16; //dt*10
    double tick =0.0;
    double rotation_speed= 2.0;
    double translation_speed=1.0;

    bool reset = false;

};

#endif //HEXAPOD_CONTROLLER_H
