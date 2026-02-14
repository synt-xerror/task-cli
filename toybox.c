#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

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
