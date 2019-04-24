//Berechnung und Ausgabe der Levenshtein Distanz zwischen zwei Wörtern
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printMatrix (int *matrix, int zeilen, int spalten); 

void main () {
	char wort1[49], wort2[49];								//2 Strings mit Platz für 49 Zeichen, da 49*2=98, letzte Mögl für 2 Stellen für Ausgabe Zahlen in der Matrix
	int laenge1, laenge2, i, n, distanz;
	
	printf("Eingabe des ersten Wortes: ");					//Aufforderung zur Eingabe von Wörtern
	scanf("%s", wort1);
	printf("Eingabe des zeiten Wortes: ");
	scanf("%s", wort2);
	
	laenge1 = strlen(wort1) + 1;							//Länge um 1 höher als Wort, da Levenshteinmatrix mit leerem Buchstaben beginnt
	laenge2 = strlen(wort2) + 1;
	
	int ergebnisMatrix[laenge1][laenge2];					//2D Array als Ergebnismatrix erstellen
	memset (ergebnisMatrix, 0, sizeof(ergebnisMatrix));		//Array mit Nullen füllen
	
	for (i = 0; i < laenge2; i++) {							//Erste Zeile mit Zalen von 0 bis Länge des Zielwortes füllen (einfüge Operation beim Wortvergleich)
		ergebnisMatrix[0][i] = i;
	}
	
	for (i = 1; i < laenge1; i++) {							//Erste Spalte mit Zahlen von 0 bis Länge des Quellwortes füllen (löschen Operation beim Wortvergleich)
		ergebnisMatrix[i][0] = i;
	}
	
	for (i = 1; i < laenge1; i++) {							//Zusammensetzung der Matrix
		for (n = 1; n < laenge2; n++) {
			if (wort1[i - 1] == wort2[n - 1]) {				//Wenn Buchstaben an Stelle gleich sind --> keine erhöhung der Levenshtein Distanz
				ergebnisMatrix[i][n] = ergebnisMatrix[i - 1][n - 1];
			}
			else {											//Wenn Buchstaben verschiden erhöhe um 1 von min(links daneben, darüber)
				if (ergebnisMatrix[i][n - 1] > ergebnisMatrix[i - 1][n])
					ergebnisMatrix[i][n] = ergebnisMatrix[i - 1][n] + 1;
				else
					ergebnisMatrix[i][n] = ergebnisMatrix[i][n - 1] + 1;
			}
		}
	}
	
	distanz = ergebnisMatrix[laenge1 - 1][laenge2 - 1];				//Levenshteindistanz = Element rechts unten
	printMatrix (&ergebnisMatrix[0][0], laenge1, laenge2);	//Funktionsaufruf die Ergebnismatrix auszugeben
	printf("\nDie Levenshteindistanz zwischen '%s' und '%s' betraegt: %i", wort1, wort2, distanz);		//Ausgabe der Levenshtein Distanz
	getchar();
	printf("\nContinue...");
	getchar();
}

void printMatrix (int *matrix, int zeilen,int spalten) {	//Funktion zur Ausgabe der Ergebnismatrix
	int n, m;
	printf("\n");
	for (n = 0; n < zeilen; n++) {							//Zeilen
		for (m = 0; m < spalten; m++){						//Spalten
			printf("%3i", *(matrix + n * spalten + m));		//Ausgabe der Zahlen in der Matrix
		}
		printf("\n");										//Zeilenumburch
	}
}