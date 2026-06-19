#include "../inc/GateAND.h"

bool GateAND::getOutput(){
    // 輸入有0, 輸出就為0
    if (find(iPins.begin(), iPins.end(), 0) != iPins.end()){
        return 0;
    }else
        return 1;
}