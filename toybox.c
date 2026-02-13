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
// DIR_ROOT é o fallback caso a XDG_VAR não exista
// Caso o diretório não estiver na home, use NULL como primeiro argumento
// Se HOME = NULL, a função assume que a pasta que quer está fora da pasta /home/usuário 

// Importante: essa função retorna um char*. Para abrir o diretório retornado, você deve usar
// a função opendir() com o valor retornado de get_dir()
char* get_dir(char* HOME, char* DIR_ROOT, char* DIR_NAME) {
	if (DIR_NAME[0] == '~') {
		perror("get_dir function doesn't expand '~'!");
		return NULL;
	} else if (DIR_NAME[0] == '/') {
		perror("get_dir DIR_NAME (3rd argumment) can't begin with '/'!");
		return NULL;
	}

	char *DIR_FINAL;

	// se não tiver home, assume estar na raíz
	if (HOME) {
		int size = strlen(home()) + 1 + strlen(DIR_ROOT) + 1 + strlen(DIR_NAME);
		DIR_FINAL = malloc(size);
		DIR_FINAL[0] = '\0';

		strcat(DIR_FINAL, HOME);
		strcat(DIR_FINAL, "/");
		strcat(DIR_FINAL, DIR_ROOT);
		strcat(DIR_FINAL, "/");
		strcat(DIR_FINAL, DIR_NAME);
	} else {
		int size = 1 + strlen(DIR_ROOT) + 1 + strlen(DIR_NAME) + 1;
		DIR_FINAL = malloc(size);
		DIR_FINAL[0] = '\0';

		strcat(DIR_FINAL, "/");
		strcat(DIR_FINAL, DIR_ROOT);
		strcat(DIR_FINAL, "/");
		strcat(DIR_FINAL, DIR_NAME);
	}

	    
	if (!DIR_FINAL) {  
		fprintf(stderr, "Return of %s in get_dir is NULL!",
				DIR_FINAL);
		return NULL;
	} else {
		const DIR *dir_exist = opendir(DIR_FINAL);
		if (!dir_exist) {
			const int status = mkdir(DIR_FINAL, 0755);
			if (status != 0) {		
				fprintf(stderr, "'%s' doesn't exist and cannot be created!",
						DIR_FINAL);
				return NULL;
			}
		}

		return DIR_FINAL;
	}
}     
