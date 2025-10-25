#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int16_t age;
    char name[30];
    double height;
} Person;

void printPerson(const Person *p) {

    printf("Person: %s\t (%d of age with height %.1lf cm)\n", p->name, p->age, p->height);
}

int main() {

    Person person1 = {.age=55, .name = "Samuel", .height = 190 };
    printPerson(&person1);

    Person person2 = {} ;
    person2.age = 15;
    strncpy(person2.name, "Libby", sizeof(person2.name)); // <string.h>
    person2.height = 165;
    printPerson(&person2);

    Person person3;
    // copy using memcpy
    memcpy(&person3, &person1, sizeof(person1));
    printPerson(&person3);

    // use copy assignment operator
    Person person4 = person2;
    printPerson(&person4);

    return 0;
}
