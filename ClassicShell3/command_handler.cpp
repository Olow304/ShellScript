#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>
#include <sstream>
#include <assert.h>
#include <vector>

#include <readline/readline.h>
#include <readline/history.h>

#include "command_handler.h"
#include "cd.h"
#include "exit.h"
#include "help.h"


using namespace std;

static char* current_pwd;

void commandhandler::launchProg(char **arg_hdlr, int run_background){	 
	 int pid_err = -1;
	 int pid  = getpid();
	 
	 if((pid=fork())==-1){
		 cout << "The child process is not able to be created" << endl;
		 return;
	 }
	 
	if(pid==0)
	{
		setenv("child",getcwd(current_pwd, 1024),1);	
		// If we launch non-existing commands we end the process
		if (execvp(arg_hdlr[0],arg_hdlr) == pid_err)
		{
			cout << "Invalid: command not found" << *arg_hdlr[1] << endl;
			kill(getpid(),SIGTERM);
		}	
	}
	 
	if (run_background == 0)
	{
		waitpid(pid,NULL,0);
	}
	else{
	 cout << "Success: process created with PID: " << pid << endl;
	}	 
}


int commandhandler::prompt_handler(char* arg_hdlr[]){
	int index, pos, run_background = 0;
	char *pass_arugs[256];
	
	//create stringstream ss and string variable to hold our data
	string commandHolder;
	stringstream ss;
	ss << *arg_hdlr;
	ss >> commandHolder;
	
	vector<string> all;
	all.push_back(commandHolder);
	
	// We look for the special characters and separate the command itself
	// in a new array for the arguments
	while (arg_hdlr[pos] != NULL){
		if ( (commandHolder == ">") || (commandHolder == "<") || (commandHolder == "&"))
		{
			continue;
		}
		//all.push_back(commandHolder);
		pass_arugs[pos] = arg_hdlr[pos];
		pos++;
	}
	
	if(commandHolder == "help") 
	{
		help();
	}
	
 	else if (commandHolder == "pwd")
 	{
		cout << getcwd(current_pwd, 1000) << endl;
	} 
	
	else if (commandHolder == "clear") 
	{
		system("clear");
	}
		
	else if (commandHolder == "cd") 
	{
		changeCD cd;
		cd.prompt_change_directory(arg_hdlr);
	}

	else if (commandHolder == "exit")
	{
		exit_sh();
	}
	
	else if (commandHolder == "history")
  {
  	string store;
  	stringstream ss;
  	ss << *arg_hdlr;
  	ss >> store;
  	
  	vector<string> all;
  	all.push_back(store);
  	for(vector<string>::iterator it = all.begin(); it != all.end(); it++)
  	{
  		cout << *it << endl;
  	}
  }

	else
	{
		while (arg_hdlr[index] != NULL && run_background == 0)
		{
			if (commandHolder == "&")
			{
				run_background = 1;
				//cout << "Starting background job" << endl;
				
			}
			index++;
		}
		pass_arugs[index] = NULL;
		launchProg(pass_arugs,run_background);
	}
	
	
	return 1;
}

