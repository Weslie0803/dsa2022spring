import random
import subprocess
seed = "QWERTYUIOPASDFGHJKLZXCVBNM"
count = 0
n = random.randrange(0,5)
sa = []
for i in range(0,n):
    while(True):
        a = random.choice(seed)
        if i == 0:
            count = 1
        elif a == sa[i-1]:
            if count == 1:
                count = 2
            elif count == 2:
                continue
        else:
            count = 1
        break

    sa.append(a)
ini = "".join(sa)

print(ini)

m = random.randrange(0,500000)
print(m)


for i in range(0,m):
    k = random.randrange(0,n+1)
    s = random.choice(seed)
    print(k,s)

    p = subprocess.Popen('./standard', shell=False, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    inp = ini + "\n" + "1\n" + str(k) + " " + s + "\n"
    out = p.communicate(inp.encode())[0]
    ini = out.decode()
    n = len(ini) - 1