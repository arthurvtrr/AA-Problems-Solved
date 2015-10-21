n,m = map(int, raw_input().split())

table = []

for lin in range(n):
	table.append("")
	for col in range(m):
		if lin % 2 == 0:
			table[lin] += "#"
		elif lin % 4 == 1 and col == m-1:
			table[lin] += "#"
		elif lin % 4 == 3 and col == 0:
			table[lin] += "#"
		else:
			table[lin] += "."
			
for i in range(len(table)):
    print table[i]
