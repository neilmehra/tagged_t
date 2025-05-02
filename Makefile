CMAKE        ?= cmake
CMAKE_ARGS   ?= -DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX)
BUILD_DIR    := build
STAMP_FILE   := $(BUILD_DIR)/CMakeCache.txt

.PHONY: all build test run clean

all: build test

$(STAMP_FILE):
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CMAKE) $(CMAKE_ARGS) ..

build: $(STAMP_FILE)
	cmake --build $(BUILD_DIR)

test: build
	cd $(BUILD_DIR) && ctest --output-on-failure

clean:
	rm -rf $(BUILD_DIR)
