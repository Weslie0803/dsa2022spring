import os
from subprocess import run
from time import time

make = "make "
exe = "./"
cmd = "main"

"""# 生成可执行文件
for i in range(1, 10):
    prog = cmd + i.__str__()
    os.system(make + prog)
"""
# 测试开始
for i in range(1,10):
    for j in range(1,7):
        tick = time()
        run("./main" + i.__str__(), stdin=open("./iofile/" + j.__str__() + ".in"), 
            stdout=open("./iofile/" + i.__str__()  + "-" + j.__str__() + ".out", "w"), shell=True).check_returncode()
        print("%d-%d: %f s" % (i, j, time() - tick))