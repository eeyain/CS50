#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count, custom data type known as 'candidate'
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void swappointers(candidate *xp, candidate *yp);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;                                                                   //error code 1, not enough arguments (candidates)
    }

    // Populate array of candidates
    candidate_count = argc - 1;                                                     //takes total number of arguments provided after running ./plurality as no. of candidates
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;                                                                   //error code 2, too many arguments (candidates)
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)                                                      //implement linear search
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name,candidates[i].name) == 0)                           //YOU CANT USE STRING == STRING IT DOESNT WORK THAT WAY USE STRCMP
        {
            candidates[i].votes++;
            return true;
        }
    }
    // TODO
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)                                                     //do something similar to selection sort? except the sorting part, just select the highest int
{
    int maxindex;
    for (int i = 0; i < candidate_count - 1; i++)                           //selection sort
    {
        maxindex = i;
        for (int j = i + 1; j < candidate_count; j++)                       //
        {
            if (candidates[j].votes > candidates[i].votes)                  //if manage to find higher votes in position, change highest vote to this one
            {
                maxindex = j;
            }
        }
        swappointers(&candidates[maxindex], &candidates[i]);                //swap the pointers of maximum value & i positions
    }

    for (int count = 0; count < MAX; count++)
    {
        if (candidates[count].votes == candidates[0].votes)                 //if the no. of votes of the current are same as no. of votes of the max (1st), print
        {
            printf("%s\n",candidates[count].name);
        }
    }
    // TODO
    return;
}

void swappointers(candidate *xp, candidate *yp)                             //function to swap the pointers of 2 variables
{
    candidate temp = *xp;
    *xp = *yp;
    *yp = temp;
}
