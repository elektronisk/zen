#ifndef board_h
#define board_h

#include <QWidget>
#include <QSize>
#include <QGridLayout>
#include "tile.h"

class Board : public QWidget {
	Q_OBJECT
	
private:
	QGridLayout *tileLayout;
	QSize boardSize;
	Tile **tileArray; // 2D array of pointers to tiles
	void deactivate();

signals:
	void solved();

public slots:
	bool checkSolved();

public:
	Board(QWidget *parent);
	~Board();
	void resetBoard(QSize dim);
	void clearBoard();
	void setupBoard(QSize);

};

#endif
