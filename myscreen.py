#!/usr/bin/env python

from os import system
import curses

def get_param(prompt_string):
	screen.clear()
	screen.border(0)
	screen.addstr(2, 2, prompt_string)
	screen.refresh()
	input = screen.getstr(10, 10, 60)
	return input

def execute_cmd(cmd_string):
	system("clear")
	a = system(cmd_string)
	print ""
	if a == 0:
		print "Command executed correctly"
	else:
		print "Command terminated with error"
	raw_input("Press enter")
	print ""

x = 0

while x != ord('4'):
	f = open("/home/gngrbrd/dev/scratch/myfile.txt","r")
	l = f.readlines()

	screen = curses.initscr()

	screen.clear()
	screen.border(0)
	if(len(l) == 3):
		screen.addstr(4, 4, l[0])
		screen.addstr(5, 4, l[1])
		screen.addstr(6, 4, l[2])
		p=l
	else:
		if(len(p) ==3):
			screen.addstr(4, 4, p[0])
			screen.addstr(5, 4, p[1])
			screen.addstr(6, 4, p[2])
	screen.refresh()
	f.close()

curses.endwin()

