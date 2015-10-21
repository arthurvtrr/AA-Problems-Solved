n, d = map(int, raw_input().split())

minutos = map(int, raw_input().split())

tempo_gasto = 0
musicas = 0
piadas = 0

for num in minutos:
	if d - tempo_gasto >= num:
		tempo_gasto += num
		musicas += 1
	else:
		print -1
		exit()
	
	if musicas == n:
		break

	if d - tempo_gasto >= 10:
		tempo_gasto += 10
		piadas += 2

	elif d - tempo_gasto < 10 and musicas < n:
		print -1
		exit()

	elif d - tempo_gasto >= 5:
		tempo_gasto += 5
		piadas += 1

if (d - tempo_gasto) >= 5:
	piadas += (d - tempo_gasto) / 5

print piadas
