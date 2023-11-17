#include <stdio.h>
#include <string.h>
#include <stdbool.h>
typedef struct
{
    char name_of_order[50];
    float price;
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
float get_price(Order order, int quantity);
bool add_orders(int order, Order orders[], OrderedOrder order_to_be_added[], int *size, int quantity);
float get_total_price(OrderedOrder orders[], int size);
void print_reciept(int size, OrderedOrder orderedOrder[]);

int main()
{
    // Declare Variables
    int size = 0;
    bool running = true;

    // Initialize Orders
    Order frappucino = {"Frappucino", 69.99};
    Order kopiko_brown = {"Kopiko Brown", 10.00};
    Order milo = {"Milo", 20.00};
    Order coke = {"Coke", 9};
    Order pepsi = {"Pepsi", 10};
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
        if (add_orders(order, orders, orderedOrder, &size, quantity) == false)
        {
            printf("Bye!");
            return 0;
        }
    }
    print_reciept(size, orderedOrder);
    return 0;
}

float get_price(Order order, int quantity)
{
    return order.price * quantity;
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
        printf("\n%d: %-14s\t |  %.2f php\n", i + 1, orders[i].name_of_order,
               orders[i].price);
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
    OrderedOrder ordered_order = {order, quantity, get_price(order, quantity)};
    orders_to_be_added[*last_index] = ordered_order;
    printf("\nAdded!\n");
    *last_index += 1;
}