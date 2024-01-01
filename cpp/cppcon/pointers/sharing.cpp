#include <iostream>
#include <string>

struct Person {
    std::string nickname;
};

struct Company {
    Person *ceo;
};

struct Friends {
    Person *friend1;
};

int main() {
    Person person;
    person.nickname = "Michael";

    Person *myFakeTwinBrother;
    Company myEmployer;
    Friends myFriends;

    myFakeTwinBrother = &person;
    myEmployer.ceo = &person;
    myFriends.friend1 = &person;

    person.nickname = "Mike";

    std::cout << (*myFakeTwinBrother).nickname << std::endl;
    std::cout << myFakeTwinBrother->nickname << std::endl;
    std::cout << myEmployer.ceo->nickname << std::endl;
    std::cout << myFriends.friend1->nickname << std::endl;

    return 0;
}
