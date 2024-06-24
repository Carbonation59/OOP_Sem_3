// Почечура Артемий, гр. М8О-206Б-20
// ЛР №8, вариант 3
// Фигуры: квадрат, прямоугольник, трапеция
/* Создать приложение, которое будет считывать из стандартного ввода данные фигур, согласно варианту задания, выводить их характеристики на экран и записывать в файл. Фигуры могут задаваться как своими вершинами, так и другими характеристиками (например, координата центра, количество точек и радиус).
        Программа должна:
                1.   Осуществлять ввод из стандартного ввода данных фигур, согласно варианту задания;
                2.   Программа должна создавать классы, соответствующие введенным данных фигур;
                3.   Программа должна содержать внутренний буфер, в который помещаются фигуры.
                4.   При накоплении буфера они должны запускаться на асинхронную обработку, после чего буфер должен очищаться;
                5.   Обработка должна производиться в отдельном потоке;
                6.   Реализовать два обработчика, которые должны обрабатывать данные буфера:
                a.   Вывод информации о фигурах в буфере на экран;
                b.   Вывод информации о фигурах в буфере в файл. Для каждого буфера должен создаваться файл с уникальным именем.
                7.   Оба обработчика должны обрабатывать каждый введенный буфер.
                                Т.е. после каждого заполнения буфера его содержимое должно выводиться как на экран, так и в файл.
                8.   Обработчики должны быть реализованы в виде лямбда-функций и должны хранится в специальном массиве обработчиков.
                                Откуда и должны последовательно вызываться в потоке – обработчике.
                9.   В программе должно быть ровно два потока (thread). Один основной (main) и второй для обработчиков;
                10.  В программе должен явно прослеживаться шаблон Publish-Subscribe. Каждый обработчик должен быть реализован как отдельный подписчик.
                11.      Реализовать в основном потоке (main) ожидание обработки буфера в потоке-обработчике.
                                Т.е. после отправки буфера на обработку основной поток должен ждать, пока поток обработчик выведет данные на экран и запишет в файл.*/

#include <iostream>
#include <fstream>
#include <exception>
#include <list>
#include <vector>
#include <cmath>
#include <string>
#include <utility>
#include <memory>
#include <future>
#include <mutex>
#include <condition_variable>

double PI = 3.14159265;

using namespace std;

struct Vertex {
        double x = 0;
        double y = 0;
        void print() {
                cout << "(" << x << "; " << y << ")";
        }
};

Vertex operator- (Vertex a, Vertex b) {
        return { a.x - b.x, a.y - b.y };
}

istream& operator>>(istream& in, Vertex& vertex) {
        in >> vertex.x >> vertex.y;
        return in;
}

ostream& operator<<(ostream& out, const Vertex& vertex) {
        out << vertex.x << " " << vertex.y;
        return out;
}

enum class type_figure {
        unknown = -1,
        Rhombus = 0,
        Trapezoid = 1,
        Rectangle = 2,
};

string type_to_string(type_figure type) {
        if (type == type_figure::Rhombus) {
                return "Square";
        }
        else if (type == type_figure::Trapezoid) {
                return "Trapezoid";
        }
        else if (type == type_figure::Rectangle) {
                return "Rectangle";
        }
        else {
                throw runtime_error("Undefined figure type");
        }
}

class Figure {
public:
        vector<Vertex> data;
        Figure() = default;
        Figure(vector<Vertex> vec) : data(vec) {}
        void print() {
                cout << type_to_string(get_type_figure()) << ": (";
                bool is_first = true;
                for (Vertex& v : data) {
                        if (!is_first) {
                                cout << ", ";
                        }
                        is_first = false;
                        v.print();
                }
                cout << ")\n";
        }
        virtual type_figure get_type_figure() {
                return type_figure::unknown;
        }
};

class Rhombus : public Figure {
public:
        Rhombus() : Figure(vector<Vertex>(4)) {}
        Rhombus(Vertex a, Vertex b, Vertex c, Vertex d) : Figure({ a, b, c, d}) {}
        Rhombus(vector<Vertex> v) {
                if (v.size() != 4) {
                        throw invalid_argument("Incorrect number of vertex of rhombus");
                }
                data = v;
        }
        virtual type_figure get_type_figure() { return type_figure::Rhombus; }
};

class Rectangle : public Figure {
public:
        Rectangle() : Figure(vector<Vertex>(4)) {}
        Rectangle(Vertex a, Vertex b, Vertex c, Vertex d) : Figure({ a, b, c, d }) {}
        Rectangle(vector<Vertex> v) {
                if (v.size() != 4) {
                        throw invalid_argument("Incorrect number of vertex of Rectangle");
                }
                data = v;
        }
        virtual type_figure get_type_figure() { return type_figure::Rectangle; }
};

class Trapezoid : public Figure {
public:
        Trapezoid() : Figure(vector<Vertex>(4)) {}
        Trapezoid(Vertex a, Vertex b, Vertex c, Vertex d) : Figure({ a, b, c, d }) {}
        Trapezoid(vector<Vertex> v) {
                if (v.size() != 4) {
                        throw invalid_argument("Incorrect number of vertex of Trapezoid");
                }
                data = v;
        }
        virtual type_figure get_type_figure() { return type_figure::Trapezoid; }
};

istream& operator>>(istream& input, Figure& figure) {
        for (Vertex& v : figure.data) {
                input >> v;
        }
        return input;
}

ostream& operator<<(ostream& output, Figure& figure) {
        output << static_cast<int>(figure.get_type_figure()) << " ";
        for (const Vertex& v : figure.data) {
                output << v << " ";
        }
        return output;
}

enum class type_of_action {
        unknown,
        add,
        remove,
};

struct Action {
        type_of_action type = type_of_action::unknown;
        shared_ptr<Figure> figure_ptr;
};

class Factory {
public:
        list<shared_ptr<Figure>> docs;
        size_t max_size;
        mutex mut;
        condition_variable cv_prod;
        condition_variable cv_cons;
        future<void> fut;
        bool prod_stopped = false;
        Factory(size_t mx) {
                max_size = mx;
                fut = async([&]() {logger(); });
        }
        Factory() {
                max_size = 3;
                fut = async([&]() {logger(); });
        }
        ~Factory() {
                prod_stopped = true;
                cv_cons.notify_all();
                fut.get();
        }
        void inload() {
                static int i = 0;
                i++;
                ofstream out("log" + to_string(i) + ".txt");
                if (!out) {
                        throw invalid_argument("Incorrect filename");
                }
                for (auto& ptr : docs) {
                        out << *ptr << "\n";
                }
                out << "\n";
        }
        void add(shared_ptr<Figure> figure_ptr) {
                unique_lock<mutex> lock(mut);
                cv_prod.wait(lock, [&] { return docs.size() < max_size; });
                docs.push_back(move(figure_ptr));
                cv_cons.notify_all();
        }
        void print() {
                cout << "Add in document log";
                static int i = 0;
                ++i;
                cout << i << ":\n";
                for (const auto& ptr : docs) {
                        ptr->print();
                }
        }
        void logger() {
                while (!prod_stopped) {
                        unique_lock<mutex> lock(mut);
                        cv_cons.wait(lock, [&] { return docs.size() >= max_size || prod_stopped; });
                        if (!docs.empty()) {
                                print();
                                inload();
                                docs.clear();
                        }
                        cv_prod.notify_all();
                }
        }
};

void help() {
        cout << "0 - exit programm\n";
        cout << "1 - input Rhombus\n";
        cout << "2 - input Trapezoid\n";
        cout << "3 - input Rectangle\n";
}

double side_2pow(Vertex a, Vertex b) {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

double cross(Vertex a, Vertex b) {
        return a.x * b.y - b.x * a.y;
}

bool is_rhombus(vector<Vertex>& coord) {
        double a = side_2pow(coord[0], coord[1]);
        double b = side_2pow(coord[1], coord[2]);
        double c = side_2pow(coord[2], coord[3]);
        double d = side_2pow(coord[3], coord[0]);
        if ((a == b) && (b == c) && (c == d) && (d == a)) {
                return true;
        }
        return false;
}

bool is_rectangle(vector<Vertex>& coord) {
        double a = side_2pow(coord[0], coord[1]);
        double b = side_2pow(coord[1], coord[2]);
        double c = side_2pow(coord[2], coord[3]);
        double d = side_2pow(coord[3], coord[0]);
        if ((a == c) && (b == d)) {
                for (int i = 0; i < 3; i++) {
                        if (((coord[(i + 1) % 4].x - coord[i % 4].x) * (coord[(i + 2) % 4].x - coord[(i + 1) % 4].x) +
                                (coord[(i + 1) % 4].y - coord[i % 4].y) * (coord[(i + 2) % 4].y - coord[(i + 1) % 4].y)) != 0) {
                                return false;
                        }
                }
                return true;
        }
        return false;
}

bool is_trapezoid(vector<Vertex>& coord) {
        double s1 = cross(coord[0] - coord[1], coord[2] - coord[3]);
        double s2 = cross(coord[1] - coord[2], coord[0] - coord[3]);
        return (s1 != s2 && (s1 == 0 || s2 == 0));
}

int main() {
        int mx;
        cout << "Enter max size of doc: ";
        cin >> mx;
        Factory doc(mx);
        int cmd = -1;
        help();
        while (cmd != 0) {
                try {
                        cin >> cmd;
                        if (cmd == 1) { // Rhombus
                                cout << "Enter four pair of coord vertex of rhombus: ";
                                vector<Vertex> v(4);
                                for (int i = 0; i < 4; i++) {
                                       if(!(cin >> v[i])){
                                                cin.clear();
                                                cin.ignore(1e9, '\n');
                                                throw runtime_error("Incorrect values");
                                        }
                                }
                                if (is_rhombus(v)) {
                                        doc.add(make_shared<Rhombus>(v));
                                }
                                else {
                                        cout << "Is not a rhombus\n";
                                }
                        }
                        else if (cmd == 2) { // Trapezoid
                                cout << "Enter four pair of coord vertex of trapezoid: ";
                                vector<Vertex> v(4);
                                for (int i = 0; i < 4; i++) {
                                       if(!(cin >> v[i])){
                                                cin.clear();
                                                cin.ignore(1e9, '\n');
                                                throw runtime_error("Incorrect values");
                                        }
                                }
                                if (is_trapezoid(v)) {
                                        doc.add(make_shared<Trapezoid>(v));
                                }
                                else {
                                        cout << "Is not a trapezoid\n";
                                }
                        }
                        else if (cmd == 3) { // Rectangle
                                cout << "Enter four pair of coord vertex of rectangle: ";
                                vector<Vertex> v(4);
                                for (int i = 0; i < 4; i++) {
                                        if(!(cin >> v[i])){
                                                cin.clear();
                                                cin.ignore(1e9, '\n');
                                                throw runtime_error("Incorrect values");
                                        }
                                }
                                if (is_rectangle(v)) {
                                        doc.add(make_shared<Rectangle>(v));
                                }
                                else {
                                        cout << "Is not a rectangle\n";
                                }
                        }
                        else if (cmd == 0) {
                                break;
                        }
                        else {
                                throw runtime_error("Wrong command");
                        }
                }
                catch (runtime_error& ex) {
                        cout << ex.what() << "\n";
                }
                catch (invalid_argument& ex) {
                        cout << ex.what() << "\n";
                }
                catch (out_of_range& ex) {
                        cout << ex.what() << "\n";
                }
        }
        return 0;
}
