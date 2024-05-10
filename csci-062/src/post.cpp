#include "post.h"
#include <sstream>
#include <string>

Post::Post() {
  // this is not how i would do this but whatever
  this->likes = {};
  this->message_ = "";
  this->messageId_ = 0;
  this->ownerId_ = 0;
}

Post::Post(int messageId, int ownerId, std::string message,
           std::set<int> likes) {
  this->likes = likes;
  this->message_ = message;
  this->messageId_ = messageId;
  this->ownerId_ = ownerId;
}
std::string Post::toString() {
  std::stringstream buf;
  buf << this->message_ << " Liked by " << likes.size() << " people.";
  return buf.str();
}

// ## Getters

int Post::getMessageId() { return this->messageId_; }
int Post::getOwnerId() { return this->ownerId_; }
std::string Post::getMessage() { return this->message_; }
bool Post::is_liked(int id) { return this->likes.find(id) != this->likes.end(); }
void Post::set_liked(int id, bool liked) {
  if (liked) this->likes.insert(id);
  else this->likes.erase(id);
}

// ## Functions to be overwritten

std::string Post::getAuthor() { return ""; }
bool Post::getIsPublic() { return true; }

// ------------------ IPOST ---------------------------

IncomingPost::IncomingPost() : Post::Post() {}

IncomingPost::IncomingPost(int messageId, int ownerId, std::string message,
                           std::set<int> likes, bool isPublic, std::string author)
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
