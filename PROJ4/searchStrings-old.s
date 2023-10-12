WRITE = 1
stdout = 1
chrange_start = 0x20
chrange_end = 0x7E

.section .data
eol: .ascii "\n" 


.global searchStrings

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

searchStrings:
# rdi - en. base  rsi - tamanho da área de memória onde está o ficheiro 
	push %rbp
	mov %rsp, %rbp
	
# rdi = contents (apontador para o início do ficheiro)
# rsi = tamanho do ficheiro
# for loop entre rdi e rdi+(rsi)
# ver caracter a caracter se está entre 0x20 e 0x7E
# passar esse caracter ao myPutChar

	mov %rdi, %rcx		# i = rcx
	mov %rdi, %r8	# r8 = loop end = rdi+rsi
	add %rsi, %r8
	
	.loop:
	cmp %rcx, %r8		# if loop end
	jz .end
	
	cmpb $chrange_start, (%rcx)	# if 0x20 > rcx
	jl .inc_loop
	cmpb $chrange_end, (%rcx)	# if 0x7E < rcx
	jg .inc_loop
	mov %rcx, %rdi
	push %rcx
	call myPutChar		# print char
	pop %rcx
	
	.inc_loop:
	inc %rcx
	jmp .loop
	
	.end:
	mov %rbp, %rsp
	pop %rbp
	ret
	


