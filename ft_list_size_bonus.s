; typedef struct s_list {
; 	void *data;				// 8 bytes
; 	struct s_list *next;	// 8 bytes
; } t_list;

; int ft_list_size(t_list *list);


section .text
	global ft_list_size

ft_list_size:
	xor rax, rax
	.loop:
		cmp rdi, 0
			je .end
		inc rax
		mov rdi, [rdi + 8];	list = list->next (8 bytes from start)
		jmp .loop
	.end:
		ret