#include <iostream>
#include <list>
#include <iomanip>
using namespace std;

struct UserData{
    string name = "Admin";
    int year = 2023;
    int dependent = 0;
};

struct TaxData{
    string name;
    double taxPaid;
    double income;
};

const float HANMUC[7] = {
    0.05,
    0.1,
    0.15,
    0.2,
    0.25,
    0.3,
    0.5
};
void ThietLapHanMuc();
void NhapThongTin();
void TinhThue();
void QuyetToan();


double CalTax(double income);
double CalTaxYear(double income);

//Han Muc
float workerExemption = 11,dependentExemption = 4.4;
//user data
UserData user;
list<TaxData> taxData;
int main() {
    int select;

    while (true) {
        cout << "------------------- Menu -------------------" << endl;
        cout << "1. Thiet lap han muc" << endl;
        cout << "2. Nhap thong tin" << endl;
        cout << "3. Tinh thue thu nhap ca nhan" << endl;
        cout << "4. Quyet toan thue thu nhap ca nhan" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "Moi nhap lua chon: ";
        cin >> select;

        if (select == 0) {
            return 0;
        }

        switch (select) {
            case 1:
                ThietLapHanMuc();
                break;
            case 2:
                NhapThongTin();
                break;
            case 3:
                TinhThue();
                break;
            case 4:
                QuyetToan();
                break;
            default:
                cout << "Vui long nhap trong khoang (0 - 4)" << endl;
        }
    }

    return 0;
}

void ThietLapHanMuc() {
    while (true) {
        cout << "Menu thiet lap han muc" << endl;
        cout << "1. Han muc nguoi lao dong: " << workerExemption << " trieu" << endl;
        cout << "2. Han muc nguoi phu thuoc: " << dependentExemption << " trieu" << endl;
        cout << "3. Quay ve Menu" << endl;
        int choice;
        cout << "Chon 1, 2 hoac 3: ";
        cin >> choice;

        if (choice == 1) {
            cout << "nhap han muc ban muon(trieu):";
            cin >> workerExemption;
        } else if (choice == 2) {
            cout << "nhap han muc ban muon(trieu):";
            cin >> dependentExemption;
        } else if (choice == 3) {
            system("cls");
            return;
        } else {
            cout << "Nhap 1, 2 hoac 3" << endl;
        }
    }
}

void NhapThongTin(){
    while (true) {
        cout << "Menu nhap thong tin" << endl;
        cout << "1. Nhap Thong Tin" << endl;
        cout << "2. Quay ve Menu" << endl;
        int choice;
        cout << "Chon 1 hoac 2: ";
        cin >> choice;

        if (choice == 1) {
            cout << "nhap ten:";
            cin.ignore();
            getline(cin,user.name);

            cout << "nhap nam tinh thue:";
            cin >> user.year;

            cout << "nhap so nguoi phu thuoc:";
            cin >> user.dependent;

            cout << "da nhap thong tin thanh cong";
            cout << "\n------------------------------------------\n";
        } else if (choice == 2) {
            system("cls");
            return;
        } else {
            cout << "Nhap 1 hoac 2" << endl;
        }
    }
}

void TinhThue() {
    while (true) {
        cout << "Menu tinh thue" << endl;
        cout << "1. Tinh Thue" << endl;
        cout << "2. Quay ve Menu" << endl;
        int choice;
        cout << "Chon 1 hoac 2: ";
        cin >> choice;

        if (choice == 1) {
            if (taxData.size() < 12) {
                system("cls");

                TaxData tax;
                cout << "Nhap thang: ";
                cin.ignore();
                getline(cin, tax.name);

                cout << "Nhap thu nhap thang nay (trieu): ";
                cin >> tax.income;
                tax.taxPaid = CalTax(tax.income);

                cout << "Thue cua " << tax.name << " la: " << tax.taxPaid << " trieu\n";

                taxData.push_back(tax);
            } else {
                cout << "Ban da nhap du 12 thang" << endl;
                return;
            }
        } else if (choice == 2) {
            system("cls");
            return;
        } else {
            cout << "Nhap 1 hoac 2" << endl;
        }
    }
}

void QuyetToan(){
    if(taxData.size <= 0)
    {
        cout << "chua co du lieu";
        return;
    }
    cout << "Don vi: Trieu Dong\n";
    int stt = 1;
    double totalIncome,totalTaxPaid = 0;
    cout << left << setw(4) << "STT" << " | ";
    cout << left << setw(20) << "Ten" << " | ";
    cout << left << setw(10) << "Thue" << " | ";
    cout << left << setw(15) << "Thu Nhap" << endl;

    cout << string(51, '-') << endl;

    for(TaxData tax : taxData)
    {
        cout << left << setw(4) << stt <<" | ";
        cout << left << setw(20) << tax.name << " | ";
        cout << left << setw(10) << tax.taxPaid << " | ";
        cout << left << setw(15) << tax.income << endl;
        stt++;
        totalIncome += tax.income;
        totalTaxPaid += tax.taxPaid;
    }
    cout << string(51, '-') << endl;

    cout << "Tong thu nhap nam " << user.year << " la: " << totalIncome << endl;
    cout << "Thu nhap tinh thue la: " << (totalIncome - 132) << endl;
    cout << "Thue tam nop la: " << totalTaxPaid << endl;
    double dTaxPaid = CalTaxYear(totalIncome);
    cout << "Thue thuc te la: " << CalTaxYear(totalIncome) << endl;
    double dRealPaid = dTaxPaid - totalTaxPaid;
    cout << "Thue: " << (dRealPaid > 0 ? "duong => phai nop them" : "am => duoc nhan lai") << endl;
}
double CalTaxYear(double income){
    income -= workerExemption * 12;
    income -= dependentExemption * user.dependent * 12;
    double tempIncome = 0.0;

    if (income <= 0) {
        tempIncome = 0.0;
    } else if (income <= 60) {
        tempIncome = income * HANMUC[0];
    } else if (income <= 120) {
        tempIncome = (income - 60) * HANMUC[1] + 3;
    } else if (income <= 216) {
        tempIncome = (income - 120) * HANMUC[2] + 9;
    } else if (income <= 384) {
        tempIncome = (income - 216) * HANMUC[3] + 23.4;
    } else if (income <= 624) {
        tempIncome = (income - 384) * HANMUC[4] + 57;
    } else if (income <= 960) {
        tempIncome = (income - 624) * HANMUC[5] + 117;
    } else {
        tempIncome = (income - 960) * HANMUC[6] + 217.8;
    }

    return tempIncome;
}
double CalTax(double income) {
    income -= workerExemption;
    income -= dependentExemption * user.dependent;
    double tempIncome = 0.0;

    if (income <= 0) {
        tempIncome = 0.0;
    } else if (income <= 5) {
        tempIncome = income * HANMUC[0];
    } else if (income <= 10) {
        tempIncome = (income - 5) * HANMUC[1] + 0.25;
    } else if (income <= 18) {
        tempIncome = (income - 10) * HANMUC[2] + 0.75;
    } else if (income <= 32) {
        tempIncome = (income - 18) * HANMUC[3] + 1.95;
    } else if (income <= 52) {
        tempIncome = (income - 32) * HANMUC[4] + 4.75;
    } else if (income <= 80) {
        tempIncome = (income - 52) * HANMUC[5] + 9.75;
    } else {
        tempIncome = (income - 80) * HANMUC[6] + 18.15;
    }

    return tempIncome;
}


