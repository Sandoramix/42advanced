


; size_t ft_strlen(char *str);
; RDI: str

; RAX: return value

;The BSS (Block Started Symbol) section: used for declaring variables/functions (with uninitialized data).
; global: exposes the variable on global scope
section: .text
	global ft_strlen

ft_strlen:
	xor	rax, rax
	;TODO
