#include <iostream>
#include <list>
#include <iomanip>
using namespace std;

struct UserData {
    string name = "Admin";
    int year = 2023;
    int dependent = 0;
};

struct TaxData {
    string name;
    double taxPaid;
    double income;
};

float hanMuc[7] = {
    0.05,
    0.1,
    0.15,
    0.2,
    0.25,
    0.3,
    0.35
};
int hanMucThue[7][2] = {
    {5, 60},
    {10, 120},
    {18, 216},
    {32, 384},
    {52, 624},
    {80, 960}
};

void ThietLapHanMuc();
void NhapThongTin();
void TinhThue();
void QuyetToan();
void ThietLapPhanTramThue();

double CalTax(double income);
double CalTaxYear(double income);

// Han Muc
float workerExemption = 11, dependentExemption = 4.4;

// User data
UserData user;
list<TaxData> taxData;

int main() {
    int select;

    while (true) {
        cout << "------------------- Menu -------------------" << endl;
        cout << "1. Thiet lap han muc mien tru" << endl;
        cout << "2. Thiet lap phan tram thue" << endl;
        cout << "3. Nhap thong tin" << endl;
        cout << "4. Tinh thue thu nhap ca nhan" << endl;
        cout << "5. Quyet toan thue thu nhap ca nhan" << endl;
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
                ThietLapPhanTramThue();
                break;
            case 3:
                NhapThongTin();
                break;
            case 4:
                TinhThue();
                break;
            case 5:
                QuyetToan();
                break;
            default:
                cout << "Vui long nhap trong khoang (0 - 5)" << endl;
        }
    }

    return 0;
}

void ThietLapHanMuc() {
    cout << "nhap han muc ban muon(trieu):";
    cin >> workerExemption;
    cout << "nhap han muc ban muon(trieu):";
    cin >> dependentExemption;
    system("cls");
}

void ThietLapPhanTramThue(){
    for(int i =0;i < sizeof(hanMuc);i++)
    {
        float hamMucTemp = 0;
        cout << "Thay Doi Han muc " << hanMucThue[i][0] << "trieu/thang va " << hanMucThue[i][1] << "trieu/nam la:" << hanMuc[i] * 100.0  << "% Sang:";
        cin >> hamMucTemp;
        hanMuc[i] = hamMucTemp / 100.0;
    }
    system("cls");
}
void NhapThongTin() {
    cout << "nhap ten:";
    cin.ignore();
    getline(cin, user.name);

    cout << "nhap nam tinh thue:";
    cin >> user.year;

    cout << "nhap so nguoi phu thuoc:";
    cin >> user.dependent;

    cout << "da nhap thong tin thanh cong";
    cout << "\n------------------------------------------\n";
    system("cls");
}

void TinhThue() {
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
    system("cls");
}

void QuyetToan() {
    if (taxData.size() <= 0) {
        cout << "chua co du lieu";
        return;
    }
    cout << "Don vi: Trieu Dong\n";
    int stt = 1;
    double totalIncome, totalTaxPaid = 0;
    cout << left << setw(4) << "STT" << " | ";
    cout << left << setw(20) << "Ten" << " | ";
    cout << left << setw(10) << "Thue" << " | ";
    cout << left << setw(15) << "Thu Nhap" << endl;

    cout << string(51, '-') << endl;

    for (TaxData tax : taxData) {
        cout << left << setw(4) << stt << " | ";
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

double CalTaxYear(double income) {
    income -= workerExemption * 12;
    income -= dependentExemption * user.dependent * 12;
    double tempIncome = 0.0;

    if (income <= 0) {
        tempIncome = 0.0;
    } else if (income <= 60) {
        tempIncome = income * hanMuc[0];
    } else if (income <= 120) {
        tempIncome = (income - 60) * hanMuc[1] + 3;
    } else if (income <= 216) {
        tempIncome = (income - 120) * hanMuc[2] + 9;
    } else if (income <= 384) {
        tempIncome = (income - 216) * hanMuc[3] + 23.4;
    } else if (income <= 624) {
        tempIncome = (income - 384) * hanMuc[4] + 57;
    } else if (income <= 960) {
        tempIncome = (income - 624) * hanMuc[5] + 117;
    } else {
        tempIncome = (income - 960) * hanMuc[6] + 217.8;
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
        tempIncome = income * hanMuc[0];
    } else if (income <= 10) {
        tempIncome = (income - 5) * hanMuc[1] + 0.25;
    } else if (income <= 18) {
        tempIncome = (income - 10) * hanMuc[2] + 0.75;
    } else if (income <= 32) {
        tempIncome = (income - 18) * hanMuc[3] + 1.95;
    } else if (income <= 52) {
        tempIncome = (income - 32) * hanMuc[4] + 4.75;
    } else if (income <= 80) {
        tempIncome = (income - 52) * hanMuc[5] + 9.75;
    } else {
        tempIncome = (income - 80) * hanMuc[6] + 18.15;
    }

    return tempIncome;
}
