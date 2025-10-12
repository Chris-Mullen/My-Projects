import os
from constants import *

def clear():
	os.system("clear")

def divider_title(title):
	title = title.replace(" ", "=")
	title = "\n\n" + "=" * terminalWidth + "\n" + "=" * int((terminalWidth - len(title))/2) + title + "=" * int((terminalWidth - len(title))/2) + "\n" + "=" * terminalWidth + "\n\n"
	return title

def divider_title2(title):
	return "\n\n" + ":" * int(terminalWidth / 2) + "\n" + ":: " + " " * int(terminalWidth / 2 - len(title) - 6) + title + " ::" + "\n" + ":" * int(terminalWidth / 2) + "\n\n"
	
def divider():
	return "\n" + "-" * terminalWidth + "\n"

def divider2():
	div = " " * int(terminalWidth/4) + "~" * int(terminalWidth/2) + " " * int(terminalWidth/4)
	return "\n\n" + div + "\n" + div + "\n" + div + "\n\n"

def print_divider(colour='RED', end='\n'):
	print_text(divider(), colour, end)

def print_divider_title(title, colour='WHITE', end='\n'):
	print_text(divider_title(title), colour, end)

def print_divider2(colour='WHITE', end='\n'):
	print_text(divider2(), colour, end)

def print_divider_title2(title, colour='WHITE', end='\n'):
	print_text(divider_title2(title), colour, end)

def print_text(text, colour='WHITE', end='\n'):
	print(colours[colour], end='')
	print(text, end='')
	print(colours['WHITE'], end=end)
