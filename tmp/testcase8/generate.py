#coding=gbk
file = open('1.txt','w')
file.write('useradd worker worker_password 3 鏋楁棴\nlogout\nsu worker worker_password\n')

for i in range(1000):
    file.write('select 123456789'+str(i)+'\nmodify -name="'+\
        str(i)+"'s book\" -keyword=\""+\
        str(i)+'|'+str(i+1)+'|'+str(i+2)+'" -author="'+\
        str(i*2)+'" -price='+\
        str(i)+'\n')

file.write("exit\n")
file.close()

for i in range(2,101):
    with open(str(i)+'.txt','w') as f:
        f.write('logout\nsu worker worker_password\n')
        if i % 3 == 0:
            f.write('show -ISBN=123456789'+str(i)+'\n')
        elif i % 3 == 1:
            f.write('show -author="'+str(2*i)+'"\n')
        else:
            f.write('show -keyword="'+str(i)+'"\n')
        f.write("exit\n")

