// Shell starter file
// You may make any changes to any part of this file.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COMMAND_LENGTH 1024
#define NUM_TOKENS (COMMAND_LENGTH / 2 + 1)

#define HISTORY_DEPTH 10

char history[HISTORY_DEPTH][COMMAND_LENGTH];
int count = 0;

/**
 * Command Input and Processing
 */

/*
 * Tokenize the string in 'buff' into 'tokens'.
 * buff: Character array containing string to tokenize.
 *       Will be modified: all whitespace replaced with '\0'
 * tokens: array of pointers of size at least COMMAND_LENGTH/2 + 1.
 *       Will be modified so tokens[i] points to the i'th token
 *       in the string buff. All returned tokens will be non-empty.
 *       NOTE: pointers in tokens[] will all point into buff!
 *       Ends with a null pointer.
 * returns: number of tokens.
 */
int tokenize_command(char *buff, char *tokens[])
{
	int token_count = 0;
	_Bool in_token = false;
	int num_chars = strnlen(buff, COMMAND_LENGTH);
	for (int i = 0; i < num_chars; i++) {
		switch (buff[i]) {
		// Handle token delimiters (ends):
		case ' ':
		case '\t':
		case '\n':
			buff[i] = '\0';
			in_token = false;
			break;

		// Handle other characters (may be start)
		default:
			if (!in_token) {
				tokens[token_count] = &buff[i];
				token_count++;
				in_token = true;
			}
		}
	}
	tokens[token_count] = NULL;
	return token_count;
}

/**
 * Read a command from the keyboard into the buffer 'buff' and tokenize it
 * such that 'tokens[i]' points into 'buff' to the i'th token in the command.
 * buff: Buffer allocated by the calling code. Must be at least
 *       COMMAND_LENGTH bytes long.
 * tokens[]: Array of character pointers which point into 'buff'. Must be at
 *       least NUM_TOKENS long. Will strip out up to one final '&' token.
 *       tokens will be NULL terminated (a NULL pointer indicates end of tokens).
 * in_background: pointer to a boolean variable. Set to true if user entered
 *       an & as their last token; otherwise set to false.
 */
 
 void add_history(char *buff){
	 
	 if(count < HISTORY_DEPTH) {
		 strcpy(history[count], buff);
	 }
	 else {
		 for(int i = 0; i < HISTORY_DEPTH - 1; i++){
			 strcpy(history[i], history[i+1]);
		 }
		 strcpy(history[HISTORY_DEPTH-1], buff);
	 }
	 count++;
 }
 
 void display_history(){
	int n = count;
	char count2[10];
	int index = 0;
	
	if(n > HISTORY_DEPTH){
		n = count - (HISTORY_DEPTH-1);
	} 
	else {
		n = 1;
	}
	
	for (int i = n; i <= count; i++){
		sprintf(count2, "%d\t", i);
		write(STDOUT_FILENO, count2, strlen(count2));
		
		write(STDOUT_FILENO, history[index], strlen(history[index]));
		
		index++;
	}
	 
 }
 
void read_command(char *buff, char *tokens[], _Bool *in_background)
{
	*in_background = false;

	// Read input
	int length = read(STDIN_FILENO, buff, COMMAND_LENGTH-1);
	
	if (length < 0) {
		perror("Unable to read command from keyboard. Terminating.\n");
		exit(-1);
	}
	
	if(strlen(buff) > 0) {
		add_history(buff);
	}

	// Null terminate and strip \n.
	buff[length] = '\0';
	if (buff[strlen(buff) - 1] == '\n') {
		buff[strlen(buff) - 1] = '\0';
	}

	// Tokenize (saving original command string)
	int token_count = tokenize_command(buff, tokens);
	if (token_count == 0) {
		return;
	}

	// Extract if running in background:
	if (token_count > 0 && strcmp(tokens[token_count - 1], "&") == 0) {
		*in_background = true;
		tokens[token_count - 1] = 0;
	}
}


/**
 * Main and Execute Commands
 */
int main(int argc, char* argv[])
{
	char input_buffer[COMMAND_LENGTH];
	char *tokens[NUM_TOKENS];
<<<<<<< HEAD
=======
	int stat_loc;
	char wd[PATH_MAX];
	
	
>>>>>>> master
	while (true) {

		// Get command
		// Use write because we need to use read() to work with
		// signals, and read() is incompatible with printf().
		write(STDOUT_FILENO, "> ", strlen("> "));
		_Bool in_background = false;
		read_command(input_buffer, tokens, &in_background);
<<<<<<< HEAD
=======
		
		if (!tokens[0]) {
			continue;
		}
		
		if (strcmp(tokens[0], "history") == 0) {
			
			display_history();
			continue;
		}
		
		
		if (strcmp(tokens[0], "exit") == 0) {
			exit(0);
		}
		
		if (strcmp(tokens[0], "pwd") == 0) {
				write(STDOUT_FILENO, wd, strlen(wd));
				write(STDOUT_FILENO, "\n", strlen("\n"));
				continue;
		}
		
		if (strcmp(tokens[0], "cd") == 0) {
			if (chdir(tokens[1]) < 0) {
                write(STDOUT_FILENO, "Invalid directory.\n", strlen("Invalid directory.\n"));	
            }
			continue;
		}
		
		
		pid_t child_pid = fork();
		if (child_pid < 0){
			perror("ERROR: Fork failed");
            exit(1);
		}
		
		if (child_pid == 0){ //child process
		/* Never returns if the call is successful */
			if( execvp(tokens[0], tokens) < 0 ) {
				write(STDOUT_FILENO, tokens[0], strlen(tokens[0]));
				write(STDOUT_FILENO, ": Unknown command.\n", strlen(": Unknown command.\n"));	
                exit(1);
			}
		}
		else {
			if (!in_background) { //ELSE: loop back to read_command
				waitpid(child_pid, &stat_loc, WUNTRACED);
			}
			
		}
		
	
		
		//free(tokens);
		//free(input_buffer);
		
		
		
		
>>>>>>> master

		// DEBUG: Dump out arguments:
		for (int i = 0; tokens[i] != NULL; i++) {
			write(STDOUT_FILENO, "   Token: ", strlen("   Token: "));
			write(STDOUT_FILENO, tokens[i], strlen(tokens[i]));
			write(STDOUT_FILENO, "\n", strlen("\n"));
		}
		if (in_background) {
			write(STDOUT_FILENO, "Run in background.", strlen("Run in background."));
		}

		/**
		 * Steps For Basic Shell:
		 * 1. Fork a child process
		 * 2. Child process invokes execvp() using results in token array.
		 * 3. If in_background is false, parent waits for
		 *    child to finish. Otherwise, parent loops back to
		 *    read_command() again immediately.
		 */

	}
	return 0;
}


