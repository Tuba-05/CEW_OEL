#include <stdio.h>
#include <stdlib.h>

int main() {
    char emailCommand[500];  // Buffer to hold the command

    // Compose the Mutt command
    snprintf(emailCommand, sizeof(emailCommand),
             "echo 'Your email body goes here' | mutt -s 'Subject Line' tubabintenaushad@gmail.com -e 'set content_type=text/plain'");

    // Execute the command using system function
    int result = system(emailCommand);

    if (result == -1) {
        printf("Failed to send the email.\n");
        return 1;
    }

    printf("Email sent successfully.\n");
    return 0;
}
