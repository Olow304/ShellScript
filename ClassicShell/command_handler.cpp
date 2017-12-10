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

#include "command_handler.h"
#include "cd.h"
using namespace std;

static char* current_pwd;

void commandhandler::launchProg(char **arg_hdlr, int run_background){	 
	 int pid_err = -1;
	 int pid  = getpid();
	 
	 if((pid=fork())==-1){
		 cout << "The child process is not able to be created" << endl;
		 return;
	 }
	 
	if(pid==0){
		
		setenv("child",getcwd(current_pwd, 1024),1);	
		// If we launch non-existing commands we end the process
		if (execvp(arg_hdlr[0],arg_hdlr) == pid_err){
			cout << "Invalid: command not found" << endl;
			kill(getpid(),SIGTERM);
		}
	 }
	 
	 if (run_background == 0){
		 waitpid(pid,NULL,0);
	 }
	 else{
	 	cout << "Success: process created with PID: " << pid << endl;
	 }	 
}

int commandhandler::prompt_handler(char* arg_hdlr[]){
	int i, j, run_background = 0;
	int fileDescriptor, standardOut;
	int aux;
	char *pass_arugs[256];
	
	//create stringstream ss and string variable to hold our data
	string commandHolder;
	stringstream ss;
	ss << *arg_hdlr;
	ss >> commandHolder;
	
	// We look for the special characters and separate the command itself
	// in a new array for the arguments
	while (arg_hdlr[j] != NULL){
		if ( (commandHolder == ">") || (commandHolder == "<") || (commandHolder == "&")){
			break;
		}
		pass_arugs[j] = arg_hdlr[j];
		j++;
	}
	
	if(commandHolder == "help") 
	{
		cout << "hellow" << endl;
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
		
	//This is extra credit
	else if (commandHolder == "echo")
	{
    char *echoChar[1001];
    stringstream echoHolder;
    string echoName;
    echoHolder << *echoChar;
    echoHolder >> echoName;
    cout << commandHolder << endl;
	}

	else{
		while (arg_hdlr[i] != NULL && run_background == 0){
			if (commandHolder == "&")
				run_background = 1;
			i++;
		}
		pass_arugs[i] = NULL;
		launchProg(pass_arugs,run_background);
	}
	
	return 1;
}

