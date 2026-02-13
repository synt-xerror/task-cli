#include <stdio.h>
#include <stdlib.h>
#include "toybox.h"

// IDEAS
// - Organização das tarefas por lista
// - Sincronização via ADB
// - Organização por prioridade
// - Data limite
     
int main()     
{     
	const char* TASK_DIR = get_dir(home(), ".local/share", "task");
	
	printf("[DEBUG]: Tentando imprimir...\n");
	printf("%s", TASK_DIR);
	
	free(TASK_DIR);
	return 0; 
}
