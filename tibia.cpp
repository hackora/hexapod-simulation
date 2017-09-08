#include"tibia.h"

Tibia::Tibia(GMlib::Vector<float,3> pos){
    // Start values
    radius = 1.0f;
    height = 2.0f;
    position = pos;
}

void Tibia::setRadius(float r)
{
    this->radius = r;
}

void Tibia::setHeight(float h){

    this->height = h;
}

void Tibia::insertPyramid(const std::shared_ptr<GMlib::Scene>& s){

    auto pyramid = new GMlib::PCone<float>(radius, height);
    pyramid->toggleDefaultVisualizer();
    pyramid->replot(4, 4, 1, 1);                               // 4 vertex gives a pyramid shape
    pyramid->setMaterial(GMlib::GMmaterial::ruby());
    pyramid->translateGlobal(position);
    s->insert(pyramid);

}
