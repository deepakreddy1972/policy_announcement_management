#include <stdio.h>
#include <string.h>

#define MAX_POLICIES 100
#define MAX_TITLE_LEN 50
#define MAX_DESC_LEN 200

struct Policy {
    int id;
    char title[MAX_TITLE_LEN];
    char description[MAX_DESC_LEN];
};

struct Policy policies[MAX_POLICIES];
int policy_count = 0;

FILE *file;

// Load policies from file
void loadPolicies() {
    file = fopen("policies.dat", "rb");
    if (file == NULL) {
        // File does not exist → create new
        file = fopen("policies.dat", "wb");
        fclose(file);
        return;
    }

    fread(&policy_count, sizeof(int), 1, file);
    fread(policies, sizeof(struct Policy), policy_count, file);
    fclose(file);
}

// Save policies to file
void savePolicies() {
    file = fopen("policies.dat", "wb");
    fwrite(&policy_count, sizeof(int), 1, file);
    fwrite(policies, sizeof(struct Policy), policy_count, file);
    fclose(file);
}

void addPolicy() {
    if (policy_count < MAX_POLICIES) {
        policies[policy_count].id = policy_count + 1;
        printf("Enter policy title: ");
        getchar(); 
        fgets(policies[policy_count].title, MAX_TITLE_LEN, stdin);
        policies[policy_count].title[strcspn(policies[policy_count].title, "\n")] = 0;

        printf("Enter policy description: ");
        fgets(policies[policy_count].description, MAX_DESC_LEN, stdin);
        policies[policy_count].description[strcspn(policies[policy_count].description, "\n")] = 0;

        policy_count++;
        savePolicies(); // AUTO-SAVE
        printf("Policy added successfully with ID %d.\n", policy_count);
    } else {
        printf("Policy limit reached!\n");
    }
}

void listPolicies() {
    if (policy_count == 0) {
        printf("No policies available.\n");
        return;
    }
    printf("Listing all policies:\n");
    for (int i = 0; i < policy_count; i++) {
        printf("ID: %d\nTitle: %s\nDescription: %s\n\n", 
            policies[i].id, policies[i].title, policies[i].description);
    }
}

void searchPolicyByTitle() {
    char search_title[MAX_TITLE_LEN];
    printf("Enter title to search: ");
    getchar();
    fgets(search_title, MAX_TITLE_LEN, stdin);
    search_title[strcspn(search_title, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < policy_count; i++) {
        if (strstr(policies[i].title, search_title) != NULL) {
            printf("Found Policy - ID: %d\nTitle: %s\nDescription: %s\n\n", 
                policies[i].id, policies[i].title, policies[i].description);
            found = 1;
        }
    }
    if (!found) {
        printf("No policy found with title containing '%s'.\n", search_title);
    }
}

int main() {
    int choice;

    // Load existing data automatically
    loadPolicies();

    do {
        printf("\nPolicy Management System\n");
        printf("1. Add Policy\n2. List Policies\n3. Search Policy by Title\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPolicy();
                break;
            case 2:
                listPolicies();
                break;
            case 3:
                searchPolicyByTitle();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
