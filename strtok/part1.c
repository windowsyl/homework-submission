#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

size_t my_strspn (char *s, const char *delims)
{
    for (size_t i = 0; i < strlen(s); i++)
    {
        for (size_t j = 0; j < strlen(delims); j++)
        {
            if(s[i] != delims[j])
            {
                return i;
            }
        }
    }
    return strlen(s);
}

size_t my_strcspn (char *s, const char *delims)
{
    for (size_t i = 0; i < strlen(s); i++)
    {
        for (size_t j = 0; j < strlen(delims); j++)
        {
            if(s[i] == delims[j])
            {
                return i;
            }
        }
    }
    return strlen(s);
}

char *my_strtok(char *s, const char *delims) {
    // static variables maintain their value between
    // calls to the function in which they are declared.
    static char *next_token = NULL;
    
    if(s == NULL) {
        // If the first argument is NULL, we're
        // starting from the last token we found.
        s = next_token;
    }

    // ** (1) strspn counts the number of leading characters in the string delims. 
    //by adding that to s, the pointer will now be pointing to the first character in the string that isn't a delimeter.
    // What is the next line of code doing?
    s += my_strspn(s, delims);
    // If we're at the end of the string, we're done
    if(*s == '\0') {
        return NULL;
    }
    // ** (2) strcspn counts how many leading characters aren't in the delims string, so by pointing next_token to s+that, it will point to the next delimeter.
    // What is the next line of code doing?
    next_token = s + strcspn(s, delims);
    // ** (3) the if statment checks if next token got to the end of the string, rather than hitting a delimeter.
    //if it hit a delimeter, it cuts the string there and points next_token to the beginning of the next token, prepared to be called again and keep cutting.
    //if it hit the end of the string, it is expecting to be called on a completely different string next, and is prepared as next_token is already reset to NUL.
    // What is this if-statement doing and why?
    if(*next_token != '\0') {
        *next_token = '\0';
        next_token++;
    }
    
    return s;
}

int main( int argc, char *argv[] ) {
    char *s = strdup(".aaa.aasfajdhf.sdfjhsdafh.aba.");
    s = my_strtok(s, "."); 
    while (s != NULL)
    {
    printf("%s\n",s);
    s = my_strtok(NULL, ".");
    }

    return 0;
}
