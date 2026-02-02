; https://web.stanford.edu/class/cs107/resources/x86-64-reference.pdf

; size_t ft_strlen(char *str);
; RDI: str

; RAX: return value

; The BSS (Block Started Symbol) section: used for declaring program instructions.
; global: exposes the variable on global scope
section .text
	global ft_strlen

; XOR TABLE
;-----------;
;   | 0 | 1 ;
;-----------;
; 0 | 0 | 1 ;
;-----------;
; 1 | 1 | 0 ;
;-----------;

ft_strlen:
	; set rax to 0 (exclusive OR operator)
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