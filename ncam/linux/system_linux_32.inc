;----------------------------------------------------------------------------|\
                                                              _____           |\
      Autor: Notsgnik                                       /||   /           |\
      Email: Labruillere gmail.com                         / ||  /            |\
      website: notsgnik.github.io                         /  || /             |\
      License: GPL v3                                    /___||/              |\
      																		  |\
------------------------------------------------------------------------------|

%include	'ncam/linux/linux_32_define.inc'

%ifndef _BUFF_SIZE_
	%define _BUFF_SIZE_ 4096
%endif

%macro	loadreg	0
	mov	max, mr10
	mov	mbx, mr11
	mov	mcx, mr12
	mov	mdx, mr13
%endmacro

%macro	savereg	0
	mov	mr10, max
	mov	mr11, mbx
	mov	mr12, mcx
	mov	mr13, mdx
%endmacro

%macro	@@start			0
	segment	.text
		global @start
		@start:
			base_init
%endmacro
	
%macro	sys_call		1
	mov	max, %1
	int	80h
%endmacro

%macro	sys.write_out	2
	mov			mcx, %2
	mov			mdx, %1
	call		_SYSWRITEOUT
%endmacro

%macro base_init	0
	jmp _END_BASE_INIT
	_EXIT_GOOD:
		sys.exit	0
	_EXIT_BAD:
		sys.exit	1
	_SAVEREG:
		savereg
		ret
	_LOADREG:
		loadreg
		ret
	_SYSWRITEOUT:
		call		_SAVEREG
		mov			mbx, stdout
		sys_call	sys_write
		call		_LOADREG
		ret
	_DOCALL:
		call _SAVEREG
		;add_chain
		mov	[ max ], mr10
		mov	[ max + ptr_size ], mr11
		mov	[max + 2*ptr_size ], mr12
		mov	[max + 3*ptr_size ], mr13
		call _LOADREG
		ret
	_DORET:
		;rm_chain
		;load_chain
		ret
	_END_BASE_INIT:
%endmacro

%macro	sys.exit		1
	mov	mbx, %1
	sys_call  sys_exit
%endmacro

%macro	gquit			0
	jmp _EXIT_GOOD
%endmacro

%macro	char	1
	mov		max , %1			
%endmacro


