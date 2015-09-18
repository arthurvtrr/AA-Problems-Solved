coins = raw_input().split()

soma = 0
for num in coins:
	soma += int(num)

if soma % 5 == 0 and soma > 0:
	print soma / 5
else:
	print "-1"
