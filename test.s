WRITE = 1
stdout = 1

.section .data

eol: .ascii "l"

.section .text

myPutChar:
#  rdi : byte address
	push %rbp
	mov %rsp, %rbp

# rdi = 1 char
# fazer syscall ao write para dar print desse rdi

	mov $1, %rdx		# 1 char
	mov %rdi, %rsi		# print rdi char
	mov $stdout, %rdi	# write in stdout
	mov $WRITE,%rax 	# syscall write
	syscall
	
	mov %rbp, %rsp
	pop %rbp
	ret

_start:
	push %rbp
	mov %rsp, %rbp

	mov eol, %rdi
  call myPutChar

	mov %rbp, %rsp
	pop %rbp
	ret