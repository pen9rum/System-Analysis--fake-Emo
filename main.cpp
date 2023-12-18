#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cctype>
#include <string>
#include <set>

using namespace std;
double calculateCategoryRisk(const string& category, const vector<string>& barcodes, const vector<string>& invalidBarcodes);
string getCategoryCode(const string& barcode);
string getCategoryCodeFromName(const string& categoryName);
double calculateRiskPercent(int invalidCount, int totalCount);

double calculateCategoryRisk(const string& category, const vector<string>& barcodes, const vector<string>& invalidBarcodes) {
    int sampleNumber = 0;
    int invalidCount = 0;
    string categoryCode = getCategoryCodeFromName(category);

    for (const string& barcode : barcodes) {
        if (getCategoryCode(barcode) == categoryCode) {
            sampleNumber++;
        }
    }

    for (const string& barcode : invalidBarcodes) {
        if (getCategoryCode(barcode) == categoryCode) {
            invalidCount++;
        }
    }

    return calculateRiskPercent(invalidCount, sampleNumber);
}

string getCategoryCode(const string& barcode) {
    return barcode.length() >= 7 ? barcode.substr(5, 2) : "";
}

string getCategoryCodeFromName(const string& categoryName) {
    if (categoryName == "Top") return "01";
    if (categoryName == "Pants") return "02";
    if (categoryName == "Coat") return "03";
    if (categoryName == "Shoes") return "04";
    if (categoryName == "Accessories") return "05";
    return "";
}

double calculateRiskPercent(int invalidCount, int totalCount) {
    return totalCount > 0 ? static_cast<double>(invalidCount) / totalCount : 0.0;
}
const set<string> validBrands = {"MHV", "DXN", "DNV", "VCS", "ILG", "OFA", "GWF", "CVF", "KIG", "QJO", "GRV", "MUX", "GIE", "KJT", "WUT"};
const set<string> validManufacturers = {"IF", "TJ", "PL", "KI", "BW", "RG"};

bool isValidManufacturer(const string& code) {
    return validManufacturers.find(code) != validManufacturers.end();
}

bool isValidBrand(const string& code) {
    return validBrands.find(code) != validBrands.end();
}

bool isBarcodeValid(const string& barcode) {
    if (barcode.length() != 18) return false;
   if (!isValidBrand(barcode.substr(0, 3))) return 2;
    if (!isValidManufacturer(barcode.substr(3, 2))) return 3;

    for (int i = 0; i < 5; ++i)
        if (!isalpha(barcode[i])) return false;
    for (int i = 5; i < 18; ++i)
        if (!isdigit(barcode[i])) return false;

    return true;
}
int isBarcodeValid2(const string& barcode) {
    if (barcode.length() != 18) return 1;
     if (!isValidBrand(barcode.substr(0, 3))) return 2;  // Check first 3 characters for brand
    if (!isValidManufacturer(barcode.substr(3, 2))) return 3;  // Check next 2 characters for manufacturer


    for (int i = 0; i < 5; ++i)
        if (!isalpha(barcode[i])) return 4;
    for (int i = 5; i < 18; ++i)
        if (!isdigit(barcode[i])) return 5;

    return 6;
}
string getRandomBarcode(const vector<string>& barcodes, mt19937& gen) {
    uniform_int_distribution<> dis(0, barcodes.size() - 1);
    return barcodes[dis(gen)];
}

vector<string> getInvalidBarcodes(const vector<string>& barcodes) {
    vector<string> invalidBarcodes;
    for (const string& barcode : barcodes) {
        if (!isBarcodeValid(barcode)) {
            invalidBarcodes.push_back(barcode);
        }
    }
    return invalidBarcodes;
}

void printInvalidBarcodes(const vector<string>& invalidBarcodes) {
    for (const string& barcode : invalidBarcodes) {
        cout << "Invalid Barcode: " << barcode << "\n";
    }
}
void sampleAndCheckBarcodes(int value, const vector<string>& barcodes, mt19937& gen, vector<string>& invalidBarcodes) {
    for (int i = 0; i < value; ++i) {
        string selectedBarcode = getRandomBarcode(barcodes, gen);
        cout << "Sampled Barcode: " << selectedBarcode << "\\n";

        if (!isBarcodeValid(selectedBarcode)) {
            cout << "Error: Invalid barcode.\\n";
            invalidBarcodes.push_back(selectedBarcode);
        }
    }
}
int main() {
    int value;
    cout << "Enter the number of samples: ";
    cin >> value;

    vector<string> barcodes;
    string tempBarcode;
    cout << "Enter the barcodes (enter 'done' to finish):\\n";
    while (true) {
        cin >> tempBarcode;
        if (tempBarcode == "done") break;
        barcodes.push_back(tempBarcode);
    }

    random_device rd;
    mt19937 gen(rd());
    vector<string> invalidBarcodes;

    for (int i = 0; i < value; ++i) {
        string selectedBarcode = getRandomBarcode(barcodes, gen);
        //cout << "Sampled Barcode: " << selectedBarcode << endl;

        if (isBarcodeValid2(selectedBarcode)!=6) {
            int k =isBarcodeValid2(selectedBarcode);
            cout << "Error" << to_string(k) << ": Invalid barcode.\n";

            invalidBarcodes.push_back(selectedBarcode);
        }
    }

    cout << "List of invalid barcodes:\n";
    printInvalidBarcodes(invalidBarcodes);

    return 0;
}
