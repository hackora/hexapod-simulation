#include"cube.h"

Cube::Cube(){
    width = 1.0f;
    breadth = 1.0f;
    height = 1.0f;
    pos = GMlib::Point<float,3>(0.0f,0.0f,0.0f);
    makeCube();
}

Cube::Cube(GMlib::Point<float,3>pos , float width, float breadth, float height){
    this->width = width;
    this->breadth = breadth;
    this->height =height;
    this->pos = pos;
    makeCube();

}

Cube::Cube(const Cube& copy){

    width = copy.width;
    breadth = copy.breadth;
    height = copy.height;
    pos = copy.pos;
    planes = copy.planes;
}

void Cube::setWidth(float w){
    width = w;
}

void Cube::setBreadth(float b){
    breadth =b;
}

void Cube::setHeight(float h){
    height =h;
}

void Cube::makeCube(){

    planes.push_back(std::make_unique<Plane>(
                         pos + GMlib::Vector<float,3>(0.5*breadth, 0.5*width, -0.5*height),
                          GMlib::Vector<float,3>(0.0f, -width, 0.0f),
                          GMlib::Vector<float,3>(-breadth, 0.0f, 0.0f)));

    planes.push_back(std::make_shared<Plane>(
                         pos + GMlib::Vector<float,3>(0.5*breadth, 0.5*width, 0.5*height),
                         GMlib::Vector<float,3>(0.0f, -width, 0.0f),
                         GMlib::Vector<float,3>(-breadth, 0.0f, 0.0f)));

     planes.push_back(std::make_shared<Plane>(
                          pos + GMlib::Vector<float,3>(0.5*breadth, 0.5*width, -0.5*height),
                          GMlib::Vector<float,3>(0.0f, -width, 0.0f),
                          GMlib::Vector<float,3>(0.0, 0.0f, height)));

     planes.push_back(std::make_shared<Plane>(
                          pos + GMlib::Vector<float,3>(0.5*breadth, 0.5*width, -0.5*height),
                          GMlib::Vector<float,3>(-breadth, 0.0f, 0.0f),
                          GMlib::Vector<float,3>(0.0f, 0.0f, height)));

     planes.push_back(std::make_shared<Plane>(
                          pos + GMlib::Vector<float,3>(-0.5*breadth, -0.5*width, -0.5*height),
                          GMlib::Vector<float,3>(0.0f,width, 0.0f),
                          GMlib::Vector<float,3>(0.0f, 0.0f, height)));

     planes.push_back(std::make_shared<Plane>(
                          pos +GMlib::Vector<float,3>(-0.5*breadth, -0.5*width, -0.5*height),
                          GMlib::Vector<float,3>(breadth, 0.0f, 0.0f),
                          GMlib::Vector<float,3>(0.0f, 0.0f, height)));

}

void Cube::setMaterial(const GMlib::Material& m){

    for(auto& it:planes){
        it->setMaterial(m);
    }
}

void Cube::replot(int m1, int m2, int d1, int d2){

    for(auto& it:planes){
        it->replot(m1,m2,d1,d2); 
    }
}

void Cube::toggleDefaultVisualizer(){

    for(auto& it:planes){
        it->toggleDefaultVisualizer();
    }
}

void Cube::insertToScene(const std::shared_ptr<GMlib::Scene>& scene) {

    for(auto& it:planes){
        scene->insert(it.get());
    }
}
