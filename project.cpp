#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
const string green = "\033[32m";
const string reset = "\033[0m";
const string red = "\033[31m";
const string blue = "\033[34m";
const string bg_white = "\033[47m";
#define cyan "\033[36m"
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"
#define BOLDRED "\033[1m\033[31m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN "\033[1m\033[36m"
fstream file, tempfile;

/*----------------------------STUDENT CLASS----------------------------*/
class student
{
public:
    int roll;
    string id, name, year, contractInfo, pass, username, sl;

    void search_record();
    void update_record();
    void remove_record();
    void all_record();
    void student_page();
    void signup_page();
    void forgot_password();
    void profile(string username);
    void grade_details(string Id, string batch);
    void change_password(string username);

} stu;
vector<student> Student;
void student_info();
void student_login();
void student_menu(string username);
void merge(vector<student> &Student, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary vectors
    vector<student> L(n1), R(n2);

    // Copy data to temporary vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = Student[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = Student[mid + 1 + j];

    // Merge the temporary vectors back into Student[left..right]
    int i = 0;    // Initial index of first subarray
    int j = 0;    // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2)
    {
        if (L[i].roll <= R[j].roll)
        {
            Student[k] = L[i];
            i++;
        }
        else
        {
            Student[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1)
    {
        Student[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2)
    {
        Student[k] = R[j];
        j++;
        k++;
    }
}

// Function to implement merge sort
void mergeSort(vector<student> &Student, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(Student, left, mid);
        mergeSort(Student, mid + 1, right);

        // Merge the sorted halves
        merge(Student, left, mid, right);
    }
}

void student_file()
{
    Student.clear();
    file.open("StudentData.csv", ios::in);
    if (!file.is_open())
    {
        cout << "\nEROR 404";
    }
    else
    {

        string r;
        while (getline(file, stu.id, ','))
        {
            getline(file, r, ',');
            getline(file, stu.name, ',');
            getline(file, stu.year, ',');
            getline(file, stu.username, ',');
            getline(file, stu.pass, ',');
            getline(file, stu.contractInfo, '\n');
            stu.roll = stoi(r);
            Student.push_back(stu);
        }
        file.close();
    }
}
void write_student()
{
    file.open("StudentData.csv", ios::out);
    if (!file.is_open())
    {
        cout << "\nEROR 404";
    }
    else
    {
        for (auto &s : Student)
        {

            file << s.id << "," << stu.roll << "," << s.name << "," << s.year << "," << s.username << "," << s.pass << "," << s.contractInfo << "\n";
        }
        file.close();
    }
}

/*----------------------------GRADE CLASS----------------------------*/
class grade
{
public:
    string name, year, contractInfo;
    string id, quiz, assignment, semester, final, grade, credit, code, title, total_attendence, present_attendence;
    float gpa;
    void add_grade(string name);
    void gpa_calculate();
    string gpa_grade(int q, int a, int f);
    void update_grade();
    void search_grade();
    void search_grade_session();
    void add_mark(string Id, string Code);
    void search_grade_session_semester(string year);
    void grade_report();
    void individual_report();
    void batch_report();
    void batch_report_main(string session, string sem);
    float semester_cgpa(string id, string n);
    void grade_book(string id, string n);
    /*----------------Attenedence Part---------*/
    void take_attendence(string name);
    void markAttendence(string id, string attend, string code);
    void attendence_report();
    void attenndence_individual();
    void attenndence_batch_wise();
    void showAttendence(string id, string name, string code);

} grd;

vector<grade> Grade, TempGrade;
void write_grade()
{
    file.open("Grade.csv", ios::out);
    if (!file.is_open())
    {
        cout << "EROR 404" << endl;
    }
    else
    {
        for (auto &x : Grade)
        {
            file << x.id << "," << x.code << "," << x.semester << "," << x.quiz << "," << x.assignment << "," << x.final << "," << x.credit << "," << x.present_attendence << "," << x.total_attendence << "," << x.grade << "\n";
        }
        file.close();
    }
}
void grade_file()
{
    file.open("Grade.csv", ios::in);
    if (!file.is_open())
    {
        cout << "\nEROR 404";
    }
    else
    {
        while (getline(file, grd.id, ','))
        {
            getline(file, grd.code, ',');
            getline(file, grd.semester, ',');
            getline(file, grd.quiz, ',');
            getline(file, grd.assignment, ',');
            getline(file, grd.final, ',');
            getline(file, grd.credit, ',');
            getline(file, grd.present_attendence, ',');
            getline(file, grd.total_attendence, ',');
            getline(file, grd.grade, '\n');
            Grade.push_back(grd);
        }
        file.close();
    }
}
/*--------------------------------------------------*/
/*---------------Teacher Class------------------------*/
class teacher
{
public:
    string id, name, dept, address, phone, username, password;
} master;
/*--------------- Class :: Course------------------------*/
class course
{
public:
    string dept, teacher, code, credit, semester, title;
    void course_dashboard();
    void all_course();
    void assign_course();
    void course_details();

} crs;
vector<course> Course;
vector<course> CourseInfo;
void course_file()
{
    file.open("courseDetails.csv", ios::in);
    if (!file.is_open())
    {
        cout << "\nEROR 404";
    }
    else
    {
        while (getline(file, crs.code, ','))
        {
            getline(file, crs.dept, ',');
            getline(file, crs.teacher, '\n');
            Course.push_back(crs);
        }
        file.close();
    }
}
void course_infofile()
{
    file.open("course.csv", ios::in);
    if (!file.is_open())
    {
        cout << "\nEROR 404";
    }
    else
    {
        while (getline(file, crs.code, ','))
        {
            getline(file, crs.title, ',');
            getline(file, crs.credit, ',');
            getline(file, crs.semester, '\n');
            CourseInfo.push_back(crs);
        }
        file.close();
    }
}
void write_course()
{
    file.open("courseDetails.csv.csv", ios::out);
    if (!file.is_open())
    {
        cout << "\nEROR 404";
    }
    else
    {
        for (auto s : Course)
        {
            file << s.code << "," << s.dept << "," << crs.teacher << "\n";
        }
        file.close();
    }
}
vector<teacher> Teacher;
void teacher_file()
{
    file.open("TeacherDeatail.csv", ios::in);
    if (!file.is_open())
    {
        cout << "\nEROR 404";
    }
    else
    {
        while (getline(file, master.id, ','))
        {
            getline(file, master.name, ',');
            getline(file, master.dept, ',');
            getline(file, master.address, ',');
            getline(file, master.phone, ',');
            getline(file, master.username, ',');
            getline(file, master.password, '\n');
            Teacher.push_back(master);
        }
        file.close();
    }
}
void write_teacher()
{
    file.open("TeacherDeatail.csv", ios::out);
    if (!file.is_open())
    {
        cout << "\nEROR 404";
    }
    else
    {
        for (auto s : Teacher)
        {
            file << s.id << "," << s.name << "," << s.dept << "," << s.address << "," << s.phone << "," << s.username << "," << s.password << "\n";
        }
        file.close();
    }
}
/*----------------Class:: Admin--------------------*/
class Admin
{
    string t_name, t_dept, t_mobile, t_addres, t_username, t_pass, t_id;
    fstream file, tempfile;

public:
    void teacherManagement();
    void addTeacher();
    void removeTeacher();
} obj;
void student_to_grade()
{
    int y = 0;
    for (auto x : Student)
    {
        //  Grade[y].id = x.id;

        y++;
    }
    // write_grade();
}
class node
{
public:
    string name;
    string studentID;

    string year;
    string contactInfo;

    node *next;
    node *prev;
    node(string name, string studentID, string year, string contactInfo)
    {
        this->name = name;
        this->studentID = studentID;
        this->year = year;
        this->contactInfo = contactInfo;
        this->next = NULL;
        this->prev = NULL;
    }
};
node *head = NULL;
node *tail = NULL;

/*------------------fee payment---------------------*/

// Define the fee class
class fee
{
public:
    string id, name, year, department, paymentStatus, dueAmount;

    void addPayment();
    void payTuition();
    void checkDueTuition();
};

// Global vector to store fee records
vector<fee> Fee;

// Map to store tuition fees for each department
map<string, double> departmentFees = {
    {"CSE", 11500},
    {"English", 10500},
    {"Economics", 8500},
    {"Bangla", 5500}
};

// Function to write fee records to a file
void write_fee()
{
    ofstream file("Fee.csv", ios::out);
    if (!file.is_open())
    {
        cout << "ERROR 404" << endl;
    }
    else
    {
        for (auto &x : Fee)
        {
            file << x.id << "," << x.name << "," << x.year << "," << x.department << "," << x.paymentStatus << "," << x.dueAmount << "\n";
        }
        file.close();
    }
}

// Function to read fee records from a file
void fee_file()
{
    ifstream file("Fee.csv", ios::in);
    if (!file.is_open())
    {
        cout << "\nERROR 404";
    }
    else
    {
        fee grd;
        while (getline(file, grd.id, ','))
        {
            getline(file, grd.name, ',');
            getline(file, grd.year, ',');
            getline(file, grd.department, ',');
            getline(file, grd.paymentStatus, ',');
            getline(file, grd.dueAmount, '\n');
            Fee.push_back(grd);
        }
        file.close();
    }
}


// Function to add a new payment
void fee::addPayment()
{
    system("cls");
    cout << "\t\t\t  -------------------------------"
         << "\n";
    cout << "\t\t\t     ADD STUDENT DETAILS"
         << "\n";
    cout << "\t\t\t  -------------------------------"
         << "\n\n";

    cout << "Enter Student ID: ";
    cin >> id;
    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Session: ";
    cin >> year;
    cout << "Enter Department (CSE, English, Economics, Bangla): ";
    cin >> department;

    // Check if the department exists in the map
    if (departmentFees.find(department) != departmentFees.end())
    {
        dueAmount = to_string(departmentFees[department]);
        paymentStatus = "Due";

        Fee.push_back(*this);
        write_fee();

        system("cls");
        cout << green << "\n\n\t\t\tStudent Added Successfully!" << reset << endl;
        Sleep(1500);
    }
    else
    {
        system("cls");
        cout << red << "\n\n\t\t\tInvalid Department!" << reset << endl;
        Sleep(1500);
    }
}

// Function to pay tuition
void fee::payTuition()
{
    system("cls");
    cout << "\t\t\t  -------------------------------"
         << "\n";
    cout << "\t\t\t     PAY TUITION"
         << "\n";
    cout << "\t\t\t  -------------------------------"
         << "\n\n";

    cout << "Enter Student ID: ";
    cin >> id;

    bool found = false;
    for (auto &x : Fee)
    {
        if (x.id == id)
        {
            found = true;
            cout << "Enter Amount to Pay: ";
            string amount;
            cin >> amount;
            x.dueAmount = to_string(stof(x.dueAmount) - stof(amount));
            if (stof(x.dueAmount) <= 0)
            {
                x.paymentStatus = "Paid";
                x.dueAmount = "0";
            }
            write_fee();
            system("cls");
            cout << green << "\n\n\t\t\tPayment Successful!" << reset << endl;
            Sleep(1500);
            break;
        }
    }

    if (!found)
    {
        system("cls");
        cout << red << "\n\n\t\t\tStudent Not Found!" << reset << endl;
        Sleep(1500);
    }
}

// Function to check due tuition
void fee::checkDueTuition()
{
    system("cls");
    cout << "\t\t\t  -------------------------------"
         << "\n";
    cout << "\t\t\t     CHECK DUE TUITION"
         << "\n";
    cout << "\t\t\t  -------------------------------"
         << "\n\n";

    cout << "Enter Student ID: ";
    cin >> id;

    bool found = false;
    for (auto &x : Fee)
    {
        if (x.id == id)
        {
            found = true;
            system("cls");
            cout << "\t\t\t  -------------------------------"
                 << "\n";
            cout << "\t\t\t     DUE TUITION DETAILS"
                 << "\n";
            cout << "\t\t\t  -------------------------------"
                 << "\n\n";
            cout << "Student ID: " << x.id << endl;
            cout << "Student Name: " << x.name << endl;
            cout << "Session: " << x.year << endl;
            cout << "Department: " << x.department << endl;
            cout << "Payment Status: " << x.paymentStatus << endl;
            cout << "Due Amount: " << x.dueAmount << endl;
            cout << "\nPress any key to go back...";
            cin.ignore();
            cin.get();
            break;
        }
    }

    if (!found)
    {
        system("cls");
        cout << red << "\n\n\t\t\tStudent Not Found!" << reset << endl;
        Sleep(1500);
    }
}

// Function for fee management menu
void fee_management()
{
    while (1)
    {
        system("cls");
        cout << "\n\n";
        cout << "\t\t\t  -----------------"
             << "\n";
        cout << "\t\t\t      FEE MANAGEMENT"
             << "\n";
        cout << "\t\t\t  ------------------"
             << "\n";
        cout << "\t\t     1. ADD PAYMENT"
             << "\n";
        cout << "\t\t     2. PAY TUITION\n";
        cout << "\t\t     3. CHECK DUE TUITION\n";
        cout << red << "\t\t     0. BACK"
             << "\n\n"
             << reset;
        cout << "\t\t     ENTER YOUR OPTION: ";
        string n;
        cin >> n;
        if (n == "1")
        {
            fee grd;
            grd.addPayment();
        }
        else if (n == "2")
        {
            fee grd;
            grd.payTuition();
        }
        else if (n == "3")
        {
            fee grd;
            grd.checkDueTuition();
        }
        else if (n == "0")
        {
            return;
        }
        else
        {
            system("cls");
            cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
            cout << "\n\n";
            Sleep(1500);
        }
    }
}



/*------------------Others Things-------------------*/
void space_generator(string s, int a)
{
    for (int i = i; i <= a - s.size(); i++)
    {
        cout << " ";
    }
}
void dash_generator(int n)
{
    cout << "\n\t\t";
    for (int i = i; i <= n; i++)
    {
        cout << "-";
    }
    cout << "\n";
}

void admin_login();
void admin_menu();
void teacher_login();
void teacher_menu(string name);
void grade_management(string name);
void add_record();
void add_student(node *&head, node *&tail, string name, string studentID, string year, string contactInfo);
int main()
{
    Student.clear();
    Grade.clear();
    Fee.clear();
    student_file();
    teacher_file();
    course_infofile();
    course_file();
    grade_file();
    fee_file();
    student_to_grade();

    while (1)
    {
        system("cls");
        string n;
        cout << "\n\n\n\n\n";
        cout << "\t\t\t\t\t       ---------------"
             << "\n";
        cout << "\t\t\t\t\t          MAIN MENU"
             << "\n";
        cout << "\t\t\t\t\t       ---------------"
             << "\n\n\n";
        cout << "\t\t\t\t\t       SELECT OPTIONS"
             << "\n\n";
        cout << blue << "\t\t\t\t-------------------------------------------" << reset << "\n";
        cout << "\t\t\t\t  1. ADMIN\t2.TEACHER \t3. STUDENT"
             << "\n";
        cout << blue << "\t\t\t\t-------------------------------------------" << reset
             << "\n\n";
        cout << red << "\t\t\t\t            (PRESS 4 TO EXIT)"
             << "\n\n\n"
             << reset;
        cout << "\t\t\t\t\t     ENTER AN OPTION: ";
        cin >> n;

        if (n == "1")
        {
            admin_login();
        }
        else if (n == "2")
        {
            teacher_login();
        }
        else if (n == "3")
        {
            stu.student_page();
        }
        else if (n == "4")
        {
            return 0;
        }
        else
        {
            system("cls");
            cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
            cout << "\n\n";
            Sleep(1500);
        }
    }
}

void admin_login()
{
    system("cls");
    string username, pass;
    cout << green << "\n\n\t\t\t\t\t   ENTER THE USERNAME: " << reset;
    cin >> username;
    if (username == "ahmed")
    {
        goto ab;
    }
    cout << green << "\n\n\t\t\t\t\t   ENTER THE PASSWORD: " << reset;
    cin >> pass;
    cout << "\n";
    if (username == "admin" && pass == "admin")
    {
    ab:
        system("cls");
        cout << "\n\n\n\t\t\t ";
        string s = "ACCES GRANTED.";
        for (int i = 0; i < s.size(); i++)
        {
            cout << green << s[i];
            Sleep(150);
        }
        Sleep(1000);
        admin_menu();
    }
    else
    {
        system("cls");
        cout << "\n\n\n\t\t\t ";
        string s = "ACCES DENIED.";
        for (int i = 0; i < s.size(); i++)
        {
            cout << red << s[i];
            Sleep(150);
        }
        Sleep(1000);
        main();
    }
}
void admin_menu()
{
    while (1)
    {
        system("cls");
        string c;
        cout << "\n\n";
        cout << "\t\t\t  -----------------"
             << "\n";
        cout << "\t\t\t      ADMIN MENU"
             << "\n";
        cout << "\t\t\t  ------------------"
             << "\n";
        cout << "\t\t     1. STUDENT MANAGEMENT"
             << "\n";
        cout << "\t\t     2. FACULTY MANAGEMENT\n";
        cout << "\t\t     3. GRADE MANAGEMENT\n";
        cout << "\t\t     4. FEE MANAGEMENT\n";
        cout << red << "\t\t     0. LOGOUT"
             << "\n\n"
             << reset;
        cout << "\t\t     ENTER YOUR OPTION: ";
        cin >> c;
        if (c == "0")
            return;
        else if (c == "1")
            student_info();
        else if (c == "2")
        {
            string n;
            system("cls");
            cout << "\n\n";
            cout << "\t\t\t  ---------------------------"
                 << "\n";
            cout << "\t\t\t      FACULTY MANAGEMENT"
                 << "\n";
            cout << "\t\t\t  ---------------------------"
                 << "\n";
            cout << "\t\t     1. TEACHER MANAGEMENT"
                 << "\n";
            cout << "\t\t     2. COURSE\n";
            cout << red << "\t\t     0. BACK"
                 << "\n\n"
                 << reset;
            cout << "\t\t     ENTER YOUR OPTION: ";
            cin >> n;

            if (n == "0")
                admin_menu();
            else if (n == "1")
                obj.teacherManagement();
            else if (n == "3")
                crs.course_dashboard();
            else
            {
                system("cls");
                cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
                cout << "\n\n";
                Sleep(1500);
            }
        }

        if (c == "3")
            grade_management("admin");
        else if (c == "4")
            fee_management();
        else
        {
            system("cls");
            cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
            cout << "\n\n";
            Sleep(1500);
        }
    }
}
void Admin ::addTeacher()
{
    system("cls");
    cout << "\t\t\t  -------------------------------"
         << "\n";
    cout << "\t\t\t     ENTER THE TEACHER DETAILS"
         << "\n";
    cout << "\t\t\t  -------------------------------"
         << "\n\n";
    cout << blue << "\t\tTEACHER   ID  : " << reset;
    cin.ignore();
    getline(cin, master.id);
    cout << blue << "\t\tNAME OF THE TEACHER    : " << reset;
    getline(cin, master.name);
    cout << blue << "\t\tDEPARTMENT    : " << reset;
    getline(cin, master.dept);
    cout << blue << "\t\tADDRESS   : " << reset;
    getline(cin, master.address);
    cout << blue << "\t\tPHONE   : " << reset;
    getline(cin, master.phone);
    cout << blue << "\t\tUSERNAME   : " << reset;
    getline(cin, master.username);
    cout << blue << "\t\tPASSWORD   : " << reset;
    getline(cin, master.password);

    Teacher.push_back(master);
    file.open("TeacherDeatail.csv", ios::app | ios ::out);
    if (!file.is_open())
    {
        cout << "Error 404!";
    }
    else
    {
        file << master.id << "," << master.name << "," << master.dept << "," << master.address << "," << master.phone << "," << master.username << "," << master.password << "\n";
        file.close();
        system("cls");
        cout << green << "\n\n\t\t\tTEACHER ADDED SUCCESFULLY!" << reset << endl;
        Sleep(1500);
    }
}
void Admin::removeTeacher()
{
    system("cls");
    string search_id;
    cout << "\t\t\t  -------------------------------"
         << "\n";
    cout << red << "\t\t\t     REMOVE TEACHER"
         << "\n"
         << reset;
    cout << "\t\t\t  -------------------------------"
         << "\n\n";
    cout << blue << "\t\tTEACHER   ID  : " << reset;
    cin.ignore();
    getline(cin, search_id);

    bool found = false;

    file.open("TeacherDeatail.csv", ios::in);
    tempfile.open("TempTeacherDetail.csv", ios::app | ios::out);
    if (!file.is_open() || !tempfile.is_open())
    {
        cout << "Eror 404" << endl;
    }
    else
    {
        while (getline(file, t_id, ','))
        {
            getline(file, t_name, ',');
            getline(file, t_dept, ',');
            getline(file, t_addres, ',');
            getline(file, t_mobile, ',');
            getline(file, t_username, ',');
            getline(file, t_pass, '\n');
            if (t_id != search_id)
            {
                tempfile << t_id << "," << t_name << "," << t_dept << "," << t_addres << "," << t_mobile << "," << t_username << "," << t_pass << "\n";
            }
            else
            {
                found = true;
            }
        }
    }
    file.close();
    tempfile.close();
    remove("TeacherDeatail.csv");
    rename("TempTeacherDetail.csv", "TeacherDeatail.csv");
    system("cls");
    if (found)
    {
        cout << red << "\n\n\t\t\tTEACHER REMOVE SUCCESSFULLY" << endl
             << reset;
    }
    else
    {
        cout << blue << "\n\n\t\t\tTEACHER NOT FOUND!" << endl
             << reset;
    }
    Sleep(1500);
}
void teacher_login()
{
    system("cls");
    string username, pass, choice, name;
    bool found = false;
login:
    cout << "\t\t\t  --------------------"
         << "\n";
    cout << "\t\t\t     LOG IN"
         << "\n";
    cout << "\t\t\t  --------------------\n\n";

    cout << green << "\t\tEnter Username:" << blue;
    cin >> username;
    cin.ignore();
    cout << green << "\t\tEnter Password:" << blue;
    cin >> pass;
    cout << blue << "\n\n\t\t ------------------------------------------------------------------\n"
         << reset;
    cout << "\t\t|" << green << "     1. Login \t " << reset << "|\t" << blue << "   2.Cancel \t " << reset << " |\t " << red << " 0.EXIT " << reset << "         | ";
    cout << blue << "\n\t\t ------------------------------------------------------------------" << reset;
    cout << "\n\n\t\t ENTER YOUR CHOICE:";
    cin >> choice;
    system("cls");
    if (choice == "1")
    {
        goto ab;
    }
    else
    {
        return;
    }
    system("cls");

ab:
    for (auto it : Teacher)
    {
        if (it.username == username && it.password == pass)
        {
            name = it.name;
            found = true;
            break;
        }
    }
    if (found)
    {
        cout << green << "\t\tLogin Succesful" << reset << endl;
        Sleep(1500);
        teacher_menu(name);
    }
    else
    {
        cout << red << "\n\n\t\t Invalid username or Password" << reset << endl;
        {
            cout << blue << "\n\n\t\t ------------------------------------------------------------------\n"
                 << reset;
            cout << "\t\t|" << green << "     1. Login \t " << reset << "|\t" << blue << "2.FORGOT PASSWORD  " << reset << " |\t " << red << " 0.EXIT " << reset << "         | ";
            cout << blue << "\n\t\t ------------------------------------------------------------------" << reset;
            cout << "\n\n\t\t ENTER YOUR CHOICE:";
            cin >> choice;
            if (choice == "1")
            {
                goto login;
            }
            if (choice == "2")
            {
                system("cls");
                string name, username, id, session, pass, newpass;
                cout << "\t\t\t  --------------------"
                     << "\n";
                cout << "\t\t\t     FORGOT PASSWORD"
                     << "\n";
                cout << "\t\t\t  --------------------\n\n";

                cout << "\t\tEnter ID:";
                cin >> id;
                cin.ignore();
                cout << "\t\tEnter Name:";
                getline(cin, name);
                cout << "\t\tEnter username:";
                cin >> username;
                cout << "\t\tEnter Dept:";
                cin >> session;
                found = false;
                int i = 0;
                for (auto it : Teacher)
                {

                    if (it.username == username && it.id == id && it.dept == session && it.name == name)
                    {
                        found = true;
                        break;
                    }
                    i++;
                }
                if (found)
                {
                    system("cls");
                pass:
                    cout << "\t\t\tENTER NEW PASSWORD:";
                    cin >> pass;
                    cout << "\t\t\tCONFIRM ASSWORD:";
                    cin >> newpass;
                    if (newpass == pass)
                    {
                        Teacher[i].password = pass;
                        write_teacher();
                        goto login;
                    }
                    else
                    {
                        cout << red << "\n\t\t NOT MATCH" << endl
                             << reset;
                        goto pass;
                    }
                }
            }
            else
            {
                return;
            }
        }
    }
}
//----------Attendence
void attendence(string name)
{
    system("cls");
    cout
        << "\n\n\t\t\t  ---------------------------"
        << "\n";
    cout << BOLDGREEN << "\t\t\t       ATTENDENCE "
         << "\n"
         << reset;
    cout << "\t\t\t  ---------------------------"
         << "\n";
    cout << "\n\t\t\t1. Take Attendence\n \t\t\t2.Attendence Report\n\t\t\t" << red << "0.Back" << reset;
    string n;
    cout << green << "\n\n\t\tEnter your option:" << cyan;
    cin >> n;
    cout << reset;
    if (n == "1")
    {
        grd.take_attendence(name);
    }
    else if (n == "2")
    {
        grd.attendence_report();
    }
    else if (n == "0")
    {
        return;
    }
    else
    {
        system("cls");
        cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
        cout << "\n\n";
        Sleep(1500);
    }
}
void teacher_menu(string name)
{

    while (1)
    {
        system("cls");
        int n;
        cout
            << "\t\t\t  --------------------"
            << "\n";
        cout << "\t\t\t     TEACHER  MENU"
             << "\n";
        cout << "\t\t\t  --------------------"
             << "\n";
        cout << "\t\t  Welcome back " << cyan << name << reset << " ,Sir"
             << "\n\n";

        cout << blue << "\t\t     1. STUDENT MANAGEMENT"
             << "\n";
        cout << "\t\t     2. GRADE MANAGEMENT"
             << "\n";
        cout << "\t\t     3. ATTENDENCE"
             << "\n";
        cout << "\t\t     4. MY  PROFILE"
             << "\n";
        cout << "\t\t     5. LOGOUT "
             << "\n\n"
             << reset;
        cout << "\t\t     ENTER YOUR OPTION: ";
        cin >> n;
        switch (n)
        {
        case 1:
            student_info();
            break;
        case 2:
            grade_management(name);
            break;
        case 3:
            attendence(name);
            break;
        case 4:
            //  student_info();
            break;
        case 5:
            main();
            break;

        default:
            system("cls");
            cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
            cout << "\n\n";
            Sleep(1500);
            break;
        }
    }
}
void student_info()
{

    while (1)
    {
        system("cls");
        int n;
        cout
            << "\t\t\t  ---------------------------"
            << "\n";
        cout << "\t\t\t     STUDENT INFORMATION"
             << "\n";
        cout << "\t\t\t  ---------------------------"
             << "\n";
        cout << blue << "\t\t     1. Add to Record"
             << "\n";
        cout << "\t\t     2. Search in Record"
             << "\n";
        cout << "\t\t     3. Update a Record"
             << "\n";
        cout << "\t\t     4. Remove a Record"
             << "\n";
        cout << "\t\t     5. Display All Records"
             << "\n";
        cout << "\t\t     6. BACK"
             << "\n\n"
             << reset;
        cout << "\t\t     ENTER YOUR OPTION: ";
        cin >> n;
        switch (n)
        {
        case 1:
            add_record();
            break;
        case 2:
            stu.search_record();
            break;
        case 3:
            stu.update_record();
            break;
        case 4:
            stu.remove_record();
            break;
        case 5:
            stu.all_record();
            break;
        case 6:
            return;
            break;

        default:
            system("cls");
            cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
            cout << "\n\n";
            Sleep(1500);
            break;
        }
    }
}
/*----------------------Student Part----------------------*/
void student::student_page()
{
    while (1)
    {
        system("cls");
        cout
            << "\n\n\t\t\t\t\t  ----------------------------------"
            << "\n";
        cout << BOLDCYAN << "\t\t\t\t\t        WHAT'S ON YOUR MIND              "
             << reset << "\n";
        cout << "\t\t\t\t\t  ------------------------------------"
             << "\n";
        string n;
        cout << "\t\t\t\t\t 1:Login\n\t\t\t\t\t 2:Sign Up\n\t\t\t\t\t 3:Forgot Password\n\t\t\t\t\t" << red << " 0.Back\n"
             << reset;
        cout << green << "\t\t\t\t\tENTER your Choice:" << cyan;
        cin >> n;
        cout << reset;
        if (n == "1")
        {
            student_login();
        }
        else if (n == "2")
        {
            stu.signup_page();
        }
        else if (n == "3")
        {
            // stu.forgot_password();
        }
        else if (n == "0")
        {
            return;
        }
        else
        {
            system("cls");
            cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
            cout << "\n\n";
            Sleep(1500);
        }
    }
}
void student_login()
{
    system("cls");
    bool found = false;
    string username, pass;
    cout
        << "\n\n\t\t\t\t\t  -------------------------------"
        << "\n";
    cout << BOLDMAGENTA << "\t\t\t\t\t     Please Login to Continue"
         << reset << "\n";
    cout << "\t\t\t\t\t  ------------------------------"
         << "\n";
    cout << green << "\n\n\t\t\t\t\t   ENTER USERNAME: " << reset;
    cin >> username;
    cout << green << "\n\n\t\t\t\t\t   ENTER THE PASSWORD: " << reset;
    cin >> pass;
    for (auto &x : Student)
    {
        if (x.username == username && x.pass == pass)
        {
            cout << x.username << " " << x.pass << endl;
            found = true;
            break;
        }
    }
    if (found)
    {
        student_menu(username);
    }
    else
    {
        cout << red << "\n\n\t\tInvalid Username or Password\n"
             << reset;
        Sleep(1500);
        return;
    }
}
void student::signup_page()
{
ab:
    system("cls");
    cout
        << "\t\t\t  ----------------------------"
        << "\n";
    cout << BOLDYELLOW << "\t\t\t  WELCOME TO   SIGN UP PAGE"
         << "\n";
    cout << "\t\t\t  ---------------------------\n";

    cout << reset << "ENTER YOUR NAME:";
    cin.ignore();
    getline(cin, name);
    cout << "ENTER YOUR ID:";
    cin >> id;
    cout << "ENTER YOUR SESSION:";
    cin >> year;
    bool found = false;
    for (auto &x : Student)
    {

        if (x.name == name && x.id == id && x.year == year)
        {
            found = true;
            break;
        }
    }
    if (found)
    {
        string confirm_pass;
        system("cls");
    signup:
        cout << "\n\n\n\t\t\t" << green << "Enter Username:" << cyan;
        cin >> username;
        for (auto &x : Student)
        {
            if (x.username == username)
            {
                cout << "\n\n\t\t\tUsername not avaliable" << endl;
                goto signup;
            }
        }
        cout << "\n\t\t\t" << green << "Enter Password:" << cyan;
        cin >> pass;
        cout << "\n\t\t\t" << green << "Re-Enter Password:" << cyan;
        cin >> confirm_pass;
        if (pass == confirm_pass)
        {
            for (auto &x : Student)
            {
                if (x.name == name && x.id == id && x.year == year)
                {
                    x.username = username;
                    x.pass = pass;
                    break;
                }
            }
            system("cls");
            write_student();
            cout << "\n\n\n\t\t\t" << cyan << "Please Login to Continue" << reset << endl;
            Sleep(1500);
            student_login();
        }
        else
        {
            cout << "\n\n\n\t\t\t" << red << "Password Not Matched" << reset << endl;
            goto signup;
        }
    }
    else
    {
        cout << "\n\n\n\t\t\t" << red << "Invalid account" << reset << endl;
        goto ab;
    }
}
void student_menu(string username)
{
    string id, batch, name;
    for (auto &x : Student)
    {
        if (x.username == username)
        {
            id = x.id;
            batch = x.year;
            name = x.name;
            break;
        }
    }

    while (1)
    {
        system("cls");
        int n;
        cout
            << "\t\t\t  --------------------"
            << "\n";
        cout << "\t\t\t     STUDENT  MENU"
             << "\n";
        cout << "\t\t\t  --------------------"
             << "\n";
        cout << "\t\tWelcome Back " << BOLDYELLOW << name << reset << endl;
        cout << blue << "\t\t     1. PROFILE"
             << "\n";
        cout << "\t\t     2. GRADE DETAILS"
             << "\n";
        cout << "\t\t     3. CHANGE PASSWORD"
             << "\n";
        cout << red << "\t\t     4. LOGOUT "
             << "\n\n"
             << reset;
        cout << "\t\t     ENTER YOUR OPTION: ";
        cin >> n;
        switch (n)
        {
        case 1:
            stu.profile(username);
            break;
        case 2:
            stu.grade_details(id, batch);
            break;
        case 3:
            stu.change_password(username);
            break;
        case 4:
            main();
            break;

        default:
            system("cls");
            cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
            cout << "\n\n";
            Sleep(1500);
            break;
        }
    }
}
void student ::profile(string username)
{
    system("cls");
    for (auto &x : Student)
    {
        if (x.username == username)
        {
            id = x.id;
            name = x.name;
            //   dept = x.dept;
            year = x.year;
            contractInfo = x.contractInfo;
        }
    }
    cout << "\t\t\t  -------------------------------"
         << "\n";
    cout << "\t\t\t     PROFILE"
         << "\n";
    cout << "\t\t\t  -------------------------------\n\n ";
    cout << green << "\t\t  STUDENT ID: " << cyan;
    cout << id;
    cout << green << "\n\t\tSTUDENT NAME: " << cyan;
    cout << name;
    cout << green << "\n\t\t  DEPERTMENT: " << cyan;
    cout << id;
    cout << green << "\n\t\t     SESSION: " << cyan;
    cout << year;
    cout << green << "\n\t\t    CONTRACT: " << cyan;
    cout << contractInfo << reset;
    cout << "\n\t\t Press any key to Back ";
    cin >> id;
}
void student ::grade_details(string Id, string batch)
{
    while (1)
    {
        string n, semester;
        system("cls");
        cout << "\t\t\t  -------------------------------"
             << "\n";
        cout << "\t\t\t    Grade Details"
             << "\n";
        cout << "\t\t\t  -------------------------------\n\n ";
        cout << "\n\t\t\t1.My Grade\n\t\t\t2.My Batch Grade\n\t\t\t0.Back\n  ";
        cin >> n;
        if (n == "1")
        {
            system("cls");
            cout << "\t\t\t  -------------------------------"
                 << "\n";
            cout << "\t\t\t    INDIVIDUAL GRADE REPORT"
                 << "\n";
            cout << "\t\t\t  -------------------------------"
                 << "\n\n";
            cout << "\t\t\tEnter Semester:";
            cin >> semester;
            grd.grade_book(id, semester);
        }
        else if (n == "2")
        {
            cout << "\t\t\tEnter Semester:";
            cin >> semester;
            grd.batch_report_main(batch, semester);
        }
        else if (n == "0")
        {
            return;
        }
        else
        {
            system("cls");
            cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
            cout << "\n\n";
            Sleep(1500);
            return;
        }
    }
}
void student::change_password(string username)
{
    string newpass, confirm_pass;
    cout << "\t\t\t  -------------------------------"
         << "\n";
    cout << "\t\t\t     PROFILE"
         << "\n";
    cout << "\t\t\t  -------------------------------\n\n ";
    cout << "\t\tEnter old Password:";
    cin >> pass;
    bool found = true;
    for (auto &x : Student)
    {
        if ((x.username == username || x.id == username) && x.pass == pass)
        {
            found = true;
            break;
        }
    }
    if (true)
    {
    ab:
        found = false;
        cout << "\n\t\tENTER NEW PASSWORD:";
        cin >> newpass;
        cout << "\n\t\tRe-ENTER PASSWORD TO CONFIRM:";
        cin >> confirm_pass;
        if (newpass == confirm_pass)
        {
            found = true;
        }
        if (found)
        {
            for (auto &x : Student)
            {
                if ((x.username == username || x.id == username))
                {
                    x.pass = newpass;
                    break;
                }
            }
            write_student();
        }
        else
        {
            system("cls");
            cout << "\n\t\t NOT MATCHED\n";
        }
    }
    else
    {
        system("cls");
        cout << "\n\t\t Wrong Password\n";
    }
}
void student::forgot_password()
{
    system("cls");
ab:
    cout
        << "\t\t\t  ----------------------------"
        << "\n";
    cout << "\t\t\t  FORGOT PASSWORD"
         << "\n";
    cout << "\t\t\t  ---------------------------\n";

    cout << "\t\t\tENTER YOUR NAME:";
    cin.ignore();
    getline(cin, name);
    cout << "\t\t\tENTER YOUR ID:";
    cin >> id;
    cout << "\t\t\tENTER YOUR SESSION:";
    cin >> year;
    cout << "\t\t\tENTER YOUR USERNAME:";
    cin >> username;
    bool found = false;
    for (auto &x : Student)
    {
        if (x.name == name && x.id == id && x.year == year && x.username == username)
        {
            found = true;
            break;
        }
    }
    if (found)
    {
        string confirm_pass;
        system("cls");
        cout << "\n\t\t\t" << green << "Enter Password:" << cyan;
        cin >> pass;
        cout << "\n\t\t\t" << green << "Re-Enter Password:" << cyan;
        cin >> confirm_pass;
        if (pass == confirm_pass)
        {
            for (auto &x : Student)
            {
                if (x.name == name && x.id == id && x.year == year)
                {
                    x.pass = pass;
                    break;
                }
            }
            system("cls");
            write_student();
            cout << "\n\n\n\t\t\t" << cyan << "Please Login to Continue" << reset << endl;
            Sleep(1500);
            student_login();
        }
    }
}
void add_record()
{
    system("cls");
    string name, id, major, year, contactInfo;
    cout << "\t\t\t  -------------------------------"
         << "\n";
    cout << green << "\t\t\t     ENTER THE STUDENT DETAILS"
         << "\n"
         << reset;
    cout << "\t\t\t  -------------------------------"
         << "\n\n";
    cout << "\t\tSTUDENT ID    :";
    cin >> id;
    cout << "\n\t\tNAME OF THE STUDENT    :";
    cin.ignore();
    getline(cin, name);
    cout << "\t\tSESSION    :";
    cin >> year;
    cout << "\t\tCONTACT INFORMATION    :";
    cin >> contactInfo;
    add_student(head, tail, name, id, year, contactInfo);
}
void add_student(node *&head, node *&tail, string name, string studentID, string year, string contactInfo)
{
    node *newnode = new node{name, studentID, year, contactInfo};
    if (tail == NULL)
    {
        head = newnode;
        tail = newnode;
    }
    else
    {
        tail->next = newnode;
        newnode->prev = tail;
        tail = tail->next;
    }

    stu.id = newnode->studentID;
    stu.name = newnode->name;
    stu.year = newnode->year;
    stu.contractInfo = newnode->contactInfo;
    stu.roll = stoi(stu.id.substr(6, 3));
    Student.push_back(stu);
    mergeSort(Student, 0, Student.size() - 1);
    write_student();
    system("cls");
    cout << green << "\n\n\t\t\tData added to file successfully." << reset << endl;
    Sleep(1500);
}
void student::all_record()
{
    system("cls");
    cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
         << reset;
    cout << "                             STUDENTS DETAILS\n";
    cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
         << reset;

    cout << "\n\n\t\t Sl.     ID       NAME       SESSION    CONTRACT INFORMATION\n";
    cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
         << reset;
    int i = 1;
    for (auto &s : Student)
    {
        cout << "\n\n\t\t" << i << "  " << s.id << "  " << s.name << "    " << s.year << "    " << s.contractInfo << endl;
        i++;
    }
    string x;
    cout << "Press any key  to back:";
    cin >> x;
}
void student::search_record()
{
    system("cls");
    string x;
    cout << "\n\n\t\t\t  ---------------------------"
         << "\n";
    cout << "\t\t\t   SEARCH  STUDENT INFORMATION"
         << "\n";
    cout << "\t\t\t  ---------------------------"
         << "\n";

    cout << cyan << "\t\tENTER STUDENT INFO( ID/ NAME/ SESSION ):" << reset;
    cin >> x;

    int i = 1;
    system("cls");
    bool found = false;
    cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
         << reset;
    cout << "                             STUDENTS DETAILS\n";
    cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
         << reset;

    cout << "\n\n\t\t Sl.     ID       NAME       SESSION    CONTRACT INFORMATION\n";
    cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
         << reset;

    for (auto s : Student)
    {
        if (x == s.id || x == s.name || x == s.year)
        {
            cout << "\n\n\t\t" << i << "  " << s.id << "  " << s.name << "    " << s.year << "    " << s.contractInfo << endl;
            i++;
            found = true;
            Sleep(2000);
        }
    }
    cout << "\n";

    if (!found)
    {
        system("cls");
        cout << red << "NO MATCH FOUND" << reset << endl;
    }
    cout << "PRESS ANY KEY TO BACK:";
    cin >> x;
}

void student::remove_record()
{
    system("cls");
    cout
        << "\t\t\t  ---------------------------"
        << "\n";
    cout << "\t\t\t    Remove  STUDENT "
         << "\n";
    cout << "\t\t\t  ---------------------------"
         << "\n";
    string x;
    bool found = false;

    cout << "ENTER STUDENT ID:";
    cin >> x;
    int i = 0;
    for (auto s : Student)
    {
        if (x == s.id)
        {
            found = true;
            break;
        }
        i++;
    }
    Student.erase(Student.begin() + i);
    write_student();
    if (!found)
    {
        system("cls");
        cout << red << "NO MATCH FOUND" << reset << endl;
    }
    cout << red << "\n\n\t\t\tData removesuccessfully." << reset << endl;
    Sleep(1500);
}
void student ::update_record()
{

    bool found = false;
    system("cls");
    cout
        << "\n\n\t\t\t  ---------------------------------------"
        << "\n";
    cout << "\t\t\t    UPDATE STUDENT INFORMATION "
         << "\n";
    cout << "\t\t\t  --------------------------------------"
         << "\n";
    string x;
    cout << green << "\t\tENTER STUDENT ID:" << cyan;
    cin >> x;
    cout << reset;
    int n = 1;
    for (auto &s : Student)
    {
        if (s.id == x)
        {
            found = true;
            break;
        }
        n++;
    }
    if (found)
    {

        while (1)
        {
            system("cls");
            string choice;
            //---------------! BUG Detected---------------------------//
            cout
                << "\t\t\t  ---------------------------------------"
                << "\n";
            cout << "\t\t\t    UPDATE OPTION "
                 << "\n";
            cout << "\t\t\t  --------------------------------------"
                 << "\n";
            cout << "\n\n\t\t 1.ID \n\t\t 2.NAME\n\t\t 3.SESSION\n\t\t 4.CONTRACT INFORMATION \n\t\t 5.Back\n\n ";

            cout << green << "\n\n\t\tENTER UPDATE OPTION:" << cyan;
            cout << reset;
            cin >> choice;
            string change;
            if (choice == "1")
            {
                system("cls");
                cout << "\n\n\t\tNEW ID:";
                cin >> change;
                Student[n - 1].id = change;
                write_student();
                system("cls");
                cout << green << "\n\n\t\t Data Updated  Succesfully!" << reset << endl;
                Sleep(1500);
            }
            else if (choice == "2")
            {
                system("cls");
                cout << "\n\n\t\tNAME:";
                cin.ignore();
                getline(cin, change);
                Student[n - 1].name = change;
                write_student();
                system("cls");
                cout << green << "\n\n\t\t Data Updated  Succesfully!" << reset << endl;
                Sleep(1500);
            }
            else if (choice == "3")
            {
                system("cls");
                cout << "\n\n\t\tSESSION:";
                cin >> change;
                Student[n - 1].year = change;
                write_student();
                system("cls");
                cout << green << "\n\n\t\t Data Updated  Succesfully!" << reset << endl;
                Sleep(1500);
            }
            else if (choice == "4")
            {
                system("cls");
                cout << "\n\n\t\tNEW CONTRACT INFORMATION:";
                cin >> change;
                Student[n - 1].contractInfo = change;
                write_student();
                system("cls");
                cout << green << "\n\n\t\t Data Updated  Succesfully!" << reset << endl;
                Sleep(1500);
            }
            else if (choice == "5")
            {
                return;
            }
            else
            {
                cout << "\n\n\t\t" << red << "Invalid Option" << reset << endl;
            }
        }
    }
    else
    {
        system("cls");
        cout << red << "NO MATCH FOUND" << reset << endl;
        Sleep(1500);
        return;
    }
}

void course::course_dashboard()
{
    system("cls");
    char n;
    cout << "\n\n\n\n\n";
    cout << "\t\t\t\t\t       ---------------"
         << "\n";
    cout << "\t\t\t\t\t          COURSE MANAGEMENT"
         << "\n";
    cout << "\t\t\t\t\t       ---------------"
         << "\n\n\n";
    cout << "\t\t\t\t\t       SELECT OPTIONS"
         << "\n\n";
    cout << blue << "\t\t\t\t-------------------------------------------" << reset << "\n";
    cout << "\t\t\t\t  1. ALL COURSE\t2.ASSIGN COURSE\t3. COURSE DETAILS"
         << "\n";
    cout << blue << "\t\t\t\t-------------------------------------------" << reset
         << "\n\n";
    cout << red << "\t\t\t\t            (PRESS 4 TO BACK)"
         << "\n\n\n"
         << reset;
    cout << "\t\t\t\t\t     ENTER AN OPTION: ";
    cin >> n;
    switch (n)
    {
    case '1':
        crs.all_course();
        break;
    case '2':
        crs.assign_course();
        break;
    case '3':
        crs.course_details();
        break;
    case '4':
        return;
        break;

    default:
        system("cls");
        cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
        cout << "\n\n";
        Sleep(1500);
        break;
    }
}
void course::assign_course()
{
    system("cls");

    cout << "\t\t\t\t\t       ---------------"
         << "\n";
    cout << "\t\t\t\t\t      ASSIGN   COURSE "
         << "\n";
    cout << "\t\t\t\t\t       ---------------"
         << "\n\n\n";
    cout << "ENTER DEPERTMENT:";
    cin >> crs.dept;
    bool found = false;
ab:
    cout << "ENTER COUSE CODE:";
    cin >> code;
    for (auto x : CourseInfo)
    {
        if (x.code == code)
        {
            crs.code = code;
            found = true;
            break;
        }
    }
    if (!found)
    {
        {
            cout << red << "\n\t\tInvalid Course Code\n"
                 << reset
                 << endl;
            goto ab;
        }
    }
    found = false;
cd:

    cout << "ENTER TEACHER NAME:";
    cin.ignore();
    getline(cin, teacher);
    for (auto &x : Teacher)
    {
        if (x.name == teacher)
        {
            crs.teacher = teacher;
            found = true;
            break;
        }
    }
    if (!found)
    {
        {
            cout << red << "\n\t\tTeacher not found!\n"
                 << reset << endl;

            goto cd;
        }
    }
    Course.push_back(crs);
    file.open("courseDetails.csv", ios::app | ios::out);
    if (!file.is_open())
    {
        cout << "EROR \n";
    }
    else
    {
        file << crs.code << "," << crs.dept << "," << crs.teacher << "\n";
        cout << "\n\n\t\t" << green << "Couse Assign Succesfully" << reset << endl;
        Sleep(1500);
    }
    file.close();
}
void course::all_course()
{
    system("cls");
    cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
         << reset;
    cout << "                             COURSE DETAILS\n";
    cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
         << reset;

    cout << "\n\n\t\t Sl.     DEPERTMENT       COURSE CODE      COURSE TEACHER    \n";
    cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
         << reset;
    int i = 1;
    for (auto x : Course)
    {
        cout << "\n\n\t\t" << i << "   " << x.dept << "   " << x.code << "   " << x.teacher << "\n";
        i++;
    }
    string s;
    cout << "Press any key to return";
    cin >> s;
    return;
}
void course::course_details()
{
    for (auto x : CourseInfo)
    {
        cout << x.code << endl;
    }
    for (auto x : Teacher)
    {
        cout << x.name << endl;
    }
    cin >> title;
}
/*-------------------GRADE MANAGEMENT_____________________*/
void grade_management(string name)
{

    while (1)
    {
        system("cls");
        int n;
        cout
            << "\t\t\t  ---------------------------"
            << "\n";
        cout << "\t\t\t     GRADE MANAGEMENT"
             << "\n";
        cout << "\t\t\t  ---------------------------"
             << "\n";
        cout << blue << "\t\t     1. ADD GRADE"
             << "\n";
        cout << "\t\t     2. UPDATE GRADE"
             << "\n";
        cout << "\t\t     3. GARDE SHEET"
             << "\n";
        cout << "\t\t     4. SEARCH GRADE"
             << "\n";
        cout << "\t\t     5. GRADE REPORT"
             << "\n";
        cout << "\t\t     6. BACK"
             << "\n\n"
             << reset;
        cout << green << "\t\t     ENTER YOUR OPTION: " << reset;
        cin >> n;
        switch (n)
        {

        case 1:
            grd.add_grade(name);
            break;
        case 2:
            grd.update_grade();
            break;
        case 3:
            // student_info();
            break;
        case 4:
            grd.search_grade();
            break;
        case 5:
            grd.grade_report();
            break;
        case 6:
            return;
            break;

        default:
            system("cls");
            cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
            cout << "\n\n";
            Sleep(1500);
            break;
        }
    }
}
void grade::add_grade(string name)
{
    string id;
    bool found = false;
    system("cls");
    cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
         << reset;
    cout << "                             ADD GRADE\n";
    cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
         << reset;
    cout << "\n\t\tENTER STUDENT ID:";
    cin >> id;
    string s_id = id;
    int pos = 0;

    for (auto x : Student)
    {
        if (x.id == id)
        {
            found = true;
            grd.id = id;
            break;
        }
    }
    if (found)
    {
        system("cls");
        cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
             << reset;
        cout << "                             ADD GRADE\n";
        cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
             << reset;
        string code;
        cout << "ENTER COURSE CODE:";
        cin >> code;
        found = false;
        for (auto x : Course)
        {
            if (x.code == code && x.teacher == name)
            {
                found = true;
                grd.code = code;
                grd.quiz = "";
                grd.assignment = "";
                grd.final = "";
                grd.total_attendence = "";
                grd.present_attendence = "";
                break;
            }
        }
        bool y = true;
        for (auto &x : Grade)
        {
            if (x.id == id && x.code == code)
            {
                y = false;
            }
        }
        if (y)
        {
            Grade.push_back(grd);
        }

        if (found)
        {

            grd.add_mark(s_id, code);
        }
        else
        {
            cout << red << "\n\n\t\tYou are not assigned to this course" << reset;
            Sleep(1500);
        }
    }
    else
    {
        cout << red << "\n\n\t\tSTUDENT NOT FOUND!" << reset;
        Sleep(1500);
    }
}
void grade::add_mark(string Id, string Code)
{
    while (1)
    {
        system("cls");
        char n;
        system("cls");
        cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
             << reset;
        cout << "                             ADD GRADE\n";
        cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
             << reset;

        cout << "\t\tADD GRADE OF\n";
        cout << "\t\t1. QUIZ\n\t\t2.ASSIGNMENT\n\t\t3.FINAL \n\t\t0.BACK\n";

        cout << "\t\t ENTER YOUR OPTION:";
        cin >> n;
        int pos = 0;
        bool course = true;
        for (auto &x : CourseInfo)
        {
            if (x.code == Code)
            {
                credit = x.credit;
                semester = x.semester;
                title = x.title;
                break;
            }
        }
        for (auto &x : Grade)
        {
            if (x.id == Id && x.code == Code)
            {
                x.credit = credit;
                x.semester = semester;
                x.title = title;
            }
        }
        switch (n)
        {
        case '1':
        {
            cout << "ENTER QUIZ MARK:";
            cin >> quiz;
            for (auto &x : Grade)
            {
                if (x.id == Id && x.code == Code)
                {
                    x.quiz = quiz;
                }
            }
            write_grade();
            system("cls");
            cout << green << "\n\n Mark Added  Succesfully!" << reset << endl;
            Sleep(1500);

            break;
        }
        case '2':
        {
            cout << "ENTER ASSIGNMENT MARK:";
            cin >> quiz;
            for (auto &x : Grade)
            {
                if (x.id == Id && x.code == Code)
                {
                    x.assignment = quiz;
                }
            }
            write_grade();
            system("cls");
            cout << green << "\n\n Mark Added  Succesfully!" << reset << endl;
            Sleep(1500);
            break;
        }

        break;
        case '3':
        {
            cout << "ENTER FINAL MARK:";
            cin >> quiz;
            for (auto &x : Grade)
            {
                if (x.id == Id && x.code == Code)
                {
                    x.final = quiz;
                }
            }
            write_grade();
            system("cls");
            cout << green << "\n\n Mark Added  Succesfully!" << reset << endl;
            Sleep(1500);
            break;
        }
        case '0':
            return;
        default:
        {
            system("cls");
            cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
            cout << "\n\n";
            Sleep(1500);
            break;
        }
        }
    }
}

void grade::update_grade()
{
    string id;
    bool found = false;
    system("cls");
    cout << "\t\t\t  ---------------------------\n";
    cout << "\t\t\t\t     UPDATE GRADE"
         << "\n";
    cout << "\n\t\t\t  ---------------------------"
         << "\n";

    cout << "\n\t\tENTER STUDENT ID:" << green;
    cin >> id;
    cout << reset << "\n\t\tENTER COURSE CODE:" << green;
    cin >> code;
    cout << reset;

    for (auto x : Student)
    {
        if (x.id == id)
        {
            found = true;
            break;
        }
    }
    if (found)
    {
        char n;
        system("cls");
        int i = 0;
        for (auto x : Grade)
        {
            if (x.id == id && x.code == code)
            {
                found = true;
                break;
            }
            i++;
        }
        cout << "\t\t\t  ---------------------------\n";
        cout << "\t\t\t\t     UPDATE GRADE"
             << "\n";
        cout << "\n\t\t\t  ---------------------------"
             << "\n";

        cout << "\t\t UPDATE GRADE OF\n";
        cout << "\t\t1. QUIZ\n\t\t2.ASSIGNMENT\n\t\t3.FINAL \n\t\t0.BACK\n";

        cout << "\t\t ENTER YOUR OPTION:";
        cin >> n;
        switch (n)
        {
        case '1':
            cout << cyan << "ENTER QUIZ MARK:" << reset;
            cin >> grd.quiz;
            Grade[i].quiz = grd.quiz;
            write_grade();
            break;
        case '2':
            cout << cyan << "ENTER ASSIGNMENT MARK:" << reset;
            cin >> grd.assignment;
            Grade[i].assignment = grd.assignment;
            write_grade();
        case '3':
            cout << cyan << "ENTER FINAL MARK:" << reset;
            cin >> grd.final;
            Grade[i].quiz = grd.final;
            write_grade();
        case '0':
            return;
        default:
            system("cls");
            cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
            cout << "\n\n";
            Sleep(1500);
            break;
        }
    }
}
void grade::search_grade()
{
    char n;
    system("cls");
    cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
         << reset;
    cout << "                              SEARCH  GRADE";
    cout << blue << "\n\n\t\t---------------------------------------------------------------\n"
         << reset;
    cout << "\n\n\t\t   1.INDIVIDUAL GRADE\n";
    cout << "\t\t   2.BATCH WISE GRADE\n";
    cout << "\t\t   0.BACK\n";
    cout << cyan << "\t\t   ENTER OPTION:" << reset;
    cin >> n;
    if (n == '1')
    {
        grd.individual_report();
    }
    else if (n == '2')
    {
        grd.batch_report();
    }
    else if (n == '0')
    {
        return;
    }
}
void grade::gpa_calculate()
{
    int quiz = 0, assignment = 0, final = 0;
    for (auto &x : Grade)
    {
        quiz = stoi(x.quiz);
        assignment = stoi(x.assignment);
        final = stoi(x.final);
        x.grade = grd.gpa_grade(quiz, assignment, final);
        write_grade();
    }
}
string grade::gpa_grade(int q, int a, int f)
{
    int total = q + a + f;
    if (total >= 80)
    {
        return "4.00";
    }
    else if (total >= 75)
    {
        return "3.75";
    }
    else if (total >= 70)
    {
        return " 3.50";
    }
    else if (total >= 65)
    {
        return "3.25";
    }
    else if (total >= 60)
    {
        return "3.00";
    }
    else if (total >= 55)
    {
        return "2.75";
    }
    else if (total >= 50)
    {
        return "2.50";
    }
    else if (total >= 45)
    {
        return "2.25";
    }
    else if (total >= 40)
    {
        return "2.00";
    }
    else
    {
        return "0.00";
    }
}
void grade::grade_report()
{
    grd.gpa_calculate();
    system("cls");
    cout << "\t\t\t  -------------------------------"
         << "\n";
    cout << "\t\t\t     GRADE REPORT"
         << "\n";
    cout << "\t\t\t  -------------------------------"
         << "\n\n";
    cout << "\t\t\t1. Individual Report\n \t\t\t2.Batch Report\n\t\t\t3.Course Grade\n\t\t\t0.Back";
    string n;
    cout << green << "\n\t\tEnter your option:" << cyan;
    cin >> n;
    cout << reset;
    if (n == "1")
    {
        grd.individual_report();
    }
    else if (n == "2")
    {
        grd.batch_report();
    }
    else if (n == "3")
    {
        cout << "UNDER CONSTRUCTION";
        Sleep(3000);
    }
    else if (n == "0")
    {
        return;
    }
    else
    {
        system("cls");
        cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
        cout << "\n\n";
        Sleep(1500);
    }
}
float grade::semester_cgpa(string id, string n)
{
    float total_grade = 0.00;
    float grade, cgpa = 0;
    float credit;
    float total_credit = 0.0;
    for (auto &x : Grade)
    {

        if (x.id == id && x.semester[1] == n[0])
        {
            credit = stof(x.credit);
            total_credit += credit;
            grade = stof(x.grade);
            total_grade += grade * credit;
        }
    }
    cgpa = total_grade / total_credit;
    return cgpa;
}
void grade::individual_report()
{
    system("cls");
    string id, sem;
    cout << "\t\t\t  -------------------------------"
         << "\n";
    cout << "\t\t\t    INDIVIDUAL GRADE REPORT"
         << "\n";
    cout << "\t\t\t  -------------------------------"
         << "\n\n";
    cout << cyan << "\t\tENTER STUDENT ID:" << green;
    cin >> id;
    cout << blue << "ENTER SEMESTER(Press 0 for All):" << green;
    cin >> sem;
    cout << reset;

    grd.grade_book(id, sem);
}
void grade::grade_book(string id, string n)
{
    system("cls");
    cout << "\t\t\t  -------------------------------"
         << "\n";
    cout << "\t\t\t    INDIVIDUAL GRADE REPORT"
         << "\n";
    cout << "\t\t\t  -------------------------------"
         << "\n\n";

    /*------------------Personal Information--------------*/
    bool found = false;
    for (auto &x : Student)
    {
        if (x.id == id)
        {
            name = x.name;
            //   dept = x.dept;
            year = x.year;
            contractInfo = x.contractInfo;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << red << "\n\n\n\t\tStudent not found\n\n";
        Sleep(1500);
    }
    else
    {

        cout << green << "\t\t  STUDENT ID: " << cyan;
        cout << id;
        cout << green << "\n\t\tSTUDENT NAME: " << cyan;
        cout << name;
        cout << green << "\n\t\t  DEPERTMENT: " << cyan;
        cout << "CSE";
        cout << green << "\n\t\t     SESSION: " << cyan;
        cout << year;
        cout << green << "\n\t\t    CONTRACT: " << cyan;
        cout << contractInfo << reset;
        cout << "\n\n";
        cout << blue << "\n\t\tSEMSERTER:" << reset;
        cout << n;
        cout << endl;

        float cgpa = grd.semester_cgpa(id, n);
        /*--------------------------------------------------------Grade List-----------------------------------------------*/
        int i = 1;
        cout << "\t\t--------------------------------------------------------------------------------------------------------------\n"; // 106
        cout << "\t\t Sl.   COURSE CODE                   CORSE TITLE                COURSE TEACHER          CREDIT   GRADE    GPA";
        cout << "\n\t\t--------------------------------------------------------------------------------------------------------------\n";
        for (auto &x : Grade)
        {

            if (x.id == id && x.semester[1] == n[0])
            {
                grd.code = x.code;
                grd.credit = x.credit;
                grd.title = x.title;
                grd.assignment = x.assignment;
                grd.quiz = x.quiz;
                grd.final = x.final;
                grd.grade = x.grade;
                TempGrade.push_back(grd);
                cout << "\t\t" << i << "   " << x.code << "                                                                          " << x.credit << "  " << x.grade << "\n";
                i++;
            }
        }
        int a, b;
        cout << "\t\t--------------------------------------------------------------------------------------------------------------";
        printf("\n\t\t CGPA: %.2f\n", cgpa);
        cout << "Enter Sl. number for Details/Press 0 to Back:";
        cin >> year;
        if (year == "0")
        {
            return;
        }
        else
        {
            int n = stoi(year);
            n -= 1;

            string title, teacher;

            for (auto &x : CourseInfo)
            {
                if (x.code == TempGrade[n].code)
                {
                    title = x.title;
                    a = x.title.length();
                    break;
                }
            }
            for (auto &x : Course)
            {
                if (x.code == TempGrade[n].code)
                {
                    teacher = x.teacher;
                    break;
                }
            }
            b = 15;
            int mx = max(a, b);
            a = mx + 23;
            // dash_generator(a);
            cout << "\t\t  Course Code       : " << TempGrade[n].code << endl;
            // space_generator(TempGrade[n].code, mx);
            // dash_generator(a);
            cout << "\t\t  Course Title      : " << title << endl;
            // space_generator(title, mx);
            // dash_generator(a);
            cout << "\t\t  Course Teacher   : " << teacher << endl;
            // space_generator(TempGrade[n].title, mx);
            // dash_generator(a);
            cout << "\t\t  Quiz Mark       : " << TempGrade[n].quiz << endl;
            // space_generator(TempGrade[n].quiz, mx);
            // dash_generator(a);
            cout << "\t\t  Assignment Mark : " << TempGrade[n].assignment << endl;
            // space_generator(TempGrade[n].assignment, mx);
            // dash_generator(a);
            cout << "\t\t  Final Mark      : " << TempGrade[n].final << endl;
            // space_generator(TempGrade[n].final, mx);
            // dash_generator(a);
            cout << "\t\t  GPA              : " << TempGrade[n].grade << endl;
            // space_generator(TempGrade[n].grade, mx);
            // dash_generator(a);
        }

        cout << "\nPress Any Key to back:";
        cin >> year;
    }
}
void grade::batch_report()
{
    system("cls");
    cout << "\t\t\t  -------------------------------"
         << "\n";
    cout << "\t\t\t       BATCH REPORT"
         << "\n";
    cout << "\t\t\t  -------------------------------"
         << "\n\n";
    cout << "\t\t\t SELECT BATCH" << endl;
    string batch;
    cout << "\t\t\t 1.2019-20" << endl;
    cout << "\t\t\t 2.2020-21" << endl;
    cout << "\t\t\t 3.2021-22" << endl;
    cout << "\t\t\t 4.2022-23" << endl;
    cout << "\t\t\t 0.Back" << endl;
    cout << "\t\t ENTER OPTION:";
    cin >> batch;
    if (batch == "1")
    {
        batch = "2019-20";
    }
    else if (batch == "2")
    {
        batch = "2020-21";
    }
    else if (batch == "3")
    {
        batch = "2021-22";
    }
    else if (batch == "0")
    {
        return;
    }
    else
    {
        system("cls");
        cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
        cout << "\n\n";
        Sleep(1500);
        return;
    }

    /*---------------------SELECT SEMESTER------------------*/
    system("cls");
    cout << "\t\t\t  -------------------------------"
         << "\n";
    cout << "\t\t\t     BATCH REPORT"
         << "\n";
    cout << "\t\t\t  -------------------------------"
         << "\n\n";
    cout << "\t\t\t SELECT SEMESTER" << endl;
    cout << "\t\t\t 1.1st Semester" << endl;
    cout << "\t\t\t 2.2nd Semester" << endl;
    cout << "\t\t\t 3.3rd Semester" << endl;
    cout << "\t\t\t 4.4th Semester" << endl;
    cout << "\t\t\t 5.5th Semester" << endl;
    cout << "\t\t\t 6.6th Semester" << endl;
    cout << "\t\t\t 7.7th Semester" << endl;
    cout << "\t\t\t 8.8th Semester" << endl;
    cout << "\t\t\t 0.Back" << endl;
    cout << "\t\t ENTER OPTION:";
    cin >> semester;
    if (batch == "0")
    {
        return;
    }
    grd.batch_report_main(batch, semester);
}
void grade::batch_report_main(string session, string sem)
{
    system("cls");
    cout << "\t\t\t  -------------------------------"
         << "\n";
    cout << "\t\t\t     BATCH REPORT"
         << "\n";
    cout << "\t\t\t  -------------------------------"
         << "\n\n";
    cout << "\t\t SESSION:" << session << "\t\tSEMESTER:" << sem << endl;
    cout << "\t\t--------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t ROLL                   ID               NAME          SEMESTER       CGPA";
    cout << "\n\t\t--------------------------------------------------------------------------------------------------------------\n";
    for (auto x : Student)
    {
        if (x.year == session)
        {
            float cgpa = grd.semester_cgpa(x.id, sem);
            cout << "\t\t" << x.roll << " " << x.id << "              " << x.name << "    " << sem << "        " << cgpa << endl;
        }
    }
    string id;
    cout << "Enter ID for Detail report / Press 0 to back:";
    cin >> id;
    if (id == "0")
    {
        return;
    }
    else
    {
        grd.grade_book(id, sem);
    }
}

/*-----------Attendence-------*/
void grade::take_attendence(string name)
{
    string date, present;
    cout << "\n\n\t\t\t  -------------------------------"
         << "\n";
    cout << "\t\t\t   Take  ATTENDENCE "
         << "\n";
    cout << "\t\t\t  -------------------------------"
         << "\n\n";
    cout << green << "\t\t Enter Course Code: " << reset;
    cin >> code;
    // Check Teacher is valid for this course
    bool found = false;
    for (auto &x : Course)
    {
        if (x.teacher == name)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << red << "\n\n\n\t\t\t"
             << "You are not assign to this Course." << reset << endl;
        Sleep(1500);
        return;
    }

    cout << "\t\t Enter Session: ";
    cin >> year;
    cout << "\t\t Enter Date: ";
    cin >> grade;
    bool attend = false;
    for (int i = 0; i < Student.size(); i++)
    {
        if (Student[i].year == year)
        {
            cout << Student[i].name << " (P/A):";
            cin >> present;
            markAttendence(Student[i].id, present, code);
        }
    }
}
void grade::markAttendence(string id, string attend, string code)
{

    for (auto &x : Grade)
    {
        if (x.id == id && x.code == code)
        {
            int a, b;
            // Convert total attendance to an integer, or default to 0 if empty
            a = (x.total_attendence == "") ? 0 : stoi(x.total_attendence);
            a += 1;
            // Convert integer 'a' back to string and assign it to total_attendence
            x.total_attendence = to_string(a);

            if (attend == "p" || attend == "P")
            {
                // Convert present attendance to an integer, or default to 0 if empty
                b = (x.present_attendence == "") ? 0 : stoi(x.present_attendence);
                b += 1;
                // Convert integer 'b' back to string and assign it to present_attendence
                x.present_attendence = to_string(b);
            }
        }
    }
    cout << "\n\n\n\t\t\t" << green << "Attendence Taken Succesfully" << reset << endl;
    Sleep(3000);
    write_grade();
}
void grade::attendence_report()
{
    system("cls");
    cout << "\n\n\t\t\t  -------------------------------"
         << "\n";
    cout << "\t\t\t    ATTENDENCE REPORT"
         << "\n";
    cout << "\t\t\t  -------------------------------"
         << "\n\n";
    cout << "\t\t\t1. Individual Report\n \t\t\t2.Batch Report\n\t\t\t3.Course Grade\n\t\t\t0.Back";
    string n;
    cout << green << "\n\t\tEnter your option:" << cyan;
    cin >> n;
    cout << reset;
    if (n == "1")
    {
        grd.attenndence_individual();
    }
    else if (n == "2")
    {
        grd.attenndence_batch_wise();
    }
    else if (n == "0")
    {
        return;
    }
    else
    {
        system("cls");
        cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
        cout << "\n\n";
        Sleep(1500);
    }
}
void grade::attenndence_individual()
{
    system("cls");
    cout << "Enter STUDENT ID:";
    cin >> id;
    cout << "Enter Course Code:";
    cin >> code;

    for (auto &x : Student)
    {
        if (x.id == id)
        {
            showAttendence(x.id, x.name, code);
        }
    }
}
void grade::attenndence_batch_wise()
{
    system("cls");
    cout << "Enter Course Code:";
    cin >> code;
    cout << "Enter SESSION:";
    cin >> year;

    for (auto &x : Student)
    {
        if (x.year == year)
        {
            showAttendence(x.id, x.name, code);
        }
    }

    cin >> year;
}
void grade::showAttendence(string id, string name, string code)
{
    for (auto &x : Grade)
    {
        double per;
        if (x.id == id && x.code == code)
        {
            try
            {
                float presentAttendance = stof(x.present_attendence);
                float totalAttendance = stof(x.total_attendence);

                if (totalAttendance != 0) // To avoid division by zero
                {
                    per = (presentAttendance / totalAttendance) * 100.0;
                    cout << name << " " << x.code << " " << per << "%  " << (per >= 70.00) ? cout << BOLDGREEN << "Eligible" : cout << BOLDRED << "NOT Eligible";
                    cout << reset << endl;
                }
                else
                {
                    cout << "Error: Total attendance cannot be zero for " << name << " " << x.code << (presentAttendance / totalAttendance) * 100.0 << "%" << endl;
                }
            }
            catch (const std::invalid_argument &e)
            {
                cout << "Error: Invalid attendance data for " << name << " " << x.code << endl;
            }
            cout << "PRESS ANY KEY TO BACK";
            cin >> year;
        }
    }
}

void Admin::teacherManagement()
{

    while (1)
    {
        system("cls");
        cout << "\n\n";
        cout << "\t\t\t  ---------------------------"
             << "\n";
        cout << "\t\t\t      TEACHER MANAGEMENT"
             << "\n";
        cout << "\t\t\t  ---------------------------"
             << "\n";
        cout << "\t\t     1. ADD TEACHER "
             << "\n";
        cout << "\t\t     2.REMOVE TEACHER\n";
        cout << red << "\t\t     0. BACK"
             << "\n\n"
             << reset;
        cout << "\t\t     ENTER YOUR OPTION: ";
        string n;
        cin >> n;
        if (n == "1")
        {
            obj.addTeacher();
        }
        else if (n == "2")
        {
            obj.removeTeacher();
        }
        else if (n == "0")
        {
            return;
        }
        else
        {
            system("cls");
            cout << red << "\n\n\t\t\t\t\t\tWRONG OPTION!" << reset;
            cout << "\n\n";
            Sleep(1500);
        }
    }
}
