import numpy  as np
import random
import string


A = np.random.randint(0,9, (500000,4))

codes = [ str(code[0]) +
          str(code[1]) + 
          str(code[2]) + 
          str(code[3]) + 
          random.choice(string.ascii_letters).upper() +
          random.choice(string.ascii_letters).upper()
          for code in A ]
strfile = 'codes_500K.txt'
with open(strfile, 'w+') as f :
    for code in codes :
        f.write(code + '\n')

print('done')
