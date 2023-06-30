
# REMCU MCU SDK Collection

---


## Overview

The REMCU MCU SDK Collection is a comprehensive compilation of modified Microcontroller Unit (MCU) Software Development Kits (SDKs) sourced from various chip vendors. These SDKs have undergone meticulous customization and adaptation to seamlessly integrate with the [REMCU]() library on multiple platforms, including Windows, Linux, and MacOS.This collection  empowers developers to remotely control MCUs from their PC applications using familiar APIs from the vendor SDKs made possible through the technology of [MCU Peripheral Forwarding]().

By leveraging the REMCU library, developers can seamlessly integrate the functions of the vendor SDKs into their PC applications. REMCU interrupts all peripheral operations, including storing and loading from registers, and executes them on the chip using OpenOCD or GDB server. This allows developers to conveniently and efficiently control the MCU's peripherals directly from their PC environment.

## How to use

To build REMCU Toolkit, please follow these steps:

1. Install the necessary dependencies:
   - CMake: Install CMake, which is used for building the project.
   - Git: Install Git, which is required for retrieving the source code.
   - Python: Install Python, as it is needed for certain build scripts.
   - Clang version 8: Install Clang version 8, as it is the required compiler for REMCU Toolkit.
   - Ninja (optional): Install Ninja, which is an optional build system that can provide faster build times.

2. Obtain the source code:
   - Clone the REMCU Toolkit repository from GitHub using the following command:
     ```
     git clone https://github.com/
     ```

3. Get the prebuilt LLVM ADIN fork or bu:
   - Visit the REMCU Toolkit GitHub repository (https://github.com/) and download the prebuilt LLVM ADIN fork package provided in the release section.
   - Extract the LLVM ADIN fork package to a directory of your choice.

   **or**
   
   Build LLVM ADIN fork (optional):
If you prefer to build LLVM ADIN fork yourself instead of using a prebuilt version, follow the instructions provided in the REMCU Toolkit repository to build LLVM ADIN fork.

4. Build REMCU Toolkit:
   - Open a terminal and navigate to the directory where you cloned the REMCU Toolkit repository.
   - Create a build directory:
     ```
     mkdir build
     cd build
     ```
   - Configure the build using CMake, specifying the path to the LLVM ADIN fork:
     ```
     cmake -DCMAKE_C_COMPILER=/path/to/clang-8 -DCMAKE_CXX_COMPILER=/path/to/clang++-8 -DLLVM_CONFIG_PATH=/path/to/llvm-adin/bin/llvm-config ..
     ```
     Replace "/path/to/clang-8", "/path/to/clang++-8", and "/path/to/llvm-adin" with the actual paths to the Clang version 8 binaries and the extracted LLVM ADIN fork directory.
   - Build the project using Ninja (optional) or the default build system (usually Make):
     ```
     ninja
     # or
     make
     ```

5. Verify the build:
   - After the build process completes successfully, you should find the REMCU Toolkit executable or library files in the build directory.

Congratulations! You have successfully built REMCU Toolkit. You can now proceed to use it in your embedded development projects.