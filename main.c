#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 25
#define FILENAME "sales.txt"

struct Product {
    char name[50];
    int code;
    float unitPrice;
    int quantity;
    float totalSalesValue;
};

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

void inputSalesData(struct Product *product) {
    printf("Enter product name: ");
    scanf("%s", product->name);

    printf("Enter product code: ");
    scanf("%d", &product->code);

    printf("Enter unit price: ");
    scanf("%f", &product->unitPrice);

    printf("Enter quantity in stock: ");
    scanf("%d", &product->quantity);

    product->totalSalesValue = 0;
}

void calculateSalesValue(struct Product *product) {
    product->totalSalesValue = product->unitPrice * product->quantity;
}

void adjustStock(struct Product *product) {
    if (product->quantity > 100) {
        product->quantity -= product->quantity * 0.10;
    }
}

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
    struct Product inventory[MAX_PRODUCTS];

    loadSalesData(inventory, MAX_PRODUCTS);

    for (int i = 0; i < MAX_PRODUCTS; ++i) {
        inputSalesData(&inventory[i]);

        calculateSalesValue(&inventory[i]);
    }

    for (int i = 0; i < MAX_PRODUCTS; ++i) {
        adjustStock(&inventory[i]);
    }

    displaySalesInfo(inventory, MAX_PRODUCTS);

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
