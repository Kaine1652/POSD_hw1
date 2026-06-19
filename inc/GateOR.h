#ifndef GATEOR_H
#define GATEOR_H

#include "Device.h"

class GateOR : public Device {
public:
    bool getOutput() override;
};

#endif