//#include <date.h>
#include <stdio.h>
#include <myuser.h>

int main(){

        GTree * tree = createMYUSERS_TREE("/Users/Ambrosiny/Desktop/Universidade/2ano/LI3/dump exemplo/android/Users.xml");
		/*
		long key = 0;
		MYUSER use;

		while(scanf("%ld",&key)){
			use = search_USER(tree,key);
			if (!use)
				printf("Não encontrou\n");
			else{
				printf("ID:%ld\n",getIdMYUSER(use));
				printf("Rep:%d\n",getREPMYUSER(use));
				printf("Use:%s\n", getUsername(use));
				printf("Bio:%s\n",getBiography(use));
			}
		}

		freeTreeUSER(tree);*/



        return 1;
}
