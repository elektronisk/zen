#include <iostream>
#include <QWidget>
#include <QGridLayout>
#include <board.h>

Board::Board(QWidget *parent) : QWidget(parent) {
	setupBoard(QSize(2,2)); //default size
}

void Board::resetBoard(QSize dim) {
	clearBoard();
	setupBoard(dim);
}

void Board::clearBoard() {
	// clear previous board
	for (int x = 0; x < boardSize.width(); x++) {
		for (int y = 0; y < boardSize.height(); y++) {
			delete tileArray[y*boardSize.height() + x];
		}
	}
	delete tileLayout;	// Get rid of the layout
	delete[] tileArray; // And the allocated array of pointers to the tiles that are now gone
}

void Board::setupBoard(QSize dim) {
	
	if (!dim.isValid() || dim.isNull()) {
		dim = QSize(2,2);
	}
	boardSize = dim;

	int totaltiles = boardSize.width()*boardSize.height();
	tileArray = new Tile*[totaltiles]; //Array of pointers to tiles
	
	tileLayout = new QGridLayout(this);
	tileLayout->setSpacing(0);
	setLayout(tileLayout);

	Tile *tempTile;
	for (int x = 0; x < boardSize.width(); x++) {
		for (int y = 0; y < boardSize.height(); y++) {
			tempTile= new Tile(0, this); // Allocate tiles to the pointers
			tileArray[y*boardSize.height() + x] = tempTile;
			
			connect(tempTile, SIGNAL(rotated()), this, SLOT(checkSolved()));
			tileLayout->addWidget(tempTile, y, x);
		}
	}
	
	// go through the shared edges and randomize their status.
	srand(time(NULL));
	for (int x = 0; x < (boardSize.width() - 1); x++) {
		for (int y = 0; (y < boardSize.height() - 1); y++) {
			int u = rand() % 2;
			tileArray[y*boardSize.height() + x]->setEdge(EDGE_DOWN, u);
			tileArray[(y+1)*boardSize.height()+x]->setEdge(EDGE_UP, u);
			u = rand() % 2;
			tileArray[y*boardSize.height() + x]->setEdge(EDGE_RIGHT, u);
			tileArray[y*boardSize.height() + x +1]->setEdge(EDGE_LEFT,u);
		}
	}
	
	// go through the tiles and randomize their rotation
	
	for (int x = 0; x < (boardSize.width()); x++) {
		for (int y = 0; (y < boardSize.height()); y++) {
			tempTile = tileArray[y*boardSize.height() + x];
			int r = rand() % 4;
			tempTile->rotaten(r);
			if (tempTile->getEdgecount() == 0) {
				tempTile->setEnabled(false); // disable tiles with no edges
			}
		}
	}
	checkSolved();
}

Board::~Board() {
	delete tileArray;
	for (int x = 0; x < boardSize.width(); x++) {
		for (int y = 0; y < boardSize.height(); y++) {
			delete tileArray[y*boardSize.height() + x];
		}
	}
}

void Board::deactivate() {
	for (int x = 0; x < boardSize.width(); x++) {
		for (int y = 0; y < boardSize.height(); y++) {
			tileArray[y*boardSize.height() + x]->setEnabled(false);
		}
	}
}

bool Board::checkSolved() {
	Tile *tempTile;
	Tile *neighbourTile;
	for (int x = 0; x < boardSize.width(); x++) {
		for (int y = 0; y < boardSize.height(); y++) {
			// Go through each tile
			tempTile = tileArray[y*boardSize.height() + x];
			if (tempTile->getEdgecount() >= 1) {
				// If this tile has one or more edges, it has to be checked
				for (int e = 1; e < 16; e *= 2) {
					// For this tile, check all 4 edges
					if (tempTile->hasEdge(e)) {
						// For each edge, check if it is matched with its neighbour
						switch(e) {
							case EDGE_UP:
								if (y == 0) { return false; }  // is at edge of the board
								neighbourTile = tileArray[(y-1)*boardSize.height() + x];
								if (!neighbourTile->hasEdge(EDGE_DOWN)) {return false;}
								break;
							case EDGE_RIGHT:
								if (x == boardSize.width()) { return false; }
								neighbourTile = tileArray[(y)*boardSize.height() + (x+1)];
								if (!neighbourTile->hasEdge(EDGE_LEFT)) {return false;}
								break;
							case EDGE_DOWN:
								if (y == boardSize.height()) {return false; }
								neighbourTile = tileArray[(y+1)*boardSize.height() + x];
								if (!neighbourTile->hasEdge(EDGE_UP)) {return false;}
								break;
							case EDGE_LEFT:
								if (x == 0) {return false; }
								neighbourTile = tileArray[y*boardSize.height() + (x-1)];
								if (!neighbourTile->hasEdge(EDGE_RIGHT)) {return false;}
								break;
						}
					}
				}
			} else {
				// Tile has no edges to be connected
			}
		}
	}
	emit solved();
	deactivate();
	return true;

}
