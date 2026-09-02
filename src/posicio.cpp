#include "posicio.h"

Posicio Posicio::up()
{
    Posicio pos = Posicio(m_fila, m_columna);
    if (m_fila - 1 < 0)
        pos.setFila(0);
    else
        pos.setFila(m_fila - 1);
    return pos;
}

Posicio Posicio::left()
{
    Posicio pos = Posicio(m_fila, m_columna);
    if (m_columna - 1 < 0)
        pos.setColumna(0);
    else
        pos.setColumna(m_columna - 1);
    return pos;
}

Posicio Posicio::down()
{
    Posicio pos = Posicio(m_fila, m_columna);
    if (m_fila + 1 > MAX_FILES)
        pos.setFila(MAX_FILES);
    else
        pos.setFila(m_fila + 1);
    return pos;
}

Posicio Posicio::right()
{
    Posicio pos = Posicio(m_fila, m_columna);
    if (m_columna + 1 > MAX_COLUMNES)
        pos.setColumna(MAX_COLUMNES);
    else
        pos.setColumna(m_columna + 1);
    return pos;
}

