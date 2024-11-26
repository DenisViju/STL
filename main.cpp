#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Doctor {
    string id;
    string speciality;
    int time;
    vector <string> problemeRezolvate;
};

struct Problem {
    string id;
    string speciality;
    int time;
};

int main()
{
    ifstream inFile("input.txt");

    if (!inFile) {
        cerr << "Nu s-a putut deschide fișierul input.txt\n";
        return 1;
    }

    int no_problems, no_doctors, time;
    string name, speciality;
    vector<Doctor> doctors;
    vector<Problem> problems;

    inFile >> no_problems;
    problems.reserve(no_problems);

    for (int i = 0; i < no_problems; i++) {
        inFile >> name;
        inFile >> speciality;
        inFile >> time;
        problems.push_back(Problem{ name, speciality, time });
        
    }

    inFile >> no_doctors;
    doctors.reserve(no_doctors);

    for (int i = 0; i < no_doctors; i++) {
        inFile >> name;
        inFile >> speciality;
        doctors.push_back(Doctor{ name, speciality, 8, {}});


    }
    
    for (auto& problem : problems) {
       auto doctorIt = find_if(doctors.begin(), doctors.end(), [&problem](Doctor& doctor) {
            return problem.speciality == doctor.speciality && doctor.time >= problem.time;
            });
       
    
        if (doctorIt != doctors.end()) {
                doctorIt->problemeRezolvate.push_back(problem.id);
                doctorIt->time -= problem.time;
        }

    }
    for (auto& doctor : doctors) {
        if (!doctor.problemeRezolvate.empty()) {
            cout << doctor.id << " " << doctor.problemeRezolvate.size();
            for (auto& problema : doctor.problemeRezolvate)
                cout << " " << problema;
            cout << endl;
        }
    }

    
    return 0;
}