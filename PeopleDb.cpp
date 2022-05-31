#include <stdio.h>
#include <string.h>
#include <list>
#include <iterator>
#include <emscripten/bind.h>

using namespace emscripten;
using namespace std;

class PersonInfo
{
private:
    string name;
    string age;
    string country;
public:

    PersonInfo(string name, string age, string country)
    {
        this->name = name;
        this->age = age;
        this->country = country;
    }

    string getName()
    {
        return this->name;
    }

    string getAge()
    {
        return this->age;
    }

    string getCountry()
    {
        return this->country;
    }
};

class PeopleDb
{
private:
    // std::list<PersonInfo>::iterator personIterator;
public:
    vector<PersonInfo> peopleVector;

    PeopleDb()
    {
    }
    void addPerson(string name, string age, string country)
    {
        PersonInfo* person = new PersonInfo(name, age, country);
        peopleVector.push_back(*person);
    }

    int getDbSize()
    {
        return peopleVector.size();
    }

    string getPersonAtRow(int idx)
    {
        string retstr = peopleVector.at(idx).getName() + ", " + peopleVector.at(idx).getAge() + ", " + peopleVector.at(idx).getCountry();
        return retstr;
    }

    string getPersonAtRowName(int idx)
    {
        string retstr = peopleVector.at(idx).getName();
        return retstr;
    }

    string getPersonAtRowAge(int idx)
    {
        string retstr = peopleVector.at(idx).getAge();
        return retstr;
    }

    string getPersonAtRowCountry(int idx)
    {
        string retstr = peopleVector.at(idx).getCountry();
        return retstr;
    }
};

// Binding code
EMSCRIPTEN_BINDINGS(peopledb) {
  class_<PeopleDb>("PeopleDb")
    .constructor<>()
    .function("getDbSize", &PeopleDb::getDbSize)
    .function("addPerson", &PeopleDb::addPerson)
    .function("getPersonAtRow", &PeopleDb::getPersonAtRow)
    .function("getPersonAtRowName", &PeopleDb::getPersonAtRowName)
    .function("getPersonAtRowAge", &PeopleDb::getPersonAtRowAge)
    .function("getPersonAtRowCountry", &PeopleDb::getPersonAtRowCountry)
    ;
}

// Bind this code like so:
// emcc -lembind -o PeopleDb_wa_gen.js PeopleDb.cpp
