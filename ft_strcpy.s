; char *ft_strcpy(char *dst, const char *src);
; RDI: dst
; RSI: src

; RAX: return value

; The BSS (Block Started Symbol) section: used for declaring program instructions.
; global: exposes the variable on global scope
section .text
	global ft_strcpy

ft_strcpy:
	xor rax, rax
	.loop:
		mov bl, [rsi + rax]	;src[rax]
		mov [rdi + rax], bl	;dst[rax] = src[rax]
		cmp bl, 0
			je .end
		inc rax
		jmp .loop
	.end:
		mov rax, rdi
		ret