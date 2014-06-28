
%include 'ncam/defswitch.inc'

%define	printd(x,y)	sys.write_out x, y
%define	printd(y)	sys.write_out 1, y

segment	.bss
	_tmp		ptr		8
	_buffer		small 	_BUFF_SIZE_
	_structlist	ptr 	1
	
segment		.data
	_allocate_error	db	"error : 0x000001", 0Ah
	_allocate_error.len	equ	$-_allocate_error


%macro	docall	1
	call	_DOCALL
	call	%1
%endmacro

%macro	doret	0
	call	_DORET
	ret
%endmacro

%macro	emov	2
	mov		max, %2
	mov		%1, max
%endmacro


%macro	gpointer		1
	segment		.bss
		%1	ptr	1
	segment		.text
%endmacro

%macro	gchar			1
	segment		.bss
		%1	resd	1
	segment		.text
%endmacro

%macro	gchars			2
	segment		.data
		%1	db	%2
		%1.len	equ	$-%1
	segment		.text
%endmacro

%macro	gchar			2
	segment		.data
		%1	db	%2
	segment		.text
%endmacro


