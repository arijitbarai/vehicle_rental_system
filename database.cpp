//
// Created by ariji on 2/25/2024.
//
#ifndef database_cpp
#define database_cpp

#include "database.h"
#include "string_helper.h"

#include <iostream>

using namespace std;

const char DELIMETER = ';';

Database::Database() throw(MemoryError, IoError) {
    try{
        this -> vehicleTable = new Table<Vehicle>("vehicles.txt");
        this -> userTable = new Table<User>("users.txt");
        this -> tripTable = new Table<Trip>("trips.txt");

        this -> fetchAllVechicles();
        this -> fetchAllUsers();
        this -> fetchAllTrips();
    }

    catch (...) {
        throw;
    }
}

void Database ::fetchAllVechicles() throw(IoError, MemoryError) {
    this -> vehicleTable -> fileStream.open(this-> vehicleTable -> fileName);

    if (!this -> vehicleTable -> fileStream){
        throw IoError();
    }

    for (string line; getline(this -> vehicleTable ->fileStream, line);) {
        vector<string> components = split(line, DELIMETER);

        auto recordId                       = stol(components[0]);
        auto registrationNumber            = components[1];
        auto type                                = VehicleType (stol(components[2]));
        auto seats                           = stoi(components[3]);
        auto companyName                   = components[4];
        auto pricePerKm                   = stod(components[5]);
        auto PUCExpirationDate                    = Date(components[6]);

        // fix this line
      Storable * record = new Vehicle(registrationNumber, type, seats, companyName, pricePerKm, PUCExpirationDate, recordId);

        if (!record){
            throw MemoryError();
        }

        this -> vehicleTable -> records ->push_back(record);
    }
    this -> vehicleTable -> fileStream.close();
}

void Database ::fetchAllUsers() throw(IoError, MemoryError) {
    this -> userTable -> fileStream.open(this -> userTable -> fileName);

    if (!this -> userTable -> fileStream){
        throw IoError();
    }
    for (string  line; getline(this -> userTable -> fileStream,line);) {
        vector<string> components = split(line, DELIMETER);

        auto recordId            = stoi(components[0]);
        auto name              = components[1];
        auto contact           = components[2];
        auto email              = components[3];

        Storable * record = new User(name, contact, email, recordId);

        if (!recordId){
            throw MemoeyError();
        }
        this -> userTable -> records ->push_back(record);
    }
    this -> userTable -> fileStream.close();
}

void Database ::fetchAllTrips() throw(IoError, MemoeyError) {
    this -> tripTable -> fileStream.open(this-> tripTable -> fileName);

    if (!this -> tripTable -> fileStream){
        throw IoError();
    }

    for (string line; getline(this -> tripTable -> fileStream, line);) {
        vector<string> components = split(line, DELIMETER);

        try {
            auto recordId                      = stoi(components[0]);
            auto vehiclePtr               = this -> vehicleTable ->getReferenceOfRecordForId(stoi(components[1]));
            auto userPtr                    = this -> userTable ->getReferenceOfRecordForId(stoi(components[2]));
            auto startDate                         = Date (components[3]);
            auto endDate                           = Date (components[4]);
            auto startReading                = stol(components[5]);
            auto endReading                  = stol(components[6]);
            auto fare                      = stod(components[7]);
            auto isCompleted                      = components[8] == "0" ? false : true;

            Storable * record = new Trip(vehiclePtr, userPtr, startDate, endDate, startReading, endReading, recordId, fare, isCompleted);
            if (!record){
                throw MemoeyError();
            }
            this -> tripTable -> records -> push_back(record);
        }
        catch (...) {

        }
    }
    this -> tripTable -> fileStream.close();
}

const Vehicle * const Database ::getVehicle(string registrationNo) const throw(NoSuchRecordError) {
    for (auto & record: *this -> vehicleTable -> records) {
        Vehicle * vehicle = dynamic_cast<Vehicle*>(record);
        if (vehicle){
            if (vehicle -> getRegistrationNumber() == registrationNo){
                return vehicle;
            }
        }
    }
    throw NoSuchRecordError();
}

const User * const Database ::getUser(std::string contactNo) const throw(NoSuchRecordError) {
    for (auto & record: *this -> userTable -> records) {
        User * user = dynamic_cast<User*>(record);
        if (user ){
            if (user -> getContact() == contactNo){
                return user;
            }
        }
    }
    throw NoSuchRecordError();
}

const vector<const Vehicle*> Database ::getVehicle(Date startDate, Date endDate, VehicleType type) const {
    vector<const Vehicle*>  vehicles = vector<const Vehicle*>();

    for (auto & vrecord: *this -> vehicleTable -> records) {
        Vehicle * vehicle = dynamic_cast<Vehicle*>(vrecord);

        if (vehicle && vehicle -> getVehicleType() == type){
            bool tripFound = false;

            for (auto & trecord: this -> tripTable -> records) {
                Trip * trip = dynamic_cast<Trip*>(trecord);

                if (
                        trip &&
                        !trip -> isCompleted() &&
                        trip -> getVehicle().getRecordId() == vehicle -> getRecordId() &&
                        !(trip -> getStartDate() <= startDate && trip -> getEndDate() <= startDate)
                        ){
                    tripFound = true;
                    break;
                }
            }
            if (!tripFound){
                vehicles.push_back(vehicle);
            }
        }
    }
    return vehicles;
}

void Database ::cleanUp() {
    delete this -> vehicleTable;
    delete this -> userTable;
    delete this -> tripTable;
}

Database :: ~Database(){
    this -> cleanUp();
}

const Table<Vehicle> *const Database ::getVehicleRef() const {
    return this -> vehicleTable;
}

const Table<User> *const Database ::getUserRef() const {
    return this -> userTable;
}

const Table<Trip> *const Database ::getTripRef() const{
    return this -> tripTable;
}


#endif