#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int len_of_file(FILE* fp);
void word_count(FILE* fp);
void reading_str(FILE* fp);
int verefication(FILE* fp);
void file_text_write(FILE* fp);
void replace_words_starting_with_char(FILE* fp);
int if_close(FILE* fp);
void print_str(FILE* fp);

const char* file = "text.txt";

int main(arg, kvark)
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".utf8");

    FILE* fp;

    fp = fopen(file, "w");
    verefication(fp);
    print_str(fp);
    if_close(fp);

    fp = fopen(file, "r");
    verefication(fp);
    reading_str(fp);
    word_count(fp);
    if_close(fp);

    fp = fopen(file, "r+");
    verefication(fp);
    replace_words_starting_with_char(fp);
    if_close(fp);

    fp = fopen(file, "r");
    verefication(fp);
    printf("\nФайл после изменений:\n");
    reading_str(fp);
    word_count(fp);
    if_close(fp);


    return 0;
}

int len_of_file(FILE* fp)
{
    int len = 0;
    char a;
    rewind(fp);
    while ((fscanf(fp, "%c", &a)) != EOF)
    {
        len += 1;
    }
    return len;
}

void word_count(FILE* fp)
{
    int count = 0;
    char prev = ' ';
    char current;

    rewind(fp); 

    while ((fscanf(fp, "%c", &current)) != EOF)
    {
        if (prev == ' ' && current != ' ' && current != '\n')
        {
            count += 1;
        }
        prev = current;
    }

    printf("\nКоличество слов: %d\n", count);
}

void reading_str(FILE* fp)
{
    printf("Содержимое файла: ");
    char value;
    rewind(fp); 
    while ((fscanf(fp, "%c", &value)) != EOF)
    {
        printf("%c", value);
    }
}

int verefication(FILE* fp)
{
    if (!fp)
    {
        printf("Error, check your actions");
        return 1;
    }
    return 0;
}

void file_text_write(FILE* fp)
{
    int value;
    printf("Ввод закончится, когда будет введено нечисловое значение\n");
    printf("Введите числа: ");
    while (scanf("%d", &value) == 1) {
        fprintf(fp, "%d ", value);
    }
}

int if_close(FILE* fp)
{
    if (fclose(fp) == EOF)
    {
        printf("Ошибка закрытия файла");
        return 1;
    }
    return 0;
}

void print_str(FILE* fp)
{
    char buffer[1024]; 
    printf("Введите текст (завершите ввод нажатием Enter):\n");

    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        fprintf(fp, "%s", buffer);
    }
}

void replace_words_starting_with_char(FILE* fp)
{
    int length = len_of_file(fp);
    rewind(fp);

    char target;
    printf("\nВведите букву, слова с которой нужно заменить: ");
    scanf(" %c", &target);

    int pos = 0;
    int word_start_pos = 0;
    int in_word = 0;
    int c;

    while (pos < length)
    {
        c = fgetc(fp);
        pos++;

        if (c == EOF) break;

        if (!in_word && c != ' ' && c != '\n')
        {
            word_start_pos = pos - 1;
            in_word = 1;

            if (c == target)
            {

                fseek(fp, word_start_pos, SEEK_SET);
                pos = word_start_pos;

                while (pos < length)
                {
                    c = fgetc(fp);
                    if (c == ' ' || c == '\n' || c == EOF) break;

                    fseek(fp, -1, SEEK_CUR);
                    fputc(' ', fp);
                    fflush(fp);
                    pos++;
                }

                fseek(fp, pos, SEEK_SET);
                in_word = 0;
                continue;
            }
        }
        else if (in_word && (c == ' ' || c == '\n'))
        {
            in_word = 0;
        }
    }
}