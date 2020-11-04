#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

size_t location(const char *word);
char *word_to_pig_latin(const char *word) {
    size_t vowelLocation = location(word);
    char *newWord;
    if(vowelLocation == 0)
    {
        newWord = malloc(sizeof(char)*(strlen(word)+4));
        strcpy(newWord, word);
        strcat(newWord, "way");
    } else {
        newWord = malloc(sizeof(char)*(strlen(word)+3));
        strcpy(newWord, &word[vowelLocation]);
        strncat(newWord, word, vowelLocation);
        strcat(newWord, "ay");
    }
    for (size_t i = 0; i < strlen(newWord); i++)
    {
        if (tolower(newWord[i]) != newWord[i])
        {
            newWord[i] = tolower(newWord[i]);
            newWord[0] = toupper(newWord[0]);
        }
    }
    return newWord;
}

size_t location(const char *word)
{
    const char vowels[] = {'A', 'a', 'E', 'e', 'I', 'i', 'O', 'o', 'U', 'u', 'y'};
    bool found = false;
    size_t vowelLocation = 0;
    int whichVowel = 0;
    while(true)
    {
        while(whichVowel < 11)
        {
            if ((int)word[vowelLocation] == (int)vowels[whichVowel])
            {
                return vowelLocation;
            }else{
            whichVowel++;
            }
        }
        vowelLocation++;
        whichVowel = 0;
    }
}

void test_pig_latin() {
    const char *cases[][2] = {
        { "exit", "exitway" },
        { "Yellow", "Ellowyay" },
        { "scram", "amscray" },
        { "blue", "ueblay" },
        { "Type", "Ypetay" },
        { "igloo", "iglooway" },
        { "Float", "Oatflay" },
        { "bandanda",  "andandabay" },
        { "Apple", "Appleway" },
        
        // feel free to add more cases above this line,
        // but leave the { NULL, NULL } line intact.
        { NULL, NULL }
    };
    
    size_t i = 0;
    int failed_cases = 0, passed_casses = 0;
    while(1) {
        const char *original = cases[i][0];
        const char *expected_latin = cases[i][1];
        
        if(!original || !expected_latin) {
            break;
        }
        
        char *actual_latin = word_to_pig_latin(original);
        
        if(!actual_latin || strcmp(expected_latin, actual_latin) != 0) {
            printf("Test case failed: expected '%s' -> '%s', but got '%s'\n", original, expected_latin, actual_latin);
            
            failed_cases++;
        }
        else {
            passed_casses++;
        }
        
        free(actual_latin);
        
        i++;
    }
    
    printf("%d/%d cases passed\n", passed_casses, failed_cases + passed_casses);
}

int main(int argc, char *argv[]) {
    test_pig_latin();
    
    return 0;
}