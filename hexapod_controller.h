#ifndef HEXAPOD_CONTROLLER_H
#define HEXAPOD_CONTROLLER_H

#include<gmParametricsModule>
#include<memory>

#include "gait.h"
#include "hexapod.h"
#include <vector>


class Hexapod_controller: public GMlib::SceneObject {
    GM_SCENEOBJECT (Hexapod_controller)

public:
    Hexapod_controller();
    void walk_forward();
    void walk_backward();
    void turn_right();
    void turn_left();
    void addHexapod(std::shared_ptr<Hexapod> hexapod);


protected:
    void walk_forward(Gait gait, double dt);
    void walk_backward(Gait gait, double dt);
    void run();
    void rotate_in_place();
    void go_from_A_to_B();

private:
    std::shared_ptr<Gait> tripod;
    int step_in_cycle =1;
    std::shared_ptr<Gait> wave;
    std::shared_ptr<Hexapod> hexapod;
    std::shared_ptr<GMlib::PCylinder<float>> body;
    std::vector<std::shared_ptr<Leg>> legs;
    std::vector<GMlib::Point<float,3>> target_positions;
    GMlib::APoint<float,3> tip_position; // IK variable
    std::vector<std::vector<IKAngles>> angles;  //leg/step (3 angles)
    void localSimulate(double dt) override;
    void update_target_positions(Gait gait, int i, int j);
    void update_angles(int i, int j);
    unsigned int time=0;

    int wave_steps[6] = {1,3,3,3,3,3};
    int active_leg = 0;
    int tripod_steps[6] = {1,3,1,3,1,3};
    bool IK = false;

    double timespan = 0.8;
    double tick =0.0;
    double rotation_speed= 2.0;
    double translation_speed=1.0;

    void run_inverse_kinematicts(Gait gait);

};

#endif //HEXAPOD_CONTROLLER_H
