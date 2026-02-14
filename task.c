#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toybox.h"

// IDEAS
// - Organização das tarefas por lista
// - Sincronização via ADB
// - Organização por prioridade
// - Data limite

// --- Global values - Don't use it, them is just for easy edits ---

// directories (begin with nothing)
char* DATA_DIR = ".local/share/task-cli";
char* CONFIG_DIR = ".config/task-cli";

// files
char* TASK_FILE = "task.txt";


int main()     
{     
	char* DEF_DATA_DIR = get_dir(home(), DATA_DIR);
	char* DEF_CONFIG_DIR = get_dir(home(), CONFIG_DIR);
	
	char* DEF_TASK_FILE = get_file(DEF_DATA_DIR, TASK_FILE);

	printf("DEF_DATA_DIR: %s\n", DEF_DATA_DIR);
	printf("DEF_CONFIG_DIR: %s\n", DEF_CONFIG_DIR);
	printf("DEF_TASK_FILE: %s\n", DEF_TASK_FILE);
	
	free(DEF_DATA_DIR);
	free(DEF_CONFIG_DIR);
	free(DEF_TASK_FILE);
	return 0; 
}
