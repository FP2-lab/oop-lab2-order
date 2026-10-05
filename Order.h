#ifndef ORDER_H
#define ORDER_H

// Статус выполнения заказа
enum class OrderStatus {
    NEW,
    CONFIRMED,
    CANCELLED
};

class Order {
private:
    int orderId;            // номер заказа
    double totalCost;       // стоимость заказа
    int itemCount;          // количество товаров
    OrderStatus status;     // статус выполнения

    static int objectCount; // количество существующих объектов Order

    // Вспомогательный метод для вывода статуса текстом
    static const char* statusToString(OrderStatus s);

public:
    // Конструкторы и деструктор
    Order();                                    // без аргументов
    Order(int id);                              // с номером заказа
    Order(int id, double cost, int count);      // с начальным составом
    Order(const Order& other);                  // копирующий
    ~Order();

    // Методы чтения
    int getOrderId() const;
    double getTotalCost() const;
    int getItemCount() const;
    OrderStatus getStatus() const;
    static int getObjectCount();

    // Методы изменения состояния
    bool addItem(double price);
    bool removeItem(double price);
    bool confirm();
    bool cancel();

    // Вывод информации
    void print() const;
};

#endif // ORDER_H