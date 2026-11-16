.PHONY: all configure run test clean
BUILD_DIR ?= build
CMAKE ?= cmake

all: configure
	$(CMAKE) --build $(BUILD_DIR) --config Release

configure:
	$(CMAKE) -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Release

run: all
	./$(BUILD_DIR)/cyber_defense

test: configure
	$(CMAKE) --build $(BUILD_DIR) --config Debug
	ctest --test-dir $(BUILD_DIR) -C Debug --output-on-failure

clean:
	$(CMAKE) -E rm -rf $(BUILD_DIR)
