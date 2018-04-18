#include "HashCase.h"

#include "Hash/Hash.h"
#include <stdio.h>
#include <string.h>

typedef struct
{
    char* name;
    int id;
    int score;
}Student;

int hash_compare(HashKey* k1, Hash* k2)
{
    return strcmp((char*)k1, (char*)k2);
}

void HashCase()
{
    Hash* hash = Hash_Create();
    Student s1 = {"xiaoming", 1, 90};
    Student s2 = {"xiaohong", 2, 91};
    Student s3 = {"xiaodong", 3, 92};
    Student s4 = {"xiaohan", 4, 93};
    Student s5 = {"xiaofei", 5, 94};

    Hash_Add(hash, s1.name, &s1, hash_compare);
    Hash_Add(hash, s2.name, &s2, hash_compare);
    Hash_Add(hash, s3.name, &s3, hash_compare);
    Hash_Add(hash, s4.name, &s4, hash_compare);
    Hash_Add(hash, s5.name, &s5, hash_compare);

    printf("hash count = %d\n", Hash_Count(hash));

    Student* ss = (Student*)Hash_Get(hash, "xiaofei", hash_compare);

    printf("name = %s\n", ss->name);
    printf("id = %d\n", ss->id);
    printf("score = %d\n", ss->score);

    printf("hash count = %d\n", Hash_Count(hash));
    Hash_Destroy(hash);
}
