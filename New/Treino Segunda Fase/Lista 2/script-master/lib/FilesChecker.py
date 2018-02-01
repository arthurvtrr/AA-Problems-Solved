
import os
from lib import EditDistance

def corrigir_espacos():

	invalido = False

	for filename in os.listdir("alunos"):
		if " " in filename:
			if invalido == False:		
				print '\n\nNome de aluno com espaco:'
		
			print '\t' + filename
			invalido = True

	if invalido:

		print '\ncorrigir nome de alunos com espaco automaticamente? (s/n)',

		ans = raw_input()
		if ans == 'n' or ans == 'N':
			raise Exception ("Nome das pastas dos alunos invalido, corrija manualmente")
		else:
			os.system ("find -name '* *' -type d | rename 's/ /_/g'")

	return invalido

def verificar_extensoes (linguagens):

	for aluno in os.listdir("alunos"):
		for filename in os.listdir("alunos/" + aluno):
			extensao = os.path.splitext(filename)[1]
			if os.path.isdir("alunos/" + aluno + "/" + filename):
				raise Exception (aluno + "/" + filename + " eh um diretorio ")
			if extensao not in linguagens:
				raise Exception ("Linguagem invalida do aluno " + aluno + ": " + filename)
			
	return False


def corrigir_arquivos(problems):

	invalido = False	

	for aluno in os.listdir("alunos"):
		arquivos = []
		for filename in os.listdir("alunos/" + aluno):

			arquivo = os.path.splitext(filename)[0]
			extensao = os.path.splitext(filename)[1]

			existeProblema = False
			proximo = (1000, "")
		
			for p in problems:
				if arquivo == p.getName():
					existeProblema = True
					if p.getName() in arquivos:
						raise Exception (aluno + " com duas solucoes para o mesmo problema")
					arquivos.append(p.getName())
				else:	
					distance = EditDistance.edit_distance (p.getName(), arquivo)
					if proximo[0] > distance:
						proximo = (distance, p.getName())
						
			if existeProblema == False:
				
				if invalido == False:
					print "\n\nNome de arquivo invalido:"		
		
				invalido = True
				
		
				print "\nSubstituir \"" + filename + "\" por \"" + proximo[1] + extensao + "\" do aluno " + aluno + "? (s/n)"
				ans = raw_input()
				if ans == 'n' or ans == 'N':
					raise Exception ("Nome de problema invalido do aluno " + aluno + ": " + filename)
				else:
					os.rename ("alunos/" + aluno + "/" + filename, "alunos/" + aluno + "/" + proximo[1] + extensao)
					
					if proximo[1] in arquivos:
						raise Exception (aluno + " com duas solucoes para o mesmo problema")
					arquivos.append (proximo[1])
	return invalido


def check(problems, linguagens):
		
	a = corrigir_espacos() 
	b = verificar_extensoes(linguagens) 
	c = corrigir_arquivos(problems)
	return a or b or c

	
