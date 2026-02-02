; https://web.stanford.edu/class/cs107/resources/x86-64-reference.pdf

; int ft_strcmp(const char *s1, const char *s2);
; RDI: s1
; RSI: s2

; RAX: return value

; The BSS (Block Started Symbol) section: used for declaring program instructions.
; global: exposes the variable on global scope
section .text
	global ft_strcmp

ft_strcmp:
	xor rax, rax
	xor rbx, rbx
	xor rcx, rcx
	.loop:
		mov bl, [rdi + rax]	;s1[rax]
		mov cl, [rsi + rax]	;s2[rax]
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