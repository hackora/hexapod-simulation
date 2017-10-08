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
    void walk_forward(Gait gait, int step, bool stepChanged, double dt);
    void walk_backward(Gait gait);
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
    std::vector<GMlib::Vector<float,3>> target_positions;
    std::vector<std::vector<IKAngles>> angles;  //leg/step (3 angles)
    void localSimulate(double dt) override;
    void update_target_positions(Gait gait);
    void update_angles();
    unsigned int time=0;
    int tripod_steps[6] = {1,2,1,2,1,2};


};

#endif //HEXAPOD_CONTROLLER_H
