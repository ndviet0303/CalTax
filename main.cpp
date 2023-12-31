#include <iostream>
#include <list>
#include <iomanip>
#include <cmath>
using namespace std;

struct UserData {
    string name = "Admin";
    int year = 2023;
    int dependent = 0;
};

struct TaxData {
    int name;
    double taxPaid;
    double income;
};

//Han muc thue thu nhap theo thang.
float hanMuc[7] = {
    0.05,
    0.1,
    0.15,
    0.2,
    0.25,
    0.3,
    0.35
};
//Han muc thue thu nhap theo nam.
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

// User Data
UserData user;
list<TaxData> taxData;

int main() {
    int select;

    while (true) {
        cout << "------------------- Menu -------------------" << endl;
        cout << " 1. Thiet lap han muc mien tru" << endl;
        cout << " 2. Thiet lap phan tram thue" << endl;
        cout << " 3. Nhap thong tin" << endl;
        cout << " 4. Tinh thue thu nhap ca nhan" << endl;
        cout << " 5. Quyet toan thue ca nam" << endl;
        cout << " 0. Thoat chuong trinh" << endl;
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
                break;
        }
    }

    return 0;
}

void ThietLapHanMuc() {
    do {
	cout << "Nhap han muc ban muon (trieu): ";
    cin >> workerExemption;
    } while (workerExemption <= 0);

    do {
    cout << "Nhap han muc doi voi moi nguoi phu thuoc (trieu): ";
    cin >> dependentExemption;
    system("cls");
    } while (dependentExemption <= 0);
}

void ThietLapPhanTramThue(){
    for(int i =0;i < sizeof(hanMuc) / sizeof(hanMuc[0]);i++)
    {
         float hanMucTemp = 0;
        if(i == (sizeof(hanMuc) / sizeof(hanMuc[0]) - 1))
        {
            cout << "Thay Doi Han Muc > " << hanMucThue[i - 1][0] << " trieu/thang va > " << hanMucThue[i -1][1] << " trieu/nam la " << hanMuc[i] * 100.0  << "% sang: ";
            do {
			cin >> hanMucTemp;
            hanMuc[i] = hanMucTemp / 100.0;
            } while (hanMucTemp <= 0);
        }
        else{
            cout << "Thay Doi Han Muc " << hanMucThue[i][0] << " trieu/thang va " << hanMucThue[i][1] << " trieu/nam la " << hanMuc[i] * 100.0  << "% sang: ";
	        do {
			cin >> hanMucTemp;
	        hanMuc[i] = hanMucTemp / 100.0;
		    } while (hanMucTemp <= 0);
        }
    }
    system("cls");
}
void NhapThongTin() {
    cout << "Ho va ten: ";
    cin.ignore();
    getline(cin, user.name);

	do {
    cout << "Nam tinh thue: ";
    cin >> user.year;
    } while (user.year <= 0);

    do {
    cout << "So nguoi phu thuoc: ";
    cin >> user.dependent;
    } while (user.dependent <= 0);

    cout << "Da nhap thong tin thanh cong!";
    cout << "\n------------------------------------------\n";
    system("cls");
}

void TinhThue() {
    if (taxData.size() < 12) {
        system("cls");
        cout << " -Thong tin-" << endl;
        cout << "Ho va ten: " << user.name << endl;
        cout << "So nguoi phu thuoc: " << user.dependent << endl;
        cout << "Han muc mien tru gia canh: " << workerExemption << endl;
        cout << "Han muc mien tru voi moi nguoi phu thuoc: " << dependentExemption << endl;
        cout << "Don vi: trieu dong" << endl;
        if(taxData.size() > 0)
        {
            int stt = 1;
            cout << left << setw(4) << " STT" << " | ";
            cout << left << setw(20) << "Thang" << " | ";
            cout << left << setw(10) << "Thu Nhap" << " | ";
            cout << left << setw(10) << "Thue" << endl;

            cout << string(51, '-') << endl;

            for (TaxData tax : taxData) {
                cout << left << setw(4) << stt << " | ";
                cout << left << setw(20) << tax.name << " | ";
                cout << left << setw(10) << tax.income << " | ";
                cout << left << setw(10) << tax.taxPaid << endl;
                stt++;
            }
            cout << string(51, '-') << endl;
        }
        TaxData tax;
        cout << "Nhap thang: ";
        cin >> tax.name;
        if(tax.name <= 0 || tax.name > 12)
        {
            cout << "Nhap trong khoang 1 - 12." << endl;
            cout << "Bam enter de tiep tuc.";
            cin.ignore();
            cin.get();
            return;
        }

         for (TaxData taxF : taxData) {
                if(taxF.name == tax.name)
                {
                    cout << "Thang nay da duoc nhap." << endl;
                    cout << "Bam enter de tiep tuc.";
                    cin.ignore();
                    cin.get();
                    return;
                }
        }

        cout << "Nhap thu nhap thang nay (trieu): ";
        cin >> tax.income;
        tax.taxPaid = CalTax(tax.income);

        cout << "Thue cua thang " << tax.name << " la: " << tax.taxPaid << " trieu\n";

        taxData.push_back(tax);

        cout << "Bam enter de tiep tuc.";
        cin.ignore();
        cin.get();

    } else {
        cout << "Ban da nhap du 12 thang." << endl;
        return;
    }
    system("cls");
}

void QuyetToan() {
    if (taxData.size() <= 0) {
        cout << "Chua co du lieu." << endl;
        return;
    }
    cout << " -Thong tin-" << endl;
    cout << "Ho va ten: " << user.name << endl;
    cout << "So nguoi phu thuoc: " << user.dependent << endl;
    cout << "Han muc mien tru gia canh: " << workerExemption << endl;
    cout << "Han muc mien tru voi moi nguoi phu thuoc: " << dependentExemption << endl;
    cout << "Don vi: trieu dong" << endl;
    int stt = 1;
    double totalIncome = 0, totalTaxPaid = 0;
    cout << left << setw(4) << " STT" << " | ";
    cout << left << setw(20) << "Thang" << " | ";
    cout << left << setw(10) << "Thu Nhap" << " | ";
    cout << left << setw(10) << "Thue" << endl;
    cout << string(51, '-') << endl;

    for (TaxData tax : taxData) {
        cout << left << setw(4) << stt << " | ";
        cout << left << setw(20) << tax.name << " | ";
        cout << left << setw(10) << tax.income << " | ";
        cout << left << setw(10) << tax.taxPaid << endl;
        stt++;
        totalIncome += tax.income;
        totalTaxPaid += tax.taxPaid;
    }
    cout << string(51, '-') << endl;
    cout << "Don vi: trieu dong" << endl;
    cout << "Tong thu nhap nam " << user.year << " la: " << totalIncome << endl;
    cout << "Thu nhap tinh thue: " << (totalIncome - 132) << endl;
    cout << "Thue tam nop: " << totalTaxPaid << endl;
    double dTaxPaid = CalTaxYear(totalIncome);
    cout << "Thue thuc te: " << CalTaxYear(totalIncome) << endl;
    double dRealPaid = dTaxPaid - totalTaxPaid;
    cout << "Thue: " <<  dRealPaid << endl;
    double iGiaTriTuyetDoi = abs(dRealPaid);
    (dRealPaid > 0 ? cout << "Ban phai nop them " << iGiaTriTuyetDoi << " trieu dong." : cout << "Ban duoc nhan lai " << iGiaTriTuyetDoi << " trieu dong." ) << endl;
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
