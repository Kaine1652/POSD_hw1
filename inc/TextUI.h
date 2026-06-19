#ifndef TEXTUI_H
#define TEXTUI_H

#include "LogicSimulator.h"

class TextUI {
private:
    LogicSimulator simulator;
    bool IsFileLoaded = false; // 判斷是否已經導入
public:
    void displayMenu(); // 顯示選單
    void processCommand(); // 處理用戶輸入的命令
    void CommandLoad();
    void CommandSimulationResult();
    void CommandTruthTable();
    void CommandExit();
    void CommandUnknown();
};

#endif