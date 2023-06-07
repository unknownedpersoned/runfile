#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define _RUN_FILENAME 	"runfile"
#define _RUN_MSGBYE		"\e[1;93mrun\e[0m: \e[1;91mclosed with error\e[0m\n"
#define _RUN_MSGNEXIST 	"\e[1;93mrun\e[0m: \e[1;91mrunfile doesn't exist\e[0m\n"
#define _RUN_MSGSHERROR "\e[1;93mrun\e[0m: \e[1;91mshell failed to open (runfile is empty?)\e[0m\n"
#define _RUN_MSGRUNNING "\e[1;93mrunning\e[0m+\n"
#define _RUN_MSGWALKING "\e[1;92mwalking\e[0m line \e[1;92m%d\e[0m+\n"
#define _RUN_MSGDONE	"\n\e[1;93mrunning done\e[0m-"

int main(int argc, char *argv[]) {
	printf(_RUN_MSGRUNNING);
	FILE *p = NULL, *f;
	int c, s, l = 1, d = 0, v = argc>1?0==strcmp(argv[1], "-")?1:0:0;
	char *b;
	f = fopen(_RUN_FILENAME, "r");
	if (f == NULL) {
		printf("%s%s", _RUN_MSGNEXIST, _RUN_MSGBYE);
		return 1;
	}
	while (1) {
		s = 0;
		b = malloc(1);
		while ((c = getc(f)) != EOF) {
			if (c == '\n') break;
			b = (char *)realloc(b, sizeof(char)*++s);
			b[s-1] = (char)c;
			d++;
		}
		if (s < 2 || l > d || (p = popen(b, "r")) == NULL) {
			free(b);
			fclose(f);
			printf("%s%s", p==NULL?_RUN_MSGSHERROR:_RUN_MSGDONE, p==NULL?_RUN_MSGBYE:"");
			return 0;
		}
		printf(_RUN_MSGWALKING, l);
		if (v)
			while(fgetc(p)!=EOF)
 		   		;
		else
			while((c=fgetc(p))!=EOF)
 	 			putchar(c);  
 	 	c = 0;
    	pclose(p);
    	free(b);
		l++;
    }
}
