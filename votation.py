#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Aug  3 14:18:54 2018

@author: vincent

@brief simule un vote par classement à partir d'un fichier de candidats
Le fichier créé selon un format csv avec des \t comme séparateurs.

\note il n'y a pas de \t avant le \n de chaque fin de ligne.
"""
import os
import sys, getopt
import time
from random import randint

def main(argv):
    candidats = '' # liste des candidats (fichier entrée)
    vote = '' # résultat du vote (fichier sortie)
    votants = 0 # nombre de votants
    try:
        opts, args = getopt.getopt(argv,"hi:v:o:",["ifile=","nb=","ofile="])
    except getopt.GetoptError:
        print (sys.argv[0],' -i <candidats> -v <nb> -o <vote>')
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print (sys.argv[0],' -i <candidats> -v <nb votants> -o <vote>')
            sys.exit()
        elif opt == '-v':
            votants = arg
        elif opt in ("-i", "--ifile"):
            candidats = arg
        elif opt in ("-o", "--ofile"):
            vote = arg
    print ('Input file is ', candidats)
    print ('Output file is ', vote)
    print ('Nb de votants = ',votants)

    candf = open(candidats, "r")
    votef = open(vote, "w")

    candlist = []
    for line in candf:
        candlist.append(line.strip(' \n'))
    print(candlist)
    nbcand = len(candlist)

    entete = 'ID votant\tDate\tCode vote' # début d'entête du fichier
    for c in candlist:
        entete=entete+'\t'+c # on complète
    print(entete) # pour vérif.
    votef.write(entete+'\n') #écrit l'entête du fichier

    # boucle sur les votants
    for v in range(1,int(votants)+1):
        voteline = str(v) # Id du votants
        ts = time.time() # timestamp
        readable = time.ctime(ts) #human readable timestamp
        voteline = voteline+'\t'+readable+'\t'+'Vote XXX'
        for c in candlist: # même ordre que dans l'entête
            pick = randint(1,nbcand) # ordre aléatoire
#            print("random=",c,pick) # pour vérif
            voteline=voteline+'\t'+str(pick)
        votef.write(voteline+'\n')
    candf.close()
    votef.close()

if __name__ == "__main__":
    main(sys.argv[1:])
