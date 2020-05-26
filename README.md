# Get_Block_Implementation
Command Line Linux Shell for simulation of allocating disk blocks function of Operating System


## Description :
- Language – C++
- Approach – Multithreading
- IDE – Visual Studio Code

## Commands :
- echo------Printing HashQueue, FreeList and ProcessList
- process----Creating process
- clear-----Clear the screen
- help------Open the help section

### echo :
It take only one parameter.
- hashqueue for printing HashQueue
- freelist for printing FreeList
- processlist for printing ProcessList

### process - Create processes :
It takes any number of parameter as a file name
- for each file name a new process is being created


## Running the Program :
- Open terminal/Command prompt and change directory to the folder of the
project ( BufferCache ).
- *Linux – Type<br>
```make```
- *Windows – Check out GnuWin's make, which provides a native port for
Windows (without requiring a full runtime environment like Cygwin).
- Type – ```make clean```<br>
for removing compiled files of header files.
- run - ```./bufferCache```
-----------------------------------------------------------------------------
- This command invokes main.cpp file and create a shell of bufferCache.
- `main.cpp` initializes the buffers in the freelist.
- You can check by using - ```echo hashqueue``` and ```echo freelist``` command
that block is added to the both hashqueue and freelist.
- Use `process` command for creating new processes. This creates threads as the number of filename given
which runs independently in the background until block is allocated.
e.g ```process input1.txt input2.txt input3.txt``` for each filename a new thread is being created.
- run ```echo processlist``` command to check that process is added to the
processlist and it displays the process ID provided by the OS.
- If requested block is unlocked and present in freelist then it is allocated to
that process after that particular thread process terminates and removed
from the processlist.
- But if block is marked as delayed write, then a 20 seconds simulated
asynchronous write has been done and after that block is available to
allocate.
- use ```help``` command for further help.
