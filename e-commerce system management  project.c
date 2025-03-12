#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures
typedef struct Product {
    char name[50];
    float price;
    int stock;
    struct Product* next;
} Product;

typedef struct CartItem {
    char productName[50];
    int quantity;
    float price;
    struct CartItem* next;
} CartItem;

Product* productList = NULL;
CartItem* cart = NULL;

// Function Prototypes
void addProduct();
void displayProducts();
void addToCart();
void displayCart();
void checkout();
Product* findProduct(char* productName);
void freeProductList();
void freeCart();

int main() {
    int choice;

    do {
        printf("\nSimple E-commerce System\n");
        printf("1. Add Product\n2. Display Products\n3. Add to Cart\n4. Display Cart\n5. Checkout\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1: addProduct(); break;
            case 2: displayProducts(); break;
            case 3: addToCart(); break;
            case 4: displayCart(); break;
            case 5: checkout(); break;
            case 6: freeProductList();freeCart(); exit(0);
            default: printf("Invalid choice.\n");
        }
    } while (1);

    return 0;
}

void addProduct() {
    Product* newProduct = (Product*)malloc(sizeof(Product));
    printf("Enter product name: ");
    fgets(newProduct->name, sizeof(newProduct->name), stdin);
    newProduct->name[strcspn(newProduct->name, "\n")] = 0;
    printf("Enter product price: ");
    scanf("%f", &newProduct->price);
    printf("Enter product stock: ");
    scanf("%d", &newProduct->stock);
    getchar(); // Consume newline

    newProduct->next = productList;
    productList = newProduct;
    printf("Product added successfully.\n");
}

void displayProducts() {
    Product* current = productList;
    if (!current) {
        printf("No products available.\n");
        return;
    }

    printf("\nProducts:\n");
    while (current) {
        printf("- %s: %.2f (Stock: %d)\n", current->name, current->price, current->stock);
        current = current->next;
    }
}

void addToCart() {
    char productName[50];
    int quantity;

    printf("Enter product name: ");
    fgets(productName, sizeof(productName), stdin);
    productName[strcspn(productName, "\n")] = 0;

    Product* product = findProduct(productName);
    if (!product) {
        printf("Product not found.\n");
        return;
    }

    printf("Enter quantity: ");
    scanf("%d", &quantity);
    getchar(); // Consume newline

    if (product->stock < quantity) {
        printf("Insufficient stock.\n");
        return;
    }

    CartItem* newCartItem = (CartItem*)malloc(sizeof(CartItem));
    strcpy(newCartItem->productName, product->name);
    newCartItem->quantity = quantity;
    newCartItem->price = product->price * quantity;
    newCartItem->next = cart;
    cart = newCartItem;

    product->stock -= quantity;
    printf("Product added to cart.\n");
}

void displayCart() {
    CartItem* current = cart;
    if (!current) {
        printf("Cart is empty.\n");
        return;
    }

    printf("\nCart:\n");
    float total = 0;
    while (current) {
        printf("- %s: %d x %.2f = %.2f\n", current->productName, current->quantity, current->price / current->quantity, current->price);
        total += current->price;
        current = current->next;
    }
    printf("Total: %.2f\n", total);
}

void checkout() {
    displayCart();
    freeCart();
    printf("Checkout completed.\n");
}

Product* findProduct(char* productName) {
    Product* current = productList;
    while (current) {
        if (strcmp(current->name, productName) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void freeProductList(){
    Product* current = productList;
    while(current){
        Product* temp = current;
        current = current->next;
        free(temp);
    }
    productList = NULL;
}

void freeCart(){
    CartItem* current = cart;
    while(current){
        CartItem* temp = current;
        current = current->next;
        free(temp);
    }
    cart = NULL;
}
