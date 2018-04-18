//#include <date.h>
#include <stdio.h>
#include <myuser.h>
#include <mypost.h>
#include <loading.h>
#include <interface.h>
#include <time.h>

int main(){
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
		int i;
		long * ks;
		MYDATE date;
		clock_t t;
		t = clock();
		TAD_community com = init();
//		com = load(com,"/home/pedro/Desktop/dump/android");
		//com = load(com,"/Users/Ambrosiny/Desktop/dump exemplo/android");

		t = clock()-t;
		double a1 = ((double)t)/CLOCKS_PER_SEC*1000;
		printf("Init->%f\n",a1);

		t = clock();
		//com = load(com,"/home/pedro/Desktop/dump/ubuntu");
		com = load(com,"/Users/Ambrosiny/Desktop/dump exemplo/android");
		t = clock()-t;
		double a2 = ((double)t)/CLOCKS_PER_SEC*1000;
		printf("Load->%fms\n",a2);
		/*
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
		Date di = createDate(1,0,2009);
		Date df = createDate(1,1,2020);
		t = clock();
		teste = total_posts(com,di,df);
		t = clock()-t;
		printf("P:%ld -> R:%ld\n",get_fst_long(teste),get_snd_long(teste));
		double a6 = ((double)t)/CLOCKS_PER_SEC*1000;
		printf("Q3->%fms\n",a6);
		free_date(di);
		free_date(df);
		/*
		t = clock();
		l = contains_word(com, "ubuntu", 100);
		t = clock()-t;
		a3 = ((double)t)/CLOCKS_PER_SEC*1000;

		printf("\n\nQ8v1->%fms\n(IDs, Dates):",a3);
		free_list(l);

		t = clock();
		l = contains_word(com, "java", 100);
		t = clock()-t;
		a3 = ((double)t)/CLOCKS_PER_SEC*1000;
		printf("\n\nQ8v2->%fms\n(IDs, Dates):",a3);
		free_list(l);



		Date dB = createDate(1,7,2017);
		Date dE = createDate(1,11,2017);
		t = clock();
		l = most_used_best_rep(com, 100, dB,dE);
		t = clock()-t;
		a3 = ((double)t)/CLOCKS_PER_SEC*1000;
		printf("\n\nQ11->%fms\n(Numero de ocorrencias):",a3);
		for(i = 0; i < get_listsize(l); i++)
			printf("\t%ld", get_list(l, i));
		printf("\n");
		free_date(dB);
		free_date(dE);
		free_list(l);*/
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
*/							/*
							di = createDate(1,1,2000);
							df = createDate(1,1,2020);
						  	LONG_list resp = questions_with_tag(com,"services",di,df);
							long aux;

							for(int i =0; i < 10;i++){
								aux = get_list(resp,i);
								printf("%ld \n", aux	);
							}*/
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
						Date di = createDate(1,0,2009);
						Date df = createDate(1,1,2020);
						t = clock();
						LONG_pair pat = total_posts(com,di,df);
						t = clock()-t;
						double a6 = ((double)t)/CLOCKS_PER_SEC*1000;
						printf("P=%ld -> R=%ld\n",get_fst_long(pat),get_snd_long(pat));
						printf("Q3->%fms\n",a6);

		t = clock();
		com = clean(com);
		t = clock()-t;
		double a5 = ((double)t)/CLOCKS_PER_SEC*1000;
		printf("Free->%fms\n",a5);
		free(com);

        return 1;
}
