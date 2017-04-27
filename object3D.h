typedef struct graph {
	int **points; //Coordenadas x, y, z de cada ponto
	int **lines; //Indice do primeiro e ultimo ponto da linha
	int cent[3]; // Coordenadas x, y e z para projecao no sist de referencia do universo
	int ang[3]; //Angulos de rotacao nas coordenadas x, y e z
	int scale[3]; //Escala do objeto, x, y e z
	int p, l; //qnt de pontos e linhas
}graphObject;

graphObject* newObject(int n_points, int m_lines);

void printMtrObject (int linha, int coluna, int** mtr);

graphObject* newCube ();

void printObjectInfo (graphObject* obj);

//O objeto deve estar na origem para poder escalar o tamanho dele
graphObject* scaleObject(graphObject* obj, int scale);

//O objeto deve estar na origem para poder escalar o tamanho dele
graphObject* moveCenter(graphObject* obj, int center);

void showLinesCube (graphObject* cube);
