#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product {
    int id;
    char name[50];
    int quantity;
    float price;
    char supplier[50];
};

// Function declarations
void addProduct();
void displayProducts();
void searchProduct();
void updateQuantity();
void updatePrice();
void deleteProduct();

int main() {
    int choice;

    while (1) {
        printf("\n===== Inventory Management System =====\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Search Product\n");
        printf("4. Update Quantity\n");
        printf("5. Update Price\n");
        printf("6. Delete Product\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addProduct(); break;
            case 2: displayProducts(); break;
            case 3: searchProduct(); break;
            case 4: updateQuantity(); break;
            case 5: updatePrice(); break;
            case 6: deleteProduct(); break;
            case 7: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

// Add product
void addProduct() {
    struct Product p;
    FILE *fp = fopen("inventory.dat", "ab");

    printf("Enter ID: ");
    scanf("%d", &p.id);
    printf("Enter Name: ");
    scanf("%s", p.name);
    printf("Enter Quantity: ");
    scanf("%d", &p.quantity);
    printf("Enter Price: ");
    scanf("%f", &p.price);
    printf("Enter Supplier: ");
    scanf("%s", p.supplier);

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);

    printf("Product added successfully!\n");
}

// Display products
void displayProducts() {
    struct Product p;
    FILE *fp = fopen("inventory.dat", "rb");

    printf("\nID\tName\tQty\tPrice\tSupplier\n");
    printf("------------------------------------------------\n");

    while (fread(&p, sizeof(p), 1, fp)) {
        printf("%d\t%s\t%d\t%.2f\t%s\n", p.id, p.name, p.quantity, p.price, p.supplier);
    }

    fclose(fp);
}

// Search product
void searchProduct() {
    struct Product p;
    int id, found = 0;
    FILE *fp = fopen("inventory.dat", "rb");

    printf("Enter Product ID to search: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("Found: %d %s %d %.2f %s\n", p.id, p.name, p.quantity, p.price, p.supplier);
            found = 1;
        }
    }

    if (!found)
        printf("Product not found!\n");

    fclose(fp);
}

// Update quantity
void updateQuantity() {
    struct Product p;
    int id, found = 0;
    FILE *fp = fopen("inventory.dat", "rb+");

    printf("Enter Product ID: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("Enter new quantity: ");
            scanf("%d", &p.quantity);

            fseek(fp, -sizeof(p), SEEK_CUR);
            fwrite(&p, sizeof(p), 1, fp);

            found = 1;
            printf("Quantity updated!\n");
            break;
        }
    }

    if (!found)
        printf("Product not found!\n");

    fclose(fp);
}

// Update price
void updatePrice() {
    struct Product p;
    int id, found = 0;
    FILE *fp = fopen("inventory.dat", "rb+");

    printf("Enter Product ID: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("Enter new price: ");
            scanf("%f", &p.price);

            fseek(fp, -sizeof(p), SEEK_CUR);
            fwrite(&p, sizeof(p), 1, fp);

            found = 1;
            printf("Price updated!\n");
            break;
        }
    }

    if (!found)
        printf("Product not found!\n");

    fclose(fp);
}

// Delete product
void deleteProduct() {
    struct Product p;
    int id;
    FILE *fp = fopen("inventory.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    printf("Enter Product ID to delete: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id != id) {
            fwrite(&p, sizeof(p), 1, temp);
        }
    }
    fclose(fp);
    fclose(temp);

    remove("inventory.dat");
    rename("temp.dat", "inventory.dat");

    printf("Product deleted successfully!\n");
}
