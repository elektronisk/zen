#include <iostream>
#include <QPalette>
#include <QPushButton>
#include "tile.h"

Tile::Tile(unsigned char bits, QWidget *parent) : QPushButton(parent) {
	
	setMinimumSize(50,50);
	setMaximumSize(50,50);
	setIconSize(QSize(50,50));
	setEdges(bits);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	setFlat(true);
	connect(this, SIGNAL(clicked(bool)), this, SLOT(rotate()));
}

void Tile::setEdges(unsigned char bits) {
	if (bits > 15) {
		bits = 0;
	} else {
		this->edgebits = bits;
	}
	updateIcon();
}
void Tile::setEdge(unsigned char edge, bool state) {
	edgebits = 0x0F & (edgebits & ~edge); // clear bit
	if (state == true) {
		edgebits |= edge; // set bit
	}
	updateIcon();
}

void Tile::updateIcon() {
	QIcon icon(QString("img/%1.png").arg((int)edgebits));
	setIcon(icon);
}

int Tile::getEdgecount() {
	int count = 0;
	if (this->edgebits & EDGE_UP) count++;
	if (this->edgebits & EDGE_RIGHT) count++;
	if (this->edgebits & EDGE_DOWN) count++;
	if (this->edgebits & EDGE_LEFT) count++;
	return count;
}

bool Tile::hasEdge(unsigned char edgebit) {
	return (edgebits & edgebit)? true : false;
}

void Tile::rotate() {
	if (edgebits == 0) return;
	unsigned char temp = edgebits & 8; // save leftmost bit before left shift (right rotate)
	edgebits = edgebits << 1;
	edgebits &= 0x0E;
	edgebits |= (temp ? 1 : 0);
	updateIcon();
	emit rotated();
}
void Tile::rotaten(int n) {
	if (n == 0) return;
	rotate();
	rotaten(n-1);
}
