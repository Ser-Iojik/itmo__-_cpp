#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <exception>
#include <stdexcept>
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
protected:
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
class ClosedLine : public BrokenLine {
public:
    // Конструктор
    explicit ClosedLine(vector<Point> points) : BrokenLine(std::move(points)) {}

    // Проверка на Замкнутость
    void CheckClosedLine () {
        int n = points.size();
        // Проверяем по координатам первой и последней точки
        if (points[0].x != points[n-1].x || points[0].y != points[n-1].y) {
            throw invalid_argument("This ClosedLine, doesn't close. Input points again, please!");
        }
    }

    // Конструктор копирования
    ClosedLine (const ClosedLine &Cl) : BrokenLine(Cl) {}

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
            throw invalid_argument("This Polygon, doesn't close. Input points again, please!");
        }
    }

    void perimeter () {
        // Длины всех сторон
        vector<int> edge;
        for (int i = 0; i <= points.size()-1; i++) {
            if (i == points.size()-1) {
                float dx = points[0].x - points[i].x;
                float dy = points[0].y - points[i].y;
                float d = sqrt(dx * dx + dy * dy);
                edge.push_back(d);
                break;
            }
            float dx = points[i].x - points[i+1].x;
            float dy = points[i].y - points[i+1].y;
            float d = sqrt(dx * dx + dy * dy);
            edge.push_back(d);
        }

        // Периметр
        float Perimeter = 0;
        for (float i : edge) {
            Perimeter += i;
        }
        cout << "Poly perimeter = " << Perimeter << endl;
    }
    // Площадь
    void square () {
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

    virtual bool CheckPolygon () {
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
        if (result_plus == product.size() || result_minus == product.size()) {
            return true;
        }
        else {
            throw invalid_argument("This Polygon, is incorrect. Input points again, please!");
            return false;
        }
    }

    // Деструктор
    ~Polygon () = default;
};

// Проверить на одну прямую
// Класс Треугольник
class Triangle : public Polygon {
public:
    // Конструктор
    explicit Triangle(vector<Point> v, const Polygon &Poly) : Polygon(std::move(v)), Pl(Poly) {}

    // Конструктор копирования
    Triangle(const Polygon &poly, const Triangle &Trio) : Polygon(poly), Pl(Trio.Pl) {}

    Polygon Pl;

    // Деструктор
    ~Triangle () = default;
};

// Класс Трапеция
class Trapezoid : public Polygon {
public:
    // Конструктор
    explicit Trapezoid(vector<Point> v, const Polygon &Poly) : Polygon(std::move(v)), Pl(Poly) {}

    // Конструктор копирования
    Trapezoid(const Polygon &poly, const Trapezoid &Trap) : Polygon(poly), Pl(Trap.Pl) {}

    bool CheckPolygon () override {
        if ( (((points[0].x-points[1].x)*(points[2].y-points[3].y) == 
        (points[0].y-points[1].y)*(points[2].x-points[3].x)) ||
        ((points[0].x-points[3].x)*(points[1].y-points[2].y) ==
        (points[0].y-points[3].y)*(points[1].x-points[2].x))) &&
        (points[0].x == points[4].x && points[0].y == points[4].y)) {
                cout << "It's a Trap!" << endl;
                return true;
        } else {
            throw invalid_argument("This Trapezoid, is incorrect. Input points again, please!");
            return false;
        }
    } 

    Polygon Pl;

    // Деструктор
    ~Trapezoid () = default;
};

// Класс правильный многоугольник
class CorrectPolygon : public Polygon {
public:
    // Конструктор
    explicit CorrectPolygon(vector<Point> v, const Polygon &Poly) : Polygon(std::move(v)), Pl(Poly) {}

    // Конструктор копирования
    CorrectPolygon(const Polygon &poly, const Trapezoid &Trap) : Polygon(poly), Pl(Trap.Pl) {}

    int n = points.size();
    bool CheckPolygon () override {
        const double EPS = 0.1; // погрешность
        bool check = true; 

        float dx = points[0].x - points[n-1].x;
        float dy = points[0].y - points[n-1].y;
        float d0 = sqrt(dx * dx + dy * dy);

        for (int i = 0; i < points.size()-1; i++) {
            float dx = points[i].x - points[i+1].x;
            float dy = points[i].y - points[i+1].y;
            float di = sqrt(dx * dx + dy * dy);

            if(fabs(di - d0) > EPS) {
            check = false;
            break;
            }
        }
        return check;
    }

    Polygon Pl;

    // Деструктор
    ~CorrectPolygon () = default;
};
// bool YouITMOstudent() {
//     return true;
// }

// int WorkForeverUntilYouDie() {
//     return false;
// }

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
    try {Cl.CheckClosedLine();}  catch (invalid_argument& e) {cerr << e.what() << endl; return -1;}

    vector<Point> PolyPoints;
    PolyPoints.emplace_back();
    PolyPoints.emplace_back(0, 5);
    PolyPoints.emplace_back(10, 5);
    PolyPoints.emplace_back(10, 0);
    PolyPoints.emplace_back();

    Polygon Poly(PolyPoints);
    Poly.perimeter();
    Poly.square();

    try {Poly.CheckClosedLine();}  catch (invalid_argument& e) {cerr << e.what() << endl; return -1;}
    try {Poly.CheckPolygon();}     catch (invalid_argument& e) {cerr << e.what() << endl; return -1;}

    vector<Point> TrioPoints;
    TrioPoints.emplace_back();
    TrioPoints.emplace_back(4, 3);
    TrioPoints.emplace_back(4, 0);
    TrioPoints.emplace_back();

    Polygon  TrioPoly(TrioPoints);
    Triangle Trio(TrioPoints ,TrioPoly);
    Trio.perimeter();
    Trio.square();

    try {Trio.CheckClosedLine();}  catch (invalid_argument& e) {cerr << e.what() << endl; return -1;}
    try {Trio.CheckPolygon();}     catch (invalid_argument& e) {cerr << e.what() << endl; return -1;}

// while (YouITMOstudent()) {
//     return WorkForeverUntilYouDie();
// }

    vector<Point> TrapPoints;
    TrapPoints.emplace_back();
    TrapPoints.emplace_back(2, 4);
    TrapPoints.emplace_back(6, 4);
    TrapPoints.emplace_back(8, 0);
    TrapPoints.emplace_back();

    Polygon   TrapPoly(TrapPoints);
    Trapezoid Trap(TrapPoints, TrapPoly);
    Trap.perimeter();
    Trap.square();
    try {Trap.CheckClosedLine();}  catch (invalid_argument& e) {cerr << e.what() << endl; return -1;}
    try {Trap.CheckPolygon();}     catch (invalid_argument& e) {cerr << e.what() << endl; return -1;}

    vector<Point> CorrectPolyPoints;
    CorrectPolyPoints.emplace_back();
    CorrectPolyPoints.emplace_back(2, 4);
    CorrectPolyPoints.emplace_back(6, 4);
    CorrectPolyPoints.emplace_back(8, 0);
    CorrectPolyPoints.emplace_back();

    Polygon        Correct(CorrectPolyPoints);
    CorrectPolygon CorrectPoly(CorrectPolyPoints, Correct);
    CorrectPoly.perimeter();
    CorrectPoly.square();
    try {CorrectPoly.CheckClosedLine();}  catch (invalid_argument& e) {cerr << e.what() << endl; return -1;}
    try {CorrectPoly.CheckPolygon();}     catch (invalid_argument& e) {cerr << e.what() << endl; return -1;}

    if (CorrectPoly.CheckPolygon()) {
        cout << "CorrectPoly correct" << endl;
    } else {
        cout << "CorrectPoly not correct" << endl;
    }

//    Справочные материалы
//    push_back добавляет копию объекта (или обеспечивает перемещение, если возможно),
//    а emplace_back создает объект непосредственно в конце вектора,
//    т.е. без лишнего копирования (или перемещения).

    return 0;
}