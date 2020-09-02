import sys
import argparse
import string
import unicodedata

parser = argparse.ArgumentParser()
parser.add_argument("-i", "--inF", help="Nombre del archivo de Entrada")
parser.add_argument("-t", "--test", help="Test Elegido")
parser.add_argument("-n", "--nproc", help="np Elegido")
args = parser.parse_args()

if args.inF:
    fhand = open(args.inF)
    lines = fhand.readlines()

if args.test:
    numeroDeTest = int(args.test)

if args.nproc:
    np = int(args.nproc)

def strip_accents(s):
	return ''.join((c for c in unicodedata.normalize('NFD', s) if unicodedata.category(c) != 'Mn'))


def testMember():
	ok = True 
	for i in range(len(lines)):
		if i <= 3:
			if not "no esta" in strip_accents(lines[i].rstrip('\n').decode('utf-8')):
				ok = False
				break
		if i == 10:	
			if not "no esta" in strip_accents(lines[i].rstrip('\n').decode('utf-8')):
				ok = False
				break
		if i >= 11 and i != 14:	
			if not "> esta" in strip_accents(lines[i].rstrip('\n').decode('utf-8')):
				ok = False
				break

	if ok:
		print "TEST MEMBER OK!"				
	else:
		print "TEST MEMBER FALLO :("

def testLoad():
	ok = True
	n_libre = 0;
	FreeBef = False; 
	for line in lines:
		linea = strip_accents(line.rstrip('\n').decode('utf-8'))
		if "Free" in linea:
			n_libre = int(linea.split()[2])
			FreeBef = True
		if ("Loading" in linea) and FreeBef:
			FreeBef = False
			if n_libre != int(linea.split()[1]):
				ok = False
				break
		if "esta" in linea:
			if "no esta" in linea:
				ok = False
				break		

	if ok:
		print "TEST LOAD OK!"				
	else:
		print "TEST LOAD FALLO :("

def testMax():
	ok = True
	for line in lines:
		linea = strip_accents(line.rstrip('\n').decode('utf-8'))
		if "maximo" in linea:
			if not "<duck,4>" in linea:
				ok = False
				break
	if ok:
		print "TEST MAXIMO OK!"				
	else:
		print "TEST MAXIMO FALLO :("


if numeroDeTest == 0:
	testMember()

if numeroDeTest == 1:
	testLoad()
if numeroDeTest == 2:
	testMax()	

