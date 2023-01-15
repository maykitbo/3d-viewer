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

void Fasade::Move(float x, float y, float z) {
    std::cout << "move: " << x << " " << y << " " << z << "\n";
}

void Fasade::Rotate(float x, float y, float z) {
    std::cout << "rotate: " << x << " " << y << " " << z << "\n";
}

void Fasade::Scale(float s) {
    std::cout << "scale: " << s << "\n";
}

void Fasade::ESize(float s) {
    std::cout << "e size: " << s << "\n";
}

void Fasade::VSize(float s) {
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

void Fasade::RType(RotateType t) {
    std::cout << "r type: " << (int)t << "\n";
}

void Fasade::VColor(QColor c) {
    std::cout << "Vertices Color: " << c.redF() << " " << c.greenF() << " " << c.blueF() << "\n";
    control_->SetVColor(ClolorToString(c));
}

void Fasade::EColor(QColor c) {
    std::cout << "Lines Color: " << c.redF() << " " << c.greenF() << " " << c.blueF() << "\n";
    control_->SetEColor(ClolorToString(c));
}

void Fasade::BgColor(QColor c) {
    std::cout << "Background Color: " << c.redF() << " " << c.greenF() << " " << c.blueF() << "\n";
    control_->SetBgColor(ClolorToString(c));
}

void Fasade::Gif(double t, int fps) {
    std::cout << "gif: " << t << "s " << fps << " fps\n";
}

void Fasade::Render(RenderType type) {
    std::cout << "render: " << (int)type << "\n";
}


