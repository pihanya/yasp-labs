section .text

; Descriiption:
; Exit program with code %rax
;
; Arguments:
; %rdx - exit code
exit:
    mov       rdi, rdx
    mov       rax, 60
    syscall

; Descriiption:
; Get length of the given string
;
; Arguments:
; %rdi - adress of the string
;
; Result:
; %rax - amount of symbols in given string
string_length:
    push       rbx
    mov        rbx, rdi
    xor        rax, rax
.loop:
    cmp        byte[rdi+rax], 0
    je         .end
    inc        rax
    jmp        .loop
.end:
    pop        rbx
    ret

; Description:
; Print given string
;
; Arguments:
; %rdi - adress of the string
print_string:
    mov         rsi, rdi          ; %rsi = $rdi (adress of the string)
    call        string_length
    mov         rdx, rax          ; %rdx = length (string size)
    mov         rax, 1            ; %rax = 1 (write syscall)
    mov         rdi, 1            ; %rdi = 1 (descriptor)
    syscall                       ; call write(%rdi: fd, %rsi: buf, %rdx: count)
    ret

; Description
; Prints char with given returncode
;
; Arguments:
; %rdi - code of the char to be printed
print_char:
    push rcx
    push rax
    push rsi
    push rdx
    push rdi

    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 1

    syscall

    pop rdi
    pop rdx
    pop rsi
    pop rax
    pop rcx

    ret

print_newline:
    mov         rdi, 10
    call        print_char
    ret

; Description
; Print unsigned 8-byte integer in decimal format
;
; Arguments:
; %rdi - unsigned 8-byte integer to be printed
print_uint:
    mov r9, rsp

    dec rsp
    mov byte[rsp], 0
    mov r8, 10
    mov rax, rdi
.loop:
    xor rdx, rdx
    div r8
    add rdx, 48
    dec rsp
    mov byte[rsp], dl
    test rax, rax
    jnz .loop

	  mov rdi, rsp
	  call print_string

	  mov rsp, r9
	  ret

; Description
; Print signed 8-byte integer in decimal format
;
; Arguments:
; %rdi - signed 8-byte integer to be printed
print_int:
    and rdi, rdi
    jns .unsigned

    push rdi
    mov rdi, 45
    call print_char
    pop rdi
    neg rdi
.unsigned:
    call print_uint
    ret

; Check whether one string equals the another
; %rax = 1, если равны
; %r8, %r9 - addresses of compared strings
string_equals:
    push rdi
    push rsi
    xor rax, rax
    xor r8, r8
    xor r9, r9
.loop:
    mov r8b, byte[rdi]
    mov r9b, byte[rsi]
    cmp r8, r9
    jne .fail
    inc rdi
    inc rsi
    test r8, r8
    jnz .loop
    inc rax
.fail:
    pop rsi
    pop rdi
    ret

; Read char from stdin
; rsi -- прочитанный символ
read_char:
    push 0
    xor rax, rax
    xor rdi, rdi
    mov rsi, rsp
    mov rdx, 1
    syscall
    mov al, byte[rsp]
    pop rsi
    ret

section .data
  	word_buffer times 256 db 0

section .text

; Description
; Skip first whitespace symbols and read until whitespace
;
; Arguments:
; %rdi - address of the scanned string
; %rsi - maximal size of word
;
; Returns:
; %rax - address of the read word
; %rdx - length of the read word
read_word:
	xor r8, r8
	mov r8, rdi
.skip:
  push rsi
		call read_char
    pop rsi
		test rax, rax
		jz .finish
		cmp rax, 32
		jle .skip
.read_next:
		mov [r8], rax
		inc r8
    push rsi
		call read_char
    pop rsi
		cmp rax, 32
		jg .read_next
.finish:
		call string_length
		mov rdx, rax
		mov rax, rdi
    ret

; Description
; Parse unsigned int from given stirng
; Arguments:    
; %rdi - address of parsed string
; returns rax: number, rdx : length
parse_uint:
    push rdi
    xor rax, rax
    xor rdx, rdx
    xor r10, r10
    mov r8, 10
.loop:
    cmp byte[rdi], 48
    jl .end
    cmp byte[rdi], 57
    jg .end
    inc r10
    mul r8
    xor r9, r9
    mov r9b, byte[rdi]
    sub r9, 48
    add rax, r9
    inc rdi
    jmp .loop
.end:
    mov rdx, r10
    pop rdi
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_int:
    xor rax, rax
    cmp byte[rdi], 45
    je .signed
    call parse_uint
    ret
.signed:
    inc rdi
    call parse_uint
    neg rax
    inc rdx
    ret


string_copy:
    push rcx
.loop:
    xor rcx, rcx
    mov cl, byte[rdi]
    mov byte[rsi], cl
    inc rdi
    inc rsi
    test rcx, rcx
    jnz .loop
    pop rcx
    ret
