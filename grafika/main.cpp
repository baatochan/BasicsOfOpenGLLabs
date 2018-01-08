/*************************************************************************************/
//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacją osi
//  układu współrzędnych dla rzutowania perspektywicznego
/*************************************************************************************/
#include <gl/gl.h>
#include <gl/glut.h>

typedef float point3[3];
static GLfloat viewer[]= {0.0, 0.0, 10.0};

// inicjalizacja położenia obserwatora
static GLfloat thetaX = 0.0;   // kąt obrotu obiektu
static GLfloat thetaY = 0.0;   // kąt obrotu obiektu
static GLfloat pix2angle;     // przelicznik pikseli na stopnie

static GLint status = 0;       // stan klawiszy myszy
// 0 - nie naciśnięto żadnego klawisza
// 1 - naciśnięty zostać lewy klawisz
// 2 - prawy klawisz

static int x_pos_old=0;       // poprzednia pozycja kursora myszy (os x)
static int delta_x = 0;        // różnica pomiędzy pozycją bieżącą (os x) i poprzednią kursora myszy

static int y_pos_old=0;       // poprzednia pozycja kursora myszy (os y)
static int delta_y = 0;        // różnica pomiędzy pozycją bieżącą (os y) i poprzednią kursora myszy

static int zoom_pos_old=0;       // poprzednia pozycja kursora myszy (zoom)
static int delta_zoom = 0;        // różnica pomiędzy pozycją bieżącą (zoom) i poprzednią kursora myszy
//
/*************************************************************************************/
// Funkcja rysująca osie układu wspó?rz?dnych

void Axes(void)
{
	point3  x_min = {-5.0, 0.0, 0.0};
	point3  x_max = { 5.0, 0.0, 0.0};
// pocz?tek i koniec obrazu osi x

	point3  y_min = {0.0, -5.0, 0.0};
	point3  y_max = {0.0,  5.0, 0.0};
// pocz?tek i koniec obrazu osi y

	point3  z_min = {0.0, 0.0, -5.0};
	point3  z_max = {0.0, 0.0,  5.0};
//  pocz?tek i koniec obrazu osi y
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
// Funkcja określająca co ma być rysowane (zawsze wywoływana, gdy trzeba
// przerysować scenę)

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// Czyszczenie okna aktualnym kolorem czyszczącym

	glLoadIdentity();
// Czyszczenie macierzy bie??cej

	if (status == 2) {
		viewer[2] = viewer[2] + delta_zoom*pix2angle;
		if (viewer[2] < 4) viewer[2] = 4;
		if (viewer[2] > 90) viewer[2] = 90;
	}

	gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
// Zdefiniowanie położenia obserwatora
	Axes();
// Narysowanie osi przy pomocy funkcji zdefiniowanej powyżej

	if(status == 1)                     // jeśli lewy klawisz myszy wcięnięty
	{
		thetaX += delta_x*pix2angle;    // modyfikacja kąta obrotu o kat proporcjonalny
		thetaY += delta_y*pix2angle;    // modyfikacja kąta obrotu o kat proporcjonalny
	}                                  // do różnicy położeń kursora myszy

	glRotatef(thetaX, 0.0, 1.0, 0.0);  //obrót obiektu o nowy kąt
	glRotatef(thetaY, 1.0, 0.0, 0.0);

	glColor3f(1.0f, 1.0f, 1.0f);
// Ustawienie koloru rysowania na biały

	glutWireTeapot(3.0);
// Narysowanie czajnika
	glFlush();
// Przekazanie poleceń rysujących do wykonania
	glutSwapBuffers();

}
/*************************************************************************************/
// Funkcja ustalająca stan renderowania

void MyInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
// Kolor czyszczący (wypełnienia okna) ustawiono na czarny
}
/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie stałych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokość i szerokość okna) są
// przekazywane do funkcji za każdym razem gdy zmieni się rozmiar okna.

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	pix2angle = 360.0/(float)horizontal;  // przeliczenie pikseli na stopnie

	glMatrixMode(GL_PROJECTION);
	// Przełączenie macierzy bieżącej na macierz projekcji

	glLoadIdentity();
	// Czyszcznie macierzy bieżącej

	float aspect = (GLfloat)horizontal/vertical;

	gluPerspective(70, aspect, 1.0, 100.0);
	// Ustawienie parametrów dla rzutu perspektywicznego


	if(horizontal <= vertical)
		glViewport(0, (vertical-horizontal)/2, horizontal, vertical);

	else
		glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkości okna okna widoku (viewport) w zależności
	// relacji pomiędzy wysokością i szerokością okna

	glMatrixMode(GL_MODELVIEW);
	// Przełączenie macierzy bieżącej na macierz widoku modelu

	glLoadIdentity();
	// Czyszczenie macierzy bieżącej

}
/*************************************************************************************/
// Funkcja "bada" stan myszy i ustawia wartości odpowiednich zmiennych globalnych

void Mouse(int btn, int state, int x, int y)
{


	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old=x;         // przypisanie aktualnie odczytanej pozycji kursora
		y_pos_old=y;         // przypisanie aktualnie odczytanej pozycji kursora
		// jako pozycji poprzedniej
		status = 1;          // wcięnięty został lewy klawisz myszy
	} else if (btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		zoom_pos_old=y;
		status = 2;
	}
	else

		status = 0;          // nie został wcięnięty żaden klawisz
}

/*************************************************************************************/
// Funkcja "monitoruje" położenie kursora myszy i ustawia wartości odpowiednich
// zmiennych globalnych

void Motion( GLsizei x, GLsizei y )
{

	delta_x=x-x_pos_old;     // obliczenie różnicy położenia kursora myszy

	x_pos_old=x;            // podstawienie bieżącego położenia jako poprzednie

	delta_y=y-y_pos_old;     // obliczenie różnicy położenia kursora myszy

	y_pos_old=y;            // podstawienie bieżącego położenia jako poprzednie

	delta_zoom=x-zoom_pos_old;     // obliczenie różnicy położenia kursora myszy

	zoom_pos_old=x;            // podstawienie bieżącego położenia jako poprzednie

	glutPostRedisplay();     // przerysowanie obrazu sceny
}

/*************************************************************************************/

/*************************************************************************************/
// Główny punkt wejścia programu. Program działa w trybie konsoli

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);

	glutInit(&argc, argv);

	glutInitWindowSize(300, 300);

	glutCreateWindow("Rzutowanie perspektywiczne");

	glutDisplayFunc(RenderScene);
// Określenie, że funkcja RenderScene będzie funkcją zwrotną
// (callback function).  Będzie ona wywoływana za każdym razem
// gdy zajdzie potrzeba przerysowania okna

	glutReshapeFunc(ChangeSize);
// Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną
// za zmiany rozmiaru okna

	MyInit();
// Funkcja MyInit() (zdefiniowana powyżej) wykonuje wszelkie
// inicjalizacje konieczne  przed przystąpieniem do renderowania
	glEnable(GL_DEPTH_TEST);
// Włączenie mechanizmu usuwania niewidocznych elementów sceny
	glutMouseFunc(Mouse);
// Ustala funkcję zwrotną odpowiedzialną za badanie stanu myszy

	glutMotionFunc(Motion);
// Ustala funkcję zwrotną odpowiedzialną za badanie ruchu myszy
	glutMainLoop();
// Funkcja uruchamia szkielet biblioteki GLUT

	return 0;
}
/*************************************************************************************/
