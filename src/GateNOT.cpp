#include "../inc/GateNOT.h"

bool GateNOT::getOutput(){
    // 反轉初始值
    return !iPins[0];
}