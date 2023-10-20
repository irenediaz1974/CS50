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
} candidate;

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
    // TODO : Find if a name is in the array of candidates
    // update the global preferences array to indicate that the voter (voter)
    // has that candidate as their rank preference (where 0 is the first preference, 1 is the second preference, etc.).

    for (int c = 0; c < candidate_count; c++)
    {
        if (strcmp(candidates[c].name, name) == 0)
        {
            preferences[voter][rank] = c;
            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO fill the candidates.votes field in array candidates (candidates[i].votes)
    // if non-eliminated candidates count votes in the preference matrix with j=0
    // if candidate is eliminated, update votes by next preference option j=1 (if non_eliminated)...or 2...

    int num_candidate = 0;

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            num_candidate = preferences[i][j];

            if (candidates[num_candidate].eliminated == false)
            {
                candidates[num_candidate].votes += 1;

                break;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO find 50 % of the votes voter_count / 2
    int c_50 = voter_count / 2;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > c_50)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min_val = 100;
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes <= min_val)
            {
                min_val = candidates[i].votes;
            }
        }
    }
    return min_val;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // to find if two are tied
    int c_tie = 0;
    int c_eliminate = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes == min)
            {
                c_tie += 1;
            }
        }
        else
        {
            c_eliminate += 1;
        }
    }
    if (c_tie >= candidate_count - c_eliminate)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}