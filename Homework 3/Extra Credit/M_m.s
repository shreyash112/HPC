	.file	"M_m.c"
	.text
	.p2align 4,,15
	.globl	CLOCK
	.type	CLOCK, @function
CLOCK:
.LFB41:
	.cfi_startproc
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movl	$1, %edi
	movq	%rsp, %rsi
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	call	clock_gettime@PLT
	imulq	$1000, (%rsp), %rax
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	8(%rsp), %xmm1
	mulsd	.LC0(%rip), %xmm1
	cvtsi2sdq	%rax, %xmm0
	movq	24(%rsp), %rax
	xorq	%fs:40, %rax
	addsd	%xmm1, %xmm0
	jne	.L5
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L5:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE41:
	.size	CLOCK, .-CLOCK
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC2:
	.string	"Time for the loop = %4.2f milliseconds\n"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC3:
	.string	"Element %d,%d = %f\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB42:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movl	$145, %edi
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$3145768, %rsp
	.cfi_def_cfa_offset 3145824
	leaq	16(%rsp), %rbp
	movq	%fs:40, %rax
	movq	%rax, 3145752(%rsp)
	xorl	%eax, %eax
	leaq	1048576(%rbp), %r13
	movq	%rbp, %rbx
	call	srand@PLT
.L7:
	leaq	2048(%rbx), %r12
	.p2align 4,,10
	.p2align 3
.L8:
	call	rand@PLT
	pxor	%xmm0, %xmm0
	addq	$4, %rbx
	cvtsi2ss	%eax, %xmm0
	mulss	.LC1(%rip), %xmm0
	movss	%xmm0, -4(%rbx)
	cmpq	%r12, %rbx
	jne	.L8
	cmpq	%r13, %rbx
	jne	.L7
	leaq	1048592(%rsp), %r12
	leaq	1048576(%r12), %r14
	movq	%r12, %r15
.L11:
	leaq	2048(%r15), %r13
	.p2align 4,,10
	.p2align 3
.L10:
	call	rand@PLT
	pxor	%xmm0, %xmm0
	addq	$4, %r15
	cvtsi2ss	%eax, %xmm0
	mulss	.LC1(%rip), %xmm0
	movss	%xmm0, -4(%r15)
	cmpq	%r13, %r15
	jne	.L10
	cmpq	%r14, %r15
	jne	.L11
	leaq	2097168(%rsp), %r13
	xorl	%eax, %eax
	leaq	1048576(%r13), %rsi
	movq	%r13, %rdx
.L12:
	leaq	8(%rdx), %rdi
	movq	%rdx, %rcx
	movq	$0, (%rdx)
	movq	$0, 2040(%rdx)
	addq	$2048, %rdx
	andq	$-8, %rdi
	subq	%rdi, %rcx
	addl	$2048, %ecx
	shrl	$3, %ecx
	cmpq	%rsi, %rdx
	rep stosq
	jne	.L12
	xorl	%eax, %eax
	call	CLOCK
	movsd	%xmm0, 8(%rsp)
.L13:
	xorl	%esi, %esi
	.p2align 4,,10
	.p2align 3
.L17:
	leaq	(%rsi,%r12), %rax
	leaq	(%rsi,%r15), %rcx
	movq	%rbp, %rdx
	movaps	0(%r13,%rsi), %xmm1
	.p2align 4,,10
	.p2align 3
.L14:
	addq	$2048, %rax
	addq	$4, %rdx
	movss	-4(%rdx), %xmm0
	shufps	$0, %xmm0, %xmm0
	mulps	-2048(%rax), %xmm0
	cmpq	%rcx, %rax
	addps	%xmm0, %xmm1
	jne	.L14
	movaps	%xmm1, 0(%r13,%rsi)
	addq	$16, %rsi
	cmpq	$2048, %rsi
	jne	.L17
	addq	$2048, %rbp
	addq	$2048, %r13
	cmpq	%rbx, %rbp
	jne	.L13
	xorl	%eax, %eax
	call	CLOCK
	subsd	8(%rsp), %xmm0
	leaq	.LC2(%rip), %rsi
	movl	$1, %edi
	movl	$1, %eax
	call	__printf_chk@PLT
	pxor	%xmm0, %xmm0
	leaq	.LC3(%rip), %rsi
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	movl	$1, %edi
	movl	$1, %eax
	cvtss2sd	2097168(%rsp), %xmm0
	call	__printf_chk@PLT
	pxor	%xmm0, %xmm0
	leaq	.LC3(%rip), %rsi
	movl	$63, %ecx
	movl	$63, %edx
	movl	$1, %edi
	movl	$1, %eax
	cvtss2sd	2226444(%rsp), %xmm0
	call	__printf_chk@PLT
	pxor	%xmm0, %xmm0
	leaq	.LC3(%rip), %rsi
	movl	$1, %edi
	movl	$511, %ecx
	movl	$511, %edx
	movl	$1, %eax
	cvtss2sd	3145740(%rsp), %xmm0
	call	__printf_chk@PLT
	xorl	%eax, %eax
	movq	3145752(%rsp), %rdi
	xorq	%fs:40, %rdi
	jne	.L25
	addq	$3145768, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L25:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE42:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	2696277389
	.long	1051772663
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC1:
	.long	805306368
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
