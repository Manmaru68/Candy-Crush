#ifndef PARTIDA_H
#define PARTIDA_H

#include <string>
#include <iostream>
#include <fstream>
#include "tauler.h"
#include "posicio.h"

using namespace std;

class Partida
{
public:
    Partida() {}
    void inicialitza(const string& nomFitxer);
    bool iniciaMoviment(const Posicio& pos1, const Posicio& pos2);
    void continuaMoviment(const Posicio& pos1, const Posicio& pos2);
    void escriuTauler(const string& nomFitxer);
    Candy stringToCandy(const char& caramelInput);
    char candyToString(const Candy& caramelInput);

    //SETTERS
    void setCaramelObjectiu(ColorCandy& CaramelObjectiu) { m_CaramelObjectiu = CaramelObjectiu; }
    void setQuantitatObjectiu(int& QuantitatObjectiu) { m_QuantitatObjectiu = QuantitatObjectiu; }
    void setMoviments(int& Moviments) { m_Moviments = Moviments; }
    void setQuantitatCaramels(int& Caramels) { m_nQuantitatCaramels = Caramels; }
    void setMovimentsFets(int& moviments) { m_nMovimentsFets = moviments; }
    void setTauler(Tauler& tauler) { m_tauler = tauler; }
    void setMovementState(MovementState state) { m_movementState = state;}

    //GETTERS
    ColorCandy getCaramelObjectiu() const { return m_CaramelObjectiu; }
    int getQuantitatObjectiu() const { return m_QuantitatObjectiu; }
    int getMoviments() const { return m_Moviments; }
    int getQuantitatCaramels() const { return m_nQuantitatCaramels; }
    int getMovimentsFets() const { return m_nMovimentsFets; }
    Tauler getTauler() const { return m_tauler; }
    MovementState getMovementState() const { return m_movementState; }

private:
    Tauler m_tauler;
    ColorCandy m_CaramelObjectiu;
    MovementState m_movementState;
    int m_QuantitatObjectiu;
    int m_Moviments;
    int m_nQuantitatCaramels;
    int m_nMovimentsFets;

};


#endif
