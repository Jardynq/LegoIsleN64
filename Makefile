SOURCE_DIR=src
BUILD_DIR=build
ASSET_DIR=assets

# TODO: Currently only support INFOMAIN.SI
scripts = Infocntr/INFOMAIN.SI

V=1
include $(N64_INST)/include/n64.mk
include $(N64_INST)/include/t3d.mk

# Grab include dirs from mips-g++ and add them to compile_commands.json
INCLUDE := $(shell $(N64_CXX) -E -x c++ - -v 2>&1 < /dev/null | \
             sed -n '/#include <...> search starts here:/,/End of search list./p' | \
             grep ' /' | tr -d ' ')
CXXFLAGS += $(patsubst %,-I%, $(INCLUDE))
CXXFLAGS += -Isrc
CXXFLAGS += $(patsubst %,-I%,$(shell find src/lego -type d))
CXXFLAGS += $(patsubst %,-I%,$(shell find src/omni -type d))
CXXFLAGS += $(patsubst %,-I%,$(shell find src/tgl -type d))
CXXFLAGS += $(patsubst %,-I%,$(shell find src/realtime -type d))
CXXFLAGS += $(patsubst %,-I%,$(shell find src/modeldb -type d))
CXXFLAGS += $(patsubst %,-I%,$(shell find src/viewmanager -type d))
CXXFLAGS += $(patsubst %,-I%,$(shell find src/mxdirectx -type d))
CXXFLAGS += $(patsubst %,-I%,$(shell find src/mxgeometry -type d))

CXXFLAGS += -I3rdparty/vec 
CXXFLAGS += -I3rdparty/libsmacker 

CXXFLAGS += -include $(SOURCE_DIR)/global.h
#CXXFLAGS += -NDEBUG

#SRCS := $(wildcard $(SOURCE_DIR)/**/*.cpp $(SOURCE_DIR)/*.cpp)
#OBJS := $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/legofs.o

isle.z64: N64_ROM_TITLE="LegoIsleN64"
isle.z64: $(BUILD_DIR)/isle.dfs $(BUILD_DIR)/isle.elf
$(BUILD_DIR)/isle.elf: $(OBJS)

asset_test.z64: N64_ROM_TITLE="LegoIsleN64"
asset_test.z64: $(BUILD_DIR)/isle.dfs $(BUILD_DIR)/asset_test.elf
$(BUILD_DIR)/asset_test.elf: $(BUILD_DIR)/asset_test.o $(BUILD_DIR)/legofs.o

clean:
	rm -rf $(BUILD_DIR)/* isle.z64

all: isle.z64
.PHONY: all clean

-include $(wildcard $(BUILD_DIR)/*.d)


$(BUILD_DIR)/isle.dfs:
# Build the sidump tool
	$(MAKE) -j4 -C 3rdparty/LegoIsleN64-legofs
	cp 3rdparty/LegoIsleN64-legofs/sidump $(BUILD_DIR)/sidump

# Make top level folders lowercase
	echo "Making top level folders lowercase"
	@for file in $(ASSET_DIR)/*; do \
		dir=$$(dirname "$$file"); \
		name=$$(basename "$$file"); \
		lower=$$(echo "$$name" | tr '[:upper:]' '[:lower:]'); \
		if [ "$$name" != "$$lower" ]; then \
			temp="$$(mktemp -d)"; \
			mv -T "$$dir/$$name" "$$temp"; \
			mv -T "$$temp" "$$dir/$$lower"; \
		fi; \
	done

# Check for missing assets
	@missing=""
	@for dir in $($(ASSET_DIR)/cursors $(ASSET_DIR)/data $(ASSET_DIR)/scripts); do \
	 	if [ ! -d "$$dir" ]; then \
	 		missing="$$missing$$dir/ is missing.\n"; \
	 	elif [ -z "$$(find $$dir -type f 2>/dev/null)" ]; then \
	 		missing="$$missing$$dir is empty.\n"; \
	 	fi; \
	done; \
	if [ -n "$$missing" ]; then \
		echo ""; \
		echo "Error: missing assets!"; \
		echo -n "$$missing"; \
		echo "Within a legitimate game installation, you should find a folder called 'LEGO'."; \
		echo "Copy the contents of that folder into the 'assets' folder try building again."; \
		echo ""; \
		exit 1; \
	fi

# Create a skeleton directory for the DFS
	@echo "Creating dfs skeleton"
	find $(ASSET_DIR) -type d -exec mkdir -p $(BUILD_DIR)/{} \;

# Convert cursor files
	@echo "Converting cursor files"
	@for file in "$(ASSET_DIR)/cursors"/*; do \
		echo "Processing "$$file""; \
		mksprite -c 1 -f RGBA16 -o "$(BUILD_DIR)/$(ASSET_DIR)/cursors/" "$$file"; \
	done

# Compress data files
	@echo "Compressing data files"
	@for file in "$(ASSET_DIR)/data"/*; do \
		echo "Processing $$file"; \
		mkasset -c 1 -o "$(BUILD_DIR)/$(ASSET_DIR)/data/" "$$file"; \
	done

# Convert script files
	@echo "Converting script files"
	@for script in $(scripts); do \
		script_dir="$(BUILD_DIR)/$(ASSET_DIR)/scripts/$$script"; \
		temp_dir="$$(mktemp -d)"; \
		mkdir -p $$script_dir; \
		\
		echo "Processing $$script"; \
		$(BUILD_DIR)/sidump "$$temp_dir" "$(ASSET_DIR)/scripts/$$script"; \
		\
		echo "Converting embedded bitmaps"; \
		for file in $$temp_dir/*.bmp; do \
			out="$${file%.bmp}.png"; \
			ffmpeg -hide_banner -loglevel error -y -i "$$file" "$$out"; \
			mksprite -c 1 -f RGBA16 -o "$$script_dir" "$$out"; \
			rm "$$file" "$$out"; \
		done; \
		\
		echo "Converting embedded wave files"; \
		for file in $$temp_dir/*.wav; do \
			audioconv64 --wav-compress 1 -o "$$script_dir" "$$file"; \
			rm "$$file"; \
		done; \
		\
		vf_scaledown="scale=trunc(iw/32)*32:trunc(ih/16)*16"; \
		echo "Converting embedded flc files"; \
		for file in $$temp_dir/*.flc; do \
			out="$${file%.flc}.m1v"; \
			ffmpeg -hide_banner -loglevel error -y -i "$$file" \
				-vf "$$vf_scaledown" -vb 800K \
				-c:v mpeg1video -an -r 24 "$$out"; \
			mv "$$out" "$$script_dir"; \
			rm "$$file"; \
		done; \
		for file in $$temp_dir/*.pho; do \
			out="$${file%.pho}.m1v"; \
			ffmpeg -hide_banner -loglevel error -y -i "$$file" \
				-vf "$$vf_scaledown,vflip" -vb 800K \
				-c:v mpeg1video -an -r 24 "$$out"; \
			mv "$$out" "$$script_dir"; \
			rm "$$file"; \
		done; \
		\
		echo "Converting embedded smacker files"; \
		for file in $$temp_dir/*.smk; do \
			out_vid="$${file%.smk}.m1v"; \
			out_wav="$${file%.smk}.wav"; \
			ffmpeg -hide_banner -loglevel error -y -i "$$file" \
				-vf "$$vf_scaledown" -vb 800K \
				-c:v mpeg1video -an -r 24 "$$out_vid"; \
			mv "$$out_vid" "$$script_dir"; \
			\
			has_audio=$(ffprobe -v error -select_streams a \
				-show_entries stream=codec_type -of csv=p=0 "$file"); \
			if [ "$$has_audio" = "audio" ]; then \
				ffmpeg -hide_banner -loglevel error \
					-y -i "$$file" -vn -acodec pcm_s16le -ar 32000 -ac 1 "$$out_wav"; \
				audioconv64 --wav-compress 1 -o "$$script_dir" "$$out_wav"; \
				rm "$$out_wav"; \
			fi; \
			rm "$$file"; \
		done; \
		\
		echo "Converting remaining files"; \
		for file in $$temp_dir/*; do \
			mkasset -c 1 -o "$$script_dir" "$$file"; \
		done; \
		for file in $$temp_dir/*.*; do \
			mv "$$file" "$${file%.*}"; \
			mkasset -c 1 -o "$$script_dir" "$${file%.*}"; \
		done; \
		\
		# TODO the rest......; \
		\
		rm -r "$$temp_dir"; \
	done

# Create the DFS
	@echo "Creating DFS"
	mkdfs $@ $(BUILD_DIR)/$(ASSET_DIR)
