## Introduction
This is the 8th École 42 project, and is about creating a simple shell, where we learn a lot about Shell, processes, UNIX and file descriptors, debbuging, hash tables, lexical analysis and much more.  
Also this is the first e42 project that requires group work, so we learn a lot about mob programming, documentation, git tools like working on different branches and task management as well.

## About the project
The project requires your Shell to:  
- Display a prompt when waiting for a new command.  
- Have a working history.  
- Search and launch the right executable (based on the PATH variable or using a  
relative or an absolute path).  
- Not use more than one global variable. Think about it. You will have to explain  
its purpose.  
- Not interpret unclosed quotes or special characters which are not required by the  
subject such as \ (backslash) or ; (semicolon).  
- Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.  
- Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).  
- Implement redirections:  
	- '<' should redirect input.  
	- '>' should redirect output.  
	- '<<' should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!  
	- '>>' should redirect output in append mode.  
- Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.  
- Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.  
- Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.  
- Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.  
- In interactive mode:  
	- ctrl-C displays a new prompt on a new line.  
	- ctrl-D exits the shell.  
	- ctrl-\ does nothing.  
- Must implement the following builtins:  
	- echo with option -n  
	- cd with only a relative or absolute path  
	- pwd with no options  
	- export with no options  
	- unset with no options  
	- env with no options or arguments  
	- exit with no options  

## Usage:
Install Readline library with `sudo apt-get install libreadline-dev`  
Compile the program `make`  
You're ready to run it, have fun!! `./minishell`  

## Developed by:
[prmarquesz](https://github.com/prmarquesz)  
[GuiMartinelli](https://github.com/GuiMartinelli)  
