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
# rdi = 1 char
# faz syscall write para dar print desse rdi

	push %rbp
	mov %rsp, %rbp

	mov $1, %rdx		  # char length = 1
	mov %rdi, %rsi		# print rdi char
	mov $stdout, %rdi	# write in stdout
	mov $WRITE, %rax 	# syscall write
	syscall
	
	mov %rbp, %rsp
	pop %rbp
	ret	

searchStrings:
# rdi - en. base  rsi - tamanho da area de memoria onde esta o ficheiro
# rdi = contents (apontador para o inicio do ficheiro)
# rsi = fileSize
# rcx = counter (i)
# for loop entre rdi e r8=rdi+(rsi)
# r9b = printable character flag
# verifica caracter a caracter se esta no range printable (entre 0x20 e 0x7E)
# se for printable passa esse caracter ao myPutChar
# se for unprintable e o anterior for printable imprime \n
# garantindo assim que as sequencias sao impressas em linhas separadas

	push %rbp
	mov %rsp, %rbp

	mov %rdi, %rcx	# i = rcx
	mov %rdi, %r8		# r8 = loop end = rdi+rsi
	add %rsi, %r8
	
	.loop:
	cmp %rcx, %r8		# if loop end
	jz .end
	
	cmpb $chrange_start, (%rcx)	# if 0x20 > *rcx
	jl .unprintable_found				# then *rcx is unprintable
	cmpb $chrange_end, (%rcx)		# if 0x7E < *rcx
	jg .unprintable_found				# then *rcx is unprintable

	# printable was found!
	movb $1, %r9b 	# set r9b = printable flag to one
	mov %rcx, %rdi	# passes the printable char address to the first argument to call myPutChar
	jmp .print

	.print:
	push %rcx					# syscall messes with rcx so we push and pop it to preserve it
	call myPutChar		# prints char on rdi
	pop %rcx
	jmp .inc_loop

	.unprintable_found:
	cmpb $1, %r9b 		# if previous char was printable
	jz .print_newline	# prints \n
	jmp .inc_loop

	.print_newline:
	movb $0, %r9b 	# set printable flag to 0
	mov $eol, %rdi	# passes \n to the first argument to call myPutChar
	jmp .print

	.inc_loop:
	inc %rcx
	jmp .loop
	
	.end:
	mov %rbp, %rsp
	pop %rbp
	ret


