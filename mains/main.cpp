#include <bits/stdc++.h>
using namespace std;

class Problem
{
public:
    string name;
    string type;
    int startingHour;
    int priority;
    int hoursNeeded;
    Problem(string name, string type, int startingHour, int hoursNeeded, int priority)
    {
        this->name = name;
        this->type = type;
        this->startingHour = startingHour;
        this->hoursNeeded = hoursNeeded;
        this->priority = priority;
    }
    bool operator<(const Problem &other) const
    {
        if (this->startingHour == other.startingHour)
            return this->priority < other.priority;
        else
            return this->startingHour > other.startingHour;
    }
    void displayInfo()
    {
        cout << this->priority << " " << this->name << " " << this->type << " " << this->startingHour << " " << this->hoursNeeded << endl;
    }
};

class Doctor
{
public:
    string id;
    vector<string> types;
    vector<Problem> assignedProblems;
    Doctor(string id)
    {
        this->id = id;
    }
    void displayInfo()
    {
        cout << this->id << endl;
        cout << "Qualifications : ";
        for (int i = 0; i < this->types.size(); i++)
            cout << this->types[i] << " ";
        cout << endl;
        if (this->assignedProblems.size() == 0)
            cout << "No problems solved yet" << endl;
        else
        {
            cout << "Problems solved : " << endl;
            for (int i = 0; i < this->assignedProblems.size(); i++)
                this->assignedProblems[i].displayInfo();
        }
    }
    bool isAvailable(Problem p)
    {
        string type = p.type;
        vector<string>::iterator checkType = find_if(
            this->types.begin(), this->types.end(), [type](string str)
            { return type == str; });
        if (checkType != this->types.end())
        {
            if (this->assignedProblems.size() == 0)
                return true;
            else
            {
                Problem lastProblem = this->assignedProblems[this->assignedProblems.size() - 1];
                if ((lastProblem.startingHour + lastProblem.hoursNeeded <= p.startingHour) && (p.startingHour + p.hoursNeeded) <= 17)
                    return true;
                return false;
            }
        }
        return false;
    }
};

priority_queue<Problem> problems;
vector<Doctor> doctors;

void init()
{
    ifstream file("input.txt");
    int len;
    file >> len;
    for (int i = 0; i < len; i++)
    {
        string name, type;
        int startingHour, hoursNeeded;
        int priority;
        file >> name >> type >> startingHour >> hoursNeeded >> priority;
        problems.push(Problem(name, type, startingHour, hoursNeeded, priority));
    }
    file >> len;
    for (int i = 0; i < len; i++)
    {
        string id;
        int lenTypes;
        file >> id >> lenTypes;
        Doctor doctor(id);
        for (int j = 0; j < lenTypes; j++)
        {
            string type;
            file >> type;
            doctor.types.push_back(type);
        }
        doctors.push_back(doctor);
    }
}

void displayData()
{
    cout << "Problems : " << endl;
    if (problems.empty())
    {
        cout << "No more problems left" << endl;
    }
    else
    {
        while (!problems.empty())
        {
            Problem p = problems.top();
            p.displayInfo();
            problems.pop();
            cout << "----" << endl;
        }
    }

    cout << endl;
    cout << "Doctors : " << endl;
    for (int i = 0; i < doctors.size(); i++)
    {
        doctors[i].displayInfo();
        cout << "----" << endl;
    }
}

void solve()
{
    while (!problems.empty())
    {
        Problem problem = problems.top();
        int index = 0;
        while (index != doctors.size())
        {
            if (doctors[index].isAvailable(problem))
            {
                doctors[index].assignedProblems.push_back(problem);
                break;
            }
            index++;
        }

        problems.pop();
    }
}

int main()
{
    init();
    solve();
    displayData();
    return 0;
}
