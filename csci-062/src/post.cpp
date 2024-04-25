#include "post.h"
#include <sstream>
#include <string>

Post::Post() {
  // this is not how i would do this but whatever
  this->likes_ = 0;
  this->message_ = "";
  this->messageId_ = 0;
  this->ownerId_ = 0;
}

Post::Post(int messageId, int ownerId, std::string message, int likes) {
  this->likes_ = likes;
  this->message_ = message;
  this->messageId_ = messageId;
  this->ownerId_ = ownerId;
}
std::string Post::toString() {
  std::stringstream buf;
  buf << this->message_ << " Liked by " << likes_ << " people.";
  return buf.str();
}

// ## Getters

int Post::getMessageId() { return this->messageId_; }
int Post::getOwnerId() { return this->ownerId_; }
std::string Post::getMessage() { return this->message_; }
int Post::getLikes() { return this->likes_; }

// ## Functions to be overwritten

std::string Post::getAuthor() { return ""; }
bool Post::getIsPublic() { return true; }

// ------------------ IPOST ---------------------------

IncomingPost::IncomingPost() : Post::Post() {}

IncomingPost::IncomingPost(int messageId, int ownerId, std::string message,
                           int likes, bool isPublic, std::string author)
    : Post(messageId, ownerId, message, likes) {
  this->isPublic_ = isPublic;
  this->author_ = author;
}

std::string IncomingPost::toString() {
  std::stringstream buf;
  buf << this->author_ << " wrote";
  if (!this->getIsPublic()) {
    buf << "(private)";
  }
  buf << ": " << this->Post::toString();

  return buf.str();
}
std::string IncomingPost::getAuthor() { return this->author_; }
bool IncomingPost::getIsPublic() { return this->isPublic_; }
