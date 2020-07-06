#include <iostream>
#include <vector>
#include <algorithm>

struct Item             //Создаю класс "Предмет"
{
    std::string name;   // ввожу имя предмета
    double weight;      // ввожу вес предмета
    double cost;        // ввожу стоимость предмета
    double value;       // ввожу ценность предмета

    Item(std::string n, double w, double c): name(n), weight(w), cost(c), value(w / c) {} // Создаю конструктор для класса Предмета 
};                                                                                        

int main()
{
    system("chcp 1251");
    std::vector<Item> items;  // Задаю список из предметов
    items.emplace_back("Калькулятор", 5, 10);
    items.emplace_back("Фотокамера", 4, 10);
    items.emplace_back("Телефон", 9, 10);
    items.emplace_back("Ноутбук", 10, 10);
    items.emplace_back("Ручка", 1, 10);

    std::sort(begin(items), end(items), [](Item& item1, Item& item2){return item1.value > item2.value;}); // Начинаю сортировку предметов по ценности
                                                                                                          // использую лямбда функцию              
    double backpack_weight = 20; // задаю вместимость рюкзака 
    std::vector<Item> backpack; // Список предметов в рюкзаке

    for (auto& item: items) // создаю цикл для перебора отсортированного списка предметов
    {
        if (backpack_weight - item.weight >= 0) { // если предмет помещается в рюкзак
            backpack.push_back(item);             // помещаем его в рюкзак
            backpack_weight -= item.weight;       // Уменьшаем запас вместимости рюкзака
        }
    }

    for (auto &item : backpack)    // вывод итогового списка предметов в рюкзаке
        std::cout << item.name << " ";
    std::cout << "\n";
}