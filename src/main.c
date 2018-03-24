//#include <date.h>
#include <stdio.h>

static int fp = 0;

int stringcompare(char*a1 ,char* a2){
  for (int i = 0; a1[i] != '\n' || a2[i] != '\0';i++)
    if (a1[i] != a2[i])
      return 0;

  return 1;
}


void menu(char *args){
  char *buffer;

  if (stringcompare(args,"1")){
    printf("ID do post:\n" );
    readln(buffer,100);
    //printf("%d\n",(atoi(args)) );
    return;
  }

  if (stringcompare(args,"2")){
    printf("Numero de Utilizadores:\n" );
    readln(buffer,100);
    printf("%d\n",(atoi(buffer)) );
    return;
  }
  if (stringcompare(args,"3")){
    printf("Data Inicial:\n" );
    readln(buffer,100);
    // converte Data
    printf("Data Inicial:\n" );
    readln(buffer,100);
    return;
  }
    //printf("%d\n",(atoi(buffer)) );

  if (stringcompare(args,"4")){
    printf("Data Inicial:\n" );
    readln(buffer,100);
    // converte Data
    printf("Data Inicial:\n" );
    readln(buffer,100);
    printf("Tag Pretendida procurar\n" );
    return;
  }
  if (stringcompare(args,"5")){
    printf("ID do utilizador:\n" );
    readln(buffer,100);
    return;
  }
  if (stringcompare(args,"6")){
    printf("Data Inicial:\n" );
    readln(buffer,100);
    // converte Data
    printf("Data Inicial:\n" );
    readln(buffer,100);
    printf("N\n" );
    readln(buffer,100);
    return;
  }
  if (stringcompare(args,"7")){
    printf("Data Inicial:\n" );
    readln(buffer,100);
    // converte Data
    printf("Data Inicial:\n" );
    readln(buffer,100);
    printf("N\n" );
    readln(buffer,100);
    return;
  }
  if (stringcompare(args,"8")){
    printf("Palavra:\n" );
    readln(buffer,100);
    printf("N\n" );
    readln(buffer,100);
    return;
  }
  if (stringcompare(args,"9")){
    printf("ID gajo 1:\n" );
    readln(buffer,100);
    printf("ID gajo 2:\n" );
    readln(buffer,100);
    return;
  }
  if (stringcompare(args,"10")){
    printf("ID pergunta:\n" );
    readln(buffer,100);
    return;
  }

  if (stringcompare(args,"11")){
    printf("Data Inicial:\n" );
    readln(buffer,100);
    // converte Data
    printf("Data Final:\n" );
    readln(buffer,100);
    // converte Data
    printf("N\n" );
    readln(buffer,100);
    printf("%d\n",(atoi(buffer)) );
    return;
  }

  printf("erro\n" );
  return;
}

int readln(char *buff, int buffsz){
	char	*bp = buff, c;
	int	n;

	while(bp - buff < buffsz &&
	      (n = read(fp, bp, 1)) > 0) {
		if (*bp++ == '\n')
			return (bp - buff);
	}

	if (n < 0)
		return -1;

	if (bp - buff == buffsz)
		while (read(fp, &c, 1) > 0 && c != '\n');

	return (bp - buff);
}




int main(){
  char buffer[100];
  int aux;
    while (readln(buffer,100)){
      if (stringcompare(buffer,"exit")){
          return(0);
        }
      else{
        menu(buffer);
      }
    }


}
