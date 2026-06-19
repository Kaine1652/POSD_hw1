#ifndef GATEAND_H
#define GATEAND_H

#include "Device.h"

class GateAND : public Device {
public:
    bool getOutput() override;
};

#endif