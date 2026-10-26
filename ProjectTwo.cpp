/*
 * CS 300 Project Two - Advising Assistance Program
 * Author: Jesse Carles
 *
 * Loads ABC University course data from a file into a binary search tree.
 * Prints the course list in order and displays individual courses and prerequisites.
 */

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

struct Node {
    Course course;
    Node* left;
    Node* right;

    explicit Node(const Course& courseData)
        : course(courseData), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    Node* insertNode(Node* node, const Course& course) {
        if (node == nullptr) {
            return new Node(course);
        }

        if (course.courseNumber < node->course.courseNumber) {
            node->left = insertNode(node->left, course);
        }
        else if (course.courseNumber > node->course.courseNumber) {
            node->right = insertNode(node->right, course);
        }
        else {
            node->course = course;
        }

        return node;
    }

    void inOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }

        inOrder(node->left);
        cout << node->course.courseNumber << ", "
             << node->course.courseTitle << '\n';
        inOrder(node->right);
    }

    void destroyTree(Node* node) {
        if (node == nullptr) {
            return;
        }

        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        clear();
    }

    void clear() {
        destroyTree(root);
        root = nullptr;
    }

    void insert(const Course& course) {
        root = insertNode(root, course);
    }

    const Course* search(const string& courseNumber) const {
        Node* current = root;

        while (current != nullptr) {
            if (courseNumber == current->course.courseNumber) {
                return &current->course;
            }

            if (courseNumber < current->course.courseNumber) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        return nullptr;
    }

    void printAll() const {
        inOrder(root);
    }

    bool empty() const {
        return root == nullptr;
    }
};

string trim(const string& text) {
    const string whitespace = " \t\r\n";
    size_t start = text.find_first_not_of(whitespace);

    if (start == string::npos) {
        return "";
    }

    size_t end = text.find_last_not_of(whitespace);
    return text.substr(start, end - start + 1);
}

string toUpper(string text) {
    transform(text.begin(), text.end(), text.begin(),
        [](unsigned char ch) { return static_cast<char>(toupper(ch)); });
    return text;
}

vector<string> splitCSVLine(const string& line) {
    vector<string> tokens;
    string token;
    stringstream stream(line);

    while (getline(stream, token, ',')) {
        tokens.push_back(trim(token));
    }

    return tokens;
}

bool loadCourses(const string& fileName, BinarySearchTree& courseTree) {
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cout << "Error: Unable to open file \"" << fileName << "\".\n";
        return false;
    }

    vector<Course> courses;
    string line;
    int lineNumber = 0;

    while (getline(inputFile, line)) {
        ++lineNumber;

        if (trim(line).empty()) {
            continue;
        }

        vector<string> tokens = splitCSVLine(line);

        if (tokens.size() < 2 || tokens[0].empty() || tokens[1].empty()) {
            cout << "Error: Invalid course data on line " << lineNumber << ".\n";
            cout << "Each course must include a course number and title.\n";
            return false;
        }

        Course course;
        course.courseNumber = toUpper(tokens[0]);
        course.courseTitle = tokens[1];

        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(toUpper(tokens[i]));
            }
        }

        courses.push_back(course);
    }

    if (courses.empty()) {
        cout << "Error: The selected file did not contain any course data.\n";
        return false;
    }

    for (const Course& course : courses) {
        for (const string& prerequisite : course.prerequisites) {
            bool found = false;

            for (const Course& possibleCourse : courses) {
                if (possibleCourse.courseNumber == prerequisite) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Error: Prerequisite " << prerequisite
                     << " for " << course.courseNumber
                     << " does not exist in the input file.\n";
                return false;
            }
        }
    }

    courseTree.clear();

    for (const Course& course : courses) {
        courseTree.insert(course);
    }

    cout << "Course data loaded successfully.\n";
    return true;
}

void displayMenu() {
    cout << "\n1. Load Data Structure.\n"
         << "2. Print Course List.\n"
         << "3. Print Course.\n"
         << "9. Exit\n\n";
}

void printCourseInformation(const BinarySearchTree& courseTree,
                            const string& requestedCourseNumber) {
    const string courseNumber = toUpper(trim(requestedCourseNumber));
    const Course* course = courseTree.search(courseNumber);

    if (course == nullptr) {
        cout << courseNumber << " is not a valid course.\n";
        return;
    }

    cout << course->courseNumber << ", " << course->courseTitle << '\n';

    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None\n";
        return;
    }

    cout << "Prerequisites: ";

    for (size_t i = 0; i < course->prerequisites.size(); ++i) {
        const Course* prerequisiteCourse =
            courseTree.search(course->prerequisites[i]);

        if (prerequisiteCourse != nullptr) {
            cout << prerequisiteCourse->courseNumber
                 << " (" << prerequisiteCourse->courseTitle << ")";
        }
        else {
            cout << course->prerequisites[i];
        }

        if (i + 1 < course->prerequisites.size()) {
            cout << ", ";
        }
    }

    cout << '\n';
}

int main() {
    BinarySearchTree courseTree;
    bool dataLoaded = false;
    int choice = 0;

    cout << "Welcome to the course planner.\n";

    while (choice != 9) {
        displayMenu();
        cout << "What would you like to do? ";

        string input;
        getline(cin, input);

        try {
            string cleanedInput = trim(input);
            size_t position = 0;
            choice = stoi(cleanedInput, &position);

            if (position != cleanedInput.size()) {
                throw invalid_argument("extra characters");
            }
        }
        catch (...) {
            cout << input << " is not a valid option.\n";
            choice = 0;
            continue;
        }

        switch (choice) {
        case 1: {
            cout << "What is the file name that contains the course data? ";
            string fileName;
            getline(cin, fileName);

            dataLoaded = loadCourses(trim(fileName), courseTree);
            break;
        }

        case 2:
            if (!dataLoaded || courseTree.empty()) {
                cout << "Please load the course data first.\n";
            }
            else {
                cout << "Here is a sample schedule:\n\n";
                courseTree.printAll();
            }
            break;

        case 3:
            if (!dataLoaded || courseTree.empty()) {
                cout << "Please load the course data first.\n";
            }
            else {
                cout << "What course do you want to know about? ";
                string courseNumber;
                getline(cin, courseNumber);
                printCourseInformation(courseTree, courseNumber);
            }
            break;

        case 9:
            cout << "Thank you for using the course planner!\n";
            break;

        default:
            cout << choice << " is not a valid option.\n";
            break;
        }
    }

    return 0;
}
