to_change = [0]*150

def change(c):
	if to_change[ord(c)]:
		if ord(c) > 91:
			return 'f'
		return 'F'
	return c

letters = ['s','j','b','z','p','v','x','S','J','B','Z','P','V','X']
for l in letters:
	to_change[ord(l)] = 1

while True:
	try:
		word = raw_input()
	except EOFError:
		break
	n = len(word)
	
	cont = 0
	f = '*'
	resp = ""
	for i in range(n):
		x = change(word[i])
		if (x == 'f' or x == 'F') and cont == 0:
			f = x
			cont += 1
		elif x == 'f' or x == 'F':
			cont += 1
		else:
			if cont > 0:
				resp += f
				cont = 0
			resp += x
	
	if cont > 0:
		resp += f
	
	print resp
