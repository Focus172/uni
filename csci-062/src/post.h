#ifndef POST_H
#define POST_H

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
  std::string toString();
  std::string getAuthor();
  bool getIsPublic();
};

#endif // POST_H
