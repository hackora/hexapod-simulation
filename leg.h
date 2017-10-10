#ifndef LEG_H
#define LEG_H

#include<gmParametricsModule>
#include<memory>
#include "tibia.h"

struct IKAngles {

    GMlib::Angle coxaAngle;
    GMlib::Angle femurAngle;
    GMlib::Angle tibiaAngle;
    IKAngles(GMlib::Angle coxa, GMlib::Angle femur, GMlib::Angle tibia) {coxaAngle = coxa; femurAngle = femur; tibiaAngle = tibia; }
    void operator=(IKAngles angles){coxaAngle = angles.coxaAngle; femurAngle = angles.femurAngle; tibiaAngle = angles.tibiaAngle;}
};


class Leg: public  GMlib::SceneObject {
    GM_SCENEOBJECT(Leg)

    public:

        Leg(GMlib::Point<float,3> pos= {0.0f,0.0f,0.0f} , bool orientation = true);
        Leg(const Leg &copy){}
        virtual ~Leg() {}
        void setMaterial(const GMlib::Material &cm, const GMlib::Material &fm, const GMlib::Material &tm, const GMlib::Material &jm);
        void replot(int m1=20, int m2=20, int d1=1, int d2=1);
        void toggleDefaultVisualizer();
        void insert(GMlib::Scene& scene){ scene.insert(this);}

        IKAngles inverseKinematics(GMlib::Point<float,3> targetPosition);
        void update_tip_position();
        GMlib::APoint<float,4> get_tip_pos(){update_tip_position();return tip_base_pos;}
        std::shared_ptr<GMlib::PSphere<float>> leg_base;
        std::shared_ptr<GMlib::PSphere<float>> tip;


        std::vector<std::shared_ptr<GMlib::PSphere<float>>> getJoints();
        std::shared_ptr<GMlib::PCylinder<float>> getCoxa();
        std::shared_ptr<GMlib::PCylinder<float>> getFemur();
        std::shared_ptr<Tibia> getTibia();
        bool isRight(){return right;}


    protected:
        std::shared_ptr< GMlib::PCylinder<float>> coxa;
        std::shared_ptr<GMlib::PCylinder<float>> femur;
        std::shared_ptr<Tibia> tibia;
        std::vector<std::shared_ptr< GMlib::PSphere<float>>> joints;    // 3


    private:
        void makeCoxa();
        void makeFemur();
        void makeTibia();
        void makeJoints();
        void adjustPositions();
        void link();

        bool right;
        GMlib::APoint<float,4> tip_base_pos;

};


#endif // LEG_H
