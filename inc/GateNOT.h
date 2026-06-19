#ifndef GATENOT_H
#define GATENOT_H

#include "Device.h"

class GateNOT : public Device {
public:
    bool getOutput() override;
};

#endif