#include <iostream>
#include <vector>
#include <algorithm>

struct Item             //������ ����� "�������"
{
    std::string name;   // ����� ��� ��������
    double weight;      // ����� ��� ��������
    double cost;        // ����� ��������� ��������
    double value;       // ����� �������� ��������

    Item(std::string n, double w, double c): name(n), weight(w), cost(c), value(w / c) {} // ������ ����������� ��� ������ �������� 
};                                                                                        

int main()
{
    system("chcp 1251");
    std::vector<Item> items;  // ����� ������ �� ���������
    items.emplace_back("�����������", 5, 10);
    items.emplace_back("����������", 4, 10);
    items.emplace_back("�������", 9, 10);
    items.emplace_back("�������", 10, 10);
    items.emplace_back("�����", 1, 10);

    std::sort(begin(items), end(items), [](Item& item1, Item& item2){return item1.value > item2.value;}); // ������� ���������� ��������� �� ��������
                                                                                                          // ��������� ������ �������              
    double backpack_weight = 20; // ����� ����������� ������� 
    std::vector<Item> backpack; // ������ ��������� � �������

    for (auto& item: items) // ������ ���� ��� �������� ���������������� ������ ���������
    {
        if (backpack_weight - item.weight >= 0) { // ���� ������� ���������� � ������
            backpack.push_back(item);             // �������� ��� � ������
            backpack_weight -= item.weight;       // ��������� ����� ����������� �������
        }
    }

    for (auto &item : backpack)    // ����� ��������� ������ ��������� � �������
        std::cout << item.name << " ";
    std::cout << "\n";
}