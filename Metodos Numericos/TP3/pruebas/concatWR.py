g = open('./stats/params.txt', 'r')
params = g.readline()
params = params.split(" ")
inicio = int(params[0])
fin = int(params[1])

output = open('./winrates.txt', 'w')

m = range(inicio,fin+1)
for i in m: 
	l = []
	with open('./stats/winrate/leagues_NBA_'+ str(i) +'_winrate.csv', 'r') as f:
		for line in f:
			line = line.strip()
		   	if len(line) > 0:
		    	l.append(float(line.rstrip(" \n")))
	for a in range(len(l)):
		output.write(str(l[a]))
		output.write('\n')
		#print "\n"
