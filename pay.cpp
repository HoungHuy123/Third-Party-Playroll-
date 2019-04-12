
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "person.cpp"
using namespace std;


void readData(vector<Person> &employees) {
    string fname;
    string lname;
    int  id;
    string cname;
    float prate;
    float hworkpay;
    Person ps; 
    
    ifstream myfile;
    myfile.open ("input.txt");
    while(myfile >> fname >> lname >> id >> cname >> prate >> hworkpay){
    ps.setFirstName(fname);
    ps.setLastName(lname);
    ps.setEmployeeId(id);
    ps.setCompanyName(cname);
    ps.setPayRate(prate);
    ps.setHoursWorked(hworkpay);
    employees.push_back(ps);
    }
    //for (int i =0; i< employees.size(); i++){
    //    cout << employees.at(i).fullName() << endl;
    //}
    myfile.close();    
};
void getCompanies(vector<Person> &employees, vector<string> &companyNames){

    for (int i=0; i < employees.size(); i++){
        int j = 0;
        if (companyNames.empty()){
            companyNames.push_back(employees.at(i).getCompanyName());
        }
        for (int n=0; n < companyNames.size(); n++){
            if (employees.at(i).getCompanyName() == companyNames.at(n)){
                j++;
            }
        }
        if (j==0){
            companyNames.push_back(employees.at(i).getCompanyName());
        }
    }

};
void printHighestPaid(vector<Person> &employees){
    int num; 
    float empPaid = 0.0;
    //cout << "outside";
    for (int i = 0; i < employees.size(); i++) {
        //cout << "in the loop";
        if (empPaid < employees.at(i).totalPay()){
            empPaid = employees.at(i).totalPay();
            num = i;
           // cout << num;
        }
    }
    cout << "Highest Paid: " << employees.at(num).fullName() << endl;
    cout << "Employee ID: " << employees.at(num).getEmployeeId() << endl;
    cout << "Employer: " << employees.at(num).getCompanyName() << endl;
    cout << "Total Pay: $" << employees.at(num).totalPay() << endl;
};

void seperateAndSave(vector<Person> &employees, vector<string> &companyNames){
    ofstream outFile;
    string txtname;
    float total = 0.0;
    for (int i=0; i<companyNames.size(); i++){
        txtname = companyNames.at(i) + ".txt";
        outFile.open(txtname);
        for (int j=0; j< employees.size(); j++){
            if (companyNames.at(i) == employees.at(j).getCompanyName()){
                outFile << setw(15) << left << employees.at(j).getFirstName() << setw(15) << left << employees.at(j).getLastName();
                outFile << setw(5) << left << employees.at(j).getEmployeeId() << setw(15) << left << employees.at(j).getCompanyName();
                outFile << setw(10) << left << "$" << fixed << setprecision(2) << employees.at(j).totalPay() << endl;
                total += employees.at(j).totalPay();
            }
        }
        outFile << setw(7) << "Total" << setw(8) << left << "$" << total;
        outFile.close();
    }
};
int main(){

vector<Person> employees; 
vector<string> companyNames;

readData(employees);
//cout << "after read data" << endl;
getCompanies(employees,companyNames);
//cout << "after getcompanies" << endl;
printHighestPaid(employees);
//cout << "after print highest paid" << endl;
seperateAndSave(employees, companyNames);
//cout << "after separate and save " << endl;

    return 0;
}