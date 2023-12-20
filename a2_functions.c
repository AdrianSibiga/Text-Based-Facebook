/********* definitions.c ********
    Student Name 	= Adrian Sibiga
    Student Number	= 101196820
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t* add_user(user_t* users, const char* username, const char* password)
{
   //Create new user
   user_t* new_user = malloc(sizeof(user_t));
   assert(new_user != NULL);

   new_user->friends = NULL;
   new_user->posts = NULL;
   strcpy(new_user->username, username);
   strcpy(new_user->password, password);

   if (users == NULL || strcasecmp(new_user->username, users->username) < 0) {
      new_user->next = users;
      users = new_user;
      return new_user;
   }

   user_t* current_user = users;

   while (current_user->next != NULL && strcasecmp(current_user->next->username, new_user->username) < 0) {
      current_user = current_user->next;
   }

   new_user->next = current_user->next;
   current_user->next = new_user;

   return users;
}
/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t* find_user(user_t* users, const char* username)
{
   user_t* current_user = users;

   while (current_user != NULL) {
      if (strcmp(current_user->username, username) == 0) {
         // printf("%s\n", current_user->posts->next->content);
         // printf("%s\n", current_user->posts->next->next->content);
         return current_user;
      }
      current_user = current_user->next;
   }
   return NULL;
}
/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t* create_friend(const char* username)
{
   //Create a new friend
   friend_t* new_friend = malloc(sizeof(friend_t));
   assert(new_friend != NULL);

   //Initiate new friend
   strcpy(new_friend->username, username);
   new_friend->next = NULL;

   return new_friend;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t* user, const char* friend)
{
   //Create new friend
   friend_t* new_friend = malloc(sizeof(friend_t));
   assert(new_friend != NULL);

   strcpy(new_friend->username, friend);

   if (user->friends == NULL || strcasecmp(new_friend->username, user->friends->username) < 0) {
      new_friend->next = user->friends;
      user->friends = new_friend;
      return;
   }

   friend_t* current_friend = user->friends;

   while (current_friend->next != NULL && strcasecmp(current_friend->next->username, new_friend->username) < 0) {
      current_friend = current_friend->next;
   }

   new_friend->next = current_friend->next;
   current_friend->next = new_friend;
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t* user, char* friend_name) //input "user_to_find" as "user"
{
   friend_t* current = user->friends;
   friend_t* temp;

   if (current == NULL) {
      return  0;
   }

   if (strcmp(user->friends->username, friend_name) == 0) {
      temp = current->next;
      free(current);
      user->friends = temp;
      return 1;
   }

   while (current->next != NULL) {
      if (strcmp(current->next->username, friend_name) == 0) {
         temp = current->next->next;
         free(current->next);
         current->next = temp;
         return 1;
      }
      current = current->next;
   }
   return 0;
}


/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t* create_post(const char* text)
{
   post_t* post = malloc(sizeof(post_t));
   assert(post != NULL);

   strcpy(post->content, text);
   post->next = NULL;
   return post;
}

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t* user, const char* text)
{
   post_t* post = create_post(text);

   post->next = user->posts;
   user->posts = post;
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t* user, int number)
{
   post_t* current = user->posts;
   post_t* temp;

   if (current == NULL) {
      return 0;
   }

   if (number == 1) {
      temp = current->next;
      free(current);
      user->posts = temp;
      return 1;
   }

   int count = 1;
   while (current->next != NULL) {
      if (count == number - 1) {
         temp = current->next->next;
         free(current->next);
         current->next = temp;
         return 1;
      }
      count++;
      current = current->next;
   }
   return 0;
}

/*
   Function that  displays a specific user's posts
*/
void display_user_posts(user_t* user)
{
   post_t* current = user->posts;
   int count = 1;

   printf("-----------------------------------------------\n");
   printf("%s's Posts:\n", user->username);

   if (current == NULL) {
      printf("No posts available for %s.\n", user->username);
   }
   else {
      while (current != NULL) {
         printf("%d- %s\n", count, current);
         current = current->next;
         count++;
      }
   }

   printf("------------------------------------------------\n\n");
}

/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t* user)
{
   friend_t* current = user->friends;
   int count = 1;

   printf("\nList of %s's friends:\n", user->username);
   if (current == NULL) {
      printf("No friends available for %s.\n", user->username);
   }
   else {
      while (current != NULL) {
         printf("%d- %s\n", count, current);
         current = current->next;
         count++;
      }
   }
   printf("\n");
}
/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t* users)
{
   user_t* current = users;
   int display_next = 1;
   char yes;

   while (display_next == 1) {
      if (current != NULL) {
         display_user_posts(current);
      }
      else {
         printf("All Posts have been displayed.\n");
         return;
      }
      if (current->next != NULL) {
         display_user_posts(current->next);
      }
      else {
         printf("All Posts have been displayed.\n");
         return;
      }
      printf("Do you want to display the next 2 users posts? (Y/N): ");
      scanf(" %c", &yes);
      printf("\n");
      if ((yes == 'y') || (yes == 'Y')) {
         display_next = 1;
         current = current->next->next;
      }
      else {
         display_next = 0;
      }
   }
}

/*
   Fucntion that free all users from the database before quitting the application.
*/
void teardown(user_t* users)
{
   user_t* current = users;
   user_t* next;
   friend_t* current_friend = users->friends;
   friend_t* next_friend;
   post_t* current_post = users->posts;
   post_t* next_post;

   while (current != NULL) {
      while (current_friend != NULL) {
         next_friend = current_friend->next;
         free(current_friend);
         current_friend = next_friend;
      }
      while (current_post != NULL) {
         next_post = current_post->next;
         free(current_post);
         current_post = next_post;
      }
      next = current->next;
      free(current);
      current = next;
   }
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{

   printf("***********************************************\n");
   printf("                 MAIN MENU:\n");
   printf("***********************************************\n");
   printf("1. Register a new User\n");
   printf("2. Manage a user's profile (change password)\n");
   printf("3. Manage a user's posts (display/add/remove)\n");
   printf("4. Manage a user's friends (display/add/remove)\n");
   printf("5. Display All Posts\n");
   printf("6. Exit\n\n");

   printf("Enter your choice: ");

}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t* read_CSV_and_create_users(FILE* file, int num_users)
{
   user_t* users = NULL;
   char buffer[500];
   fgets(buffer, sizeof(buffer), file); // Read and discard the header line
   int count = 0;
   for (int i = 0; i < num_users; i++)
   {
      fgets(buffer, sizeof(buffer), file);
      buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

      char* token = strtok(buffer, ",");
      char* token2 = strtok(NULL, ",");
      users = add_user(users, token, token2);
      char* username = token;

      token = strtok(NULL, ",");

      user_t* current_user = users;
      for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
         ;

      while (token != NULL && strcmp(token, ",") != 0 && count < 3)
      {
         if (strcmp(token, " ") != 0)
         {
            add_friend(current_user, token);
         }
         token = strtok(NULL, ",");
         count++;
      }
      count = 0;

      // token = strtok(NULL, ",");
      while (token != NULL && strcmp(token, ",") != 0)
      {
         add_post(current_user, token);
         token = strtok(NULL, ",");
      }

   }
   return users;
}


/********Extra functions********/


// Prints the linked list of users
void print_list_usernames(user_t* user)
{
   if (user == NULL) {
      printf("empty list\n");
      return;
   }

   user_t* curr;

   for (curr = user; curr->next != NULL; curr = curr->next) {
      printf("%s -> ", curr->username);
   }

   /* Print the last node. */
   printf("%s\n", curr->username);
}

//Prints the linked list of a user's friends
void print_list_friends(friend_t* friend)
{
   if (friend == NULL) {
      printf("empty list\n");
      return;
   }

   friend_t* curr;

   for (curr = friend; curr->next != NULL; curr = curr->next) {
      printf("%s -> ", curr->username);
   }

   /* Print the last node. */
   printf("%s\n", curr->username);
}

//Prints the linked list of a user's posts
void print_list_posts(post_t* post)
{
   if (post == NULL) {
      printf("empty list\n");
      return;
   }

   post_t* curr;

   for (curr = post; curr->next != NULL; curr = curr->next) {
      printf("%s -> ", curr->content);
   }

   /* Print the last node. */
   printf("%s\n", curr->content);
}

/********************************/