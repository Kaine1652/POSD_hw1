#include "../inc/TextUI.h"
#include <iostream>

using namespace std;
// 顯示選單
void TextUI::displayMenu() {
    cout << "1. Load logic circuit file" << endl;
    cout << "2. Simulation" << endl;
    cout << "3. Display truth table" << endl;
    cout << "4. Exit" << endl;
}
// 處理用戶輸入的命令
void TextUI::processCommand() {
    int command;
    while (true){
        displayMenu();
        cout << "Command: ";
        cin >> command;
        switch (command) {
            case 1:
                CommandLoad();
                break;
            case 2:
                CommandSimulationResult();
                break;
            case 3:
                CommandTruthTable();
                break;
            case 4:
                CommandExit();
                break;
            default:
                CommandUnknown();
                break;
        }
    }
}
// 載入電路
void TextUI::CommandLoad(){
    string filepath; // 檔案路徑
    cout << "Please key in a file path: ";
    cin >> filepath;
    if(simulator.load(filepath)){
        IsFileLoaded = true;
        cout << "Circuit: " << simulator.NI << " input pins, " << simulator.NO << " output pins and " << simulator.NG << " gates\n" << endl ;
    }
    else
        cout << "File not found or file format error!!\n" << endl;
}
// 取得模擬結果
void TextUI::CommandSimulationResult(){
    if (IsFileLoaded){
        int count = simulator.NI;
        int input;
        simulator.inputs.clear();
        // 處理錯誤值
        while (count > 0){
            cout << "Please key in the value of input pin " << simulator.NI - count + 1  << ": ";
            cin >> input;
            if (input == 0 || input == 1){
                simulator.inputs.push_back(input);
                count--;
            }
            else{
                cout << "The value of input pin must be 0/1" << endl;
            }
        }
        // 顯示前半段
        string SimulationResult; // 模擬電路結果
        SimulationResult = "";
        SimulationResult += "Simulation Result:\n";
        for (int i = 0; i < simulator.NI; i++){
            SimulationResult += "i ";
        }
        SimulationResult += "| ";
        for (int i = 0; i < simulator.NO; i++){
            SimulationResult = SimulationResult + "o" + " ";
        }
        SimulationResult += "\n";
        for (int i = 0; i < simulator.NI; i++){
            SimulationResult = SimulationResult + to_string(i+1) + " ";
        }
        SimulationResult += "| ";
        for (int i = 0; i < simulator.NO; i++){
            SimulationResult = SimulationResult + to_string(i+1) + " ";
        }
        SimulationResult += "\n";
        for (int i = 0; i < simulator.NI; i++){
            SimulationResult += "--";
        }
        SimulationResult += "+";
        for (int i = 0; i < simulator.NO; i++){
            SimulationResult += "--";
        }
        SimulationResult += "\n";
        for (int i = 0; i < simulator.NI; i++){
            SimulationResult = SimulationResult + to_string(simulator.inputs[i]) + " ";
        }
        SimulationResult = SimulationResult + "| " + simulator.getSimulationResult(simulator.inputs) + "\n\n";
        cout << SimulationResult;
    }
    else
        cout << "Please load an lcf file, before using this operation.\n\n";
}
// 取得真值表
void TextUI::CommandTruthTable(){
    if (IsFileLoaded){
        // 顯示前半段
        string TruthTable;
        TruthTable = "";
        TruthTable += "Truth table:\n";
        for (int i = 0; i < simulator.NI; i++){
            TruthTable += "i ";
        }
        TruthTable += "| ";
        for (int i = 0; i < simulator.NO; i++){
            TruthTable = TruthTable + "o" + " ";
        }
        TruthTable += "\n";
        for (int i = 0; i < simulator.NI; i++){
            TruthTable = TruthTable + to_string(i+1) + " ";
        }
        TruthTable += "| ";
        for (int i = 0; i < simulator.NO; i++){
            TruthTable = TruthTable + to_string(i+1) + " ";
        }
        TruthTable += "\n";
        for (int i = 0; i < simulator.NI; i++){
            TruthTable += "--";
        }
        TruthTable += "+";
        for (int i = 0; i < simulator.NO; i++){
            TruthTable += "--";
        }
        TruthTable += "\n";
        cout << simulator.getTruthTable(TruthTable) << endl;
    }
    else
        cout << "Please load an lcf file, before using this operation.\n\n";
}
// 結束程式
void TextUI::CommandExit(){
    cout << "Goodbye, thanks for using LS." << endl;
    // 釋放記憶體
    for (Device* gate : simulator.circuit) {
        delete gate;
    }
    exit(0);
}

void TextUI::CommandUnknown(){
    cout << "Invalid command. Please try again." << endl;
}