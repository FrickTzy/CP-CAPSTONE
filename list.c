#include <stdio.h>
#include <string.h>

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

void add_order(int *last_index, OrderedOrder orders[], Order order, int quantity);
OrderedOrder make_order(Order order, int quantity);
float get_price(Order order, int quantity);
float get_total_price(OrderedOrder orders[], int size);

void main()
{
    int size = 0;
    Order frappucino = {"Frappucino", 69.99};
    Order kopikoBrown = {"Kopiko Brown", 10.00};
    Order milo = {"Milo", 20.00};
    Order coke = {"Coke", 9};
    Order pepsi = {"Pepsi", 10};
    Order blank = {"", 0};
    Order orders[] = {frappucino, kopikoBrown, milo, pepsi, coke};
    OrderedOrder orderedOrder[] = {};
    printf("\n   Name: \t\t Price: \t Quantity:\n");
    add_order(&size, orderedOrder, frappucino, 2);
    add_order(&size, orderedOrder, kopikoBrown, 100);
    add_order(&size, orderedOrder, milo, 20);
    add_order(&size, orderedOrder, coke, 1000);
    for (int i = 0; i < size; i++)
    {
        printf("\n%d: %-14s\t %.2f php \t %d\t  |    %.2f php\n", i + 1, orderedOrder[i].order.name_of_order,
               orderedOrder[i].order.price, orderedOrder[i].quantity, orderedOrder[i].total_price);
    }
    printf("-----------------------------------------------------------------------");
    printf("\n\n\t\t\t\t\t\tTotal: %.2f php", get_total_price(orderedOrder, size));
}

void add_order(int *last_index, OrderedOrder orders[], Order order, int quantity)
{
    orders[*last_index] = make_order(order, quantity);
    *last_index += 1;
}

OrderedOrder make_order(Order order, int quantity)
{
    OrderedOrder ordered_order = {order, quantity, get_price(order, quantity)};
    return ordered_order;
}

float get_price(Order order, int quantity)
{
    return order.price * quantity;
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