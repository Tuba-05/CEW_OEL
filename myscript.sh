#!/bin/bash

# Set any necessary environment variables
export MY_ENV_VARIABLE="some_value"

# Change to the directory containing your source files
cd /home/maida/Desktop/CEW

# Compile the program
gcc -I./cJSON main.c cJSON/cJSON.c send_email.c -o myprogram -lcurl

# Execute the compiled program
./myprogram

# Additional logic or commands if needed

