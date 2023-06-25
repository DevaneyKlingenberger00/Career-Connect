#include <iostream> 
#include <string> 
#include <map> 
#include <vector> 
#include <algorithm> 

using namespace std; 

// enum to store type of profile 
enum ProfileType 
{ 
	Student, 
	Employer 
}; 

// Base class 
class Profile 
{ 
protected: 
	// string to store name of profile 
	string name; 

	// stores age of profile 
	int age; 
public: 
	// constructor to create profile 
	Profile(string n, int a) 
	{ 
		name = n; 
		age = a; 
	} 

	// return name of profile 
	string getName() 
	{ 
		return name; 
	} 

	// return age of profile 
	int getAge() 
	{ 
		return age; 
	} 

	virtual void print() = 0; 
	virtual ProfileType getType() = 0; 
}; 

// Derived class for Student 
class Student : public Profile 
{ 
private: 
	// marks scored by student 
	float marks; 
public: 
	// constructor to create student 
	Student(string n, int a, float m) 
		: Profile(n, a) 
	{ 
		marks = m; 
	} 

	// return marks scored by student 
	float getMarks() 
	{ 
		return marks; 
	} 

	// print profile details 
	void print() 
	{ 
		cout << "Name: " << name << endl; 
		cout << "Age: " << age << endl; 
		cout << "Marks: " << marks << endl; 
	} 

	// return type of profile 
	ProfileType getType() 
	{ 
		return Student; 
	} 
}; 

// Derived class for Employer 
class Employer : public Profile 
{ 
private: 
	// string to store designatipon of employer 
	string designation; 
public: 
	// constructor to create employer 
	Employer(string n, int a, string des) 
		: Profile(n, a) 
	{ 
		designation = des; 
	} 

	// return designation of employer 
	string getDesignation() 
	{ 
		return designation; 
	} 

	// print profile details 
	void print() 
	{ 
		cout << "Name: " << name << endl; 
		cout << "Age: " << age << endl; 
		cout << "Designation: " << designation << endl; 
	} 

	// return type of profile 
	ProfileType getType() 
	{ 
		return Employer; 
	} 
}; 

// stores profile of student and employer 
map<int, Profile*> profiles; 

// function to create profile 
void createProfile(ProfileType type) 
{ 
	string name; 
	int age; 

	// input name and age of profile to be created 
	cout << "Name: "; 
	cin >> name; 
	cout << "Age: "; 
	cin >> age; 

	// create profile depending on type 
	if (type == Student) 
	{ 
		float marks; 
		cout << "Marks: "; 
		cin >> marks; 
		profiles[profiles.size() + 1] = 
					new Student(name, age, marks); 
		cout << "Profile created successfully!!\n"; 
	} 
	else if (type == Employer) 
	{ 
		string designation; 
		cout << "Designation: "; 
		cin >> designation; 
		profiles[profiles.size() + 1] = 
					new Employer(name, age, designation); 
		cout << "Profile created successfully!!\n"; 
	} 
} 

// function to display profile details 
void displayProfile(int id) 
{ 
	if (profiles.find(id) != profiles.end()) 
		profiles[id]->print(); 
	else
		cout << "Profile not found!!\n"; 
} 

// function to matchmake students and employers 
void matchMake() 
{ 
	// stores students 
	vector<Student*> students; 

	// stores employers 
	vector<Employer*> employers; 

	// split profiles into students and employers 
	for (auto it = profiles.begin(); it != profiles.end(); it++) 
		if (it->second->getType() == Student) 
			students.push_back(dynamic_cast<Student*>(it->second)); 
		else
			employers.push_back(dynamic_cast<Employer*>(it->second)); 

	// sort students in descending order of their marks 
	sort(students.begin(), students.end(), 
		[](Student* a, Student* b) { 
			return a->getMarks() > b->getMarks(); 
		}); 

	// sort employers in descending order of their age 
	sort(employers.begin(), employers.end(), 
		[](Employer* a, Employer* b) { 
			return a->getAge() > b->getAge(); 
		}); 

	// matchmake students and employers 
	cout << "List of matches:\n"; 
	int count = 0; 
	for (int i = 0; i < students.size(); i++) 
		for (int j = 0; j < employers.size(); j++) 
		{ 
			cout << "Match " << ++count << 
				": Student " << students[i]->getName() << 
				" and Employer " << employers[j]->getName() << endl; 
			employers.erase(employers.begin() + j); 
			break; 
		} 
} 

// Driver Code 
int main() 
{ 
	// create profiles 
	createProfile(Student); 
	createProfile(Student); 
	createProfile(Employer); 
	createProfile(Employer); 
	createProfile(Employer); 

	// display profile details 
	displayProfile(2); 

	// matchmake students and employers 
	matchMake(); 

	return 0;	 
}