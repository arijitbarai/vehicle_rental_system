//
// Created by ariji on 2/22/2024.
//

#ifndef APPLICATION_TABLE_H
#define APPLICATION_TABLE_H

#include "storable.cpp"
#include "error.h"

#include <vector>
#include <string>
#include <fstream>

using namespace std;

template<class T> class Table {
private:
    string fileName;
    fstream fileStream;

    vector<Storable *> * records = NULL;

    T * getReferenceOfRecordForId (long  recordId) const throw(NosuchRecordError );

    void writeTofile() throw (IoError);

    const T * const addNewRecord (T data) throw (MemoryError, IoError);

    void  updateRecord( T updatedRecord) throw (IoError, NoSuchRecordError);

public:
    Table(string fileName) throw(MemoryError);
    ~Table();
    long getNextRecordId() const;

    const T * const getRecordForId(long recordId) const throw(NoSuchRecordError);

    friend class Database;
};
#endif //APPLICATION_TABLE_H
