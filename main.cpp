#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>
#include <iostream>
#include <sstream>

#include "cd.h"
#include "init.h"
extern char** environ;

using namespace std;


const int INPUT_LIMIT = 256; // max number of tokens for a command
const int INPUT_MAX_LIME = 1024; // max number of characters from user input


const int INPUT_CMD_LENGHT = 128;
const int HISTORY_COUNT = 20;
extern char** environSet;
static char* current_pwd;

void prompt_name()
{
	char username[1001] = "";
	gethostname(username, sizeof(username));
	printf("%s@%s %s > ", getenv("LOGNAME"), username, getcwd(current_pwd, 1024));

}

void prompt_init(){
    int C_PID  = getpid();
    // The shell is interactive if STDIN is the terminal 
    int prompt_terminal = STDOUT_FILENO; 
    int prompt_interactive = isatty(prompt_terminal);  

		if (prompt_interactive) 
		{
			while (tcgetpgrp(STDIN_FILENO) != (GBSH_PGID = getpgrp()))
					kill(C_PID , SIGTTOU);             
	   
			// Put ourselves in our own process group
			setpgid(C_PID , C_PID ); // we make the shell process the new process
			GBSH_PGID = getpgrp();
			if (C_PID  != GBSH_PGID) {
					printf("Error");
					exit(EXIT_FAILURE);
			}
			// Grab control of the terminal
			tcsetpgrp(STDIN_FILENO, GBSH_PGID);  
			
			// Save default terminal attributes for shell
			tcgetattr(STDIN_FILENO, &GBSH_TMODES);

     }
}

int prompt_handler(char * arg_hdlr[])
{
	//declare some variables
	int index, j, back = 0;
	int fileDescriptor, standardOut;
	int aux;
	char *pass_arugs[256];
	
	//create stringstream ss and string variable to hold our data
	string commandHolder;
	stringstream ss;
	ss << *arg_hdlr;
	ss >> commandHolder;
	
	while (arg_hdlr[j] != NULL){
		if ( (commandHolder == ">") || (commandHolder == "<") || (commandHolder == "&")){
			break;
		}
		pass_arugs[j] = arg_hdlr[j];
		j++;
	}
	
	if(commandHolder == "help") 
	{
		cout << "help" << endl;
	}
	

}

int main(int argc, char *argv[], char **envp)
{

	int prmpt_loop;
	char line[INPUT_MAX_LIME];
	char * tokens[INPUT_LIMIT];
	int numTokens;
	const char s[4] = "\n\t";
	
	prompt_init();	
	
	environ = envp;
	setenv("shell", getcwd(current_pwd, 1024), 1);
	
	while(TRUE)
	{
		if(prmpt_loop == 0)
			prompt_name();
		
		fgets(line, INPUT_MAX_LIME, stdin);
		
		if((tokens[0] = strtok(line, s)) == NULL) 
			continue;
			
		numTokens = 1;
		while((tokens[numTokens] = strtok(NULL, s)) != NULL) 
			numTokens++;
	
		prompt_handler(tokens);
	}
		
	return 0;
}
