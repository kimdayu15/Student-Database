#ifndef STUDENT_DATABASE_H
#define STUDENT_DATABASE_H

#include "student_map.h"
#include "student_ordered_map.h"

class StudentDatabase {// do not change this line
public:

    StudentDatabase();

    void add_student(int student_id, int score);

    void update_score(int student_id, int new_score);

    int get_score(int student_id) const;

    int get_student(int score) const;

    void remove_student(int student_id);

    int** get_top_k_students(int k);

    int get_rank(int score) const;

    int* range_query(int low, int high, int& count);

private:
    StudentMap studentMap;
    StudentOrderedMap orderedMap;
};

#endif