SOURCE_DIR=src
BUILD_DIR=build
ASSET_DIR=assets

V=1
include $(N64_INST)/include/n64.mk
include $(N64_INST)/include/t3d.mk

LEGOFS=$(BUILD_DIR)/legofs.dfs
include Makeassets

# Grab include dirs from mips-g++ and add them to compile_commands.json
INCLUDE := $(shell $(N64_CXX) -E -x c++ - -v 2>&1 < /dev/null | \
             sed -n '/#include <...> search starts here:/,/End of search list./p' | \
             grep ' /' | tr -d ' ')
CXXFLAGS += $(patsubst %,-I%, $(INCLUDE))
CXXFLAGS += $(patsubst %,-I%,$(shell find $(SOURCE_DIR)/isle -type d))
CXXFLAGS += -I$(SOURCE_DIR)
CXXFLAGS += -I$(SOURCE_DIR)/tests
CXXFLAGS += -I3rdparty/vec 

CXXFLAGS += -include $(SOURCE_DIR)/global.h
#CXXFLAGS += -NDEBUG

#SRCS := $(wildcard $(SOURCE_DIR)/**/*.cpp $(SOURCE_DIR)/*.cpp)
#OBJS := $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/legofs.o

isle: isle.z64
isle.z64: N64_ROM_TITLE="LegoIsleN64"
isle.z64: $(LEGOFS) $(BUILD_DIR)/isle.elf
$(BUILD_DIR)/isle.elf: $(OBJS)

tests: test_assets.z64

test_assets.z64: $(LEGOFS) $(BUILD_DIR)/test_assets.elf
$(BUILD_DIR)/test_assets.elf: $(BUILD_DIR)/tests/test_assets.o $(BUILD_DIR)/legofs.o

clean:
	@rm -f *.z64
	@rm -rf $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)

all: isle tests
.PHONY: all clean

-include $(wildcard $(BUILD_DIR)/*.d)
