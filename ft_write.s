; void ft_write(int fd, const void *buf, size_t count);
; RDI: fd
; RSI: buf
; RDX: count

; RAX: return value

; errno handling
; syscall returns negative value (on RAX register) on error which is errno but negative
; so we need to store it in the errno location

; syscall 1: write
; https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/

section .text
	global ft_write
	extern __errno_location	; function that returns the address of errno

ft_write:
	mov rax, 1; 1-> write
	syscall
	cmp rax, 0
		jge .end
	neg rax
	mov rdi, rax
	call __errno_location
	mov [rax], rdi
	mov rax, -1
	.end:
		ret