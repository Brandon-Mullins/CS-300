#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>

class Course {
public:
    Course() : number(""), title("") {}

    Course(const std::string& number, const std::string& title)
        : number(number), title(title) {}

    std::string getNumber() const { return number; }
    std::string getTitle() const { return title; }

    void addPrerequisite(const std::string& prereq) {
        prerequisites.push_back(prereq);
    }

    void printCourse() const {
        std::cout << "Course Number: " << number << "\n"
                  << "Title: " << title << "\n";
        if (prerequisites.empty()) {
            std::cout << "No prerequisites.\n";
        } else {
            std::cout << "Prerequisites: ";
            for (const auto& prereq : prerequisites) {
                std::cout << prereq << " ";
            }
            std::cout << "\n";
        }
    }

private:
    std::string number;
    std::string title;
    std::vector<std::string> prerequisites;
};

class CourseCatalog {
public:
    void loadCourses(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file!\n";
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string number, title, prerequisite;

            std::getline(ss, number, ',');
            std::getline(ss, title, ',');

            Course course(number, title);

            while (std::getline(ss, prerequisite, ',')) {
                course.addPrerequisite(prerequisite);
            }

            courses[number] = course;
        }

        file.close();
    }

    void printCourseList() const {
        if (courses.empty()) {
            std::cout << "No courses loaded.\n";
            return;
        }

        std::cout << "Course List:\n";
        for (const auto& pair : courses) {
            std::cout << pair.second.getNumber() << ": " << pair.second.getTitle() << "\n";
        }
    }

    void printCourse(const std::string& courseNumber) const {
        auto it = courses.find(courseNumber);
        if (it != courses.end()) {
            it->second.printCourse();
        } else {
            std::cout << "Course not found.\n";
        }
    }

private:
    std::unordered_map<std::string, Course> courses;
};

int main() {
    CourseCatalog catalog;
    int choice;

    while (true) {
        std::cout << "\nUse the input and pick a number. \n";
        std::cout << "1. Load Data Structure.\n";
        std::cout << "2. Print Course List.\n";
        std::cout << "3. Print Course.\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter a number: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                catalog.loadCourses("courses.txt");
                std::cout << "Courses loaded successfully.\n";
                break;

            case 2:
                catalog.printCourseList();
                break;

            case 3:
                {
                    std::string courseNumber;
                    std::cout << "Enter course number: ";
                    std::cin >> courseNumber;
                    catalog.printCourse(courseNumber);
                }
                break;

            case 9:
                std::cout << "Exiting program.\n";
                return 0;

            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }


}
