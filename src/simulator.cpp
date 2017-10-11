#include "simulator.h"
#include "hexapod.h"

Simulator::Simulator(GMlib::Scene& scene) : _scene{scene}{

}

void Simulator::setupSimulator(){

    _hexapod = std::make_shared< Hexapod>();
    _hexapod->toggleDefaultVisualizer();
    _hexapod->replot();
    _hexapod->setMaterial(GMlib::GMmaterial::blackPlastic(),GMlib::GMmaterial::sapphire(),
                                     GMlib::GMmaterial::ruby(),GMlib::GMmaterial::blackRubber(),GMlib::GMmaterial::snow());
    _hex_controller = Hexapod_controller();
    double dt = 0.016;
    _scene.enabledFixedDt();
    _scene.setFixedDt(dt);
    insert_to_scene(_hexapod);
    _hex_controller.addHexapod(_hexapod);
    _scene.insert(&_hex_controller);
}
