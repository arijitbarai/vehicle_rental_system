#ifndef storable_cpp
#define storable_cpp
#include "serializable.cpp"



using namespace std;


class Storable : public Serializable{
protected:
    long recordId;
public:
    Storable(long recordId){ this ->recordId = recordId;};
    long getRecordId () const {return this->recordId;};

    virtual void setDataForm(Storable * s) = 0;

    template<class T> friend class Table;
    friend class  Database;
};
#endif