#include "gameType.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std; 
int main()
{
    gameType g1; 
    deckType mainDeck;
    deckType playPile; 

    //STARTING THE GAME
    srand(time(0));

    //Get Player Info
    g1.readPlayerData(); 

    /* Debug Only : Check player data
    for (int i = 0; i < 4; i++) {
        g1.players[i].printPlayerData(); 
    }
    */

    //Deal Hands
    mainDeck.generateDeck();
    for (int i = 0; i < 4; i++) {
        g1.players[i].dealHand(mainDeck);
    }

    //Set first card to play from
    playPile.addCard(mainDeck.drawRandomCard());
    g1.setTopCard(playPile);
    
    //Initialize first player and game direction
    g1.setCurrentPlayer(0);
    g1.setGameDirection(directionType::CLOCKWISE);

    //GAMEPLAY LOOP
    //Winstate consideration
    while (g1.getPlayerWon() == false) {
   
        //CURRENT PLAYER MOVES    
        
        //Reset card flags
        g1.setDrawActive(false); 
        g1.setWildActive(false); 
        g1.setReverseActive(false);
        g1.setSkipActive(false); 

        //Print needed information
        cout << "======================" << endl << "Top card:" << endl;
        g1.getTopCard().printCardInfo(); 
        cout << "======================" << endl << endl;
        cout << g1.players[g1.getCurrentPlayer()].getName() << "'s Current Hand: " << endl;
        g1.players[g1.getCurrentPlayer()].printHand(); 

        //User-controlled
        if (g1.players[g1.getCurrentPlayer()].getPlayerControlled() == true) {
            
            //Valid card to play
            if (g1.players[g1.getCurrentPlayer()].readMove(g1.getTopCard(), playPile) == true) {
                g1.setTopCard(playPile);

                //Activate draw card flag, if needed
                if (g1.getTopCard().getLabel() == cardLabelType::DRAW2 || g1.getTopCard().getLabel() == cardLabelType::DRAW4)
                    g1.setDrawActive(true);

                //Activate wild card flag, if needed
                if (g1.getTopCard().getLabel() == cardLabelType::WILD || g1.getTopCard().getLabel() == cardLabelType::DRAW4)
                    g1.setWildActive(true);

                //Activate skip card flag, if needed
                if (g1.getTopCard().getLabel() == cardLabelType::SKIP)
                    g1.setSkipActive(true); 

                //Activate reverse card flag, if needed
                if (g1.getTopCard().getLabel() == cardLabelType::REVERSE)
                    g1.setReverseActive(true); 
            }
            

            //No cards to play
            else {               
               
                //Check if main deck is empty
                if (mainDeck.getSize() == 0) 
                    mainDeck.swapDeck(playPile);
               
                //Otherwise, draw a card
                else 
                    g1.players[g1.getCurrentPlayer()].drawCard(mainDeck);
            }

        }
            
        //Automated
        else if (g1.players[g1.getCurrentPlayer()].getPlayerControlled() == false) {
            
            //Valid card to play
            if (g1.players[g1.getCurrentPlayer()].setRandomMove(g1.getTopCard(), playPile) == true) {
                g1.setTopCard(playPile);

                //Activate draw card flag, if needed
                if (g1.getTopCard().getLabel() == cardLabelType::DRAW2 || g1.getTopCard().getLabel() == cardLabelType::DRAW4)
                    g1.setDrawActive(true);

                //Activate wild card flag, if needed
                if (g1.getTopCard().getLabel() == cardLabelType::WILD || g1.getTopCard().getLabel() == cardLabelType::DRAW4)
                    g1.setWildActive(true); 

                //Activate skip card flag, if needed
                if (g1.getTopCard().getLabel() == cardLabelType::SKIP)
                    g1.setSkipActive(true);

                //Activate reverse card flag, if needed
                if (g1.getTopCard().getLabel() == cardLabelType::REVERSE)
                    g1.setReverseActive(true);
            }

            //No cards to play
            else {
                
                //Check if main deck is empty
                if (mainDeck.getSize() == 0)
                    mainDeck.swapDeck(playPile); 
               
                //Otherwise, draw a card
                else  
                    g1.players[g1.getCurrentPlayer()].drawCard(mainDeck);

            }
        }

        //Check if that move made an "Uno"
        if (g1.players[g1.getCurrentPlayer()].hand.getSize() == 1)
            cout << "***** UNO! *****" << endl;

        //Check if that move won the game
        g1.players[g1.getCurrentPlayer()].setWinState(); 
        if (g1.players[g1.getCurrentPlayer()].getWinState() == true) {
            cout << g1.players[g1.getCurrentPlayer()].getName() << " Wins!" << endl;
            return 0; 
        }

        

        //Wild Card Operation
        if (g1.getWildActive() == true && (g1.getTopCard().getLabel() == cardLabelType::DRAW4 || g1.getTopCard().getLabel() == cardLabelType::WILD)) {
            
            g1.readWildColor(); 

            //Reset wild card flag
            g1.setWildActive(false); 
        }


        // DETERMINING NEXT PLAYER
        //Reverse Card
        if (g1.getTopCard().getLabel() == cardLabelType::REVERSE) {
            
            if (g1.getGameDirection() == directionType::CLOCKWISE && g1.getReverseActive() == true) {
                g1.setGameDirection(directionType::COUNTERCLOCKWISE);
                g1.setCurrentPlayer(g1.getCurrentPlayer() - 1);

                //Reset reverse card flag
                g1.setReverseActive(false); 
            }

            else if (g1.getGameDirection() == directionType::COUNTERCLOCKWISE && g1.getReverseActive() == true) {
                g1.setGameDirection(directionType::CLOCKWISE);
                g1.setCurrentPlayer(g1.getCurrentPlayer() + 1);

                //Reset reverse card flag
                g1.setReverseActive(false); 
            }

        }
        
        //Advancing to next player based on play direction
               
        // Skip Card
        else if (g1.getTopCard().getLabel() == cardLabelType::SKIP) {
            
            if (g1.getGameDirection() == directionType::CLOCKWISE && g1.getSkipActive() == true) {
                g1.setCurrentPlayer(g1.getCurrentPlayer() + 2);

                //Reset skip card flag
                g1.setSkipActive(false);
            }
            else if (g1.getGameDirection() == directionType::COUNTERCLOCKWISE && g1.getSkipActive() == true) {
                g1.setCurrentPlayer(g1.getCurrentPlayer() - 2);

                //Reset skip card flag
                g1.setSkipActive(false);
            }

        }

        //Standard Case
        else {
            
            if (g1.getGameDirection() == directionType::CLOCKWISE)
                g1.setCurrentPlayer(g1.getCurrentPlayer() + 1);
            else if (g1.getGameDirection() == directionType::COUNTERCLOCKWISE)
                g1.setCurrentPlayer(g1.getCurrentPlayer() - 1); 
      
        }
        


        //DRAW2 OR DRAW4 (ADDING CARDS TO NEXT PLAYER'S HAND)
        //Draw 2
        if (g1.getDrawActive() == true && g1.getTopCard().getLabel() == cardLabelType::DRAW2) {
            g1.players[g1.getCurrentPlayer()].draw2(mainDeck);
            
            //Skip move
            if (g1.getGameDirection() == directionType::CLOCKWISE)
                g1.setCurrentPlayer(g1.getCurrentPlayer() + 1);
            else if (g1.getGameDirection() == directionType::COUNTERCLOCKWISE)
                g1.setCurrentPlayer(g1.getCurrentPlayer() - 1);

            //Reset draw card flag
            g1.setDrawActive(false); 

        }

        //Draw 4
        if (g1.getDrawActive() == true && g1.getTopCard().getLabel() == cardLabelType::DRAW4) {
            g1.players[g1.getCurrentPlayer()].draw4(mainDeck);
            
            //Skip move
            if (g1.getGameDirection() == directionType::CLOCKWISE)
                g1.setCurrentPlayer(g1.getCurrentPlayer() + 1);
            else if (g1.getGameDirection() == directionType::COUNTERCLOCKWISE)
                g1.setCurrentPlayer(g1.getCurrentPlayer() - 1);

            //Reset draw card flag
            g1.setDrawActive(false); 
        }

        


    }
    
}


