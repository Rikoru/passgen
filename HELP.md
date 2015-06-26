# Password Generator

It generates passwords!

## Available Commands

-c | --stdout = Prints only to standard output.
Put this at the beginning if you want it to affect help.

-h | --help = Opens this help file.

-a | --smallalpha = Enables lowercase letters.

-A | --largealpha = Enables uppercase letters.

-s | --symbol = Enables symbols to be generated.

-n | --amount = Specify how many passwords to generate.
e.g. 'passgen -n 6' will generate 6 passwords.
Max amount to generate: 100 normally, 1000 for stdout.

-l | --length = Specify length of passwords to generate.
e.g. 'passgen -l 32' will generate a 32 digit password.
Max length to generate: 256 characters.

More commands are likely to be added with time, stay tuned.
