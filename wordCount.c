#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 50
#define MAX_PARAGRAPH_LEN 1000

// Function to convert a string to lowercase
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Check if character is a delimiter (space or punctuation)
int is_delimiter(char ch) {
    return !(isalpha(ch) || isdigit(ch));
}

int main() {
    char paragraph[MAX_PARAGRAPH_LEN];
    char words[MAX_WORDS][MAX_WORD_LEN];
    int freq[MAX_WORDS] = {0};
    int word_count = 0;

    printf("Enter a paragraph:\n");
    fgets(paragraph, sizeof(paragraph), stdin);

    // Replace newline with null terminator if present
    paragraph[strcspn(paragraph, "\n")] = 0;

    int len = strlen(paragraph);
    char word[MAX_WORD_LEN];
    int w_index = 0;

    for (int i = 0; i <= len; i++) {
        if (i == len || is_delimiter(paragraph[i])) {
            if (w_index > 0) {
                word[w_index] = '\0';
                to_lowercase(word);

                // Check if word already exists
                int found = 0;
                for (int j = 0; j < word_count; j++) {
                    if (strcmp(words[j], word) == 0) {
                        freq[j]++;
                        found = 1;
                        break;
                    }
                }
                if (!found && word_count < MAX_WORDS) {
                    strcpy(words[word_count], word);
                    freq[word_count] = 1;
                    word_count++;
                }
                w_index = 0;
            }
        } else {
            if (w_index < MAX_WORD_LEN - 1) {
                word[w_index++] = paragraph[i];
            }
        }
    }

    // Print word frequencies
    printf("\nWord Frequencies:\n");
    for (int i = 0; i < word_count; i++) {
        printf("%s : %d\n", words[i], freq[i]);
    }

    return 0;
}
