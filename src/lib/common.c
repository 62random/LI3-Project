#include <common.h>
#include <string.h>
#include <stdlib.h>

// definido par nao dar warnings ao usar a funcao da GNU
char * mystrdup (const char *s) {
    if(s == NULL) return NULL;
    char *d = malloc (strlen (s) + 1);
    if (d == NULL) return NULL;
    strcpy (d,s);
    return d;
}

/**
 * @brief			Função auxiliar que retorna a negação da função de biblioteca strcmp.
 * @param			Primeira string.
 * @param			Segunda string.
*/
int not_strcmp(void * str1, void * str2) {
	char * a = (char *) str1;
	char * b = (char *) str2;
	return !strcmp(a, b);
}

/**
 * @brief			Função auxiliar que compara dois longs.
 * @param			Primeiro long.
 * @param			Segundo long.
*/
int cmp_longs(const void * l1, const void * l2){
	if(*(long *)l1 == *(long *)l2 )
		return 0;
	if(*(long *)l1 > *(long *)l2)
		return -1;
	else
		return 1;
}
