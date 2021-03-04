#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <memory.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define IN 0
#define OUT 1

#define SRV_PORT 1234
#define PATH_SIZE 128

#define TAR_LEN 256
#define TAR "sudo tar -x <&"

int s, s_new = 0;
char buf[256];

void siginthandler() {
    	strcpy(buf, "Сервер завершил работу!\n");
        write(OUT, buf, strlen(buf));
	
    	shutdown(s_new, 2);
    	if (s_new)
        	close(s_new);

    	exit(0);
}

int main() {
	struct sockaddr_in sin;
     	struct sockaddr_in from_sin;

     	int i;
     	char num[5];
	unsigned from_len;

	char path[PATH_SIZE];
	char tar[TAR_LEN];
     	
     	signal(SIGINT, &siginthandler);

     	s = socket(AF_INET, SOCK_STREAM, 0);
     	memset((char *)&sin, '\0', sizeof(sin));
     	sin.sin_family = AF_INET;
     	sin.sin_addr.s_addr = INADDR_ANY;
     	sin.sin_port = SRV_PORT;
     	bind(s, (struct sockaddr *)&sin, sizeof(sin));

     	listen(s, 3);

	strcpy(buf, "Сервер начал работу!\n");
        write(OUT, buf, strlen(buf));
    	while (1) {
        	for (i = 0; i < PATH_SIZE; i++) { path[i] = '\0'; }

        	from_len = sizeof(from_sin);
        	s_new = accept(s, (struct sockaddr *)&from_sin, &from_len);
        	read(s_new, path, PATH_SIZE);

        	if (chdir(path) < 0) {
			shutdown(s_new, 2);
        		close(s_new);
        		s_new = 0;

			strcpy(buf, "Ошибка: неверно указана точка назначения!\n");
        		write(OUT, buf, strlen(buf));
			continue;
		}

        	sprintf(num, "%d", s_new);
		strcpy(buf, "Копирование в "); strcat(buf, path); strcat(buf, " из узла-клиента ...\n");
        	write(OUT, buf, strlen(buf));

    		strcpy(tar, TAR);
   		strcat(tar, num);
		system(tar);

    		write(OUT, tar, strlen(tar)); write(OUT, "\n", 1);
	
		strcpy(buf, "Копирование в "); strcat(buf, path); strcat(buf, " заверешено!\n\n");
        	write(OUT, buf, strlen(buf));

        	shutdown(s_new, 2);
        	close(s_new);
        	s_new = 0;
    	}
}
