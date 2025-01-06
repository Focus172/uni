#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include <vector>

class Network {
private:
public:
  std::vector<User *> users_;

public:
  Network();
  ~Network();

  /// pre: pointer is non-null and unique
  /// post: the user is added
  void addUser(User *);

  /// pre: none
  /// post: a link between 2 users is added if either doesn't returns -1
  int addConnection(std::string s1, std::string s2);

  /// pre: none
  /// post: a link between 2 users is deleted if either doesn't returns -1
  int deleteConnection(std::string s1, std::string s2);

  /// pre: none
  /// post: returns the number user
  int numUsers();

  /// pre: none
  /// post: gets the id of the user by name. returns -1 if the user doesn't
  ///       exists
  int getId(std::string name);
  /// pre: none
  /// post: gets pointer to a user from a given id. returns null if there is no
  ///       such user. pointer is valid until next call to `addUser` or
  ///       `readUsers`
  User *getUser(int id);

  /// pre: none
  /// post: gets an inmutable reference to the users of this network
  std::vector<User *> const &getUsers();

  /// pre: who is a valid user
  /// post: find users who has the most friends in common with the given user
  ///       returns the number of mutuals in score and the ids in the return
  ///       value.
  std::vector<int> suggestFriends(int who, int &score);

  /// pre: none
  /// post: return lists of users who are only friends with each other.
  std::vector<std::vector<int>> groups();

  /// pre: ownerId is a valid user id
  /// post: the posts string are returned
  std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic);

  // pre: none
  // post: gets the post given an id of a user
  Post *getPost(int messageId) {
    for (User *user : users_) {
      for (Post *post : user->getPosts()) {
        if (post->getMessageId() == messageId) {
          return post;
        }
      }
    }

    return nullptr; // return null if no post with the given messageId is found
  }

  /// pre: fname is a non-null string
  /// post: the network reads in users from the file. returns -1 if file
  ///       doesnt exists or is ill formatted
  int read_users_csv(const char *fname);

  /// pre: fname is a non-null string
  /// post: attempts to write users to the given file name creating it if needed
  ///       returns -1 if file could not be opened
  int write_users_csv(const char *fname);

  int read_posts_csv(const char *fname);
  int write_posts_csv(const char *fname);
};

#endif // !NETWORK_H
