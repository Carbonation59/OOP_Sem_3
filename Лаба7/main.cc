// Почечура Артемий, гр. М8О-206Б-20
// ЛР №7, вариант 7
/* Спроектировать простейший «графический» векторный редактор.
Требование к функционалу редактора:
·         создание нового документа
·         импорт документа из файла
·         экспорт документа в файл
·         создание графического примитива (согласно варианту задания)
·         удаление графического примитива
·         отображение документа на экране (печать перечня графических объектов и их характеристик в std::cout)
·         реализовать операцию undo, отменяющую последнее сделанное действие. Должно действовать для операций добавления/удаления фигур.*/
/*Требования к реализации:
·         Создание графических примитивов необходимо вынести в отдельный класс – Factory.
·         Сделать упор на использовании полиморфизма при работе с фигурами;
·         Взаимодействие с пользователем (ввод команд) реализовать в функции main;*/

#include <iostream>
#include <fstream>
#include <exception>
#include <list>
#include <vector>
#include <cmath>
#include <string>
#include <utility>
#include <memory>
#include <stack>

double PI = 3.14159265;

using namespace std;

struct Vertex {
        double x = 0;
        double y = 0;
        void print() {
                cout << "(" << x << "; " << y << ")";
        }
};

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
        Triangle = 0,
        Hexagon = 1,
        Pentagon = 2,
};

string type_to_string(type_figure type) {
        if (type == type_figure::Triangle) {
                return "Triangle";
        }
        else if (type == type_figure::Hexagon) {
                return "Hexagon";
        }
        else if (type == type_figure::Pentagon) {
                return "Pentagon";
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

class Triangle : public Figure {
public:
        Triangle() : Figure(vector<Vertex>(3)) {}
        Triangle(Vertex a, Vertex b, Vertex c) : Figure({ a, b, c}) {}
        Triangle(vector<Vertex> v) {
                if (v.size() != 3) {
                        throw invalid_argument("Incorrect number of vertex of square");
                }
                data = v;
        }
        virtual type_figure get_type_figure() { return type_figure::Triangle; }
};

class Pentagon : public Figure {
public:
        Pentagon() : Figure(vector<Vertex>(5)) {}
        Pentagon(Vertex a, Vertex b, Vertex c, Vertex d, Vertex e) : Figure({ a, b, c, d, e }) {}
        Pentagon(vector<Vertex> v) {
                if (v.size() != 5) {
                        throw invalid_argument("Incorrect number of vertex of pentagon");
                }
                data = v;
        }
        virtual type_figure get_type_figure() { return type_figure::Pentagon; }
};

class Hexagon : public Figure {
public:
        Hexagon() : Figure(vector<Vertex>(6)) {}
        Hexagon(Vertex a, Vertex b, Vertex c, Vertex d, Vertex e, Vertex f) : Figure({ a, b, c, d, e, f }) {}
        Hexagon(vector<Vertex> v) {
                if (v.size() != 6) {
                        throw invalid_argument("Incorrect number of vertex of hexagon");
                }
                data = v;
        }
        virtual type_figure get_type_figure() { return type_figure::Hexagon; }
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

class Docs {
public:
        Docs() = default;
        list<shared_ptr<Figure>> data;
        stack<Action> act;
        void upload(string& filename) {
                ofstream out(filename);
                if (!out) {
                        throw invalid_argument("Incorrect filename");
                }
                for (const auto& ptr : data) {
                        out << *ptr << "\n";
                }
        }
        void inload(const string& filename) {
                data.clear();
                while (act.size() != 0) {
                        act.pop();
                }
                ifstream in(filename);
                if (!in) {
                        throw invalid_argument("Incorrect filename");
                }
                int type_int;
                while (in >> type_int) {
                        type_figure type = (type_figure)type_int;
                        shared_ptr<Figure> figure_ptr;
                        if (type == type_figure::Triangle) {
                                figure_ptr = make_shared<Triangle>();
                        }
                        else if (type == type_figure::Hexagon) {
                                figure_ptr = make_shared<Hexagon>();
                        }
                        else if (type == type_figure::Pentagon) {
                                figure_ptr = make_shared<Pentagon>();
                        }
                        else {
                                throw runtime_error("Undefined figure type");
                        }
                        in >> *figure_ptr;
                        data.push_back(move(figure_ptr));
                }
        }
        void add(shared_ptr<Figure> figure_ptr) {
                Action tmp;
                tmp.type = type_of_action::add;
                tmp.figure_ptr = figure_ptr;
                data.push_back(move(figure_ptr));
                act.push(tmp);
        }
        void remove(size_t idx) {
                if (idx >= data.size() || idx < 0) {
                        throw out_of_range("Index out of range");
                }
                Action tmp;
                tmp.type = type_of_action::remove;
                auto it = next(data.begin(), idx);
                tmp.figure_ptr = *it;
                data.erase(it);
                act.push(tmp);
        }
        void print() {
                for (auto& ptr : data) {
                        ptr->print();
                }
        }
        void undo() {
                if (act.size() == 0) {
                        throw out_of_range("Nothing undo");
                }
                Action tmp = act.top();
                act.pop();
                if (tmp.type == type_of_action::unknown) {
                        return;
                }
                else if (tmp.type == type_of_action::add) {
                        data.pop_back();
                }
                else if (tmp.type == type_of_action::remove) {
                        data.push_back(tmp.figure_ptr);
                }
                else {
                        throw runtime_error("Undefined action type");
                }
        };
};

void help() {
        cout << "0 - exit programm\n";
        cout << "1 filename - inload file\n";
        cout << "2 filename - upload file\n";
        cout << "3 - input triangle\n";
        cout << "4 - input hexagon\n";
        cout << "5 - input pentagon\n";
        cout << "6 ind - remove element\n";
        cout << "7 - print all elments\n";
        cout << "8 - undo\n";
}

double side_2pow(Vertex a, Vertex b) {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool check_vertex(const vector<Vertex>& v) {
        for (int i = 0; i < v.size(); i++) {
                if (side_2pow(v[i % v.size()], v[(i + 1) % v.size()]) != side_2pow(v[(i + 1) % v.size()], v[(i + 2) % v.size()])) {
                        return false;
                }
        }
        return true;
}

int main() {
        Docs doc;
        int cmd = -1;
        help();
        while (cmd != 0) {
                try {
                        cout << "Enter command: ";
                        cin >> cmd;
                        if (cmd == 1) { // inload file
                                cout << "Enter filename: ";
                                string filename;
                                cin >> filename;
                                doc.inload(filename);
                        }
                        else if (cmd == 2) { // upload file
                                cout << "Enter filename: ";
                                string filename;
                                cin >> filename;
                                doc.upload(filename);
                        }
                        else if (cmd == 3) { // Triangle
                                cout << "Enter side: ";
                                double side;
                                if(!(cin >> side) || side<=0){
                                        cin.clear();
                                        cin.ignore(1e9, '\n');
                                        throw runtime_error("Incorrect values");
                                }
                                vector<Vertex> v(3);
                                double R = side / (2 * sin(PI / 3.0));
                                double r = side / (2 * tan(PI / 3.0));
                                v[0].x = -side / 2; v[0].y = -r;
                                v[1].x = 0; v[1].y = R;
                                v[2].x = side / 2; v[2].y = -r;
                                doc.add(make_shared<Triangle>(v));
                        }
                        else if (cmd == 4) { // Hexagon
                                cout << "Enter side: ";
                                double side;
                                if(!(cin >> side) || side<=0){
                                        cin.clear();
                                        cin.ignore(1e9, '\n');
                                        throw runtime_error("Incorrect values");
                                }
                                vector<Vertex> v(6);
                                double R = side / (2 * sin(PI / 6.0));
                                double r = side / (2 * tan(PI / 6.0));
                                v[0].x = -R; v[0].y = 0;
                                v[1].x = -1 * side / 2; v[1].y = r;
                                v[2].x = side / 2; v[2].y = r;
                                v[3].x = R; v[3].y = 0;
                                v[4].x = -1 * side / 2; v[4].y = -1 * r;
                                v[5].x = side / 2; v[5].y = -1 * r;
                                doc.add(make_shared<Hexagon>(v));
                        }
                        else if (cmd == 5) { // Pentagon
                                cout << "Enter side: ";
                                int side;
                                if(!(cin >> side) || side<=0){
                                        cin.clear();
                                        cin.ignore(1e9, '\n');
                                        throw runtime_error("Incorrect values");
                                }
                                double R = side / (2 * sin(PI / 5.0));
                                double r = side / (2 * tan(PI / 5.0));
                                vector<Vertex> v(5);
                                v[0].x = -R; v[0].y = 0;
                                v[1].x = 0; v[1].y = R;
                                v[2].x = R; v[2].y = 0;
                                v[3].x = -1 * side / 2; v[3].y = -1 * r;
                                v[4].x = side / 2; v[4].y = -1 * r;
                                doc.add(make_shared<Pentagon>(v));
                        }
                        else if (cmd == 6) { // remove
                                cout << "Enter index ";
                                size_t idx;
                                cin >> idx;
                                doc.remove(idx);
                        }
                        else if (cmd == 7) { // print
                                doc.print();
                        }
                        else if (cmd == 8) { // undo
                                doc.undo();
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