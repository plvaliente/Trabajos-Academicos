#!/bin/bash

## TEST Member
( mpiexec -np $1 ./dist_hashmap 1 < testMember.in ) > testMember.log
python test.py -i testMember.log -t 0

## TEST Load
( mpiexec -np $1 ./dist_hashmap 1 < testLoad.in ) > testLoad.log
python test.py -i testLoad.log -t 1


## TEST AddAndInc
( mpiexec -np $1 ./dist_hashmap 1 < testAdd.in ) > testAdd.log
if [[ $1 < 4 ]]; then
	echo "Para np chicos el Test AddAndInc pierde su confiabilidad"
	echo "porque hay pocos nodos para que sean muchos distintos"
fi
ok=true
for (( i = 0; i < 3; i++ )); do
	( mpiexec -np $1 ./dist_hashmap 1 < testAdd.in ) > Add.tmp.$i.log
done
for (( i = 0; i < 3; i++ )); do
	diff testAdd.log Add.tmp.$i.log	> differ.txt
	if [[ !( -s differ.txt ) ]]; then
		ok=false

	fi
done
for (( i = 1; i < 3; i++ )); do
	diff Add.tmp.0.log Add.tmp.$i.log > differ.txt
	if [[ !( -s differ.txt ) ]]; then
		ok=false
	fi
done
diff Add.tmp.1.log Add.tmp.2.log > differ.txt
if [[ !( -s differ.txt ) ]]; then
	ok=false
fi

if [[ !($ok) ]]; then
	echo "TEST ADD FALLO :("
else
	echo "TEST ADD OK!"
fi	
rm Add.tmp.* differ.txt

## TEST Maximum
( mpiexec -np $1 ./dist_hashmap 1 < testMax.in ) > testMax.log
python test.py -i testMax.log -t 2
