#include "student_database.h"
#include <stdexcept>

StudentDatabase::StudentDatabase()
{}

void StudentDatabase::add_student(int student_id, int score){
    studentMap.add_student(student_id, score);
    orderedMap.add_student(student_id, score);
}

void StudentDatabase::update_score(int student_id, int new_score){
    studentMap.update_score(student_id, new_score);
    orderedMap.update_score(student_id, new_score);
}

int StudentDatabase::get_score(int student_id) const{
    return studentMap.get_score(student_id);
}

int StudentDatabase::get_student(int score) const{
    return orderedMap.get_student(score);
}

void StudentDatabase::remove_student(int student_id){
    studentMap.remove_student(student_id);
    orderedMap.remove_student(student_id);
}

int** StudentDatabase::get_top_k_students(int k){
    int** result = new int*[k];

    for (int i = 0; i < k; i++)
    {
        result[i] = new int[2];
        result[i][0] = -1;
        result[i][1] = -1;
    }

    StudentOrderedMap::Node* curr = orderedMap.getHead()->forwrd[0];

    int total = 0;

    while (curr != nullptr)
    {
        total++;
        curr = curr->forwrd[0];
    }

    curr = orderedMap.getHead()->forwrd[0];

    StudentOrderedMap::Node** arr = new StudentOrderedMap::Node*[total];

    int pos = 0;

    while (curr != nullptr)
    {
        arr[pos++] = curr;
        curr = curr->forwrd[0];
    }

    int filled = 0;

    for (int score = 100; score >= 0 && filled < k; score--)
{
    for (int i = 0; i < total && filled < k; i++)
    {
        if (arr[i]->score == score)
        {
            result[filled][0] = arr[i]->student_id;
            result[filled][1] = arr[i]->score;
            filled++;
        }
    }
}

    delete[] arr;

    return result;
}

int* StudentDatabase::range_query(int low, int high, int& count){
    StudentOrderedMap::Node* curr = orderedMap.getHead()->forwrd[0];

    count = 0;

    while (curr != nullptr)
    {
        if (curr->score >= low && curr->score <= high)
        {
            count++;
        }

        curr = curr->forwrd[0];
    }

    if (count == 0)
    {
        return nullptr;
    }

    int* result = new int[count];

    curr = orderedMap.getHead()->forwrd[0];

    StudentOrderedMap::Node** arr = new StudentOrderedMap::Node*[count];

    curr = orderedMap.getHead()->forwrd[0];

    int pos = 0;

    while (curr != nullptr)
    {
        if (curr->score >= low && curr->score <= high)
        {
            arr[pos++] = curr;
        }

        curr = curr->forwrd[0];
    }

    int idx = 0;

    for (int score = 100; score >= 0; score--){
        for (int i = 0; i < count; i++)
        {
            if (arr[i]->score == score)
            {
                result[idx++] = arr[i]->student_id;
            }
        }
    }   

    delete[] arr;

    return result;
}

int StudentDatabase::get_rank(int score) const{
    StudentOrderedMap::Node* curr = orderedMap.getHead()->forwrd[0];

    int distinctScores = 0;
    int prevScore = -1;
    bool found = false;

    while (curr != nullptr)
    {
        if (curr->score != prevScore)
        {
            distinctScores++;
            prevScore = curr->score;
        }

        if (curr->score == score)
        {
            found = true;
        }

        curr = curr->forwrd[0];
    }

    if (!found)
    {
        throw std::runtime_error("Score does not exist");
    }

    curr = orderedMap.getHead()->forwrd[0];

    int rank = distinctScores;
    prevScore = -1;

    while (curr != nullptr)
    {
        if (curr->score != prevScore)
        {
            if (curr->score == score)
            {
                return rank;
            }

            rank--;
            prevScore = curr->score;
        }

        curr = curr->forwrd[0];
    }

    throw std::runtime_error("Score does not exist");
}

