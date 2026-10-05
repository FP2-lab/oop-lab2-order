#include "Order.h"
#include <iostream>
#include <iomanip>

// Определение статического счётчика (в .cpp, один раз)
int Order::objectCount = 0;

// Основной конструктор со списком инициализации.
// Некорректные значения заменяются безопасными, чтобы объект
// всегда создавался в корректном состоянии.
Order::Order(int id, double cost, int count)
    : orderId(id >= 0 ? id : 0),
      totalCost(cost >= 0 ? cost : 0.0),
      itemCount(count >= 0 ? count : 0),
      status(OrderStatus::NEW)
{
    // Инвариант: в пустом заказе стоимость равна нулю
    if (itemCount == 0) {
        totalCost = 0.0;
    }
    ++objectCount;
}

// Конструктор без аргументов: пустой новый заказ с номером 0
Order::Order() : Order(0, 0.0, 0) {}

// Конструктор с номером заказа: пустой новый заказ
Order::Order(int id) : Order(id, 0.0, 0) {}

// Копирующий конструктор
Order::Order(const Order& other)
    : orderId(other.orderId),
      totalCost(other.totalCost),
      itemCount(other.itemCount),
      status(other.status)
{
    ++objectCount;
}

// Деструктор: показывает момент завершения времени жизни объекта
Order::~Order() {
    std::cout << "Order #" << orderId << " destroyed" << std::endl;
    --objectCount;
}

// Статический геттер счётчика
int Order::getObjectCount() {
    return objectCount;
}
// Преобразование статуса в текст для вывода
const char* Order::statusToString(OrderStatus s) {
    switch (s) {
        case OrderStatus::NEW:       return "NEW";
        case OrderStatus::CONFIRMED: return "CONFIRMED";
        case OrderStatus::CANCELLED: return "CANCELLED";
    }
    return "UNKNOWN";
}

// Методы чтения
int Order::getOrderId() const {
    return orderId;
}

double Order::getTotalCost() const {
    return totalCost;
}

int Order::getItemCount() const {
    return itemCount;
}

OrderStatus Order::getStatus() const {
    return status;
}

// Вывод информации об объекте
void Order::print() const {
    std::ios_base::fmtflags oldFlags = std::cout.flags();
    std::streamsize oldPrecision = std::cout.precision();

    std::cout << "Order #" << orderId
              << " | Items: " << itemCount
              << " | Total: " << std::fixed << std::setprecision(2) << totalCost
              << " | Status: " << statusToString(status)
              << std::endl;

    // Возвращаем настройки потока, чтобы не влиять на остальной вывод
    std::cout.flags(oldFlags);
    std::cout.precision(oldPrecision);
}
// Добавление товара в заказ. Возвращает true, если операция выполнена.
bool Order::addItem(double price) {
    if (status != OrderStatus::NEW) {
        std::cout << "Error: order #" << orderId
                  << " is " << statusToString(status)
                  << ", cannot add item" << std::endl;
        return false;
    }
    if (price <= 0) {
        std::cout << "Error: item price must be positive" << std::endl;
        return false;
    }
    ++itemCount;
    totalCost += price;
    return true;
}

// Удаление товара из заказа. Возвращает true, если операция выполнена.
bool Order::removeItem(double price) {
    if (status != OrderStatus::NEW) {
        std::cout << "Error: order #" << orderId
                  << " is " << statusToString(status)
                  << ", cannot remove item" << std::endl;
        return false;
    }
    if (itemCount == 0) {
        std::cout << "Error: order #" << orderId
                  << " has no items to remove" << std::endl;
        return false;
    }
    if (price <= 0 || price > totalCost) {
        std::cout << "Error: invalid price for removal" << std::endl;
        return false;
    }
    --itemCount;
    totalCost -= price;
    // Инвариант: в пустом заказе стоимость равна нулю
    if (itemCount == 0) {
        totalCost = 0.0;
    }
    return true;
}