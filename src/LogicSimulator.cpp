#include "../inc/LogicSimulator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

// gate type (1: AND, 2: OR, 3: NOT)
// 載入電路(1)
bool LogicSimulator::load(const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        return false;
    }
    string line;
    int lineNumber = 0;
    int x = 1;
    //釋出記憶體
    for (Device* gate : circuit) {
        delete gate;
    }
    circuit.clear();
    while (getline(file, line)) {
        stringstream ss(line);
        if (lineNumber == 0) { 
            ss >> NI;
        } else if((lineNumber == 1)){
            ss >> NG;
        }
        else {
            int gateType;
            ss >> gateType;

            Device* gate = nullptr;
            if (gateType == 1) {
                gate = new GateAND();
            } else if (gateType == 2) {
                gate = new GateOR();
            } else if (gateType == 3) {
                gate = new GateNOT();
            }
            if (gate) {
                string conn;
                gate->ID = x;
                // 到0停止
                while (ss >> conn && conn != "0") {
                    gate->connections.push_back(conn);
                    gate->iPins.push_back(-1);
                }
                circuit.push_back(gate);
                x++;
            }
        }
        lineNumber++;
    }
    //計算輸出個數
    string FinishGateID;
    NO = NG;

    for (int i = 0; i < circuit.size(); i++) {
        if (!circuit[i]->IsOutput) {
            continue;
        }
        FinishGateID = to_string(circuit[i]->ID) + ".1";
        for (int j = 0; j < circuit.size(); j++) {
            if (find(circuit[j]->connections.begin(), circuit[j]->connections.end(), FinishGateID) != circuit[j]->connections.end()) {
                circuit[i]->IsOutput = false;
                NO--;
                break;
            }
        }
    }
    return true;
}
//取得模擬結果(2)
string LogicSimulator::getSimulationResult(vector<int> Inputs) {
    // 前處理 // 賦予有"-"的值(連接電路輸入), 其餘為-1
    for (auto& gate : circuit) {
        gate->Finish = false;
        for (int i = 0; i < gate->iPins.size(); i++) {
            gate->iPins[i] = -1;
            string connection = gate->connections[i];
            if (connection.find("-") != string::npos) {
                int conn_temp = stoi(connection);
                gate->iPins[i] = Inputs[-conn_temp - 1];
            }
        }
    }
    //處理輸出
    bool IsAllBinary; // 判斷邏輯閘輸入是否都為0或1
    int ExecutionCount = NG; // 執行次數
    while (ExecutionCount--){
        for (int i = 0; i < circuit.size(); i++){
            IsAllBinary = find(circuit[i]->iPins.begin(), circuit[i]->iPins.end(), -1) == circuit[i]->iPins.end();
            // 是否已經完成並輸出、邏輯閘輸入是否都為0或1
            if (circuit[i]->Finish == false && IsAllBinary == true){
                ProcessResult(circuit[i]);
            }
        }
    }
    // 寫入輸出
    output = "";
    for (int i = 0; i < circuit.size(); i++){
        if(circuit[i]->IsOutput){
            output = output + to_string(circuit[i]->oPin) + " ";
        }
    }
    output.pop_back();
    return output;
}
//處理輸出
void LogicSimulator::ProcessResult(Device* gate){
    string FinishGateID; // 已完成邏輯閘編號
    gate->oPin = gate->getOutput();
    gate->Finish = true;
    // 將已完成的邏輯閘輸出到其他iPins
    FinishGateID = to_string(gate->ID) + ".1";
    for (int i = 0; i < circuit.size(); i++){
        for (int j = 0; j < circuit[i]->connections.size(); j++){
            if(circuit[i]->connections[j] == FinishGateID){
                circuit[i]->iPins[j] = gate->oPin;
            }
        }
    }
}
// 取得真值表(3)
string LogicSimulator::getTruthTable(string TruthTable) {
    // 從0開始帶入getSimulationResult()以取得輸出
    int maxNumber = (1 << NI);
    string binary;
    for (int i = 0; i < maxNumber; ++i) {
        inputs.clear();
        binary = toBinary(i, NI);
        for (int j = 0; j < NI; j++){
            inputs.push_back(binary[j] - '0');
            TruthTable = TruthTable + to_string(inputs[j]) + " ";
        }
        TruthTable = TruthTable + "| " + getSimulationResult(inputs) + "\n";
    }
    return TruthTable;
}
// 轉二進制
string LogicSimulator::toBinary(int number, int numBits) {
    string binary(numBits, '0');
    for (int i = 0; i < numBits; i++) {
        if ((number >> (numBits - 1 - i)) & 1) {
            binary[i] = '1';
        }
    }
    return binary;
}
