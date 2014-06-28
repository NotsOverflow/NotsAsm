;----------------------------------------------------------------------------|\
                                                              _____           |\
      Autor: Notsgnik                                       /||   /           |\
      Email: Labruillere gmail.com                         / ||  /            |\
      website: notsgnik.github.io                         /  || /             |\
      License: GPL v3                                    /___||/              |\
      																		  |\
------------------------------------------------------------------------------|

; everything is to do
	extern _GetStdHandle@4
	extern _WriteConsoleA@20
	extern _ExitProcess@4

	section .bss
		numCharsWritten:        resb 1
    
	%define	stdin		0
	%define	stdout		1
	%define	stderr		2


	%define	@start			_start
	%define	sys_exit		_ExitProcess@4
	%define	sys_write		_WriteConsoleA@20
	%define	sys_gethandle	_GetStdHandle@4
	
	%macro	sys_call		1
		call	%1
	%endmacro
	
	%macro	sys.write_out	2
		push    	dword, -11
		sys_call	sys_gethandle
		push    	dword, 0
		push    	numCharsWritten
		push    	dword, %1
		push		dword, %2
		push		rax
		sys_call    sys_write
	%endmacro
	
	%macro	sys.exit	1
		push		dword,	%1
		sys_call	sys_exit
	%endmacro

	
