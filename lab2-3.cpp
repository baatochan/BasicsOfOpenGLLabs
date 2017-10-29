/*************************************************************************************/
// Trochę bardziej skomplikowany program wykorzystujący funkcje biblioteki OpenGL
/*************************************************************************************/
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
/*************************************************************************************/

// Funkcaja określająca, co ma być rysowane 
// (zawsze wywoływana, gdy trzeba przerysować scenę)


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszczącym
	glColor3f(0.0f, 1.0f, 0.0f);
	// Ustawienie aktualnego koloru rysowania na zielony

	glBegin(GL_TRIANGLES);       // Narysowanie zielonego trójkąta
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 50.0f);
		glVertex2f(50.0f, 0.0f);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f); // Ustawienie aktualnego koloru rysowania na czerwony

	glBegin(GL_TRIANGLES); // Narysowanie czerwonego trójkąta
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 50.0f);
		glVertex2f(-50.0f, 0.0f);
	glEnd();

	glFlush();
	// Przekazanie poleceń rysujących do wykonania
}
/*************************************************************************************/
// Funkcja ustalająca stan renderowania

void MyInit(void)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor okna wnętrza okna - ustawiono na szary
}
/*************************************************************************************/
// Funkcja służąca do kontroli zachowania proporcji rysowanych obiektów
// niezależnie od rozmiarów okna graficznego


void ChangeSize(GLsizei horizontal, GLsizei vertical)
// Parametry horizontal i vertical (szerokość i wysokość okna) są
// przekazywane do funkcji za każdym razem, gdy zmieni się rozmiar okna
{
	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio określającej proporcję wymiarów okna

	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0
		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkościokna okna urządzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Określenie układu współrzędnych obserwatora
	glLoadIdentity();
	// Określenie przestrzeni ograniczającej
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie współczynnika proporcji okna
	// Gdy okno na ekranie nie jest kwadratem wymagane jest 
	// określenie okna obserwatora. 
	// Pozwala to zachować właściwe proporcje rysowanego obiektu
	// Do określenia okna obserwatora służy funkcja glOrtho(...)

	if (horizontal <= vertical)
		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	// Określenie układu współrzędnych    
	glLoadIdentity();
}
/*************************************************************************************/
// Główny punkt wejścia programu. Program działa w trybie konsoli

int main(int argc, char* argv[])
{
	// Ukrycvie okna konsoli
	HWND con = GetConsoleWindow();
	ShowWindow(con, SW_HIDE);

    glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wyświetlania
	// GLUT_SINGLE - pojedynczy bufor wyświetlania
	// GLUT_RGBA - model kolorów RGB

	glutCreateWindow("Trzeci program w OpenGL");
	// Utworzenie okna i określenie treści napisu w nagłówku okna

	glutDisplayFunc(RenderScene);
	// Określenie, że funkcja RenderScene będzie funkcją zwrotną (callback)
	// Biblioteka GLUT będzie wywoływała tą funkcję za każdym razem, gdy
	// trzeba będzie przerysować okno


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powyżej) wykonuje wszelkie  
	// inicjalizacje konieczneprzed przystąpieniem do renderowania

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

    return 0;
}
/*************************************************************************************/