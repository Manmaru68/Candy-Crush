#include "tauler.h"

//  Selecciona un Caramel aleatori, utilitzada per generar el tauler.
Candy randomCandy(int i, int j)
{
    srand(time(NULL) + i - j);
    ColorCandy c = static_cast<ColorCandy>(rand() % 6);
    TipusCandy t = static_cast<TipusCandy>(rand() % NUM_TYPE_CANDIES);
    return Candy(c, t);
}

//  Deconstructor 
Tauler::~Tauler()
{
    //if (m_movimentsFrom != nullptr)
      //  delete[] m_movimentsFrom;
    //if (m_movimentsTo != nullptr)
      //  delete[] m_movimentsTo;
}

//  Funcio auxiliar general, retorna true si el punt "point" esta entre vectors de l'array vector, 
//  on cada dos punts d'aquesta array es un vector
bool pointInVector(Posicio point, Posicio vector[], int size)
{
    int i = 0;
    bool inVector = false;
    
    for (int s = 0; s < (size / 2) && !inVector; s++)
    {
        while (i < (vector[1 + s * 2].getColumna() - vector[s * 2].getColumna()) && !inVector)
        {
            Posicio temp = Posicio(vector[s * 2].getFila(), vector[s * 2].getColumna()+i);
            if (point == temp)
                inVector = true;
            else i++;
        }
        if (!inVector)
        {
            i = 0;
            while (i < (vector[1 + s*2].getFila() - vector[s*2].getFila()) && !inVector)
            {
                Posicio temp = Posicio(vector[s*2].getFila()+i, vector[s*2].getColumna());
                if (point == temp)
                    inVector = true;
                else i++;
            }
        }
    }
    return inVector;
}

//  Inicialitza el tauler amb una mida quadrada.
void Tauler::inicialitza(int tamany)
{
    m_nColumnes = tamany;
    m_nFiles = tamany;
    m_gravityPointer = 0;
    m_gravityArray[0].setColor(VERMELL); m_gravityArray[0].setTipus(NORMAL);
    m_gravityArray[1].setColor(TARONJA); m_gravityArray[1].setTipus(NORMAL);
    m_gravityArray[2].setColor(GROC); m_gravityArray[2].setTipus(NORMAL);
    m_gravityArray[3].setColor(BLAU); m_gravityArray[3].setTipus(NORMAL);
    m_gravityArray[4].setColor(VERD); m_gravityArray[4].setTipus(NORMAL);
    m_gravityArray[5].setColor(LILA); m_gravityArray[5].setTipus(NORMAL);
    for (int i = 0; i < tamany; i++)
        for (int j = 0; j < tamany; j++)
            m_tauler[i][j] = randomCandy(i, j);
}


//  Guarda qualsevol moviment en dues arrays dinamiques. Una array indica de on prové el moviment i l'altre cap a on hi va.
void Tauler::setMoviments(int maxMoviments)
{
    m_nMoviments = 0;
    m_movimentsFrom = new Posicio[maxMoviments];
    m_movimentsTo = new Posicio[maxMoviments];
}


bool Tauler::moveCheck(Posicio from, Posicio to)
{
    swap(from, to);
    bool doable = playerCheck(from, to, true);
    if (!doable)
        swap(from, to);
    else
    {
        m_afterSwipe = true;
        m_movimentsFrom[m_nMoviments] = from;
        m_movimentsTo[m_nMoviments++] = to;
    }
    return doable;
}

//  Fa un moviment, retorna true si resulta en una combinacio de caramels i fals si no s'ha fet res.
bool Tauler::move(Posicio from, Posicio to, MovementState state)
{
    bool checking = false;
    switch (state)
    {
    case CHECKING:
        for (int i = m_nFiles - 1; i >= 0 && !checking; i--)
            for (int j = m_nColumnes - 1; j >= 0 && !checking; j--)
                checking = playerCheck(Posicio(i, j), Posicio(m_nFiles - 1 - i, m_nColumnes - 1 - j), false);
        break;
    case DELETING:
        checking = true;
        check();
        break;
    case GRAVITY:
        checking = true;
        gravity();
        break;
    }

    return checking;
}

//  Intercanvia dos caramels a partir de les seves posicions, 
//  també activa aquells caramels que son funcionals en aquesta acció, com la Bomba de Caramel
void Tauler::swap(Posicio from, Posicio to)
{
    Candy cFrom = m_tauler[from.getFila()][from.getColumna()];
    Candy cTo = m_tauler[to.getFila()][to.getColumna()];
    m_tauler[from.getFila()][from.getColumna()] = m_tauler[to.getFila()][to.getColumna()];
    m_tauler[to.getFila()][to.getColumna()] = cFrom;
    

}

//  Mira si hi han combinacions, si hi han retorna true. Comprova modularment cada tipus de caramel.
bool Tauler::check()
{
    bool valid = false;
    if (getTauler(m_movimentsFrom[m_nMoviments-1]).getTipus() == BOMBA_DE_CARAMEL && 
        getTauler(m_movimentsTo[m_nMoviments - 1]).getTipus() == BOMBA_DE_CARAMEL)
    {
        valid = true;

        setTauler(Candy(NO_COLOR, NO_TIPUS), m_movimentsFrom[m_nMoviments - 1]);
        setTauler(Candy(NO_COLOR, NO_TIPUS), m_movimentsTo[m_nMoviments - 1]);
        for (int i = 0; i < NO_TIPUS; i++)
            removeAllColors((ColorCandy)i);
    }
    else if (getTauler(m_movimentsFrom[m_nMoviments - 1]).getTipus() == BOMBA_DE_CARAMEL)
    {
        valid = true;
        removeAllColors(getTauler(m_movimentsTo[m_nMoviments - 1]).getColor());
        setTauler(Candy(NO_COLOR, NO_TIPUS), m_movimentsFrom[m_nMoviments - 1]);
    }
    else if (getTauler(m_movimentsTo[m_nMoviments - 1]).getTipus() == BOMBA_DE_CARAMEL)
    {
        valid = true;
        removeAllColors(getTauler(m_movimentsFrom[m_nMoviments - 1]).getColor());
        setTauler(Candy(NO_COLOR, NO_TIPUS), m_movimentsTo[m_nMoviments - 1]);
    }
    for (int i = m_nFiles - 1; i >= 0; i--)
    {
        for (int j = m_nColumnes - 1; j >= 0; j--)
        {
            Posicio pos(i, j);
            Posicio posArr[4]; // Array de dos vectors com a maxim, indicant de on fins a on son els caramels que conformen una combinació.
            if (checkForRow(pos, posArr, 5)) // Comprovació bomba caramel, major prioritat
            {
                valid = true;
                Candy c(m_tauler[i][j].getColor(), BOMBA_DE_CARAMEL);
                removeCombination(posArr, 2, c);
            }
            else if(checkForCross(pos, posArr))
            {
                valid = true;
                Candy c(m_tauler[i][j].getColor(), ENVOLTORI);
                removeCombination(posArr, 4, c);
            }
            else if (checkForRatllatVertical(pos, posArr))
            {
                valid = true;
                Candy c(m_tauler[i][j].getColor(), RATLLAT_VERTICAL);
                removeCombination(posArr, 2, c);
            }
            else if (checkForRatllatHoritzontal(pos, posArr))
            {
                valid = true;
                Candy c(m_tauler[i][j].getColor(), RATLLAT_HORITZONTAL);
                removeCombination(posArr, 2, c);
            }
            else if (checkForRow(pos, posArr, 3)) //    Comprova caramel normal, menor prioritat
            {
                valid = true;
                Candy c(NO_COLOR, NO_TIPUS);
                removeCombination(posArr, 2, c);
            }
        }
    }
    if (valid) m_afterSwipe = false;
    return valid;
}

bool Tauler::playerCheck(Posicio from, Posicio to, bool fromPlayer)
{
    bool valid = false;
    
    Posicio posArr[4]; // Array de dos vectors com a maxim, indicant de on fins a on son els caramels que conformen una combinació.
    if ((getTauler(from).getTipus() == BOMBA_DE_CARAMEL ||
        getTauler(to).getTipus() == BOMBA_DE_CARAMEL) && fromPlayer) {
        valid = true;
    }
    else if (checkForRow(from, posArr, 5) || checkForRow(to, posArr, 5)) // Comprovació bomba caramel, major prioritat
    {
        valid = true;
    }
    else if (checkForCross(from, posArr) || checkForCross(to, posArr))
    {
        valid = true;
    }
    else if (checkForRatllatVertical(from, posArr) || checkForRatllatVertical(to, posArr))
    {
        valid = true;
    }
    else if (checkForRatllatHoritzontal(from, posArr) || checkForRatllatHoritzontal(to, posArr))
    {
        valid = true;
    }
    else if (checkForRow(from, posArr, 3) || checkForRow(to, posArr, 3)) //    Comprova caramel normal, menor prioritat
    {
        valid = true;
    }

    return valid;
}


//  Elimina una linia sencera, per els caramels ratllats
void Tauler::removeLinia(Posicio p, TipusCandy t)
{
    Candy emptyCandy = Candy(NO_COLOR, NO_TIPUS);
    if (t == RATLLAT_HORITZONTAL)
    {
        for (int i = 0; i < m_nColumnes; i++)
            if (m_tauler[p.getFila()][i].getTipus() != RATLLAT_HORITZONTAL)
                popCandy(m_tauler[p.getFila()][i], Posicio(p.getFila(), i));
            else
                m_tauler[p.getFila()][i] = emptyCandy;
    }

    else if (t == RATLLAT_VERTICAL)
    {
        for (int i = 0; i < m_nFiles; i++)
            if (m_tauler[i][p.getColumna()].getTipus() != RATLLAT_VERTICAL)
                popCandy(m_tauler[i][p.getColumna()], Posicio(i, p.getColumna()));
            else
                m_tauler[i][p.getColumna()] = emptyCandy;
    }

}

// Elimina tots els caramels d'un color
void Tauler::removeAllColors(ColorCandy color)
{
    for (int i = 0; i < m_nFiles; i++)
        for (int j = 0; j < m_nColumnes; j++)
            if (m_tauler[i][j].getColor() == color)
                popCandy(m_tauler[i][j], Posicio(i, j));
}


// Funció general per activar caramels quan un altre caramel s'activa o una combinació es completa
void Tauler::popCandy(Candy c, Posicio p)
{
    Candy emptyCandy = Candy(NO_COLOR, NO_TIPUS);
    switch (c.getTipus())
    {
    case RATLLAT_HORITZONTAL:
    case RATLLAT_VERTICAL:
        removeLinia(p, c.getTipus());
        break;

    case ENVOLTORI:
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
                if (!(i == 0 && j == 0))
                    popCandy(m_tauler[p.getFila() + i][p.getColumna() + j], Posicio(p.getFila() + i, p.getColumna() + j));
        m_tauler[p.getFila()][p.getColumna()] = emptyCandy;
        break;

    case BOMBA_DE_CARAMEL:

        break;

    case NORMAL:
    default:
        m_tauler[p.getFila()][p.getColumna()] = emptyCandy;
        break;
    }
    candiesDestroyed[c.getColor()]++;
}


//  Activa o esborra els caramels d'una combinació, reemplaça l'espai buit amb el caramel especial si es el cas
void Tauler::removeCombination(Posicio posArr[], int size, Candy c)
{
    for (int s = 0; s < size / 2; s++)
        for (int i = 0; i <= abs(posArr[1 + s * 2].getFila() - posArr[s * 2].getFila()); i++)
            for (int j = 0; j <= abs(posArr[1 + s * 2].getColumna() - posArr[s * 2].getColumna()); j++)
            {
                Posicio pos(posArr[s * 2].getFila() + i, posArr[s * 2].getColumna() + j);
                popCandy(m_tauler[pos.getFila()][pos.getColumna()], pos);
            }


    if (c.getTipus() != NORMAL && c.getTipus() != NO_TIPUS)
    {
        if (m_afterSwipe)
        {
            if (c.getTipus() == RATLLAT_HORITZONTAL) c.setTipus(RATLLAT_VERTICAL);
            else if (c.getTipus() == RATLLAT_VERTICAL) c.setTipus(RATLLAT_HORITZONTAL);

            if (pointInVector(m_movimentsFrom[m_nMoviments-1], posArr, size))
                m_tauler[m_movimentsFrom[m_nMoviments-1].getFila()][m_movimentsFrom[m_nMoviments-1].getColumna()] = c;
            else if (pointInVector(m_movimentsTo[m_nMoviments-1], posArr, size))
                m_tauler[m_movimentsTo[m_nMoviments-1].getFila()][m_movimentsTo[m_nMoviments-1].getColumna()] = c;
            else 
                m_tauler[posArr[0].getFila()][posArr[0].getColumna()] = c;
        } else
            m_tauler[posArr[0].getFila()][posArr[0].getColumna()] = c;
    }

}


// Comprova s'hi hi han espais buit en el tauler !(OBSOLET)!
bool Tauler::checkEmpty(Posicio &emptyPos, int column)
{
    Candy emptyCandy = Candy(NO_COLOR, NO_TIPUS);
    int i = m_nFiles - 1; //Busca desde abaix a la dreta fins a dalt a la esquerra horizontalment.
    bool found = false, end = true;
    while (i >= 0 && !found)
    {
        if (m_tauler[i][column] == emptyCandy)
        {
            found = true;
            emptyPos.setFila(i);
            emptyPos.setColumna(column);
        } else i--;
    }
    i = m_nFiles - 1; found = false;
    while (i >= 0 && end)
    {
        if (m_tauler[i][column] == emptyCandy)
            found = true;
        else if (found)
            end = false;
        i--;
    }
    if (!found)
        end = false;
    return end;
}


//  Funcio que fa caure tots els caramels en direcció cap avall i remplaça els espais buits
//  amb els caramels corresponents de manera ciclica.
void Tauler::gravity()
{
    Candy emptyCandy = Candy(NO_COLOR, NO_TIPUS);

    for (int columna = 0; columna < m_nColumnes; columna++)
    {
        int count = m_nFiles - 1;
        for (int i = m_nFiles - 1; i >= 0; i--)
        {
            if (!(m_tauler[i][columna] == emptyCandy))
                m_tauler[count--][columna] = m_tauler[i][columna];
        }
        while(count >= 0)
            m_tauler[count--][columna] = emptyCandy;
    }

    for (int i = m_nFiles - 1; i >= 0; i--)
        for (int j = 0; j < m_nColumnes; j++)
        {
            if (m_tauler[i][j] == emptyCandy)
            {
                m_tauler[i][j] = m_gravityArray[m_gravityPointer];
                m_gravityPointer = (m_gravityPointer + 1) % 6;
            }
        }

}


//  Comprova combinació per caramel ratllat en direcció horitzontal
bool Tauler::checkForRatllatHoritzontal(Posicio pos, Posicio posArr[])
{
    ColorCandy color = m_tauler[pos.getFila()][pos.getColumna()].getColor();
    bool valid = false;
    int i = 0;
    while(i < 4 && !valid)
    {
        int j = 0;
        valid = true;
        while(j < 4 && valid)
        {
            if (!((pos.getColumna() - i+j >= 0) && (pos.getColumna() - i+j < m_nColumnes)) || m_tauler[pos.getFila()][pos.getColumna() - i+j].getColor() == NO_COLOR)
                valid = false;
            else if (color != m_tauler[pos.getFila()][pos.getColumna() - i+j].getColor())
                valid = false;
            else j++;
        }
        i++;
    }
    if (valid)
    {
        posArr[0] = Posicio(pos.getFila(), pos.getColumna() - i+1);
        posArr[1] = Posicio(pos.getFila(), pos.getColumna() - i+1 + 3);
    }

    return valid;
}


// Comprova combinació de qualsevol numero de caramels en qualsevol direcció
bool Tauler::checkForRow(Posicio pos, Posicio posArr[], int howMany)
{
    ColorCandy color = m_tauler[pos.getFila()][pos.getColumna()].getColor();
    bool valid = checkForRowHoritzontal(pos, posArr, howMany);
    if (!valid)
        valid = checkForRowVertical(pos, posArr, howMany);


    return valid;

}


bool Tauler::checkForRowVertical(Posicio pos, Posicio posArr[], int howMany)
{
    ColorCandy color = m_tauler[pos.getFila()][pos.getColumna()].getColor();
    bool valid = false;
    int i = 0;
    while (i < howMany && !valid)
    {
        int j = 0;
        valid = true;
        while (j < howMany && valid)
        {
            if (!((pos.getFila() - i + j >= 0) && (pos.getFila() - i + j < m_nFiles)) || m_tauler[pos.getFila() - i + j][pos.getColumna()].getColor() == NO_COLOR)
                valid = false;
            else if (color != m_tauler[pos.getFila() - i + j][pos.getColumna()].getColor())
                valid = false;
            else j++;
        }
        i++;
    }
    if (valid)
    {
        posArr[0] = Posicio(pos.getFila() - i + 1, pos.getColumna());
        posArr[1] = Posicio(pos.getFila() - i + howMany, pos.getColumna());
    }


    return valid;

}

bool Tauler::checkForRowHoritzontal(Posicio pos, Posicio posArr[], int howMany)
{
    ColorCandy color = m_tauler[pos.getFila()][pos.getColumna()].getColor();
    bool valid = false;
    int i = 0;
    while (i < howMany && !valid)
    {
        int j = 0;
        valid = true;
        while (j < howMany && valid)
        {
            if (!((pos.getColumna() - i + j >= 0) && (pos.getColumna() - i + j < m_nColumnes)) || m_tauler[pos.getFila()][pos.getColumna() - i + j].getColor() == NO_COLOR)
                valid = false;
            else if (color != m_tauler[pos.getFila()][pos.getColumna() - i + j].getColor())
                valid = false;
            else j++;
        }
        i++;
    }
    if (valid)
    {
        posArr[0] = Posicio(pos.getFila(), pos.getColumna() - i + 1);
        posArr[1] = Posicio(pos.getFila(), pos.getColumna() - i + howMany);
    }
    return valid;
}

//  Comprova combinació per caramel ratllat en direcció vertical
bool Tauler::checkForRatllatVertical(Posicio pos, Posicio posArr[])
{
    ColorCandy color = m_tauler[pos.getFila()][pos.getColumna()].getColor();
    bool valid = false;
    int i = 0;
    while(i < 4 && !valid)
    {
        int j = 0;
        valid = true;
        while(j < 4 && valid)
        {
            if (!((pos.getFila() - i+j >= 0) && (pos.getFila() - i+j < m_nFiles)) || m_tauler[pos.getFila() - i+j][pos.getColumna()].getColor() == NO_COLOR)
                valid = false;
            else if (color != m_tauler[pos.getFila() - i+j][pos.getColumna()].getColor())
                valid = false;
            else j++;
        }
        i++;
    }
    if (valid)
    {
        posArr[0] = Posicio(pos.getFila() - i+1, pos.getColumna());
        posArr[1] = Posicio(pos.getFila() - i+1 + 3, pos.getColumna());
    }

    return valid;
}


//  Comprova combinació en forma de creu, per caramel envoltori.
bool Tauler::checkForCross(Posicio pos, Posicio posArr[])
{
    ColorCandy color = m_tauler[pos.getFila()][pos.getColumna()].getColor();
    bool valid = checkForRowVertical(pos, posArr, 3);
    if (valid)
    {
        posArr[2] = posArr[0];
        posArr[3] = posArr[1];
        valid = checkForRowHoritzontal(pos, posArr, 3);
    }
    return valid;
}


void Tauler::dibuixa(int mousePosX, int mousePosY, double deltaTime)
{

    for (int posX = 0; posX < 10; posX++)
        for (int posY = 0; posY < 10; posY++)
        {
            Candy caramel = getTauler(posY, posX);
            if (caramel.isHeld())
                caramel.dibuixa(mousePosY, mousePosX, false);
            else
                caramel.dibuixa(posY, posX, true);
        }
}