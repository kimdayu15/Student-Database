#ifndef STUDENT_MAP_H
#define STUDENT_MAP_H

#include <stdexcept>
using namespace std;

class StudentMap { // do not change this line
public:
    struct Node { // do not change this line
        int student_id; // do not change this line
        int score; // do not change this line

        Node* next;
    };

    static const int TABLE_SIZE = 1000; // do not change this line

    StudentMap();

    void add_student(int student_id, int score);

    void update_score(int student_id, int new_score);

    int get_score(int student_id) const;

    void remove_student(int student_id);

    ~StudentMap();

private:
    Node* table[TABLE_SIZE];

    int hashing(int student_id) const;
};

#endif