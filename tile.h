#ifndef tile_h
#define tile_h

#include <QPushButton>
#include <QWidget>

#define EDGE_UP 1
#define EDGE_RIGHT 2
#define EDGE_DOWN 4
#define EDGE_LEFT 8

class Tile : public QPushButton {
	Q_OBJECT

	unsigned char edgebits; // non-zero value indicates an edge up, right, down and left
	int edgecount;
	
	void updateIcon();
signals:
	void rotated();

public:
	Tile(unsigned char bits, QWidget *parent = 0);
	void setEdge(unsigned char, bool);
	int getEdgecount();
	bool hasEdge(unsigned char edgebit);
	void setEdges(unsigned char bits);
	void rotaten(int n);

public slots:
	void rotate();
	
private:

};

#endif
