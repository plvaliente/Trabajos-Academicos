#!/bin/bash

# Modo de uso:
# ./obtenerStatsJugadores.sh archivoSalidaConTodasLasEstadisticas.txt
# Deja en el archivo pasado como parametro las estadisticas 
# indicadas en la tercera linea de ../stats/params.txt comprendidas
# entre los anios indicados en la primera linea de dicho archivo.

param=$1

if [ $# != 1 ]; then
	echo "Es necesario pasar un argumento."
	exit 1;
fi

mkdir -p ../estadisticasJugadores
salida=../estadisticasJugadores/$param
rm -f $salida

paramsDir=../stats/params.txt
statsDir=../stats/totals

intervalo=$(head -n 1 $paramsDir)
IFS=' ' read -r -a estadisticas <<< $(sed '3q;d' $paramsDir)

inicio=${intervalo[0]}
final=${intervalo[1]}

for a in $(seq $inicio $final); do

	b="$a"
	salida2="$salida$b"
	rm -f $salida2

	stats=$(find $statsDir -maxdepth 1 -name "*$a*")
	# Remover espacios en blanco
	sed -i 's/ //g' $stats $stats
	# Remover *
	sed -i 's/*//g' $stats $stats
	# Si un valor esta vacio agregar 0
	sed -i 's/,,/,0.0,/g' $stats $stats
	
	cat $stats | while read line
	do
		if [ "$line" != "" ]; then
			value=$(echo $line | cut -d',' -f1)
			echo -n $value >> $salida2
			for e in "${!estadisticas[@]}"; do
				echo -n ',' >> $salida2
				value=$(echo $line | cut -d',' -f"${estadisticas[$e]}")
				echo -n $value >> $salida2
			done
			echo " " >> $salida2
		fi
	done
done