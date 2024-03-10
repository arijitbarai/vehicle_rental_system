//
// Created by ariji on 2/25/2024.
//

#ifndef APPLICATION_DATABASE_H
#define APPLICATION_DATABASE_H

#include "vehicle.h"
#include "users.h"
#include "trip.h"
#include "table.cpp"
#include "error.cpp"

using namespace std;

class Database {
private:
    Table<Vehicle> * vehicleTable;
    Table<User> * userTable;
    Table<Trip> * tripTable;

    void fetchAllVechicles() throw(IoError, MemoryError);
    void fetchAllUsers() throw(IoError, MemoryError);
    void fetchAllTrips() throw(IoError,MemoryError);
    void cleanUp();

public:
    Database() throw(MemoryError,IoError);
    ~Database();

    const Table<Vehicle> * const getVehicleRef() const;
    const Table<User> * const getUserRef() const;
    const Table<Trip> * const getTripRef() const;

    const Vehicle*  const getVehicle(string registrationNO) const throw(NoSuchRecordError);
    const User* const getUser(string contactNo) const throw(NoSuchRecordError);

    const vector<const Vehicle*> getVehicle(Date startDate, Date endDate, VehicleType type) const;

    template<class T> void addNewRecord(T*record) throw (IoError,MemoryError);

    template<class T> void updateRecord(T*record) throw(IoError,NoSuchRecordError);
};

#endif //APPLICATION_DATABASE_H
