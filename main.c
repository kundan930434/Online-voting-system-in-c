#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES 5
#define FILE_NAME "votes.dat"

typedef struct {
    char name[50];
    int votes;
} Candidate;

void displayCandidates(Candidate candidates[], int n) {
    printf("\nAvailable candidates:\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }
}

void vote(Candidate candidates[], int n) {
    int choice;
    printf("\nEnter the number of the candidate you want to vote for: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > n) {
        printf("\nInvalid choice. Try again.\n");
    } else {
        candidates[choice - 1].votes++;
        printf("\nVote successfully cast for %s!\n", candidates[choice - 1].name);
    }
}

void displayResults(Candidate candidates[], int n) {
    printf("\nVoting results:\n");
    for (int i = 0; i < n; i++) {
        printf("%s: %d votes\n", candidates[i].name, candidates[i].votes);
    }
}

void saveVotes(Candidate candidates[], int n) {
    FILE *file = fopen(FILE_NAME, "wb");
    if (file == NULL) {
        printf("\nError saving the votes!\n");
        exit(1);
    }
    fwrite(candidates, sizeof(Candidate), n, file);
    fclose(file);
}

void loadVotes(Candidate candidates[], int n) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("\nNo previous votes found. Starting a new election.\n");
        return;
    }
    fread(candidates, sizeof(Candidate), n, file);
    fclose(file);
}

int main() {
    Candidate candidates[MAX_CANDIDATES] = {
        {"RAJA TAYAGI", 0},
        {"DIPTI JHA", 0},
        {"KARAN DUBE", 0},
        {"KUNDAN KRISHNAN", 0},
        {"SHREYASH SINGH", 0}
    };

    int choice;
    loadVotes(candidates, MAX_CANDIDATES);

    while (1) {
        printf("\nOnline Voting System\n");
        printf("1. Display candidates\n");
        printf("2. Cast a vote\n");
        printf("3. Show results\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayCandidates(candidates, MAX_CANDIDATES);
                break;
            case 2:
                vote(candidates, MAX_CANDIDATES);
                saveVotes(candidates, MAX_CANDIDATES);
                break;
            case 3:
                displayResults(candidates, MAX_CANDIDATES);
                break;
            case 4:
                saveVotes(candidates, MAX_CANDIDATES);
                printf("\nExiting system. Goodbye!\n");
                exit(0);
            default:
                printf("\nInvalid option. Try again.\n");
        }
    }

    return 0;
}
