#!/bin/usr/python
import os
import subprocess
import time
f= open("a.txt", "r")
g=open("cpu.txt","a")
h=open("cs.txt","a")
off=0
start=time.time()
for i in range(150):
    f.seek(0)
    time.sleep(15)
    subprocess.Popen("perf stat -o a.txt -p 3189 sleep 5",shell=True);
    l=f.readlines()
    s1=l[5].split()
    s2=l[6].split()
    g.writelines(s1[4]+"\t"+str(time.time()-start+off)+'\n')
    h.writelines(s2[0]+"\t"+str(time.time()-start+off)+'\n')
f.close()
g.close()
h.close()
