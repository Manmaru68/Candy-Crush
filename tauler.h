#ifndef TAULER_H
#define TAULER_H
#include "candy.h"
#include "InfoJoc.h"
#include "GraphicManager.h"
#include "posicio.h"
#include "definicions.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

class Tauler
{

public:
    Tauler() : m_nColumnes(0), m_nFiles(0), m_nMoviments(0), m_gravityPointer(0), m_afterSwipe(false) {};
    ~Tauler();

    //GETTERS
    int getNColumnes() const { return m_nColumnes; };
    int getNFiles() const { return m_nFiles; };
    int getCandiesDestroyed(ColorCandy c) const { return candiesDestroyed[c]; };
    int getMoviments() const {return m_nMoviments; };
    Candy getTauler(int fila, int columna) const { return m_tauler[fila][columna]; };
    Candy getTauler(Posicio pos) const { return m_tauler[pos.getFila()][pos.getColumna()]; };
    bool getAfterSwipe() const { return m_afterSwipe; }


    //SETTERS
    void setTauler(Candy caramel, int fila, int columna) { m_tauler[fila][columna] = caramel; };
    void setTauler(Candy caramel, Posicio pos) {  m_tauler[pos.getFila()][pos.getColumna()] = caramel; };
    void setMoviments(int maxMoviments);

    void inicialitza(int size);
    bool moveCheck(Posicio from, Posicio to);
    bool move(Posicio from, Posicio to, MovementState state);
    void dibuixa(int mousePosX, int mousePosY, double deltaTime);



private:
    Candy m_tauler[MAX_COLUMNES][MAX_FILES];
    Candy m_gravityArray[NUM_COLOR_CANDIES];
    Posicio* m_movimentsFrom;
    Posicio* m_movimentsTo;
    int m_nMoviments;
    int candiesDestroyed[NUM_COLOR_CANDIES];
    int m_nColumnes;
    int m_nFiles;
    int m_gravityPointer;
    bool m_afterSwipe;

    //Funcions auxiliars internes

    bool playerCheck(Posicio from, Posicio to, bool fromPlayer);
    bool check();
    bool checkEmpty(Posicio& emptyPos, int column);
    bool checkForCross(Posicio pos, Posicio posArr[]);
    bool checkForRatllatVertical(Posicio pos, Posicio posArr[]);
    bool checkForRow(Posicio pos, Posicio posArr[], int howMany);
    bool checkForRowVertical(Posicio pos, Posicio posArr[], int howMany);
    bool checkForRowHoritzontal(Posicio pos, Posicio posArr[], int howMany);
    bool checkForRatllatHoritzontal(Posicio pos, Posicio posArr[]);

    void swap(Posicio from, Posicio to);
    void removeCombination(Posicio posArr[], int size, Candy c);
    void removeLinia(Posicio p, TipusCandy t);
    void removeAllColors(ColorCandy color);
    void popCandy(Candy c, Posicio p);
    void gravity();
};

#endif

