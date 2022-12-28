#include "Client.h"

int main() {
    if (!CreateSocket()) {
        return EXIT_FAILURE;
    }

    SetupServerInfo();

    char Command[50];
    printf("Waiting for a commands...\n");
    while (fgets(Command, 30, stdin)) {
        if (strncmp(Command, "exit", 4) == 0) {
            break;
        } else if (strncmp(Command, "download", 8) == 0) {
            // Split the command into "download" & "filename", just get FileName
            char *FileName;
            FileName = strtok(Command, " \n");
            FileName = strtok(NULL, " \n");

            if (CheckFileStatus(FileName)) {
                long long TimeBefore, TimeAfter;

                printf("Receiving...\n");

                TimeBefore = getCurrentTime();
                recvFile(FileName);
                TimeAfter = getCurrentTime();

                printf("End of receiving.\n");
                printf("Total cost %.3lf seconds.\n", (TimeAfter - TimeBefore) / 1000.0);
            }
        } else {
            printf("Illegal command\n");
        }

        printf("Waiting for a commands...\n");
    }

    return EXIT_SUCCESS;
}
