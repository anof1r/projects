#include <iostream>
#include <math.h>

auto min_distance(double x1, double y1, double x2, double y2, double x3, double y3) { 

    auto k = (y1 - y2) / (x1 - x2);//Находим коэффициенты уравнения прямой, которому принадлежит данный отрезок.
    auto b = y1 - k * x1;
    auto x_base = (x3 * x2 - x3 * x1 + y2 * y3 - y1 * y3 + y1 * b - y2 * b) / (k * y2 - k * y1 + x2 - x1); // основание прямой лежащей на отрезке
    double len = -1;
    if ((x_base <= x2 && x_base >= x1) || (x_base <= x1 && x_base >= x2)) // Если основание высоты лежит на отрезке
        len = sqrt((x3 - x_base) * (x3 - x_base) + (y3 - x_base * k - b) * (y3 - x_base * k - b));
    return len;
}

// Функция для подсчета длины отрезка по координатам его точек
auto length(double x1, double x2, double y1, double y2) { 
    auto result = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    return result;
}

int main() {
    using namespace std;
    setlocale(LC_ALL, "Russian");

    double xa, xb, ya, yb, xc, xd, yc, yd, len, len1, len2, len3, len4, 
           min = -1, delta, delta1, delta2, t = -2 , s = -2 ;
    cout << "Введите координаты точек ПЕРВОГО отрезка " << endl;
    cout << "X = "  ;
    cin >> xa;
    cout << "Y = ";
    cin >> ya;
    cout << "X1 = ";
    cin >> xb;
    cout << "Y1 = ";
    cin >> yb;
    cout << "Введите координаты точек ВТОРОГО отрезка " << endl;
    cout << "X = ";
    cin >> xc;
    cout << "Y = ";
    cin >> yc;
    cout << "X1 = ";
    cin >> xd;
    cout << "Y1 = ";
    cin >> yd; 
    
    //Используем метод крамера для решения систем уравнений
    delta = (xb - xa) * (-yd + yc) - (yb - ya) * (-xd + xc); 
    delta1 = (xb - xa) * (yc - ya) - (yb - ya) * (xc - xa);
    delta2 = -(-xd + xc) * (yc - ya) + (-yd + yc) * (xc - xa); 
    if (delta != 0) { 
        t = delta1 / delta;
        s = delta2 / delta;
    }
    if ((t >= 0 && s >= 0) && (t <= 1 && s <= 1)) { // Проверка пересечения отрезков , если пересекаются значит мин. расстояние 0
        min = 0; 
        cout << "Отрезки пересекаются" << endl;
    }
    else {
        //Из концов одного отрезка ищем минимальную высоту опущенную на другой отрезок.
        len1 = min_distance(xa, ya, xb, yb, xc, yc);
        min = len1;
        len2 = min_distance(xa, ya, xb, yb, xd, yd);
        if ((len2 < min && len2 != -1) || min == -1) min = len2;
        len3 = min_distance(xc, yc, xd, yd, xa, ya);
        if ((len3 < min && len3 != -1) || min == -1) min = len3;
        len4 = min_distance(xc, yc, xd, yd, xb, yb);
        if ((len4 < min && len4 != -1) || min == -1) min = len4;
        if (min == -1) { //В случае если не получается опустить высоту на отрезок будем искать минимальное расстояние между точками концов отрезков.
            len1 = length(xa,xc,ya,yc);
            min = len1;
            len2 = length(xb,xd,yb,yd);
            if (len2 < min) min = len2;
            len3 = length(xb,xc,yb,yc);
            if (len3 < min) min = len3;
            len4 = length(xa,xd,ya,yd);
            if (len4 < min) min = len4;
        }
	}
    cout << "Минимальное расстояние между отрезками = " << min << endl;
    system("pause");
}