#include "student_database.h"
#include <iostream>
#include <exception>

using namespace std;

// Function to print the top k students by score
void print_top_k_students(int** top_students, int k) {
    cout << "Top " << k << " students by score:" << endl;
    for (int i = 0; i < k; i++) {
        if (top_students[i][0] != -1) {
            cout << "Student ID: " << top_students[i][0] << ", Score: " << top_students[i][1] << endl;
        } else {
            cout << "No student data available for rank " << i + 1 << "." << endl;
        }
    }
}

// Function to print range query result
void print_range_query_result(int* student_ids, int count, const StudentDatabase& db) {
    cout << "Range query result count: " << count << endl;
    for (int i = 0; i < count; ++i) {
        cout << "Student ID: " << student_ids[i] 
                  << ", Score: " << db.get_score(student_ids[i]) << endl;
    }
}

// Test function for StudentMap
void test_student_map() {
    StudentMap map;
    int id1 = 20261234;
    int id2 = 20264321;

    map.add_student(id1, 95);
    map.add_student(id2, 88);

    cout << "Testing StudentMap:" << endl;
    try {
        cout << "Score of " << id1 << ": " << map.get_score(id1) << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    map.update_score(id1, 98);
    try {
        cout << "Updated Score of " << id1 << ": " << map.get_score(id1) << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    map.remove_student(id2);
    try {
        map.get_score(id2);
    } catch (const exception& e) {
        cerr << "Expected exception: " << e.what() << endl;
    }
}

// Test function for StudentOrderedMap

void test_student_ordered_map() {
    StudentOrderedMap ordered_map;
    int id1 = 20261234;
    int id2 = 20264321;
    int id3 = 20265678;
    int id4 = 20266666;

    ordered_map.add_student(id1, 95);
    ordered_map.add_student(id2, 88);
    ordered_map.add_student(id3, 97);
    ordered_map.add_student(id4, 88);

    cout << "\nTesting StudentOrderedMap:" << endl;
    try {
        cout << "Student with score 88: ID " << ordered_map.get_student(88) << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    ordered_map.update_score(id1, 99);
    try {
        cout << "Updated ID " << id1 << " to score 99" << endl;
        cout << "Student with score 99: ID " << ordered_map.get_student(99) << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    ordered_map.remove_student(id2);
    try {
        int student_id = ordered_map.get_student(88);
        cout << "Student with score 88 after removal: ID " << student_id << endl;
    } catch (const exception& e) {
        cerr << "Expected exception: " << e.what() << endl;
    }
}
void test_student_database() {
    StudentDatabase db;

    int id1 = 20261234; // Student with initial score 95, updated to 99
    int id2 = 20264321; // Student with score 88
    int id3 = 20265678; // Student with score 97
    int id4 = 20269999; // Student with score 90
    int id5 = 20261111; // Student with score 90
    int id6 = 20262222; // Student with score 90

    // Adding students
    db.add_student(id1, 95);
    db.add_student(id2, 88);
    db.add_student(id3, 97);
    db.add_student(id4, 90);
    db.add_student(id5, 90); // Duplicate score with id4
    db.add_student(id6, 90); // Duplicate score with id4 and id5

    cout << "\nTesting StudentDatabase:\n" << endl;

    // Test get_score
    try {
        cout << "Score of " << id1 << ": " << db.get_score(id1) << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    // Test update_score
    db.update_score(id1, 99);
    try {
        cout << "Updated Score of " << id1 << ": " << db.get_score(id1) << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    // Test get_top_k_students with k = 5
    int k = 5;
    int** top_students = db.get_top_k_students(k);
    print_top_k_students(top_students, k);

    // Free the allocated memory
    for (int i = 0; i < k; ++i) {
        delete[] top_students[i];
    }
    delete[] top_students;

    // Test get_rank for score 90
    try {
        int score_rank = db.get_rank(90);
        cout << "\nRank of score 90: " << score_rank << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    // Test get_rank for score 88
    try {
        int score_rank = db.get_rank(88);
        cout << "Rank of score 88: " << score_rank << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    // Test get_rank for score not in the database
    try {
        int score_rank = db.get_rank(85);
        cout << "Rank of score 85: " << score_rank << endl;
    } catch (const exception& e) {
        cerr << "Expected exception: " << e.what() << endl;
    }

    // Remove a student and test get_top_k_students again
    db.remove_student(id3); // Remove student with score 97
    k = 5;
    top_students = db.get_top_k_students(k);
    cout << "\nAfter removing student ID " << id3 << ":" << endl;
    print_top_k_students(top_students, k);

    // Free the allocated memory
    for (int i = 0; i < k; ++i) {
        delete[] top_students[i];
    }
    delete[] top_students;

    // Test get_rank after removal
    try {
        int score_rank = db.get_rank(97);
        cout << "Rank of score 97: " << score_rank << endl;
    } catch (const exception& e) {
        cerr << "Expected exception: " << e.what() << endl;
    }

    // Test get_rank for updated score
    try {
        int score_rank = db.get_rank(99);
        cout << "Rank of score 99: " << score_rank << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    // Test range_query for [90, 100]
    try {
        int count = 0;
        int* student_ids = db.range_query(90, 100, count);
        cout << "\nRange query [90, 100]:" << endl;
        if (student_ids != nullptr) {
            print_range_query_result(student_ids, count, db);
            delete[] student_ids;
        } else {
            cout << "No students in range." << endl;
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main() {
    cout << "Starting tests..." << endl;

    test_student_map();
    test_student_ordered_map();
    test_student_database();

    cout << "Tests completed." << endl;

    return 0;
}