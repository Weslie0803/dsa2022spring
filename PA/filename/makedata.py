import random

N = random.randrange(0,501000)
M = random.randrange(0,501000)
K = random.randrange(0,100)

def random_str(slen=10):
    seed = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()_+=-"
    sa = []
    for i in range(slen):
        sa.append(random.choice(seed))
    return ''.join(sa)

str1 = random_str(N)
str2 = random_str(M)
print(N,M,K)
print(str1)
print(str2)

