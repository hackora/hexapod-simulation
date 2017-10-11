#include "gait.h"


Gait::Gait(gait_type type) {
    lift_height = 0.5f;
    id = type;
    step_size = 0.3f;

    set_supportLegs();
    set_dutyFactor();
    set_stanceTime();
    set_swingTime();
    set_bodyVelocity();
}

void Gait::set_supportLegs() {

    if (Tripod) support_legs = 3;
    else support_legs = 5;
}

void Gait::set_bodyVelocity() {

    body_velocity = step_size / cycle_time.count();
}

void Gait::set_dutyFactor()
{
    if(id == Tripod) duty_factor = 0.5f;
    else duty_factor = 0.66f;
}

void Gait::set_stanceTime()
{
    stance_time = (1 - duty_factor) * cycle_time;
}

void Gait::set_swingTime()
{
    swing_time = duty_factor * cycle_time;
}
