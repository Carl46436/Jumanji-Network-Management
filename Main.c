#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMISSION_PER_PAIR 500

typedef struct Member {
    char name[50];
    int commission;
    struct Member* left;
    struct Member* right;
} Member;

Member* createMember(char* name) {
    Member* newMember = (Member*)malloc(sizeof(Member));
    strcpy(newMember->name, name);
    newMember->commission = 0;
    newMember->left = newMember->right = NULL;
    return newMember;
}

void addDownline(Member* parent, char* leftName, char* rightName) {
    if (leftName != NULL && strlen(leftName) > 0) {
        parent->left = createMember(leftName);
    }
    if (rightName != NULL && strlen(rightName) > 0) {
        parent->right = createMember(rightName);
    }
    if (parent->left != NULL && parent->right != NULL) {
        parent->commission += COMMISSION_PER_PAIR;
    }
}

void displayDownlines(Member* member) {
    if (member == NULL) return;

    printf("\nMember: %s\n", member->name);
    printf("Commission: P%d\n", member->commission);

    if (member->left) {
        printf("Left Downline: %s\n", member->left->name);
    } else {
        printf("Left Downline: None\n");
    }

    if (member->right) {
        printf("Right Downline: %s\n", member->right->name);
    } else {
        printf("Right Downline: None\n");
    }
}

void displayNetwork(Member* root, int level) {
    if (root == NULL) return;

    for (int i = 0; i < level; i++) printf("  ");
    printf("|| %s (Commission: P%d)|| \n", root->name, root->commission);

    displayNetwork(root->left, level + 1);
    displayNetwork(root->right, level + 1);
}

void addDownlineInteractive(Member* root) {
    char parentName[50], leftName[50], rightName[50];

    printf("Enter the name of the parent member: ");
    scanf("%s", parentName);

    // Search for the parent node
    Member* current = root;
    if (strcmp(current->name, parentName) != 0) {
        if (current->left && strcmp(current->left->name, parentName) == 0) {
            current = current->left;
        } else if (current->right && strcmp(current->right->name, parentName) == 0) {
            current = current->right;
        } else {
            printf("Parent member not found.\n");
            return;
        }
    }

    printf("Enter the name of the left downline (or press Enter to skip): ");
    scanf("%s", leftName);
    printf("Enter the name of the right downline (or press Enter to skip): ");
    scanf("%s", rightName);

    addDownline(current, leftName, rightName);
}

int main() {
    Member* root = createMember("Carl");

    addDownline(root, "CJ", "Sweet");
    addDownline(root->left, "Ivy", "John");
    addDownline(root->right, "Kevin", "Michael");

    int choice;

    while (1) {
        printf("\n--- Jumanji Network Management ---\n");
        printf("1. Display Network Tree\n");
        printf("2. Search Member and Display Downlines\n");
        printf("3. Add Downlines\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("clear");
                printf("\nNetwork Tree:\n");
                displayNetwork(root, 0);
                break;

            case 2:
                system("clear");
                printf("Enter the name of the member: ");
                char searchName[50];
                scanf("%s", searchName);

                if (strcmp(root->name, searchName) == 0) {
                    displayDownlines(root);
                } else if (root->left && strcmp(root->left->name, searchName) == 0) {
                    displayDownlines(root->left);
                } else if (root->right && strcmp(root->right->name, searchName) == 0) {
                    displayDownlines(root->right);
                } else {
                    printf("Member not found.\n");
                }
                break;

            case 3:
                system("clear");
                addDownlineInteractive(root);
                break;

            case 4:
                system("clear");
                printf("Exiting...\n");
                exit(0);
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
