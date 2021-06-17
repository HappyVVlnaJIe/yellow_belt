#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <math.h> 
#include <memory>

const double PI = 3.14;

class Figure {
public:
    virtual std::string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Triangle :public Figure {
public:
    Triangle(double a, double b, double c) : _a(a), _b(b), _c(c) {}
    std::string Name() const override {
        return "TRIANGLE";
    }
    double Perimeter() const override {
        return _a + _b + _c;
    }
    double Area() const override {
        double p = Perimeter() / 2;
        return sqrt(p*(p-_a)*(p-_b)*(p-_c));
    }
private:
    double _a, _b, _c;
};

class Rect :public Figure {
public:
    Rect(double width, double height) : _width(width), _height(height) {}
    std::string Name() const override {
        return "RECT";
    }
    double Perimeter() const override {
        return (_width+_height)*2;
    }
    double Area() const override {
        return _width*_height;
    }
private:
    double _width, _height;
};

class Circle :public Figure {
public:
    Circle(double r) : _r(r) {}
    std::string Name() const override {
        return "CIRCLE";
    }
    double Perimeter() const override {
        return 2*PI*_r;
    }
    double Area() const override {
        return PI * _r * _r;
    }
private:
    double _r;
};

std::shared_ptr<Figure> CreateFigure(std::istringstream& is) {
    std::string figure;
    is >> figure;
    if (figure=="RECT") {
        double width, height;
        is >> width >> height;
        return std::make_shared<Rect>(width, height);
    }
    if (figure == "TRIANGLE") {
        double a, b, c;
        is >> a >> b >> c;
        return std::make_shared<Triangle>(a,b,c);
    }
    if (figure == "CIRCLE") {
        double r;
        is >> r;
        return std::make_shared<Circle>(r);
    }
}

int main() {
    std::vector<std::shared_ptr<Figure>> figures;
    for (std::string line; getline(std::cin, line); ) {
        std::istringstream is(line);

        std::string command;
        is >> command;
        if (command == "ADD") {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> std::ws;
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                std::cout << std::fixed << std::setprecision(3)
                    << current_figure->Name() << " "
                    << current_figure->Perimeter() << " "
                    << current_figure->Area() << std::endl;
            }
        }
    }
    return 0;
}