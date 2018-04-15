//#include <date.h>
#include <stdio.h>
#include <myuser.h>
#include <mypost.h>
#include <loading.h>
#include <interface.h>
#include <time.h>

int inited 	= 0;
int loaded 	= 0;


int main(){
	char string[256];
	char string2[256];
	TAD_community com = NULL;
	clock_t t;
	long long1,long2,long3;
	int int1,int2,int3;
	STR_pair stp;
	LONG_list llis;
	USER user;
	LONG_pair lp;
	Date ini,fi;
	while(1){
		gets(string);

		if(strcmp(string,"exit") == 0){
			if (loaded != 0){
				printf("Falta dar clean(free) a struct \n");
				continue;
			}
			else
				break;
		}
		if(strcmp(string,"init") == 0){
			com = init();
			inited = 1;
			printf("Init done\n\n");
			continue;
		}
		if(strcmp(string,"load") == 0|| strcmp(string,"q0") == 0){
			if(inited != 1){
				printf("Falta dar init\n");
				continue;
			}
			printf("Escrever Path\nExemplo /home/alexrone/a/ubuntu\n");
			gets(string);
			printf("A dar load plz wait bitch\n\n");

			com = load(com,string);
			loaded = 1;
			printf("LOAD done\n\n");

			continue;
		}
		if(strcmp(string,"q1")== 0){
			if(loaded != 1){
				printf("Falta dar load\n");
				continue;
			}
			printf("Escrever id do Post\n");
			gets(string);
			long1 = atol(string);
			t = clock();
			stp = info_from_post(com, long1);
			t = clock()-t;
			double a5 = ((double)t)/CLOCKS_PER_SEC*1000;
			printf("Q1->%fms\n\n\n",a5);
			continue;

		}
		if(strcmp(string,"q2")==0){
			if(loaded != 1){
				printf("Falta dar load\n");
				continue;
			}
			printf("N max\n");
			gets(string);
			int1 = atoi(string);
			t = clock();
			llis = top_most_active(com, int1);
			t = clock()-t;
			double a5 = ((double)t)/CLOCKS_PER_SEC*1000;
			printf("Q2->%fms\n\n\n",a5);
			continue;

		}
		if(strcmp(string,"q3")==0){
			if(loaded != 1){
				printf("Falta dar load\n");
				continue;
			}
			printf("Data inicial do tipo dia-mes-ano\n");
			scanf("%i-%i-%i",&int1,&int2,&int3);
			ini = createDate(int1,int2,int3);
			printf("Data final\n");
			scanf("%i-%i-%i",&int1,&int2,&int3);
			fi = createDate(int1,int2,int3);
			t = clock();
			lp = total_posts(com,ini,fi);
			t = clock()-t;
			double a5 = ((double)t)/CLOCKS_PER_SEC*1000;
			printf("Q3->%fms\n\n\n",a5);
			continue;

		}
		if(strcmp(string,"q4")==0){
			if(loaded != 1){
				printf("Falta dar load\n");
				continue;
			}
			printf("Tag a verificar\n");
			gets(string2);
			printf("Data inicial do tipo dia-mes-ano\n");
			scanf("%i-%i-%i",&int1,&int2,&int3);
			ini = createDate(int1,int2,int3);
			printf("Data final\n");
			scanf("%i-%i-%i",&int1,&int2,&int3);
			fi = createDate(int1,int2,int3);
			t = clock();
			llis = questions_with_tag(com,string2,ini,fi);
			t = clock()-t;
			double a5 = ((double)t)/CLOCKS_PER_SEC*1000;
			printf("Q4->%fms\n\n\n",a5);
			continue;

		}
		if(strcmp(string,"q5")==0){
			if(loaded != 1){
				printf("Falta dar load\n");
				continue;
			}
			printf("ID do user\n");
			gets(string);
			long1 = atol(string);
			t = clock();
			user = get_user_info(com,long1);
			t = clock()-t;
			double a5 = ((double)t)/CLOCKS_PER_SEC*1000;
			printf("Q5->%fms\n\n\n",a5);
			continue;
		}
		if(strcmp(string,"q6")==0){
			if(loaded != 1){
				printf("Falta dar load\n");
				continue;
			}
			printf("N max\n");
			gets(string);
			int1 = atoi(string);

			printf("Data inicial do tipo dia-mes-ano\n");
			scanf("%i-%i-%i",&int1,&int2,&int3);
			ini = createDate(int1,int2,int3);
			printf("Data final\n");
			scanf("%i-%i-%i",&int1,&int2,&int3);
			fi = createDate(int1,int2,int3);
			t = clock();
			llis = most_voted_answers(com,int1,ini,fi);
			t = clock()-t;
			double a5 = ((double)t)/CLOCKS_PER_SEC*1000;
			printf("Q6->%fms\n\n\n",a5);
			continue;
		}
		if(strcmp(string,"q7")==0){
			if(loaded != 1){
				printf("Falta dar load\n");
				continue;
			}
			printf("N MAX\n");
			gets(string);
			int1 = atoi(string);

			printf("Data inicial do tipo dia-mes-ano\n");
			scanf("%i-%i-%i",&int1,&int2,&int3);
			ini = createDate(int1,int2,int3);
			printf("Data final\n");
			scanf("%i-%i-%i",&int1,&int2,&int3);
			fi = createDate(int1,int2,int3);
			t = clock();
			llis = most_answered_questions(com,int1,ini,fi);
			t = clock()-t;
			double a5 = ((double)t)/CLOCKS_PER_SEC*1000;
			printf("Q7->%fms\n\n\n",a5);
			continue;
		}
		if(strcmp(string,"q8")==0){
			if(loaded != 1){
				printf("Falta dar load\n");
				continue;
			}
			printf("N MAX\n");
			gets(string);
			int1 = atoi(string);
			printf("Palavra a verificar\n");
			gets(string);
			int1 = atoi(string);
			t = clock();
			llis = contains_word(com,string,int1);
			t = clock()-t;
			double a5 = ((double)t)/CLOCKS_PER_SEC*1000;
			printf("Q8->%fms\n\n\n",a5);
			continue;
		}
		if(strcmp(string,"q9")==0){
			if(loaded != 1){
				printf("Falta dar load\n");
				continue;
			}
			printf("Escrever id1\n");
			gets(string);
			long1 = atol(string);
			printf("Escrever id2\n");
			gets(string);
			long2 = atol(string);
			printf("N MAX\n");
			gets(string);
			int1 = atoi(string);
			t = clock();
			llis = both_participated(com, long1,long2,int1);
			t = clock()-t;
			double a5 = ((double)t)/CLOCKS_PER_SEC*1000;
			printf("Q9->%fms\n\n\n",a5);
			continue;
		}
		if(strcmp(string,"q10")==0){
			if(loaded != 1){
				printf("Falta dar load\n");
				continue;
			}
			printf("ID DO POST\n");
			gets(string);
			long1 = atol(string);
			t = clock();
			long2 = better_answer(com,long1);
			t = clock()-t;
			double a5 = ((double)t)/CLOCKS_PER_SEC*1000;
			printf("Q10->%fms\n\n\n",a5);
			continue;
		}
		if(strcmp(string,"q11")==0){
			if(loaded != 1){
				printf("Falta dar load\n");
				continue;
			}
			printf("N MAX\n");
			gets(string);
			int1 = atoi(string);
			printf("Data inicial do tipo dia-mes-ano\n");
			scanf("%i-%i-%i",&int1,&int2,&int3);
			ini = createDate(int1,int2,int3);
			printf("Data final\n");
			scanf("%i-%i-%i",&int1,&int2,&int3);
			fi = createDate(int1,int2,int3);

			t = clock();
		//	llis = most_used_best_rep(com,int1,ini,fi);
			t = clock()-t;
			double a5 = ((double)t)/CLOCKS_PER_SEC*1000;
			printf("Q11->%fms\n\n\n",a5);
			continue;
		}
		if(strcmp(string,"clean")==0){
			com = clean(com);
			loaded = 0;
			printf("clean(free) done\n\n");

		}


		printf("NOPE\n");
	}
	free(com);


	/*int i;
	long * ks;
	MYDATE date;
	t = clock();
	TAD_community com = init();
	com = load(com,"/home/alexrone/a/ubuntu");
	LONG_list aux = both_participated(com, 82,186,10);
	com = clean(com);
	free(com);
	return 1;*/
}



		/*
        TREE usertree = createMYUSERS_TREE("/Users/Ambrosiny/Desktop/Universidade/2ano/LI3/dump exemplo/android/Users.xml");
		TREE postTreeId = NULL, postTreeData = NULL;
		createMYPOST_TREES("/Users/Ambrosiny/Desktop/Universidade/2ano/LI3/dump exemplo/android/Posts.xml", &postTreeId, &postTreeData, usertree);
		xmlVotes("/Users/Ambrosiny/Desktop/Universidade/2ano/LI3/dump exemplo/android/Votes.xml", postTreeId);


		printf("Enter ID\n");
		long key = 0;
		//MYUSER use;
		MYPOST post;
		while(scanf("%ld",&key)){
		//while(scanf("%ld",&key) && key != 0){
			//use = search_USER(usertree,key);
			post = search_POSTID(postTreeId, key);
			//if (!use)
			if (!post)
				printf("Não encontrou\n");
			else{
				print_posts_MYPOST(post);
				//printf("ID:%ld\n",getIdMYUSER(use));
				//printf("Rep:%d\n",getREPMYUSER(use));
				//printf("Use:%s\n", getUsername(use));
				//printf("Bio:%s\n",getBiography(use));
				//printf("ID: %ld\n",getIdP(post));

				int n;
				MYDATE date = NULL;
				char * names;
				char ** tags = NULL;

				getPostTypeIdP(post, &n);
				printf("PostTypeId: %d\n", n);

				getOwnerIdP(post, &key);
				printf("OwnerId: %ld\n", key);

				getDateP(post, &date);
				printf("Data: %d-%d-%d\n", get_MYyear(date), get_MYmonth(date), get_MYday(date));
				free_MYdate(date);

				getOwnerNameP(post, &names);
				printf("OwnerName: %s\n", names);
				free(names);

				getTitleP(post, &names);
				printf("Title: %s\n", names);
				free(names);

				getTagsP(post, &tags);
				printf("Tags: ");
				if(tags != NULL)
					for(int i = 0; tags[i] != NULL; i++)
						printf("%s\t", tags[i]);
				printf("\n");
				free_StringArray(tags);

				getAnswersP(post, &n);
				printf("Answers: %d\n", n);

				getCommentsP(post, &n);
				printf("Comments: %d\n", n);

				getFavsP(post, &n);
				printf("FavoriteCount: %d\n", n);

				getVotesP(post, &n);
				printf("VoteCount: %d\n", n);

				getPIdP(post, &key);
				printf("ParentId: %ld\n", key);

				getScoreP(post, &n);
				printf("Score: %d\n\n", n);

			}
		}


		freeTreeUSER(usertree);
		freeTREE_AVL(postTreeId);
		freeTREE_AVL(postTreeData);*/
		///Users/Ambrosiny/Desktop/Universidade/2ano/li3/dump exemplo/android

//		com = load(com,"/Users/Ambrosiny/Desktop/Universidade/2ano/li3/dump exemplo/android");
/*
||||||| merged common ancestors
		com = load(com,"/home/pedro/Desktop/dump/android");
//		com = load(com,"/Users/Ambrosiny/Desktop/Universidade/2ano/li3/dump exemplo/android");

=======
//		com = load(com,"/home/pedro/Desktop/dump/android");
		//com = load(com,"/Users/Ambrosiny/Desktop/dump exemplo/android");

>>>>>>> c78a478e8227f92c2a19a8ae4c243c240cbd3082
		t = clock()-t;
		double a1 = ((double)t)/CLOCKS_PER_SEC*1000;
		printf("Init->%f\n",a1);

		t = clock();
		com = load(com,"/home/pedro/Desktop/dump/ubuntu");
		//com = load(com,"/Users/Ambrosiny/Desktop/dump exemplo/ubuntu");
		t = clock()-t;
		double a2 = ((double)t)/CLOCKS_PER_SEC*1000;
		printf("Load->%fms\n",a2);

		t = clock();
		LONG_list l = top_most_active(com,100);
		t = clock()-t;
		double a3 = ((double)t)/CLOCKS_PER_SEC*1000;
		printf("Q2->%fms\n",a3);
		free_list(l);

		t = clock();
		l = top_most_active(com,80);
		t = clock()-t;
		double a4 = ((double)t)/CLOCKS_PER_SEC*1000;
		printf("Q2->%fms\n",a4);
		free_list(l);

		LONG_pair teste;
		Date di = createDate(1,1,2010);
		Date df = createDate(31,6,2019);
		t = clock();
		teste = total_posts(com,di,df);
		t = clock()-t;
		double a6 = ((double)t)/CLOCKS_PER_SEC*1000;
		printf("Q3->%fms\n",a6);

		t = clock();
		l = contains_word(com, "ubuntu", 1000);
		t = clock()-t;
		a3 = ((double)t)/CLOCKS_PER_SEC*1000;

		printf("\n\nQ8v1->%fms\n(IDs, Dates):",a3);						//
		for(i = 0; i < get_listsize(l); i++){							//
			printf("\t(%ld, ", get_list(l, i));							//
			getDateP(search_POSTID((TREE) bla(com),get_list(l,i)), &date);		//
			printMyDate(date);											//  TESTES
			printf(")");												//
		}																//
		printf("\n%d resultados\n", i);									//
		free_list(l);

		t = clock();
		l = contains_word(com, "cona", 100);
		t = clock()-t;
		a3 = ((double)t)/CLOCKS_PER_SEC*1000;
		printf("\n\nQ8v2->%fms\n(IDs, Dates):",a3);
		for(i = 0; i < get_listsize(l); i++){							//
			printf("\t(%ld, ", get_list(l, i));							//
			getDateP(search_POSTID((TREE) bla(com),get_list(l,i)), &date);		//
			printMyDate(date);											//  TESTES
			printf(")");												//
		}																//
		printf("\n%d resultados\n", i);									//
		free_list(l);



					//		LONG_pair teste;
					//		Date di = createDate(1,1,2010);
					//		Date df = createDate(31,6,2010);
					//		teste = total_posts(com,di,df);
					//		printf("Perguntas %ld ||||  Respotas  %ld\n\n",get_fst_long(teste),get_snd_long(teste));


					//		STR_pair teste2;
					//		teste2 = info_from_post(com,51);
					//		printf("Titulo %s  ||||| User  %s\n\n",get_fst_str(teste2),get_snd_str(teste2));

						//	USER teste3;
						//  teste3 = get_user_info(com,100);
					//		printf("BIO = %s",get_bio(teste3) );
					//		long * auxl = get_10_latest_posts(teste3);
					//		for(int i = 0; i<10;i++)
					//			printf("%ld --",auxl[i] );
					//		printf("\n");
					//		free_user(teste3);

//							long teste4 = better_answer(com,2);
//							printf("\n%ld\n",teste4 );
*/
/*							LONG_list l;
							l = top_most_active(com,1000);
							for(i=0;i < 1000; i++)
								printf("%ld\n",get_list(l,i));
							free_list(l);
							printf("lalalalal\n");
							l = top_most_active(com,2);
							for(i=0;i < 2; i++)
								printf("%ld\n",get_list(l,i));
							free_list(l);
							printf("lalalalal\n");
							l = top_most_active(com,3);
							for(i=0;i < 3; i++)
								printf("%ld\n",get_list(l,i));
							free_list(l);
*/
		//					Date di = createDate(1,1,2000);
			//				Date df = createDate(1,1,2020);
				//		  	LONG_list resp = questions_with_tag(com,"randr",di,df);
	/*	Date di = createDate(1,1,2010);
		Date df = createDate(31,6,2010);
		LONG_list l;
		l = most_answered_questions(com,10, di,df);
	*/

						//}
			/*
		Date di = createDate(1,1,2010);
		Date df = createDate(31,6,2010);
		LONG_list l;
		l = most_answered_questions(com,10, di,df);
						}*/
						/*
						Date di = createDate(1,1,2010);
						Date df = createDate(31,6,2019);
						LONG_list l;
						l = most_answered_questions(com,30, di,df);
						for(i = 0; i < 30; i++)
							printf("Id:%ld\n",get_list(l,i));
						free_date(di);
						free_date(df);
						free_list(l);*/
			//			printf("%ld\n",get_list(aux,0) );
		//			t = clock();
//					t = clock()-t;
	//				double a5 = ((double)t)/CLOCKS_PER_SEC*1000;
		//							printf("Q8->%fms\n\n\n",a5);
