#include"cube.h"

Cube::Cube(){
    width = 1.0f;
    breadth = 1.0f;
    height = 1.0f;
    constructCube();
}

Cube::Cube(GMlib::Point<float,3>pos , float width, float breadth, float height){
    this->width = width;
    this->breadth = breadth;
    this->height =height;
    constructCube();

}

void Cube::setWidth(float w){

}

void Cube::setBreadth(float b){

}

void Cube::setHeight(float h){

}

void Cube::constructCube(){


}
