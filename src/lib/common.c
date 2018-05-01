#include <common.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
 * @param	str1	Primeira string.
 * @param	str2	Segunda string.
*/
int not_strcmp(void * str1, void * str2) {
	char * a = (char *) str1;
	char * b = (char *) str2;
	return !strcmp(a, b);
}

/**
 * @brief			Função auxiliar que compara dois longs.
 * @param	l1		Primeiro long.
 * @param	l2		Segundo long.
*/
int cmp_longs(const void * l1, const void * l2){
	if(*(long *)l1 == *(long *)l2 )
		return 0;
	if(*(long *)l1 > *(long *)l2)
		return -1;
	else
		return 1;
}



/**
 * @brief			Função auxiliar que avança para a proxima palavra de uma string.
 * @param	str		String.
 * @param	aux		Endereço para a posicao da proxima palavra.
*/
static void gotoNextWord(char str[],int * aux){
	int i = *aux;
	while(isspace(str[i]) == 0 && ispunct(str[i]) == 0 && str[i] != '\0')
		i++;
	*aux=i;
}

/**
 * @brief			Função que verificar se uma palavra existe numa string.
 * @param	str		String.
 * @param	w		Palavra a verificar.
*/
int wordstr(char str[], char w[]){

	int slen = strlen(str);
	int wlen = strlen(w);

	int i,j,wcount;
	i = j = wcount = 0;

	while(i < slen){
		if(str[i] == w[0]){
			for(j = 0; j < wlen; j++){
				if(str[i+j] != w[j]){

					gotoNextWord(str,&i);
					break;
				}
			}
			if (j == wlen){
				if(isspace(str[i+j]) || ispunct(str[i+j])||str[i+j]=='\0')
					return 1;


			}
		}
		else{
			gotoNextWord(str,&i);
		}
		i++;
	}
	return 0;
}
