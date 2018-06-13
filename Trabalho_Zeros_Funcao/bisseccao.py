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
#       -> Trocar também os valores iniciais para o método e a tolerância    #
#                                                                            #
#   Run: python3 bisseccao.py                                                #
##############################################################################

import math as mt


def function_01(x):
    return mt.sin(x) - (mt.e ** x)


def function_02(x):
    return mt.e ** (mt.cos(x)) - x


def function_03(x):
    return (2.0 ** x) - (x / 2.0) - (2.0 * x)


def export_latex(data):
    print("\\begin{table}[h!]")
    print("\t\centering")
    print("\t\\begin{tabular}{| c || l | l | l | l |}")
    print("\t\t\hline")
    print(
        "\t\t$ k $"
        + "&"
        + "$ a $"
        + "&"
        + "$ b $"
        + "&"
        + "$ c $"
        + "&"
        + "$ Erro relativo (\%) $"
        + "\\\\"
    )
    k = 0
    for line in data:
        print("\t\t\hline")
        print(
            "\t\t\t"
            + str(k)
            + " & "
            + str(line[0])
            + " & "
            + str(line[1])
            + " & "
            + str(line[2])
            + " & "
            + str(line[3])
            + "\\\\"
        )
        k += 1
    print("\t\t\hline")
    print("\t\end{tabular}")
    print("\t\caption{Método da Bissecção}")
    print("\t\label{table:b:}")
    print("\end{table}")
    print("\n")


# metodo da bisseccao
def bisseccao(a, b, tolerance, f):
    if f(a) * f(b) > 0:
        print("Os pontos não setisfazem a hipótese inicial do teorema de Bolzano")
        return -1
    c = (a + b) / 2.0
    data = []
    data += [[a, b, c, abs((a - b) / a)]]
    while abs((a - b) / a) >= tolerance:
        if f(a) * f(c) > 0:
            a = c
        else:
            b = c
        c = (a + b) / 2.0
        data += [[a, b, c, abs((a - b) / a)]]
        # export_latex(data) # comentar esta opção para não exportar
    return c


def main():
    print(bisseccao(-5, 0, 0.0000001, function_01))
    print(bisseccao(1, 2, 0.0000001, function_02))
    print(bisseccao(2, 3, 0.0000001, function_03))


if __name__ == "__main__":
    main()
