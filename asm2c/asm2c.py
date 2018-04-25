#!/usr/bin/python
'''========================================================================================================
// Basically, all of files downloaded from my website can be modified or redistributed for any purpose.
// It is my honor to share my interesting to everybody.
// If you find any illeage content out from my website, please contact me firstly.
// I will remove all of the illeage parts.
// Thanks :)
//
// This script is intended for translating from x86 assembly(from IDA Pro) to like-asm C language.
//
// Steward Fu (steward.fu@gmail.com)
// https://steward-fu.github.io/website/index.htm
========================================================================================================*/
'''
#!/usr/bin/python
import os
import sys
CPP = 'output.c'

if len(sys.argv) != 2:
	print 'usage:'
	print '  ./asm2c.py input.asm'
	sys.exit()

asm = sys.argv[1]

f = open(asm)
asm_line = f.readlines()
f.close()

f_cpp = open(CPP, 'w')
for line in asm_line:
	if (line.startswith(';') == True) or (line == ''):
		continue

	token_list = ' '.join(line.split()).split(' ')
	for token in token_list:
		if token == ';':
			break
		print token

f_cpp.close()
print 'translated c file: ' + CPP
print 'task done !'
