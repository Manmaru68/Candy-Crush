#ifndef CANDY_H
#define CANDY_H


#include "definicions.h"
#include "InfoJoc.h"
#include "GraphicManager.h"
#include <iostream>
#include <sstream>

using namespace std;

//Gesti� caracteristiques de cada caramel

class Candy
{
public:
	Candy() : m_color(NO_COLOR), m_tipus(NO_TIPUS), m_held(false) {}
	Candy(ColorCandy c, TipusCandy t) : m_color(c), m_tipus(t), m_held(false) {}

	ColorCandy getColor() const { return m_color; }
	TipusCandy getTipus() const { return m_tipus; }
	bool isHeld() const { return m_held; }
	void setColor(ColorCandy color) { m_color = color; }
	void setTipus(TipusCandy tipus) { m_tipus = tipus; }
	void setHeld(bool held) { m_held = held; }
	string intToString(int& canvi);
	void dibuixa(int posX, int posY, bool gridSnap);
	bool operator==(Candy& candyIgual);


private:
	ColorCandy m_color;
	TipusCandy m_tipus;
	bool m_held;

};



#endif
