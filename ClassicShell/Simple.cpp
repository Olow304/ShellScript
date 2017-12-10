#define TRUE 1
#define FALSE !TRUE
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>
#include <sstream>

#include "cd.h"
#include "command_handler.h"

using namespace std;

//This needs to be public vairable
const int TM = 200;
const int MLI = 1000;
const int MCI = 200;
const int TOKENS_MAXS = TM; // max number of tokens_passed for a command
const int MAX_LINE_INPUT = MLI; // max number of characters from user input
const int MAX_COMMAND_INPUT = MCI;
extern char** environ;
static char* current_pwd;
static pid_t gbash_pid;
static pid_t gbash_parent;
static int is_shell_interacvtive;
static struct termios bash_modes;
static char* currentDirectory;
int start_prompt;

class MyClass{
public:
	void print();
	void prompt_prompt_init();
	void launchProg(char **arg_hdlr, int background);
	//int prompt_handler(char * arg_hdlr[]);

private:
	string name;
	// Shell pid, pgid, terminal modes

	pid_t pid;
};




void MyClass::print()
{
	cout << "This is Classific shell" << endl;
}

// CREDIT https://www.gnu.org/software/libc/manual/html_node/Initializing-the-Shell.html
// Inspired by one of the sample code on gnu website "Initializing the shell"
void MyClass::prompt_prompt_init(){
    int C_PID  = getpid();
    // The shell is interactive if STDIN is the terminal 
    int prompt_terminal = STDOUT_FILENO; 
    int prompt_interactive = isatty(prompt_terminal);  

		if (prompt_interactive) 
		{
			while (tcgetpgrp(STDIN_FILENO) != (gbash_parent = getpgrp()))
					kill(C_PID , SIGTTOU);             
	   
			// Put ourselves in our own process group
			setpgid(C_PID , C_PID ); // we make the shell process the new process group leader
			gbash_parent = getpgrp();
			if (C_PID  != gbash_parent) {
					printf("Error");
					exit(EXIT_FAILURE);
			}
			// Grab control of the terminal
			tcsetpgrp(STDIN_FILENO, gbash_parent);  
			
			// Save default terminal attributes for shell
			tcgetattr(STDIN_FILENO, &bash_modes);

     }
}

int main(int argc, char *argv[], char ** envp)
{
	int background = 1;
	MyClass cla;
	changeCD name;
	commandhandler handler;
	cla.print();
	
	char input_lines[MAX_LINE_INPUT];
	char * tokens_passed[TOKENS_MAXS];
	int num_passed_tokens;
	
	cla.prompt_prompt_init();
	environ = envp;
	
	setenv("shell",getcwd(current_pwd, 1024),1);
	
	while(TRUE){
		// We print the shell prompt if necessary
		if (start_prompt == 0) name.prompt_name();

		fgets(input_lines, MAX_LINE_INPUT, stdin);
	
		if((tokens_passed[0] = strtok(input_lines," \n\t")) == NULL) 
			continue;

		num_passed_tokens = 1;
		while((tokens_passed[num_passed_tokens] = strtok(NULL, " \n\t")) != NULL) 
			num_passed_tokens++;
		
		handler.prompt_handler(tokens_passed);
	
	}
	
	return 0;
}














