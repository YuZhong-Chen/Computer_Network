#include "Client.h"

int main() {
    if (!CreateSocket()) {
        return EXIT_FAILURE;
    }

    SetupServerInfo();

    InitSendPkt();

    printf("Waiting for a commands...\n");
    getchar();

    char Command[50];
    while (fgets(Command, 30, stdin)) {
        if (strncmp(Command, "exit", 4) == 0) {
            break;
        } else if (strncmp(Command, "download", 8) == 0) {
            // Split the command into "download" & "filename", just get FileName
            char *FileName;
            FileName = strtok(Command, " \n");
            FileName = strtok(NULL, " \n");

            if (CheckFileStatus(FileName)) {
                time_t t1, t2;

                printf("Receiving...\n");

                t1 = time(NULL);
                recvFile(FileName);
                t2 = time(NULL);

                printf("End of receiving.\n");
                printf("Total cost %ld secs\n", t2 - t1);
            }
        } else {
            printf("Illegal command\n");
        }

        printf("Waiting for a commands...\n");
    }

    return EXIT_SUCCESS;
}
