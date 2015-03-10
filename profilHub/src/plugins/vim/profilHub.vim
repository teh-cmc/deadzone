" * Copyright (C) 2013  Quentin Perez <perez.quentin77@gmail.com>
" *
" * This file is part of profilHub.
" *
" * profilHub is free software: you can redistribute it and/or modify
" * it under the terms of the GNU General Public License as published by
" * the Free Software Foundation, either version 3 of the License, or
" * (at your option) any later version.
" *
" * This program is distributed in the hope that it will be useful,
" * but WITHOUT ANY WARRANTY; without even the implied warranty of
" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
" * GNU General Public License for more details.
" *
" * You should have received a copy of the GNU General Public License
" * along with this program.  If not, see <http://www.gnu.org/licenses/>.
" *

if exists("loaded_profilhub") || &cp
	finish
endif

let	loaded_profilhub = 1.0
let	s:save_cpo = &cpo
set	cpo&vim

if !exists(":PH")
	command -nargs=* Ph call <SID>Ph(<f-args>)
endif

function	s:Ph(...)

echohl Title
echo "\tprofilHub is free software: you can redistribute"
echo "it and/or modify it under the terms of the GNU General Public License"
echo "\t   https://github.com/reyclement/profilHub"
echohl None
let s:extension = expand('%:e')

if !(s:extension ==? "c" || s:extension ==? "cpp")
	echoe "Ph is compatible with .c and .cpp"
	return
endif
if a:0 == 0
	call PhSynopsis()
elseif a:1 == "--version"
	call PhVersion()
elseif a:1 == "--dump"
	if a:0 == 2
		call PhDump(a:2)
	else
		echoe "Use :Ph --dump <path>"
	endif
elseif a:1 == "--exec"
	if a:0 >= 4
		let	s:i = 4
		let	s:argv_list = []
		
		while s:i <= a:0
			call add(s:argv_list, a:{s:i})
			let s:i = s:i + 1
		endwhile
		call PhExec(a:2, a:3, s:argv_list)
	else
		echoe "Use :Ph --exec <debug_level> <path> <argv>"
	endif
else
	echoe ":Ph " . a:1 . " not found."
endif

"let index = 1
"while index <= a:0
"	echo "  Arg " . index . " is " . a:{index}
"	let index = index + 1
"endwhile
endfunction

function	PhExec(debug_level, path, argv_list)
echo "Call PhExec(" . a:debug_level . ", " . a:path . ", [argv] "
for n in a:argv_list
	echo n
endfor
endfunction

function	PhDump(path)
if filereadable(a:path)
	let s:cmd = '/bin/cat ' . a:path
	let s:read = system(s:cmd)
	let s:line = split(s:read, "\n")
	let s:open = 0
	for w in s:line
		let s:words = split(w, "\t")
		let s:argv1 = "\"" . s:words[0] . "\""
		let s:cmdfind = '/usr/bin/find . -type f -name ' . s:argv1
		let s:pathfile = system(s:cmdfind)
		let s:pathfile = substitute(s:pathfile, "\n", "", "g")
		let s:argv1 = "\"" . s:pathfile . "\""
		let s:argv3 = "\"" . s:words[2] . "\""
		exe ":caddexpr printf('%s:%d:%s'," . s:argv1 . "," . s:words[1] . "," . s:argv3 . ")"
		let s:open = 1
	endfor
	if s:open == 1
		exe ":copen"
	else
		echo "\n\t\t\tNo problems detected."
	endif
else
	echoe a:path . " no such file."
endif
endfunction

function	PhVersion()
echo "--------------------------------------------------------------"
echo "profilHub is a hub of debugging and profiling tools for Linux."
echo "--------------------------------------------------------------"
echo "--------------------------------------------------------------"
echo "                         Maintainers                          "
echo "                             ---                              "
echo "             Hugo Nedelec <hugo.nedelec@gmail.com>            "
echo "           Quentin Perez <perez.quentin77@gmail.com>          "
echo "         Jean Hasdenteufel <jeanhasdenteufel@gmail.com>       "
echo "           Jean-Baptiste Noblot <noblot.jb@gmail.com>         "
echo "             Clement Rey <cr.rey.clement@gmail.com>           "
echo "                             ---                              "
echo "                           Version                            "
echo "                             0.1                              "
echo "--------------------------------------------------------------"
endfunction

function	PhSynopsis()
echo "How to use Ph (profilHub plugin)"
echo ":Ph --exec <debug_level> <path> <argv>"
echo ":Ph --dump <path>"
echo ":Ph --version"
endfunction
