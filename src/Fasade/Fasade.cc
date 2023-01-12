#include "Fasade.h"
#include "../Controller/Controller.h"

using namespace s21;

void Fasade::Parse(std::string &file_path) {
    pars_.parse(file_path);

// действия после парсинга


    std::cout << pars_.getVertex().size() << "\n";
    for (auto i : pars_.getVertex()) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    std::cout << pars_.getLines().size() << "\n";
    for (auto i : pars_.getLines()) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

void Fasade::Move(double x, double y, double z) {
    std::cout << "move: " << x << " " << y << " " << z << "\n";
    control_->SetMove(x, y, z);
}

void Fasade::Rotate(double x, double y, double z) {
    std::cout << "rotate: " << x << " " << y << " " << z << "\n";
    control_->SetRotate(x, y, z);
}

void Fasade::RotateX(double x) {
    std::cout << "rotate x: " << x << "\n";
}

void Fasade::RotateY(double y) {
    std::cout << "rotate y: " << y << "\n";
}

void Fasade::RotateZ(double z) {
    std::cout << "rotate z: " << z << "\n";
}

void Fasade::MoveX(double x) {
    std::cout << "move x: " << x << "\n";
}

void Fasade::MoveY(double y) {
    std::cout << "move y: " << y << "\n";
}

void Fasade::MoveZ(double z) {
    std::cout << "move z: " << z << "\n";
}

void Fasade::Scale(double s) {
    std::cout << "scale: " << s << "\n";
}

void Fasade::ESize(double s) {
    std::cout << "e size: " << s << "\n";
}

void Fasade::VSize(double s) {
    std::cout << "v size: " << s << "\n";
}

void Fasade::EType(EdgesType t) {
    std::cout << "e type: " << (int)t << "\n";
}

void Fasade::VType(VerticesType t) {
    std::cout << "v type: " << (int)t << "\n";
}

void Fasade::PType(Projection t) {
    std::cout << "p type: " << (int)t << "\n";
}

void Fasade::VColor(QColor c) {
    std::cout << "Vertices Color: " << c.redF() << " " << c.greenF() << " " << c.blueF() << "\n";
    control_->SetVColor(ClolorToString(c));
}

void Fasade::EColor(QColor c) {
    std::cout << "Vertices Color: " << c.redF() << " " << c.greenF() << " " << c.blueF() << "\n";
    control_->SetEColor(ClolorToString(c));
}

void Fasade::BgColor(QColor c) {
    std::cout << "Vertices Color: " << c.redF() << " " << c.greenF() << " " << c.blueF() << "\n";
    control_->SetBgColor(ClolorToString(c));
}
