#ifndef LOGICSIMULATOR_H
#define LOGICSIMULATOR_H

#include "GateAND.h"
#include "GateOR.h"
#include "GateNOT.h"
class LogicSimulator {
private:
    string output; // 電路輸出
    string toBinary(int number, int numBits); // 轉二進制
    void ProcessResult(Device* gate); //處理輸出
public:
    vector<Device*> circuit; // 儲存全部邏輯閘
    int NI; // 輸入個數
    int NG; // 邏輯閘個數
    int NO = 0; // 輸出個數
    vector<int> inputs;
    bool load(const string& filepath); // 載入電路
    string getSimulationResult(vector<int> inputs); // 取得模擬結果
    string getTruthTable(string TruthTable); // 取得真值表
};

#endif