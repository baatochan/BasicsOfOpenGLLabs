/*************************************************************************************/
// Najprostszy program wykorzystujący funkcje biblioteki OpenGL
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

	glutCreateWindow("Pierwszy program w OpenGL");
	// Utworzenie okna i określenie treści napisu w nagłówku okna

	glutDisplayFunc(RenderScene);
	// Określenie, że funkcja RenderScene będzie funkcją zwrotną (callback)
	// Biblioteka GLUT będzie wywoływała tą funkcję za każdym razem, gdy
	// trzeba będzie przerysować okno
	MyInit();
	// Funkcja MyInit (zdefiniowana powyżej) wykonuje wszelkie 
	// inicjalizacje konieczne przed przystąpieniem do renderowania

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

    return 0;
}
/**************************************************************************************/