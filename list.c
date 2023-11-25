#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct
{
    char value[100];
} String;
typedef struct
{
    char name_of_order[50];
    float price;
    int amount_of_products;
    bool has_flavors;
    char *flavors[4];
    String flavor;
} Order;
typedef struct
{
    Order order;
    int quantity;
    float total_price;
} OrderedOrder;

void add_order(int *last_index, OrderedOrder orders_to_be_added[], Order order, int quantity, String flavor);
OrderedOrder make_order(Order order, int quantity);
void print_orders(int size, Order orders[]);
float get_price(float price, int quantity);
bool add_orders(int order, Order orders[], OrderedOrder order_to_be_added[], int *size, int quantity, String flavor);
float get_total_price(OrderedOrder orders[], int size);
void print_reciept(int size, OrderedOrder orderedOrder[]);
void subtract_product(Order *order, int quantity);
void print_flavors(char *flavors[]);

int main()
{

    // title
    printf("\n_______________________________________________________________________________________");
    printf("                                                                                       \n"
           ",------.  ,------. ,------.  ,---.  ,--.   ,--.    ,-----.    ,---.  ,--. ,--.,------. \n"
           "|  .-.  \\ |  .--. '|  .---' /  O  \\ |   `.'   |    |  |) /_  /  O  \\ |  .'   /|  .---' \n"
           "|  |  \\  :|  '--'.'|  `--, |  .-.  ||  |'.'|  |    |  .-.  \\|  .-.  ||  .   ' |  `--,  \n"
           "|  '--'  /|  |\\  \\ |  `---.|  | |  ||  |   |  |    |  '--' /|  | |  ||  |\\   \\|  `---. \n"
           "`-------' `--' '--'`------'`--' `--'`--'   `--'    `------' `--' `--'`--' '--'`------'");
    printf("\n\n_______________________________________________________________________________________\n\n   ");
    sleep(3);


    // Declare Variables
    int size = 0;
    bool running = true;
    srand(time(NULL));

    // Initialize Orders
    Order frappucino = {"Frappucino", 69.99, 100 + rand() % 100, false};
    Order chocolates = {"Chocolates", 80, 100 + rand() % 100, false};
    Order cookies = {"Cookies", 50, 100 + rand() % 100, false};
    Order muffin = {"Muffin", 99, 100 + rand() % 100, false};
    Order cake = {"Cake", 159, 100 + rand() % 100, true, {"Chocolate", "Vanilla", "Mocha", "Red Velvet"}};
    Order orders[] = {frappucino, chocolates, cookies, muffin, cake};

    OrderedOrder orderedOrder[100];

    while (running)
    {

        int order = 0;
        int quantity = 0;
        int size_of_orders = sizeof(orders) / sizeof(orders[0]);
        int flavor_index = 0;
        String name_of_flavor = {""};
        print_orders(size_of_orders, orders);
            printf("\nWhat's your order? (Type '0' to pay!)\n");
        scanf("%d", &order);
        if (order == 0)
        {
            running = false;
            break;
        }
        else if (order <= 0 || order > size_of_orders)
        {
            sleep(1);
            printf("\nThis is not a valid order number! (Only 1-%d)\n", size_of_orders);
            sleep(1);
            continue;
        }
        else if (orders[order - 1].amount_of_products == 0)
        {
            sleep(1);
            printf("\nSorry, we don't have anymore!\n");
            sleep(1);
            continue;
        }
        else if (orders[order - 1].has_flavors)
        {
            while (true)
            {
                print_flavors(orders[order - 1].flavors);
                printf("\n\nWhat's the flavor?\n");
                scanf("%d", &flavor_index);
                if (flavor_index <= 0 || flavor_index > 4)
                {
                    sleep(1);
                    printf("\nThis is not a valid flavor number! (Only 1-4)\n ");
                    sleep(1);
                }
                else
                {
                    break;
                }
            }
            strcpy(name_of_flavor.value, orders[order - 1].flavors[flavor_index - 1]);
        }
        printf("How much?\n");
        scanf("%d", &quantity);

        while (true)
        {
            if (quantity <= orders[order - 1].amount_of_products)
            {
                break;
            }
            else
            {
                printf("\nThis is not a valid quantity! (Available stock: %d)\n", orders[order - 1].amount_of_products);
                printf("\nAmount of orders: ");
                scanf("%d", &quantity);
            }
        }
        subtract_product(&orders[order - 1], quantity);
        if (add_orders(order, orders, orderedOrder, &size, quantity, name_of_flavor) == false)
        {
            printf("Bye!");
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
        printf("\n%d: %-14s\t |  %.2f php\t (%d)\n", i + 1, orders[i].name_of_order,
               orders[i].price, orders[i].amount_of_products);
    }
}

void print_flavors(char *flavors[])
{
    printf("\n   Flavors: ");
    for (int i = 0; i < 4; i++)
    {
        printf("\n%d: %s", i + 1, flavors[i]);
    }
}

bool add_orders(int order, Order orders[], OrderedOrder order_to_be_added[], int *size, int quantity, String flavor)
{
    if (order <= 0)
    {
        return false;
    }
    order = order - 1;
    add_order(size, order_to_be_added, orders[order], quantity, flavor);
    return true;
}

void add_order(int *last_index, OrderedOrder orders_to_be_added[], Order order, int quantity, String flavor)
{
    if (order.has_flavors)
    {
        char order_name[100];
        strcpy(order_name, order.name_of_order);
        strcpy(order.name_of_order, flavor.value);
        strcat(order.name_of_order, " ");
        strcat(order.name_of_order, order_name);
    }
    OrderedOrder ordered_order = {order, quantity, get_price(order.price, quantity)};
    orders_to_be_added[*last_index] = ordered_order;
    sleep(1);
    printf("\nAdded!\n");
    sleep(1);
    *last_index += 1;
}
void subtract_product(Order *order, int quantity)
{
    order->amount_of_products -= quantity;
}