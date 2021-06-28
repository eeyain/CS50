#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
              //A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q,  R, S, T, U, V, W, X, Y, Z
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 == score2)                       //print winner
    {
        printf("Tie!\n");
    }
    else if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int compute_score(string word)
{
    string s = word;
    int sum = 0;                                        //initialize variables
    for (int i = 0, n = strlen(word); i < n; i++)       //convert each char of the input string into uppercase
    {
        if (islower(s[i]))
        {
            s[i] = toupper(s[i]);
        }
    }
    for (int i = 0, n = strlen(word); i < n; i++)       //sum loop
    {
        if (s[i] >= 'A' && s[i] <= 'Z')                 //filters out alphabet characters only
        {
            sum = sum + POINTS[s[i] - 65];              //refer to ASCII table. assigns each letter to a numerical value e.g. a = 1, b = 2 etc
        }
    }
    return sum;

    /*
    int s[] = word;
    int sum = 0;
    if (s[i] >= 'a' && s[i] <= 'z')
    {
        s[i] = s[i] - 32;                 //convert to uppercase
    }
    for (int i = 0, int n = strlen(s); i < n; i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            sum = sum + POINTS[s[i] - 65];
        }
    }
    return sum;
    // TODO: Compute and return score for string
    */
}

