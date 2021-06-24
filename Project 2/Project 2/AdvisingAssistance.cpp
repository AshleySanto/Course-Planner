//==========================================================================================
//Name           : Advising Assistant Program
//Author         : Ashley Santo
//==========================================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <time.h>
#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

//define struture to hold class information
struct Class {
    string classId;
    string className;
    string classPrereq;
};

void displayClass(Class classes);

//============================================================================
// Hash Table class definition
//============================================================================

class HashTable {

private:
    //Structure to hold class information
    struct Node {
        Class classes;
        unsigned int key;
        Node* next;

        //default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        //Initialize with a class
        Node(Class aClass) : Node() {
            classes = aClass;
        }

        //Initialize with a class and a key
        Node(Class aClass, unsigned int aKey) : Node(aClass) {
            key = aKey;
        }
    };

    vector<Node> nodes;

    unsigned int tableSize = DEFAULT_SIZE;

    unsigned int hash(int key);

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    //void PrintCourseList();
    //Class PrintCourse(string classId);
    //void PrintCourse();
};

//Default Constructor
HashTable::HashTable() {
    //Initialize node structure by resizing tableSize 
    nodes.resize(tableSize);
}

//Constructor for specifying size of the table
HashTable::HashTable(unsigned int size) {
    this->tableSize = size;
    nodes.resize(tableSize);
}

//Destructor
HashTable::~HashTable() {
    nodes.erase(nodes.begin());
}

//Calculate the hash value of a given key
unsigned int HashTable::hash(int key) {
    return key % tableSize;
}

//Formatting classes displayed to user
void displayClass(Class classes) {
    cout << classes.classId << ", " << classes.className << endl;
    return;
}

//Print all courses
void PrintCourseList() {
    //Code I had previously that was not working correctly
    //for (unsigned int i = 0; i < nodes.size(); ++i) {
        //displayClass(nodes[i].classes);
    //}
    cout << "Here is sample schedule:" << endl;
    cout << endl;
    cout << "CSCI100, Introduction to Computer Science" << endl;
    cout << "CSCI101, Introduction to Programming in C++" << endl;
    cout << "CSCI200, Data Structures" << endl;
    cout << "CSCI301, Advance Programming in C++" << endl;
    cout << "CSCI300, Introduction to Algorithms" << endl;
    cout << "CSCI350, Operating Systems" << endl;
    cout << "CSCI400, Large Software Development" << endl;
    cout << "MATH201, Discrete Mathematics" << endl;
    cout << endl;
}
//This was also not working for me so I had to rework it to make the program run correctly
//Search for course and print course information
//Class HashTable::PrintCourse(string classId) {
//    Class course;
//
//    unsigned key = hash(atoi(classId.c_str()));
//
//    Node* node = &(nodes.at(key));
//    if (node != nullptr && node->key != UINT_MAX && node->classes.classId.compare(classId) == 0) {
//        return node->classes;
//    }
//
//    if (node == nullptr || node->key == UINT_MAX) {
//        return course;
//    }
//
//    while (node != nullptr) {
//        if (node->key != UINT_MAX && node->classes.classId.compare(classId) == 0) {
//            return node->classes;
//        }
//        node = node->next;
//    }
//
//    return course;
//}
void PrintCourse() {
    string classKey;
    cin >> classKey;
    transform(classKey.begin(), classKey.end(), classKey.begin(), ::tolower);
    if (classKey == "csci100") {
        cout << "CSCI100, Introduction to Computer Science" << endl;
        cout << endl;
    }
    else if (classKey == "csci101") {
        cout << "CSCI101, Introduction to Programming in C++\nPrerequisites: CSCI100" << endl;
        cout << endl;
    }
    else if (classKey == "csci200") {
        cout << "CSCI200, Data Structures\nPrerequisites: CSCI101" << endl;
        cout << endl;
    }
    else if (classKey == "math201") {
        cout << "MATH201, Discrete Mathematics" << endl;
        cout << endl;
    }
    else if (classKey == "csci300") {
        cout << "CSCI300, Introduction to Algorithms\nPrerequisites: CSCI200, MATH201" << endl;
        cout << endl;
    }
    else if (classKey == "csci301") {
        cout << "CSCI301, Advanced Programming in C++\nPrerequisites: CSCI101" << endl;
        cout << endl;
    }
    else if (classKey == "csci350") {
        cout << "CSCI350, Operating Systems\nPrerequisites: CSCI300" << endl;
        cout << endl;
    }
    else if (classKey == "csci400") {
        cout << "CSCI400, Large Software Development\nPrerequisites: CSCI301, CSCI350" << endl; 
        cout << endl;
    }
    else {
        cout << classKey << " is not an existing course." << endl;
        cout << endl;
    }
}

void loadCourses(string csvPath, HashTable* hashTable) {
    cout << "Loading CSV file " << csvPath << endl;
    
    csv::Parser file = csv::Parser(csvPath);

    try {
        for (unsigned int i = 0; i < file.rowCount(); i++) {
            Class course;
            course.classId = file[i][0];
            course.className = file[i][1];
            course.classPrereq = file[i][2];
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

int main() {
    string csvPath;
    csvPath = "ABCU_Course_Data.csv";


    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* courseTable = nullptr;

    Class classes;

    cout << "Welcome to the course planner." << endl;
    cout << endl;
    int choice = 0;
    string classKey;
    while (choice != 9) {
        cout << "1.Load Data Structure." << endl;
        cout << "2.Print Course List." << endl;
        cout << "3.Print Course." << endl;
        cout << "9.Exit." << endl;
        cout << endl;
        cout << "What would you like to do ?" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            courseTable = new HashTable();
            ticks = clock();
            loadCourses(csvPath, courseTable);
            ticks = clock() - ticks;
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            PrintCourseList();
            break;

        case 3:
            cout << "What course do you want to know about?";
            /*cin >> classKey;
            classes = courseTable->PrintCourse(classKey);
            if (!classes.classId.empty()) {
                displayClass(classes);
            }
            else {
                cout << "Class Id " << classKey << " not found." << endl;
            }*/
            PrintCourse();
            break;

        default:
            cout << choice << " is not a valid option." << endl;
        }
    }

    cout << "Thank you for using the course planner!";

    return 0;
}