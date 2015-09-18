balloons = map(int,raw_input().split())

max_position = balloons.index(max(balloons))

b = balloons.pop(max_position)

if b >= 2 * (balloons[0] + balloons[1]):
	print balloons[0] + balloons[1]
else:
	print (b + balloons[0] + balloons[1]) / 3
