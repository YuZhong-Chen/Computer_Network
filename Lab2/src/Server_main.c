#include "Server.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please input the port number\n");
        return EXIT_FAILURE;
    }

    // argv[1] is the PORT number.
    if (!CreateSocket(atoi(argv[1]))) {
        return EXIT_FAILURE;
    }

    SetupClientInfo();

    while (true) {
        printf("Server waiting... \n");
        char *Command = ReceiveCmd();
        printf("Process command... \n");

        if (!strcmp(Command, "download")) {
            char *FileName = strtok(NULL, " \n");
            char FilePath[100];
            sprintf(FilePath, SERVER_DATABASE_PATH);
            strcat(FilePath, FileName);

            FILE *fd = fopen(FilePath, "rb");  // Read the file in binary format.
            if (fd == NULL) {
                // Send FILE_NOT_EXISTS msg to the client
                printf("The %s is not exist.\n", FileName);
                if (!SendMsg("FILE_NOT_EXISTS")) {
                    return EXIT_FAILURE;
                }
            } else {
                // Send FILE_EXIST msg to the client
                printf("The %s is exist.\n", FileName);
                if (!SendMsg("FILE_EXISTS")) {
                    return EXIT_FAILURE;
                }

                // Sleep 1 seconds before transmitting data to make sure the client is ready
                sleep(1);
                printf("Transmitting...\n");

                // Start to send the file to the client
                SendFile(fd);

                printf("End of transmitting.\n");
            }
        } else {
            printf("Illegal request!\n");
        }

        printf("\n");
    }

    return EXIT_SUCCESS;
}
