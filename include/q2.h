#ifndef Q2_H
#define Q2_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

namespace q2 {

struct Patient {

    Patient(std::string _name, size_t _age, size_t _smokes, size_t _area_q, size_t _alkhol)
        : name { _name }
        , age { _age }
        , smokes { _smokes }
        , area_q { _area_q }
        , alkhol { _alkhol }
    {
    }

    std::string name;
    size_t age;
    size_t smokes;
    size_t area_q;
    size_t alkhol;
};

inline std::vector<Patient> read_file(std::string filename)
{
    std::vector<Patient> patient;
    std::ifstream file("lung_cancer.csv");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string txt = buffer.str();

    std::regex pattern(R"((\w+)(\s*),(\w+)(\s*),(\d+),(\d+),(\d+),(\d+))");
    std::smatch match;

    while (std::regex_search(txt, match, pattern)) {

        std::string first_name { match[1].str() };
        std::string last_name { match[3].str() };
        std::istringstream iss_age { match[5].str() };
        std::istringstream iss_smokes { match[6].str() };
        std::istringstream iss_areaq { match[7].str() };
        std::istringstream iss_alkhol { match[8].str() };

        size_t age;
        size_t smokes;
        size_t areaq;
        size_t alkhol;

        iss_age >> age;
        iss_smokes >> smokes;
        iss_areaq >> areaq;
        iss_alkhol >> alkhol;

        patient.push_back(Patient(first_name + " " + last_name, age, smokes, areaq, alkhol));
        txt = match.suffix().str();
    }
    return patient;
}

inline bool compare(const Patient& patient_1, const Patient& patient_2)
{
    size_t a { 3 * (patient_1.age) + 5 * (patient_1.smokes) + 2 * (patient_1.area_q) + 4 * (patient_1.alkhol) };
    size_t b { 3 * (patient_2.age) + 5 * (patient_2.smokes) + 2 * (patient_2.area_q) + 4 * (patient_2.alkhol) };
    return a > b;
}

inline void sort(std::vector<Patient>& patient)
{
    std::sort(patient.begin(), patient.end(), compare);
}

}

#endif // Q2_H