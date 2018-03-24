
typedef struct my_post *MYPOST;

struct my_post {
	long 		id;
	long 		parent_id;
	struct date	cdate;
	int 		score;
	long 		ownerid;
	char *		ownername;
	char *		title;
	char **		tags;
	int 		anscount;
	int			commcount;
	int			favcount;
	int			votecount;			//contruir ao dar load
	//lista de votos (so com o id do user)
} * MYPOST;


long getId(MYPOST post){
  return post->id;
}

long getPId(MYPOST post){
  return post->parent_id;
}

struct date getDate(MYPOST post){
  return post->cdate;
}


long getOwnerId(MYPOST post){
  return post->score;
}

char* getOwnerName(MYPOST post){
  return post->ownername;
}

char* getTile(MYPOST post){
  
}
