#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <fstream>



vector<tuple<float, float, float>> leArquivo(string nomeArquivo){

    string linhaString;
	//float numero;
	ifstream myArq;
	vector<double> saida;

	myArq.open(nomeArquivo, ios::in);


	if(myArq.is_open()){

		while(!myArq.eof()){

			getline(myArq, linhaString);
			if(!linhaString.empty()){
				//numero = stof(linhaString, NULL);
				numero = stod(linhaString, NULL);
				saida.push_back(numero);
			}
		}
		myArq.close();
	}
	return saida;
}



/*
Reader obj;

float angle;

void init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Generic RPG 3D");

    //AllocConsole();
    freopen( "CON", "wt", stdout );
    freopen( "CON", "wt", stderr );

    obj.load("trabCGR.obj");

    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
}

void display(void)
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, -2.75f, -5.0f);
    obj.draw("trabCGR.obj");

    glutSwapBuffers();
    angle += .1f;
}


void reshape( int width, int height )
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
*/
int main(int argc, char **argv)
{

/*
    init(argc, argv);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutMainLoop();
*/
    return 0;
}
