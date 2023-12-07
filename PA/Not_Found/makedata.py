import random

n = random.randrange(1,2**24+1)
sa = []

for i in range(n):
    sa.append(random.choice("01"))

print("".join(sa))