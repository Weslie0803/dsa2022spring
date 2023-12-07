sa = []
for i in range(0,512):
    sa.append("XX")
    sa.append("DD")
for i in range(0,512):
    sa.append("A")
    sa.append("A")
    sa.append("B")
    sa.append("B")
sa.append("CCD")
print("".join(sa))

#print(3076)
print(1025)
"""
for i in range(0,1023):
    print(0,"Z")
    print(0,"Y")
print(0,"Z")
print(4094,"D")
print(4092,"X")
print(0,"Z")
print(0,"Y")

for i in range(0,512):
    print(4094,"A")
    print(4094,"B")


print(4095,"C")
"""
for i in range(0,512):
    print(2048,"A")
    print(2048,"B")

print(2049,"C")