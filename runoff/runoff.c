#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            printf("preferences[voter][rank]%i\n", preferences[voter][rank]);
            // candidates[i].votes++;
            // printf("candidates  votes%i\n", candidates[i].votes);
            return true;
            // break;
        }
    }
    // TODO
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int k = 0; k < voter_count; k++)
    {
        int current_vote = preferences[k][0];
        if (candidates[current_vote].eliminated == true)
        {
            current_vote = preferences[k][1];
            if (candidates[current_vote].eliminated == true)
            {
                current_vote = preferences[k][2];
            }
        }
        candidates[current_vote].votes++;
    }


    // TODO
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    float majority = 0.0;
    if (voter_count % 2 == 0)
    {
        majority = voter_count / 2.0;
    }
    else
    {
        majority = (voter_count / 2.0) + 0.5;
    }
    int int_majority = (int)majority;
    // printf("majority %i\n", int_majority);

    for (int l = 0; l < voter_count; l++)
    {
        if (candidates[l].votes > int_majority)
        {
            printf("%s\n", candidates[l].name);
            //printf("has %i votes\n", candidates[l].votes);
            return true;
            break;
        }
        // return false;
    }

    // TODO
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{


    for (int m = 0; m < candidate_count; m++)
    {
        int minimum_value_index = m;
        for (int n = m + 1; n < candidate_count; n++)
        {
            if ((candidates[n].votes < candidates[minimum_value_index].votes) && candidates[n].eliminated == false)
            {
                minimum_value_index = n;
            }
        }
        if (minimum_value_index != m)
        {
            candidate temp = candidates[m];
            candidates[m] = candidates[minimum_value_index];
            candidates[minimum_value_index] = temp;
        }
    }

    // TODO
    return candidates[0].votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{

    for (int o = 0; o < candidate_count; o++)
    {
        if ((candidates[o].eliminated == false) && (candidates[o].votes != min))
        {
            return false;
            break;
        }
        // return true;
    }


    // TODO
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int p = 0; p < candidate_count; p++)
    {
        if ((candidates[p].eliminated == false) && (candidates[p].votes == min))
        {
            candidates[p].eliminated = true;
        }
        // return true;
    }

    // TODO
    return;
}
