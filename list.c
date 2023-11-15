#include <stdio.h>
#include <string.h>

typedef struct
{
    char name_of_order[50];
    float price;
    int quantity_bought;
} Order;

void append_array(int *last_index, Order orders[], Order order_to_be_added);

void main()
{
    Order order_1, order_2, order_3, order_4, order_5;
    Order order5;
    Order orders[] = {order_1, order_2, order_3};
    strcpy(orders[0].name_of_order, "Frappucino");
    orders[0].price = 69.99;
    strcpy(orders[1].name_of_order, "Kopiko Brown");
    orders[1].price = 10.00;
    strcpy(orders[2].name_of_order, "Milo");
    orders[2].price = 20.00;
    strcpy(order_4.name_of_order, "Coke");
    order_4.price = 9;
    strcpy(order_5.name_of_order, "Pepsi");
    order_5.price = 1;
    printf("\n   Name: \t\t Price:\n");
    int last_index = sizeof(orders) / sizeof(orders[0]);
    append_array(&last_index, orders, order_4);
    append_array(&last_index, orders, order_5);
    for (int i = 0; i < last_index; i++)
    {
        printf("\n%d: %-14s\t %.2f php\n", i + 1, orders[i].name_of_order, orders[i].price);
    }
}

void append_array(int *last_index, Order orders[], Order order_to_be_added)
{
    orders[*last_index] = order_to_be_added;
    *last_index += 1;
}