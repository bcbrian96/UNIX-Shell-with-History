Project 2: Shell with History

CMPT 300 D100: Operating Systems I
Instructor: Arrvindh Shriraman 

Group Mu
Brian Lee 301250913 bblee@sfu.ca
SeongJin Kim 301258579 ska158@sfu.ca

This assignment contains shell.c, Makefile, and README.md in the Ass2.tar.gz file.
The purpose of this project was to develop a simple UNIX shell that accepts user commands and then executes each command in a seperate process.
The technique used for implementing the shell interface was to have the parent process first read what the user enters on the command line, and then create a seperate child process that performs the command.
In addition, internal commands such as: exit, pwd, cd were implemented.
Finally, a history feature was created. The shell was modified to provide a history feature that allows the user access up to the ten most recently entered commands.