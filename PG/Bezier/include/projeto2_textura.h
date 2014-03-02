/*
-----------------------------------------------------------------------------
* Projeto 2 de Processamento Gráfico
* equipe: Ângelo Sant'ana, Pedro Lázaro
* 2013.2
*
-----------------------------------------------------------------------------
*/

#ifndef _OPENGL_TUTORIAL_H_
#define _OPENGL_TUTORIAL_H_

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <math.h>

#include <iostream>
#include <fstream>
#include <string>

#include <gl/glut.h>

using namespace std;

// Constantes do programa
#define PI 3.14159265
#define FPS			30	// Quantidade de atualizacoes por segundo do programa
#define ESC			27	// Valor da tecla ESC
#define IDLE		-2	// Nada a fazer
#define MODIFIED	-1	// A tela foi modificada

class Ponto {
public:
	double x, y, z;
};

class Vetor {
public:
	double x, y, z, modulo;
};

class Camera {
public: 
	Ponto pontoCamera;
	Vetor vetorN, vetorV;
	double distancia, hX, hY;

};

class Objeto {
public:
	int quantPontos, quantTriangulos;
	vector <Ponto> pontos;
	vector <Ponto> triangulos;
};

class Iluminacao {
public:
	Ponto pontoLuz;
	double reflexaoAmbiente, constDifusa, especular, rugosidade;
	Vetor corAmbiental, corFonteLuz, vetorDifuso;
};

double modulo (Vetor u);

vector <Vetor> ortogonalizar (Vetor v, Vetor u);

double produtoEscalar (Vetor v, Vetor u);

Vetor normalizarVetor (Vetor v);

Vetor produtoVetorial (Vetor a, Vetor b);

/**
* Funcao para inicializacao do programa.
*/
void myinit();

/**
* Esta funcao vai ser chamada quando a tela for redimensionada.
* @param w Largura atual da tela.
* @param h Altura atual da tela.
*/
void myreshape (GLsizei w, GLsizei h);

/**
* Esta é a funcao responsavel por pintar os objetos na tela.
*/
void mydisplay();

/**
* Esta funcao vai ser chamada toda vez que o mouse se mover com uma tecla apertada.
* Vai atualizar a posicao do quadrado que esta sendo movido.
* @param x Coordenada x atual do mouse.
* @param y Coordenada y atual do mouse.
*/
void handleMotion(int x, int y);

/**
* Esta funcao vai ser chamada toda vez que uma tecla do mouse seja clicada ou levantada.
* Com o botao direito do mouse, um quadrado pode ser criado na posicao atual do mouse, com uma cor e tamanho aleatorio.
* Com o botao esquerdo do mouse, um quadrado pode ser movimentado.
* @param btn Tecla levantada. Ex: GLUT_LEFT_BUTTON.
* @param state Estado da tecla. Ex: GLUT_DOWN.
* @param x Coordenada x atual do mouse.
* @param y Coordenada y atual do mouse.
*/
void handleMouse(int btn, int state, int x, int y);

/**
* Esta funcao vai ser chamada toda vez que uma tecla comum seja levantada.
* @param key Tecla levantada.
* @param x Coordenada x atual do mouse.
* @param y Coordenada y atual do mouse.
*/
void hadleKeyboard(unsigned char key, int x, int y);

/**
* Esta funcao vai ser chamada toda vez que uma tecla especial seja levantada.
* Botao F5 o programa volta ao estado inicial.
* @param key Tecla levantada. Ex: GLUT_KEY_F5.
* @param x Coordenada x atual do mouse.
* @param y Coordenada y atual do mouse.
*/
void hadleSpecialKeyboard(int key, int x, int y);

/**
* Representa uma maquina de estados do programa. Vai ser executada FPS vezes por segundo.
* @param id Identificador da maquina de estados.
*/
void loop(int id);

#endif //_OPENGL_TUTORIAL_H_
