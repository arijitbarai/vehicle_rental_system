#include "application.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    Application * application = new Application();
    application -> start();
}