#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
using namespace std;

struct a_point {
    float x;
    float y;
};

struct b_point {
    float x;
    float y;
};



// Класс Точка
class Point {
public:
    // Конструктор по умолчанию, создающий точку 0,0
    Point() {
        x = 0;
        y = 0;
    }

    // Конструктор
    Point (float set_x, float set_y) : x(set_x) , y(set_y) {}

    // Конструктор копирования
    Point (const Point &PointCopy) : x(PointCopy.x), y(PointCopy.y) {}

    float x, y;

    // Деструктор
    ~Point () = default;
};

// Класс Ломаная линия
class BrokenLine {
private:
    vector<Point> points;
public:
    // Конструктор для ломаной
    explicit BrokenLine (vector<Point> v) : points(std::move(v)) {}

    // Конструктор копирования
    BrokenLine (const BrokenLine &Bl) : points(Bl.points) {}

    // Деструктор
    ~BrokenLine () = default;
};

// Класс Замкнутая линия
class ClosedLine {
private:
    vector<Point> points;
public:
    // Конструктор
    explicit ClosedLine (vector<Point> v) : points(std::move(v)) {}

    // Проверка на Замкнутость
    virtual void CheckClosedLine () {
        int n = points.size();
        // Проверяем по координатам первой и последней точки
        if (points[0].x != points[n-1].x || points[0].y != points[n-1].y) {
            throw "This ClosedLine, doesn't close. Input points again, please!";
        }
    }

    // Конструктор копирования
    ClosedLine (const ClosedLine &Cl) : points(Cl.points) {}

    // Деструктор
    ~ClosedLine () = default;
};

// Класс Многоугольник
class Polygon {
public:
    vector<Point> points;
    // Конструктор
    explicit Polygon (vector<Point> v) : points(std::move(v)) {}

    // Конструктор копирования
    Polygon (const Polygon &Poly) : points(Poly.points) {}

    // Проверка на Замкнутость
    void CheckClosedLine () {
        int n = points.size();
        // Проверяем по координатам первой и последней точки
        if (points[0].x != points[n-1].x || points[0].y != points[n-1].y) {
            throw "This ClosedLine, doesn't close. Input points again, please!";
        }
    }

    void measure () {
        // Длины всех сторон
        vector<int> edge;
        for (int i = 0; i <= points.size()-1; i++) {
            if (i == points.size()-1) {
                float dx = points[0].x - points[i].x;
                float dy = points[0].y - points[i].y;
                float d = sqrt(dx * dx + dy * dy);
                edge.push_back(d);
                // cout << "d" << "_" << i << ": " << d << endl;
                break;
            }
            float dx = points[i].x - points[i+1].x;
            float dy = points[i].y - points[i+1].y;
            float d = sqrt(dx * dx + dy * dy);
            edge.push_back(d);
            // cout << "d" << "_" << i << ": " << d << endl;
        }

        // Периметр
        float Perimeter = 0;
        for (float i : edge) {
            Perimeter += i;
        }
        cout << "Poly perimeter = " << Perimeter << endl;

        // Площадь
        float group_plus = 0;
        float group_minus = 0;
        float square;
        int n = points.size();
        for (int i = 0; i <= points.size()-1; i++) {
            if (i == points.size()-1) {
                group_plus  += points[i].x * points[n-1].y;
                group_minus -= points[i].y * points[n-1].x;
                break;
            }
            group_plus  += points[i].x * points[i+1].y;
            group_minus -= points[i].y * points[i+1].x;
        }
        square = abs(group_plus - group_minus)/2;
        cout << "Poly square: " << square << endl;
    }

    char CheckPolygon () {
        // (b−a)×(c−a)>0
        // a×b=xayb−yaxb
        
        vector<float> product;
        a_point a{};
        b_point b{};
        
        for (int i = 0; i+2 <= points.size()-1; i++) {
            a.x = points[i+1].x - points[i].x;
            a.y = points[i+1].y - points[i].y;

            b.x = points[i+2].x - points[i].x;
            b.y = points[i+2].y - points[i].y;

            float ABC = a.x * b.y - a.y * b.x;
            product.push_back(ABC);
        }

        float result_plus = 0;
        float result_minus = 0;
        for (float i : product) {
            if (i > 0) {
                result_plus += 1;
            } else if (i < 0) {
                result_minus += 1;
            }
        }
        if (result_plus == product.size() || result_minus == product.size()) {}
        else {
            throw "This Polygon, is incorrect. Input points again, please!";
        }
    }

    // Деструктор
    ~Polygon () = default;
};

// Класс Треугольник
class Triangle {
public:
    // Конструктор
    explicit Triangle (const Polygon& Poly) : Pl(Poly) {}

    // Конструктор копирования
    Triangle (const Triangle &Trio) : Pl(Trio.Pl) {}

    void measure () {
        // Длины всех сторон
        vector<int> edge;
        for (int i = 0; i <= Pl.points.size()-1; i++) {
            if (i == Pl.points.size()-1) {
                float dx = Pl.points[0].x - Pl.points[i].x;
                float dy = Pl.points[0].y - Pl.points[i].y;
                float d = sqrt(dx * dx + dy * dy);
                edge.push_back(d);
                // cout << "d" << "_" << i << ": " << d << endl;
                break;
            }
            float dx = Pl.points[i].x - Pl.points[i+1].x;
            float dy = Pl.points[i].y - Pl.points[i+1].y;
            float d = sqrt(dx * dx + dy * dy);
            edge.push_back(d);
            // cout << "d" << "_" << i << ": " << d << endl;
        }

        // Периметр
        float Perimeter = 0;
        for (float i : edge) {
            Perimeter += i;
            // cout << "Edge = " << edge[i] << " " << i << endl;
        }
        cout << "Triangle perimeter = " << Perimeter << endl;

        // Площадь
        float group_plus = 0;
        float group_minus = 0;
        float square;
        int n = Pl.points.size();
        for (int i = 0; i <= Pl.points.size()-1; i++) {
            if (i == Pl.points.size()-1) {
                group_plus  += Pl.points[i].x * Pl.points[n-1].y;
                group_minus -= Pl.points[i].y * Pl.points[n-1].x;
                break;
            }
            group_plus  += Pl.points[i].x * Pl.points[i+1].y;
            group_minus -= Pl.points[i].y * Pl.points[i+1].x;
        }
        square = abs(group_plus - group_minus)/2;
        cout << "Triangle square: " << square << endl;
    }

    char CheckPolygon () {
        // (b−a)×(c−a)>0
        // a×b=xayb−yaxb
        
        vector<float> product;
        a_point a{};
        b_point b{};
        
        for (int i = 0; i+2 <= Pl.points.size()-1; i++) {
            a.x = Pl.points[i+1].x - Pl.points[i].x;
            a.y = Pl.points[i+1].y - Pl.points[i].y;

            b.x = Pl.points[i+2].x - Pl.points[i].x;
            b.y = Pl.points[i+2].y - Pl.points[i].y;

            float ABC = a.x * b.y - a.y * b.x;
            product.push_back(ABC);
        }

        float result_plus = 0;
        float result_minus = 0;
        for (float i : product) {
            if (i > 0) {
                result_plus += 1;
            } else if (i < 0) {
                result_minus += 1;
            }
        }
        if (result_plus == product.size() || result_minus == product.size()) {}
        else {
            throw "This Triangle, is incorrect. Input points again, please!";
        }
    }
    Polygon Pl;

    // Деструктор
    ~Triangle () = default;
};

// Класс Трапеция
class Trapezoid {
public:
    // Конструктор
    explicit Trapezoid (const Polygon& Poly) : Pl(Poly) {}

    // Конструктор копирования
    Trapezoid (const Trapezoid &Trap) : Pl(Trap.Pl) {}

    void measure () {
        // Длины всех сторон
        vector<int> edge;
        for (int i = 0; i <= Pl.points.size()-1; i++) {
            if (i == Pl.points.size()-1) {
                float dx = Pl.points[0].x - Pl.points[i].x;
                float dy = Pl.points[0].y - Pl.points[i].y;
                float d = sqrt(dx * dx + dy * dy);
                edge.push_back(d);
                break;
            }
            float dx = Pl.points[i].x - Pl.points[i+1].x;
            float dy = Pl.points[i].y - Pl.points[i+1].y;
            float d = sqrt(dx * dx + dy * dy);
            edge.push_back(d);
        }

        // Периметр
        float Perimeter = 0;
        for (float i : edge) {
            Perimeter += i;
        }
        cout << "Trapezoid perimeter = " << Perimeter << endl;

        // Площадь
        float group_plus = 0;
        float group_minus = 0;
        float square;
        int n = Pl.points.size();
        for (int i = 0; i <= Pl.points.size()-1; i++) {
            if (i == Pl.points.size()-1) {
                group_plus  += Pl.points[i].x * Pl.points[n-1].y;
                group_minus -= Pl.points[i].y * Pl.points[n-1].x;
                break;
            }
            group_plus  += Pl.points[i].x * Pl.points[i+1].y;
            group_minus -= Pl.points[i].y * Pl.points[i+1].x;
        }
        square = abs(group_plus - group_minus)/2;
        cout << "Trapezoid square: " << square << endl;
    }

    char CheckTrapezoid () {
        // (b−a)×(c−a)>0
        // a×b=xayb−yaxb
        
        vector<float> product;
        a_point a{};
        b_point b{};
        
        for (int i = 0; i+2 <= Pl.points.size()-1; i++) {
            a.x = Pl.points[i+1].x - Pl.points[i].x;
            a.y = Pl.points[i+1].y - Pl.points[i].y;

            b.x = Pl.points[i+2].x - Pl.points[i].x;
            b.y = Pl.points[i+2].y - Pl.points[i].y;

            float ABC = a.x * b.y - a.y * b.x;
            product.push_back(ABC);
        }

        float result_plus = 0;
        float result_minus = 0;
        // for (int i = 0; i < product.size(); i++) {
        for (float i : product) {
            if (product[i] > 0) {
                result_plus += 1;
            } else if (product[i] < 0) {
                result_minus += 1;
            }
        }

        // a_point vector1 = 

        if (result_plus == product.size() || result_minus == product.size()) {}
        else {
            throw "This Trapezoid, is incorrect. Input points again, please!";
        }
    }
    Polygon Pl;

    // Деструктор
    ~Trapezoid () = default;
};

// Класс правильный многоугольник
class CorrectPolygon {
public:
    // Конструктор
    explicit CorrectPolygon (const Polygon& Poly) : Pl(Poly) {}

    // Конструктор копирования
    CorrectPolygon (const Trapezoid &Trap) : Pl(Trap.Pl) {}

    void measure () {
        // Длины всех сторон
        vector<int> edge;
        for (int i = 0; i <= Pl.points.size()-1; i++) {
            if (i == Pl.points.size()-1) {
                float dx = Pl.points[0].x - Pl.points[i].x;
                float dy = Pl.points[0].y - Pl.points[i].y;
                float d = sqrt(dx * dx + dy * dy);
                edge.push_back(d);
                break;
            }
            float dx = Pl.points[i].x - Pl.points[i+1].x;
            float dy = Pl.points[i].y - Pl.points[i+1].y;
            float d = sqrt(dx * dx + dy * dy);
            edge.push_back(d);
        }

        // Периметр
        float Perimeter = 0;
        for (float i : edge) {
            Perimeter += i;
        }
        cout << "CorrectPolygon perimeter = " << Perimeter << endl;

        // Площадь
        float group_plus = 0;
        float group_minus = 0;
        float square;
        int n = Pl.points.size();
        for (int i = 0; i <= Pl.points.size()-1; i++) {
            if (i == Pl.points.size()-1) {
                group_plus  += Pl.points[i].x * Pl.points[n-1].y;
                group_minus -= Pl.points[i].y * Pl.points[n-1].x;
                break;
            }
            group_plus  += Pl.points[i].x * Pl.points[i+1].y;
            group_minus -= Pl.points[i].y * Pl.points[i+1].x;
        }
        square = abs(group_plus - group_minus)/2;
        cout << "CorrectPolygon square: " << square << endl;
    }

    char CheckCorrectPolygon () {
        // (b−a)×(c−a)>0
        // a×b=xayb−yaxb

        vector<float> product;
        a_point a{};
        b_point b{};

        for (int i = 0; i+2 <= Pl.points.size()-1; i++) {
            a.x = Pl.points[i+1].x - Pl.points[i].x;
            a.y = Pl.points[i+1].y - Pl.points[i].y;

            b.x = Pl.points[i+2].x - Pl.points[i].x;
            b.y = Pl.points[i+2].y - Pl.points[i].y;

            float ABC = a.x * b.y - a.y * b.x;
            product.push_back(ABC);
        }

        float result_plus = 0;
        float result_minus = 0;
        // for (int i = 0; i < product.size(); i++) {
        for (float i : product) {
            if (product[i] > 0) {
                result_plus += 1;
            } else if (product[i] < 0) {
                result_minus += 1;
            }
        }
        if (result_plus == product.size() || result_minus == product.size()) {}
        else {
            throw "This Trapezoid, is incorrect. Input points again, please!";
        }
    }
    Polygon Pl;

    // Деструктор
    ~CorrectPolygon () = default;
};

// Допилить проверку трапеции и многоугольника

int main() {

    vector<Point> BlPoints;
    BlPoints.emplace_back();
    BlPoints.emplace_back(2, 4);
    BlPoints.emplace_back(6, 7);
    BlPoints.emplace_back(10, 3);

    BrokenLine Bl(BlPoints);

    vector<Point> ClPoints;
    ClPoints.emplace_back();
    ClPoints.emplace_back(2, 4);
    ClPoints.emplace_back(6, 7);
    ClPoints.emplace_back();

    ClosedLine Cl(ClPoints);

    // Проверка Замкнутой Ломаной линии на замкнутость
    try {  
        Cl.CheckClosedLine();
    }
    catch (const char *str) {
        cout << str << endl;
    }

    vector<Point> PolyPoints;
    PolyPoints.emplace_back();
    PolyPoints.emplace_back(0, 5);
    PolyPoints.emplace_back(10, 5);
    PolyPoints.emplace_back(10, 0);
    PolyPoints.emplace_back();

    Polygon Poly(PolyPoints);
    Poly.measure();

    try {  
        Poly.CheckClosedLine();
    }
    catch (const char *str) {
        cout << str << endl;
    }

    // Проверка Полигона на выпуклость
    try {  
        Poly.CheckPolygon();
    }
    catch (const char *str) {
        cout << str << endl;
    }

    vector<Point> TrioPoints;
    TrioPoints.emplace_back();
    TrioPoints.emplace_back(4, 3);
    TrioPoints.emplace_back(4, 0);
    TrioPoints.emplace_back();

    Polygon  TrioPoly(TrioPoints);
    Triangle Trio(TrioPoly);
    Trio.measure();

    vector<Point> TrapPoints;
    TrapPoints.emplace_back();
    TrapPoints.emplace_back(2, 4);
    TrapPoints.emplace_back(6, 4);
    TrapPoints.emplace_back(8, 0);
    TrapPoints.emplace_back();

    Polygon  TrapPoly(TrapPoints);
    Trapezoid Trap(TrapPoly);
    Trap.measure();

    vector<Point> CorrectPolyPoints;
    CorrectPolyPoints.emplace_back();
    CorrectPolyPoints.emplace_back(2, 4);
    CorrectPolyPoints.emplace_back(6, 4);
    CorrectPolyPoints.emplace_back(8, 0);
    CorrectPolyPoints.emplace_back();

    Polygon  Correct(CorrectPolyPoints);
    CorrectPolygon CorrectPoly(Correct);
    CorrectPoly.measure();

//    Справочные материалы
//    push_back добавляет копию объекта (или обеспечивает перемещение, если возможно),
//    а emplace_back создает объект непосредственно в конце вектора,
//    т.е. без лишнего копирования (или перемещения).

    return 0;
}