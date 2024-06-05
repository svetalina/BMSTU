	.file	"scalar_prod.c"
	.text
	.globl	c_scalar_prod
	.def	c_scalar_prod;	.scl	2;	.type	32;	.endef
	.seh_proc	c_scalar_prod
c_scalar_prod:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	%r8, 32(%rbp)
	movq	24(%rbp), %rax
	movss	(%rax), %xmm1
	movq	32(%rbp), %rax
	movss	(%rax), %xmm0
	mulss	%xmm0, %xmm1
	movq	24(%rbp), %rax
	movss	4(%rax), %xmm2
	movq	32(%rbp), %rax
	movss	4(%rax), %xmm0
	mulss	%xmm2, %xmm0
	addss	%xmm0, %xmm1
	movq	24(%rbp), %rax
	movss	8(%rax), %xmm2
	movq	32(%rbp), %rax
	movss	8(%rax), %xmm0
	mulss	%xmm2, %xmm0
	addss	%xmm1, %xmm0
	movq	16(%rbp), %rax
	movss	%xmm0, (%rax)
	nop
	popq	%rbp
	ret
	.seh_endproc
	.globl	sse_scalar_prod
	.def	sse_scalar_prod;	.scl	2;	.type	32;	.endef
	.seh_proc	sse_scalar_prod
sse_scalar_prod:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	%r8, 32(%rbp)
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	32(%rbp), %rcx
/APP
 # 13 "src/scalar_prod.c" 1
	.intel_syntax noprefix
	movaps xmm0, (%rdx)
	movaps xmm1, (%rcx)
	mulps xmm0, xmm1
	movhlps xmm1, xmm0
	addps xmm0, xmm1
	movaps xmm1, xmm0
	shufps xmm0, xmm0, 1
	addps xmm0, xmm1
	movss (%rax), xmm0
	
 # 0 "" 2
/NO_APP
	nop
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (Rev6, Built by MSYS2 project) 10.2.0"
