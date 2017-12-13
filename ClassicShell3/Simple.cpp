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
#include <ncurses.h>
#include <vector>

#include <readline/readline.h>
#include <readline/history.h>

#include "cd.h"
#include "command_handler.h"
#include "initShell.h"

using namespace std;

//This needs to be public vairable
const int TM = 200;
const int MLI = 1000;
const int MCI = 200;
const int TOKENS_MAXS = TM; // number of tokens_passed for a command
const int MAX_LINE_INPUT = MLI; // number of characters from user input
const int MAX_COMMAND_INPUT = MCI;
extern char** environ;
static char* current_pwd;
int start_prompt;

void store_history(char *store)
{
	string str;
	stringstream ss;
	ss << store;
	ss >> str;
	vector<string> all;
	all.push_back(str);
	for(vector<string>::iterator it = all.begin(); it != all.end(); it++)
	{
		cout << *it << endl;
	}
}

void print_histtory(char *list)
{
	string convert;
	stringstream ss;
	ss << list;
	ss >> convert;	

}

int main(int argc, char *argv[], char ** envp)
{
	MyClass cla;
	changeCD name;
	commandhandler handler;
	cla.print();
	
	char input_lines[MAX_LINE_INPUT];
	char * tokens_passed[TOKENS_MAXS];
	int num_passed_tokens;
	char symbol[] = " \n\t";
	
	vector<string> all;
	
	cla.prompt_prompt_init();
	environ = envp;
	
	setenv("shell",getcwd(current_pwd, 1024),1);
	
	int status = 1;
	
	while(status){
		
		// We print the shell prompt if necessary
		if (start_prompt == 0) 
			name.prompt_name();

		//char* store_commands = fgets(input_lines, MAX_LINE_INPUT, stdin);
		fgets(input_lines, MAX_LINE_INPUT, stdin);
	
		if((tokens_passed[0] = strtok(input_lines,symbol)) == NULL) 
			continue;

		num_passed_tokens = 1;
		while((tokens_passed[num_passed_tokens] = strtok(NULL, symbol)) != NULL) 
			num_passed_tokens++;
		
		handler.prompt_handler(tokens_passed);
		
		//cout << store_commands << endl;
	
	}
	
	return 0;
}


