#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;

class Logger
{
    static Logger* instance; // 1) приватный статический указатель на единственный экземпляр класса
    int log_сount = 0; // сколько раз происходила запись строки в файл

    Logger() // 2) конструктор - приватный (запрещает создавать объекты за пределами класса)
    {

    }

public:
    static Logger* GetInstance() // 3) публичный статический геттер на получение адреса единственного объекта
    {
        // если объекта журнала не существует - он создаётся
        return instance == nullptr ? instance = new Logger() : instance;
    }

    void Write(string message) // записать в журнал строку текста
    {
        log_сount++;
        cout << log_сount << ": " << message << "\n";
        // альтернативные варианты:
        // 1) записать строку в коллекцию (массив, список и тд) и хранить данные в памяти
        // 2) записать строку в файл
        ofstream output_file("log.txt", ios::app);
        if (output_file.is_open()) {
            output_file << message << "\n";
            output_file.close();
            //cout << "Строка успешно записана в файл.";
        }
        else {
            //cerr << "Не удалось открыть файл для записи.";
        }
        // 3) отправлять данные по сети
    }

    void Write(int value)
    {
        Write(to_string(value));
    }
};

Logger* Logger::instance = nullptr;

//Date
class Date {
    unsigned short day;
    unsigned short month;
    long long year;

public:
    Date() : Date(23, 12, 2023) {}

    Date(unsigned short day, unsigned short month, long long year)
    {
        SetDay(day);
        SetMonth(month);
        SetYear(year);
    }

    void PrintDate() const
    {
        cout << day << "." << month << "." << year << "\n";
    }

    void SetDay(unsigned short day)
    {
        if (day == 0 || day > 31) throw "ERROR!!! The day must be from 0 to 31 !!!";
        this->day = day;
    }

    unsigned short GetDay() const
    {
        return day;
    }

    void SetMonth(unsigned short month)
    {
        if (month == 0 || month > 12) throw "ERROR!!! The day must be from 1 to 12 !!!";
        this->month = month;
    }

    unsigned short GetMonth() const
    {
        return month;
    }

    void SetYear(long long year)
    {
        this->year = year;
    }

    long long GetYear() const
    {
        return year;
    }
};

//Student

class Student {
    static unsigned int count;
    string surname;
    string name;
    string middlename;
    string adress;
    string phonenumber;
    int average_grade;
    unsigned int countpractic = 0;
    unsigned int counthomework = 0;
    unsigned int countexam = 0;
    int* grade_of_practic = new int[countpractic];
    int* grade_of_homework = new int[counthomework];
    int* grade_of_exam = new int[countexam];

public:
    Student(const Student& original)
    {
        count++;
        this->surname = original.surname;
        this->name = original.name;
        this->middlename = original.middlename;
        this->adress = original.adress;
        this->phonenumber = original.phonenumber;
        this->countpractic = original.countpractic;
        this->counthomework = original.counthomework;
        this->countexam = original.countexam;
        this->count = original.count;
        this->average_grade = original.average_grade;
        this->grade_of_practic = new int[original.countpractic];
        for (int i = 0; i < countpractic; i++)
        {
            this->grade_of_practic[i] = original.grade_of_practic[i];
        }

        this->grade_of_homework = new int[original.counthomework];
        for (int i = 0; i < counthomework; i++)
        {
            this->grade_of_homework[i] = original.grade_of_homework[i];
        }

        this->grade_of_exam = new int[original.countexam];
        for (int i = 0; i < countexam; i++)
        {
            this->grade_of_exam[i] = original.grade_of_exam[i];
        }
        Logger::GetInstance()->Write("Student make copy");
        TimeNow();
    }

    Student() : Student("Studenchenko", "Student", "Studentovich", "Studencheskaya 38", "0630300033") { count++;Logger::GetInstance()->Write("Student has been created\n"), TimeNow(); }

    Student(string surname, string name, string middlname, string adress, string phonenumber)
    {
        count++;
        SetSurname(surname);
        SetName(name);
        SetMiddlName(middlname);
        SetAdress(adress);
        SetPhone(phonenumber);
        Logger::GetInstance()->Write("Student has been created\n");
        TimeNow();
    }

    Student(string surname, string name, string middlname, string adress) :Student(surname, name, middlename, adress, "0687680685") {}

    ~Student()
    {
        count--;
        if (grade_of_practic != nullptr)
            delete[] grade_of_practic;
        if (grade_of_homework != nullptr)
            delete[] grade_of_homework;
        if (grade_of_exam != nullptr)
            delete[] grade_of_exam;
        Logger::GetInstance()->Write("Student has been destroyed\n");
        TimeNow();
    }

    void TimeNow()
    {
        SYSTEMTIME st;
        char title[200];
        GetSystemTime(&st);
        printf("%02d:%02d:%02d\n", (st.wHour + 3) % 24, st.wMinute, st.wSecond);
    }

    void PrintStudent() 
    {

        cout << "Surname: " << surname << "\n";
        cout << "Name: " << name << "\n";
        cout << "Midlname: " << middlename << "\n";
        cout << "Adress: " << adress << "\n";
        cout << "Phonnumber: " << phonenumber << "\n";
        Logger::GetInstance()->Write("Student print\n");
        TimeNow();
    }
    unsigned int GetCount()
    {
        return count;
    }
    void AddPractic(int newcountry)
    {
        int* temp = new int[countpractic + 1];
        for (int i = 0; i < countpractic; i++)
        {
            temp[i] = grade_of_practic[i];
        }

        temp[countpractic] = newcountry;
        countpractic++;
        delete[]grade_of_practic;
        grade_of_practic = temp;
    }

    void PrintPractic() const
    {
        cout << "Practic: ";
        for (int i = 0; i < countpractic; i++)
        {
            cout << grade_of_practic[i] << ", ";
        }
        cout << "\n";
    }

    int GePracticRatesCount(unsigned int index) const
    {
        if (index < countpractic)
        {
            return grade_of_practic[index];
        }
    }

    void AddHomeWork(int newcountry)
    {
        int* temp = new int[counthomework + 1];
        for (int i = 0; i < counthomework; i++)
        {
            temp[i] = grade_of_homework[i];
        }
        temp[counthomework] = newcountry;
        counthomework++;
        delete[]grade_of_homework;
        grade_of_homework = temp;
    }

    void PrintHomeWork() const
    {
        cout << "HomeWork: ";
        for (int i = 0; i < counthomework; i++)
        {
            cout << grade_of_homework[i] << ", ";
        }
        cout << "\n";
    }

    int GetHomeWorkRatesCount(unsigned int index) const
    {
        if (index < counthomework)
        {
            return grade_of_homework[index];
        }
    }

    void AddExam(int newcountry)
    {
        int* temp = new int[countexam + 1];
        for (int i = 0; i < countexam; i++)
        {
            temp[i] = grade_of_exam[i];
        }
        temp[countexam] = newcountry;
        countexam++;
        delete[]grade_of_exam;
        grade_of_exam = temp;
    }

    void  AverageGrade()
    {

        for (int i = 0; i < countexam; i++)
        {
            average_grade += grade_of_exam[i] / countexam;
        }
        cout << average_grade << "\n";
    }

    void PrintExam() const
    {
        cout << "Exam: ";
        for (int i = 0; i < countexam; i++)
        {
            cout << grade_of_exam[i] << ", ";
        }
        cout << "\n";
    }

    int GetExamRatesCount(unsigned int index) const
    {
        if (index < countexam)
        {
            return grade_of_exam[index];
        }
    }

    void SetSurname(string surname)
    {
        this->surname = surname;
    }

    string GetSurname() const
    {
        return surname;
    }

    void SetName(string name)
    {
        this->name = name;
    }

    string GetName() const
    {
        return name;
    }

    void SetMiddlName(string middlname)
    {
        this->middlename = middlname;
    }

    string GetMiddlName() const
    {
        return middlename;
    }

    void SetAdress(string adress)
    {
        this->adress = adress;
    }

    string GetAdress() const
    {
        return adress;
    }

    void SetPhone(string phonenumber)
    {
        this->phonenumber = phonenumber;
    }

    string GetPhone() const
    {
        return phonenumber;
    }
    void SetAverageGrade(int average_grade)
    {
        this->average_grade = average_grade;
    }
    int GetAverageGrade() const
    {
        return average_grade;
    }
};
//Group
class Group {

    unsigned short countstudent = 0;
    Student** classmates = nullptr;
    string group_name;
    string specification;
    unsigned short number_of_course;

public:
    Group()
    {
        SetGroupName("P26");
        SetNumberOfCourse(2);
        SetSpecification("Software Development");

    }

    Group(const Group& original)
    {
        this->countstudent = original.countstudent;
        this->classmates = new Student * [original.countstudent];

        for (int i = 0; i < countstudent; i++)
        {
            this->classmates[i] = new Student(*original.classmates[i]);
        }

        this->group_name = original.group_name;
        this->specification = original.specification;
        this->number_of_course = original.number_of_course;
    }

    void Print() const
    {
        cout << group_name << "\n\n";
        for (int i = 0; i < countstudent; i++)
        {
            classmates[i]->PrintStudent();
            classmates[i]->PrintExam();
            classmates[i]->PrintHomeWork();
            classmates[i]->PrintPractic();
            classmates[i]->AverageGrade();
        }
    }
    //добавляем студента
    void AddStudent(const Student& new_student)
    {
        Student** temp = new Student * [countstudent + 1];
        for (int i = 0; i < countstudent; i++)
        {
            temp[i] = classmates[i];
        }
        temp[countstudent] = new Student(new_student);
        countstudent++;
        delete[]classmates;
        classmates = temp;
    }

    void WeanStudent(unsigned short index)
    {
        Student** temp = new Student * [countstudent - 1];
        for (int i = 0, j = 0; i < countstudent; i++)
        {
            if (i != index)
            {
                temp[j++] = classmates[i];
            }
        }
        delete classmates[index];
        delete[] classmates;
        countstudent--;
        classmates = temp;
        // тут будет удалени по индексу
    }
    //удяляем за низкий сред балу за экзамен
    void Expel()
    {
        if (countstudent == 0) {
            cout << "The group is empty.\n";
            return;
        }
        int minGradeIndex = 0; // индекс студента с самым низким баллом
        // находим индекс студента с самым низким баллом
        for (int i = 1; i < countstudent; i++)
        {
            if (classmates[i]->GetAverageGrade() < classmates[minGradeIndex]->GetAverageGrade()) {
                minGradeIndex = i;
            }
        }
        // удаляем студента с самым низким баллом
        Student** temp = new Student * [countstudent - 1];
        for (int i = 0, j = 0; i < countstudent; i++)
        {
            if (i != minGradeIndex) {
                temp[j++] = classmates[i];
            }
        }
        delete classmates[minGradeIndex];
        delete[] classmates;
        countstudent--;
        classmates = temp;
        cout << "The student with the lowest grade point average is dropped from the group.\n";
    }

    void SetCountOfStudent(int countstudent)
    {
        this->countstudent = countstudent;
    }

    int GetCountOfStudent() const
    {
        return countstudent;
    }

    void SetGroupName(string group_name)
    {
        this->group_name = group_name;
    }

    string GetGroupName() const
    {
        return group_name;
    }

    void SetSpecification(string specification)
    {
        this->specification = specification;
    }

    string GetSpecification() const
    {
        return specification;
    }

    void SetNumberOfCourse(int number_of_course)
    {
        this->number_of_course = number_of_course;
    }

    int GetNumberOfCourse() const
    {
        return number_of_course;
    }

    ~Group()
    {
        for (int i = 0; i < countstudent; i++)
        {
            delete classmates[i];
        }
        delete[] classmates;
    }
};

unsigned int Student::count;

int main()
{
    Student a;
    a.AddExam(11);
    a.AddExam(12);
    Student b;
    b.AddExam(10);
    b.AddExam(9);
    Group g;
    g.AddStudent(a);
    g.AddStudent(b);
    g.Print();
    g.Expel();
    g.Print();
    Student copya;
    copya = a;
    Student copyb;
    copyb = b;
    Group copy;
    copy = g;
    //Добавил Sleep, чтоб убедится, что вреся работает(будет на 1 секунду больше);
    Sleep(1000);
    copy.Print();
}
