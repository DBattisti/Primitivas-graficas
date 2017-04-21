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
};

int win;

void createPolygon();

void setup(){
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   gluOrtho2D(0, 599, 0, 799);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);
  createPolygon();
  glFlush();
}

void createPolygon (){
  float points[MAX_POINTS][2];
  int x_size, y_size;

  for (int i = 0; i < MAX_POINTS; i++) {
    // coordenada x
    points[i][0] = round(rand()%WIDHT_LIMIT);
    // coordenada y
    points[i][1] = round(rand()%HEIGHT_LIMIT);
  }

  for (int i = 1; i < MAX_POINTS; i++) {
    createLine(points[i-1][0],points[i-1][1],points[i][0],points[i][1]);
  }
  createLine(points[0][0],points[0][1],points[MAX_POINTS-1][0],points[MAX_POINTS-1][1]);
}

void menu (int item_menu){
    switch (item_menu) {
      case MENU_EXIT:
        glutDestroyWindow(win);
        break;
      case MENU_CLEAN:
        glutPostRedisplay();
        break;
      default:
        printf("Invalid menu item:%d\n", item_menu);
    }
}

int main (int argc, char *argv[]){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutInitWindowSize(800,600);

   win = glutCreateWindow("Rasterizacao de retas e circunferencias");

   glutCreateMenu(menu);
   glutAddMenuEntry("Refresh",MENU_CLEAN);
   glutAddMenuEntry("Sair",MENU_EXIT);
   glutAttachMenu(GLUT_RIGHT_BUTTON);

   setup();
   glutDisplayFunc(display);

   glutMainLoop();

   return 0;
}
