CC = g++
#CXXFLAGS = -Wall -g -std=c++17 -O2
LDFLAGS = -lgtest -lgtest_main -pthread
TARGETS = main ../test/UnitTest

COMMON_SRCS = LogicSimulator.cpp TextUI.cpp GateAND.cpp GateNOT.cpp GateOR.cpp
main_SRCS = main.cpp 
UnitTest_SRCS = ../test/UnitTest.cpp 

# 生成對應文件列表
main_OBJS = $(COMMON_SRCS:.cpp=.o) $(main_SRCS:.cpp=.o)
UnitTest_OBJS = $(COMMON_SRCS:.cpp=.o) $(UnitTest_SRCS:.cpp=.o)

# 編譯所有目標
all: $(TARGETS)

# 生成 main 可執行文件
main: $(main_OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(main_OBJS)

# 生成 UnitTest 可執行文件
../test/UnitTest: $(UnitTest_OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(UnitTest_OBJS) $(LDFLAGS)

# 編譯對應文件
%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

# 清理中間文件和可執行文件
clean:
	del /q *.o
#	del /q main.exe
#	del /q "../test/UnitTest.exe"
	del /q "../test/*.o"