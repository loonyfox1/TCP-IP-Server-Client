import subprocess
import random
import sys

'''
1. For show result data file:
    run "od -tfD <filename>.bin" in terminal
2. To fix error "Address already in use":
    run "sudo lsof -i:<port>"
    then "sudo kill <PID>"
3. If you want to change port or ip, do not forget to change it for server (OzzyServer/config.ini file)
4. To test the server throughput, change NUM_CLIENTS, but remember about the number of open files limits (about 500 in generall)
5. Sorry for creating so many config and data files. For deleting:
    run "find . -name "data*.bin" -delete; find OzzyClient/ -name "config*[0-9].ini" -delete"
'''

NUM_CLIENTS = 100
PORT = 54000
HOST = "127.0.0.1"
N_SAMPLES = 1e6

MAX_DOUBLE = 1e9
MIN_DOUBLE = -MAX_DOUBLE

def getNextConfig(port, host, number, i):
    filename = "OzzyClient/config"+str(i)+".ini"
    with open(filename,"w") as file:
        file.write(
        "PORT = "+str(port)+"\n"+
        "HOST = "+host+"\n"+
        "NUMBER = "+str(number))
    return filename

'''
6. Comment Server subprocess (next 2 lines) if you want to run server manually
'''
server = ("OzzyServer/bin/main", "OzzyServer/config.ini")
popenServer = subprocess.Popen(server, stdout=subprocess.PIPE, stderr = subprocess.PIPE)

clients = []
for i in range(NUM_CLIENTS):
    number = format(random.uniform(MIN_DOUBLE, MAX_DOUBLE),'f')
    configfile = getNextConfig(PORT, HOST, number, i)
    datafile = "data"+str(i)+".bin"
    client = ("OzzyClient/bin/main", configfile, datafile)
    clients.append(subprocess.Popen(client, stdout=subprocess.PIPE, stderr = subprocess.PIPE))
    print("Client "+str(i)+" with "+configfile+" and number "+str(number)+" runs")


for cl in clients:
    cl.wait()
    (out, err) = cl.communicate()
    print (out.decode("utf-8"), err.decode("utf-8") )
