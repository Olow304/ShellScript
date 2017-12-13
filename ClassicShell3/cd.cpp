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

#define KGRN "\x1B[34m"

#include "cd.h"
using namespace std;

static char* current_pwd;

int changeCD::prompt_change_directory(char* arg_hdlr[])
{
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

void changeCD::prompt_name(){
	char username[1001] = "";
	gethostname(username, sizeof(username));
	//printf(KGRN);
	cout << getenv("LOGNAME") << "@" << username << " ~ [" << getcwd(current_pwd, 1000) << "]~$ ";
	//cout << "> ";
}


