#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../graphicPrimitives.h"

#define MAX_POINTS 3
#define HEIGHT_LIMIT 500
#define WIDHT_LIMIT 500

enum MENU_TYPE{
        MENU_EXIT,
        MENU_CLEAN,
        MENU_FILL,
};

float points[MAX_POINTS][2];
int win;

void createPolygonMtr();

void setup(){
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   gluOrtho2D(0, 599, 0, 599);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);
  createPolygonMtr();
  glFlush();
}

void createPolygonMtr (){
  int idColor;
  for (int i = 0; i < MAX_POINTS; i++) {
    // coordenada x
    points[i][0] = round(rand()%WIDHT_LIMIT);
    // coordenada y
    points[i][1] = round(rand()%HEIGHT_LIMIT);
  }

  initMtr();
  for (int i = 1; i < MAX_POINTS; i++) {
    idColor = rand()%5+1;
    createLineMtr(points[i-1][0],points[i-1][1],points[i][0],points[i][1],idColor);
  }
  createLineMtr(points[0][0],points[0][1],points[MAX_POINTS-1][0],points[MAX_POINTS-1][1],idColor);

  printMtr();
}

void fillPolygon(){
  int idColor;
  int sum_x = 0, sum_y = 0;
  for (int i = 0; i < MAX_POINTS; i++) {
    sum_x += points[i][0];
    sum_y += points[i][1];
  }
  int med_x = sum_x/MAX_POINTS;
  int med_y = sum_y/MAX_POINTS;

  idColor = rand()%5+1;
  fill((int)med_x,(int)med_y,idColor);
  printMtr();
  glFlush();
}

void menu (int item_menu){
    switch (item_menu) {
      case MENU_EXIT:
        glutDestroyWindow(win);
        break;
      case MENU_CLEAN:
        glutPostRedisplay();
        break;
      case MENU_FILL:
        fillPolygon();
        break;
      default:
        printf("Invalid menu item:%d\n", item_menu);
    }
}

int main (int argc, char *argv[]){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutInitWindowSize(600,600);

   win = glutCreateWindow("Preenchimento de polígonos");

   glutCreateMenu(menu);
   glutAddMenuEntry("Preencher",MENU_FILL);
   glutAddMenuEntry("Refresh",MENU_CLEAN);
   glutAddMenuEntry("Sair",MENU_EXIT);
   glutAttachMenu(GLUT_RIGHT_BUTTON);

   setup();
   glutDisplayFunc(display);

   glutMainLoop();

   return 0;
}
