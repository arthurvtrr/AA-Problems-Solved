string = raw_input()

k = int(raw_input())

string += "-" * k
x = len(string)

sizes = []
for i in range(x-k):
	for j in range(i,x+1):
		test = string[i:j]
		if len(test) % 2 != 0:
			continue
		n = len(test) / 2
		size = 0
		for l in range(n):
			if test[l] != test[l+n] and test[l+n] != "-":
				break
			size += 2
		sizes.append(size)
print max(sizes)
