APP_NAME = geometry
LIB_NAME = libgeometry
TEST_NAME = geometry_test

TFLAG = -I thirdparty
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
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.$(SRC_EXT),$(OBJ_DIR)/test/%.o,$(TEST_SOURCES))

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.$(SRC_EXT)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(LIB_PATH)
	rm $(APP_OBJECTS)
	rm $(LIB_OBJECTS)
	rm $(DEPS)
	rm $(APP_PATH)
	rm $(TEST_PATH)
	rm $(TEST_OBJECTS)




.PHONY: test
test: $(TEST_PATH) $(LIB_PATH)
	$(TEST_PATH)

$(TEST_PATH): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(OBJ_DIR)/$(TEST_DIR)/main.o: $(TEST_DIR)/main.c
	$(CC) -c $(TFLAG) $(CFLAGS) $(CPPFLAGS) $< -o $@

$(OBJ_DIR)/$(TEST_DIR)/tests.o: $(TEST_DIR)/tests.c
	$(CC) -c $(TFLAG) $(CFLAGS) $(CPPFLAGS) $< -o $@


