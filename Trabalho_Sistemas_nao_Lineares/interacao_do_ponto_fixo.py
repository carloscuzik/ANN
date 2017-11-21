import numpy as np

def erro(x1a, x2a, x1b, x2b):
  return max(abs(x1b-x1a), abs(x2b-x2a)) / max(abs(x1b), abs(x2b))

def eq1(x1,x2):
  return 9.0*x1 - x2**3

def eq2(x1,x2):
  return x1**2 - 6.0*x2 + 1

def prova(x1,x2):
  return (eq1(x1,x2), eq2(x1,x2))

def f1(x1,x2):
  return (x2**3) / 9.0

def f2(x1,x2):
  return (1 + x1**2) / 6.0

def fixed_point(x1,x2):
  k=0
  while(True):
    x1_ant = x1
    x2_ant = x2
    x1 = f1(x1_ant,x2_ant)
    x2 = f2(x1_ant,x2_ant)
    error = erro(x1_ant,x2_ant,x1,x2)
    k+=1
    if(error < 10**-5):
      print str(k) + ' & ' +  str("{0:.7f}".format(x1_ant)) + ' & ' +  str("{0:.7f}".format(x2_ant)) + ' & ' +  str("{0:.7f}".format(error)) + ' \\\\'
      return (x1,x2,error)
    print str(k) + ' & ' +  str("{0:.7f}".format(x1_ant)) + ' & ' +  str("{0:.7f}".format(x2_ant)) + ' & ' +  str("{0:.7f}".format(error)) + ' \\\\'


def main():
  res = fixed_point(0.5,0.5)
  print prova(res[0], res[1])

if __name__ == '__main__':
  main()
