
import os

class Problem:
	
	def __init__ (self, name, src):
		
		self.name = name
		self.number_of_tests = len(os.listdir(src))
		
		self.tests = [ [] for i in range (self.number_of_tests) ]
		
		for i in range (self.number_of_tests):
			
			test_dir = src + '/' + str(i + 1)
			
			if os.path.isdir (test_dir) == False:
				raise Exception ('Pastas de testes do problema \'' + self.name + '\' enumerados incorretamente')
			
			numero_de_casos = len (os.listdir(test_dir))
			
			if (numero_de_casos % 2 == 1):
				raise Exception ('Casos do teste \'' + str(i + 1) + '\' do problema \'' + self.name + '\' enumerados incorretamente')
			
			numero_de_casos /= 2
			
			for j in range (numero_de_casos):
				_in = test_dir + '/' + 'in' + str (j + 1)
				_out = test_dir + '/' + 'out' + str (j + 1)
				if os.path.isfile (_in) == False or os.path.isfile (_out) == False:
					 raise Exception ('Casos do teste \'' + str(i + 1) + '\' do problema \'' + self.name + '\' enumerados incorretamente')
				
				self.tests[i].append ((_in, _out))
	
	def getName (self):
		return self.name
	
	def getNumberOfTests (self):
		return self.number_of_tests
		
	def getCasosDoTeste (self, i):
		return self.tests[i]
		

def getProblems():
	
	if os.path.isdir('problemas') == False:
		raise Exception ('Pasta com os problemas nao encontrado')
		
	problems = []
	
	for problem in os.listdir("problemas/"):
		problems.append (Problem (problem, 'problemas/' + problem))
	
	return problems
