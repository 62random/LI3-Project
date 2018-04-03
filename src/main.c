//#include <date.h>
#include <stdio.h>
#include <myuser.h>
#include <mypost.h>
#include <loading.h>

int main(){

        TREE usertree = createMYUSERS_TREE("/Users/Ambrosiny/Desktop/Universidade/2ano/LI3/dump exemplo/android/Users.xml");
		TREE postTreeId = NULL, postTreeData = NULL;
		createMYPOST_TREES("/Users/Ambrosiny/Desktop/Universidade/2ano/LI3/dump exemplo/android/Posts.xml", &postTreeId, &postTreeData, usertree);
		xmlVotes("/Users/Ambrosiny/Desktop/Universidade/2ano/LI3/dump exemplo/android/Votes.xml", postTreeId);
                /*

		printf("Enter ID\n");
		long key = 0;
		MYUSER use;
		//MYPOST post;
		while(scanf("%ld",&key)){
		//while(scanf("%ld",&key) && key != 0){
			use = search_USER(usertree,key);
			//post = search_POSTID(postTreeId, key);
			if (!use)
			//if (!post)
				printf("Não encontrou\n");
			else{

				printf("ID:%ld\n",getIdMYUSER(use));
				printf("Rep:%d\n",getREPMYUSER(use));
				printf("Use:%s\n", getUsername(use));
				printf("Bio:%s\n",getBiography(use));
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
				*/
			//}
	//	}


		freeTreeUSER(usertree);
		freeTREE_AVL(postTreeId);
		freeTREE_AVL(postTreeData);



        return 1;
}
