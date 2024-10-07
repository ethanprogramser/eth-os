bits 32


section .text
    align 4
    dd 0x1BADB002
    dd 0x00000000
    dd -(0x1BADB002 + 0x00000000)

global start
extern main 


start:
  cli
  mov esp, stack_space
  call main
  hlt

HaltKernel:
  cli
  hlt
  jmp HaltKernel

section .bss

resb 8192

stack_space:

