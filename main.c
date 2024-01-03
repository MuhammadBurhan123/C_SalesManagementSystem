#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 25
#define FILENAME "sales.txt"

// Define the Product structure
struct Product {
    char name[50];
    int code;
    float unitPrice;
    int quantity;
    float totalSalesValue;
};

// Function to load product information from a file
void loadSalesData(struct Product products[], int size) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < size; ++i) {
        fscanf(file, "%s %d %f %d %f",
               products[i].name,
               &products[i].code,
               &products[i].unitPrice,
               &products[i].quantity,
               &products[i].totalSalesValue);
    }

    fclose(file);
}

// Function to input product information from the user
void inputSalesData(struct Product *product) {
    printf("Enter product name: ");
    scanf("%s", product->name);

    printf("Enter product code: ");
    scanf("%d", &product->code);

    printf("Enter unit price: ");
    scanf("%f", &product->unitPrice);

    printf("Enter quantity in stock: ");
    scanf("%d", &product->quantity);

    // Initialize total sales value to 0 initially
    product->totalSalesValue = 0;
}

// Function to calculate total sales value and update the structure
void calculateSalesValue(struct Product *product) {
    product->totalSalesValue = product->unitPrice * product->quantity;
}

// Recursive function to adjust stock based on certain conditions
void adjustStock(struct Product *product) {
    // Your recursive logic goes here
    // For example, reduce quantity by 10% if it's above a certain threshold
    if (product->quantity > 100) {
        product->quantity -= product->quantity * 0.10;
    }
}

// Function to display product information
void displaySalesInfo(struct Product products[], int size) {
    printf("%-20s %-10s %-15s %-20s %-20s\n",
           "Product Name", "Product Code", "Unit Price", "Quantity in Stock", "Total Sales Value");

    for (int i = 0; i < size; ++i) {
        printf("%-20s %-10d %-15.2f %-20d %-20.2f\n",
               products[i].name,
               products[i].code,
               products[i].unitPrice,
               products[i].quantity,
               products[i].totalSalesValue);
    }
}

int main() {
    // Declare an array of Product structures
    struct Product inventory[MAX_PRODUCTS];

    // Load data from the file (if available)
    loadSalesData(inventory, MAX_PRODUCTS);

    // Input data for each product
    for (int i = 0; i < MAX_PRODUCTS; ++i) {
        inputSalesData(&inventory[i]);

        // Calculate total sales value for each product
        calculateSalesValue(&inventory[i]);
    }

    // Adjust stock based on certain conditions (recursive function)
    for (int i = 0; i < MAX_PRODUCTS; ++i) {
        adjustStock(&inventory[i]);
    }

    // Display product information
    displaySalesInfo(inventory, MAX_PRODUCTS);

    // Save data to the file
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return 1;
    }

    for (int i = 0; i < MAX_PRODUCTS; ++i) {
        fprintf(file, "%s %d %.2f %d %.2f\n",
                inventory[i].name,
                inventory[i].code,
                inventory[i].unitPrice,
                inventory[i].quantity,
                inventory[i].totalSalesValue);
    }

    fclose(file);

    return 0;
}
