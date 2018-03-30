#ifndef __PAIR_H__
#define __PAIR_H__
typedef struct str_pair* STR_pair;

STR_pair 	create_pair		(char* fst, char* snd);
void 		set_fst			(STR_pair pair, char* str);
void 		set_snd			(STR_pair pair, char* str);
char * 		get_fst			(STR_pair pair);
char * 		get_snd			(STR_pair pair);
void 		free_pair		(STR_pair pair);
#endif
