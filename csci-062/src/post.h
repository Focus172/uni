#ifndef POST_H
#define POST_H

#include <cstdlib>
#include <set>
#include <string>

class Post {
private:
  int messageId_;
  int ownerId_;
  std::string message_;

  std::set<int> likes;

public:
  Post();
  Post(int messageId, int ownerId, std::string message, std::set<int> likes);
  Post(int messageId, int ownerId, std::string message, int likes) {

    std::set<int> tlikes;
    for (int i = 0; i < likes; i++) {
      tlikes.insert(rand());
    }

    *this = Post(messageId, ownerId, message, tlikes);
  }

  int getMessageId();
  int getOwnerId();
  std::string getMessage();

  bool is_liked(int id);
  void set_liked(int id, bool liked = true);

  virtual std::string toString();
  virtual std::string getAuthor();
  virtual bool getIsPublic();
};

class IncomingPost : public Post {
private:
  std::string author_;
  bool isPublic_;

public:
  IncomingPost();
  IncomingPost(int messageId, int ownerId, std::string message,
               std::set<int> likes, bool isPublic, std::string author);
  IncomingPost(int messageId, int ownerId, std::string message, int likes,
               bool isPublic, std::string author) {

    std::set<int> tlikes;
    for (int i = 0; i < likes; i++) {
      tlikes.insert(rand());
    }
    *this = IncomingPost(messageId, ownerId, message, tlikes, isPublic, author);
  }
  std::string toString();
  std::string getAuthor();
  bool getIsPublic();
};

#endif // POST_H
