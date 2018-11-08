#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{
    if (argc > 2 || argc == 1)
    {
        printf("Error: Missing port number or too many arugments.\n");
        return -1;
    }
    else
    {
        FILE *fp;
        struct sockaddr_in server;
        int ssocket;
        int SocketAccept;
        int addr = sizeof(server);
        int port;
        int on;
        char file[18167];
        char readlinechar[255];
        fp = fopen("FAQ.html", "r");
        file[0] = '\0';
        while (fgets(readlinechar, 255, fp) != NULL)
        {
            strcat(file, readlinechar);
        }

        ssocket = socket(AF_INET, SOCK_STREAM, 0);
        if (ssocket < 0)
        {
            printf("ERROR opening socket\n");
            return -1;
        }
        else
        {
            port = atoi(argv[1]);
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = INADDR_ANY;
            server.sin_port = htons(port);
            /**
         * Now that the socket is made, there needs to be a binding for the connection.
         * */
            if (bind(ssocket, (struct sockaddr *)&server, sizeof(server)))
            {
                printf("ERROR on binding\n");
                return -1;
            }
            else
            {
                on = 1;

                while (on == 1)
                {
                    listen(ssocket, on);
                    puts("Listening for connection");
                    SocketAccept = accept(ssocket, (struct sockaddr *)&server, (socklen_t *)&addr);
                    if (SocketAccept < 0)
                    {
                        printf("Error not with acceptance\n");
                        return -1;
                    }
                    send(SocketAccept, file, strlen(file), 0);
                    puts("File sent");
                }
            }
            return 0;
        }
    }
}
