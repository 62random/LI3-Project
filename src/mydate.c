#include "mydate.h"
#include <stdio.h>

struct mydate {
  int day;
  int month;
  int year;
};

/**
 * @brief			Função inicializa a estrutura de data.
 * @param			Variável para o dia.
 * @param			Variável para o mês.
 * @param			Variável para o ano.
*/

MYDATE createMYDate(int day, int month, int year) {
    MYDATE d = malloc(sizeof(struct mydate));
    d->day = day;
    d->month = month;
    d->year = year;
    return d;
}

/**
 * @brief			Função devolve a informação para o dia da data.
 * @param			Apontador para a data.
*/

int get_MYday(MYDATE d) {
    return d->day;
}


/**
 * @brief			Função devolve a informação para o mês da data.
 * @param			Apontador para a data.
*/

int get_MYmonth(MYDATE d) {
    return d->month; //change to enum? (Acho que sim. Desta forma já garantimos a limitação necessária)
}


/**
 * @brief			Função devolve a informação para o ano da data.
 * @param			Apontador para a data.
*/

int get_MYyear(MYDATE d) {
    return d->year;
}


/**
 * @brief			Função liberta a memória da data.
 * @param			Apontador para a data.
*/

void free_MYdate(MYDATE d) {
	if(d != NULL)
    	free(d);
}

/**
 * @brief			Função calcula o tamanho de uma data.
*/

int MYdate_size() {
	return sizeof(struct mydate);
}

/**
 * @brief			Função compara duas datas para árvores.
 * @param			Apontador para a data 1.
 * @param			Apontador para a data 2.
*/

int compare_MYDATE_AVL(void * data1, void * data2){

    MYDATE a = (MYDATE) data1;
    MYDATE b = (MYDATE) data2;

    if (a->year == b->year && a->month == b->month && a->day==b->day)
        return 0;
    if (a->year == b->year && a->month == b->month && a->day < b->day)
        return 1;
    if (a->year == b->year && a->month == b->month && a->day > b->day)
        return -1;
    if (a->year == b->year && a->month > b->month)
        return -1;
    if (a->year == b->year && a->month < b->month)
        return 1;
    if (a->year > b->year)
        return -1;

    return 1;

}

/**
 * @brief			Função compara duas datas para listas.
 * @param			Apontador para a data 1.
 * @param			Apontador para a data 2.
*/

int compare_MYDATE_LIST(void * data1, void * data2){

	MYDATE a = (MYDATE) data1;
	MYDATE b = (MYDATE) data2;

	if (a->year == b->year && a->month == b->month && a->day==b->day)
		return 0;
	if (a->year == b->year && a->month == b->month && a->day < b->day)
		return 0;
	if (a->year == b->year && a->month == b->month && a->day > b->day)
		return 1;
	if (a->year == b->year && a->month > b->month)
		return 1;
	if (a->year == b->year && a->month < b->month)
		return 0;
	if (a->year > b->year)
		return 1;

	return 0;

}

/**
 * @brief			Função converte um MYDATE para Date.
 * @param			Apontador para a data.
*/

Date MYDATEtoDate(MYDATE a){
	Date aux;
	aux = createDate(a->day,a->month,a->year);
	return aux;
}

/**
 * @brief			Função converte um Date para MYDATE.
 * @param			Apontador para a data.
*/

MYDATE DatetoMYDATE(Date a){
	MYDATE aux;
	int dia,mes,ano;
	dia = get_day(a);
	mes = get_month(a);
	ano = get_year(a);

	aux = createMYDate(dia,mes,ano);

	return aux;
}

/**
 * @brief			Imprimir uma data.
 * @param			Apontador para a data.
*/

void printMyDate(MYDATE d){
	printf("(%d-%d-%d)", get_MYday(d), get_MYmonth(d), get_MYyear(d));
}
