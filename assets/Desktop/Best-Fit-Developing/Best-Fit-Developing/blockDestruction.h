#pragma once


void RowSwap(int RowNumber,int gameBoard[10][20]){
    for(int r = RowNumber; r > 0;r--){
        for(int c = 0; c < 10; c++){
            gameBoard[c][r] = gameBoard[c][r-1];
        }
    }

    for(int c = 0; c < 10; c++){
        gameBoard[c][0] = 0;
    }
}



void RowCheck(int gameBoard[10][20],int &rowsDestroyed){
    bool Destroyable = 1;
    for (int r = 0; r < 20; r++){
        Destroyable = 1;
        for(int c = 0; c < 10;c++){
            if(gameBoard[c][r] == 0){
                Destroyable = 0;
                break;
            }
        }
        if(Destroyable){
            RowSwap(r,gameBoard);
            rowsDestroyed += 1;
            r--;
        }
        
    }
}
