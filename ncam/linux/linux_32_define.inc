
%define	v0x		eax
%define	v1x		ebx
%define	v2x		ecx
%define	v3x		edx
%define	v4x		esi
%define	v5x		edi


%define	v0		ax
%define	v1		bx
%define	v2		cx
%define	v3		dx
%define	v4		si
%define	v5		di

%define	v0l		al
%define	v1l		bl
%define	v2l		cl
%define	v3l		dl
%define	v4l		sil
%define	v5l		dil

%define	max		eax
%define	mbx		ebx
%define	mcx		ecx
%define	mdx		edx
%define	mbp		ebp
%define	msi		esi
%define	mdi		edi
%define	msp		esp
%define	mr8		r8d
%define	mr9		r9d
%define	mr10	r10d
%define	mr11	r11d
%define	mr12	r12d
%define	mr13	r13d
%define	mr14	r14d
%define	mr15	r15d
%define	ptr		resd
%define	small	resb
%define	big		resd
%define	ptr_size 4

%define	stdin		0
%define	stdout		1
%define	stderr		2

%define	sys_exit		1
%define	sys_write		4

%define	@start			_start
