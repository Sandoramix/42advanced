; typedef struct s_list {
; 	void *data;
; 	struct s_list *next;
; } t_list;


section .text
	global ft_list_push_front
	extern malloc

; t_list *ft_list_create_elem(void *data);
ft_list_create_elem:
	xor rax, rax
	push rdi
	mov rdi, 16					; sizeof(t_list)
	call malloc
	cmp rax, 0
		je .end
	pop rdi
	mov [rax], rdi				; data
	mov rdi, 0x0
	mov [rax + 8], rdi			; next = NULL
	.end:
		ret

; void ft_list_push_front(t_list **begin_list, void *data);
ft_list_push_front:
	xor rax, rax
	cmp rdi, 0
		je .end
	push rdi
	mov rdi, rsi
	call ft_list_create_elem	; RAX = new node
	cmp rax, 0
		je .end
	pop rdx						; RDX = begin_list
	mov rcx, [rdx]				; RCX = *begin_list
	mov [rax + 8], rcx
	mov [rdx], rax
	.end:
	ret
