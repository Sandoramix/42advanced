;void	ft_list_sort(t_list **begin_list, int (*cmp)());
; RDI = begin_list
; RSI = cmp

section .text
	global ft_list_sort

ft_list_sort:
	call rsi

	.end:
		ret