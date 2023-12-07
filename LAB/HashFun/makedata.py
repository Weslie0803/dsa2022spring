import os

# 数据1：从poj中随机选取100000
os.system("./iofile/makedata -input poj -insert 100000 -query 100000 -output ./iofile/1.in")
# 数据2：从hdu中随机选取100000
os.system("./iofile/makedata -input hdu -insert 100000 -query 100000 -output ./iofile/2.in")
# 数据3：从poj中随机选取1000
os.system("./iofile/makedata -input poj -insert 1000 -query 1000 -output ./iofile/3.in")
# 数据4：从hdu中随机选取1000
os.system("./iofile/makedata -input hdu -insert 1000 -query 1000 -output ./iofile/4.in")
# 数据5：从poj中选取100000高命中
os.system("./iofile/makedata -on -input poj -insert 100000 -query 100000 -output ./iofile/5.in")
# 数据4：从hdu中随机选取1000
os.system("./iofile/makedata -on -input hdu -insert 100000 -query 100000 -output ./iofile/6.in")
