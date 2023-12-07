import random

def random_str(slen=10):
    seed = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()_+=-"
    sa = []
    for i in range(slen):
        sa.append(random.choice(seed))
    return ''.join(sa)

def random_cm():
    seed1 = "<>IDSR"
    seed2 = "LR"
    seed3 = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()_+=-"
    sa = []
    a = random.choice(seed1)
    sa.append(a)
    if(a == '<' or a == '>' or a == 'D' or a == 'I'):
        sa.append(' ')
        sa.append(random.choice(seed2))
        if(a == 'I'):
            sa.append(' ')
            sa.append(random.choice(seed3))
    return ''.join(sa)

s = random_str(10)
print(s)
n = 10
print(n)
for i in range(0,n):
    print(random_cm())

