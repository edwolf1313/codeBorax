// Edward Hosea / c14170059
// Transformasi Bezier curve
// Grafika komputer - Universitas Kristen Petra
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <conio.h>
using namespace std;
vector<float> vf, vn;
vector <float> cx, cy;
int sizewin = 450,counter=0;
//class vec {
//private:
//	
//public:
//	
//	vec() {
//		
//	}/*
//	float get_vc() {
//		return ;
//	}*/
//};
void draw_line(){
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(vf[0],vf[1]);
	glVertex2f(vn[0], vn[1]);
	vf.clear();
	vf = vn;
	vn.clear();
	glEnd();
	glFlush();
}

void draw_pixel(float x, float y) {
	glBegin(GL_POINTS);
	glPointSize(3);
	glColor3f(1, 0, 0);
	glVertex2f(x,y);
	glEnd();
	glFlush();
}

int fact(int x) {
	int res = 1;
	for (int i = 2; i <= x; i++)
		res = res * i;
	return res;
}
void draw_bezier() {
	vector<float> tmp;
	int cons[500];
	for (int x = 0; x < 1; x++) {
		for (int y = 0; y < counter; y++) {
			//fac
			cons[y]=fact(counter-1)/(fact(y)*fact(counter-1-y));
			cout << cons[y];
		}
	}
	cout << endl;
	cout << cy.size() << endl;
	for (float x = 0; x <= 1;x+=0.0001) {
		float tmx = 0, tmy = 0;
		for (int y = 0; y < counter; y++) {
			tmx += cons[y] * pow((1 - x), counter - y - 1.0)*pow(x, y)*cx[y];
			tmy += cons[y] * pow((1 - x), counter - y - 1.0)*pow(x, y)*cy[y];
		}
		draw_pixel(tmx,tmy);
	}
}
void display() {
	glColor3f(0, 0, 0);
}
void keyboard(unsigned char key,int a,int b) {}
void mouse(int button,int stt,int x,int y) {

	if (button == GLUT_LEFT_BUTTON && stt == GLUT_UP)
	{
		float coor_x=x, coor_y=y;
		coor_x = (coor_x - (sizewin / 2))/(sizewin/2);
		coor_y = -1 * (coor_y - (sizewin / 2))/(sizewin/2);
		cout << coor_x << "," << coor_y << endl;
		draw_pixel(coor_x,coor_y);
		cx.push_back(coor_x);
		cy.push_back(coor_y);
		counter++;
		if (vf.size() > 0) {
			vn.push_back(coor_x);
			vn.push_back(coor_y);
			draw_line();
			draw_bezier();
		}
		else {
			vf.push_back(coor_x);
			vf.push_back(coor_y);
		}
	}
}
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glPointSize(3.0);
	glLoadIdentity();
	/*gluOrtho2D(0.0, 64.0, 0.0, 48.0);*/
}
int main(int argc, char** argv) {
	/*srand(time(NULL));*/
	glutInit(&argc, argv);          // Initialize GLUT
	/*glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);*/
	glutInitWindowSize(sizewin, sizewin);   // Set the window's initial width & height
	glutCreateWindow("Grafkom");  // Create window with the given title
	glutInitWindowPosition(320, 320); // Position the window's initial top-left corner
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	glutIdleFunc(display);
	/*glutSpecialFunc(keyboard_line);*/
	glutMouseFunc(mouse);//manggil function mouse
	glutKeyboardUpFunc(keyboard);
	initGL();                       // Our own OpenGL initialization
	glutMainLoop();                 // Enter the event-processing loop
	return 0;
}