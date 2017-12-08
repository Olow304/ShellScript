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

using namespace std;

int prompt_change_directory(char* arg_hdlr[]){
	if (arg_hdlr[1] == NULL) {
		chdir(getenv("HOME")); 
		return 1;
	}
	else{ 
		if (chdir(arg_hdlr[1]) == -1) {
			cout << "can't relocated directory" << endl;
      return -1;
		}
	}
	return 0;
}
