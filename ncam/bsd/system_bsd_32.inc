;evrything is to do
	%define	stdin		0
	%define	stdout		1
	%define	stderr		2
	
	%define	sys_exit		1
	%define	sys_write		4

	%define	@start			_start
	
	%macro	sys_call		1
		mov	max, %1
		int	80h
	%endmacro
	
	%macro	sys.write_out	2
		push	dword, %1
		push	dword, %2
		push	dword, stdout
		sys_call  sys_write
	%endmacro
	
	%macro	sys.exit	1
		push	dword, %1
		sys_call  sys_exit
	%endmacro
