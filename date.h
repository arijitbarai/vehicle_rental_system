//
// Created by ariji on 2/21/2024.
//

#ifndef APPLICATION_DATE_H
#define APPLICATION_DATE_H

#include "storable.cpp"

#include <ctime>
#include <string>

using namespace std;

typedef struct Date : Serializable{
private:
    struct tm date;
    bool empty;

public:
    Date (string date);

    Date( );

    Date operator + (int days);

    bool operator > (Date date) const;

    bool operator >= (Date date) const;

    bool operator < (Date date) const;

    bool operator <= (Date date) const;

    bool isEmpty() const;

    string  toString() const;
} Date;

#endif //APPLICATION_DATE_H
