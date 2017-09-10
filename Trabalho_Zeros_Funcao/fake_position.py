##############################################################################
#   Integrantes:                                                             #
#       -> CARLOS EDUARDO CUZIK ... (06):function_01                         #
#       -> JOÃO VITOR PEREIRA ..... (14):function_02                         #
#       -> PYETTRA FERREIRA ....... (24):function_03                         #
#                                                                            #
#   Objetivo: Construir e avaliar o método da Falsa Posição com diferentes   #
#             funções de entradas e intervalos                               #
#                                                                            #
#   Descrição: Utilização da biblioteca padrão do python3 para as funções    #
#              seno, cosseno e a contante de Euler.                          #
#                                                                            #
#   Observações:                                                             #
#       -> Utilizar o python 3.0 para a execução do programa.                #
#       -> Trocar a função na chamada do método da Posição Falsa.            #
##############################################################################

import math as mt

def function_01(x):
	return mt.sin(x)- (mt.e**x)

def function_02(x):
	return mt.e**(mt.cos(x)) - x

def function_03(x):
	return (2.0**x) - (x/2.0) - (2.0*x)

def secant_root(x1,x2,f):
	return x2 - ((f(x2)*(x2-x1))/(f(x2)-f(x1)))

# Método da Posição Falsa
def fake_position(x1, x2, tolerance, f):
	if(f(x1) * f(x2) > 0):
		print("Os pontos não setisfazem a hipótese inicial")
		return -1;
	x_middle = secant_root(x1,x2,f)
	while(abs(f(x_middle))>=tolerance):
		if(f(x1) * f(x_middle) > 0):
			x1 = x_middle
		else:
			x2 = x_middle
		x_middle = secant_root(x1,x2,f)
	return x_middle;

def main():
	print(fake_position(-5,0,0.0001, function_01))
	print(fake_position( 0,2,0.0001, function_02))
	print(fake_position( 2,3,0.0001, function_03))

if __name__ == '__main__':
    main()