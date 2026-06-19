#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Device {
public:
    vector<int> iPins; // 連接腳位的布林值
    int oPin = -1; // 邏輯閘輸出(只會有一個)
    int ID; // 邏輯閘編號
    vector<string> connections; // 連接腳位
    bool Finish = false; // 判斷是否已得到輸出
    bool IsOutput = true; // 判斷是否為電路輸出
    virtual bool getOutput() = 0; // 取得邏輯閘輸出
};

#endif