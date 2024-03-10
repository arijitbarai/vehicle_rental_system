//
// Created by ariji on 2/22/2024.
//
#include "table.h"

#include <iostream>

using namespace std;

template<class T> Table<T> ::Table(std::string fileName) throw(MemoryError) {
    this -> fileName = fileName;
    this -> records = new vector<Storable *>();
    if (!this -> records){
        throw MemoryError();
    }
}

template<class T> long Table<T> ::getNextRecordId() const {} const{
    return this -> records-> size()+1;
}

template<class T> const T * const Table<T> ::addNewrecord(T record) throw(MemoryError, IoError) {
    T * newRecord = new T(record);
    if (!newRecord){
        throw new MemoyError();
    }
     newRecord -> recordId =  this -> getNextRecordId();
    this -> records -> push_back(newRecord);

    try{
        this -> writeTofile();
    }

    catch (IoError error){
        this -> records -> pop_back();
        delete newRecord;
        throw ;
    }
    return newRecord;
}

template <class T> void Table<T> ::updateRecord(T updatedRecord) throw(IoError, NoSuchRecordError) {
    for (auto & record : *this -> records) {
        if (record -> getRecordId() == updatedRecord.getRecordId()){
            T * pointerToRecord = dynamic_cast<T*> (record);

            if (pointerToRecord){
                T oldRecord = T(*pointerToRecord);
                record -> setDataForm(&updatedRecord);

                try {
                    this -> writeTofile();
                    return;
                }
                catch (IoError error) {
                    record -> setDataForm(&oldRecord);
                    throw ;
                }
            }
        }

    }
    throw NoSuchRecordError();
}

template<class T> void Table<T> ::writeTofile() throw(IoError) {
    this -> fileStream.open(fileName, ios::out | ios :: trunc);

    if (!this -> fileStream){
        throw IoError();
    }

    for (auto & record : *records) {
        fileStream << record -> toString() << endl;
    }
    this -> fileStream.close();
}

template<class T> const T * const Table<T> ::getRecordForId(long recordId) const throw(NoSuchRecordError) {
    try {
        return this ->getReferenceOfRecordForId(recordId);
    }
    catch (NoSuchRecordError error) {
        throw;
    }
}

template<class T> T * Table<T> ::getReferenceOfRecordForId(long recordId) const throw(NOSuchRecordError) {
    for (auto & record : *records) {
        if (record -> getRecordId() == recordId){
            return dynamic_cast<T*>(record);
        }
    }
    throw NoSuchRecordError();
}

template<class T>Table<T> :: ~Table(){
    for (auto & record : *this -> records) {
        delete dynamic_cast<T*>(record);
    }

    this -> records -> clear();
    this -> records ->  shrink_to_fit();
    delete this -> records;
}