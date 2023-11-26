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
    bool is_beverage;
    bool has_flavors;
    int amount_of_flavors;
    char *flavors[10];
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
void print_flavors(char *flavors[], int amount_of_flavors);
Order make_new_order(char *name_of_order, float price);
bool check_pay(int *order);

int main()
{

    // Title
    printf("\n____________________________________________________________________________________________________");
    printf("                                                                                                   \n"
           " ,---.  ,--.   ,--.,------.,------.,--------.,-----.  ,------. ,------.  ,---.  ,------.   ,---.   \n"
           "'   .-' |  |   |  ||  .---'|  .---''--.  .--'|  |) /_ |  .--. '|  .---' /  O  \\ |  .-.  \\ '   .-'  \n"
           "`.  `-. |  |.'.|  ||  `--, |  `--,    |  |   |  .-.  \\|  '--'.'|  `--, |  .-.  ||  |  \\  :`.  `-.  \n"
           ".-'    ||   ,'.   ||  `---.|  `---.   |  |   |  '--' /|  |\\  \\ |  `---.|  | |  ||  '--'  /.-'    | \n"
           "`-----' '--'   '--'`------'`------'   `--'   `------' `--' '--'`------'`--' `--'`-------' `-----'");
    printf("\n____________________________________________________________________________________________________\n   ");
    sleep(2);

    // Declare Variables
    int size = 0;
    bool running = true;
    srand(time(NULL));

    // Initialize Orders
    Order chocolates = {"Chocolates", 99, 100 + rand() % 100, false, false};
    Order muffin = {"Muffin", 99, 100 + rand() % 100, false, false};
    Order cake = {"Cake", 159, 100 + rand() % 100, false, true, 3, {"Vanilla", "Mocha", "Red Velvet"}};
    Order croissant = {"Croissant ", 50, 100 + rand() % 100, false, true, 2, {"Strawberry", "Chocolate"}};
    Order cookies = {"Cookies", 45, 100 + rand() % 100, false, true, 3, {"Matcha", "Chocolate Chips", "Cookies and Cream"}};
    Order waffle = {"Waffle", 60, 100 + rand() % 100, false, false};
    Order donut = {"Mini Doughnuts", 125,100 + rand() % 100, false, false};
    Order brownies = {"Brownies", 120 , 100 + rand() % 100, false, false};
    Order churos = {"Churos", 40 , 100 + rand() % 100, false, false};

    // Initialize Drinks
    Order iced_caramel = {"Iced Caramel", 70, 100 + rand() % 100, true, false};
    Order salted_caramel = {"Salted Caramel", 70, 100 + rand() % 100, true, false};
    Order caramel_mocha = {"Caramel Mocha", 70, 100 + rand() % 100, true, false};
    Order hot_americano = {"Hot Americano", 70, 100 + rand() % 100, true, false};
    Order hot_tea = {"Hot Tea", 70, 100 + rand() % 100, true, false};

    // Initialize list of possible order
    Order orders[] = {chocolates, cookies, muffin, cake, cookies, croissant, waffle, donut, brownies, churos,
                      iced_caramel, salted_caramel, caramel_mocha, hot_americano, hot_tea};

    OrderedOrder orderedOrder[100];

    while (running)
    {

        int order = 0;
        int quantity = 0;
        int size_of_orders = sizeof(orders) / sizeof(orders[0]);
        int flavor_index = 0;
        String name_of_flavor = {""};
        print_orders(size_of_orders, orders);
        printf("\n\nWhat's your order? (Type '/pay' to pay!) ");
        if (check_pay(&order))
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
                print_flavors(orders[order - 1].flavors, orders[order - 1].amount_of_flavors);
                printf("\n\nWhat's the flavor? ");
                scanf("%d", &flavor_index);
                if (flavor_index <= 0 || flavor_index > orders[order - 1].amount_of_flavors)
                {
                    sleep(1);
                    printf("\nThis is not a valid flavor number! (Only 1-%d)\n ", orders[order - 1].amount_of_flavors);
                    sleep(1);
                }
                else
                {
                    break;
                }
            }
            strcpy(name_of_flavor.value, orders[order - 1].flavors[flavor_index - 1]);
        }
        printf("How much? ");
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

void get_date_time(char *dateTime) {
    time_t t = time(NULL);
    struct tm *localTime = localtime(&t);
    strftime(dateTime, 50, "\n%I:%M %p\t\t\t\t\t\t%B %d, %Y", localTime);
}

void print_reciept(int size, OrderedOrder orderedOrder[])
{
    char current_date_time[50];
    get_date_time(current_date_time);
    printf("%s\n", current_date_time);

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
    bool printed_drinks = false;
    printf("\n\t\tDesserts and Pastries:\n");
    printf("\n   Name: \t\t    Price: \t Quantity:\n");
    for (int i = 0; i < size; i++)
    {
        if (orders[i].is_beverage && !printed_drinks)
        {
            printf("\n\n\t\t   Drinks:\n");
            printf("\n    Name: \t\t    Price: \t Quantity:\n");
            printed_drinks = true;
        }
        printf("\n%d: %-14s\t|   %.2f php\t (%d)\n", i + 1, orders[i].name_of_order,
               orders[i].price, orders[i].amount_of_products);
    }
}

void print_flavors(char *flavors[], int amount_of_flavors)
{
    printf("\n   Flavors: ");
    for (int i = 0; i < amount_of_flavors; i++)
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
    printf("\nOrder Added!\n");
    sleep(1);
    *last_index += 1;
}
void subtract_product(Order *order, int quantity)
{
    order->amount_of_products -= quantity;
}

bool check_pay(int *order)
{
    float number = 0;
    char buffer[10] = {};
    scanf("\n%[^\n]", &buffer);
    if (strcmp(buffer, "/pay") == 0)
    {
        return true;
    }
    else if (sscanf(buffer, "%f", &number) != 1)
    {
        *order = 0;
        return false;
    }
    else
    {
        *order = (int)number;
        return false;
    }

}