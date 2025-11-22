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

/* ===========================
   FILE HANDLING FUNCTIONS
   =========================== */

void saveToFile() {
    FILE *file = fopen("policies.dat", "wb");
    if (!file) {
        printf("Error saving file!\n");
        return;
    }
    fwrite(&policy_count, sizeof(int), 1, file);
    fwrite(policies, sizeof(struct Policy), policy_count, file);
    fclose(file);
}

void loadFromFile() {
    FILE *file = fopen("policies.dat", "rb");
    if (!file) {
        printf("No existing file. Starting new database.\n");
        return;
    }
    fread(&policy_count, sizeof(int), 1, file);
    fread(policies, sizeof(struct Policy), policy_count, file);
    fclose(file);
}

/* ===========================
   CRUD FUNCTIONS
   =========================== */

void addPolicy() {
    if (policy_count >= MAX_POLICIES) {
        printf("Limit reached!\n");
        return;
    }

    getchar(); 
    policies[policy_count].id = policy_count + 1;

    printf("Enter title: ");
    fgets(policies[policy_count].title, MAX_TITLE_LEN, stdin);
    policies[policy_count].title[strcspn(policies[policy_count].title, "\n")] = 0;

    printf("Enter description: ");
    fgets(policies[policy_count].description, MAX_DESC_LEN, stdin);
    policies[policy_count].description[strcspn(policies[policy_count].description, "\n")] = 0;

    policy_count++;
    saveToFile();

    printf("Policy added successfully.\n");
}

void listPolicies() {
    if (policy_count == 0) {
        printf("No policies found.\n");
        return;
    }
    for (int i = 0; i < policy_count; i++) {
        printf("\nID: %d\nTitle: %s\nDescription: %s\n",
               policies[i].id, policies[i].title, policies[i].description);
    }
}

void searchPolicy() {
    char keyword[MAX_TITLE_LEN];
    getchar();
    printf("Enter search keyword: ");
    fgets(keyword, MAX_TITLE_LEN, stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    int found = 0;

    for (int i = 0; i < policy_count; i++) {
        if (strstr(policies[i].title, keyword) != NULL) {
            printf("\nID: %d\nTitle: %s\nDescription: %s\n",
                   policies[i].id, policies[i].title, policies[i].description);
            found = 1;
        }
    }

    if (!found)
        printf("No matching policy found.\n");
}

void updatePolicy() {
    int id;
    printf("Enter policy ID to update: ");
    scanf("%d", &id);
    
    if (id < 1 || id > policy_count) {
        printf("Invalid ID.\n");
        return;
    }

    getchar();

    printf("Enter new title: ");
    fgets(policies[id - 1].title, MAX_TITLE_LEN, stdin);
    policies[id - 1].title[strcspn(policies[id - 1].title, "\n")] = 0;

    printf("Enter new description: ");
    fgets(policies[id - 1].description, MAX_DESC_LEN, stdin);
    policies[id - 1].description[strcspn(policies[id - 1].description, "\n")] = 0;

    saveToFile();
    printf("Policy updated successfully.\n");
}

void deletePolicy() {
    int id;
    printf("Enter policy ID to delete: ");
    scanf("%d", &id);

    if (id < 1 || id > policy_count) {
        printf("Invalid ID.\n");
        return;
    }

    for (int i = id - 1; i < policy_count - 1; i++) {
        policies[i] = policies[i + 1];
        policies[i].id = i + 1; // reassign ID
    }

    policy_count--;
    saveToFile();

    printf("Policy deleted successfully.\n");
}

/* ===========================
   MAIN MENU
   =========================== */

int main() {
    loadFromFile();
    int choice;

    do {
        printf("\n=========== POLICY ANNOUNCEMENT MANAGEMENT ===========\n");
        printf("1. Add Policy\n");
        printf("2. List Policies\n");
        printf("3. Search Policy by Title\n");
        printf("4. Update Policy\n");
        printf("5. Delete Policy\n");
        printf("6. Exit\n");
        printf("=======================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPolicy(); break;
            case 2: listPolicies(); break;
            case 3: searchPolicy(); break;
            case 4: updatePolicy(); break;
            case 5: deletePolicy(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}
