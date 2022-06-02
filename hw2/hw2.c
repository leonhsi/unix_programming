#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void usage(){
	printf("usage: ./logger [-o file] [-p sopath] [--] cmd [cmd args ...]\n");
	printf("    -p: set the path to logger.so, default = ./logger.so\n");
	printf("    -o: print output to file, print to \"stderr\" if no file specified\n");
	printf("    --: separate the arguments for logger and for the command\n");
}

int main(int argc, char *argv[]){

	if(argc == 1){
		printf("no command given.\n");
		return 0;
	}

	char *ld_preload_path = "./logger.so";
	char *output_file = "stderr";
	
	int idx;
	for(idx=1; idx<argc; idx++){
		if(strcmp(argv[idx], "--") == 0){
			idx++;
			break;
		}
		else if(strcmp(argv[idx], "-p") == 0){
			ld_preload_path = argv[++idx];
		}
		else if(strcmp(argv[idx], "-o") == 0){
			output_file = argv[++idx];
		}
		else if(argv[idx][0] == '-'){
			printf("%s: invalid option -- '%c'\n", argv[0], argv[idx][1]);
			usage();
			return 0;
		}
		else{
			break;
		}
	}

	//set output file
	setenv("OUTPUT_FILE", output_file, 1);
	char output_file_env[strlen(output_file) + sizeof("OUTPUT_FILE=")];
	sprintf(output_file_env, "OUTPUT_FILE=%s", output_file);
	
	//exec args
	char *exec_args[argc-idx+1];
	for(int i=idx; i<argc; i++){
		exec_args[i-idx] = argv[i];
	}
	exec_args[argc-idx] = '\0';

	//exec envs
	char *path = getenv("PATH");
	char pathenv[strlen(path) + sizeof("PATH=")];
	sprintf(pathenv, "PATH=%s", path);

	char ld_preload_env[strlen(ld_preload_path) + sizeof("LD_PRELOAD=")];
	sprintf(ld_preload_env, "LD_PRELOAD=%s", ld_preload_path);

	char *envp[] = {pathenv, ld_preload_env, output_file_env, NULL};

	execvpe(exec_args[0], exec_args, envp);

	return 0;
}
