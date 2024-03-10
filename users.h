//
// Created by ariji on 2/21/2024.
//

#ifndef APPLICATION_USERS_H
#define APPLICATION_USERS_H
#include "storable.cpp"

#include <string>

using namespace std;

class User : public Storable{
private:
    string name;
    string contact;
    string email;

public:
    User(string name, string contact, string email, long recordId = 0);

    string getName() const;
    string  getContact() const;
    string  getEmail() const;

    void setName(string newName);
    void setContact(string newContact);
    void setEmail(string newEmail);
    void display() const;
    string  toString() const;
    void setDataFrom(Storable * s);
};
#endif //APPLICATION_USERS_H
