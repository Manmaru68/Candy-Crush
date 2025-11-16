#include "candy.h"

bool Candy::operator==(Candy& candyIgual)
{
	//Caramels compatibles, ha de ser mateix color. El tipus es indiferent ja que al fer un moviment v�lid, s'accionar� el tipus tamb�, sent valida la parella (normal, normal, ratllat)
	return candyIgual.getColor() == m_color;
}

string Candy::intToString(int& canvi)
{
	//Per poder inicialitzar a traves d'un string o per poder llegir o escriure
	ostringstream ss;
	ss << canvi;
	return ss.str();
}

void Candy::dibuixa(int posY, int posX, bool gridSnap)
{
    float positionY = posY;
    float positionX = posX;
    if (gridSnap)
    {
        positionX = CELL_INIT_X + (posX * CELL_W) + (CELL_W / 2);
        positionY = CELL_INIT_Y + (posY * CELL_H) + (CELL_H / 2);
    }
         
    switch (m_tipus)
    {
    case NORMAL:
        switch (m_color)
        {
        case VERD:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_GREEN, positionX, positionY, true);
            break;
        case LILA:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PURPLE, positionX, positionY, true);
            break;
        case BLAU:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE, positionX, positionY, true);
            break;
        case TARONJA:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ORANGE, positionX, positionY, true);
            break;
        case VERMELL:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_RED, positionX, positionY, true);
            break;
        case GROC:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_YELLOW, positionX, positionY, true);
            break;
        }
        break;
    case RATLLAT_HORITZONTAL:
        switch (m_color)
        {
        case VERD:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_GREEN_HORIZONTAL, positionX, positionY, true);
            break;
        case LILA:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PURPLE_HORIZONTAL, positionX, positionY, true);
            break;
        case BLAU:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE_HORIZONTAL, positionX, positionY, true);
            break;
        case TARONJA:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ORANGE_HORIZONTAL, positionX, positionY, true);
            break;
        case VERMELL:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_RED_HORIZONTAL, positionX, positionY, true);
            break;
        case GROC:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_YELLOW_HORIZONTAL, positionX, positionY, true);
            break;
        }
        break;
    case RATLLAT_VERTICAL:
        switch (m_color)
        {
        case VERD:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_GREEN_VERTICAL, positionX, positionY, true);
            break;
        case LILA:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PURPLE_VERTICAL, positionX, positionY, true);
            break;
        case BLAU:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE_VERTICAL, positionX, positionY, true);
            break;
        case TARONJA:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ORANGE_VERTICAL, positionX, positionY, true);
            break;
        case VERMELL:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_RED_VERTICAL, positionX, positionY, true);
            break;
        case GROC:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_YELLOW_VERTICAL, positionX, positionY, true);
            break;
        }
        break;
    case ENVOLTORI:
        switch (m_color)
        {
        case VERD:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_GREEN_WRAPPED, positionX, positionY, true);
            break;
        case LILA:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PURPLE_WRAPPED, positionX, positionY, true);
            break;
        case BLAU:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE_WRAPPED, positionX, positionY, true);
            break;
        case TARONJA:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ORANGE_WRAPPED, positionX, positionY, true);
            break;
        case VERMELL:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_RED_WRAPPED, positionX, positionY, true);
            break;
        case GROC:
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_YELLOW_WRAPPED, positionX, positionY, true);
            break;
        }
        break;
    case BOMBA_DE_CARAMEL:
        GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_COLOUR_BOMB, positionX, positionY, true);
        break;
    }
}

