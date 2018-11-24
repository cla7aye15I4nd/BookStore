#coding=utf-8
import os
import time
exe = 'bookstore'

temp_dir = 'temp'

test_name = [
    'user test 1',
    'user test 2',
    'user test 3',
    'book test 1',
    'book test 2',
    'book test 3',
    'file test 1',
    'pressure test 1',
    'file test 2',
    'pressure test 2',
]
test_loc = list(map(lambda x: 'testcase'+str(x),range(1,11)))

for i in range(6):
    nw = time.time()
    k = test_name[i]
    loc = test_loc[i]
    os.system('mkdir '+temp_dir)
    os.system('cp '+exe+' '+temp_dir+'/bookstore')
    command = 'cp '+'test_data/'+loc+'.txt '+temp_dir+'/command.txt;cd '+\
        temp_dir+';./'+'bookstore > ans.txt 2> cerr.txt;cd ..'
    os.system(command)
    result = os.system('cmp test_data/'+loc+'_ans.txt '+temp_dir+'/ans.txt')
    os.system('rm -r '+temp_dir)
    if result != 0:
        print('case '+str(i+1)+' failed')
        continue
        #exit(1)
    print('case '+str(i+1)+': '+str(k)+"\t-\033[1;32mACCEPT\033[0m-  time:"+str(round(time.time()-nw,3))+'s')

import sys

for i in range(6,8):
    nw = time.time()
    k = test_name[i]
    loc = test_loc[i]
    os.system('mkdir '+temp_dir)
    os.system('cp '+exe+' '+temp_dir+'/bookstore')
    with open("test_data/"+loc+"/config.txt",'r') as f:
        s = int(f.readline())
        for j in range(s):
            command = 'cp -f '+'test_data/'+loc+'/'+str(j+1)+'.txt '+temp_dir+'/command.txt;cd '+\
                temp_dir+';./'+'bookstore >> ans.txt 2>> cerr.txt;cd ..'
            os.system(command)
    result = os.system('cmp test_data/'+loc+'/ans.txt '+temp_dir+'/ans.txt')
    if result != 0:
        print('case '+str(i+1)+' failed')
        os.system('rm -r '+temp_dir)
        continue
    print('case '+str(i+1)+': '+str(k)+"\t-\033[1;32mACCEPT\033[0m-  time:"+str(round(time.time()-nw,3))+'s')
    os.system('rm '+temp_dir+'/bookstore')
    os.system('rm '+temp_dir+'/command.txt')
    if i == 7:
        sys.stdout.write("\tdatabase size: ")
        sys.stdout.flush()
        os.system('du -h --max-depth=1 temp')
    os.system('rm -r '+temp_dir)
