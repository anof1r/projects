//=====================================
/*
 Создать АРМ диспетчера междугородней телефонной станции
 (МТС). Диспетчер МТС работает с ЭВМ в режиме меню.
 Поступающие заказы хранятся в памяти ЭВМ, то есть ведется
 электронный журнал.
 Реализовать функции:
 - прием заказа; *работает*
 - исполнение очередного заказа; *работает*
 - определение номера заказа в общей очереди заказов; *работает*
 - определение номера заказа для заданного города; *работает*
 - включение срочного заказа в очередь под номером N; *работает*
 - формирование списка заказов в заданный город; *работает*
 */
//=====================================

#include <iostream>

using namespace std;

class List{
public:
    
    List();
    ~List();
    void push_back(int time,string city,string myphone,string name,string number);
    void push_front(int time,string city,string myphone,string name,string number);
    void insert(int num,int time,string city,string myphone,string name,string number);
    int find_number(string myphone);
    int find_number_city(string city);
    void orders_to_city(string city);
    int get_size(){return Size;};
    void pop_front();
    void clear();
    void sort();
private:
    
    class Node{
    public:
        Node *pNext;
        string city;
        string myphone;
        string name;
        string number;
        int time;
        
        Node (int time,string city,string myphone,string name,string number,Node *pNext = nullptr){
            this->time = time;
            this->city = city;
            this->myphone = myphone;
            this->name = name;
            this->number = number;
            this->pNext = pNext;
        }
    };
    int Size;
    Node *head;
};

List::List(){
    Size = 0;
    head = nullptr;
}

List::~List(){
    
}

void List::clear(){
    while (Size){
        pop_front();
    }
}

void List::sort(){
    Node *current = head;
    Node *prev;
    Node *prevprev;
    int counter = 0;
    if (Size == 0){
        counter = 1;
    }
    while (Size>counter+1){
            counter++;
            if (counter > 1){
                prevprev=prev;
            }
            prev = current;
            current = current->pNext;
            if ((prev->time>current->time)&&(counter==1)){
                Node *temp = head;
                head=current;
                temp->pNext = head->pNext;
                head->pNext = temp;
                current = head;
                counter = 0;
            }
            if ((prev->time>current->time)&&(counter>1)){
                Node *temp = current->pNext;
                current->pNext=prev;
                prevprev->pNext=current;
                prev->pNext = temp;
                current = head;
                counter = 0;
            }
            
        }
}

void List::push_back(int time,string city,string myphone,string name,string number){
    if (head == nullptr){
        head = new Node(time,city,myphone,name,number);
    }
    else{
        Node *current = this->head;
        while (current ->pNext!=nullptr){
            current = current->pNext;
        }
        current->pNext = new Node(time,city,myphone,name,number);
    }
    Size++;
}

int List::find_number(string myphone){
    int num=0;
    Node *current = head;
    if (current->myphone != myphone){
        num++;
    }
    if (num != 0){
        while(current->pNext!= nullptr){
            current = current->pNext;
            if (current->myphone != myphone){
                num++;
            }
            else {
                return num;
            }
        }
    }
    return -1;
}

int List::find_number_city(string city){
    int num=0;
    Node *current = head;
    if (current->city != city){
        num++;
        return 0;
    }
    if (num != 0){
        while(current->pNext!= nullptr){
            current = current->pNext;
            if (current->city != city){
                num++;
            }
            else {
                return num;
            }
        }
    }
    return -1;
}

void List::insert(int num,int time,string city,string myphone,string name,string number){
   int num_current = 0;
    Node *current =  head;
    if (num_current == num){
        push_front(time,city,myphone,name,number);
        return;
    }
    Node* previous;
    while (current->pNext!=0){
        previous=current;
        current = current->pNext;
        num++;
        if (num_current == num){
            previous->pNext = new Node (time,city,myphone,name,number,current);
            return;
           }
    }
    cout<<"Данный номер не найден, заказ поставлен в конец списка!";
    push_back(time,city,myphone,name,number);
    
}

void List::orders_to_city(string city){
    Node *current = head;
    if (current->city == city){
        cout<<"Заказ с номера: "<<current->myphone<<endl;
        cout<<"На номер: "<<current->number<<endl;
        cout<<"ФИО: "<<current->name<<endl;
        cout<<"Город звонка: "<<current->city<<endl;
        cout<<"Оплаченное время: "<<current->time<<endl<<endl;
    }
    while(current->pNext!= nullptr){
        current = current->pNext;
        if (current->city == city){
            cout<<"Заказ с номера: "<<current->myphone<<endl;
            cout<<"На номер: "<<current->number<<endl;
            cout<<"ФИО: "<<current->name<<endl;
            cout<<"Город звонка: "<<current->city<<endl;
            cout<<"Оплаченное время: "<<current->time<<endl<<endl;
        }
        
    }
}

void List::pop_front(){
    Node *temp = head;
    head = head->pNext;
    delete temp;
    Size--;
}

void List::push_front(int time,string city,string myphone,string name,string number){
    head = new Node(time,city,myphone,name,number,head);
    Size++;
}

int main(){
    setlocale(LC_ALL,"Rus");
    List lst;
    while (true){
        string command;
        cout<<"В системе сейчас "<<lst.get_size()
            <<" заказов.\n";
        cout<<"Для добавления нового заказа введите new\n";
        cout<<"Для добавления срочного заказа введите fast \n";
        cout<<"Для исполнения текущего заказа (удаления из очереди) введите - now \n";
        cout<<"Для определения номера заказа по телефону звонящего - find \n";
        cout<<"Для определения номера заказа по городу - fcity \n";
        cout<<"Для вывода звонков в город - city \n";
        cout<<"Для сортировки по времени - sortirovka \n";
        cout<<"Для завершения работы введите exit \n";
        cin>>command;
        if(command=="new"){
            string name,myphone,phone,city;
            int time;
            cout<<"Введите ФИО заказчика: ";
            getline(cin,name);
            getline(cin,name);
            cout<<"Введите телефон заказчика: ";
            getline(cin,myphone);
            cout<<"Введите заказанный телефон: ";
            getline(cin,phone);
            cout<<"Введите город звонка: ";
            getline(cin,city);
            cout<<"Введите оплаченное время звонка (мин): ";
            cin>>time;
            lst.push_back(time,city,myphone,name,phone);
            cout<<"Заказ доабвлен в очередь!\n";
        }
        if(command=="fast"){
           string name,myphone,phone,city;
            int time,num;
            cout<<"Введите ФИО заказчика: ";
            getline(cin,name);
            getline(cin,name);
            cout<<"Введите телефон заказчика: ";
            getline(cin,myphone);
            cout<<"Введите заказанный телефон: ";
            getline(cin,phone);
            cout<<"Введите город звонка: ";
            getline(cin,city);
            cout<<"Введите оплаченное время звонка (мин): ";
            cin>>time;
            cout<<"Введите желаемый номер звонка в очереди (от 0): ";
            cin>>num;
            lst.insert(num,time,city,myphone,name,phone);
            cout<<"Заказ доабвлен в очередь!\n";
        }
        if(command=="now"){
            lst.pop_front();
            cout<<"Текущий заказ успешно обработан!\n";
        }
        if(command=="sortirovka"){
            lst.sort();
            cout<<"Список отсортирован!\n";
        }
        if(command=="find"){
            cout<<"Введите телефон заказчика: ";
            string myphone;
            getline(cin,myphone);
            getline(cin,myphone);
            cout<<"Номер данного заказа!" << lst.find_number(myphone)<<endl;
        }
        if(command=="fcity"){
            cout<<"Введите город звонка: ";
            string myphone;
            getline(cin,myphone);
            getline(cin,myphone);
            cout<<"Номер первого заказа в данный город!" << lst.find_number_city(myphone)<<endl;
        }
        if(command=="city"){
            cout<<"Введите город звонка: ";
            string myphone;
            getline(cin,myphone);
            getline(cin,myphone);
            lst.orders_to_city(myphone);
        }
        if(command=="exit"){
            lst.clear();
            return 0;
        }
    }
}
/*
 В системе сейчас 0 заказов.
 Для добавления нового заказа введите new
 Для добавления срочного заказа введите fast
 Для исполнения текущего заказа (удаления из очереди) введите - now
 Для определения номера заказа по телефону звонящего - find
 Для определения номера заказа по городу - fcity
 Для вывода звонков в город - city
 Для сортировки по времени - sortirovka
 Для завершения работы введите exit
 new
 Введите ФИО заказчика: Волкова
 Введите телефон заказчика: 8999999
 Введите заказанный телефон: 492034290
 Введите город звонка: Москва
 Введите оплаченное время звонка (мин): 13
 Заказ доабвлен в очередь!
 В системе сейчас 1 заказов.
 Для добавления нового заказа введите new
 Для добавления срочного заказа введите fast
 Для исполнения текущего заказа (удаления из очереди) введите - now
 Для определения номера заказа по телефону звонящего - find
 Для определения номера заказа по городу - fcity
 Для вывода звонков в город - city
 Для сортировки по времени - sortirovka
 Для завершения работы введите exit
 new
 Введите ФИО заказчика: Будцын
 Введите телефон заказчика: 788888888
 Введите заказанный телефон: 4029034290
 Введите город звонка: Москва
 Введите оплаченное время звонка (мин): 133
 Заказ доабвлен в очередь!
 В системе сейчас 2 заказов.
 Для добавления нового заказа введите new
 Для добавления срочного заказа введите fast
 Для исполнения текущего заказа (удаления из очереди) введите - now
 Для определения номера заказа по телефону звонящего - find
 Для определения номера заказа по городу - fcity
 Для вывода звонков в город - city
 Для сортировки по времени - sortirovka
 Для завершения работы введите exit
 new
 Введите ФИО заказчика: Громнидский
 Введите телефон заказчика: 724852498
 Введите заказанный телефон: 230428340
 Введите город звонка: неМосква
 Введите оплаченное время звонка (мин): 3
 Заказ доабвлен в очередь!
 В системе сейчас 3 заказов.
 Для добавления нового заказа введите new
 Для добавления срочного заказа введите fast
 Для исполнения текущего заказа (удаления из очереди) введите - now
 Для определения номера заказа по телефону звонящего - find
 Для определения номера заказа по городу - fcity
 Для вывода звонков в город - city
 Для сортировки по времени - sortirovka
 Для завершения работы введите exit
 fast
 Введите ФИО заказчика: Таланова Вероника
 Введите телефон заказчика: 888888888
 Введите заказанный телефон: 048923904280
 Введите город звонка: Москва
 Введите оплаченное время звонка (мин): 999999999
 Введите желаемый номер звонка в очереди (от 0): 0
 Заказ доабвлен в очередь!
 В системе сейчас 4 заказов.
 Для добавления нового заказа введите new
 Для добавления срочного заказа введите fast
 Для исполнения текущего заказа (удаления из очереди) введите - now
 Для определения номера заказа по телефону звонящего - find
 Для определения номера заказа по городу - fcity
 Для вывода звонков в город - city
 Для сортировки по времени - sortirovka
 Для завершения работы введите exit
 find
 Введите телефон заказчика: 8999999
 Номер данного заказа!1
 В системе сейчас 4 заказов.
 Для добавления нового заказа введите new
 Для добавления срочного заказа введите fast
 Для исполнения текущего заказа (удаления из очереди) введите - now
 Для определения номера заказа по телефону звонящего - find
 Для определения номера заказа по городу - fcity
 Для вывода звонков в город - city
 Для сортировки по времени - sortirovka
 Для завершения работы введите exit
 fcity
 Введите город звонка: Москва
 Номер первого заказа в данный город!0
 В системе сейчас 4 заказов.
 Для добавления нового заказа введите new
 Для добавления срочного заказа введите fast
 Для исполнения текущего заказа (удаления из очереди) введите - now
 Для определения номера заказа по телефону звонящего - find
 Для определения номера заказа по городу - fcity
 Для вывода звонков в город - city
 Для сортировки по времени - sortirovka
 Для завершения работы введите exit
 city
 Введите город звонка: Москва
 Заказ с номера: 888888888
 На номер: 048923904280
 ФИО: Таланова Вероника
 Город звонка: Москва
 Оплаченное время: 999999999

 Заказ с номера: 8999999
 На номер: 492034290
 ФИО:  Волкова
 Город звонка: Москва
 Оплаченное время: 13

 Заказ с номера: 788888888
 На номер: 4029034290
 ФИО: Будцын
 Город звонка: Москва
 Оплаченное время: 133

 В системе сейчас 4 заказов.
 Для добавления нового заказа введите new
 Для добавления срочного заказа введите fast
 Для исполнения текущего заказа (удаления из очереди) введите - now
 Для определения номера заказа по телефону звонящего - find
 Для определения номера заказа по городу - fcity
 Для вывода звонков в город - city
 Для сортировки по времени - sortirovka
 Для завершения работы введите exit
 sortirovka
 Список отсортирован!
 */
