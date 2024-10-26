#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// Define the Course structure
struct Course {
    std::string courseId;
    std::string courseTitle;
    std::vector<std::string> prerequisites;
};

// Define the TreeNode structure
struct TreeNode {
    Course course;
    TreeNode* left;
    TreeNode* right;
    TreeNode(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// Define the Courses class
class Courses {
private:
    TreeNode* root;

    void insertNode(TreeNode*& node, Course course);
    void inOrderTraversal(TreeNode* node);
    Course searchNode(TreeNode* node, std::string courseId);

public:
    Courses() : root(nullptr) {}
    void insert(Course course);
    void printCourses();
    Course search(std::string courseId);
};

// Implementation of the Courses methods
void Courses::insertNode(TreeNode*& node, Course course) {
    if (node == nullptr) {
        node = new TreeNode(course);
    }
    else if (course.courseId < node->course.courseId) {
        insertNode(node->left, course);
    }
    else {
        insertNode(node->right, course);
    }
}

void Courses::inOrderTraversal(TreeNode* node) {
    if (node != nullptr) {
        inOrderTraversal(node->left);
        std::cout << node->course.courseId << ": " << node->course.courseTitle << std::endl;
        if (!node->course.prerequisites.empty()) {
            std::cout << "Prerequisites: ";
            for (const auto& prereq : node->course.prerequisites) {
                std::cout << prereq << " ";
            }
            std::cout << std::endl;
        }
        inOrderTraversal(node->right);
    }
}

Course Courses::searchNode(TreeNode* node, std::string courseId) {
    if (node == nullptr) {
        return Course(); // return empty course if not found
    }
    else if (node->course.courseId == courseId) {
        return node->course;
    }
    else if (courseId < node->course.courseId) {
        return searchNode(node->left, courseId);
    }
    else {
        return searchNode(node->right, courseId);
    }
}

void Courses::insert(Course course) {
    insertNode(root, course);
}

void Courses::printCourses() {
    inOrderTraversal(root);
}

Course Courses::search(std::string courseId) {
    return searchNode(root, courseId);
}

// Function to load courses from the file
bool loadCourses(Courses& bst) {

    std::ifstream file("C:/Users/blake/OneDrive/Desktop/CS 300 ABCU_Advising_Program_Input.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file: CS_300_ABCU_Advising_Program_Input.csv" << std::endl;
        return false;
    }
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string courseId, courseTitle, prereq;
        getline(iss, courseId, ',');
        getline(iss, courseTitle, ',');
        Course course = { courseId, courseTitle, {} };
        while (getline(iss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }
        bst.insert(course);
    }
    file.close();
    std::cout << "Courses loaded successfully from file!" << std::endl;
    return true;
}

// Function to display the menu
void displayMenu() {
    std::cout << "\nMenu Options:" << std::endl;
    std::cout << "1. Load Data Structure." << std::endl;
    std::cout << "2. Print Course List." << std::endl;
    std::cout << "3. Print Course." << std::endl;
    std::cout << "9. Exit" << std::endl;
}

// Function to handle the menu choices
void handleMenu(Courses& bst) {
    int choice = 0;
    bool dataLoaded = false; // Check if data has been loaded

    while (choice != 9) {
        displayMenu();
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        if (!dataLoaded && choice != 1 && choice != 9) {
            std::cout << "You need to load the data first!" << std::endl;
            continue;
        }

        switch (choice) {
        case 1:
            dataLoaded = loadCourses(bst); // Load data
            break;
        case 2:
            if (dataLoaded) {
                bst.printCourses();
            }
            break;
        case 3: {
            if (dataLoaded) {
                std::string courseId;
                std::cout << "Enter course ID: ";
                std::cin >> courseId;
                Course course = bst.search(courseId);
                if (!course.courseId.empty()) {
                    std::cout << course.courseId << ": " << course.courseTitle << std::endl;
                    if (!course.prerequisites.empty()) {
                        std::cout << "Prerequisites: ";
                        for (const std::string& prereq : course.prerequisites) {
                            std::cout << prereq << " ";
                        }
                        std::cout << std::endl;
                    }
                }
                else {
                    std::cout << "Course not found." << std::endl;
                }
            }
            break;
        }
        case 9:
            std::cout << "Thank you for using the Course Planner!" << std::endl;
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << choice << " is not a valid option." << std::endl;
        }
    }
}


int main() {
    std::cout << "Welcome to the Course Planner!" << std::endl;
    Courses courseTree;
    handleMenu(courseTree);
    return 0;
}
