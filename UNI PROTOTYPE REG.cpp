# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <limits>

using namespace std;
// global var.
int role=0;



// abstract class
class Person {
    protected:
    string name;
    int id;

    public:
    Person() : name("Unknown"), id(0000) {
    }
    Person(string x, int y) : name(x), id(y) {
    }
    int getid() {
        return id;
    }
    string getname() {
        return name;
    }
    void setname(string n) {
        name = n;
    }
    void setid(int i) {
        id = i;
    }
    virtual void displayinfo() = 0;
};





// Course class
class Course{
    public:
    int course_id;
    string course_name;
    int Max_students;
    int Current_students;

    Course(int id, string name, int max) : course_id(id), course_name(name), Max_students(max), Current_students(0) {
    }

    void add_student() {
        if (Current_students >= Max_students){
            throw "Course is full";
        } 
        Current_students++;
    }

    void remove_student() {
        if (Current_students > 0) {
            Current_students--;
        }
    }

    void show_course_info() {
        cout << "Course ID: " << course_id << ", Name: " << course_name 
        << " (" << Current_students << "/" << Max_students << ")" << endl;
    }
};
















//Student class derived from Person class
class Student : public Person {
    private:
    int yearofstudy;
    string department;
    vector<Course> reg_courses;

    public:
    Student(string name, int id, int p, string o, vector<Course> cou): Person(name, id), yearofstudy(p), department(o), reg_courses(cou) {

    }

    Student() : yearofstudy(0), department("Unknown"), reg_courses({}) {
    }

    void set_yearofstudy(int y) {
        yearofstudy = y;
    }

    void set_department(string d) {
        department = d;
    }

    void setreg_courses(vector<Course> reg) {
        reg_courses = reg;
    }

    int get_year_of_study() {
        return yearofstudy;
    }

    string get_department() {
        return department;
    }

    vector<Course> get_reg_courses() {
        return reg_courses;
    }

    void regcourse(Course cr) {
        reg_courses.push_back(cr);
    }

    void display_registered_courses() {
        cout << "The registered courses are: " << endl;
        for (int i = 0; i < reg_courses.size(); i++) { 
            cout << reg_courses[i].course_name << endl;
        }
        cout << "\n";
    }

    void displayinfo() override {
    cout << "Student Name: " << name << endl;
    cout << "Student ID: " << id << endl;
    cout << "Year of study: " << yearofstudy << endl;
    cout << "Department: " << department << endl;
    display_registered_courses();
}

    void drop_course(int course_id) {
        bool found = false;
        for (int i = 0; i < reg_courses.size(); i++) {
            if (reg_courses[i].course_id == course_id) {
                reg_courses.erase(reg_courses.begin() + i);
                cout << "Course with ID: " << course_id << " dropped successfully." << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Course not found!" << endl;
        }
    }
};





















// Instructor class derived from Person
class Instructor : public Person {
    private:
    vector<Course> taught_courses;
    vector<Student> taught_students;

    public:
    Instructor(string n, int i) : Person(n, i) {
    }
    // methode to add a course.
    void add_Course(int id, string name, int max_students) {
        Course new_course(id, name, max_students);
        taught_courses.push_back(new_course);
        cout << "Course \"" << name << "\" with max students " << max_students << " added successfully." << endl;
    }
    // methode to remove a course by id.
    void remove_course(int course_id) {
        bool found = false;
        for (int i = 0; i < taught_courses.size(); i++) {
            if (taught_courses[i].course_id == course_id) {
                cout << "Course \"" << taught_courses[i].course_name << "\" removed successfully." << endl;
                taught_courses.erase(taught_courses.begin() + i);
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Course with ID " << course_id << " not found." << endl;
        }
    }
        // to display tought courses.
    void display_taught_courses() {
        cout << "Courses taught by " << name << ":" << endl;
        for (int i = 0; i < taught_courses.size(); i++) {
            taught_courses[i].show_course_info();
        }
    }
    // methode to display all data for instructor.
    void displayinfo() override {
        cout << "Instructor info:" << endl;
        cout << "Instructor Name: " << name << endl;
        cout << "Instructor ID: " << id << endl;
        display_taught_courses();
    }
    vector<Course> get_taught_courses() {
    return taught_courses;
}
vector<Student> get_taught_students() {
    return taught_students;
}
void add_student(const Student& s) {
    taught_students.push_back(s);
}
void display_enrolled_students() {
        cout << "Students enrolled in courses taught by " << name << ":\n";
        if (taught_students.empty()) {
            cout << "No students enrolled yet.\n";
        } else {
            for (auto student : taught_students) {
                cout << "- " << student.getname() << " (ID: " << student.getid() << ")\n";
            }
        }
        cout << "------------------------------------\n";
}


};





// function to write studentdata inside a txt
void write_student_data(Student& n1) {
    ofstream file("Student data.txt");
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    file << "Student Info\n";
    file << "ID: " << n1.getid() << "\n";
    file << "Name: " << n1.getname() << "\n";
    file << "Year of Study: " << n1.get_year_of_study() << "\n";
    file << "Department: " << n1.get_department() << "\n";
    file << "Registered Courses:\n";
    vector<Course> courses = n1.get_reg_courses();
    for (auto i = 0; i < courses.size(); ++i) {
        file << "- " << courses[i].course_name << " (ID: " << courses[i].course_id << ")\n";
    }
    file << "-----------------------------\n";
    file.close();
}







// function to write Courses data inside a txt
void Write_courses_data(Course& c){
    ofstream file("Courses data.txt");
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }

    file << "Course Info:\n";
    file << "ID: " << c.course_id << "\n";
    file << "Name: " << c.course_name << "\n";
    file << "Max Students: " << c.Max_students << "\n";
    file << "Current Students: " << c.Current_students << "\n";
    file << "-----------------------------\n";
    file.close();
}









// Function to call student menu
void studentMenu(Student& student, Instructor& instructor) {
    int choice;
    cout <<"---------------------------------------------------" << endl;
    do {
        cout << "\nStudent Menu:" << endl;
        cout << "1. Display Info" << endl;
        cout << "2. Register a Course" << endl;
        cout << "3. Drop a Course" << endl;
        cout << "4. Display Registered Courses" << endl;
        cout << "5. write student data on txt file" << endl;
        cout << "6. write Registered Courses Data on a txt file" << endl;
        cout << "7. Return" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        ///////////
if (cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Please enter a valid number." << endl;
    continue;
}
        if (choice < 1 || choice > 8) {
            cout << "Invalid choice. Please enter a number between 1 and 8." << endl;
            continue;
        }

        try {
            switch (choice) {
                case 1:
                    student.displayinfo();
                    break;
                case 2: {
                    int id;
                    string name;
                    int max_students;
                    cout << "Enter the course ID: ";
                    cin >> id;
                    cout << "Enter the course name: ";
                    cin >> name;
                    cout << "Enter the maximum number of students: ";
                    cin >> max_students;
                    Course new_course(id, name, max_students);
                    student.regcourse(new_course);
                    cout << "Course registered successfully!" << endl;
                    instructor.add_student(student);
                    break;
                }
                case 3: {
                    int id;
                    cout << "Enter the course ID to drop: ";
                    cin >> id;
                    student.drop_course(id);
                    break;
                }
                case 4:
                    student.display_registered_courses();
                    break;
                case 5:
                    write_student_data(student);
                    cout << "Student data has been wrote on txt file" << endl;
                    break;
                case 6: {
                    vector<Course> courses = student.get_reg_courses();
                    for (auto& c : courses) {
                        Write_courses_data(c);
                    }
                    cout << "Registered courses data has been wrote on txt file." << endl;
                    break;
                }
                case 7:
                    return;
                case 8:
                    cout << "Thanks for using our program!" << endl;
                    exit(0);
            }
        } catch (const char* msg) {
            cout << "Error: " << msg << endl;
        }
    } while (choice != 8);
}








// function to write Instructor data in a txt.
void write_Instructor_data(Instructor& I1 ){
    ofstream file("Instructor data.txt");
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    file << "Instructor info: \n";
    file << "ID:" << I1.getid() << "\n";
    file << "Name:" << I1.getname() <<"\n";
    file << "Courses taught by " << I1.getname() << " are:\n";
    vector<Course> IC = I1.get_taught_courses();
    for (auto i = 0 ; i < IC.size() ; ++i){
    file << "- " << IC[i].course_name << " (ID: " << IC[i].course_id << ")\n";
    }
    
    file << "-----------------------------------";
    file.close();
}








// fun for Instructor menu
void Instructor_Menu(Instructor& instructor) {
    int choice;
    cout << "----------------------------------------" << endl;
    do {
        cout << "\nInstructor Menu:" << endl;
        cout << "1. Display Info." << endl;
        cout << "2. Add a Course." << endl;
        cout << "3. Remove a Course." << endl;
        cout << "4. Display Taught Courses." << endl;
        cout << "5. Write Instructor data in a txt file." << endl;
        cout << "6. Write Taught Courses Data in a txt file." << endl;
        cout << "7. Return." << endl;
        cout << "8. Display Enrolled Students.\n";
        cout << "9. Exit." << endl;
        cout << "Enter your choice: ";
        cin >> choice;
if (cin.fail()){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Please enter a valid number." << endl;
    continue;
}
        if (choice < 1 || choice > 9) {
            cout << "Invalid choice. Please enter a number between 1 and 9." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                instructor.displayinfo();
                break;
            case 2: {
                int id;
                string name;
                int max_students;
                cout << "Enter the course ID: ";
                cin >> id;
                cout << "Enter the course name: ";
                cin >> name;
                cout << "Enter the maximum number of students: ";
                cin >> max_students;
                instructor.add_Course(id, name, max_students);
                
                break;
            }
            case 3: {
                int id;
                cout << "Enter the course ID to remove: ";
                cin >> id;
                instructor.remove_course(id);
                break;
            }
            case 4:
                instructor.display_taught_courses();
                break;
            case 5:
                write_Instructor_data(instructor);
                cout << "data has been wrote in a txt file" << endl;
                break;
            case 6: {
                vector<Course> courses = instructor.get_taught_courses();
                for (auto& c : courses) {
                    Write_courses_data(c);
                }
                cout << "Taught courses data wrote on txt file successfully!" << endl;
                break;
            }
            case 7:
                return; 
                case 8:
        instructor.display_enrolled_students();
            break;
            case 9:
                cout << "Thanks for using our program!" << endl;
                exit(0); 
        }
    } while (choice != 9);
    
}














// main function
int main() {

    Instructor instructor1("KHALED ALAJAMI", 67890);
    try {
        do {

        cout << "------------------------------------------------" << endl;
        cout << "Welcome to the registration system:" << endl;
        cout << "Choose your role by number:" << endl;
        cout << "1- Student" << "  " << "\n2- Instructor" << "  " << "\n3- Exit\n" << endl;
        cin >> role;
        if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number." << endl;
            continue;
}


        if (role < 1 || role > 3) {
            cout << "Invalid input. Please enter 1 for Student, 2 for Instructor, or 3 to Exit." << endl;
            continue;
        }

        if (role == 1) {
            Course math(101, "Math", 30);
            Course physics(102, "Physics", 25);
            Student student("Tamer Alomari", 12345, 2, "Computer Science", {math, physics});
        studentMenu(student, instructor1);
        } else if (role == 2) {
            instructor1.add_Course(102 ,"Math" , 22);
            instructor1.add_Course(103 , "Pyisics" , 23);
            instructor1.add_Course(104 , "OOp" , 25);
            instructor1.add_Course(105 , "Data structure" , 25);
        Instructor_Menu(instructor1);
        } else if (role == 3) {
            cout << "Thank you for using our program!" << endl;
            break;
        }
    } while (role != 3);
   
    }
    catch (const char* msg) {
        cout << "Error: " << msg << endl;
    }

    
    return 0;
}
