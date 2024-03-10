//
// Created by ariji on 2/21/2024.
//
#include "users.h"
#include "string_helper.h"

#include <iostream>

using namespace std;

const char *const DELIMITER = ';';

User ::User(std::string name, std::string contact, std::string email, long recordId) :Storable(recordId){

    this -> name = name;
    this -> contact = contact;
    this -> email = email;
}

string User ::getName() const {
    return this -> name;
}
string User ::getContact() const {
    return this ->contact;
}
string User ::getEmail() const {
    return this -> email;
}

void User ::setName(std::string newName) {
    this -> name =newName;
}
void User::setContact(std::string newContact) {
    this -> contact = newContact;
}
void User::setEmail(std::string newEmail) {
    this ->email = newEmail;
}
void User ::display() const {
    cout << "User Details : "       << endl;
    cout << "Name : "               << this -> name           << endl;
    cout << "Contact : "            << this -> contact        << endl;
    cout << "Email id : "           << this -> email          << endl;

}

string User ::toString() const {
    stringstream ss;
    ss << recordId << DELIMITER
       << name << DELIMITER
       << contact << DELIMITER
       << email;
    return ss.str();
}

void User ::setDataFrom(Storable *s) {
    User * user = dynamic_cast<User*>(s);
    if (user){
        this -> contact = user ->contact;
        this -> name = user -> name;
        this -> email = user -> email;
    }
}