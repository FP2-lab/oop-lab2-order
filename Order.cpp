#include "Order.h"
#include <iostream>

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