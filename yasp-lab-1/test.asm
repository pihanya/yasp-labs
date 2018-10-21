section .data

characters: db '12345', 0

section .text
%include "lib.inc"
global _start

_start:
    mov       rsi, characters
    call      string_length
    mov       rax, rdx
    call      exit
