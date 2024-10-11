#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Product {
    string name;
    string category;
    double price;
    int quantity;
};

void showProduct(const Product& product) {
    cout << "________________: "  << endl;
    cout << "Product Name: " << product.name << endl;
    cout << "Category: " << product.category << endl;
    cout << "Price: $" << product.price << endl;
    cout << "Quantity in stock: " << product.quantity << endl;
}

void addProduct(vector<Product>& products) {
    Product product;
    cout << "Enter product name: ";
    cin.ignore();
    getline(cin, product.name);
    cout << "Enter product category: ";
    getline(cin, product.category);
    cout << "Enter product price: ";
    cin >> product.price;
    cout << "Enter quantity in stock: ";
    cin >> product.quantity;
    products.push_back(product);
    cout << "Product added successfully!" << endl;
}

void saveToFile(const vector<Product>& products, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& product : products) {
            file << product.name << "," << product.category << "," << product.price << "," << product.quantity << endl;
        }
        cout << "Data saved to file successfully." << endl;
    }
    else {
        cout << "Error opening file." << endl;
    }
}

void loadFromFile(vector<Product>& products, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        products.clear();
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                Product product;
                size_t pos = 0;
                product.name = line.substr(0, (pos = line.find(',')));
                line.erase(0, pos + 1);
                product.category = line.substr(0, (pos = line.find(',')));
                line.erase(0, pos + 1);
                product.price = stod(line.substr(0, (pos = line.find(','))));
                line.erase(0, pos + 1);
                product.quantity = stoi(line);
                products.push_back(product);
            }
        }
        cout << "Data loaded from file successfully." << endl;
    }
    else {
        cout << "File not found." << endl;
    }
}

void showProducts(const vector<Product>& products) {
    if (products.empty()) {
        cout << "No products available." << endl;
        return;
    }
    for (const auto& product : products) {
        showProduct(product);
    }
}

void searchProducts(const vector<Product>& products) {
    string searchTerm;
    cout << "Enter search term: ";
    cin.ignore();
    getline(cin, searchTerm);

    bool found = false;
    for (const auto& product : products) {

        if (product.name.find(searchTerm) < product.name.length()) {
            showProduct(product);
            found = true;
        }
        if (product.category.find(searchTerm) < product.category.length()) {
            showProduct(product);
            found = true;
        }
    }
    if (!found) {
        cout << "No products found." << endl;
    }
}

void menu(vector<Product>& products, const string& filename) {
    int choice;
    while (true) {
        cout << "\n Product Store Menu " << endl;
        cout << "1. Add new product" << endl;
        cout << "2. Show all products" << endl;
        cout << "3. Search for product" << endl;
        cout << "4. Save products to file" << endl;
        cout << "5. Load products from file" << endl;
        cout << "1-5:";
        cin >> choice;

        if (!cin >> choice) {
            cin.clear();  
            while (cin.get() != '\n');
            cout << "Invalid input." << endl;
        }
        else {
        }


        switch (choice) {
        case 1: addProduct(products); break;
        case 2: showProducts(products); break;
        case 3: searchProducts(products); break;
        case 4: saveToFile(products, filename); break;
        case 5: loadFromFile(products, filename); break;
        default: cout << "Invalid option. " << endl; break;
        }
    }
}

int main() {
    vector<Product> products;
    string filename = "products.txt";
    loadFromFile(products, filename);
    menu(products, filename);
}
