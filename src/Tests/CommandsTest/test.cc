#include "../../Mediator/Mediator.h"
#include "../../Controller/Controller.h"

int main() {
    s21::Shell commands;
    s21::Controller control(&commands);
    s21::Mediator mediator(&control);
    commands.AddMediator(&mediator);
}
