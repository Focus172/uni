#ifndef USER_H
#define USER_H

#include <string>
#include <set>

class User {
private:
    int id_;
    std::string name_;
    int year_;
    int zip_;
    std::set<int> friends_;

public:
    User();
    User(int id, std::string name, int year, int zip, std::set<int> friends);

    void addFriend(int id);
    void deleteFriend(int id);

    int getId();
    std::string getName();
    int getYear();
    int getZip();
    std::set<int> &getFriends();
};

#endif // USER_H
