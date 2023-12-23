#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Product {
    string name;
    float price;
};

vector<Product> products;
vector<float> prices;

void LoadValues();

void NewClient();

void DisplaySales();

void DisplayCatalog();


int main() {
    LoadValues();
    int sel = 0;
    while (true) {
        cout << "SUPERMARKET SYSTEM\n\n";
        cout << "[1] New client\n";
        cout << "[2] View Catalog\n";
        cout << "[3] View sales\n";
        cout << "[4] Exit\n";
        cout << "Select > ";
        cin >> sel;
        switch (sel) {
            case 1:
                NewClient();
                break;
            case 2:
                DisplayCatalog();
                break;
            case 3:
                DisplaySales();
                break;
            case 4:
                return 0;
        }
    }
}

void LoadValues() {
    string temp;
    float tval = 0.0;
    ifstream productInfo("products.dat");
    if (productInfo.is_open()) {
        while (productInfo >> temp) {
            Product product;
            product.name = temp;
            productInfo >> temp;
            tval = atof(temp.c_str());
            product.price = tval;
            products.push_back(product);
            prices.push_back(tval);
        }
        productInfo.close();
    } else {
        cout << "Failed to open products.dat\n";
    }
}

void NewClient() {
    int id = 0;
    int qty = 0;
    int itemqty = 0;
    float sum = 0.0;
    ofstream sales("sales.dat", ios::app);
    if (!sales.is_open()) {
        cout << "Failed to open sales.dat\n";
        return;
    }

    cout << "NEW SALE\n";
    cout << "INSTRUCTIONS:\n";
    cout << "Enter the ID of the product. After this, enter the quantity and press enter\n";
    cout << "If you have finished, enter -1 on product and will exit\n\n";
    while (true) {
        cout << "Enter product ID: ";
        cin >> id;

        if (id == -1) {
            break;
        }

        if (id < 0 || id >= products.size()) {
            cout << "Invalid product ID. Please enter a valid ID.\n";
            continue;
        }

        cout << "Enter quantity: ";
        cin >> qty;

        float value = products[id].price * qty;
        sum = sum + value;
        itemqty++;
        cout << endl;
    }

    float tax = (sum * 0.0825);
    float total = (sum + (sum * 0.0825));

    cout << "\nYou have bought " << itemqty << " items\n";
    cout << "Subtotal: " << sum << endl;
    cout << "Tax: " << tax << endl;
    cout << "Total: " << total << endl;

    float money = 0.0;
    while (true) {
        cout << "Money: ";
        cin >> money;
        if (money >= sum) {
            cout << "Your change is " << (money - total) << endl;
            cout << "Thanks for shopping. Returning to main";
            break;
        }
        cout << "Not enough money. Re-enter money\n";
    }

    sales << itemqty << "\t" << total << endl;
    sales.close();
}

void DisplayCatalog() {
    cout << "Product catalog\n\n";
    cout << "ID\tPRODUCT\tPRICE\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < products.size(); ++i) {
        cout << i << "\t" << products[i].name << "\t" << products[i].price << endl;
    }

    cout << "\n\n";
}

void DisplaySales() {
    cout << "SUPERMARKET SALES\n\n";
    cout << "Stats\n";
    string temp;
    int salesCount = 0;
    int itemCount = 0;
    float sumCount = 0;
    float tval = 0.0;
    ifstream salesFile("sales.dat");

    if (salesFile.is_open()) {
        while (salesFile >> temp) {
            salesCount++;
            tval = atof(temp.c_str());
            itemCount += tval;
            salesFile >> temp;
            tval = atof(temp.c_str());
            sumCount += tval;
        }
        salesFile.close();
    } else {
        cout << "SALES FILE NOT FOUND! Data cannot be generated\n\n";
        return;
    }

    cout << "Total of sales: " << salesCount << endl;
    cout << "Total of items sold: " << itemCount << endl;
    cout << "Total earnings: " << sumCount << endl;
    cout << "\n\n";
}
