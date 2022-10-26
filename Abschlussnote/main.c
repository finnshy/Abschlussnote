#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


struct sFach {
	char Modulbezeichnung[40];
	char Abkuerzung[5];
	double Gewichtung;
	int Note;
};

void ausgabe(struct sFach fach[30]);
void eingabe(struct sFach fach[30]);
int getSum(struct sFach fach[30]);
int getInt(char text[], int min, int max); // [in] question text for user input, array with already picked values, min and max for userinput
void printNote(struct sFach fach[30]);

int main() {
	struct sFach fach[30] = {
		{"Analysis 1","AN1",5,0},
		{"Analysis 2","AN2",6,0},
		{"Lineare ALgebra 1","LA1",5,0},
		{"Physik 1","PH1",5,0},
		{"Physik 2","PH2",5,0},							//5
		{"Grundlagen der Elektrotechnik 1","ET1",7,0},
		{"Grundlagen der Elektrotechnik 2","ET2",7,0},
		{"Elektronik 1","EL1",5,0},
		{"Programmieren 1","PR1",6,0},
		{"Programmieren 2","PR2",5,0},					//10
		{"Numerik und Stochastik","NS ",10,0},
		{"Signale und Systeme 1","SS1",10,0},
		{"Signale und Systeme 2","SS2",12,0},
		{"Elektronik 2", "EL2",10,0},
		{"Digitaltechnik","DI ",12,0},					//15
		{"Mikroprozessortechnik","MP ",12,0},
		{"Regelungstechnik","RT ",12,0},
		{"Objektorientierte Programmierung","OP ",12,0},
		{"Vertiefungsfach 1","VT1",12,0},
		{"Vertiefungsfach 2","VT2",12,0},				//20
		{"Vertiefungsfach 3","VT3",10,0},
		{"Vertiefungsfach 4","VT4",10,0},
		{"Vertiefungsfach 5","VT5",10,0},
		{"Vertiefungsfach 6","VT6",10,0},
		{"Vertiefungsfach 7","VT7",10,0},				//25
		{"Vertiefungsfach 8","VT8",10,0},
		{"Wahlpflichtmodul 1","WP1",10,0},
		{"Wahlpflichtmodul 2","WP2",10,0},
		{"Wahlpflichtprojekt","PO ",10,0},
		{"Bachelorarbeit mit Kolloquium","AN1",70,0}	//30
	};
	//ausgabe(fach);
	//eingabe(fach);
	printNote(fach);
	return 0;
}

void ausgabe(struct sFach fach[30])
{
	printf("1. Jahr |2. Jahr |3.Jahr\n-------------------------\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%s:%2d  |%s:%2d  | %s:%2d\n", fach[i].Abkuerzung, fach[i].Note, fach[i + 10].Abkuerzung, fach[i + 10].Note, fach[i + 20].Abkuerzung, fach[i + 20].Note);
	}
	printf("\n");
}

void eingabe(struct sFach fach[30])
{
	for (int i = 0; i < 30; i++)
	{
		printf("Bitte die Note für das Fach %s an:\n",fach[i].Modulbezeichnung);
		fach[i].Note=getInt("", 0, 15);
	}

}

int getSum(struct sFach fach[30])
{
	int sum = 0;
	for (int i = 0; i < 30; i++)
	{
		sum += fach[i].Note;
	}
	return sum;
}

/* Reads an int value from the user. */
int getInt(char text[], int min, int max) // [in] question text for user input, array with already picked values, min and max for userinput
{
	int value; // user input
	int finished = 0; // flag for correct user input
	char ch; // character behind number
	int retVal; // return value of scanf
	do {
		// get user input
		printf("%s", text);
		ch = '\0';
		retVal = scanf("%d%c", &value, &ch);
		// check for valid user input
		if (retVal != 2) printf("Das war keine korrekte Zahl!\n\n");
		else if (ch != '\n') printf("Unerwartete Zeichen hinter der Zahl!\n\n");
		else if (value > max || value < min) printf("Zahl ausserhalb des Intervals [%d,%d]\n\n", min, max);
		else finished = 1;
		// clear input stream
		while (ch != '\n') scanf("%c", &ch);
		// repeat if not finished
	} while (!finished);
	// return user input
	return value;
}

void printNote(struct sFach fach[30])
{
	const double NENNER = 4950.0;
	int summe = getSum(fach);
	double note = (double)summe / NENNER;

	printf("Summe der insgesamt gesammelten Punkte: %d\nGesamtabschlussnote: %.3lf = ", summe,note);

	if (summe >= 4785) {
		printf("sehr gut mit (mit Auszeichnung)");
	}
	else {
		if (summe >= 4125) {
			printf("sehr gut");
		}
		else {
			if (summe >= 3135) {
				printf("gut");
			}
			else {
				if (summe >= 2145) {
					printf("befriedigend");
				}
				else {
					if (summe >= 1650) {
						printf("bestanden");
					}
					else {
						printf("Nicht bestanden");
					}
				}
			}
		}
	}
	printf("\n");
}