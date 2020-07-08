# TCP/IP Server-Client

Test task for OzzyLogik. For test run <code>python3 test.py</code>

1. For show result data file:
    run <code>od -tfD FILENAME.bin</code> in terminal
2. To fix error "Address already in use":
    run <code>sudo lsof -i:PORT</code>
    then <code>sudo kill PID</code>
3. If you want to change port or ip, do not forget to change it for server (OzzyServer/config.ini file)
4. To test the server throughput, change NUM_CLIENTS, but remember about the number of open files limits (about 500 in generall)
5. Sorry for creating so many config and data files. For deleting: run <code>find . -name "data*.bin" -delete; find OzzyClient/ -name "config*[0-9].ini" -delete</code>

Manually running:

1. server <code>./OzzyServer/bin/main OzzyServer/config.ini</code>
2. client <code>./OzzyClient/bin/main OzzyClient/config.ini data.bin</code>

Buided with gcc `version 8.1.0 (Ubuntu 8.1.0-5ubuntu1~16.04)`
