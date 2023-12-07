a = open("output1.txt")
b = open("output2.txt")
c = int(a.read()) - int(b.read())
print(c)