#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "settings.hpp"

class t_exec {
public:
	void wget(t_string dir, t_string name)
	{
		t_string cmd = "/usr/bin/wget";
		dir += "/" + name;
		t_string html = website + name;
		char *argv[] = {(char*)cmd.c_str(),"--no-check-certificate","-O", 
						(char*)dir.c_str(), (char*)html.c_str(), NULL};
		int pid;
		int stat_loc;
		pid = fork();
		switch (pid) {
			case -1:
				perror("fork");
				exit(1);
			case 0:
				execve(cmd.c_str(), argv, 0);
				exit(0);
			default:
				wait(&stat_loc);
		}
	}
};
