#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../object3D.h"
#include "../graphicPrimitives.h"

enum MENU_TYPE{
        MENU_EXIT,
        MENU_CLEAN,
        MENU_FILL,
};

int win;

void setup(){
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   gluOrtho2D(0, 599, 0, 599);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);
  createLine(300.0,0.0,300.0,600.0,2);
  createLine(0.0,300.0,600.0,300.0,2);
  createCube();
  glFlush();
}

void createCube (){
  graphObject* orig = newCube();
  // graphObject* copy = copyObject(orig);
  graphObject* copy2 = copyObject(orig);

  // moveCenter(copy,200);
  // showLinesCube(copy);

  scaleObject(copy2,50);
  moveCenter(copy2,175);
  showLinesCube(copy2);

  printMtr();
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
        break;
      default:
        printf("Invalid menu item:%d\n", item_menu);
    }
}

int main (int argc, char *argv[]){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutInitWindowSize(600,600);

   win = glutCreateWindow("Criacao de objetos 3D");

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
