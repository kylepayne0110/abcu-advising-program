/*/
Author: Kyle Payne
Course: CS-300-13159-M01 DSA
Date: 4/12/2026
Description: Code for ABCU Computer Science Advising Assistance
*/

#include <iostream>   // for input and output
#include <fstream>   // for file handling
#include <sstream>   // for splitting lines in file
#include <vector>   // for vectors(prerequisites, temporaory tokens, sorting keys)
#include <unordered_map>   // for hash table data structure
#include <algorithm>   // for sorting
#include <cctype>   // for toUpper() function

using namespace std;

// Class to create course objects with course number, course name, and prerequisites
class Course {
public:
    string courseNumber;
	string courseName;
    vector<string> prerequisites;
};

// Funciton prototypes
bool loadCourses(string fileName, unordered_map<string, Course>& courses);
void printCourseList(const unordered_map<string, Course>& courses);
void printCourse(const unordered_map <string, Course>& courses, string courseNumber);
bool validateTokens(vector <string> tokens);
void displayMenu();
string toUpper(string input);


// function to display menu options to user
void displayMenu() {
	cout << "1. Load Data Structure." << endl;
	cout << "2. Print Course List." << endl;
	cout << "3. Print Course." << endl;
	cout << "9. Exit." << endl;
}

// function to convert string to uppercase for case insensitivity
string toUpper(string input) {
	// loop through each character in the string and convert to uppercase
	for (int i = 0; i < input.size(); i++) {
		input[i] = toupper(input[i]);
	}
	return input;
}

// function to validate tokens vector from file input for each line in  file
bool validateTokens(vector <string> tokens) {
	if (tokens.size() < 2) {
		return false;
	}
	return true;
}

// function to load courses from file, validate lines in the file, create course objects, and store them in the hash table
bool loadCourses(string fileName, unordered_map<string, Course>& courses) {
	ifstream file(fileName); // open file for reading
	if (!file.is_open()) {
		cout << "Error opening file: " << fileName << endl;
		return false;
	}
	string line; // variable to store each line of the file
	while (getline(file, line)) { // read file line by line
		vector<string> tokens; // vector to store tokens from each line
		stringstream ss(line); // create string stream to split line into tokens
		string token; // variable to store each token
		while (getline(ss, token, ',')) { // split line into tokens using comma as delimiter
			tokens.push_back(token); // add token to vector
		}
		if (!validateTokens(tokens)) { // validate tokens for each line in the file
			cout << "Invalid line in file: " << line << endl;
			continue; // skip invalid lines and continue reading the file
		}
		Course course; // create course object
		course.courseNumber = toUpper(tokens[0]); // set course number and convert to uppercase for case insensitivity
		course.courseName = tokens[1]; // set course name
		for (int i = 2; i < tokens.size(); i++) { // loop through remaining tokens and add them as prerequisites for the course
			course.prerequisites.push_back(toUpper(tokens[i])); // add prerequisite and convert to uppercase for case insensitivity
		}
		courses[course.courseNumber] = course; // add course object to hash table with course number as key and course object as value
	}
	return true; // return true if courses were loaded successfully
}

void printCourseList(const unordered_map<string, Course>&courses) {
		vector<string> courseNumbers; // vector to store course numbers for sorting
		for (const auto& pair : courses) { // loop through hash table and add course numbers to vector
			courseNumbers.push_back(pair.first);
		}
		sort(courseNumbers.begin(), courseNumbers.end()); // sort course numbers alphanumerically
		for (const string& courseNumber : courseNumbers) { // loop through sorted course numbers and print course information
			cout << courseNumber << ", " << courses.at(courseNumber).courseName << endl;
		}
}

// function to print course information for a specific course number input by user
void printCourse(const unordered_map<string, Course>& courses, string courseNumber) {
	courseNumber = toUpper(courseNumber); // convert course number input by user to uppercase for case insensitivity
	if (courses.find(courseNumber) != courses.end()) { // check if course number exists in hash table
		Course course = courses.at(courseNumber); // get course object from hash table
		cout << course.courseNumber << ", " << course.courseName << endl; // print course number and course name
		if (!course.prerequisites.empty()) { // check if course has prerequisites
			cout << "Prerequisites: "; // print prerequisites header
			for (const string& prerequisite : course.prerequisites) { // loop through prerequisites and print them
				cout << prerequisite << " ";
			}
			cout << endl; // print new line after printing prerequisites
		}
		else {
			cout << "No prerequisites." << endl; // print message if course has no prerequisites
		}
	}
	else {
		cout << "Course not found: " << courseNumber << endl; // print message if course number is not found in hash table
	}
}


int main() {
	int userChoice = 0;   // variable to store user menu choice
	string fileName;   // variable to store file name input by user
	unordered_map<string, Course> courses; // create hash table to store courses with course number as key and course object as the value
	string courseNumber;   // variable to store course number input by user for printing course information



	// Display welcome message and load courses from file
	cout << "Welcome to the ABCU Computer Science Advising Assistance Program!" << endl;

	// Prompt user for menu choice

	cout << "Please enter a menu option: " << endl;

	while (userChoice != 9) {

		// Call Display menu funciton
		displayMenu();

		// Get user input
		cin >> userChoice;
		if (cin.fail()) {
			cin.clear();                // clear error flag
			cin.ignore(1000, '\n');     // discard bad input
			userChoice = 0;             // reset to trigger invalid option message
			continue;
		}

		// Call appropriate functions based on user input using conditionals
		if (userChoice == 1) {
			cout << " Please enter the name of the file to load courses from: " << endl;
			// Prompt user for fileName
			cin.ignore();                  // flush leftover newline from cin >> userChoice
			getline(cin, fileName);        // reads the full filename including spaces

			// Call loadCourses function and pass fileName and courses to the hash table
			bool success = loadCourses(fileName, courses);
			if (success) {
				cout << "Courses loaded successfully from file: " << fileName << endl;
			}
			else {
				cout << "Failed to load courses from file: " << fileName << endl;
			}
		}

		else if (userChoice == 2) {
			// Call printCourseList function and pass courses to print the list of courses alphanumerically by course number
			printCourseList(courses);
		}

		else if (userChoice == 3) {
			// Prompt user for course number
			cout << "Please enter the course number to print information for: " << endl;

			// get course number input from user
			cin >> courseNumber;

			// Call printCourse function and pass courses and course number to print the course information
			printCourse(courses, courseNumber);

		}
		else if (userChoice == 9) {
			// Exit the program
			cout << "Thank you for using the ABCU Computer Science Advising Assistance Program! Goodbye!" << endl;
		}
		else {
			// Handle invalid input
			cout << userChoice << " is not a valid menu option, please enter a valid menu option." << endl;
		}
	}
	
		return 0;
	
}
