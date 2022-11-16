/*
	Programm 2: Abschlussnote
	Dieses Programm berechnet aus den eingegebenen Noten die Abschlussnote des Studiengangs E&I-Technik.
	Gibt diese aus und l�sst diese Ver�ndern. Die Noten werden in eine Datei abgespeichert, sodass diese
	anschlie�end auch eingelesen werden k�nnen. Zudem kann zwischen den verschiedenen Vertiefungsrichtungen 
	gew�hlt werden.
	Autoren: Finn Ole Deutschmann, Severin Brachmann
	Datum: 16.11.2022
	Version: 1.0
*/


#define _CRT_SECURE_NO_WARNINGS
//einbinden der ben�tigten Libraries
#include <stdio.h>
#include <string.h>
#include <Windows.h>

//Anlegen der Struct f�r die einzelnen Module
struct sFach {
	char Modulbezeichnung[40];
	char Abkuerzung[5];
	int Gewichtung;
	int Note;
};

void ausgabe(struct sFach fach[30]);										//gibt die Tabelle mit den Noten aus
void eingabe(struct sFach fach[30]);										//l�sst den User die Noten eingeben
int getSum(struct sFach fach[30]);											//Berrechnet die Summe der F�cher
int getInt(char* text, int min, int max, int oldValue);						//fragt einen Int vom User ab
void printNote(struct sFach fach[30]);										//druckt Note etc. aus
void useData(struct sFach fach[30], int size, char* fileName, char* mode);	//speichert ins File oder liest aus file
int userInput(struct sFach fach[30]);										//fragt Buchstaben von User ab und ruft Unterfunktion auf
void setVertiefung(struct sFach fach[30]);									//Setzt die Vertiefungsrichtung
char getC(char text[]);														//Fragt character von user ab

int main() {
	//Initialisierung der struct
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
		{"Vertiefungsfach 1","VT1",12,0},				//19
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
	useData(fach, sizeof(fach), "Noten.txt", "rb");			//lese aus Datei
	int abbruch = 0;
	while (!abbruch) {										//Solange abbruch==0
		system("cls");										//clear Screen
		printf("Herzlich Willkommen zu Aufgabe 2: Abschlussnote.\nDieses Programm kann dir deine Abschlussnote berechnen.\n\n");
		printNote(fach);									//Ausdrucken der Noten
		abbruch = userInput(fach);							//Abfrage des User Inputs + Unterfunktion
	}
	useData(fach, sizeof(fach), "Noten.txt", "wb");		//Abspeichern der Noten
	return 0;
}

//Ausgabe der Tabelle
void ausgabe(struct sFach fach[30])
{
	printf("\n1. Jahr |2. Jahr |3.Jahr\n-------------------------\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%s:%2d  |%s:%2d  | %s:%2d\n", fach[i].Abkuerzung, fach[i].Note, fach[i + 10].Abkuerzung, fach[i + 10].Note, fach[i + 20].Abkuerzung, fach[i + 20].Note);
	}
	printf("\n");
}

//Eingabe der Noten f�r ein ausgew�hltes Studienjahr
void eingabe(struct sFach fach[30])
{
	int studienjahr = getInt("Geben Sie das Studienjahr ein, f\201r das Sie die Noten eingeben wollen.\n", 1, 3,-1);
	for (int i = (studienjahr - 1) * 10; i < (studienjahr - 1) * 10 + 10; i++)
	{
		printf("Bitte die Note f\201r das Fach %s an:\n", fach[i].Modulbezeichnung);
		fach[i].Note = getInt("", 0, 15,fach[i].Note);
	}

}

//berechnet die Summe der Noten und gibt diese zur�ck
int getSum(struct sFach fach[30])
{
	int sum = 0;
	for (int i = 0; i < 30; i++)
	{
		sum += fach[i].Note * fach[i].Gewichtung;
	}
	return sum;
}

/* Reads an int value from the user. */
int getInt(char* text,int min, int max, int oldValue)
{
	char line[50];      /* user input line */
	int newValue = 0;     /* new user input value */
	int finished = 0;     /* flag for correct input */
	char ch;            /* character behind number */

	do {
		/* print user request */
		printf("%s", text);

		/* get user input */
		fgets(line, 50, stdin);

		/* if user pressed ENTER only use old value */
		if (*line == '\n') {
			newValue = oldValue;
			if (newValue != -1) {
				finished = 1;
			}

			/* check if user typed a number */
		}
		else if (sscanf(line, "%d%c", &newValue, &ch) != 2 || ch != '\n')
			printf("Das war keine gueltige Zahl!\n");

		/* check range */
		else if (newValue<min || newValue>max)
			printf("Die Zahl liegt ausserhalb des gueltigen Bereichs!\n");

		/* number is correct */
		else finished = 1;

		/* repeat until finished */
	} while (!finished);

	/* return new value */
	return newValue;
}

//Gibt die Gesamtpunktzahl, die Note und die Note in Textform aus.
void printNote(struct sFach fach[30])
{
	const double NENNER = 4950.0;
	int summe = getSum(fach);	//Berechnen der Summe
	double note = (double)(summe) / NENNER * 15; //Berechnen der Note

	//ausgabe der Gesamtnote
	printf("Summe der insgesamt gesammelten Punkte: %d\nGesamtabschlussnote: %.3lf = ", summe, note);

	//Ausgabe des Texts.
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

//Lie�t oder schreibt in die angegebene Datei.
void useData(struct sFach fach[30], int size, char* fileName, char* mode)
{
	//erstellen eines File pointers, init mit NULL
	FILE* noten = NULL;
	//�ffnen des Files
	noten = fopen(fileName, mode);
	//Wenns geklappt hat:
	if (noten) {
		if (mode[0] == 'r') {	//Wenn der Mode read ist: Lies aus dem File
			fread(&fach, size, 1, noten);
			printf("Reading from file was succesful!\n");
		}
		else {
			fwrite(&fach, size, 1, noten);	//Sonst schreibe ins file
			printf("Writing to file was succesful!\n");
		}
		fclose(noten);	//Schlie�e das FIle.
	}
	else {	//Sonst Fehlermeldung ausgeben.
		if (mode[0] == 'r') {
			printf("Reading from file failed!\n");
		}
		else {
			printf("Writing to file failed!\n");
		}
	}
}

//Fragt einen Buchstaben vom User ab:
	//a= ausgabe der Noten
	//e= eingabe von Noten
	//v= Wahl des Vertiefungsfachs
	//(in zweiter Abfrage):x= Beenden des Programms
//returnt 1 wenn programm beendet werden soll.
int userInput(struct sFach fach[30])
{
	int retval = 0;									
	int abbruch = 0;	//while schleifen Variable
	char ch;
	while (!abbruch) {	//Solange keine g�ltige eingabe gemach wurde:
		ch = getC("\n\nBenutzerf\201hrung:\nEingabe der Noten [E]\nAusgabe der Noten [A]\nAuswahl der Vertiefungsrichtung [V]\n");
		switch (ch) {
		case 'A':case'a': ausgabe(fach); abbruch = 1; break;
		case 'E':case'e': eingabe(fach); abbruch = 1; break;
		case 'V':case'v': setVertiefung(fach); abbruch = 1; break;
		default: printf("Das war kein g\201ltiger Buchstabe!");
		}
	}
	//Wenn der user x eingibt wird 1 returnt -> Programm beendet
	ch = getC("\nProgramm beenden ? \nJa[X]\nNein[Alles andere]\n");
	if (ch == 'x' || ch == 'X') {
		retval = 1;
	}
	return retval;
}

//Setzt die Vertiefungsrichtung
void setVertiefung(struct sFach fach[30])
{
	int vertiefung = getInt("Bitte geben Sie die gew\201nschte Vertiefungsrichtung an:\nAutomatisierungs- und Energietechnik [1]\nDigitale Informationstechnik [2]\nKommunikationstechnik [3]\n", 1, 3,-1);
	switch (vertiefung) {
	case 1:
		strcpy(fach[19].Abkuerzung, "ST ");
		strcpy(fach[19].Modulbezeichnung, "Steuerungstechnik");
		strcpy(fach[20].Abkuerzung, "GE ");
		strcpy(fach[20].Modulbezeichnung, "Grundlagen der Energietechnik");
		strcpy(fach[21].Abkuerzung, "PB ");
		strcpy(fach[21].Modulbezeichnung, "Prozessleittechnik und Bussysteme");
		strcpy(fach[22].Abkuerzung, "LE ");
		strcpy(fach[22].Modulbezeichnung, "Antriebe und Leistungselektronik");
		strcpy(fach[23].Abkuerzung, "RY ");
		strcpy(fach[23].Modulbezeichnung, "Reglersynthese");
		strcpy(fach[24].Abkuerzung, "EN ");
		strcpy(fach[24].Modulbezeichnung, "Energietechnik");
		strcpy(fach[25].Abkuerzung, "PA ");
		strcpy(fach[25].Modulbezeichnung, "Prozessautomatisierung");
		if (getInt("Bitte geben Sie die gew\201nschte Vertiefungsfach an:\nZustandsregelung [1]\nRegenerative Energien [2]\n", 1, 2,-1)) {
			strcpy(fach[26].Abkuerzung, "ZT ");
			strcpy(fach[26].Modulbezeichnung, "Zustandsregelung");
		}
		else {
			strcpy(fach[26].Abkuerzung, "RE ");
			strcpy(fach[26].Modulbezeichnung, "Regenerative Energien");
		}
		break;
	case 2:
		strcpy(fach[19].Abkuerzung, "EL3");
		strcpy(fach[19].Modulbezeichnung, "Elektronik 3");
		strcpy(fach[20].Abkuerzung, "GN ");
		strcpy(fach[20].Modulbezeichnung, "Grundlagen der Nachrichtentechnik");
		strcpy(fach[21].Abkuerzung, "DY ");
		strcpy(fach[21].Modulbezeichnung, "Digitale Systeme");
		strcpy(fach[22].Abkuerzung, "BS ");
		strcpy(fach[22].Modulbezeichnung, "Betriebssysteme");
		strcpy(fach[23].Abkuerzung, "DV ");
		strcpy(fach[23].Modulbezeichnung, "Digitale Signalverarbeitung");
		strcpy(fach[24].Abkuerzung, "D\232 ");
		strcpy(fach[24].Modulbezeichnung, "Digitale \232abertragungstechnik");
		strcpy(fach[25].Abkuerzung, "BU ");
		strcpy(fach[25].Modulbezeichnung, "Bussysteme und Sensorik");
		strcpy(fach[25].Abkuerzung, "MC ");
		strcpy(fach[25].Modulbezeichnung, "Mikrocontrollersysteme");
		break;
	case 3:
		strcpy(fach[19].Abkuerzung, "EL3");
		strcpy(fach[19].Modulbezeichnung, "Elektronik 3");
		strcpy(fach[20].Abkuerzung, "GN ");
		strcpy(fach[20].Modulbezeichnung, "Grundlagen der Nachrichtentechnik");
		strcpy(fach[21].Abkuerzung, "DY ");
		strcpy(fach[21].Modulbezeichnung, "Digitale Systeme");
		strcpy(fach[22].Abkuerzung, "CN ");
		strcpy(fach[22].Modulbezeichnung, "Computernetze");
		strcpy(fach[23].Abkuerzung, "DV ");
		strcpy(fach[23].Modulbezeichnung, "Digitale Signalverarbeitung");
		strcpy(fach[24].Abkuerzung, "D\232 ");
		strcpy(fach[24].Modulbezeichnung, "Digitale \232abertragungstechnik");
		strcpy(fach[25].Abkuerzung, "BU ");
		strcpy(fach[25].Modulbezeichnung, "Hochfrequenz - Elektronik");
		strcpy(fach[25].Abkuerzung, "MC ");
		strcpy(fach[25].Modulbezeichnung, "Elektromagnetische Vertr\204glichkeit");
		break;
	}
}

//Lie�t einen Character vom User ein.
char getC( // [out] user input
	char text[]) // [in] question text for user input
{
	char cha; // user input
	int finished = 0; // flag for correct user input
	char ch; // character behind number
	int retVal; // return value of scanf
	do {
		// get user input
		printf("%s", text);
		ch = '\0';
		retVal = scanf("%c%c", &cha, &ch);
		// check for valid user input
		if (retVal != 2) printf("Das war keine korrektes Zeichen!\n");
		else if (ch != '\n') printf("Unerwartete Zeichen hinter der Zahl!\n");
		else finished = 1;
		// clear input stream
		while (ch != '\n') scanf("%c", &ch);
		// repeat if not finished
	} while (!finished);
	// return user input
	return cha;
}
