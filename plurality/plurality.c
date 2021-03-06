#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
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

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
bool vote(string name)
{
    bool found = false;

    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(name, candidates[j].name) == 0)
        {
            candidates[j].votes = candidates[j].votes + 1;
            found = true;

        }

    }
    if (found)
    {
        return true;
    }
    else
    {
        return false;
    }

}

// Print the winner (or winners) of the election
void print_winner(void)
{


    // a = candidates
    // length = candidate_count


    for (int i = 0; i < candidate_count; i++)
    {
        int minimum_value_index = i;
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (candidates[j].votes < candidates[minimum_value_index].votes)
            {
                minimum_value_index = j;
            }
        }
        if (minimum_value_index != i)
        {
            candidate temp = candidates[i];
            candidates[i] = candidates[minimum_value_index];
            candidates[minimum_value_index] = temp;
        }
    }

    if (candidates[candidate_count - 1].votes == candidates[candidate_count - 2].votes)
    {
        if (candidates[candidate_count - 2].votes == candidates[candidate_count - 3].votes)
        {
            printf("%s\n%s\n%s\n", candidates[candidate_count - 1].name, candidates[candidate_count - 2].name,
                   candidates[candidate_count - 3].name);
        }
        else
        {
            printf("%s\n%s\n", candidates[candidate_count - 1].name, candidates[candidate_count - 2].name);
        }
    }
    else
    {
        printf("%s\n", candidates[candidate_count - 1].name);
    }

    /*
        for (int k = 0; k < candidate_count; k++)
        {
        printf("%s, %i\n", candidates[k].name, candidates[k].votes);
        }
    */

    return;
}

