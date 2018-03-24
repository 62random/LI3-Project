#include <libxml/parser.h>
#include <libxml/xmlwriter.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include <glib.h>
#include <common.h>xs

//gcc teste.c `xml2-config --cflags --libs` `pkg-config --cflags --libs glib-2.0` -o teste

typedef struct myuser * MYUSER;

struct myuser{
    long id;
    int rp;
    char * username;
    char * bio;
};

static void setId(MYUSER use, long id){
    use->id = id;
}

static void setRp(MYUSER use, int rp){
    use->rp = rp;
}
static void setBio(MYUSER use, char * bio){
    use->bio = mystrdup(bio);
}

static void setUsername(MYUSER use, char * nome){
    use->username = mystrdup(nome);
}

MYUSER createMYUSER(){
    MYUSER conta = malloc(sizeof(struct myuser));
    return conta;
}

void freeMYUSER(MYUSER conta){
    if (!conta){
        free(conta->bio);
        free(conta->username);
        free(conta);
    }
}

int compare_user(long * key1, long * key2){
    long id1,id2;
    int result;

    id1 = *key1;
    id2 = *key2;

    if (id1 == id2)
        result = 0;
    result = id1 > id2 ? 1 : -1 ;

    return result;
}

void freeKey(long * a){
    if (a)
        free(a);
}

void createTREE(){

    xmlDocPtr doc;
	xmlNodePtr ptr;
	struct _xmlAttr * cur;
	xmlNodePtr aux;

    doc = xmlParseFile("Users.xml");

    if( !doc) {
		fprintf(stderr, "Document not parsed successfully\n");
		exit(-1);
	}

	ptr = xmlDocGetRootElement(doc);

	if (!ptr) {
		fprintf(stderr, "empty document\n");
		xmlFreeDoc(doc);
		exit(-1);
	}

    /*
    long id;
    int rep;*/

    aux = ptr->children->next;
    xmlChar *key;
	while (aux != NULL){
        //MYUSER use = createMYUSER();
		cur = aux->properties;
		 	while (cur != NULL) {
				key = xmlNodeListGetString(doc,cur->children,1);
                /*
			    if (strcmp(cur->name,"Id")==0){
                    id = atoi(key);
                    setId(use,id);
                }
                if (strcmp(cur->name,"Reputation")==0){
                    rep = atoi(key);
                    setRp(use,rep);
                }
                if (strcmp(cur->name,"DisplayName")==0){
                    setUsername(use,key);
                }
                if (strcmp(cur->name,"AboutMe")==0){
                    setRp(use,key);
                }*/

				cur = cur->next;
			}
		aux = NULL;
	}



}




int main(){
    return 0;
}
