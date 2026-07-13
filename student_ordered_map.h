#ifndef STUDENT_ORDERED_MAP_H
#define STUDENT_ORDERED_MAP_H

class StudentOrderedMap {
public:
    static const int MAX_LEVEL = 16;

    struct Node {
        int student_id;
        int score;

        Node** forwrd;
        int level;
    };

    StudentOrderedMap();

    void add_student(int student_id, int score);

    void update_score(int student_id, int new_score);

    int get_student(int score) const;

    void remove_student(int student_id);

    Node* getHead() const;

    ~StudentOrderedMap();

private:
    Node* head;
    int currLevel;

    int randomLevel();

    Node* findById(int student_id) const;
};

#endif