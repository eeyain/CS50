#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];                                                      //preferences[0][0] == 0, preferences[0][1] == 3 etc.

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];                                        //this is a single dimensional array!!

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

void swap_pointers(pair *xp, pair *yp);
bool cycle_pairs(int end, int cycle);                                   //custom function declarations

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];                                                //i+1 because the 1st argument (0) is ./tideman
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])               //ranks[] is an array that will record down the voter's preferences
{
    for (int i = 0; i < candidate_count; i++)               //linear search
    {
        if(strcmp(name,candidates[i]) == 0)                 //result found
        {
            ranks[rank] = i;                                //update ranks array with the corresponding [name] using the input rank as taken from line 81
            return true;
        }

    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])                            //update preferences[i][j] by +1 ing
{
    for (int i = 0; i < candidate_count; i++)               //TODO: check for logic errors
    {                                                           //"you'll need a loop within a loop" - chris nolan
        for (int j = i + 1; j < candidate_count; j++)           //prefer i above the rest of the values of the ranks[] array
        {
            preferences[ranks[i]][ranks[j]]++;
        }
        preferences[ranks[i]][ranks[i]] = 0;                    //preferences[ranks[i]][ranks[i]] == 0 is declared just in case
    }                                                           //candidate [i] can't be preferred over candidate [i]
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)                                            //update pairs.winner & pairs.loser with ints
{                                                               //go thru the preferences[][] 2-dimensional array
    for (int i = 0; i < candidate_count; i++)                   //TODO: check for logic errors
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])          //filter out cases where prf[][] = 0 & the loser is actually stronger
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)   //sort the pairs[] array
{
    int maxindex;
    for (int i = 0; i < pair_count - 1; i++)                //selection sort
    {
        maxindex = i;
        for (int j = i + 1; j < pair_count; j++)            //strength is to be determined by difference between winner & loser vote count
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[i].winner][pairs[i].loser])
            {                                               //if manage to find higher difference in position, change highest vote to this one
                maxindex = j;
            }
        }
        swap_pointers(&pairs[maxindex], &pairs[i]);        //swap the pointers of maximum value & i positions
    }
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)                   //use recursion?
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle_pairs(pairs[i].winner, pairs[i].loser))          //if the cycle_pairs function doesn't return true i.e. no cycles, lock pairs
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)       //winner has no arrows pointing to them i.e source of the graph
    {                                               //the candidate with all false values in their column is the winner. false_count == candidate_count
        int false_count = 0;                        //initialise no. of false counts to 0
        for (int j = 0; j < candidate_count; j++)   //i & j help to parse 2-d arrays, j for rows (down), i for columns (left)
        {
            if (locked[j][i] == false)
            {
                false_count++;                      // +1 every time a false value is encountered
                if (false_count == candidate_count) //this condition is inside the j loop cos we want false_count to go back to 0 for each candidate
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}

//swap 2 values of type pair using their pointers
void swap_pointers(pair *xp, pair *yp)
{
    pair temp = *xp;
    *xp = *yp;
    *yp = temp;
    return;
}

bool cycle_pairs(int end, int cycle)            //this function uses recursion to determine if any cycles are created.
{
    if (end == cycle)
    {
        return true;                            //base case. if there is a cycle this function will return true
    }
    else
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if(locked[end][i])                  //do only if the pair is locked
            {
                if(cycle_pairs(i, cycle))       //alternate exit condition for call stack
                {                               //leave this in, if not the function will use the same inputs as before, causing infinite recursion
                    return true;
                }
            }
        }
    }
    return false;
}
