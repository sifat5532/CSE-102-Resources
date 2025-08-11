#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_DOCS 50
#define MAX_LEN 5000
#define MAX_TOKENS 500
#define MAX_TOKEN_LEN 50

char documents[MAX_DOCS][MAX_LEN];
char tokens[MAX_TOKENS][MAX_TOKEN_LEN];

int doc_idx_stemmed[MAX_DOCS];
char word_for_tf_idf[MAX_TOKEN_LEN];
char sorted_stemmed_tokens[MAX_TOKENS][MAX_TOKEN_LEN];

#define NUM_STOP_WORDS 8
char stop_words[NUM_STOP_WORDS][MAX_TOKEN_LEN] = {"the", "is", "a", "an", "and", "in", "of", "to"};

void normalize_case_all();
void tokenize_all();
void remove_stop_words_all();
void stem_all_tokens();
double compute_tf(char word[], int doc_id);
double compute_idf(char word[]);
void compute_tfidf_all(char word[]);
void display_stat();

// some variables to track some actions
int num_of_docs = -1;
int token_count = 0;
int is_processed = 0;

void normalize_case_all()
{
    for (int i = 0; i < num_of_docs; i++)
    {
        int doc_size = strlen(documents[i]);
        for (int j = 0; j < doc_size; j++)
        {
            documents[i][j] = tolower(documents[i][j]);
        }
    }
}

void tokenize_all()
{
    for (int i = 0; i < MAX_TOKENS; i++)
    {
        tokens[i][0] = '\0';
    }

    for (int i = 0; i < num_of_docs; i++)
    {
        int doc_size = strlen(documents[i]);
        int j;
        for (j = 0; j < doc_size; j)
        {
            if (isalnum(documents[i][j]))
            {
                int starting = j;
                int ending;
                while (isalnum(documents[i][j]))
                {
                    ending = j;
                    j++;
                }
                int k;
                for (k = 0; k <= (ending - starting); k++)
                {
                    tokens[token_count][k] = documents[i][starting + k];
                }
                tokens[token_count][k] = '\0';
                token_count++;
            }
            else
            {
                j++;
            }
        }
        doc_idx_stemmed[i] = token_count;
    }
}

void remove_stop_words_all()
{
    int c = 0;
    int word_count = 0;
    int word_deleted = 0;
    for (int i = 0; i < token_count; i++)
    {
        int matched = 0;
        for (int j = 0; j < NUM_STOP_WORDS; j++)
        {
            if (strcmp(tokens[i], stop_words[j]) == 0)
            {
                matched = 1;
                break;
            }
        }
        if (matched == 1)
        {
            for (int j = i; j < token_count; j++)
            {
                strcpy(tokens[j], tokens[j + 1]);
            }
            token_count--;
            i--;
            word_deleted++;
        }
        else
        {
            word_count++;
        }
        if (doc_idx_stemmed[c] == i + word_deleted + 1)
        {
            doc_idx_stemmed[c] = word_count;
            c++;
        }
    }
}

void stem_all_tokens()
{
    for (int i = 0; i < token_count; i++)
    {
        int length = strlen(tokens[i]);
        if (length >= 3 && tokens[i][length - 1] == 'g' && tokens[i][length - 2] == 'n' && tokens[i][length - 3] == 'i')
        {
            tokens[i][length - 3] = '\0';
        }
        else if (length >= 1 && tokens[i][length - 1] == 's')
        {
            tokens[i][length - 1] = '\0';
        }
        else if (length >= 2 && tokens[i][length - 1] == 'd' && tokens[i][length - 2] == 'e')
        {
            tokens[i][length - 2] = '\0';
        }
    }
}

double compute_tf(char word[], int doc_id)
{
    double doc_total_words = 0;
    double total_searched_word = 0;
    double tf;

    int search_initial;
    int search_ending;
    if (doc_id == 0)
    {
        doc_total_words = doc_idx_stemmed[doc_id];
        search_initial = 0;
        search_ending = doc_idx_stemmed[doc_id];
    }
    else
    {
        doc_total_words = doc_idx_stemmed[doc_id] - doc_idx_stemmed[doc_id - 1];
        search_initial = doc_idx_stemmed[doc_id - 1];
        search_ending = doc_idx_stemmed[doc_id];
    }
    for (int i = search_initial; i < search_ending; i++)
    {
        if (strcmp(word, tokens[i]) == 0)
        {
            total_searched_word++;
        }
    }
    tf = total_searched_word / doc_total_words;
    return tf;
}

double compute_idf(char word[])
{
    double idf;
    int in_how_many_docs = 0;
    for (int i = 0; i < num_of_docs; i++)
    {
        int search_initial;
        int search_ending;
        if (i == 0)
        {
            search_initial = 0;
            search_ending = doc_idx_stemmed[i];
        }
        else
        {
            search_initial = doc_idx_stemmed[i - 1];
            search_ending = doc_idx_stemmed[i];
        }

        for (int j = search_initial; j < search_ending; j++)
        {
            if (strcmp(word, tokens[j]) == 0)
            {
                in_how_many_docs++;
                break;
            }
        }
    }
    idf = log10((MAX_DOCS) / (1.0 + in_how_many_docs));
    return idf;
}

void sort_stemmed_tokens()
{
    for (int i = 0; i < token_count; i++)
    {
        strcpy(sorted_stemmed_tokens[i], tokens[i]);
    }

    for (int i = 0; i < token_count - 1; i++)
    {
        for (int k = 0; k < token_count - i - 1; k++)
        {
            if (strcmp(sorted_stemmed_tokens[k], sorted_stemmed_tokens[k + 1]) > 0)
            {
                char temp[MAX_TOKEN_LEN];
                strcpy(temp, sorted_stemmed_tokens[k]);
                strcpy(sorted_stemmed_tokens[k], sorted_stemmed_tokens[k + 1]);
                strcpy(sorted_stemmed_tokens[k + 1], temp);
            }
        }
    }
}

void display_stat()
{
    sort_stemmed_tokens();
    printf("============== TF ================\n");
    for (int i = 0; i < num_of_docs; i++)
    {
        if (i == 0)
        {
            printf("%-27s%s%d", "", "doc", i + 1);
        }
        else
        {
            printf("%-8s%s%d", "", "doc", i + 1);
        }
    }
    printf("\n");
    for (int i = 0; i < token_count; i++)
    {
        if (i == 0)
        {
            printf("%-25s", sorted_stemmed_tokens[i]);
            for (int j = 0; j < num_of_docs; j++)
            {
                double tf = compute_tf(sorted_stemmed_tokens[i], j);
                printf("%-12.4lf", tf);
            }
            printf("\n");
        }
        else
        {
            if (strcmp(sorted_stemmed_tokens[i], sorted_stemmed_tokens[i - 1]) != 0)
            {
                printf("%-25s", sorted_stemmed_tokens[i]);
                for (int j = 0; j < num_of_docs; j++)
                {
                    double tf = compute_tf(sorted_stemmed_tokens[i], j);
                    printf("%-12.4lf", tf);
                }
                printf("\n");
            }
        }
    }
    printf("\n");
    printf("=============== IDF ===============\n");
    printf("%-28s%s\n", "", "IDF");
    for (int i = 0; i < token_count; i++)
    {
        if (i == 0)
        {
            double idf = compute_idf(sorted_stemmed_tokens[i]);
            printf("%-25s%-12.4lf\n", sorted_stemmed_tokens[i], idf);
        }
        else
        {
            if (strcmp(sorted_stemmed_tokens[i], sorted_stemmed_tokens[i - 1]) != 0)
            {
                double idf = compute_idf(sorted_stemmed_tokens[i]);
                printf("%-25s%-12.4lf\n", sorted_stemmed_tokens[i], idf);
            }
        }
    }
    printf("\n");

    printf("============= TF-IDF ==============\n");
    for (int i = 0; i < num_of_docs; i++)
    {
        if (i == 0)
        {
            printf("%-27s%s%d", "", "doc", i + 1);
        }
        else
        {
            printf("%-8s%s%d", "", "doc", i + 1);
        }
    }
    printf("\n");
    for (int i = 0; i < token_count; i++)
    {
        if (i == 0)
        {
            printf("%-25s", sorted_stemmed_tokens[i]);
            double idf = compute_idf(sorted_stemmed_tokens[i]);
            for (int j = 0; j < num_of_docs; j++)
            {
                double tf = compute_tf(sorted_stemmed_tokens[i], j);
                printf("%-12.4lf", tf * idf);
            }
            printf("\n");
        }
        else
        {
            if (strcmp(sorted_stemmed_tokens[i], sorted_stemmed_tokens[i - 1]) != 0)
            {
                printf("%-25s", sorted_stemmed_tokens[i]);
                double idf = compute_idf(sorted_stemmed_tokens[i]);
                for (int j = 0; j < num_of_docs; j++)
                {
                    double tf = compute_tf(sorted_stemmed_tokens[i], j);
                    printf("%-12.4lf", tf * idf);
                }
                printf("\n");
            }
        }
    }
}

int main()
{
    // initializing all docs with empty string
    for (int i = 0; i < MAX_DOCS; i++)
    {
        documents[i][0] = '\0';
    }

    printf("Welcome to the Document Processing System!\n");
    printf("set         - Prompt for the number of documents and their text.\n");
    printf("preprocess  - Apply normalization, tokenization, stop-words removal, and stemming orderly.\n");
    printf("tf          - Compute and display Term Frequency for a specified word across documents.\n");
    printf("idf         - Compute and display Inverse Document Frequency for a specified word.\n");
    printf("tfidf       - Compute and display TF-IDF scores for a specified word across documents.\n");
    printf("stat        - Display TF, IDF, and TF-IDF for all tokens across all documents in a matrix format.\n");
    printf("help        - Print the list of all available commands.\n");
    printf("exit        - Exit the program.\n");

    int i;
    char command[20];

    while (1)
    {
        printf("Enter command: ");
        fgets(command, 20 - 1, stdin);
        command[strlen(command) - 1] = '\0';
        if (strcmp(command, "set") == 0)
        {
            // initializing all docs with empty string
            for (int i = 0; i < MAX_DOCS; i++)
            {
                documents[i][0] = '\0';
            }
            printf("Enter number of documents (1-50): ");
            scanf("%d", &num_of_docs);
            while (num_of_docs > 50 || num_of_docs < 1)
            {
                printf("Invalid number of documents. Must be from 1 to 50.\n");
                printf("Enter number of documents (1-50): ");
                scanf("%d", &num_of_docs);
            }
            scanf("%*c"); // using it to handle the last pressed enter button, otherwise it takes 'enter' as the input of first document
            for (i = 1; i <= num_of_docs; i++)
            {
                printf("Enter document %d: ", i);
                fgets(documents[i - 1], MAX_LEN, stdin); // it is taking enter as input

                while (documents[i - 1][0] == '\n')
                {
                    printf("Empty Document.\n");
                    printf("Enter document %d: ", i);
                    fgets(documents[i - 1], MAX_LEN, stdin);
                }
                int string_length_with_enter = strlen(documents[i - 1]);
                while (documents[i - 1][string_length_with_enter - 1] != '\n')
                {
                    // eliminating the extra characters one by one
                    char extra[2];
                    fgets(extra, 2, stdin);
                    while (extra[0] != '\n')
                    {
                        fgets(extra, 2, stdin);
                    }

                    printf("Document too long\n");
                    printf("Enter document %d: ", i);
                    fgets(documents[i - 1], MAX_LEN, stdin);
                    string_length_with_enter = strlen(documents[i - 1]);
                }
                // eliminating the last char which in enter
                documents[i - 1][string_length_with_enter - 1] = '\0';
            }
            if (i == num_of_docs + 1)
            {
                printf("Documents set successfully. Please, enter `preprocess' command now. It will not take other commands.\n");
            }

            // changing some variables to new state as it is setting new documents right now. so previous data should be removed.
            token_count = 0;
            is_processed = 0;

            // reseting tokens and sorted_tokens array
            for (int c = 0; c < MAX_TOKENS; c++)
            {
                tokens[c][0] = '\0';
                sorted_stemmed_tokens[c][0] = '\0';
            }
        }
        else if (strcmp(command, "preprocess") == 0)
        {
            if (num_of_docs == -1)
            {
                printf("Documents not initialized. Use 'set' command first.\n\n");
            }
            else
            {
                // normalization
                normalize_case_all();
                printf("Normalized Documents:\n");
                for (i = 1; i <= num_of_docs; i++)
                {
                    printf("Document %d: %s\n", i, documents[i - 1]);
                }
                printf("Documents normalized.\n");

                // tokenization
                token_count = 0;
                tokenize_all();
                printf("Tokens:\n");
                for (int i = 1; i <= token_count; i++)
                {
                    printf("%d. %s\n", i, tokens[i - 1]);
                }
                printf("Tokenization complete. Total tokens: %d\n", token_count);

                // remove words
                remove_stop_words_all();
                printf("Tokens after stop-word removal:\n");
                for (int i = 1; i <= token_count; i++)
                {
                    printf("%d. %s\n", i, tokens[i - 1]);
                }
                printf("Stop-word removal complete. Tokens remaining: %d\n", token_count);

                // stem tokens
                stem_all_tokens();
                printf("Stemmed Tokens:\n");
                for (int i = 0; i < token_count; i++)
                {
                    printf("%d. %s\n", i + 1, tokens[i]);
                }
                printf("Stemming complete. Total stemmed tokens: %d\n", token_count);

                is_processed = 1;
            }
        }
        else if (strcmp(command, "tf") == 0)
        {
            if (num_of_docs == -1)
            {
                printf("Documents not initialized. Use 'set' command first.\n\n");
            }
            else
            {
                if (is_processed == 0)
                {
                    printf("Please, enter `preprocess' command now. It will not take other commands.\n");
                }
                else
                {
                    printf("Enter word to compute TF: ");
                    scanf("%s", word_for_tf_idf);
                    scanf("%*c");
                    printf("TF for '%s':\n", word_for_tf_idf);
                    for (int i = 0; i < num_of_docs; i++)
                    {
                        double tf = compute_tf(word_for_tf_idf, i);
                        printf("Document %d: %.4lf\n", i + 1, tf);
                    }
                }
            }
        }
        else if (strcmp(command, "idf") == 0)
        {
            if (num_of_docs == -1)
            {
                printf("Documents not initialized. Use 'set' command first.\n\n");
            }
            else
            {
                if (is_processed == 0)
                {
                    printf("Please, enter `preprocess' command now. It will not take other commands.\n");
                }
                else
                {
                    printf("Enter word to compute IDF: ");
                    scanf("%s", word_for_tf_idf);
                    scanf("%*c");
                    double idf = compute_idf(word_for_tf_idf);
                    printf("IDF for '%s': %.4lf\n", word_for_tf_idf, idf);
                }
            }
        }
        else if (strcmp(command, "tfidf") == 0)
        {
            if (num_of_docs == -1)
            {
                printf("Documents not initialized. Use 'set' command first.\n\n");
            }
            else
            {
                if (is_processed == 0)
                {
                    printf("Please, enter `preprocess' command now. It will not take other commands.\n");
                }
                else
                {
                    printf("Enter word to compute TF-IDF: ");
                    scanf("%s", word_for_tf_idf);
                    scanf("%*c");
                    printf("TF-IDF for '%s':\n", word_for_tf_idf);
                    double idf = compute_idf(word_for_tf_idf);
                    for (int i = 0; i < num_of_docs; i++)
                    {
                        double tf = compute_tf(word_for_tf_idf, i);
                        printf("Document %d: %.4lf\n", i + 1, tf * idf);
                    }
                }
            }
        }
        else if (strcmp(command, "stat") == 0)
        {
            if (num_of_docs == -1)
            {
                printf("Documents not initialized. Use 'set' command first.\n\n");
            }
            else
            {
                if (is_processed == 0)
                {
                    printf("Please, enter `preprocess' command now. It will not take other commands.\n");
                }
                else
                {
                    display_stat();
                }
            }
        }
        else if (strcmp(command, "help") == 0)
        {
            printf("Welcome to the Document Processing System!\n");
            printf("set         - Prompt for the number of documents and their text.\n");
            printf("preprocess  - Apply normalization, tokenization, stop-words removal, and stemming orderly.\n");
            printf("tf          - Compute and display Term Frequency for a specified word across documents.\n");
            printf("idf         - Compute and display Inverse Document Frequency for a specified word.\n");
            printf("tfidf       - Compute and display TF-IDF scores for a specified word across documents.\n");
            printf("stat        - Display TF, IDF, and TF-IDF for all tokens across all documents in a matrix format.\n");
            printf("help        - Print the list of all available commands.\n");
            printf("exit        - Exit the program.\n");
        }
        else if (strcmp(command, "exit") == 0)
        {
            printf("Exiting program.\n");
            break;
        }
        else
        {
            printf("Unknown command. Type 'help' for list of commands.\n");
        }
    }
    return 0;
}