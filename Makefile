APP_NAME = geometry
LIB_NAME = libgeometry
TEST_NAME = geometry_test

TFLAG = -I thirdparty
LMFLAG = -lm
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I src -MMD
CC = gcc

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = test

APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a
TEST_PATH = $(BIN_DIR)/$(TEST_NAME)

SRC_EXT = c

APP_SOURCES = $(wildcard $(SRC_DIR)/$(APP_NAME)/*.$(SRC_EXT))
APP_OBJECTS := $(patsubst $(SRC_DIR)/%.$(SRC_EXT),$(OBJ_DIR)/$(SRC_DIR)/%.o,$(APP_SOURCES))

LIB_SOURCES = $(wildcard $(SRC_DIR)/$(LIB_NAME)/*.$(SRC_EXT))
LIB_OBJECTS := $(patsubst $(SRC_DIR)/%.$(SRC_EXT),$(OBJ_DIR)/$(SRC_DIR)/%.o,$(LIB_SOURCES))

TEST_SOURCES = $(wildcard $(TEST_DIR)/*.$(SRC_EXT))
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.$(SRC_EXT),$(OBJ_DIR)/$(TEST_DIR)/%.o,$(TEST_SOURCES))

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LMFLAG)

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.$(SRC_EXT)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: test
test: $(TEST_PATH)
	$(TEST_PATH)

$(TEST_PATH): $(TEST_OBJECTS) $(LIB_PATH)
	$(CC) $(TFLAG) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LMFLAG)

$(OBJ_DIR)/$(TEST_DIR)/main.o: $(TEST_DIR)/main.c
	$(CC) $(TFLAG) $(CFLAGS) $(CPPFLAGS) -c -o $@ $^

$(OBJ_DIR)/$(TEST_DIR)/tests.o: $(TEST_DIR)/tests.c
	$(CC) $(TFLAG) $(CFLAGS) $(CPPFLAGS) -c -o $@ $^

.PHONY: clean
clean:
	rm -rf $(LIB_PATH)
	rm -rf $(APP_OBJECTS)
	rm -rf $(LIB_OBJECTS)
	rm -rf $(APP_PATH)
	rm -rf $(TEST_PATH)
	rm -rf $(TEST_OBJECTS)
	rm -rf $(DEPS)