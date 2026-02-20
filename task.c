#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

// IDEAS
// - Organização das tarefas por lista
// - Sincronização via ADB
// - Organização por prioridade
// - Data limite

// --- Global values --- 

// directories (begin with nothing)
char* DATA_DIR = ".local/share/task-cli";
char* CONFIG_DIR = ".config/task-cli";

// files
char* TASK_FILE = "task.txt";

char* home()
{
	struct passwd *u;
	u = getpwuid(getuid());

	if (!u) {
		perror("invalid return of getpwuid() function.\n");
		return NULL;
	}
	
	return u->pw_dir;
}

// DIR_NAME deve ser o nome do diretório, não o caminho (ex: task)
// Se HOME = NULL, a função assume que a pasta que quer está fora da pasta /home/usuário 

// Importante: essa função retorna um char*. Para abrir o diretório retornado, você deve usar
// a função opendir() com o valor retornado de get_dir()
char* get_dir(const char* HOME, const char* DIR_NAME) {
	if (DIR_NAME[0] == '~') {
		perror("get_dir doesn't expand '~'");
		return NULL;
	}
	if (DIR_NAME[0] == '/') {
		perror("DIR_NAME can't begin with '/'");
		return NULL;
	}

	const char *prefix = HOME ? HOME : "";

	int size = strlen(prefix) + 1 + strlen(DIR_NAME) + 1;
	char *DIR_FINAL = malloc(size);
	if (!DIR_FINAL) {
		perror("malloc failed");
		return NULL;
	}

	sprintf(DIR_FINAL, "%s/%s", prefix, DIR_NAME);

	DIR *dir = opendir(DIR_FINAL);
	if (!dir) {
		if (mkdir(DIR_FINAL, 0755) != 0) {
			fprintf(stderr, "'%s' cannot be created\n", DIR_FINAL);
			free(DIR_FINAL);
			return NULL;
		}
	} else {
		closedir(dir);
	}

	return DIR_FINAL;
}

char* get_file(char* ROOT, char* FILE_NAME) {
	char* FINAL_FILE;
	
	FINAL_FILE = malloc(strlen(ROOT) + strlen(FILE_NAME) + 1);
	sprintf(FINAL_FILE, "%s/%s", ROOT, FILE_NAME);

	return FINAL_FILE;
}

int main(int argc, char* argv[])     
{     
	if (argc < 2) {
		printf("Commands:\n\tadd <task>: add a new task.\n\tread: read all the tasks.\n\tdone <index>: mark a task as done.\n");
        	return 1;
    	}

	char* DEF_DATA_DIR = get_dir(home(), DATA_DIR);
	char* DEF_CONFIG_DIR = get_dir(home(), CONFIG_DIR);
	
	char* DEF_TASK_FILE = get_file(DEF_DATA_DIR, TASK_FILE);
	
	FILE *task_f;

	if (strcmp(argv[1], "add") == 0) {
	
		task_f = fopen(DEF_TASK_FILE, "a+");
		if (!task_f) {
			printf("error.");
			return 1;
		}
		
		rewind(task_f);
		int lines = 0;
		char buffer[256];
		while (fgets(buffer, sizeof(buffer), task_f)) {
		    lines++;
		}

		char* new_task = argv[2];
		
		if (lines == 0) {
			fprintf(task_f, " [ ] %s", new_task);
		} else {
			fprintf(task_f, "\n [ ] %s", new_task);
		}

		fclose(task_f);
	
	} else if (strcmp(argv[1], "read") == 0) {

		task_f = fopen(DEF_TASK_FILE, "r");
		if (!task_f) {
			printf("error.");
			return 1;
		}
	
		int lines = 0;
		char buffer[256];
		while (fgets(buffer, sizeof(buffer), task_f)) {
			printf("%d. %s", lines, buffer);
			lines++;
		}
		rewind(task_f);
	
		printf("\n");
		fclose(task_f);

	} else if (strcmp(argv[1], "done") == 0) {
		
		task_f = fopen(DEF_TASK_FILE, "r");
		if (!task_f) {
			printf("error."); // im too lazy, ill do a better error message later.
			return 1;
		}

		char *endptr;
		long index = strtol(argv[2], &endptr, 10); // 10 = decimal base 
		
		if (*endptr != '\0') {
		    printf("Error: '%s' is not a valid number \n", argv[2]);
		} 
		
		int lines = 0;
		char buffer[256];
		while (fgets(buffer, sizeof(buffer), task_f)) {
		    lines++;
		}
		rewind(task_f);

		char **array = malloc(lines * sizeof(char*));
		int n = 0;

		while (fgets(buffer, sizeof(buffer), task_f)) {
		    array[n] = strdup(buffer);
		    n++;
		}
		fclose(task_f);

		if (index < 0 || index >= n) {
			printf("Error: task %ld does not exist", index);
			return 1;
		}

		task_f = fopen(DEF_TASK_FILE, "w");
		for (int i = 0; i < n; i++) {
		    	if (i != index) fputs(array[i], task_f);
			free(array[i]);
		}
		fclose(task_f);
	}

	free(DEF_DATA_DIR);
	free(DEF_CONFIG_DIR);
	free(DEF_TASK_FILE);
	return 0; 
}
