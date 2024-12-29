#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream> 
#include <iomanip> // for setw, left, right

using namespace std;


class Product {
private:
    static unsigned int ID;
    unsigned int ItemID = 0;
    unsigned int ItemPrice;
    string ItemName;
   
public:
    Product(unsigned int ItemPrice, string ItemName) : ItemPrice(ItemPrice), ItemName(ItemName)
    {
        ID++;
        ItemID = ID;
    }
    void DisplayItem() const
    {
        cout << "Product name: " << ItemName << "\tPrice: " << ItemPrice << "\tItem ID: " << ItemID << endl;
    }
    void SetPrice(unsigned int newPrice) {
        ItemPrice = newPrice;
    }

    unsigned int GetPrice() const {
        return ItemPrice;
    }

    string GetItemName() const {
        return ItemName;
    }

    unsigned int GetID() const {
        return ItemID;
    }
    
};
unsigned int Product::ID = 0;

class Storage {
private:
    unique_ptr<unique_ptr<Product>[]> products;
    unsigned int Capacity;
    unsigned int Size;

    void UpdateCapacity() {
        unsigned int newCapacity = Capacity * 2; 
        unique_ptr<unique_ptr<Product>[]> Newproducts(new unique_ptr<Product>[newCapacity]);
        for (int i = 0; i < Size; i++)
        {
            Newproducts[i] = move(products[i]);
        }
        products = move(Newproducts);
        Capacity = newCapacity;
    }

public:
    Storage(unsigned int Capacity) : Capacity(Capacity), Size(0)
    {
        products = make_unique<unique_ptr<Product>[]>(Capacity);
    }
    void AddProduct(unsigned int ItemPrice, const string &ItemName)
    {
        if (Size == Capacity)
        {
            UpdateCapacity();
        }
        products[Size] = make_unique<Product>(ItemPrice, ItemName);
        Size++;
        
    }

    void RemoveProduct(unsigned int ID) {       
        for (unsigned int i = 0; i < Size; i++) {
            if (products[i]->GetID() == ID) {
                //Move elements after removing
                for (unsigned int j = i; j < Size - 1; j++) {
                    products[j] = move(products[j + 1]);
                }
                //Reseting last element
                products[Size - 1].reset();
                Size--;
                cout << "Product with ID " << ID << " has been removed." << endl;
                return;
            }
        }
        cout << "Item with ID " << ID << " not found!" << endl;
    }


    void Display_Inventory() const {
        for (unsigned int i = 0; i < Size; i++) {
            products[i]->DisplayItem();
        }
    }

    string GetNameofProduct(unsigned int ID) {
        return products[ID - 1]->GetItemName();
    }

    void UpdatePrice(unsigned int itemID, unsigned int newPrice) {
        for (unsigned int i = 0; i < Size; i++) {
            if (products[i]->GetID() == itemID) {
                products[i]->SetPrice(newPrice);
                return;
            }
        }
        cout << "Item with ID " << itemID << " not found!" << endl;
    }

    void UpdateFile(const string &path) {
        ofstream ProductFile;
        ProductFile.open(path);
        for (unsigned int i = 0; i < Size; i++)
        {
            ProductFile << products[i]->GetItemName() << " " << products[i]->GetPrice() << endl;
        }
    }

   
};

class Employee {
private:
    static unsigned int ID;
    unsigned int EmployeeID;
    string Name;
    string Position;
    
public:
    Employee(string Name, string Position) : Name(Name), Position(Position)
    {
        ID++;
        EmployeeID = ID;
    }
    void DisplayEmployee() {
        cout << "Name: " << Name << "\tPosition: " << Position << "\tID: " << EmployeeID << endl;
    }
    string GetName() {
        return Name;
    }
    string GetPosition() {
        return Position;
    }
    unsigned int GetID() {
        return EmployeeID;
    }
    void SetName(string NewName) {
        Name = NewName;
    }
    void SetPosition(string NewPosition) {
        Position = NewPosition;
    }
};
unsigned int Employee::ID = 0;

class EmployeesContainer {
private:
    unique_ptr<unique_ptr<Employee>[]> employees;
    unsigned int Capacity;
    unsigned int Size;

    void UpdateCapacity()
    {
        unsigned int NewCapacity = Capacity * 2;
        unique_ptr < unique_ptr<Employee>[]> NewEmployees(new unique_ptr<Employee>[NewCapacity]);
        for (int i = 0; i < Size; i++)
        {
            NewEmployees[i] = move(employees[i]);
        }
        employees = move(NewEmployees);
        Capacity = NewCapacity;
    }
public:
    EmployeesContainer(unsigned int Capacity) : Capacity(Capacity), Size(0)
    {
        employees = make_unique<unique_ptr<Employee>[]>(Capacity);
    }
    void AddEmployee(const string& Name, const string& Position)
    {
        if (Size == Capacity)
        {
            UpdateCapacity();
        }
        employees[Size] = make_unique<Employee>(Name, Position);
        Size++;
    }
    void RemoveEmployee(unsigned int ID) {
        for (unsigned int i = 0; i < Size; i++) {
            if (employees[i]->GetID() == ID) {
                //Move elements after removing
                for (unsigned int j = i; j < Size - 1; j++) {
                    employees[j] = move(employees[j + 1]);
                }
                //Reseting last element
                employees[Size - 1].reset();
                Size--;
                cout << "Employee with ID " << ID << " has been removed." << endl;
                return;
            }
        }
        cout << "Item with ID " << ID << " not found!" << endl;
    }

    void Display_Employees() const {
        for (unsigned int i = 0; i < Size; i++) {
            employees[i]->DisplayEmployee();
        }
    }
    void UpdatePosition(unsigned int EmployeeID, string newPosition) {
        for (unsigned int i = 0; i < Size; i++) {
            if (employees[i]->GetID() == EmployeeID) {
                employees[i]->SetPosition(newPosition);
                return;
            }
        }
        cout << "Employee with ID " << EmployeeID << " not found!" << endl;
    }

    void UpdateFile(const string& path) {
        ofstream ProductFile;
        ProductFile.open(path);
        for (unsigned int i = 0; i < Size; i++)
        {
            ProductFile << employees[i]->GetName() << " " << employees[i]->GetPosition() << endl;
        }
    }
};

enum DeliveryStatus
{
    Accepted,
    OnWay,
    OnSort,
    Waiting,
    Courier,
    Delivered,
    Returning
};

class Pair {
public:   

    Pair(string CustomerName, string ProductName, unsigned int Amount, string DeliveryAdress, DeliveryStatus DeliveryStatus) : CustomerName(CustomerName), ProductName(ProductName), Amount(Amount), DeliveryAdress(DeliveryAdress), DeliveryStatus(DeliveryStatus){
        ID++;
        PairID = ID;    
    }

    void GetPair() {
        cout << left
            << setw(20) << "Customer Name: " << setw(20) << CustomerName
            << setw(15) << "Product: " << setw(20) << ProductName
            << setw(10) << "Amount: " << setw(10) << Amount
            << setw(15) << "Delivery address: " << setw(20) << DeliveryAdress
            << setw(10) << "Status: " << setw(15) << DeliveryStatusToString(DeliveryStatus)
            << setw(5) << "ID: " << setw(10) << PairID
            << endl;
    }

    //Getters and Setters
    void SetProductName(const unsigned int ID, Storage container[]) {
        string NewProductName = container[ID - 1].GetNameofProduct(ID);
        ProductName = NewProductName;
    }
    string GetProductName() const{
        return ProductName;
    }


    void SetDeliveryAdress(const string& NewDeliveryAdress) {
        DeliveryAdress = NewDeliveryAdress;
    }
    string GetDeliveryAdress() const{
        return DeliveryAdress;
    }


    void SetCustomerName(const string& NewCustomerName) {
        CustomerName = NewCustomerName;
    }
    string GetCustomerName() const{
        return CustomerName;
    }


    void SetAmount(const unsigned int& NewAmount) {
        Amount = NewAmount;
    }
    unsigned int GetAmount() const{
        return Amount;
    }


    unsigned int GetID() const{
        return PairID;
    }


    void SetDeliveryStatus(DeliveryStatus NewDeliveryStatus){
        this->DeliveryStatus = NewDeliveryStatus;
    }
    DeliveryStatus GetDeliveryStatus() const{
        return this->DeliveryStatus;
    }


    string DeliveryStatusToString(DeliveryStatus status) {
        switch (status) {
        case Accepted: return "Accepted";
        case OnWay: return "OnWay";
        case OnSort: return "OnSort";
        case Waiting: return "Waiting";
        case Courier: return "Courier";
        case Delivered: return "Delivered";
        case Returning: return "Returning";
        default: return "Unknown";
        }
    }


private:
    string ProductName;
    string DeliveryAdress;
    DeliveryStatus DeliveryStatus;
    string CustomerName;
    unsigned int Amount;
    static unsigned int ID;
    unsigned int PairID;

};
unsigned int Pair::ID = 0;


class Order {
private:
    unique_ptr<unique_ptr<Pair>[]> orders;
    unsigned int Size;
    unsigned int Capacity;

    void UpdateCapacity()
    {
        unsigned int NewCapacity = Capacity * 2;
        unique_ptr<unique_ptr<Pair>[]> NewOrders(new unique_ptr<Pair>[NewCapacity]);

        for (int i = 0; i < Size; i++)
        {
            NewOrders[i] = move(orders[i]);
        }
        orders = move(NewOrders);
        Capacity = NewCapacity;
    }
public:
    Order(unsigned int Capacity) : Capacity(Capacity), Size(0)
    {
        orders = make_unique<unique_ptr<Pair>[]>(Capacity);
    }

    void AddOrder(string CustomerName, string ProductName, unsigned int Amount, string DeliveryAdress, DeliveryStatus DeliveryStatus) {
        if (Size == Capacity)
        {
            UpdateCapacity();
        }
        orders[Size] = make_unique<Pair>(CustomerName, ProductName, Amount, DeliveryAdress, DeliveryStatus);
        Size++;
    }

    void RemoveOrder(unsigned int ID) {
        for (unsigned int i = 0; i < Size; i++) {
            if (orders[i]->GetID() == ID) {
                //Move elements after removing
                for (unsigned int j = i; j < Size - 1; j++) {
                    orders[j] = move(orders[j + 1]);
                }
                //Reseting last element
                orders[Size - 1].reset();
                Size--;
                cout << "Order with ID " << ID << " has been removed." << endl;
                return;
            }
        }
        cout << "Item with ID " << ID << " not found!" << endl;
    }

    void Display_Orders() const{
        for (unsigned int i = 0; i < Size; i++) {
            orders[i]->GetPair();
        }

    }

    void UpdateDeliveryStatus(const DeliveryStatus& NewDeliveryStatus, const unsigned int& PairID)
    {
        for (unsigned int i = 0; i < Size; i++) {
            if (orders[i]->GetID() == PairID) {
                orders[i]->SetDeliveryStatus(NewDeliveryStatus);
                return;
            }
        }
        cout << "Order with ID " << PairID << " not found!" << endl;
    }   

    void UpdateDeliveryAdress(const string& NewDeliveryAdress, const unsigned int& PairID)
    {
        for (unsigned int i = 0; i < Size; i++) {
            if (orders[i]->GetID() == PairID) {
                orders[i]->SetDeliveryAdress(NewDeliveryAdress);
                return;
            }
        }
        cout << "Order with ID " << PairID << " not found!" << endl;
    }

    void UpdateFile(const string& path) {
        ofstream ProductFile;
        ProductFile.open(path);
        for (unsigned int i = 0; i < Size; i++)
        {
            ProductFile << orders[i]->GetCustomerName() << " " << orders[i]->GetProductName() << " " << orders[i]->GetAmount() << " " << orders[i]->GetDeliveryAdress() << " " << orders[i]->DeliveryStatusToString(orders[i]->GetDeliveryStatus()) << endl;
        }
    }
};
/*string DeliveryStatusToString(DeliveryStatus status) {
    if (status == Accepted) return "Accepted";
    if (status == OnWay) return "OnWay";
    if (status == OnSort) return "OnSort";
    if (status == Waiting) return "Waiting";
    if (status == Courier) return "Courier";
    if (status == Delivered) return "Delivered";
    if (status == Returning) return "Returning";
}*/

DeliveryStatus StringToDeliveryStatus(const string& status) {
    if (status == "Accepted") return Accepted;
    if (status == "OnWay") return OnWay;
    if (status == "OnSort") return OnSort;
    if (status == "Waiting") return Waiting;
    if (status == "Courier") return Courier;
    if (status == "Delivered") return Delivered;
    if (status == "Returning") return Returning;

    throw invalid_argument("Unknown DeliveryStatus: " + status);
}

void ReadProductData(const string& pathProduct, Storage& storagecontainer) {
    try {
        ifstream ProductFile(pathProduct);

        string line;
        if (ProductFile.is_open()) {

            string productName;
            unsigned int productPrice;
            while (getline(ProductFile, line)) {
                istringstream iss(line);
                iss >> productName >> productPrice;
                storagecontainer.AddProduct(productPrice, productName);
            }

            ProductFile.close();
        }
    }
    catch (const exception& ex)
    {
        cerr << "Error while opening or processing the Product file " << endl;
    }

    

}

void ReadEmployeeData(const string& pathEmployee, EmployeesContainer& employeecontainer) {
    try {
        ifstream EmployeeFile(pathEmployee);

        string line;
        if (EmployeeFile.is_open()) {

            string EmployeeName;
            string EmployeePosition;
            while (getline(EmployeeFile, line)) {
                istringstream iss(line);
                iss >> EmployeeName >> EmployeePosition;
                employeecontainer.AddEmployee(EmployeeName, EmployeePosition);
            }

            EmployeeFile.close();
        }
    }
    catch (const exception& ex)
    {
        cerr << "Error while opening or processing the Employee file" << endl;
    }
}

void ReadOrdersData(const string& pathOrders, Order& orderscontainer) {
    try {
        ifstream OrdersFile(pathOrders);

        string line;
        if (OrdersFile.is_open()) {

            string CustomerName;
            string ProductName;
            unsigned int Amount;
            string DeliveryAdress;
            DeliveryStatus DeliveryStatus;
            string S_DeliveryStatus;
            while (getline(OrdersFile, line)) {
                istringstream iss(line);
                iss >> CustomerName >> ProductName >> Amount >> DeliveryAdress >> S_DeliveryStatus;
                DeliveryStatus = StringToDeliveryStatus(S_DeliveryStatus);
                orderscontainer.AddOrder(CustomerName, ProductName, Amount, DeliveryAdress, DeliveryStatus);
            }

            OrdersFile.close();
        }
    }
    catch (const exception& ex)
    {
        cerr << "Error while opening or processing the Orders file" << endl;
    }
}



int main()
{


    string Productpath = "ProductData.txt";
    string Employeepath = "EmployeeData.txt";
    string Orderspath = "OrdersData.txt";
    Storage inventory(10);
    EmployeesContainer employees(10);
    Order orders(10);
    ReadProductData(Productpath, inventory);            
    ReadEmployeeData(Employeepath, employees);
    ReadOrdersData(Orderspath, orders);


    while (true)
    {
        while (true) {
            cout << "\nChoose an option:\n";
            cout << "1. Display products\n";
            cout << "2. Add product\n";
            cout << "3. Update product price\n";
            cout << "4. Display employees\n";
            cout << "5. Add employee\n";
            cout << "6. Update employee position\n";
            cout << "7. Display orders\n";
            cout << "8. Add order\n";
            cout << "9. Update order delivery status\n";
            cout << "10. Exit\n";
            cout << "11. Remove product\n";
            cout << "12. Remove employee\n";
            cout << "13. Remove order\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
            case 1: {
                inventory.Display_Inventory();
                break;
            }
            case 2: {
                string name;
                unsigned int price;
                cout << "Enter product name: ";
                cin >> name;
                cout << "Enter product price: ";
                cin >> price;
                inventory.AddProduct(price, name);
                break;
            }
            case 3: {
                unsigned int id, newPrice;
                cout << "Enter product ID to update: ";
                cin >> id;
                cout << "Enter new price: ";
                cin >> newPrice;
                inventory.UpdatePrice(id, newPrice);
                break;
            }
            case 4: {
                employees.Display_Employees();
                break;
            }
            case 5: {
                string name, position;
                cout << "Enter employee name: ";
                cin >> name;
                cout << "Enter employee position: ";
                cin >> position;
                employees.AddEmployee(name, position);
                break;
            }
            case 6: {
                unsigned int id;
                string newPosition;
                cout << "Enter employee ID to update: ";
                cin >> id;
                cout << "Enter new position: ";
                cin >> newPosition;
                employees.UpdatePosition(id, newPosition);
                break;
            }
            case 7: {
                orders.Display_Orders();
                break;
            }
            case 8: {
                string customerName, productName, deliveryAddress, deliveryStatusStr;
                unsigned int amount;
                DeliveryStatus deliveryStatus;
                cout << "Enter customer name: ";
                cin >> customerName;
                cout << "Enter product name: ";
                cin >> productName;
                cout << "Enter amount: ";
                cin >> amount;
                cout << "Enter delivery address: ";
                cin.ignore();
                getline(cin, deliveryAddress);
                cout << "Enter delivery status (Accepted/OnWay/OnSort/Waiting/Courier/Delivered/Returning): ";
                cin >> deliveryStatusStr;
                deliveryStatus = StringToDeliveryStatus(deliveryStatusStr);
                orders.AddOrder(customerName, productName, amount, deliveryAddress, deliveryStatus);
                break;
            }
            case 9: {
                unsigned int orderId;
                string deliveryStatusStr;
                DeliveryStatus newStatus;
                cout << "Enter order ID to update: ";
                cin >> orderId;
                cout << "Enter new delivery status (Accepted/OnWay/OnSort/Waiting/Courier/Delivered/Returning): ";
                cin >> deliveryStatusStr;
                newStatus = StringToDeliveryStatus(deliveryStatusStr);
                orders.UpdateDeliveryStatus(newStatus, orderId);
                break;
            }
            case 10: {
                cout << "Exiting program.\n";
                inventory.UpdateFile(Productpath);
                employees.UpdateFile(Employeepath);
                orders.UpdateFile(Orderspath);
                return 0;
            }
            case 11: {
                unsigned int ProductID;
                cout << "Enter ID: ";
                cin >> ProductID;
                cout << "\n";
                inventory.RemoveProduct(ProductID);
                break;
            }
            case 12: {
                unsigned int EmployeeID;
                cout << "Enter ID: ";
                cin >> EmployeeID;
                cout << "\n";
                employees.RemoveEmployee(EmployeeID);
                break;
            }
            case 13: {
                unsigned int OrderID;
                cout << "Enter ID: ";
                cin >> OrderID;
                cout << "\n";
                orders.RemoveOrder(OrderID);
                break;
            }
            default: {
                cout << "Invalid choice. Try again.\n";
            }
            }
        }
    }
    return 0;
}

