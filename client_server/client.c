#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <memory.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

#define IN 0
#define OUT 1

#define SRV_PORT 1234
#define CLNT_PORT 1235 
#define PATH_SIZE 128

#define TAR_LEN 128
#define TAR "sudo tar -c tar.tar "
#define REDIRECT " 1>&"
#define IGNOR " 2>/dev/null "

char buf[256];

int main (int argc, char** argv) {
	struct hostent *hp = NULL;
    	struct sockaddr_in clnt_sin, srv_sin;

    	int s;
    	char path_dst[PATH_SIZE];

    	char tar[TAR_LEN];
    	char host[20];
    	char num[5];

    	if (argc < 3) { 
		strcpy(buf, "Некорректное число аргументов!\n");
		write(OUT, buf, strlen(buf));
		exit(1);
	}

    	s = socket (AF_INET, SOCK_STREAM, 0);
    	memset((char*)&clnt_sin, '\0', sizeof(clnt_sin));
    	clnt_sin.sin_family = AF_INET;
    	clnt_sin.sin_addr.s_addr = INADDR_ANY;
    	clnt_sin.sin_port = CLNT_PORT;
    	bind(s, (struct sockaddr *)&clnt_sin, sizeof(clnt_sin));

    	memcpy(host, argv[2], strlen(argv[2]));
    	*strchr(host, '@') = '\0';
    	memset((char*)&srv_sin, '\0', sizeof(srv_sin));

    	if (!(hp = gethostbyname(host))) {
		strcpy(buf, "Доменное имя "); strcat(buf, host); strcat(buf, " не найдено!\n");
        	write(OUT, buf, strlen(buf));
        	exit(2);
    	}

    	srv_sin.sin_family = AF_INET;
    	memcpy((char*)&srv_sin.sin_addr, hp->h_addr, hp->h_length);
    	srv_sin.sin_port = SRV_PORT;

    	if (connect(s, (struct sockaddr *) &srv_sin, sizeof(srv_sin)) == -1) {
        	strcpy(buf, "Не удалось установить соединение с "); strcat(buf, host); strcat(buf, "!\n");
        	write(OUT, buf, strlen(buf));
        	exit(3);
    	}

	strcpy(path_dst, strstr(argv[2], "/"));
    	write(s, path_dst, strlen(path_dst));

    	if (chdir(argv[1]) < 0) {
		strcpy(buf, "Путь "); strcat(buf, argv[1]); strcat(buf, " не существует!\n");
        	write(OUT, buf, strlen(buf));
        	exit(4);
	}

    	sprintf(num, "%d", s);
    	strcpy(tar, TAR);
    	strcat(tar, argv[1]);
    	strcat(tar, REDIRECT);
    	strcat(tar, num);
    	strcat(tar, IGNOR);
    	system(tar);
	
	write(OUT, tar, strlen(tar)); write(OUT, "\n", 1);

	close(s);

    	exit(0);
}
