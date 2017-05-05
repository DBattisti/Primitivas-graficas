typedef struct  {
	float **points; //Coordenadas x, y, z de cada ponto
	int **lines; //Indice do primeiro e ultimo ponto da linha
	int* trans; // Coordenadas x, y e z para projecao no sist de referencia do universo
	int* ang; //Angulos de rotacao nas coordenadas x, y e z
	float* scale; //Escala do objeto, x, y e z
	int p, l; //qnt de pontos e linhas
}graphObject;

graphObject* newObject(int n_points, int m_lines);

void destroyObject(graphObject* obj);

void printMtr (int linha, int coluna, int** mtr);

void printMtrFloat (int linha, int coluna, float** mtr);

void printArray (int size, int array[size]);

void printArrayFloat (int size, float array[size]);

graphObject* newCube ();

void printObjectInfo (graphObject* obj);

graphObject* copyObject (graphObject* orig);

//O objeto deve estar na origem para poder escalar o tamanho dele
graphObject* scaleObject(graphObject* obj, int scale);

//O objeto deve estar na origem para poder escalar o tamanho dele
graphObject* moveCenter(graphObject* obj, int center);

void matrixMult (graphObject* obj, float mtr[][3]);

void matrixSum (graphObject* obj, int mtr[3]);

void rotateX(graphObject* obj, int angle);

void rotateY(graphObject* obj, int angle);

void rotateZ(graphObject* obj, int angle);

void scaleX(graphObject* obj, double scale);

void scaleY(graphObject* obj, double scale);

void scaleZ(graphObject* obj, double scale);

void transX(graphObject* obj, int trans);

void transY(graphObject* obj, int trans);

void transZ(graphObject* obj, int trans);

void showLinesCube (graphObject* cube);
