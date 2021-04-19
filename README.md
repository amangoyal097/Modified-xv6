# Modified-xv6

Added some system calls to display process infromation and implemented cpu schedulers like MLFQ, FCFS, RR to manage processes better

## INSTRUCTIONS

    1. Install qemu in ur local machine
        sudo apt-get install qemu
    2. RUN
        make qemu-nox SCHEDULER=<RR,FCFS,PBS,MLFQ> (One out of the four)

### waitx

    -etime is set to ticks
    -rtime is set to the process rtime which is update on every clock tick fort the running process
    -ctime ist the creation time set in allocproc
    -stime is the time the process sleeps incremented on the clock tick the process is sleeping
    -wtime is etime - rtime - ctime - stime

### time

    -it execs the command and uses waitx to wait on the process

### ps

    -made a user program and called the system call print_ps() which prints the information
    -wait time is resetted everytime it is picked by the scheduler and also if it changes queues in the case of MLFQ

### FCFS

    -disabled yield() in trap(disabled preemption)
    -found the minimum creation timed process and executed it

### PBS

    -found the maximum priority among processes
    -executed the maximum priority process
    -after it has stopped running
    	if it was yeilded by a higher priority process, the loop breaks and then in the next iteration the process repeats
    -otherwise if it stopped naturally then round robin is followed
    -made the system call and user programs required to set the priority

### MLFQ

    -in the creation of the processes, initialize the required values
    -after the scheduler selects the process, assign the time slice accordingly to the process(1 time slice is 2 tick)
    -runnable processes not in queue are pushed before scheduling
    -for the scheduler part traced the queue from high to low and left to right and whenver I found the process which is RUNNABLE, i ran the process
    -pop the process from the queue
    -after it is finished running if it was found sleeping then it is added to the same queue
    -it the process execeeded their time slice then they are added to the next lower queue
    -for traps every process which have waited for more time (I 1assigned 40 ticks) are promoted to the next higher queue

### EXPLOITATION BY THE PROCESS

    -The process can exploit the policy by relinquishing control every time it is about to use all it's time slice and then get added to the same queue which is better than being demoted to a lower queue and the process will never leave the queue it was assigned

### PERFORMANCE COMPARISON BY USING THE BENCHMARK PROGRAM(5 Processes)

    -MLFQ
    	-	Wait Time: 0
    		Run Time: 4
    		Total Time: 912
    -PBS
    	-	Wait Time: 1
    		Run Time: 3
    		Total Time: 923
    -FCFS
    	-	Wait Time: 0
    		Run Time: 3
    		Total Time: 929
    -RR
    	-	Wait Time: 1
    		Run Time: 3
    		Total Time: 917

### Observation

![MLFQ graph](https://github.com/amangoyal097/Modified-xv6/blob/main/modified-xv6/MLFQ_graph.png?raw=true)

<br/>I/O bound processes staylonger in the lower priority queues and the CPU Bound are moved to higher priority queues because they exhaust their time slice while I/O bound stay in the lower priority due to less CPU time
