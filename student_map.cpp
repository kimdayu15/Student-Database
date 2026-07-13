#include "student_map.h"
#include <stdexcept>

using namespace std;

StudentMap::StudentMap() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
}

int StudentMap::hashing(int student_id) const {
    return student_id % TABLE_SIZE;
}

void StudentMap::add_student(int student_id, int score) {
    if (score < 0 || score > 100) {
        throw runtime_error("Invalid score");
    }

    int index = hashing(student_id);

    Node* rn = table[index];

    while (rn != nullptr) {
        if (rn->student_id == student_id) {
            throw runtime_error("Student already exists");
        }

        rn = rn->next;
    }

    Node* newN = new Node;
    newN->student_id = student_id;
    newN->score = score;
    newN->next = table[index];

    table[index] = newN;
}

int StudentMap::get_score(int student_id) const {
    int index = hashing(student_id);

    Node* rn = table[index];

    while (rn != nullptr) {
        if (rn->student_id == student_id) {
            return rn->score;
        }

        rn = rn->next;
    }

    throw runtime_error("Student does not exist");
}

void StudentMap::update_score(int student_id, int new_score) {
    if (new_score < 0 || new_score > 100) {
        throw runtime_error("Invalid score");
    }

    int index = hashing(student_id);

    Node* rn = table[index];

    while (rn != nullptr) {
        if (rn->student_id == student_id) {
            rn->score = new_score;
            return;
        }

        rn = rn->next;
    }

    throw runtime_error("Student does not exist");
}

void StudentMap::remove_student(int student_id) {
    int index = hashing(student_id);

    Node* rn = table[index];
    Node* pre = nullptr;

    while (rn != nullptr) {
        if (rn->student_id == student_id) {

            if (pre == nullptr) {
                table[index] = rn->next;
            }
            else {
                pre->next = rn->next;
            }

            delete rn;
            return;
        }

        pre = rn;
        rn = rn->next;
    }

    throw runtime_error("Student does not exist");
}

StudentMap::~StudentMap() {
    for (int i = 0; i < TABLE_SIZE; i++) {

        Node* rn = table[i];

        while (rn != nullptr) {
            Node* temp = rn;
            rn = rn->next;
            delete temp;
        }
    }
}
