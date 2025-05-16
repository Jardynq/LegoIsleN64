SOURCE_DIR=src
BUILD_DIR=build
ASSET_DIR=assets

V=1
#include $(N64_INST)/include/n64.mk
include 3rdparty/libdragon/n64.mk
include $(N64_INST)/include/t3d.mk

# Grab include dirs from mips-g++ and add them to compile_commands.json
INCLUDE := $(shell $(N64_CXX) -E -x c++ - -v 2>&1 < /dev/null | \
             sed -n '/#include <...> search starts here:/,/End of search list./p' | \
             grep ' /' | tr -d ' ')
CXXFLAGS += $(patsubst %,-I%, $(INCLUDE))
CXXFLAGS += $(patsubst %,-I%,$(shell find $(SOURCE_DIR)/isle -type d))
CXXFLAGS += $(patsubst %,-I%,$(shell find $(SOURCE_DIR)/omni -type d))
CXXFLAGS += -I$(SOURCE_DIR)
CXXFLAGS += -I$(SOURCE_DIR)/tests
CXXFLAGS += -I3rdparty/vec 

CXXFLAGS += -include $(SOURCE_DIR)/global.h
#CXXFLAGS += -NDEBUG

%.z64: N64_CXXFLAGS:=$(filter-out -Werror,$(N64_CXXFLAGS))

include Makeassets
include Maketests

#SRCS := $(shell find $(SOURCE_DIR) -type f -name '*.cpp')
#OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(subst $(SOURCE_DIR)/,,$(SRCS)))
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/legofs.o

isle: isle.z64
isle.z64: N64_ROM_TITLE="LegoIsleN64"
isle.z64: $(BUILD_DIR)/isle.dfs $(BUILD_DIR)/isle.elf
$(BUILD_DIR)/isle.elf: $(OBJS)
$(BUILD_DIR)/isle.dfs: $(BUILD_DIR)/assets.stamp
	@mkdir -p $(BUILD_DIR)/assets_isle/cursors
	@mkdir -p $(BUILD_DIR)/assets_isle/data
	@mkdir -p $(BUILD_DIR)/assets_isle/scripts

	@cp -r $(BUILD_DIR)/assets/cursors/* $(BUILD_DIR)/assets_isle/cursors/
	@cp -r $(BUILD_DIR)/assets/data/* $(BUILD_DIR)/assets_isle/data/
	@cp -r $(BUILD_DIR)/assets/scripts/infocntr/infomain.si \
		   $(BUILD_DIR)/assets_isle/scripts/infocntr/infomain.si

	@mkdfs $@ $(BUILD_DIR)/assets_isle

bear:
	@bear -- $(MAKE) -j -B tests --ignore-errors

clean:
	@rm -f *.z64
	@rm -rf $(BUILD_DIR)/*
	@rm -rf bin/*
	@$(MAKE) -C 3rdparty/LegoIsleN64-legofs clean

all: isle tests
.PHONY: all clean bear

-include $(wildcard $(BUILD_DIR)/*.d)
