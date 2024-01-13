#inculde "send_email.h"
#include <stdio.h>
#include <stdlib.h>

void sendEmail(const char *subject, const char *body, const char *attachment) {
    const char *smtpUsername = "tubabintenaushad@gmail.com";
    const char *smtpServer = "smtp.gmail.com";
    const char *smtpPort = "465";  // Adjust the port
    const char *smtpPassword = "nsgv anjv sxna skbi";  // Replace with your secure password retrieval method

    // Dynamically allocate memory for the email command
    char *emailCommand = (char *)malloc(3000);  // Adjust the size based on your needs

    if (emailCommand == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    // Compose the Mutt command with attachment and variable body
    snprintf(emailCommand, 3000,
             "echo '%s' | /usr/bin/mutt -s '%s' -a %s -- tubabintenaushad@gmail.com -e 'set content_type=text/plain' -e 'set ssl_starttls=yes' -e 'set smtp_url=smtp://%s@%s:%s/' -e 'set smtp_pass=%s'",
             body, subject, attachment, smtpUsername, smtpServer, smtpPort, smtpPassword);

    // Execute the command using the system function
    int result = system(emailCommand);

    // Free the dynamically allocated memory
    free(emailCommand);


    if (result == -1) {
        fprintf(stderr, "Failed to send the email.\n");
    } else {
        printf("Email sent successfully.\n");
    }
}
