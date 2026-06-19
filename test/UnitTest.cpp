#include <gtest/gtest.h>
#include "../inc/TextUI.h"
#include <iostream>

using namespace std;

class DeviceTest : public ::testing::Test {
protected:
    Device* gate;

    void SetUp() override {
        gate = nullptr;
    }

    void TearDown() override {
        delete gate;
    }

    void GateOutputTest(Device* gate, const vector<int>& pins, int expectedOutput) {
        gate->iPins = pins;
        EXPECT_EQ(gate->getOutput(), expectedOutput);
    }
};

TEST_F(DeviceTest, ANDGateTests) {
    gate = new GateAND;
    GateOutputTest(gate, {0, 0}, 0);
    GateOutputTest(gate, {0, 1}, 0);
    GateOutputTest(gate, {1, 0}, 0);
    GateOutputTest(gate, {1, 1}, 1);
}

TEST_F(DeviceTest, ORGateTests) {
    gate = new GateOR;
    GateOutputTest(gate, {0, 0}, 0);
    GateOutputTest(gate, {0, 1}, 1);
    GateOutputTest(gate, {1, 0}, 1);
    GateOutputTest(gate, {1, 1}, 1);
}

TEST_F(DeviceTest, NOTGateTests) {
    gate = new GateNOT;
    GateOutputTest(gate, {0}, 1);
    GateOutputTest(gate, {1}, 0);
}

class LogicSimulatorTest : public ::testing::Test {
protected:
    LogicSimulator simulator;
    string valid_filepath = "../testfile/file1.lcf";
    string invalid_filepath = "../testfile/xxxxx.lcf";

    void TearDown() override {
        for (Device* gate : simulator.circuit) {
            delete gate;
        }
        simulator.circuit.clear();
    }
};

TEST_F(LogicSimulatorTest, Load) {
    EXPECT_FALSE(simulator.load(invalid_filepath));
    ASSERT_TRUE(simulator.load(valid_filepath));
    EXPECT_EQ(simulator.NI, 3);
    EXPECT_EQ(simulator.NO, 1);
    EXPECT_EQ(simulator.NG, 3);
}

TEST_F(LogicSimulatorTest, GetSimulationResult) {
    ASSERT_TRUE(simulator.load(valid_filepath));

    struct TestData {
        vector<int> inputs;
        string expectedOutput;
    };

    vector<TestData> testCases = {
        {{0, 0, 0}, "0"},
        {{0, 1, 0}, "0"},
        {{0, 1, 1}, "0"},
        {{1, 0, 0}, "1"},
        {{1, 0, 1}, "1"},
        {{1, 1, 0}, "0"},
        {{1, 1, 1}, "0"}
    };

    for (const auto& testCase : testCases) {
        EXPECT_EQ(simulator.getSimulationResult(testCase.inputs), testCase.expectedOutput);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}