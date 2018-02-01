# coding: utf-8


from lib import *
import os

linguagens = ['.cpp', '.py', '.java', '.c', '.pas']

try:
	f = open ('resultados.txt', 'w')
	
	print "\ntestando estrutura dos problemas...",
	problems = Problem.getProblems()
	print "\tok"
	
	print "testando nome dos arquivos...",
	flag = FilesChecker.check(problems, linguagens)	
	
	if flag == False:	
		print "\tok"
	
	print "iniciando correcao dos alunos...\n\n"
	
	resumo = []
	
	for aluno in os.listdir("alunos"):
		
		print "Aluno: " + aluno
		f.write ("Aluno: " + aluno + '\n')
		
		total = 0
		
		for problem in problems:
			c = Correcao.corrigir (problem, aluno)
			total += c[0]
			
			print c[1] + '\n'
			f.write (c[1] + '\n\n')
		
		print "Total: " + str(total) + '\n'
		f.write ("Total: " + str(total) + '\n\n')
		
		resumo.append ((total, aluno))
		
		print '------------------------------------------------'
		f.write ('------------------------------------------------\n')
	
	resumo.sort(reverse=True)
	
	k = 1;
	
	for r in resumo:
		print " %2d\t%6.2f %s" % (k, r[0], r[1])	
		f.write (" %2d\t%6.2f %s\n" % (k, r[0], r[1]))
		k += 1

	print "\n"
	f.write ('\n')
	
	f.close()
except Exception as e:
	print "\n\tERRO " + str(e) + '\n'
