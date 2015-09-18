import math

n,m = raw_input().split()

mindiv = math.ceil(float(n) / int(m))

kmin = 0
if int(n) % int(m) == 0:
	kmin = int(m) * (mindiv*(mindiv-1)/2)
else:
	value1 = (mindiv*(mindiv-1)/2) * (int(n) % int(m))
	value2 = mindiv - 1
	value3 = (int(n) - (mindiv * (int(n) % int(m)))) / value2

	kmin = value1 + (value2*(value2-1)/2) * value3

maxdiv = int(n) - int(m) + 1

kmax = maxdiv*(maxdiv-1)/2

print int(kmin), kmax
