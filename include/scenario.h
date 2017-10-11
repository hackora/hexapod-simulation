#ifndef SCENARIO_H
#define SCENARIO_H

class Simulator;

#include "../application/gmlibwrapper.h"

// qt
#include <QObject>


class Scenario : public GMlibWrapper {
  Q_OBJECT
public:
  using GMlibWrapper::GMlibWrapper;

  void    initializeScenario() override;
  void    cleanupScenario() override;

private:
  std::shared_ptr<Simulator> _simulator;

};

#endif // SCENARIO_H
