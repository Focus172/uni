#pragma once

#include <ctime>
#include <set>
#include <string>

class Post {
public:
  // CONSTRUCTORS

  // pre: none
  // post: initializes a post object
  Post();

  // pre: messageId, ownerId, and likes must be nonnegative
  // post: initializes a post object with parameters
  Post(int messageId, int ownerId, std::string message, int like) {
    std::set<int> likes;
    for (int i = 0; i < like; i++) {
      int id = rand() % 100;
      likes.insert(id);
    }
    *this = Post(messageId, ownerId, message, likes);
  }
  Post(int messageId, int ownerId, std::string message, std::set<int> likes);

  // ACCESSOR FUNCTIONS

  // pre: none
  // post: gets the messaged id
  int getMessageId();

  // pre: none
  // post: gets the owner id
  int getOwnerId();

  // pre: none
  // post: gets the message of the post
  std::string getMessage();

  // pre: none
  // post: gets the number of likes
  std::set<int> getLiked() { return liked; }

  // pre: none
  // post: gets the author
  virtual std::string getAuthor();

  // pre: none
  // post: gets if private posts should be displayed
  virtual bool getIsPublic();

  // MODIFICATION MEMBER FUNCTIONS

  // pre: none
  // post: returns a message containing information about the post
  virtual std::string toString();

  /// Attempt to like this post
  void like(int id) { liked.insert(id); }

  std::string getHumanDate() { return std::asctime(std::localtime(&date)); }
  std::time_t getDate() { return date; }

private:
  int messageId_;
  int ownerId_;
  std::string message_;
  // int likes_;
  /// Set of user IDs that have liked this post
  std::set<int> liked;

  /// Date of the post in unix time
  std::time_t date;
};

class IncomingPost : public Post {
public:
  // CONSTRUCTORS

  // pre: none
  // post: initializes an incomingpost object
  IncomingPost();

  // pre: messageId, ownerId, and likes must be nonnegative
  // post: initializes an incomingpost object with parameters
  IncomingPost(int messageId, int ownerId, std::string message, int likes,
               bool isPublic, std::string author);

  // ACCESSOR FUNCTIONS

  // pre: none
  // post: gets the author of the incoming post
  virtual std::string getAuthor();

  // pre: none
  // post: gets if incoming post should be public or not
  virtual bool getIsPublic();

  // MODIFICATION MEMBER FUNCTIONS

  // pre: none
  // post: returns a message containing information about the incoming post
  virtual std::string toString();

private:
  std::string author_;
  bool isPublic_;
};
