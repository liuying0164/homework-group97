from hashlib import md5,sha256
import os
import time
start=time.time()
flag=b'flag{welcome}'
secrets=os.urandom(15)
m=b'admin'
k1=sha256(secrets+m+m).hexdigest()
print("随机生成的k1为：",k1)
key=input("输入key的16进制:")
cipher=input("输入哈希值")
s1=secrets+m+bytes.fromhex(key)
k2=sha256(s1).hexdigest()
print(k2)
if cipher==k2:
    print(flag)
end=time.time()
print("运行时间：",end-start,"ms")
