#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int countwords(string s);                                       //function prototypes
int countletters(string s);
int countsentences(string s);

int main(void)
{
    string text = get_string("Text: ");
    int textlength = strlen(text);
    int wordcount = countwords(text);
    int lettercount = countletters(text);
    int sentencecount = countsentences(text);

    printf("%i letter(s)\n", lettercount);
    printf("%i word(s)\n", wordcount);
    printf("%i sentence(s)\n", sentencecount);

    float L = lettercount / (wordcount * 1.0) * 100;
    float S = sentencecount / (wordcount * 1.0) * 100;                  //the 1.0 is to convert the int to a float to prevent truncation

    int index = round((0.0588 * L) - (0.296 * S) - 15.8);               //Colemann-Liau formula

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 1 && index < 16)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }

}

int countwords(string s)
{
    int sum = 0;
    for (int i = 0, n = strlen(s); i < n; i++)                      //parse string
    {
        if (s[i] == ' ' && s[i + 1] != ' ')                         //count spaces, multiple spaces don't get counted
        {
            sum++;
        }
    }
    return sum + 1;      //a single word sentence has no spaces
}

int countletters(string s)
{
    int sum = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))       //counts upper and lower case alphabets
        {
            sum++;
        }
    }
    return sum;
}

int countsentences(string s)
{
    int sum = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == '.' || s[i] == '?' || s[i] == '!')                          //counts end of sentence punctuation
        {
            sum++;
        }
    }
    return sum;
}
