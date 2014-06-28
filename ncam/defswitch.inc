;-----------------------------------------------------------------------------|\
                                                              _____           |\
      Autor: Notsgnik                                       /||   /           |\
      Email: Labruillere gmail.com                         / ||  /            |\
      website: notsgnik.github.io                         /  || /             |\
      License: GPL v3                                    /___||/              |\
                                                                              |\
------------------------------------------------------------------------------|

%ifdef		_LINUX64_
	%ifndef		_SYS_INCLUDE_DONE_
		%define		_SYS_INCLUDE_DONE_
		%include	'ncam/linux/system_linux_64.inc'
	%endif
%endif
%ifdef		_LINUX32_
	%ifndef		_SYS_INCLUDE_DONE_
		%define		_SYS_INCLUDE_DONE_
		%include	'ncam/linux/system_linux_32.inc'
	%endif
%endif
%ifdef		_BSD64_
	%ifndef		_SYS_INCLUDE_DONE_
		%define		_SYS_INCLUDE_DONE_
		%include	'ncam/bsd/system_bsd_64.inc'
	%endif
%endif
%ifdef		_BSD32_
	%ifndef		_SYS_INCLUDE_DONE_
		%define		_SYS_INCLUDE_DONE_
		%include	'ncam/bsd/system_bsd_32.inc'
	%endif
%endif
%ifdef		_WIN64_
	%ifndef		_SYS_INCLUDE_DONE_
		%define		_SYS_INCLUDE_DONE_
		%include	'ncam/windows/system_windows_64.inc'
	%endif
%endif
%ifdef		_WIN32_
	%ifndef		_SYS_INCLUDE_DONE_
		%define		_SYS_INCLUDE_DONE_
		%include	'ncam/windows/system_windows_32.inc'
	%endif
%endif

