/*************************************************************************************/
//  Program rusujacy jajko
/*************************************************************************************/
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <iostream>
#include <cmath>
#include <ctime> //dla time

#define numberOfPoints 20 // poziom szczegolowosci rysunku - im wiecej tym wiecej punktow w jajku

typedef float point3[3];
/*************************************************************************************/

static GLfloat theta[] = {0, 0, 0}; // trzy kąty obrotu

point3 eggCords[numberOfPoints][numberOfPoints]; // tablica zawierajaca wspolrzedne punktow jajka

using namespace std;

/**
 * Funkcja wyliczajaca wspolrzedne jajka w zaleznosci od szczegolowosci (numberOfPoints)
 */
void countEggCords() {
	float vmin = 0;
	float vmax = 1;
	float umin = 0;
	float umax = 1;

	float v, u, x, y, z;

	float vSpace = (vmax-vmin)/numberOfPoints; //TODO: nazwac to jakos
	float uSpace = (umax-umin)/numberOfPoints; //TODO: nazwac to jakos

	for (int i = 0; i < numberOfPoints; i++) {
		for (int j = 0; j < numberOfPoints; j++) {
			v = vmin + i*vSpace;
			u = umin + j*uSpace;

			x = -90 * pow(u, 5);
			x += 225 * pow(u, 4);
			x -= 270 * pow(u, 3);
			x += 180 * pow(u, 2);
			x -= 45 * u;
			z = x;
			x *= cos(M_PI * v);

			y = 160 * pow(u, 4);
			y -= 320 * pow(u, 3);
			y += 160 * pow(u, 2);
			y -= 5;

			z *= sin(M_PI * v);

			eggCords[j][i][0] = x;
			eggCords[j][i][1] = y;
			eggCords[j][i][2] = z;
		}
	}
}

/**
 * Funkcja rysujaca jajko.
 */
void drawEgg() {
	glColor3f(1,1,1);
	int k = 0;
	int l = 0;
	int m = 0;
	int n = 0;
	int o = 0;
	for (int i = 0; i < numberOfPoints; i++) {
		if (i == 0) {
			for (int j = 0; j < numberOfPoints; j++) {
				k = 1;
				glBegin(GL_TRIANGLES);
				glVertex3fv(eggCords[0][0]);

				glVertex3fv(eggCords[k][j]);

				if (j + 1 == numberOfPoints) {
					glVertex3fv(eggCords[numberOfPoints-1][0]);
				}
				else {
					glVertex3fv(eggCords[k][j + 1]);
				}
				glEnd();
			}
		} else if (i == numberOfPoints - 1) {
			for (int j = 0; j < numberOfPoints; j++) {
				k = 1;
				glBegin(GL_TRIANGLES);
				glVertex3fv(eggCords[0][0]);

				glVertex3fv(eggCords[i][j]);

				if (j + 1 == numberOfPoints) {
					glVertex3fv(eggCords[1][0]);
				}
				else {
					glVertex3fv(eggCords[i][j + 1]);
				}
				glEnd();
			}
		} else if (i == (numberOfPoints / 2) - 1 && numberOfPoints % 2 == 0) {
			for (int j = 0; j < numberOfPoints; j++) {
				k = numberOfPoints / 2;
				glBegin(GL_TRIANGLES);
				glVertex3fv(eggCords[k][0]);

				glVertex3fv(eggCords[i][j]);

				if (j + 1 == numberOfPoints) {
					glVertex3fv(eggCords[k+1][0]);
				}
				else {
					glVertex3fv(eggCords[i][j + 1]);
				}
				glEnd();
			}
		} else if (i == numberOfPoints / 2 && numberOfPoints % 2 == 0) {
			for (int j = 0; j < numberOfPoints; j++) {
				k = numberOfPoints / 2 + 1;
				glBegin(GL_TRIANGLES);
				glVertex3fv(eggCords[i][0]);

				glVertex3fv(eggCords[k][j]);

				if (j + 1 == numberOfPoints) {
					glVertex3fv(eggCords[k-2][0]);
				}
				else {
					glVertex3fv(eggCords[k][j + 1]);
				}
				glEnd();
			}
		} else if (numberOfPoints % 2 == 1 && i == (numberOfPoints - 1) / 2) {
			for (int j = 0; j < numberOfPoints - 1; j++) {
				k = i + 1;
				glBegin(GL_TRIANGLES);
				glVertex3fv(eggCords[i][j]);

				glVertex3fv(eggCords[k][numberOfPoints - 1 - j]);

				glVertex3fv(eggCords[i][j + 1]);
				glEnd();
			}
		} else if (numberOfPoints % 2 == 1 && i == (numberOfPoints + 1) / 2) {
			for (int j = 0; j < numberOfPoints - 1; j++) {
				k = i - 1;
				glBegin(GL_TRIANGLES);
				glVertex3fv(eggCords[i][j]);

				glVertex3fv(eggCords[k][numberOfPoints - 1 - j]);

				glVertex3fv(eggCords[i][j + 1]);
				glEnd();
			}
		} else {
			for (int j = 0; j < numberOfPoints; j++) {
				k = i + 1;
				l = j + 1;
				m = i + 1;
				n = j + 1;
				o = i;
				if (l == numberOfPoints) {
					n = 0;
					o = numberOfPoints - i;
					m = numberOfPoints - i - 1;
				}

				glBegin(GL_TRIANGLES);
				glVertex3fv(eggCords[i][j]);

				glVertex3fv(eggCords[k][j]);

				glVertex3fv(eggCords[o][n]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glVertex3fv(eggCords[m][n]);

				glVertex3fv(eggCords[k][j]);

				glVertex3fv(eggCords[o][n]);
				glEnd();
			}
		}
	}
}

// Funkcja rysująca osie układu współrzędnych
void Axes(void)
{
	point3  x_min = {-5.0, 0.0, 0.0};
	point3  x_max = { 5.0, 0.0, 0.0};
// początek i koniec obrazu osi x

	point3  y_min = {0.0, -5.0, 0.0};
	point3  y_max = {0.0,  5.0, 0.0};
// początek i koniec obrazu osi y

	point3  z_min = {0.0, 0.0, -5.0};
	point3  z_max = {0.0, 0.0,  5.0};
//  początek i koniec obrazu osi y
	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x
	glVertex3fv(x_min);
	glVertex3fv(x_max);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y
	glVertex3fv(y_min);
	glVertex3fv(y_max);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES); // rysowanie osi z
	glVertex3fv(z_min);
	glVertex3fv(z_max);
	glEnd();
}
/*************************************************************************************/
// Funkcja określająca co ma być rysowane (zawsze wywoływana gdy trzeba
// przerysować scenę)

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// Czyszczenie okna aktualnym kolorem czyszczącym

	glLoadIdentity();
// Czyszczenie macierzy bieżącej
	Axes();
// Narysowanie osi przy pomocy funkcji zdefiniowanej wyżej

	glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);

	drawEgg(); // wywolanie funkcji rysujacej jajko

	glFlush();
// Przekazanie poleceń rysujących do wykonania

	glutSwapBuffers();
//
}

// funkcja definiujaca obracanie bryly
void spinEgg()
{
	theta[0] -= 0.05;
	if( theta[0] > 360.0 ) theta[0] -= 360.0;

	theta[1] -= 0.05;
	if( theta[1] > 360.0 ) theta[1] -= 360.0;

	theta[2] -= 0.05;
	if( theta[2] > 360.0 ) theta[2] -= 360.0;

	glutPostRedisplay(); //odświeżenie zawartości aktualnego okna
}

/*************************************************************************************/
// Funkcja ustalająca stan renderowania

void MyInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
// Kolor czyszcący (wypełnienia okna) ustawiono na czarny
}
/*************************************************************************************/
// Funkcja ma za zadanie utrzymanie stałych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokość i szerokość okna) są
// przekazywane do funkcji za każdym razem gdy zmieni się rozmiar okna.

void ChangeSize(GLsizei horizontal, GLsizei vertical )
{
	GLfloat AspectRatio;
// Deklaracja zmiennej AspectRatio  określającej proporcję
// wymiarów okna
	if(vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
// Ustawienie wielkościokna okna widoku (viewport)
// W tym przypadku od (0,0) do (horizontal, vertical)
	glMatrixMode(GL_PROJECTION);
// Przełączenie macierzy bieżącej na macierz projekcji
	glLoadIdentity();
// Czyszcznie macierzy bieżącej
	AspectRatio = (GLfloat)horizontal/(GLfloat)vertical;
// Wyznaczenie współczynnika  proporcji okna
// Gdy okno nie jest kwadratem wymagane jest określenie tak zwanej
// przestrzeni ograniczającej pozwalającej zachować właściwe
// proporcje rysowanego obiektu.
// Do okreslenia przestrzeni ograniczjącej służy funkcja
// glOrtho(...)
	if(horizontal <= vertical)
		glOrtho(-7.5,7.5,-7.5/AspectRatio,7.5/AspectRatio,10.0, -10.0);
	else
		glOrtho(-7.5*AspectRatio,7.5*AspectRatio,-7.5,7.5,10.0,-10.0);
	glMatrixMode(GL_MODELVIEW);
// Przełączenie macierzy bieżącej na macierz widoku modelu
	glLoadIdentity();
// Czyszcenie macierzy bieżącej
}
/*************************************************************************************/
// Główny punkt wejścia programu. Program działa w trybie konsoli

int main(int argc, char* argv[])
{
	srand(time(0)); // ziarno dla liczb pseudo losowych

	countEggCords(); // pojedyncze wywolanie wyliczen wierzcholkow jajka

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);

	glutInit(&argc, argv);

	glutInitWindowSize(300, 300);

	glutCreateWindow("jajo");

	glutDisplayFunc(RenderScene);
// Określenie, że funkcja RenderScene będzie funkcją zwrotną
// (callback function).  Bedzie ona wywoływana za każdym razem
// gdy zajdzie potrzba przeryswania okna
	glutReshapeFunc(ChangeSize);
// Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną
// zazmiany rozmiaru okna

	glutIdleFunc(spinEgg); //zdefiniowanie funckji obrotu jajka

	MyInit();
// Funkcja MyInit() (zdefiniowana powyżej) wykonuje wszelkie
// inicjalizacje konieczne  przed przystąpieniem do renderowania
	glEnable(GL_DEPTH_TEST);
// Włączenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();
// Funkcja uruchamia szkielet biblioteki GLUT

	return 0;
}
/*************************************************************************************/