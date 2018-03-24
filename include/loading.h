

typedef struct TCD_community {
	//àrvore de USERS, com key ID
	//àrvore de POSTS, com key ID
	//posts ordenados por data?
}







/* USERS */

typedef struct my_user {
	long 	id;
	int		reputation;
	char *	dname;
	char *	about;
	//lista de posts
} * USER;



/* POSTS */

typedef struct my_post {
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
} * POST;
