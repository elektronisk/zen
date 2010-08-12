#include <QStateMachine>
#include "zen.h"
#include "ui_main.h"

Zen::Zen() {
	setupUi(this);
	board->resetBoard(QSize(3,3));
	gameMachine = new QStateMachine;
	runningState = new QState();
	solvedState = new QState();
	
	runningState->addTransition(board, SIGNAL(solved()), solvedState);
	runningState->assignProperty(this, "windowTitle","Zen - Running");
	solvedState->addTransition(startButton, SIGNAL(clicked()), runningState);
	solvedState->assignProperty(this, "windowTitle","Zen - Solved");
	gameMachine->addState(runningState);
	gameMachine->addState(solvedState);
	gameMachine->setInitialState(runningState);
	gameMachine->start();
}

void Zen::on_startButton_clicked() {
	board->resetBoard(QSize(sizeSpinBox->value(),sizeSpinBox->value()));
}
