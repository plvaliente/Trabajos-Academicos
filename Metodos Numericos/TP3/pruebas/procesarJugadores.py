#Buscar los anios a procesar
g = open('./stats/params.txt', 'r')
params = g.readline()
params = params.split(" ")
inicio = int(params[0])
fin = int(params[1])
years = range(inicio,fin+1)


#Guardar las estadisticas de jugadores por anio
matriz = []
for i in years:
	vectori = []
	f = open('./estadisticasJugadores/salidaDef'+str(i), 'r')
	for line in f:
		if(line[0] != 'R'):
			line = line.rstrip(" \n")
			vectori.append(line.split(","))
	matriz.append(vectori)
	f.close()



#Ordeno los jugadores de cada anio por equipo
for vector in matriz:
	vector.sort(key= lambda jugador: jugador[1])


#Saco promedios ponderados


anio = inicio
for vector in matriz:
	output = open('./estadisticasJugadores/equiposDef'+str(anio)+'.txt', 'w')

	i = 0
	while i < len(vector):
		if vector[i][1] != 'TOT':
			acumEquipo = []
			acumEquipo.append(vector[i][1])														#En el primer elemento de acumEquipo guardo el RK del equipo
			for k in range(len(vector[i])-2):
				acumEquipo.append(0)

			j = i

			while j < len(vector) and (vector[i][1] == vector[j][1]):
				acumEquipo[1] += int(vector[j][2])										#En el segundo elemento de acumEquipo voy sumando los minutos totales

				for k in range(len(acumEquipo)-2):
					acumEquipo[k+2] += (float(vector[j][k+3]) * float(vector[j][2])	) 	#En los demas elementos de acumEquipo voy sumando las estadisticas por los minutos
				j += 1

			i = j
			for k in range(len(acumEquipo)-2):
				acumEquipo[k+2] = acumEquipo[k+2] / acumEquipo[1]
			
			for l in range(len(acumEquipo)-2):
				output.write(str(acumEquipo[l+2]) + ' ')
			output.write('\n')
		else:
			i += 1

	anio += 1
	output.close()

g.close()
