#include "post.h"

Post::Post() : messageId_(0), ownerId_(0), message_("") {}

Post::Post(int messageId, int ownerId, std::string message, std::set<int> likes)
    : messageId_(messageId), ownerId_(ownerId), message_(message),
      liked(likes) {}

std::string Post::toString() {
  return message_;
  // + " Liked by " + std::to_string(likes_) + " people.";
}

int Post::getMessageId() { return messageId_; }

int Post::getOwnerId() { return ownerId_; }

std::string Post::getMessage() { return message_; }

std::string Post::getAuthor() { return ""; }

bool Post::getIsPublic() { return true; }

IncomingPost::IncomingPost() : Post(), isPublic_(true), author_("") {}

IncomingPost::IncomingPost(int messageId, int ownerId, std::string message,
                           int likes, bool isPublic, std::string author)
    : Post(messageId, ownerId, message, likes), isPublic_(isPublic),
      author_(author) {}

std::string IncomingPost::toString() {
  std::string final = author_ + " wrote";
  if (!isPublic_) {
    final += "(private)";
  }
  final += ": " + Post::toString();

  return final;
}

std::string IncomingPost::getAuthor() { return author_; }

bool IncomingPost::getIsPublic() { return isPublic_; }
