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
    int uniqueId;
    string name;
    string age;
    string country;
public:
    PersonInfo(int uniqueId, string name, string age, string country)
    {
        this->uniqueId = uniqueId;
        this->name = name;
        this->age = age;
        this->country = country;
    }

    int getUniqueId()
    {
        return this->uniqueId;
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

    void setName(string newName)
    {
        this->name = newName;
    }

    void setAge(string newAge)
    {
        this->age = newAge;
    }

    void setCountry(string newCountry)
    {
        this->country = newCountry;
    }
};

class PeopleDb
{
private:
    int nextUniqueId = 0;
public:
    vector<PersonInfo> peopleVector;

    PeopleDb()
    {
    }
    int addPerson(string name, string age, string country)
    {
        // Assign this person a unique Id
        int newPersonsUid = nextUniqueId;
        PersonInfo* person = new PersonInfo(newPersonsUid, name, age, country);
        peopleVector.push_back(*person);
        nextUniqueId++;
        return newPersonsUid;
    }


    int deletePersonWithUid(string uid)
    {
        int personDeleted = -1;
        int uidInt = std::stoi(uid);
        for (int i=0; i < peopleVector.size(); i++)
        {
            if (peopleVector.at(i).getUniqueId() == uidInt)
            {
                peopleVector.erase(peopleVector.begin()+i);
                personDeleted = 1;
            }
        }
        return personDeleted;
    }


    int updatePersonWithUid(string uid, string updatedName, string updatedAge, string updatedCountry)
    {
        int personUpdated = -1;
        int uidInt = std::stoi(uid);
        for (int i=0; i < peopleVector.size(); i++)
        {
            if (peopleVector.at(i).getUniqueId() == uidInt)
            {
                if (!updatedName.empty())
                {
                    peopleVector.at(i).setName(updatedName);
                    personUpdated = 1;
                }
                if (!updatedAge.empty())
                {
                    peopleVector.at(i).setAge(updatedAge);
                    personUpdated = 1;
                }
                if (!updatedCountry.empty())
                {
                    peopleVector.at(i).setCountry(updatedCountry);
                    personUpdated = 1;
                }
            }
        }
        return personUpdated;
    }

    int getDbSize()
    {
        return peopleVector.size();
    }

    string getPersonWithUid(string uid)
    {
        string retstr = "Could not find person with this UID";
        int uidInt = std::stoi(uid);
        for (int i=0; i < peopleVector.size(); i++)
        {
            if (peopleVector.at(i).getUniqueId() == uidInt)
            {
                retstr = std::to_string(peopleVector.at(i).getUniqueId()) + ", " + peopleVector.at(i).getName() + ", " + peopleVector.at(i).getAge() + ", " + peopleVector.at(i).getCountry();;
            }
        }
        return retstr;
    }

    string getPersonAtRowUid(int idx)
    {
        string retstr = std::to_string(peopleVector.at(idx).getUniqueId());
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
    .function("addPerson", &PeopleDb::addPerson)
    .function("deletePersonWithUid", &PeopleDb::deletePersonWithUid)
    .function("updatePersonWithUid", &PeopleDb::updatePersonWithUid)
    .function("getPersonWithUid", &PeopleDb::getPersonWithUid)
    .function("getPersonAtRowUid", &PeopleDb::getPersonAtRowUid)
    .function("getPersonAtRowName", &PeopleDb::getPersonAtRowName)
    .function("getPersonAtRowAge", &PeopleDb::getPersonAtRowAge)
    .function("getPersonAtRowCountry", &PeopleDb::getPersonAtRowCountry)
    ;
}

// Bind this code like so:
// emcc -lembind -o PeopleDb_wa_gen.js PeopleDb.cpp
