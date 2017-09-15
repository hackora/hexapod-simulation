#include"cube.h"

Cube::Cube(){
    width = 1.0f;
    breadth = 1.0f;
    height = 1.0f;
    pos = GMlib::Point<float,3>(0.0f,0.0f,0.0f);
    constructCube();
}

Cube::Cube(GMlib::Point<float,3>pos , float width, float breadth, float height){
    this->width = width;
    this->breadth = breadth;
    this->height =height;
    this->pos = pos;
    constructCube();

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

void Cube::constructCube(){

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

/*! HqMatrix<float,3>& Camera::getMatrix()
 *  \brief Pending Documentation
 *
 *  Pending Documentation
 */
GMlib::HqMatrix<float,3>& Cube::getMatrix() {

  /*! \todo fix how the matrix is returned */
  static GMlib::HqMatrix<float,3> retmat;
  retmat = _matrix;
  retmat.invertOrthoNormal();
  return retmat;
}


const GMlib::HqMatrix<float,3>& Cube::getMatrix() const {

  /*! \todo fix how the matrix is returned */
  static GMlib::HqMatrix<float,3> retmat;
  retmat = _matrix;
  retmat.invertOrthoNormal();
  return retmat;
}

inline
void Cube::basisChange( const GMlib::Vector<float,3>& x, const GMlib::Vector<float,3>& y,
                                                  const GMlib::Vector<float,3>& z, const GMlib::Vector<float,3>& p ) {

    static GMlib::Vector<float,4> nx, ny, nz, nw(0.0f);
    nx = -x;
    ny =  y;
    nz = -z;

    nx[3] = x*p;
    ny[3] = -(y*p);
    nz[3] = z*p;
    nw[3] = 1.0f;

    _matrix.setRow( nx, 0 );
    _matrix.setRow( ny, 1 );
    _matrix.setRow( nz, 2 );
    _matrix.setRow( nw, 3 );
  }
