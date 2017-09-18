#ifndef LEG_H
#define LEG_H

#include<gmParametricsModule>
#include<memory>

struct Angles {

    GMlib::Angle alpha;
    GMlib::Angle beta;
    GMlib::Angle gamma;
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
        void insert(const std::shared_ptr<GMlib::Scene>&scene);

        Angles inverseKinematics(GMlib::Point<float,3> oldPos, GMlib::Point<float,3> newPos);

        std::vector<std::shared_ptr<GMlib::PSphere<float>>> getJoints();
        std::shared_ptr<GMlib::PCylinder<float>> getCoxa();
        std::shared_ptr<GMlib::PCylinder<float>> getFemur();
        std::shared_ptr<GMlib::PCone<float>> getTibia();


    protected:
        std::shared_ptr< GMlib::PCylinder<float>> coxa;
        std::shared_ptr<GMlib::PCylinder<float>> femur;
        std::shared_ptr<GMlib::PCone<float>> tibia;
        std::vector<std::shared_ptr< GMlib::PSphere<float>>> joints;    // 3


    private:
        void makeCoxa();
        void makeFemur();
        void makeTibia();
        void makeJoints();
        void adjustPositions();
        void link();

        bool right;

};


#endif // LEG_H
