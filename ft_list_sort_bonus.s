;void	ft_list_sort(t_list **begin_list, int (*cmp)());
; RDI = begin_list
; RSI = cmp

section .text
	global ft_list_sort


; void swap_values(t_list *a, t_list *b)
; RDI = a
; RSI = b
.swap_values:
	xor rdi, rsi
	xor rsi, rdi
	xor rdi, rsi
	ret

ft_list_sort:
	cmp rdi, 0
		je .end
	mov r8, rdi	;r8 = begin_list
	mov r9, rsi	;r9 = cmp

	mov rbx, [rdi]	; *begin_list
	cmp rbx, 0
		je .end
	
	mov rcx, rbx
	mov rdx, rcx
	
	.main_loop:
		mov rdx, [rcx + 8]
		cmp rdx, 0
			je .end
		.inner_loop:
			mov rdi, [rcx]
			mov rsi, [rdx]
			call r9
			cmp rax, 0
				jl .no_swap
			call .swap_values
			.no_swap:
			mov rdx, [rdx + 8]
			cmp rdx, 0
				jne .inner_loop
		mov rcx, [rcx + 8]
		cmp rcx, 0
			je .end
		jmp .main_loop
	.end:
		ret