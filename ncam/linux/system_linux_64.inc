;----------------------------------------------------------------------------|\
                                                              _____           |\
      Autor: Notsgnik                                       /||   /           |\
      Email: Labruillere gmail.com                         / ||  /            |\
      website: notsgnik.github.io                         /  || /             |\
      License: GPL v3                                    /___||/              |\
      																		  |\
------------------------------------------------------------------------------|

%include	'ncam/linux/linux_64_define.inc'

%ifndef _BUFF_SIZE_
	%define _BUFF_SIZE_ 4096
%endif

%macro	loadreg	0
	mov	max, mr12
	mov	mcx, mr14
	mov	mdx, mr15
%endmacro

%macro	savereg	0
	mov	mr12, max
	mov	mr14, mcx
	mov	mr15, mdx
%endmacro

%macro	@@start			0
	segment	.text
		global @start
		@start:
			base_init
%endmacro
	
%macro	sys_call		1
	mov	v0r, %1
	syscall
%endmacro

%macro	sys.write_out	2
	call		_SAVEREG
	mov			v2r, %2
	mov			v3r, %1
	call		_SYSWRITEOUT
%endmacro

%macro	sys.allocate	1
	call		_SAVEREG
	mov			v2r, %1
	call		_SYSALLOCATEW
	call 		_LOADREG
%endmacro

%macro	sys.allocate	2
	call		_SAVEREG
	mov			v1r, 0
	mov			v2r, %1
	mov			v3r, %2
	mov			v4r, 0x0002
	mov			v5r, -1
	xor			v6r, v6r
	call		_SYSALLOCATE
%endmacro

%macro	sys.allocate	3
	call		_SAVEREG
	mov			v1r, 0
	mov			v2r, %1
	mov			v3r, %2
	mov			v4r, %3
	mov			v5r, -1
	xor			v6r, v6r
	call		_SYSALLOCATE
%endmacro

%macro	sys.allocate	4
	call		_SAVEREG
	mov			v1r, 0
	mov			v2r, %1
	mov			v3r, %2
	mov			v4r, %3
	mov			v5r, %4
	xor			v6r, v6r
	call		_SYSALLOCATE
%endmacro

%macro	sys.allocate	5
	call		_SAVEREG
	mov			v1r, 0
	mov			v2r, %1
	mov			v3r, %2
	mov			v4r, %3
	mov			v5r, %4
	mov			v6r, %5
	call		_SYSALLOCATE
%endmacro

%macro	sys.allocate	6
	call		_SAVEREG
	mov			v1r, %1
	mov			v2r, %2
	mov			v3r, %3
	mov			v4r, %4
	mov			v5r, %5
	mov			v6r, %6
	call		_SYSALLOCATE
%endmacro

%macro	sys.alloc_adressw	2
	call		_SAVEREG
	mov			v1r, %1
	mov			v2r, %2
	mov			v3r, 0x02
	mov			v4r, 0x0002
	mov			v5r, -1
	xor			v6r, v6r
	call		_SYSALLOCATE
%endmacro

%macro	sys.alloc_adress	3
	call		_SAVEREG
	mov			v1r, %1
	mov			v2r, %2
	mov			v3r, %3
	mov			v4r, 0x0002
	mov			v5r, -1
	xor			v6r, v6r
	call		_SYSALLOCATE
%endmacro

%macro	sys.check_allocate	0
	call		_EXITONAXZ
%endmacro

%macro	sys.axlz_exit		0
	call		_EXITONAXZ
%endmacro

%macro base_init	0
	jmp _INIT
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
		mov			v1r, stdout
		sys_call	sys_write
		call		_LOADREG
		ret
	_SYSALLOCATEW:
		mov			v0r, sys_mmap
		mov			v1r, 0
		mov			v3r, 0x02
		mov			v4r, 0x0002
		mov			v5r, -1
		xor			v6r, v6r
		sys_call	sys_mmap
		ret
	_SYSALLOCATE:
		mov			v0r, sys_mmap
		sys_call	sys_mmap
		call 		_LOADREG
		ret
	_EXITONAXZ:
		cmp			max, 0
		jl			_EXITONAXZPASS
		sys.write_out _allocate_error.len, _allocate_error
		jmp			_EXIT_BAD
	_EXITONAXZPASS:
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
		
	_ADDTOLIST:
		mov				mdi, [mdx+2*ptr_size]
		cmp				mdi + 2*ptr_size, _BUFF_SIZE_
		jg				_CREATELIST
		mov				[mdx + mdi], max
		mov				[mdx + mdi + ptr_size], mbx
		mov				[mdx+2*ptr_size], mdi + 2*ptr_size
		ret
		
	_CREATELIST:
		call			_SAVEREG
		mov				v2r, _BUFF_SIZE_
		call			_SYSALLOCATEW
		call			_EXITONAXZ
		mov				mdi, max
		call			_LOADREG
		mov				[mdx+ptr_size], mdi
		init_slist		mdi, mdx, 2
		mov				mdx, mdi
		jmp	_ADDTOLIST
		
	_INIT:
		mov				v2r, _BUFF_SIZE_
		call			_SYSALLOCATEW
		call			_EXITONAXZ
		mov				r13, max
		mov				v2r, _BUFF_SIZE_
		call			_SYSALLOCATEW
		call			_EXITONAXZ
		mov				_structlist, max
		init_slist		_structlist, 0, 2
		mov				v2r, _BUFF_SIZE_
		call			_SYSALLOCATEW
		call			_EXITONAXZ
		init_slist		max, 0, 3
		add_to_list		max, _structlist, 3
		
%endmacro

%macro	init_slist	3
	mov		[%1], %2
	mov		[%1 + ptr_size], 0
	mov		[%1 + 2*ptr_size], 4*ptr_size
	mov		[%1 + 3*ptr_size], %3
%endmacro


%macro	add_to_list		4
	mov		mbx, %1				; adress
	mov		mdx, %2				; list
	mov		max, %3 			; type
	mov		mcx, %4				; datasize
	call	_ADDTOLIST
%endmacro

%macro	sys.exit		1
	mov	v1r, %1
	sys_call  sys_exit
%endmacro

%macro	gquit			0
	jmp _EXIT_GOOD
%endmacro




