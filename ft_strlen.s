


; size_t ft_strlen(char *str);
; RDI: str

; RAX: return value

;The BSS (Block Started Symbol) section: used for declaring variables/functions (with uninitialized data).
; global: exposes the variable on global scope
section .text
	global ft_strlen

ft_strlen:
	; set rax to 0
	xor	rax, rax
	; check if str is null
	cmp	rdi, 0
		je	.end
	.loop:
		; load the byte at str[rax] into bl (8 bit register / 1 char)
		mov	bl, [rdi + rax]
		cmp	bl, 0
			je	.end
		inc	rax
		jmp	.loop
	.end:
		; return rax
		ret