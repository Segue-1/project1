
How to use.

1. Use makefile to compile. Just type "make"

Type "make clean" to remove for recompilation.

2. Type "./runsim.exe -n 5 < testing.data" to run.

There are a couple issues.  If you type -nm then it will give multiple error messages due to the fork.  
Any other invalid combination seems to work fine.  So -m will give one error. 

The other issue is that the number following the option doesn't do anything. I'm not sure why but I think
there's something wrong with my pr_limit.  

What this program will do is that it will run everything in testing.data and it will use the arguments
as well.  

Version control was used on github. 
