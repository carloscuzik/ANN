##############################################################################
#   Integrantes:                                                             #
#       -> CARLOS EDUARDO CUZIK ... (06):function_01                         #
#       -> JOÃO VITOR PEREIRA ..... (14):function_02                         #
#       -> PYETTRA FERREIRA ....... (24):function_03                         #
#                                                                            #
#   Objetivo: Construir e avaliar o método da Bisseccao com diferentes       #
#             funções de entradas e intervalos                               #
#                                                                            #
#   Descrição: Utilização da biblioteca padrão do python3 para as funções    #
#              seno, cosseno e a contante de Euler.                          #
#                                                                            #
#   Observações:                                                             #
#       -> Utilizar o python 3.0 para a execução do programa.                #
#       -> Trocar a função na chamada do método da bisseccao.                #
##############################################################################

import math as mt

def function_01(x):
	return mt.sin(x)- (mt.e**x)

def function_02(x):
	return mt.e**(mt.cos(x)) - x

def function_03(x):
	return (2.0**x) - (x/2.0) - (2.0*x)

#metodo da bisseccao
def bisseccao(x1, x2, tolerance, f):
	if(f(x1) * f(x2) > 0):
		print("Os pontos não setisfazem a hipótese inicial")
		return -1;
	x_middle = (x1+x2)/2.0
	while(abs(f(x_middle))>=tolerance):
		if(f(x1) * f(x_middle) > 0):
			x1 = x_middle
		else:
			x2 = x_middle
		x_middle = (x1+x2)/2.0
	return x_middle;

def main():
	print(bisseccao(-5,0,0.0001, function_01))
	print(bisseccao( 0,2,0.0001, function_02))
	print(bisseccao( 2,3,0.0001, function_03))

if __name__ == '__main__':
    main()