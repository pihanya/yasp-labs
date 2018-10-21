#=====================BEGIN OF ARGUMENTS=====================

# Project home directory
HOME_DIR=$(PWD)

# Executable file name
MAIN_ASM=test.asm
MAIN_COMPILED=test.o
MAIN_EXECUTABLE=test

# Flags using during commands execution
PYTHON_FLAGS=
NASM_FLAGS=-felf64
TEST_FILES=lib.inc test.py termcolor.pyc

#======================END OF ARGUMENTS======================

OUT_DIR=$(HOME_DIR)/out
SRC_DIR=$(HOME_DIR)/

# Create work directories
create:
	mkdir -pv $(OUT_DIR)

# Clean output
clean:
	rm -rfv $(OUT_DIR)

# Initialize
init: clean create
	cd $(HOME_DIR)

# Compile file
compile: init
	nasm $(NASM_FLAGS) $(HOME_DIR)/$(MAIN_ASM) -o $(OUT_DIR)/$(MAIN_COMPILED)
	ld -o $(OUT_DIR)/$(MAIN_EXECUTABLE) $(OUT_DIR)/$(MAIN_COMPILED)

# Test code
test: init
	cd $(HOME_DIR) && cp $(TEST_FILES) $(OUT_DIR)/
	cd $(OUT_DIR) && python $(PYTHON_FLAGS) $(OUT_DIR)/test.py
