
; int ft_strcmp(const char *s1, const char *s2);
; RDI: s1
; RSI: s2

; RAX: return value

;The BSS (Block Started Symbol) section: used for declaring variables/functions (with uninitialized data).
; global: exposes the variable on global scope
section .text
	global ft_strcmp

ft_strcmp:
	xor rax, rax
	xor bl, bl
	xor cl, cl
	.loop:
		mov bl, [rdi + rax]
		mov cl, [rsi + rax]
		cmp bl, cl
			jne .end
		cmp bl, 0
			je .end
		inc rax
		jmp .loop
	.end:
		sub rbx, rcx
		mov rax, rbx
		ret