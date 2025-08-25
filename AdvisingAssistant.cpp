#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

// Course structure
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;

    Course() {}
};

// Node structure
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class Tree {
private:
    Node* root;

    // Insert node helper
    void insertNode(Node* node, Course course) {
        if (course.courseNumber < node->course.courseNumber) {
            if (node->left == nullptr) {
                node->left = new Node(course);
            }
            else {
                insertNode(node->left, course);
            }
        }
        else {
            if (node->right == nullptr) {
                node->right = new Node(course);
            }
            else {
                insertNode(node->right, course);
            }
        }
    }

    // In-order traversal helper
    void inOrderTraversal(Node* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->course.courseNumber << ", " << node->course.title << endl;
            inOrderTraversal(node->right);
        }
    }

    // Search node helper
    Course searchNode(Node* node, string courseNumber) {
        if (node == nullptr) {
            return Course(); // Return empty course
        }

        if (courseNumber == node->course.courseNumber) {
            return node->course;
        }
        else if (courseNumber < node->course.courseNumber) {
            return searchNode(node->left, courseNumber);
        }
        else {
            return searchNode(node->right, courseNumber);
        }
    }

    // Destructor helper
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    // Constructor
    Tree() {
        root = nullptr;
    }

    // Destructor
    ~Tree() {
        destroyTree(root);
    }

    // Insert course
    void Insert(Course course) {
        if (root == nullptr) {
            root = new Node(course);
        }
        else {
            insertNode(root, course);
        }
    }

    // Search for course
    Course Search(string courseNumber) {
        return searchNode(root, courseNumber);
    }

    // Print all courses
    void printAllCourses() {
        cout << "Here is a sample schedule:" << endl;
        cout << endl;
        inOrderTraversal(root);
    }
};

// Trim whitespace from string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// Split string by delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }

    return tokens;
}

// Load courses from file
bool loadCourses(string fileName, Tree* bst) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Cannot open file " << fileName << endl;
        return false;
    }

    vector<Course> allCourses;
    string line;

    // First pass: load all courses
    while (getline(file, line)) {
        if (line.empty()) continue;

        vector<string> tokens = split(line, ',');

        if (tokens.size() < 2) {
            cout << "Error: Line must have at least course number and title" << endl;
            continue;
        }

        Course course;
        course.courseNumber = tokens[0];
        course.title = tokens[1];

        // Add prerequisites
        for (int i = 2; i < tokens.size(); i++) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(tokens[i]);
            }
        }

        allCourses.push_back(course);
        bst->Insert(course);
    }

    file.close();

    // Second pass: validate prerequisites using BST
    for (const Course& course : allCourses) {
        for (const string& prereq : course.prerequisites) {
            Course foundCourse = bst->Search(prereq);
            if (foundCourse.courseNumber.empty()) {
                cout << "Error: Prerequisite " << prereq << " not defined in file" << endl;
                return false;
            }
        }
    }

    return true;
}

// Display menu
void displayMenu() {
    cout << "Welcome to the course planner." << endl;
    cout << endl;
    cout << " 1. Load Data Structure" << endl;
    cout << " 2. Print Course List" << endl;
    cout << " 3. Print Course" << endl;
    cout << " 9. Exit" << endl;
    cout << endl;
    cout << "What would you like to do? ";
}

// Print course information
void printCourse(Tree* bst, string courseNumber) {
    // Convert to uppercase for consistent searching
    transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);

    Course course = bst->Search(courseNumber);

    if (course.courseNumber.empty()) {
        cout << "Course " << courseNumber << " not found." << endl;
        return;
    }

    cout << course.courseNumber << ", " << course.title << endl;

    if (!course.prerequisites.empty()) {
        cout << "Prerequisites: ";
        for (int i = 0; i < course.prerequisites.size(); i++) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    else {
        cout << "Prerequisites: None" << endl;
    }
}

// Check if data is loaded
bool isDataLoaded(Tree* bst) {
    Course testCourse = bst->Search("CSCI100");
    return !testCourse.courseNumber.empty();
}

int main() {
    Tree bst;
    int choice;
    string fileName;
    string courseNumber;
    bool dataLoaded = false;

    while (true) {
        displayMenu();

        // Check if input is valid
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        // Process user's menu choice
        switch (choice) {
            // Option 1: Load course data from file
        case 1: {
            cout << "Enter filename: ";
            cin.ignore();
            getline(cin, fileName);

            if (loadCourses(fileName, &bst)) {
                cout << "Data loaded successfully." << endl;
                dataLoaded = true;
            }
            else {
                cout << "Failed to load data." << endl;
            }
            break;
        }

              // Option 2: Display all courses in sorted order
        case 2: {
            if (!dataLoaded) {
                cout << "No data loaded. Please load data first." << endl;
            }
            else {
                bst.printAllCourses();
            }
            break;
        }

              // Option 3: Search for and display specific course
        case 3: {
            if (!dataLoaded) {
                cout << "No data loaded. Please load data first." << endl;
            }
            else {
                cout << "What course do you want to know about? ";
                cin.ignore();
                getline(cin, courseNumber);
                printCourse(&bst, courseNumber);
            }
            break;
        }

              // Option 9: Exit program
        case 9: {
            cout << "Thank you for using the course planner!" << endl;
            return 0;
        }

              // Handle invalid menu choices
        default: {
            cout << choice << " is not a valid option." << endl;
            break;
        }
        }

        cout << endl;
    }

    return 0;
}