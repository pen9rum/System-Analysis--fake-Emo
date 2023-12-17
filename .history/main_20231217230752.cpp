#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cctype>
#include <string>
#include <set>

using namespace std;

const set<string> validBrands = {"MHV", "DXN", "DNV", "VCS", "ILG", "OFA", "GWF", "CVF", "KIG", "QJO", "GRV", "MUX", "GIE", "KJT", "WUT"};
const set<string> validManufacturers = {"IF", "TJ", "PL", "KI", "BW", "RG"};

bool isValidManufacturer(const string &code)
{
    return validManufacturers.find(code) != validManufacturers.end();
}

bool isValidBrand(const string &code)
{
    return validBrands.find(code) != validBrands.end();
}

bool isBarcodeValid(const string &barcode)
{
    if (barcode.length() != 18)
        return false;
    if (!isValidManufacturer(barcode.substr(0, 2)))
        return false;
    if (!isValidBrand(barcode.substr(2, 3)))
        return false;

    for (int i = 0; i < 5; ++i)
        if (!isalpha(barcode[i]))
            return false;
    for (int i = 5; i < 18; ++i)
        if (!isdigit(barcode[i]))
            return false;

    return true;
}

string getRandomBarcode(const vector<string> &barcodes, mt19937 &gen)
{
    uniform_int_distribution<> dis(0, barcodes.size() - 1);
    return barcodes[dis(gen)];
}

vector<string> getInvalidBarcodes(const vector<string> &barcodes)
{
    vector<string> invalidBarcodes;
    for (const string &barcode : barcodes)
    {
        if (!isBarcodeValid(barcode))
        {
            invalidBarcodes.push_back(barcode);
        }
    }
    return invalidBarcodes;
}

void printInvalidBarcodes(const vector<string> &invalidBarcodes)
{
    for (const string &barcode : invalidBarcodes)
    {
        cout << "Invalid Barcode: " << barcode << "\\n";
    }
}
void sampleAndCheckBarcodes(int value, const vector<string> &barcodes, mt19937 &gen, vector<string> &invalidBarcodes)
{
    for (int i = 0; i < value; ++i)
    {
        string selectedBarcode = getRandomBarcode(barcodes, gen);
        cout << "Sampled Barcode: " << selectedBarcode << "\\n";

        if (!isBarcodeValid(selectedBarcode))
        {
            cout << "Error: Invalid barcode.\\n";
            invalidBarcodes.push_back(selectedBarcode);
        }
    }
}
string generateInvalidBarcode(mt19937 &gen)
{
    // 分別用於生成隨機字母和數字
    uniform_int_distribution<> charDis(0, 25);
    uniform_int_distribution<> numDis(0, 9);

    // 初始假設條碼是有效的
    string barcode = *validManufacturers.begin() + *validBrands.begin() + string(13, '0' + numDis(gen));

    // 隨機選擇錯誤類型
    int errorType = numDis(gen) % 5;

    switch (errorType)
    {
    case 0:                                                // 長度錯誤
        barcode = barcode.substr(0, numDis(gen) % 17 + 1); // 隨機生成1到17長度的條碼
        break;
    case 1: // 生產商錯誤
        do
        {
            barcode[0] = 'A' + charDis(gen);
            barcode[1] = 'A' + charDis(gen);
        } while (isValidManufacturer(barcode.substr(0, 2)));
        break;
    case 2: // 品牌錯誤
        do
        {
            barcode[2] = 'A' + charDis(gen);
            barcode[3] = 'A' + charDis(gen);
            barcode[4] = 'A' + charDis(gen);
        } while (isValidBrand(barcode.substr(2, 3)));
        break;
    case 3:                                            // 前五位包含非字母
        barcode[charDis(gen) % 5] = '0' + numDis(gen); // 將前五位中的一位替換為數字
        break;
    case 4:                                                  // 最後13位包含非數字
        barcode[5 + charDis(gen) % 13] = 'A' + charDis(gen); // 將最後13位中的一位替換為字母
        break;
    }
}

int randomSampling(int risk)
{
}

int main()
{
    int value;
    cout << "Enter the number of samples: ";
    cin >> value;

    vector<string> barcodes;
    string tempBarcode;
    cout << "Enter the barcodes (enter 'done' to finish):\\n";
    while (true)
    {
        cin >> tempBarcode;
        if (tempBarcode == "done")
            break;
        barcodes.push_back(tempBarcode);
    }

    random_device rd;
    mt19937 gen(rd());
    vector<string> invalidBarcodes;

    for (int i = 0; i < value; ++i)
    {
        string selectedBarcode = getRandomBarcode(barcodes, gen);
        cout << "Sampled Barcode: " << selectedBarcode << "\\n";

        if (!isBarcodeValid(selectedBarcode))
        {
            cout << "Error: Invalid barcode.\\n";
            invalidBarcodes.push_back(selectedBarcode);
        }
    }

    cout << "\\nList of invalid barcodes:\\n";
    printInvalidBarcodes(invalidBarcodes);

    return 0;
}
