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


protected:
    void walk_forward(Gait gait, double dt);
    void walk_backward(Gait gait=Tripod, double dt =0.016);
    void run(double dt =0.016);
    void rotate_in_place();

private:

    void localSimulate(double dt) override;
    void run_inverse_kinematicts(Gait gait);
    void update_target_positions(Gait gait, int i, int j);
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


    bool forward = true;

};

#endif //HEXAPOD_CONTROLLER_H
