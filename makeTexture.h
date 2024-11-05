#ifndef _drawFrame_H_
#define _drawFrame_H_
#include <stddef.h>
#include <stdlib.h>

void initializeEmptyArray(int sizeX, int sizeY, int (*Array)[sizeY]);

void populateArray(int sizeX, int sizeY, int (*Array)[sizeY]);

void generationStep(int sizeX, int sizeY, int (*Array)[sizeY], int (*tempArray)[sizeY]);

int tallyArray(int sizeX, int sizeY, int (*Array)[sizeY]);

void alterCell(int sizeX, int sizeY, int (*Array)[sizeY], int x, int y, int state);
#endif /*_makeTexture_H_*/