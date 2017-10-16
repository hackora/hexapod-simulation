#ifndef GAIT_H
#define GAIT_H

#include<gmParametricsModule>
#include <chrono>

using seconds_type
    = std::chrono::duration<double>; // std::ratio<1,1> is implicit
                                     // default and means seconds

enum gait_type{ Tripod, Wave, LeftTurn,RightTurn };

class Gait {

public:
    Gait(gait_type type);

    void set_supportLegs();
    void set_bodyVelocity();
    void set_dutyFactor();
    void set_stanceTime();
    void set_swingTime();




    float lift_height;
    seconds_type stance_time;
    seconds_type swing_time;
    float duty_factor;
    gait_type id;
    float support_legs;
    float step_size;
    float body_velocity;

    seconds_type cycle_time = seconds_type(1.0);



protected:

private:




};

#endif //GAIT_H
