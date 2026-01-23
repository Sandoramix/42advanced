; char *ft_strdup(const char *s);
; RDI: s

; RAX: return value

section .text
	global ft_strdup
	extern ft_strlen
	extern ft_strcpy
	extern malloc

ft_strdup:
	cmp rdi, 0
		je .end		; s == NULL
	mov rsi, rdi	; RSI: s
	push rsi		; STACK[0]: s
	call ft_strlen	; RAX: len
	mov rdi, rax	; RDI: len
	inc rdi			; RDI: len + 1
	mov rdx, rdi	; RDX: len + 1
	push rdx		; STACK[1]: len + 1
	call malloc; RAX: malloc(len + 1)
	cmp rax, 0		; malloc(len + 1) == NULL
		je .end
	mov rdi, rax	; RDI: malloc(len + 1)
	pop rdx			; RDX: STACK[1]: len + 1
	pop rsi			; RSI: STACK[0]: s
	call ft_strcpy	; RAX: ft_strcpy(malloc(len + 1), s, len + 1)
	.end:
		ret