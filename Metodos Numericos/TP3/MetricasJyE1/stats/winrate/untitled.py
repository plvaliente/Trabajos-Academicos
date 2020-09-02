
m = range(1987,2017)
for i in m: 
	l = []
	with open('leagues_NBA_'+ str(i) +'_winrate.csv', 'r') as f:
	  for line in f:
	    line = line.strip()
	    if len(line) > 0:
	      l.append(map(float, line.split(',')))
	for a in range(len(l)):
		print l[a][1] 
		#print "\n"
