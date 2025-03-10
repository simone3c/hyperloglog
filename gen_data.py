from random import randint
import sys

n = int(sys.argv[1])
l = [randint(1, (1 << 32) - 1) for _ in range(n)]
s = set(l)
with open("data.txt", "w") as f:
    f.write(str(len(l)) + '\n' + str(len(s)) + '\n')
    for i in l:
        f.write(str(i) + '\n')
