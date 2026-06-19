#include "../inc/GateOR.h"

bool GateOR::getOutput(){
    // 輸入有1, 輸出就為1
    if (find(iPins.begin(), iPins.end(), 1) != iPins.end()){
        return 1;
    }else
        return 0;
}