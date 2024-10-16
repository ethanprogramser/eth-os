export OBJ_DIR=$(abspath obj)
export BUILD_DIR=$(abspath build)
export SRC_DIR=$(abspath src)
export OUT_DIR=$(abspath out)

export ASM=nasm
export CC=cc
export LD=ld

export ASMFLAGS=-f elf32
export CFLAGS=-m32 -fno-stack-protector -fno-builtin
export LDFLAGS=-m elf_i386
