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

void append_array(int *last_index, OrderedOrder orders[], OrderedOrder order_to_be_added);
OrderedOrder make_order(Order order, int quantity);
float get_price(Order order, int quantity);

void main()
{
    Order frappucino = {"Frappucino", 69.99};
    Order kopikoBrown = {"Kopiko Brown", 10.00};
    Order milo = {"Milo", 20.00};
    Order coke = {"Coke", 9};
    Order pepsi = {"Pepsi", 10};
    Order blank = {"", 0};
    Order orders[] = {frappucino, kopikoBrown, milo, pepsi, coke};
    OrderedOrder orderedOrder[] = {};
    printf("\n   Name: \t\t Price: \t Quantity: \t\t Total Price:  \n");
    int size = 0;
    append_array(&size, orderedOrder, make_order(frappucino, 3));
    for (int i = 0; i < size; i++)
    {
        printf("\n%d: %-14s\t %.2f php \t %d\t %.2f\n", i + 1, orderedOrder[i].order.name_of_order,
               orderedOrder[i].order.price, orderedOrder[i].quantity, orderedOrder[i].total_price);
    }
}

void append_array(int *last_index, OrderedOrder orders[], OrderedOrder order_to_be_added)
{
    orders[*last_index] = order_to_be_added;
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