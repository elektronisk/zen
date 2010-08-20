#include <iostream>
#include <QPalette>
#include <QPushButton>
#include "tile.h"

Tile::Tile(unsigned char bits, QWidget *parent) : QPushButton(parent) {
	
	setMinimumSize(50,50);
	setMaximumSize(50,50);
	setIconSize(QSize(50,50));
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	
	setEdges(bits);
	setFlat(true);
	connect(this, SIGNAL(clicked(bool)), this, SLOT(rotate()));
}

void Tile::setEdges(unsigned char bits) { // Assign all 4 edges at once with a bitmap
	bits &= 0x0F; // mask away bits other than the lower 4 bits
	this->edgebits = bits;
	updateIcon();
}
void Tile::setEdge(unsigned char edge, bool state) { // Set a specific edge to a chosen state.
	edgebits = 0x0F & (this->edgebits & ~edge); // clear bit first
	if (state == true) {
		edgebits |= edge; // set bit, or leave it cleared depending on 
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
	return (this->edgebits & edgebit) ? true : false;
}

void Tile::rotate() {
	if (this->edgebits == 0) return;
	unsigned char temp = edgebits & 8;	// save the last and fourth bit before left shift (right rotate)
	edgebits = edgebits << 1; 			// Example:  0000 1110 -> 0001 1100
	edgebits &= 0x0E;					// -> 0000 1100
	edgebits |= (temp ? 1 : 0);			// -> 0000 1101    (moves the saved 'end' bit back to the beginning)
	updateIcon();
	emit rotated();
}
void Tile::rotaten(int n) {
	if (n == 0) return;
	n &= 0x3; // only use the lower two bits - limits rotation to three times.
	rotate();
	rotaten(n-1);
}
