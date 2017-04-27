#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphicPrimitives.h"

#define NUM_COL_P 3
#define NUM_COL_L 2

typedef struct graph {
	int **points; //Coordenadas x, y, z de cada ponto
	int **lines; //Indice do primeiro e ultimo ponto da linha
	int cent[3]; // Coordenadas x, y e z para projecao no sist de referencia do universo
	int ang[3]; //Angulos de rotacao nas coordenadas x, y e z
	int scale[3]; //Escala do objeto, x, y e z
	int p, l; //qnt de pontos e linhas
}graphObject;

graphObject* newObject(int n_points, int m_lines){
  graphObject* obj = malloc(sizeof(graphObject));
	obj->p = n_points;
	obj->l = m_lines;

	// Tabela de pontos
	obj->points = (int**) malloc(sizeof(int*)*n_points);
	for (size_t i = 0; i < n_points; i++) {
			obj->points[i] = (int*) malloc(sizeof(int)*NUM_COL_P);
	}
	//Tabela de linhas
	obj->lines = (int**) malloc(sizeof(int*)*m_lines);
	for (size_t i = 0; i < m_lines; i++) {
		 obj->lines[i] = (int*) malloc(sizeof(int)*NUM_COL_L);
	}

	return obj;
}

void printMtrObject (int linha, int coluna, int** mtr){
	printf("\t");
	for (size_t i = 0; i < coluna; i++) {
		printf("[%d]\t",i);
	}
	printf("\n");
	for (size_t j = 0; j < linha; j++) {
		printf("[%d]\t",j);
		for (size_t i = 0; i < coluna; i++) {
			printf(" %d\t",mtr[j][i]);
		}
		printf("\n");
	}
}

graphObject* newCube (){
	graphObject* cube = newObject(8,12);

	cube->points[0][0] =  1; cube->points[0][1] =  1; cube->points[0][2] =  1;//p3
	cube->points[1][0] =  1; cube->points[1][1] =  1; cube->points[1][2] = -1;//p6
	cube->points[2][0] =  1; cube->points[2][1] = -1; cube->points[2][2] =  1;//p2
	cube->points[3][0] =  1; cube->points[3][1] = -1; cube->points[3][2] = -1;//p7
	cube->points[4][0] = -1; cube->points[4][1] =  1; cube->points[4][2] =  1;//p4
	cube->points[5][0] = -1; cube->points[5][1] =  1; cube->points[5][2] = -1;//p5
	cube->points[6][0] = -1; cube->points[6][1] = -1; cube->points[6][2] =  1;//p1
	cube->points[7][0] = -1; cube->points[7][1] = -1; cube->points[7][2] = -1;//p8

	//face frente
	cube->lines [0][0] = 6; cube->lines [0][1] = 2;
	cube->lines [1][0] = 2; cube->lines [1][1] = 0;
	cube->lines [2][0] = 0; cube->lines [2][1] = 4;
	cube->lines [3][0] = 4; cube->lines [3][1] = 6;
	//face tras
	cube->lines [4][0] = 5; cube->lines [4][1] = 1;
	cube->lines [5][0] = 1; cube->lines [5][1] = 3;
	cube->lines [6][0] = 3; cube->lines [6][1] = 7;
	cube->lines [7][0] = 7; cube->lines [7][1] = 5;
	//interligações
	cube->lines [8][0] = 4; cube->lines [8][1] = 5;
	cube->lines [9][0] = 0; cube->lines [9][1] = 1;
	cube->lines[10][0] = 2; cube->lines[10][1] = 3;
	cube->lines[11][0] = 6; cube->lines[11][1] = 7;

	return cube;
}

void printObjectInfo (graphObject* obj){
	printf("\n##########################\n");
	printf("Quantidade de pontos: %d\n",obj->p);
	printf("Quantidade de linhas: %d\n",obj->l);
	printf("Matriz de pontos:\n");
	printMtrObject(obj->p,NUM_COL_P,obj->points);
	printf("Matriz de linhas:\n");
	printMtrObject(obj->l,NUM_COL_L,obj->lines);
	}

graphObject* copyObject (graphObject* orig){
	graphObject* copy = newObject(orig->p,orig->l);
	for (size_t j = 0; j < copy->p; j++) {
		for (size_t i = 0; i < NUM_COL_P; i++) {
			copy->points[j][i] = orig->points[j][i];
		}
	}
	for (size_t j = 0; j < copy->l; j++) {
		for (size_t i = 0; i < NUM_COL_L; i++) {
			copy->lines[j][i] = orig->lines[j][i];
		}
	}
	return copy;
}

//O objeto deve estar na origem para poder escalar o tamanho dele
graphObject* scaleObject(graphObject* obj, int scale){
	for (size_t i = 0; i < obj->p; i++) {
		for (size_t j = 0; j < NUM_COL_P; j++) {
			obj->points[i][j] *= scale;
		}
	}
	return obj;
}

//O objeto deve estar na origem para poder escalar o tamanho dele
graphObject* moveCenter(graphObject* obj, int center){
	for (size_t i = 0; i < obj->p; i++) {
		for (size_t j = 0; j < NUM_COL_P; j++) {
			obj->points[i][j] += center;
		}
	}
	return obj;
}

void showLinesCube (graphObject* cube){
	int xi, yi, zi, xj, yj, zj;
	float x1, y1, x2, y2;
	float alfa = 0.7071;
	int idColor = 1;
	for (size_t j = 0; j < cube->l; j++) {
		xi = cube->points[ cube->lines[j][0] ][0];
		yi = cube->points[ cube->lines[j][0] ][1];
		zi = cube->points[ cube->lines[j][0] ][2];
		xj = cube->points[ cube->lines[j][1] ][0];
		yj = cube->points[ cube->lines[j][1] ][1];
		zj = cube->points[ cube->lines[j][1] ][2];
		x1 = xi + alfa*zi;
		x2 = xj + alfa*zj;
		y1 = yi + alfa*zi;
		y2 = yj + alfa*zj;
		createLineMtr(x1,y1,x2,y2,idColor);
	}
}
