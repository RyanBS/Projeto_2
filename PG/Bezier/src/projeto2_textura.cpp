/*
-----------------------------------------------------------------------------
* Projeto 2 de Processamento Gráfico
* equipe: Ângelo Sant'ana, Pedro Lázaro
* 2013.2
*
-----------------------------------------------------------------------------
*/


#include "projeto2_textura.h"

int qtdQuadrados;
int estado;
GLfloat mouse_x, mouse_y;
GLfloat window_width = 800.0;
GLfloat window_height = 600.0;
Camera camera;
Objeto objeto;
Iluminacao iluminacao;

double modulo (Vetor u) {
	u.modulo = sqrt( pow((u.x), 2) + pow((u.y), 2) + pow((u.z), 2) );

	return u.modulo;
}

Vetor normalizarVetor (Vetor v) {
	double tam = modulo(v);

	v.x = v.x/tam;
	v.y = v.y/tam;
	v.z = v.z/tam;

	return v;
}

Vetor produtoVetorial (Vetor a, Vetor b) {
	Vetor result;

	result.x = a.y*b.z - a.z*b.y;
	result.y = a.z*b.x - a.x*b.z;
	result.z = a.x*b.y - a.y*b.x;

	return result;
}

double produtoEscalar (Vetor v, Vetor u) {
	return ((v.x*u.x) + (v.y*u.y) + (v.z*u.z));
}

vector <Vetor> ortogonalizar (Vetor v, Vetor u) {
	vector <Vetor> ortogonais;
	double temp = (produtoEscalar(v,u)/produtoEscalar(v,v));

	u.x = u.x - (temp)*v.x;
	u.y = u.y - (temp)*v.y;
	u.z = u.z - (temp)*v.z;

	ortogonais.push_back(v);
	ortogonais.push_back(u);

	return ortogonais;
}

void myinit()
{
	srand(time(NULL));
	qtdQuadrados = 0;
	estado = MODIFIED;

	//Imagem projetada no near plane sera desenhada na seguinte area da tela: (0,0,width,height)
	glViewport(0, 0, window_width, window_height);

	//Setando tipo de projecao..
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	// qual a necessidade de substituir a matriz pela identidade?!

	//Projecao sera ortogonal
	glOrtho(0, window_width, window_height, 0, 0, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	loop(0);	// a máquina que roda o código
}

// Nao preciso mexer nessa funcao
void myreshape (GLsizei w, GLsizei h)
{

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	window_width = (GLfloat) w;
	window_height = (GLfloat) h;
	glOrtho(0, window_width, window_height, 0, 0, 5.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mydisplay()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	for(int i = 0; i < qtdQuadrados; i++){
		/*glColor3f(quad[i].r, quad[i].g, quad[i].b);
		glBegin(GL_QUADS);
			glVertex2f(quad[i].x, quad[i].y);	// vai criar um vértice
			glVertex2f(quad[i].x+quad[i].lado, quad[i].y);
			glVertex2f(quad[i].x+quad[i].lado, quad[i].y+quad[i].lado);
			glVertex2f(quad[i].x, quad[i].y+quad[i].lado);
		glEnd(); */
	}
	
	glFlush();
}

void handleMotion(int x, int y)
{
	mouse_x = x;
	mouse_y = y;
	if((estado != MODIFIED) && (estado != IDLE)){

		printf("[Mover quad] pos = mouse(%0.2f,%0.2f)\n",mouse_x,mouse_y);
		/*
		quad[estado].x = mouse_x - quad[estado].lado/2;
		quad[estado].y = mouse_y - quad[estado].lado/2; */
	}
}

void handleMouse(int btn, int state, int x, int y)
{
	if (estado == IDLE && btn == GLUT_LEFT_BUTTON){
		mouse_x = x;
		mouse_y = y;
		if (state == GLUT_DOWN){
			for(int i = qtdQuadrados-1; i >= 0; i--){
		/*		if((mouse_x >= quad[i].x) && (mouse_x <= (quad[i].x+quad[i].lado)) && (mouse_y >= quad[i].y) && (mouse_y <= (quad[i].y+quad[i].lado))){

					estado = i;
					break;
				} */
			}
		}
	}
	else if(btn == GLUT_LEFT_BUTTON && state == GLUT_UP){
		estado = MODIFIED;
	}
	else if(estado == IDLE && btn == GLUT_RIGHT_BUTTON){		// modificar essa parte para definir o tamanho dos triangulos
		if (state == GLUT_DOWN){

			//Posicao do quadrado
			GLfloat x2 = x;
			GLfloat y2 = y;

			//Tamanho do lado aleatorio
			GLfloat lado = (((GLfloat)(rand()%200)))+10;
			//Cor
			GLfloat r = ((GLfloat)(rand()%256))/255.0;
			GLfloat g = ((GLfloat)(rand()%256))/255.0;
			GLfloat b = ((GLfloat)(rand()%256))/255.0;

			printf("[Add quad] posicao = mouse(%d,%d), lado = %0.2f, cor = rgb(%0.2f,%0.2f,%0.2f)\n",x,y, lado,r,g,b);
			estado = MODIFIED;
		}
	}
}

void hadleKeyboard(unsigned char key, int x, int y)
{
	if(key == ESC){
		exit(0);
	}
}

string pathCamera, pathIluminacao, pathObjeto, pathTextura;

void lerCamera (string endereco) {
	ifstream arquivo (endereco);

	if (arquivo.is_open()) {
		arquivo >> camera.pontoCamera.x;
		arquivo >> camera.pontoCamera.y;
		arquivo >> camera.pontoCamera.z;

		arquivo >> camera.vetorN.x;
		arquivo >> camera.vetorN.y;
		arquivo >> camera.vetorN.z;

		arquivo >> camera.vetorV.x;
		arquivo >> camera.vetorV.y;
		arquivo >> camera.vetorV.z;

		arquivo >> camera.distancia;
		arquivo >> camera.hX;
		arquivo >> camera.hY;
	} else
		printf("Documento nao abriu.\n");
}

void lerObjeto (string endereco) {
	ifstream arquivo (endereco);
	Ponto p;

	if (arquivo.is_open()) {
		arquivo >> objeto.quantPontos;
		arquivo >> objeto.quantTriangulos;

		for (int i=0; i++<objeto.quantPontos;) {
			arquivo >> p.x;
			arquivo >> p.y;
			arquivo >> p.z;

			objeto.pontos.push_back(p);
		}

		for (int i=0; i++<objeto.quantTriangulos;) {
			arquivo >> p.x;
			arquivo >> p.y;
			arquivo >> p.z;

			objeto.triangulos.push_back(p);
		}

	} else
		printf ("Arquivo nao abriu!");
}

void lerIluminacao (string endereco) {
	ifstream arquivo(endereco);

	if (arquivo.is_open()) {
		arquivo >> iluminacao.pontoLuz.x;
		arquivo >> iluminacao.pontoLuz.y;
		arquivo >> iluminacao.pontoLuz.z;

		arquivo >> iluminacao.reflexaoAmbiente;

		arquivo >> iluminacao.corAmbiental.x;
		arquivo >> iluminacao.corAmbiental.y;
		arquivo >> iluminacao.corAmbiental.z;

		arquivo >> iluminacao.constDifusa;

		arquivo >> iluminacao.vetorDifuso.x;
		arquivo >> iluminacao.vetorDifuso.y;
		arquivo >> iluminacao.vetorDifuso.z;

		arquivo >> iluminacao.especular;

		arquivo >> iluminacao.corFonteLuz.x;
		arquivo >> iluminacao.corFonteLuz.y;
		arquivo >> iluminacao.corFonteLuz.z;

		arquivo >> iluminacao.rugosidade;
	} else
		printf("O arquivo nao abriu!");
}

void hadleSpecialKeyboard(int key, int x, int y)
{
	if(key == GLUT_KEY_F5){
		myinit();
	}
}

void loop(int id)
{
	if(estado == MODIFIED){
		mydisplay();
		estado = IDLE;
	}
	else if(estado != IDLE){
		mydisplay();
	}
	glutTimerFunc(1000/FPS, loop, id);
}

int main(int argc, char **argv)
{
	pathObjeto = "C:/Users/ivonei/Angelo/UFPE/PG 2013.2/Projeto 2 - Textura/objeto.byu";
	pathCamera = "C:/Users/ivonei/Angelo/UFPE/PG 2013.2/Projeto 2 - Textura/camera.cfg";
	pathIluminacao = "C:/Users/ivonei/Angelo/UFPE/PG 2013.2/Projeto 2 - Textura/iluminacao.txt";
	pathTextura = "C:/Users/ivonei/Angelo/UFPE/PG 2013.2/Projeto 2 - Textura/textura.jpg";

	lerCamera(pathCamera);
	lerObjeto(pathObjeto);
	
	printf("%f %f %f %f %f %f %f %f %f %f %f %f\n\n", camera.pontoCamera.x, camera.pontoCamera.y,
		camera.pontoCamera.z, camera.vetorN.x, camera.vetorN.y, camera.vetorN.z, camera.vetorV.x,
		camera.vetorV.y, camera.vetorV.z, camera.distancia, camera.hX, camera.hY);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(0,100);
	glutCreateWindow("PG - OpenGL Template");
	
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(myreshape);
	glutMouseFunc(handleMouse);
	glutMotionFunc(handleMotion);
	glutKeyboardUpFunc(hadleKeyboard);
	glutSpecialUpFunc(hadleSpecialKeyboard);

	myinit();

	glutMainLoop();
	return 0;
}
