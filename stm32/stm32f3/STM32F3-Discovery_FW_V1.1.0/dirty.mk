CLANG			= clang-6.0
CLANGPP 		= gcc++
AR 				= llvm-ar
#COMPILE_FLAGS 	= -fPIC

MCU_SDK_PATH = ../..
DEVICE = STM32L1XX_MD


IR_FLAGS 			+= -g
COMPILE_FLAGS 		+= -g

BUILD_DIR 	= build
OUTPUT = test

CBE = echo

IR_SUFFIX = ll

OPT			= "echo"
LD 			= "echo"

all: clean_build $(BUILD_DIR) $(OUTPUT)


.PHONY: clean_build
clean_build:
	rm -rf $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $@

print-%  : ; @echo $* = $($*)