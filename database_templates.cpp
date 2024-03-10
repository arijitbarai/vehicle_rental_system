//
// Created by ariji on 3/9/2024.
//
#include "database.h"

template<class T> void Database ::addNewRecord(T *record) throw(IoError, MemoryError) {
    try{
        Vehicle * v = dynamic_cast<Vehicle*>(record);
        if (v){
            auto saveRecord = this -> vehicleTable -> addNewRecord(*v);
            record -> recordId = saveRecord -> recordId;
            return;
        }
        User* u = dynamic_cast<User*>(record);
        if (u){
            auto saveRecord = this -> userTable -> addNewRecord(*u);
            record -> recordId = saveRecord -> recordId;
            return;
        }
        Trip* t = dynamic_cast<Trip*>(record);
        if (t){
            auto saveRecord = this -> tripTable -> addNewRecord(*t);
            record -> recordId = saveRecord -> recordId;
            return;
        }
    }
    catch (MemoryError error){
        throw;
    }
    catch (IoError error){
        throw;
    }
}

template<class T> void Database ::updateRecord(T *record) throw(IoError, NoSuchRecordError) {
    try{
        Vehicle * v = dynamic_cast<Vehicle*>(record);
        if (v){
            this -> vehicleTable -> updateRecord(*v);
            return;
        }
        User* u = dynamic_cast<User*>(record);
        if (u){
            this -> userTable -> updateRecord(*u);
            return;
        }
        Trip* t = dynamic_cast<Trip*>(record);
        if (t){
            this -> tripTable -> updateRecord(*t);
            return;
        }
    }
    catch (NoSuchRecordError error){
        throw;
    }
    catch (IoError error){
        throw;
    }
}