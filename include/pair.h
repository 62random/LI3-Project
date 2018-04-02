#ifndef __PAIR_H__
#define __PAIR_H__
typedef struct str_pair* STR_pair;

STR_pair 	create_pair		(char* fst, char* snd);
void 		set_fst			(STR_pair pair, char* str);
void 		set_snd			(STR_pair pair, char* str);
char * 		get_fst			(STR_pair pair);
char * 		get_snd			(STR_pair pair);
void 		free_pair		(STR_pair pair);

// LONG_pair definitions
typedef struct long_pair* LONG_pair;

LONG_pair create_long_pair(long fst, long snd);
void set_fst_long(LONG_pair pair, long l);
void set_snd_long(LONG_pair pair, long l);
long get_fst_long(LONG_pair pair);
long get_snd_long(LONG_pair pair);
void free_long_pair(LONG_pair pair);

#endif
