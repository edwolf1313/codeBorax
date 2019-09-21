// Edward Hosea / c14170059
// Transformasi garis dan segitiga, object 3D
// Grafika komputer - Universitas Kristen Petra
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <string>
//#include <time.h>
#
using namespace std;
//vector<double> v1, v2, v3;
vector<vector<float>> v, vn, vt, ft, fn, fv;
//float vek[10][10];
int sizewin = 900, pi = 3.14159265359;
int ct;
class vectors {
public:

	vectors() {}
	void init_coordinat(vector<vector<float>>&v, float x, float y, float z) {
		vector<float> tmp;
		tmp.push_back(x);
		tmp.push_back(y);
		tmp.push_back(z);
		v.push_back(tmp); //v1[0..n][x..y..z]
	}
	void init_line() {
		v.clear();
		glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);//putih
		init_coordinat(v, 0.5, 0.0, 0);
		init_coordinat(v, -0.5, 0.0, 0);
		for (int w = 0; w < v.size(); w++) {
			glVertex3f(v[w][0], v[w][1], v[w][2]);
		}

		glEnd();
		glutSwapBuffers();
	}
	void init_rectangle() {
		v.clear();
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);//putih
		init_coordinat(v, 0.0, 0.5, 0);
		init_coordinat(v, 0.5, -0.5, 0);
		init_coordinat(v, -0.5, -0.5, 0);
		for (int w = 0; w < v.size(); w++) {
			glVertex3f(v[w][0], v[w][1], v[w][2]);
		}
		
		glEnd();
		glutSwapBuffers();
	}

	void init_object() {
		v.clear();
		load_object();
		draw_object();
	}
	void split(string n, vector<float>&res_x, vector<float>&res_y, vector<float>&res_z) {
		string result;
		istringstream rlt(n);
		vector<float>res;
		while (getline(rlt, result, '/')) {
			if (result == "") {
				/*res.push_back(stof(result) - 1);*/
			}
			else {
				res.push_back(stof(result) - 1);
			}
		}
		res_x.push_back(res[0]);
		res_y.push_back(res[1]);
		res_z.push_back(res[2]);
	}
	void load_object() { // load cat.obj
		string ecline;
		ifstream load_obj("cat.obj", ios::out);
		/*cout << load_obj.tellg();*/
		//	
		while (!load_obj.eof()) {
			vector<float> tmp_v;
			string x, y, z, h;
			getline(load_obj, ecline);
			if (ecline[0] == 'v' && ecline[1] == ' ')
			{
				istringstream tmlin(ecline); // istringstream getline pada string 
											 // untuk baris yang sama
				tmlin >> h >> x >> y >> z;
				/*cout << x << ";" << y << ";" << z << endl;*/
				tmp_v.push_back(stof(x)); //konversi float 
				tmp_v.push_back(stof(y));
				tmp_v.push_back(stof(z));
				v.push_back(tmp_v);
			}
			else if (ecline[0] == 'v' && ecline[1] == 't') {
				istringstream tmlin(ecline);
				tmlin >> h >> x >> y;
				/*cout << x << ";" << y << ";" << z << endl;*/
				tmp_v.push_back(stof(x)); //konversi float 
				tmp_v.push_back(stof(y));
				vt.push_back(tmp_v);
			}
			else if (ecline[0] == 'v' && ecline[1] == 'n') {
				istringstream tmlin(ecline);
				tmlin >> h >> x >> y >> z;
				/*cout << x << ";" << y << ";" << z << endl;*/
				tmp_v.push_back(stof(x)); //konversi float 
				tmp_v.push_back(stof(y));
				tmp_v.push_back(stof(z));
				vn.push_back(tmp_v);
			}
			else  if (ecline[0] == 'f' && ecline[1] == ' ') {
				istringstream tmlin(ecline);
				string result;
				vector<float>res_x, res_y, res_z;
				while (getline(tmlin, result, ' ')) {
					if (result != "f") {
						split(result, res_x, res_y, res_z);
						
					}
				}
				fv.push_back(res_x);
				ft.push_back(res_y);
				fn.push_back(res_z);
				/*cout << x << ";" << y << ";" << z << endl;*/

			}
		}
	}
	void draw_object() {	
		glColor3f(1.0, 1.0, 1.0);
		for (int x = 0; x < fv.size(); x++) {
			glBegin(GL_POLYGON);
			for (int y = 0; y < fv[x].size(); y++) {
			/*cout << fv[x][0] << endl;*/
			glVertex3f(v[(fv[x][y])][0], v[(fv[x][y])][1], v[(fv[x][y])][2]);
			glNormal3f(vn[(fn[x][y])][0], vn[(fn[x][y])][1], vn[(fn[x][y])][2]);
			}
			glEnd();
		}
		glutSwapBuffers();
	}
};
class matriks {
private:
	float **mtr, **s;
	vector<float> vtmp;
public:
	matriks() {}; // constructor
	//matriks &operator*(){
	//}
	void init_translation(float x, float y, float z) {
		s = new float*[4]; // inisial awal matriks 3x3
		for (int i = 0; i < 4; i++) {
			s[i] = new float[4];
			for (int y = 0; y < 4; y++) {
				if (i == y) {
					s[i][y] = 1;
				}
				else { s[i][y] = 0; }
			}
		}
		// ganti x =>0 dan y+>1 dibawah ini sesuai titik koodrinat yang ingin diganti
		// -1 -> 1
		s[0][3] = x;
		s[1][3] = y;
		s[2][3] = z;
	}
	void init_rotasi_x(float x, float y, float z) {
		s = new float*[4]; // inisial awal matriks 3x3
		for (int i = 0; i < 4; i++) {
			s[i] = new float[4];
			for (int y = 0; y < 4; y++) {
				if (i == y) {
					s[i][y] = 1;
				}
				else { s[i][y] = 0; }
			}
		}
		s[1][1] = cos(x * 3.14159 / 180); //90deg
		s[1][2] = -sin(x * 3.14159 / 180);
		s[2][1] = sin(y * 3.14159 / 180);
		s[2][2] = cos(y * 3.14159 / 180);
	}
	void init_rotasi_y(float x, float y, float z) {
		s = new float*[4]; // inisial awal matriks 3x3
		for (int i = 0; i < 4; i++) {
			s[i] = new float[4];
			for (int y = 0; y < 4; y++) {
				if (i == y) {
					s[i][y] = 1;
				}
				else { s[i][y] = 0; }
			}
		}
		s[0][0] = cos(x * 3.14159 / 180); //90deg
		s[0][2] = sin(x * 3.14159 / 180);
		s[2][0] = -sin(y * 3.14159 / 180);
		s[2][2] = cos(y * 3.14159 / 180);
	}
	void init_rotasi_z(float x, float y, float z) {
		s = new float*[4]; // inisial awal matriks 3x3
		for (int i = 0; i < 4; i++) {
			s[i] = new float[4];
			for (int y = 0; y < 4; y++) {
				if (i == y) {
					s[i][y] = 1;
				}
				else { s[i][y] = 0; }
			}
		}
		s[0][0] = cos(x * 3.14159 / 180); //90deg
		s[0][1] = -sin(x * 3.14159 / 180);
		s[1][0] = sin(y * 3.14159 / 180);
		s[1][1] = cos(y * 3.14159 / 180);
	}
	void init_scale(float w, float v, float z) {
		s = new float*[4]; // inisial awal matriks 3x3
		for (int i = 0; i < 4; i++) {
			s[i] = new float[4];
			for (int y = 0; y < 4; y++) {
				if (i == y) {
					s[i][y] = 1;
				}
				else { s[i][y] = 0; }
			}
		}
		// ganti x =>0 dan y+>1 dibawah ini sesuai titik koodrinat yang ingin diganti
		// -1 -> 1
		s[0][0] = w;
		s[1][1] = v;
		s[2][2] = z;
	}
	void trans_opr(float v1, float v2, float v3) {
		vtmp.clear();
		/*cout << v1 << ";" << v2 << ";" << v3 << endl;*/
		float t[10][10];
		t[0][0] = v1;
		t[1][0] = v2;
		t[2][0] = v3;
		t[3][0] = 1;
		mtr = new float*[4];
		for (int x = 0; x < 4; x++) {
			mtr[x] = new float[1];
			for (int y = 0; y < 1; y++) {
				mtr[x][y] = 0;
				for (int z = 0; z < 4; z++) {
					mtr[x][y] += s[x][z] * t[z][y];
				}
				vtmp.push_back(mtr[x][y]);
			}
		}
	}
	vector<float> get_new() {
		return vtmp;
	}
};
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void redraw_v(matriks &transform,vectors &vc) {
	vector<vector<float>> tmp;
	for (int x = 0; x < v.size(); x++)
	{
		transform.trans_opr(v[x][0], v[x][1], v[x][2]);
		tmp.push_back(transform.get_new());
		
	}
	v.clear();
	v = tmp;
	if (ct == 2) {
		if (v.size() == 2) {
			glBegin(GL_LINES);
		}
		else {
			glBegin(GL_POLYGON);
		}
		glColor3f(1.0, 1.0, 1.0);
		for (int x = 0; x < v.size(); x++) {
			glVertex3f(v[x][0], v[x][1], v[x][2]);
		}
		glEnd();
		glutSwapBuffers();
	}
	else if (ct == 4) {
		vc.draw_object();
	}
}

void to_init() { // x and y coordinate
	glBegin(GL_LINES);
	glColor3f(1, 1, 0);
	glVertex2f(-1, 0.0);
	glVertex2f(1, 0.0);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1, 1, 0);
	glVertex2f(0.0, -1);
	glVertex2f(0.0, 1);
	glEnd();
}
void keyboard(unsigned char key, int a, int b) {
	glClear(GL_COLOR_BUFFER_BIT);
	/*to_init();*/
	matriks transform;
	vectors vc;
	if (key == '1') {
		ct = 2;
		vc.init_line();
	}
	if (key == '2') {
		ct = 2;
		vc.init_rectangle();
	}
	if (key == '3') {
		ct = 4;
		vc.init_object();
	}
	if (key == 'd') {
		transform.init_translation(0.1, 0, 0);
		redraw_v(transform,vc);
	}
	if (key == 'a') {
		transform.init_translation(-0.1, 0, 0);
		redraw_v(transform,vc);
	}
	if (key == 's') {
		transform.init_translation(0, -0.1, 0);
		redraw_v(transform,vc);
	}
	if (key == 'w') {
		transform.init_translation(0, 0.1, 0);
		redraw_v(transform,vc);
	}
	if (key == 'k') {
		transform.init_scale(0.5, 0.5, 0.5);
		redraw_v(transform,vc);
	}
	if (key == 'i') {
		transform.init_scale(1.5, 1.5, 1.5);
		redraw_v(transform,vc);
	}
	if (key == 'l') {
		transform.init_rotasi_x(-5, -5, -5);
		redraw_v(transform,vc);
	}
	if (key == 'j') {
		transform.init_rotasi_x(5, 5, 5);
		redraw_v(transform,vc);
	}
	if (key == 'o') {
		transform.init_rotasi_y(-5, -5, -5);
		redraw_v(transform,vc);
	}
	if (key == 'u') {
		transform.init_rotasi_y(5, 5, 5);
		redraw_v(transform,vc);
	}
	if (key == 'b') {
		transform.init_rotasi_z(-5, -5, -5);
		redraw_v(transform,vc);
	}
	if (key == 'm') {
		transform.init_rotasi_z(5, 5, 5);
		redraw_v(transform,vc);
	}
}
void display() {}

int main(int argc, char** argv) {
	/*srand(time(NULL));*/
	glutInit(&argc, argv);          // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(sizewin, sizewin);   // Set the window's initial width & height
	glutCreateWindow("Grafkom");  // Create window with the given title
	glutInitWindowPosition(320, 320); // Position the window's initial top-left corner
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	/*glutSpecialFunc(keyboard_line);*/
	glutKeyboardUpFunc(keyboard);
	initGL();                       // Our own OpenGL initialization
	glutMainLoop();                 // Enter the event-processing loop
	return 0;
}