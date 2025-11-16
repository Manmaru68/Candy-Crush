#include "Joc.hpp"
#include "InfoJoc.h"
#include "GraphicManager.h"
#include <iostream>


void Joc::inicialitza(const string& nomFitxer)
{
   
  
    m_partida.inicialitza(nomFitxer);
    m_estat = ESTAT_JOC_ESPERA;
    GraphicManager::getInstance()->drawSprite(IMAGE_BACKGROUND, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, CELL_INIT_X, CELL_INIT_Y, false);

    
}


void Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus, double deltaTime) //IMPORTANT, ENTRA A LA FUNCIO CADA "MICROSEGON", PER LO QUE POSAR VARIABLES DE CONTROL 
{

    GraphicManager::getInstance()->drawSprite(IMAGE_BACKGROUND, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, CELL_INIT_X, CELL_INIT_Y, false);

    GraphicManager::getInstance()->drawSprite(IMAGE_RECTANGLE, 300, 65, true);
    GraphicManager::getInstance()->drawSprite(IMAGE_RECTANGLE, 300, 715, true);
    bool controlMoviment = false;
    string msg; 
    Posicio currentMouseCell = Posicio((mousePosY - CELL_INIT_Y) / 50, (mousePosX - CELL_INIT_X) / 50);

    m_temps += deltaTime;

    msg ="Moviments: " + to_string(m_partida.getMoviments() - m_partida.getMovimentsFets());
    GraphicManager::getInstance()->drawFont(FONT_RED_30, 30, 40, 1.0, msg);
    GraphicManager::getInstance()->drawSprite(IMAGE_MOVIMENTS, 260, 65, true);
    
    
    if (m_partida.getQuantitatObjectiu() - m_partida.getQuantitatCaramels() > 0)
    {
        msg = "Caramels: "+ to_string(m_partida.getQuantitatObjectiu() - m_partida.getQuantitatCaramels());
    }
    else
    {
        msg = "Caramels: " + to_string(0);
    }
    GraphicManager::getInstance()->drawFont(FONT_RED_30, 320 , 40, 1.0, msg);
    GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE, 525, 65, true);
    
    msg = "X: " + to_string(mousePosX) + ", Y: " + to_string(mousePosY);
    GraphicManager::getInstance()->drawFont(FONT_RED_30, 350, FINAL_INIT_Y+ 8, 1.0, msg);


    switch (m_estat)
    {
    case ESTAT_JOC_ESPERA:


        m_posCandy1.erase();
        m_posCandy2.erase();
        m_mouseHeld = false;
        if ((mouseStatus) && (mousePosX < 550) && (mousePosY < 650) && (mousePosX > 50) && (mousePosY > 150)) //limits tauler en px, per conversió a m_tauler mirar PosX1 o PosX2
        {
            m_estat = ESTAT_JOC_INTERCANVI;
        }

        break;
    case ESTAT_JOC_INTERCANVI:
        
        if (!m_mouseHeld)
        {
            m_posCandy1 = currentMouseCell;
            changeCandyHeld(m_posCandy1, true);
            m_mouseHeld = true;
        }

        m_posCandy2 = currentMouseCell;

        if ((m_posCandy1.up() == m_posCandy2 ||
            m_posCandy1.down() == m_posCandy2 ||
            m_posCandy1.left() == m_posCandy2 ||
            m_posCandy1.right() == m_posCandy2) &&
            !(m_posCandy1 == m_posCandy2))
        {
            controlMoviment = m_partida.iniciaMoviment(m_posCandy1, m_posCandy2);

            if (controlMoviment)
            {
                m_mouseHeld = false;
                changeCandyHeld(m_posCandy1, false);
                changeCandyHeld(m_posCandy2, false);
                m_estat = ESTAT_JOC_MOVIMENTS;
            }
        }

        if (!mouseStatus)
        {
            m_mouseHeld = false;
            changeCandyHeld(m_posCandy1, false);
            m_posCandy1.erase();
            m_posCandy2.erase();
            m_estat = ESTAT_JOC_ESPERA;
        
        }

        
        break;
    case ESTAT_JOC_MOVIMENTS:

        if (m_temps > 0.5)
        {
            m_partida.continuaMoviment(m_posCandy1, m_posCandy2);
            m_temps = 0;
        }
        if (m_partida.getMovementState() == END_MOVEMENT)
        {
            
            m_partida.setMovementState(CHECKING);
            m_posCandy1.erase();
            m_posCandy2.erase();
            m_estat = ESTAT_JOC_ESPERA;
        }

     

        if ((m_partida.getQuantitatObjectiu() <= m_partida.getQuantitatCaramels()) || (m_partida.getMoviments() == m_partida.getMovimentsFets()))
        {
            m_estat = ESTAT_FINAL;
 
        }
        break;
    case ESTAT_FINAL:
        if (m_partida.getMoviments() == m_partida.getMovimentsFets())
        {
            msg = "GAME OVER";
            GraphicManager::getInstance()->drawFont(FONT_RED_30, FINAL_INIT_X, FINAL_INIT_Y+8, 1.0, msg);
        }
        if (m_partida.getQuantitatObjectiu() <= m_partida.getQuantitatCaramels())
        {
            msg = "VICTORY";
            GraphicManager::getInstance()->drawFont(FONT_RED_30, FINAL_INIT_X, FINAL_INIT_Y+8, 1.0, msg);
        }
        return;
        break;
    }
    m_partida.getTauler().dibuixa(mousePosX, mousePosY, deltaTime);
}

void Joc::changeCandyHeld(Posicio pos, bool held)
{
    Tauler tempTauler = m_partida.getTauler();
    Candy caramel = tempTauler.getTauler(pos);
    caramel.setHeld(held);
    tempTauler.setTauler(caramel, pos);
    m_partida.setTauler(tempTauler);
}


   // Afegir l'include de GraphicManager --> #include "GraphicManager.h"
   // Fer la crida de dibuixar un sprite --> GraphicManager::getInstance()->drawSprite(image, posX, posY, centered);
   //	    Per començar podem cridar el drawSprite amb els params --> 
   //          (IMAGE_BACKGROUND,0,0, false) i 
   //          (IMAGE_BOARD, CELL_INIT_X, CELL_INIT_Y, false)



   // Dibuixar a pantalla el gràfic amb el tauler i un caramel blau centrat a la posició (2,2) del tauler


   //GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE, CELL_INIT_X + (posX * CELL_W) + (CELL_W / 2), CELL_INIT_Y + (posY * CELL_H) + (CELL_H / 2), true);





   // Dibuixar un caramel blau centrat a la posició (2,2) del tauler només si estem pressionant el botó esquerre del mouse
   // Si no l'estem pressionant només s'ha de dibuixar el tauler sense el caramel

   //if (mouseStatus)
   //{
   //    GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE, CELL_INIT_X + (posX * CELL_W) + (CELL_W / 2), CELL_INIT_Y + (posY * CELL_H) + (CELL_H / 2), true);
   //}



   // Si estem pressionant el botó esquerre del mouse, dibuixar un caramel blau centrat a la posició del tauler on tenim el mouse
   // Si no l'estem pressionant només s'ha de dibuixar el tauler sense el caramel

   //if (mouseStatus)
   //{
    //   GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE, CELL_INIT_X + (mousePosX * CELL_W) + (CELL_W / 2), CELL_INIT_Y + (mousePosY * CELL_H) + (CELL_H / 2), true);
   //}


   // Dibuixar un caramel blau a la posicio (2,2) del tauler. Eliminar-lo quan hagi passat mig segon. 
   // Tornar-lo a dibuixar al cap de mig segon i anar repetint el cicle eliminar/dibuixar cada mig segon

   //m_temps += deltaTime;
   //if (m_temps > 0.5)
   //{
     //  m_visible = !m_visible;
       //m_temps = 0.0;
   //}
    //if (m_visible)
    //   GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE, CELL_INIT_X + (posX * CELL_W) + (CELL_W / 2), CELL_INIT_Y + (posY * CELL_H) + (CELL_H / 2), true);


   
    //Imprimir les coordenades de la posició actual del ratolí a sota del tauler
    //string msg = "X: " + to_string(mousePosX) + ", Y: " + to_string(mousePosY);
    //GraphicManager::getInstance()->drawFont(FONT_WHITE_30, FINAL_INIT_X, FINAL_INIT_Y, 1.0, msg);
