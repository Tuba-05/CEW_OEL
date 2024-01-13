#inculde "send_email.h"
#include <stdio.h>
#include <stdlib.h>

void sendEmail(const char *subject, const char *body, const char *attachment) {
    char emailCommand[1000];

    // Compose the Mutt command with attachment and variable body
    snprintf(emailCommand, sizeof(emailCommand),
             "echo '%s' | mutt -s '%s' -a %s -- tubabintenaushad@gmail.com -e 'set content_type=text/plain'",
             body, subject, attachment);

    // Execute the command using the system function
    int result = system(emailCommand);

    if (result == -1) {
        fprintf(stderr, "Failed to send the email.\n");
    } else {
        printf("Email sent successfully.\n");
    }
}
