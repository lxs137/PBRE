CC = g++
# CXXFLAGS = --std=c++11 -Wall -Wfloat-equal -Weffc++ -O3
CXXFLAGS = --std=c++11 -Wall -Wfloat-equal -Weffc++ -ggdb3
LDFLAGS = -L /usr/local/lib
SRC_DIR = src
INCLUDE_DIR = include
TARGET_DIR = target
SRCS = $(shell find $(SRC_DIR) -name "*.cpp")
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(TARGET_DIR)/%.o)
HEADERS = $(shell find $(INCLUDE_DIR) -name "*.h")
BIN = engine

ifndef tag
tag = $(shell date +%Y/%m/%d-%R)
endif

# For Test
# Make Sure That GoogleTest Headers Exist
GTEST_INCLUDE_DIR = /usr/local/opt/googletest/include
# Make Sure That Googletest Obj Exist
GTEST_OBJ = /usr/local/opt/googletest/libgtest.a
TEST_DIR = test
TEST_TARGET_DIR = target-test
TEST_SRCS = $(shell find $(TEST_DIR) -name "*.cpp")
OBJS_EXCLUDE_MAIN = $(shell echo $(OBJS) | sed 's/target\/main.o//g')
TEST_BIN = unittest

default_target: help
.PHONY : default_target

$(TARGET_DIR)/%.o : $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CXXFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

engine : dir $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN)
.PHONY : engine

dir :
	@mkdir -p $(TARGET_DIR)
	@mkdir -p $(TEST_TARGET_DIR)
.PHONY : dir

memcheck : engine
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions="${VALGRIND_SUPP}" $(BIN)
.PHONY : memcheck

clean :
	rm -rf $(TARGET_DIR)
	rm -rf $(TEST_TARGET_DIR)
	rm -f $(BIN)
	rm -rf $(BIN).dSYM
	rm -f $(TEST_BIN)
	rm -rf $(TEST_BIN).dSYM
.PHONY : clean

stats :
	find $(TEST_DIR) $(SRC_DIR) $(INCLUDE_DIR) -name "*.cpp" -o -name "*.h" | xargs wc -l
.PHONY : stats

commit : clean
	git add .
	git commit -m "$(tag)"
	git push
.PHONY : commit

help :
	@echo "Some Valid Targets For This Makefile:"
	@echo "... engine"
	@echo "... clean"
	@echo "... stats"
	@echo "... tag=\"\" commit"
.PHONY : help