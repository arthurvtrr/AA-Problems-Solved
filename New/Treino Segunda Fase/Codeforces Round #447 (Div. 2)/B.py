n, m, k = map(int, raw_input().split())

def fpow(base, exp):
	if exp == 0:
		return 1
	result = fpow(base, exp/2)
	result *= result
	result %= 1000000007
	if exp % 2:
		result *= base
	return result % 1000000007

if k == -1 and (n % 2) != (m % 2):
	print 0
else:
	print fpow(2, (n-1)*(m-1))
