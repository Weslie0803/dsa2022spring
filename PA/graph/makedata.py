import random

n = random.randrange(1,200000)
n = 200000
print(n)
for _ in range(0,n):
    x = random.randrange(0,2**31)
    print(x, )
# print("\n")

for _ in range(0,n):
    y = random.randrange(0,2**31)
    print(y,)
# print("\n")

m = random.randrange(1,200000)
print(m)
for _ in range(0,m):
    px = random.randrange(0,2**31)
    py = random.randrange(0,2**31)
    print(px, py)