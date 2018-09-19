#include <cstdlib>

#include "igvInterfaz.h"

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
                             // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz() {
	ejes = true;
	num_triangulos = 100
}

igvInterfaz::~igvInterfaz () {}


// Metodos publicos ----------------------------------------

void igvInterfaz::configura_entorno(int argc, char** argv,
			                              int _ancho_ventana, int _alto_ventana,
			                              int _pos_X, int _pos_Y,
													          string _titulo){
	// inicialización de las variables de la interfaz																	
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	// inicialización de la ventana de visualización
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(_ancho_ventana,_alto_ventana);
	glutInitWindowPosition(_pos_X,_pos_Y);
	glutCreateWindow(_titulo.c_str());

	glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
	glClearColor(1.0,1.0,1.0,0.0); // establece el color de fondo de la ventana

}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

float igvInterfaz::rads(float grados)
{
	float rad = 0;
	rad = (grados * 3.14)/ 180;
	return rad;
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
		case 27: // tecla de escape para SALIR
			exit(1);
		break;
		case 101:
			if (interfaz.get_ejes() == true) {
				interfaz.set_ejes(false);
			}
			else {
				interfaz.set_ejes(true);
			}
		break;
	}
	
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
  // dimensiona el viewport al nuevo ancho y alto de la ventana
  glViewport(0,0,(GLsizei) w,(GLsizei) h);

  // guardamos valores nuevos de la ventana de visualizacion
  interfaz.set_ancho_ventana(w);
  interfaz.set_alto_ventana(h);

  // establece el tipo de proyeccion a utilizar
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-1,1,-1,1,-1,200);

  // se define la camara de vision
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(1.5,1.0,2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void igvInterfaz::set_glutDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer
	glPushMatrix(); // guarda la matriz de modelado

	// Apartado A: pintar los ejes
	if (interfaz.get_ejes() == true) {
		glBegin(GL_LINES);
			glColor3f(1, 0, 0);
			glVertex3f(-2, 0, 0);
			glVertex3f(2, 0, 0);

			glColor3f(0, 1, 0);
			glVertex3f(0, -2, 0);
			glVertex3f(0, 2, 0);

			glColor3f(0, 0, 1);
			glVertex3f(0, 0, -2);
			glVertex3f(0, 0, 2);
		glEnd();
	}

	// Apartado B: visualizar primitiva cubo en modo alambre
	glColor3f(0, 0, 0);
	glutWireCube(1);

	// apartado D: cubo hecho con líneas
	glBegin(GL_LINES);
		glColor3f(1, 1, 0);

		// Cuadrado de abajo
		glVertex3f(0.375, -0.375, 0.375);
		glVertex3f(-0.375, -0.375, 0.375);

		glVertex3f(-0.375, -0.375, -0.375);
		glVertex3f(-0.375, -0.375, 0.375);

		glVertex3f(0.375, -0.375, 0.375);
		glVertex3f(0.375, -0.375, -0.375);

		glVertex3f(-0.375, -0.375, -0.375);
		glVertex3f(0.375, -0.375, -0.375);

		// Cuadrado de arriba
		glVertex3f(0.375, 0.375, 0.375);
		glVertex3f(-0.375, 0.375, 0.375);

		glVertex3f(-0.375, 0.375, -0.375);
		glVertex3f(-0.375, 0.375, 0.375);

		glVertex3f(0.375, 0.375, 0.375);
		glVertex3f(0.375, 0.375, -0.375);

		glVertex3f(-0.375, 0.375, -0.375);
		glVertex3f(0.375, 0.375, -0.375);

		// Lineas rectas hacia abajo para unir los dos cuadrados
		glVertex3f(0.375, 0.375, -0.375);
		glVertex3f(0.375, -0.375, -0.375);

		glVertex3f(0.375, 0.375, 0.375);
		glVertex3f(0.375, -0.375, 0.375);

		glVertex3f(-0.375, 0.375, 0.375);
		glVertex3f(-0.375, -0.375, 0.375);

		glVertex3f(-0.375, 0.375, -0.375);
		glVertex3f(-0.375, -0.375, -0.375);
	glEnd();

	// apartado E: cubo hecho con triángulos
	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 1);
		glVertex3f(0.25, -0.25, 0.25);
		glVertex3f(-0.25, -0.25, 0.25);
		glVertex3f(0.25, 0.25, 0.25);

		glColor3f(1, 0, 0);
		glVertex3f(-0.25, 0.25, 0.25);
		glVertex3f(-0.25, -0.25, 0.25);
		glVertex3f(0.25, 0.25, 0.25);

		glColor3f(0, 1, 0);
		glVertex3f(0.25, -0.25, 0.25);
		glVertex3f(0.25, 0.25, -0.25);
		glVertex3f(0.25, 0.25, 0.25);

		glColor3f(1, 1, 0);
		glVertex3f(0.25, -0.25, 0.25);
		glVertex3f(0.25, 0.25, -0.25);
		glVertex3f(0.25, -0.25, -0.25);

		glColor3f(1, 0, 1);
		glVertex3f(-0.25, 0.25, 0.25);
		glVertex3f(0.25, 0.25, -0.25);
		glVertex3f(0.25, 0.25, 0.25);

		glColor3f(0, 0, 1);
		glVertex3f(-0.25, 0.25, 0.25);
		glVertex3f(0.25, 0.25, -0.25);
		glVertex3f(-0.25, 0.25, -0.25);
	glEnd();

	// apartado F: círculo hecho con triángulos
	float grados = interfaz.rads(360) / interfaz.get_num_triangulos(); // Grados de cada triángulo.
	float grado = 0; // Grado que se suma

	glBegin(GL_TRIANGLES);
	for (float i = 0; i < interfaz.get_num_triangulos(); i++) {
		glColor3f((i / interfaz.get_num_triangulos()), (i / interfaz.get_num_triangulos()), (i / interfaz.get_num_triangulos()));
		glVertex3f(0, 0, 0.5);
		glVertex3f(0.5*cos(grado), 0.5*sin(grado), 0.5);
		grado += grados;
		//printf("Para %f: ", i);
		//printf("%f\n", grado);
		glVertex3f(0.5*cos(grado), 0.5*sin(grado), 0.5);
	}
	glEnd();

	glPopMatrix (); // restaura la matriz de modelado
	glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
}
