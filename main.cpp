#include <iostream>
#include "Order.h"

// Вспомогательная функция: печатает результат операции
void showResult(const char* operation, bool ok) {
    std::cout << "  " << operation << " -> "
              << (ok ? "OK" : "REJECTED") << std::endl;
}

int main() {
    std::cout << "=== STEP 1: Creating objects ===" << std::endl;
    Order o1;                       // конструктор без аргументов
    Order o2(101);                  // конструктор с номером
    Order o3(102, 300.0, 2);        // конструктор с начальным составом
    Order o4(o3);                   // копирующий конструктор
    std::cout << "Objects alive: " << Order::getObjectCount() << std::endl;

    std::cout << "\n=== STEP 2: Initial state ===" << std::endl;
    o1.print();
    o2.print();
    o3.print();
    o4.print();

    std::cout << "\n=== STEP 3: Valid operations ===" << std::endl;
    showResult("o1.addItem(100.0)", o1.addItem(100.0));
    showResult("o2.addItem(50.0)", o2.addItem(50.0));
    showResult("o2.addItem(70.5)", o2.addItem(70.5));
    showResult("o2.removeItem(50.0)", o2.removeItem(50.0));
    showResult("o3.confirm()", o3.confirm());
    showResult("o1.cancel()", o1.cancel());

    std::cout << "\n=== STEP 4: Invalid operations ===" << std::endl;
    showResult("o3.addItem(10.0) [confirmed order]", o3.addItem(10.0));
    showResult("o3.removeItem(10.0) [confirmed order]", o3.removeItem(10.0));
    showResult("o3.cancel() [confirmed order]", o3.cancel());
    showResult("o3.confirm() [already confirmed]", o3.confirm());
    showResult("o1.confirm() [cancelled order]", o1.confirm());
    showResult("o1.addItem(5.0) [cancelled order]", o1.addItem(5.0));
    showResult("o2.addItem(-5.0) [negative price]", o2.addItem(-5.0));
    showResult("o2.removeItem(1000.0) [price > total]", o2.removeItem(1000.0));

    std::cout << "\n  Creating an empty order in a nested scope:" << std::endl;
    {
        Order empty(999);
        std::cout << "  Objects alive: " << Order::getObjectCount() << std::endl;
        showResult("empty.confirm() [no items]", empty.confirm());
        showResult("empty.removeItem(10.0) [no items]", empty.removeItem(10.0));
    }   // здесь empty уничтожается
    std::cout << "  Objects alive after scope: "
              << Order::getObjectCount() << std::endl;

    std::cout << "\n=== STEP 5: State after invalid operations ===" << std::endl;
    o1.print();
    o2.print();
    o3.print();

    std::cout << "\n=== STEP 6: Independence of objects ===" << std::endl;
    std::cout << "o4 is a copy of o3 made before o3 was confirmed." << std::endl;
    std::cout << "Before changing o4:" << std::endl;
    o3.print();
    o4.print();
    showResult("o4.addItem(40.0)", o4.addItem(40.0));
    std::cout << "After changing only o4:" << std::endl;
    o1.print();
    o2.print();
    o3.print();
    o4.print();

    std::cout << "\n=== END: Objects alive: "
              << Order::getObjectCount() << " ===" << std::endl;
    std::cout << "Destructors will be called now:" << std::endl;
    return 0;
}