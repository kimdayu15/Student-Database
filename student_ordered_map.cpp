#include "student_ordered_map.h"
#include <cstdlib>
#include <stdexcept>


StudentOrderedMap::StudentOrderedMap() {
    currLevel = 0;

    head = new Node;
    head->student_id = -1;
    head->score = -1;
    head->level = MAX_LEVEL;

    head->forwrd = new Node*[MAX_LEVEL + 1];

    for (int i = 0; i <= MAX_LEVEL; i++) {
        head->forwrd[i] = nullptr;
    }
}

void StudentOrderedMap::add_student(int student_id, int score){
    if (score < 0 || score > 100)
    {
        throw std::runtime_error("Invalid score");
    }

    Node* check = head->forwrd[0];

    while (check != nullptr)
    {
        if (check->student_id == student_id)
        {
            throw std::runtime_error("Student already exists");
        }

        check = check->forwrd[0];
    }

    Node* update[MAX_LEVEL + 1];

    Node* curr = head;

    for (int i = currLevel; i >= 0; i--)
    {
        while (
            curr->forwrd[i] != nullptr &&
            (
                curr->forwrd[i]->score < score ||
                (
                    curr->forwrd[i]->score == score &&
                    curr->forwrd[i]->student_id < student_id
                )
            )
        )
        {
            curr = curr->forwrd[i];
        }

        update[i] = curr;
    }

    int lvl = randomLevel();

    if (lvl > currLevel)
    {
        for (int i = currLevel + 1; i <= lvl; i++)
        {
            update[i] = head;
        }

        currLevel = lvl;
    }

    Node* newNode = new Node;

    newNode->student_id = student_id;
    newNode->score = score;
    newNode->level = lvl;

    newNode->forwrd = new Node*[lvl + 1];

    for (int i = 0; i <= lvl; i++)
    {
        newNode->forwrd[i] = update[i]->forwrd[i];
        update[i]->forwrd[i] = newNode;
    }
}

StudentOrderedMap::Node* StudentOrderedMap::findById(int student_id) const{
    Node* curr = head->forwrd[0];

    while (curr != nullptr)
    {
        if (curr->student_id == student_id)
        {
            return curr;
        }

        curr = curr->forwrd[0];
    }

    return nullptr;
}

void StudentOrderedMap::update_score(int student_id, int new_score){
    if (new_score < 0 || new_score > 100)
    {
        throw std::runtime_error("Invalid score");
    }

    Node* target = findById(student_id);

    if (target == nullptr)
    {
        throw std::runtime_error("Student does not exist");
    }

    remove_student(student_id);

    add_student(student_id, new_score);
}

int StudentOrderedMap::get_student(int score) const{
    Node* curr = head->forwrd[0];

    while (curr != nullptr)
    {
        if (curr->score == score)
        {
            return curr->student_id;
        }

        if (curr->score > score)
        {
            break;
        }

        curr = curr->forwrd[0];
    }

    throw std::runtime_error("Score does not exist");
}

void StudentOrderedMap::remove_student(int student_id){
    Node* target = findById(student_id);

    if (target == nullptr)
    {
        throw std::runtime_error("Student does not exist");
    }

    Node* update[MAX_LEVEL + 1];
    Node* curr = head;

    for (int i = currLevel; i >= 0; i--)
    {
        while (
            curr->forwrd[i] != nullptr &&
            (
                curr->forwrd[i]->score < target->score ||
                (
                    curr->forwrd[i]->score == target->score &&
                    curr->forwrd[i]->student_id < target->student_id
                )
            )
        )
        {
            curr = curr->forwrd[i];
        }

        update[i] = curr;
    }

    for (int i = 0; i <= target->level; i++)
    {
        if (update[i]->forwrd[i] == target)
        {
            update[i]->forwrd[i] = target->forwrd[i];
        }
    }

    delete[] target->forwrd;
    delete target;

    while (currLevel > 0 && head->forwrd[currLevel] == nullptr)
    {
        currLevel--;
    }
}   

StudentOrderedMap::~StudentOrderedMap(){
    Node* curr = head->forwrd[0];

    while (curr != nullptr)
    {
        Node* temp = curr;
        curr = curr->forwrd[0];

        delete[] temp->forwrd;
        delete temp;
    }

    delete[] head->forwrd;
    delete head;
}

int StudentOrderedMap::randomLevel() {
    int lvl = 0;

    while ((rand() % 2) && lvl < MAX_LEVEL) {
        lvl++;
    }

    return lvl;
}

StudentOrderedMap::Node* StudentOrderedMap::getHead() const{
    return head;
}
