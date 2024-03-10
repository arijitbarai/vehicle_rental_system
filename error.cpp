#ifndef error_cpp
#define error_cpp

#include <string>

using namespace std;

class Error{
private:
    string message;

public:
    Error(string message) { this->message = message;};
    string getMessage()const{ return this -> message;}
};

class NoSuchRecordError : public Error{
public:
    NoSuchRecordError() : Error("No Such Error Found") {};
};

class IoError: public Error{
public:
    IoError() : Error("I/O Error Could not open or process file make sure 'vehicle.txt', 'trips.txt', 'users.txt' file exiets in this directory"){};
};

class MemoryError : public Error{
public:
    MemoryError(): Error("System out of memory") {};
};
#endif