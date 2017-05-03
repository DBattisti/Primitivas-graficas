#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../object3D.h"
#include "../graphicPrimitives.h"

#define ANGLE_SPEED 1
#define SCALE_SPEED 2
#define TRANS_SPEED 5

enum MENU_TYPE{
        MENU_EXIT,
        MENU_CLEAN,
        MENU_PRINT,
};

int win;
graphObject* orig;
graphObject* copy;

void setup(){
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   gluOrtho2D(0, 599, 0, 599);

   orig = newCube();
   scaleObject(orig,50);
}

void display()
{
  glColor3f(0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

  createLine(300.0,0.0,300.0,600.0,2);
  createLine(0.0,300.0,600.0,300.0,2);

  clearMtrDisplay();

  copy = copyObject(orig);
  moveCenter(copy,175);
  showLinesCube(copy);
  destroyObject(copy);

  printMtrDisplay();

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
      case MENU_PRINT:
        printObjectInfo(orig);
        break;
      default:
        printf("Invalid menu item:%d\n", item_menu);
    }
}

void transformations (unsigned char key,int x, int y){
  switch (key) {
    // Rotacionar
    case 'z':
      rotateX(orig,ANGLE_SPEED);
      break;
    case 'x':
      rotateY(orig,ANGLE_SPEED);
      break;
    case 'c':
      rotateZ(orig,ANGLE_SPEED);
      break;
    case 'a':
      rotateX(orig,-ANGLE_SPEED);
      break;
    case 's':
      rotateY(orig,-ANGLE_SPEED);
      break;
    case 'd':
      rotateZ(orig,-ANGLE_SPEED);
      break;
    // Escalonar
    case 'f':
      scaleX(orig,SCALE_SPEED);
      break;
    case 'g':
      scaleY(orig,SCALE_SPEED);
      break;
    case 'h':
      scaleZ(orig,SCALE_SPEED);
      break;
    case 'v':
      scaleX(orig,1/SCALE_SPEED);
      break;
    case 'b':
      scaleY(orig,1/SCALE_SPEED);
      break;
    case 'n':
      scaleZ(orig,1/SCALE_SPEED);
      break;
    // Transladar
    case '8':
      transY(orig,TRANS_SPEED);
      break;
    case '2':
      transY(orig,-TRANS_SPEED);
      break;
    case '4':
      transX(orig,-TRANS_SPEED);
      break;
    case '6':
      transX(orig,TRANS_SPEED);
      break;
    case '1':
      transZ(orig,TRANS_SPEED);
      break;
    case '3':
      transZ(orig,-TRANS_SPEED);
      break;

  }
  glutPostRedisplay();
}

int main (int argc, char *argv[]){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutInitWindowSize(600,600);

   win = glutCreateWindow("Criacao de objetos 3D");

   glutCreateMenu(menu);
   glutAddMenuEntry("Preencher",MENU_PRINT);
   glutAddMenuEntry("Refresh",MENU_CLEAN);
   glutAddMenuEntry("Sair",MENU_EXIT);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
   glutKeyboardFunc(transformations);
   setup();
   glutDisplayFunc(display);

   glutMainLoop();

   return 0;
}
