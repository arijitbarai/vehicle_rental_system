//
// Created by ariji on 3/9/2024.
//

#ifndef UNTITLED_APPLICATION_H
#define UNTITLED_APPLICATION_H

#include "vehicle.h"
#include "users.h"
#include "trip.h"
#include "database.h"
#include "error.h"
#include "string_helper.h"

#include <fstream>

extern const char DELIMETER;
class Application {
private:
    Database *db;

    void renderMenu();

    void welcome();

    void gotoXY(int x, int y) const;

    void renderAddNewVehicleMenu() const;

    void renderViewVehicleMenu() const;

    void renderEditVehicleMenu() const;

    void renderAddNewUserMenu() const;

    void renderAddNewTripMenu() const;

    void renderViewTripMenu() const;

    void renderStartTripMenu() const;

    void renderCompleteTripMenu() const;

    void showDialogue(string message, string id = " ") const;

    void clearMemory();


public:
    Application();

    void start();

};
#endif //UNTITLED_APPLICATION_H
