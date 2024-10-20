#pragma once
#ifndef GameConstants_H
#define GameConstants_H

#define X_STEP stepX
#define Y_STEP stepY
int GRID_WIDTH = 20;
int GRID_HEIGHT = 20;

const double width = 3.3205;
const double height = 2.296848;

float stepX = width / GRID_WIDTH;
float stepY = height / GRID_HEIGHT;

#endif // !GameConstants_H

