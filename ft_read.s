; void ft_read(int fd, void *buf, size_t count);
; RDI: fd
; RSI: buf
; RDX: count

; RAX: return value

; errno handling
; syscall returns negative value (on RAX register) on error which is errno but negative
; so we need to store it in the errno location

; syscall 0: write
; https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/

section .text
	global ft_read
	extern __errno_location	; function that returns the address of errno

ft_read:
	mov rax, 0; 0 -> read
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