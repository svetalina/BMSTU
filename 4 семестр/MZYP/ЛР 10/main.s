	.file	"main.c"
	.text
	.def	printf;	.scl	3;	.type	32;	.endef
	.seh_proc	printf
printf:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$56, %rsp
	.seh_stackalloc	56
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	movq	%rcx, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%r8, -32(%rbp)
	movq	%r9, -24(%rbp)
	leaq	-40(%rbp), %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rbx
	movl	$1, %ecx
	movq	__imp___acrt_iob_func(%rip), %rax
	call	*%rax
	movq	%rbx, %r8
	movq	-48(%rbp), %rdx
	movq	%rax, %rcx
	call	__mingw_vfprintf
	movl	%eax, -84(%rbp)
	movl	-84(%rbp), %eax
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "[%lf %lf %lf] \0"
.LC1:
	.ascii "\0"
	.text
	.globl	print
	.def	print;	.scl	2;	.type	32;	.endef
	.seh_proc	print
print:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	16(%rbp), %rax
	movss	8(%rax), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movq	16(%rbp), %rax
	movss	4(%rax), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movq	16(%rbp), %rax
	movss	(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movq	%xmm2, %rax
	movq	%rax, %rdx
	movq	%rdx, %xmm2
	movq	%rax, %rcx
	movq	%xmm1, %rax
	movq	%rax, %rdx
	movq	%rdx, %xmm1
	movq	%rax, %rdx
	movq	%xmm0, %rax
	movq	%rax, %r8
	movq	%r8, %xmm0
	movapd	%xmm2, %xmm3
	movq	%rcx, %r9
	movapd	%xmm1, %xmm2
	movq	%rdx, %r8
	movapd	%xmm0, %xmm1
	movq	%rax, %rdx
	leaq	.LC0(%rip), %rcx
	call	printf
	leaq	.LC1(%rip), %rcx
	call	puts
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC6:
	.ascii "TEST C\0"
.LC8:
	.ascii "result = %f\12time = %.3g s\12\0"
.LC9:
	.ascii "\12TEST SSE ASSEMBLY\0"
	.text
	.globl	test
	.def	test;	.scl	2;	.type	32;	.endef
	.seh_proc	test
test:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	addq	$-128, %rsp
	.seh_stackalloc	128
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movss	.LC2(%rip), %xmm0
	movss	%xmm0, -20(%rbp)
	movss	.LC3(%rip), %xmm0
	movss	%xmm0, -24(%rbp)
	movss	.LC4(%rip), %xmm0
	movss	%xmm0, -28(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -32(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -36(%rbp)
	movq	$0, -64(%rbp)
	movq	$0, -56(%rbp)
	movss	-20(%rbp), %xmm0
	movss	%xmm0, -64(%rbp)
	movss	-24(%rbp), %xmm0
	movss	%xmm0, -60(%rbp)
	movss	-28(%rbp), %xmm0
	movss	%xmm0, -56(%rbp)
	movq	$0, -80(%rbp)
	movq	$0, -72(%rbp)
	movss	-20(%rbp), %xmm0
	movss	%xmm0, -80(%rbp)
	movss	-24(%rbp), %xmm0
	movss	%xmm0, -76(%rbp)
	movss	-28(%rbp), %xmm0
	movss	%xmm0, -72(%rbp)
	leaq	.LC6(%rip), %rcx
	call	puts
	leaq	-88(%rbp), %rax
	movq	%rax, %rcx
	movq	__imp_QueryPerformanceCounter(%rip), %rax
	call	*%rax
	movq	$0, -8(%rbp)
	jmp	.L5
.L6:
	leaq	-80(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	leaq	-32(%rbp), %rax
	movq	%rcx, %r8
	movq	%rax, %rcx
	call	c_scalar_prod
	addq	$1, -8(%rbp)
.L5:
	movq	-8(%rbp), %rax
	cmpq	16(%rbp), %rax
	jb	.L6
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	movq	__imp_QueryPerformanceCounter(%rip), %rax
	call	*%rax
	movq	-96(%rbp), %rax
	movq	-88(%rbp), %rdx
	subq	%rdx, %rax
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	movsd	.LC7(%rip), %xmm1
	movapd	%xmm0, %xmm2
	divsd	%xmm1, %xmm2
	movss	-32(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movq	%xmm2, %rax
	movq	%rax, %rdx
	movq	%rdx, %xmm1
	movq	%rax, %rdx
	movq	%xmm0, %rax
	movq	%rax, %rcx
	movq	%rcx, %xmm0
	movapd	%xmm1, %xmm2
	movq	%rdx, %r8
	movapd	%xmm0, %xmm1
	movq	%rax, %rdx
	leaq	.LC8(%rip), %rcx
	call	printf
	leaq	.LC9(%rip), %rcx
	call	puts
	leaq	-88(%rbp), %rax
	movq	%rax, %rcx
	movq	__imp_QueryPerformanceCounter(%rip), %rax
	call	*%rax
	movq	$0, -16(%rbp)
	jmp	.L7
.L8:
	leaq	-80(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	leaq	-36(%rbp), %rax
	movq	%rcx, %r8
	movq	%rax, %rcx
	call	sse_scalar_prod
	addq	$1, -16(%rbp)
.L7:
	movq	-16(%rbp), %rax
	cmpq	16(%rbp), %rax
	jb	.L8
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	movq	__imp_QueryPerformanceCounter(%rip), %rax
	call	*%rax
	movq	-96(%rbp), %rax
	movq	-88(%rbp), %rdx
	subq	%rdx, %rax
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	movsd	.LC7(%rip), %xmm1
	movapd	%xmm0, %xmm2
	divsd	%xmm1, %xmm2
	movss	-36(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movq	%xmm2, %rax
	movq	%rax, %rdx
	movq	%rdx, %xmm1
	movq	%rax, %rdx
	movq	%xmm0, %rax
	movq	%rax, %rcx
	movq	%rcx, %xmm0
	movapd	%xmm1, %xmm2
	movq	%rdx, %r8
	movapd	%xmm0, %xmm1
	movq	%rax, %rdx
	leaq	.LC8(%rip), %rcx
	call	printf
	nop
	subq	$-128, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	call	__main
	movl	$10000, %ecx
	call	test
	movl	$0, %eax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 4
.LC2:
	.long	1092616192
	.align 4
.LC3:
	.long	1101004800
	.align 4
.LC4:
	.long	1106247680
	.align 8
.LC7:
	.long	0
	.long	1086556160
	.ident	"GCC: (Rev6, Built by MSYS2 project) 10.2.0"
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
	.def	puts;	.scl	2;	.type	32;	.endef
	.def	c_scalar_prod;	.scl	2;	.type	32;	.endef
	.def	sse_scalar_prod;	.scl	2;	.type	32;	.endef
