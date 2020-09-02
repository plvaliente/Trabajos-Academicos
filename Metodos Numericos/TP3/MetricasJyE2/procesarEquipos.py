import sys 
#Buscar los anios a procesar
ruta = sys.argv[1] 
paramsfile = open('./stats/params.txt', 'r')
params = paramsfile.readline()
params = params.split(" ")
inicio = int(params[0])
fin = int(params[1])
years = range(inicio,fin+1)


#Guardar las estadisticas de equipos por anio
matriz = []
for i in years:
	vectori = []
	f = open('./estadisticasEquipos/'+str(ruta)+str(i), 'r')
	for line in f:
		if(line[0] != 'R'):
			line = line.rstrip(" \n")
			vectori.append(line.split(","))
	matriz.append(vectori)
	f.close()

i = 0
anio = inicio

for yeari in matriz:

	output = open('./estadisticasEquipos/equipos'+str(anio)+'.txt', 'w')

	# ordeno yeari por abreviatura
	for k in range(len(yeari)):
		numeroEquipo = '0'
		nombreEquipo = yeari[k][1]
		equiposfile = open('./stats/equipos/equipos_'+str(anio)+'.txt', 'r')
		for line in equiposfile:
			line2 = line.rstrip(" \n")
			line2 = line2.split(",")

			if line2[1] == nombreEquipo:
				numeroEquipo = line2[0]
		yeari[k][1] = int(numeroEquipo)
		equiposfile.close()

	yeari.sort(key= lambda numero: numero[1])

	for team in yeari:	
		for l in range(len(team)-2):
			output.write(str(team[l+2]) + ' ')
		output.write('\n')

	anio += 1

	output.close()

f.close()
paramsfile.close()