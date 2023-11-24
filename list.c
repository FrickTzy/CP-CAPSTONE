#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    char name_of_order[50];
    float price;
    int amount_of_products;
} Order;

typedef struct
{
    Order order;
    int quantity;
    float total_price;
} OrderedOrder;

void add_order(int *last_index, OrderedOrder orders_to_be_added[], Order order, int quantity);
OrderedOrder make_order(Order order, int quantity);
void print_orders(int size, Order orders[]);
float get_price(float price, int quantity);
bool add_orders(int order, Order orders[], OrderedOrder order_to_be_added[], int *size, int quantity);
float get_total_price(OrderedOrder orders[], int size);
void print_reciept(int size, OrderedOrder orderedOrder[]);
void subtract_product (Order order, int quantity);

int main()
{
    // Declare Variables
    int size = 0;
    bool running = true;
    srand(time(NULL));

    // Initialize Orders
    Order frappucino = {"Frappucino", 69.99,100 + rand() % 100};
    Order kopiko_brown = {"Kopiko Brown", 10.00,100 + rand() % 100};
    Order milo = {"Milo", 20.00,100 + rand() % 100};
    Order coke = {"Coke", 9,100 + rand() % 100};
    Order pepsi = {"Pepsi", 10,100 + rand() % 100};
    Order orders[] = {frappucino, kopiko_brown, milo, pepsi, coke};

    OrderedOrder orderedOrder[100];

    while (running)
    {
        int order = 0;
        int quantity = 0;
        print_orders(sizeof(orders) / sizeof(orders[0]), orders);
        printf("\nWhat's your order? (Type '69' to pay!) ");
        scanf("%d", &order);
        if (order == 69)
        {
            running = false;
            break;
        }
        printf("How much? ");
        scanf("%d", &quantity);
        subtract_product (orders[order-1], quantity);
        if (add_orders(order, orders, orderedOrder, &size, quantity) == false)
        {
            printf("Bye!");
            return 0;
        }
    }
    print_reciept(size, orderedOrder);
    return 0;
}

float get_price(float price, int quantity)
{
    return price * quantity;
}

void print_reciept(int size, OrderedOrder orderedOrder[])
{
    printf("\n   Name: \t\t Price: \t Quantity:\n");
    for (int i = 0; i < size; i++)
    {
        printf("\n%d: %-14s\t %.2f php \t %d\t  |    %.2f php\n", i + 1, orderedOrder[i].order.name_of_order,
               orderedOrder[i].order.price, orderedOrder[i].quantity, orderedOrder[i].total_price);
    }
    printf("-----------------------------------------------------------------------");
    printf("\n\n\t\t\t\t\t\tTotal: %.2f php", get_total_price(orderedOrder, size));
}

float get_total_price(OrderedOrder orders[], int size)
{
    float total_price = 0;
    for (int i = 0; i < size; i++)
    {
        total_price += orders[i].total_price;
    }
    return total_price;
}

void print_orders(int size, Order orders[])
{
    for (int i = 0; i < size; i++)
    {
        printf("\n%d: %-14s\t |  %.2f php\t %d\n", i + 1, orders[i].name_of_order,
               orders[i].price,orders[i].amount_of_products);
    }
}

bool add_orders(int order, Order orders[], OrderedOrder order_to_be_added[], int *size, int quantity)
{
    if (order == 0)
    {
        return false;
    }
    order = order - 1;
    add_order(size, order_to_be_added, orders[order], quantity);
    return true;
}

void add_order(int *last_index, OrderedOrder orders_to_be_added[], Order order, int quantity)
{
    OrderedOrder ordered_order = {order, quantity, get_price(order.price, quantity)};
    orders_to_be_added[*last_index] = ordered_order;
    printf("\nAdded!\n");
    *last_index += 1;
}
void subtract_product (Order order, int quantity) {
    order.amount_of_products-=quantity;
}