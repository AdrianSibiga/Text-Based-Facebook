/********* main.c ********
    Student Name 	=
    Student Number	=
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE
       AND GENERATE THE STARTING LINKED LIST.
    */
    FILE* csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t* users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);
    /******** DONT MODIFY THIS PART OF THE CODE ********/

    /* IMPORTANT: You must use the users linked list created in the code above.
                  Any new users should be added to that linked list.
    */

    // Your solution goes here
    // char username1[30] = "AdrianSibiga"; //1
    // char password1[15] = "Adrian";

    // char username2[30] = "JasonHuynh"; //3
    // char password2[15] = "Jason";

    // char username3[30] = "CalebAitken"; //2
    // char password3[15] = "Aitken";

    // char username4[30] = "KyleWilvers"; //4
    // char password4[15] = "Kyle";

    // char username5[30] = "MacleanCrowdis"; //4
    // char password5[15] = "Maclean";

    // user_t* users = NULL;
    // users = add_user(users, username1, password1);
    // print_list_usernames(users);
    // users = add_user(users, username2, password2);
    // print_list_usernames(users);
    // users = add_user(users, username3, password3);
    // print_list_usernames(users);
    // users = add_user(users, username4, password4);
    // print_list_usernames(users);
    // users = add_user(users, username5, password5);
    // print_list_usernames(users);

    _Bool exit = 0;
    _Bool exit_posts = 0;
    _Bool exit_friends = 0;
    _Bool deleted_post;
    _Bool deleted_friend;
    int choice;
    int choice_posts;
    int choice_posts_delete;
    int choice_friends;
    char username[30];
    char friend[30];
    char password[15];
    char post_content[250];

    printf("***********************************************\n");
    printf("        Welcome to Text-Based Facebook\n");
    printf("***********************************************\n\n");
    while (exit == 0) {

        print_menu();
        scanf("%d", &choice);

        if (choice == 1) {

            printf("\nEnter a username: ");
            scanf("%s", username);
            printf("Enter a password (up to 15 characters): ");
            scanf("%s", password);

            users = add_user(users, username, password);

            printf("\n***** User Added! *****\n\n");
        }
        else if (choice == 2) {
            printf("Enter a username to update their password: ");
            scanf("%s", username);
            user_t* user_to_find = find_user(users, username);

            if (user_to_find == NULL) {
                printf("\n\n------------------------------------------------\n");
                printf("              User not found.\n");
                printf("------------------------------------------------\n\n");
            }
            else {
                printf("Enter a new password (up to 15 characters): ");
                scanf("%s", password);
                strcpy(user_to_find->password, password);
                printf("\n***** Password Changed! *****\n\n");
            }
        }
        else if (choice == 3) {
            printf("Enter a username to manage their posts: ");
            scanf("%s", username);
            user_t* user_to_find = find_user(users, username);

            if (user_to_find == NULL) {
                printf("\n\n------------------------------------------------\n");
                printf("              User not found.\n");
                printf("------------------------------------------------\n\n");
            }
            else {
                exit_posts = 0;
                while (exit_posts == 0) {

                    display_user_posts(user_to_find);
                    printf("1. Add a new user post\n");
                    printf("2. Remove a users post\n");
                    printf("3. Return to main menu\n\n");

                    printf("Your choice: ");
                    scanf("%d", &choice_posts);

                    if (choice_posts == 1) {
                        printf("Enter your post content: ");
                        scanf(" %[^\n]s", post_content);
                        add_post(user_to_find, post_content);
                        printf("post added to your profile.\n");
                    }
                    else if (choice_posts == 2) {
                        printf("Which post do you want to delete?: ");
                        scanf("%d", &choice_posts_delete);
                        deleted_post = delete_post(user_to_find, choice_posts_delete);
                        if (deleted_post == 1) {
                            printf("Post %d was deleted successfully!\n", choice_posts_delete);
                        }
                        else {
                            printf("Invalid post's number\n\n");
                        }
                    }
                    else if (choice_posts == 3) {
                        exit_posts = 1;
                    }
                    else {
                        printf("Invalid choice. Please try again.\n\n");
                    }
                }
            }
        }
        else if (choice == 4) {
            printf("Enter a username to manage their friends: ");
            scanf("%s", username);
            user_t* user_to_find = find_user(users, username);
            if (user_to_find == NULL) {
                printf("\n\n------------------------------------------------\n");
                printf("              User not found.\n");
                printf("------------------------------------------------\n\n");
            }
            else {
                exit_friends = 0;
                while (exit_friends == 0) {
                    printf("\n------------------------------------------------\n");
                    printf("%s's friends:\n", user_to_find->username);
                    printf("------------------------------------------------\n\n");

                    printf("1. Display all user's friends\n");
                    printf("2. Add a new friend\n");
                    printf("3. Delete a friend\n");
                    printf("4. Return to main menu\n\n");

                    printf("Your choice: ");
                    scanf("%d", &choice_friends);

                    if (choice_friends == 1) {
                        display_user_friends(user_to_find);
                    }
                    else if (choice_friends == 2) {
                        printf("\nEnter a new friend's name: ");
                        scanf("%s", friend);
                        add_friend(user_to_find, friend);
                        printf("Friend added to list.\n");
                    }
                    else if (choice_friends == 3) {
                        printf("\nEnter a new friend's name to delete: ");
                        scanf("%s", friend);
                        deleted_friend = delete_friend(user_to_find, friend);
                        if (deleted_friend == 1) {
                            display_user_friends(user_to_find);
                        }
                        else {
                            printf("Invalid friend's name\n\n");
                        }
                    }
                    else if (choice_friends == 4) {
                        exit_friends = 1;
                    }
                    else {
                        printf("Invalid choice. Please try again.\n\n");
                    }
                }
            }
        }
        else if (choice == 5) {
            display_all_posts(users);
        }
        else if (choice == 6) {
            exit = 1;
            printf("\n***********************************************\n");
            printf("   Thank you for using Text-Based Facebook\n");
            printf("                   Goodbye!\n");
            printf("***********************************************\n\n");
        }
        else {
            printf("Invalid choice. Please try again.\n\n");
        }
    }
}//End of main