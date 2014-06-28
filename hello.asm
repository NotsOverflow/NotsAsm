;----------------------------------------------------------------------------|\
                                                              _____           |\
      Autor: Notsgnik                                       /||   /           |\
      Email: Labruillere gmail.com                         / ||  /            |\
      website: notsgnik.github.io                         /  || /             |\
      License: GPL v3                                    /___||/              |\
      																		  |\
------------------------------------------------------------------------------|

%define _LINUX64_

%include	'ncam/core.inc'
	 

@@start

	gchars	hello, {"ecco the dolphin",0Ah}
	gchar	letter, 'y'
	
	gchar	charholder
	
	emov	[charholder], [letter]
	printd(charholder)
	
	emov	[charholder], 0Ah
	printd(charholder)
	
	printd(hello.len, hello)	
	
	gquit


