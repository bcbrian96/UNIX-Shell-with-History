Project: Shell with History

The purpose of this project was to develop a simple UNIX shell that accepts user commands and then executes each command in a seperate process.
The technique used for implementing the shell interface was to have the parent process first read what the user enters on the command line, and then create a seperate child process that performs the command.
In addition, internal commands such as: exit, pwd, cd were implemented.
Finally, a history feature was created. The shell was modified to provide a history feature that allows the user access up to the ten most recently entered commands.
