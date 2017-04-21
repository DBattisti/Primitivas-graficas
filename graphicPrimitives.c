#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WINDOW_WIDHT 500
#define WINDOW_HEIGHT 500
#define CONT_COLOR 5

int interative = 1; //0 = false 1 = true

float COLORS [CONT_COLOR][3] = {0.3f, 0.4f, 1.0f,
																0.0f, 1.0f, 0.4f,
																1.0f, 0.3f, 0.4f,
																0.3f, 1.0f, 1.0f,
																1.0f, 0.4f, 1.0f};
int MTR[WINDOW_HEIGHT][WINDOW_WIDHT];

void initMtr (){
	for (int i = 0; i < WINDOW_HEIGHT; i++) {
		for (int j = 0; j < WINDOW_WIDHT; j++) {
			MTR[i][j] = 0;
		}
	}
}

void putPixel (float x, float y, int idColor){
	glPointSize(1);
	glBegin(GL_POINTS);
	if (idColor <= CONT_COLOR && idColor > 0)
		glColor3f(COLORS[idColor-1][0],COLORS[idColor-1][1],COLORS[idColor-1][2]);
	glVertex2f(x, y);
	glEnd();
}

void putPixelMtr (int x, int y, int idColor){
	MTR[x][y] = idColor;
}

void createLine(float x1, float y1, float x2, float y2, int idColor){
  float x, y;
  float dx = x2-x1, dy = y2-y1;
  float m = (float) dy / dx;
  float b = y1 - (m * x1);
  float xmax = fmax(x1,x2), ymax = fmax(y1,y2);
  float xmin = fmin(x1,x2), ymin = fmin(y1,y2);

  if (dx == 0){
    x = x1;
    for (y=ymin;y<ymax;y++){
      putPixel(x,y,idColor);
    }
  }
  if (dy == 0){
    y = y1;
    for(x=xmin;x<xmax;x++){
      putPixel(x,y,idColor);
    }
  }

  if ( abs(dx) >= abs(dy) ){
    for(x=xmin;x<xmax;x++){
      y = m * x + b;
      putPixel(x,y,idColor);
    }
  }
  else {
    for(y=ymin;y<ymax;y++){
      x = (y - b) / m;
      putPixel(x,y,idColor);
    }
  }
}

void createLineMtr(float x1, float y1, float x2, float y2, int idColor){
  float x = 0, y = 0;
  float dx = x2-x1, dy = y2-y1;
	float xmax = fmax(x1,x2), ymax = fmax(y1,y2);
  float xmin = fmin(x1,x2), ymin = fmin(y1,y2);

	if (dx == 0){
    x = x1;
    for (y=ymin;y<ymax;y++){
      putPixelMtr(x,y,idColor);
    }
		return;
  }
  if (dy == 0){
    y = y1;
    for(x=xmin;x<xmax;x++){
      putPixelMtr(x,y,idColor);
    }
		return;
  }

	float m = (float) dy / dx;
  float b = y1 - (m * x1);

  if ( abs(dx) >= abs(dy) ){
    for(x=xmin;x<xmax;x++){
      y = m * x + b;
      putPixelMtr(x,y,idColor);
    }
		return;
  }
  else if (abs(dx) < abs(dy)){
    for(y=ymin;y<ymax;y++){
      x = (y - b) / m;
      putPixelMtr(x,y,idColor);
    }
		return;
  }
	else{
		return;
	}
}

void printMtr (){
	int idColor;
	for (int i = 0; i < WINDOW_HEIGHT; i++) {
		for (int j = 0; j < WINDOW_WIDHT; j++) {
			if (MTR[i][j] != 0){
				idColor = MTR[i][j];
				putPixel(i,j,idColor);
			}
		}
	}
}

void delay (){
	for (int i = 0; i < 10000000; i++) {
		/* code */
	}
}

void fill (int xc, int yc, int idColor){

	MTR[xc][yc] = idColor;

	if (interative){
		printMtr();
		glFlush();
		// delay();
	}

	if (MTR[xc][yc+1] == 0){
		fill(xc,yc+1,idColor);
	}
	if (MTR[xc+1][yc] == 0){
		fill(xc+1,yc,idColor);
	}
	if (MTR[xc-1][yc] == 0){
		fill(xc-1,yc,idColor);
	}
	if (MTR[xc][yc-1] == 0){
		fill(xc,yc-1,idColor);
	}
	if (MTR[xc+1][yc+1] == 0){
		if (MTR[xc+1] == 0 || MTR[yc+1] == 0){
			fill(xc+1,yc+1,idColor);
		}
	}
	if (MTR[xc-1][yc-1] == 0){
		if (MTR[xc-1] == 0 || MTR[yc-1] == 0){
			fill(xc-1,yc-1,idColor);
		}
	}
	if (MTR[xc-1][yc+1] == 0){
		if (MTR[xc-1] == 0 || MTR[yc+1] == 0){
			fill(xc-1,yc+1,idColor);
		}
	}
	if (MTR[xc+1][yc-1] == 0){
		if (MTR[xc+1] == 0 || MTR[yc-1] == 0){
			fill(xc+1,yc-1,idColor);
		}
	}
	return;
}
