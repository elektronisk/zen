#ifndef zen_h
#define zen_h

#include <QWidget>
#include <QStateMachine>
#include "board.h"
#include "ui_main.h"

class Zen : public QWidget, private Ui::Zen {
	Q_OBJECT

private:
	QStateMachine *gameMachine;
	QState *runningState;
	QState *solvedState;
private slots:
	void on_startButton_clicked();
public:
	Zen();
	

};

#endif
