#include <iostream>
#include "geesespotter_lib.h"

char *createBoard(std::size_t xdim, std::size_t ydim){

    std::size_t size =  xdim * ydim ;

    char *new_array = new char [size]{} ; //allocation of a new array
    // pointer: keep track of where the allocation went. store the address of where the allocation took place

    for(int i = 0; i < size; i++){
        new_array[i] = 0;
    }

    return new_array;

}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim){

    std::size_t size =  xdim * ydim ;

    for( int i = 0; i < size; i++){

        if(board[i] != 9){

            if(i ==0){
                //top left
                if(board[i + xdim] == 9){
                    board[i] += 1;
                }
                if(board[i + xdim + 1] == 9){
                    board[i] += 1;
                }
                if(board[i + 1] == 9){
                    board[i] += 1;
                }


            }
            else if(i == xdim - 1){
                //top right
                if(board[i + xdim] == 9){
                    board[i] += 1;
                }
                if(board[i + xdim - 1] == 9){
                    board[i] += 1;
                }
                if(board[i - 1] == 9){
                    board[i] += 1;
                }

            }
            else if((i >0)&&(i < xdim - 1)){
                //top row
                if(board[i-1]==9){

                    board[i] += 1;
                }
                if(board[i+1]==9){
                        
                    board[i] += 1;
                }
                //3 blocks below board[i]
                for ( int j = 0; j < 3; j ++){

                    if(board[i + xdim - 1 + j] == 9){

                        board[i] += 1;
                    }
                }
            }
            else if(i == xdim *(ydim - 1)){
                //bot left
                if(board[i - xdim] == 9){
                    board[i] += 1;
                }
                if(board[i - xdim + 1] == 9){
                    board[i] += 1;
                }
                if(board[i + 1] == 9){
                    board[i] += 1;
                }

            }
            else if(i == xdim * ydim - 1){
                //bot right
                if(board[i - xdim] == 9){
                    board[i] += 1;
                }
                if(board[i - xdim - 1] == 9){
                    board[i] += 1;
                }
                if(board[i - 1] == 9){
                    board[i] += 1;
                }

            }
            else if((i > xdim *(ydim - 1))&&(i < xdim * ydim - 1)){
                //bot row
                //2 blocks next to board[i]
                if(board[i-1]==9){

                    board[i] += 1;
                }
                if(board[i+1]==9){
                        
                    board[i] += 1;
                }
                //3 blocks above board[i]
                for ( int j = 0; j < 3; j ++){

                    if(board[i - xdim - 1 + j] == 9){

                        board[i] += 1;
                    }
                }
            }
            else if((i%xdim == 0)){
                //left column
                if(board[i+1]==9){
                        
                    board[i] += 1;
                }
                if(board[i+xdim]==9){
                        
                    board[i] += 1;
                }
                if(board[i-xdim]==9){
                        
                    board[i] += 1;
                }
                if(board[i+xdim+1]==9){
                        
                    board[i] += 1;
                }
                if(board[i-xdim+1]==9){
                        
                    board[i] += 1;
                }

            }
            else if((i + 1)%xdim == 0){
                //right column
                if(board[i-1]==9){
                        
                    board[i] += 1;
                }
                if(board[i+xdim]==9){
                        
                    board[i] += 1;
                }
                if(board[i-xdim]==9){
                        
                    board[i] += 1;
                }
                if(board[i+xdim-1]==9){
                        
                    board[i] += 1;
                }
                if(board[i-xdim-1]==9){
                        
                    board[i] += 1;
                }
            }
            else{
                //middle part

                //3 blocks above board[i]
                for ( int j = 0; j < 3; j ++){

                    if(board[i - xdim - 1 + j] == 9){

                        board[i] += 1;
                    }
                }
                //2 blocks next to board[i]
                if(board[i-1]==9){

                    board[i] += 1;
                }
                if(board[i+1]==9){
                    
                    board[i] += 1;
                }
                //3 blocks below board[i]
                for ( int j = 0; j < 3; j ++){

                    if(board[i + xdim - 1 + j] == 9){

                        board[i] += 1;
                    }
                }
            }    
        }
    }
}


void hideBoard(char *board, std::size_t xdim, std::size_t ydim){

    std::size_t size =  xdim * ydim ;

    for(int i = 0; i < size; i++){

        board[i] = board[i]|hiddenBit();
        
    }
}

void cleanBoard(char *board){

    delete[] board;
    board = nullptr;

}

void printBoard(char *board, std::size_t xdim, std::size_t ydim){

    std::size_t size =  xdim * ydim ;

    for(int i = 0; i < size; i ++){

        if((i%xdim == 0)&&(i != 0)){
            std::cout<<std::endl;
        }

        if((board[i]&markedBit()) == markedBit()){

            std::cout<<'M';

        }else if((board[i]&hiddenBit()) == hiddenBit()){

            std::cout<<'*';

        }else{

            std::cout<<(board[i]&valueMask());

        }

    }

    std::cout<<std::endl;

}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){

    //already revealed
    if((board[xdim*(yloc) + xloc] & hiddenBit()) == 0){

        return 2;

    }else{

        //already marked
        if((board[xdim*(yloc) + xloc]&markedBit()) == markedBit()){
            return 1;
        }
        //contains goose
        if((board[xdim*(yloc) + xloc] & valueMask()) == 9){

            board[xdim*(yloc) + xloc] = board[xdim*(yloc) + xloc]^hiddenBit();

            return 9;
        }
    }

    //reveal hidden board

    int i = xdim*(yloc) + xloc;
    board[i] = board[i]^hiddenBit();

    if((board[i]&valueMask()) == 0){
            if(i ==0){
                //top left

                board[i + xdim]^=hiddenBit();
                board[i + xdim + 1]^=hiddenBit();
                board[i + 1]^=hiddenBit();

            }
            else if(i == xdim - 1){
                //top right
                board[i + xdim]^=hiddenBit();
                board[i + xdim - 1]^=hiddenBit();
                board[i - 1]^=hiddenBit();

            }
            else if((i >0)&&(i < xdim - 1)){
                //top row
                board[i-1]^=hiddenBit();
                board[i+1]^=hiddenBit();

                //3 blocks below board[i]
                for ( int j = 0; j < 3; j ++){

                    board[i + xdim - 1 + j]^=hiddenBit();

                }
            }
            else if(i == xdim *(ydim - 1)){
                //bot left
                board[i - xdim]^=hiddenBit();
                board[i - xdim + 1]^=hiddenBit();
                board[i + 1]^=hiddenBit();

            }
            else if(i == xdim * ydim - 1){
                //bot right
                board[i - xdim]^=hiddenBit();
                board[i - xdim - 1]^=hiddenBit();
                board[i - 1]^=hiddenBit();

            }
            else if((i > xdim *(ydim - 1))&&(i < xdim * ydim - 1)){
                //bot row
                //2 blocks next to board[i]
                board[i-1]^=hiddenBit();
                board[i+1]^=hiddenBit();

                //3 blocks below board[i]
                for ( int j = 0; j < 3; j ++){

                    board[i - xdim - 1 + j]^=hiddenBit();
                }
            }
            else if((i%xdim == 0)){
                //left column
                board[i+1]^=hiddenBit();
                board[i+xdim]^=hiddenBit();
                board[i-xdim]^=hiddenBit();
                board[i+xdim+1]^=hiddenBit();
                board[i-xdim+1]^=hiddenBit();

            }
            else if((i + 1)%xdim == 0){
                //right column
                board[i-1]^=hiddenBit();
                board[i+xdim]^=hiddenBit();
                board[i-xdim]^=hiddenBit();
                board[i+xdim-1]^=hiddenBit();
                board[i-xdim-1]^=hiddenBit();

            }
            else{
                //middle part

                //3 blocks above board[i]
                for ( int j = 0; j < 3; j ++){

                    board[i - xdim - 1 + j]^=hiddenBit();
                }
                //2 blocks next to board[i]
                board[i-1]^=hiddenBit();
                board[i+1]^=hiddenBit();
                //3 blocks below board[i]
                for ( int j = 0; j < 3; j ++){

                    board[i + xdim - 1 + j]^=hiddenBit();
                }
            }    

    }

    return 0;

}

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){

    //already revealed
    if((board[xdim*(yloc) + xloc] & valueMask()) == (board[xdim*(yloc) + xloc])){

        return 2;

    }else{

        //already marked
        if ((board[xdim*(yloc) + xloc ] & markedBit()) == markedBit()){

            board[xdim*(yloc) + xloc] = (board[xdim*(yloc) + xloc]-markedBit())|hiddenBit();

        }else{
        
            //mark it
            board[xdim*(yloc) + xloc] = board[xdim*(yloc) + xloc ] | markedBit();

        }
    }
    return 0;
}


bool isGameWon(char *board, std::size_t xdim, std::size_t ydim){

    std::size_t size =  xdim * ydim ;

    for(int i = 0; i < size; i++){

        if(((board[i] & hiddenBit()) == hiddenBit())&&((board[i]&valueMask())!=9)){
                return false;
        }
    }
    return true;
}
