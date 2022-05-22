#include <stdio.h>
#include <string.h>
#include <list>
#include <iterator>
#include <emscripten/emscripten.h>

struct personInfo
{
    char name[20];
    char age[20];
    char country[20];
};


struct personInfo people[3];

#ifdef __cplusplus
extern "C" {
#endif

EMSCRIPTEN_KEEPALIVE void addPerson(char* name, char* age, char* country)
{
    strcpy(people[0].name, name);
    strcpy(people[0].age, age);
    strcpy(people[0].country, country);
    printf("Name: %s\n", name);
    printf("Name: %s\n", people[0].name);
}

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

EMSCRIPTEN_KEEPALIVE void getPeople(char dbPeople[][3][20])
{
    for (int i = 0; i < 1; i++)
    {
        strcpy(dbPeople[0][0], people[0].name);
    }
    for (int i = 0; i < 1; i++)
    {
        strcpy(dbPeople[0][1], people[0].age);
    }
    for (int i = 0; i < 1; i++)
    {
        strcpy(dbPeople[0][2], people[0].country);
    }
    printf("Name: %s\n", dbPeople[0][0]);
}

#ifdef __cplusplus
}
#endif
