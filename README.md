# OnlineStoreManagmentSystem
 
1. Product class
Purpose: Represents a product.
Fields:
A static counter ID for generating a unique product identifier.
The name of the product ItemName (type std::string).
The price of the product ItemPrice (can be a string or a numeric type).
Methods:
Constructor: accepts the name and price, assigns a unique ID.
DisplayItem: displays information about the product.
The smart pointer unique_ptr is used to store the product in memory to avoid leaks.
2. Order class
Purpose: Represents an order.
Fields:
OrderID (automatically generated).
The list of products (a vector or array of Product - Quantity pairs, managed via smart pointers).
The total cost of the order.
The order status (an enum with the states New, Processing, Shipped, Delivered, Cancelled).
Methods:
Adding a product to an order: updates the list and cost.
Changing the order status (next_status and prev_status).
Output of information about the order.
3. Pair class (Class template)
Purpose: Represents the pair "Product - Quantity".
Methods:
Setting the product and quantity values.
Getting the values.
Comparing two pairs.
4. Working with files
Purpose: Saves data about products and orders to files.
Methods:
Reading data at program startup: handles errors of missing files or incorrect data format.
Saving data about products and orders at program termination.
5. Exception handling
Purpose: Checks user input and data correctness.
Checks the correctness of the product ID.
Checks if there is enough product in stock.
Checks for division by zero when calculating the cost (if a coefficient is used).
6. Employee class
Purpose: Represents a store employee.
Fields:
A static counter ID for generating a unique identifier.
The employee's name Name (type std::string).
The employee's role Role (for example, Manager, Cashier).
Methods:
Generate a unique ID.
Output employee information.
7. Discount calculator
Purpose: Calculates the final price of the product taking into account the discount.
DiscountCalculator class (template):
Supports various data types for the price (int, double, etc.).
Checks the correctness of the discount percentage (0–100%).
Calculates and returns the final cost.
8. Main function logic
All classes and methods are combined in main:

Loading product and employee data from files.
Displaying a list of products and orders.
Adding new products and orders.
Changing the status of orders via the user interface.
Calculating discounts on products.
Saving all changes to files.