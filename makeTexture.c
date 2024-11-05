#include "makeTexture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initializeEmptyArray(int sizeX, int sizeY, int (*Array)[sizeY]){
    for(int x = 0; x<sizeX; x++){
        for (int y =0; y < sizeY; y++){
            Array[x][y] = 0;
        }

    }
}

void populateArray(int sizeX, int sizeY, int (*Array)[sizeY]){
    srand(23265);
    for(int x = 0; x<sizeX; x++){
        for (int y =0; y < sizeY; y++){
            Array[x][y] = rand()<=150000000;
        }
    }
}

void generationStep(int sizeX, int sizeY, int (*Array)[sizeY], int (*tempArray)[sizeY]){
    int neighbors;
    int result;
    int modxplus1;
    int modxminus1;
    int modyplus1;
    int a, b, c, d, e, f, g, h ,i;

    for(int x = 0; x<sizeX; x++){
        modxplus1 = (x+1)%sizeX;
        modxminus1 = x>0?(x-1)%sizeX:sizeX-1;
        
        a = (Array[modxminus1][sizeY-1]);       b = (Array[x][sizeY-1]);        c =(Array[modxplus1][sizeY-1]);
        d = (Array[modxminus1][0]);             e =Array[x][0];                 f =(Array[modxplus1][0]);
        g = (Array[modxminus1][modyplus1]);     h =(Array[x][modyplus1]);       i =(Array[modxplus1][modyplus1]);

        for (int y =0; y < sizeY; y++){
            modyplus1 = (y+2)%sizeY;

            neighbors = (a+b+c+d+f+g+h+i); // no e (the cell we are checking for neighbors)
            result =(neighbors == 3 || (neighbors == 2 && e))?1:0;
            tempArray[x][y]= result;

            a = d;  b = e; c = f;
            d = g; e = h; f = i;
            g = Array[modxminus1][modyplus1];   h = Array[x][modyplus1];        i = Array[modxplus1][modyplus1];
        }
    }
    memcpy(Array, tempArray, sizeof(int) * sizeX * sizeY);
}

// for checking that i didn't mess it up
int tallyArray(int sizeX, int sizeY, int (*Array)[sizeY]){
    int tally = 0;
    for(int x = 0; x<sizeX; x++){
        for (int y =0; y < sizeY; y++){
            tally +=Array[x][y];
        }
    }
    return tally;
}

void alterCell(int sizeX, int sizeY, int (*Array)[sizeY], int x, int y, int state){
    Array[x][y] = state;
}