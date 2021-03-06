#ifndef SCENARIO_H
#define SCENARIO_H

class Simulator;
class Hexapod_controller;

#include "../application/gmlibwrapper.h"

// qt
#include <QObject>
#include<QImage>

class Scenario : public GMlibWrapper {
  Q_OBJECT
public:
  using GMlibWrapper::GMlibWrapper;

  void     setTexture(QImage img);
  void    initializeScenario() override;
  void    cleanupScenario() override;

  void      deleteHexapod();

private:
  std::shared_ptr<Simulator> _simulator;
  QImage                                        _img;


};

#endif // SCENARIO_H
