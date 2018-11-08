#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if (argc > 2 || argc == 1)
    {
        printf("Error: Missing port number or too many arugments.\n");
        return -1;
    }
    else
    {
        struct sockaddr_in serveraddress;
        int FileStored;
        int csocket;
        int port;
        char FileIn[18167] = {0};

        port = atoi(argv[1]);
        csocket = socket(AF_INET, SOCK_STREAM, 0);

        memset(&serveraddress, 0, sizeof serveraddress);
        serveraddress.sin_family = AF_INET;
        serveraddress.sin_port = htons(port);

        if (csocket < 0)
        {
            printf("ERROR opening socket");
            return -1;
        }
        else
        {
            if (connect(csocket, (struct sockaddr *)&serveraddress, sizeof(serveraddress)) < 0)
            {
                printf("Error Server is not up\n");
                return -1;
            }
            else
            {
                FileStored = read(csocket, FileIn, sizeof(FileIn));
                puts("Connected to server: ");
                printf("%s", FileIn);
                close(csocket);
            }
            return 0;
        }
    }
}
