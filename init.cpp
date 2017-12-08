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

#include "init.h"

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
			setpgid(C_PID , C_PID ); // we make the shell process the new process group leader
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
