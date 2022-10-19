#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


struct sFach {
	char Modulbezeichnung[40];
	char Abkuerzung[5];
	double Gewichtung;
	int Note;
};

int main() {
	struct sFach fach[30] = {
		{"Analysis 1","AN1",5,0},
		{"Lineare ALgebra 1","LA1",5,0},
		{"Physik 1","PH1",5,0},
		{"Grundlagen der Elektrotechnik 1","ET1",7,0},
		{"Programmieren 1","PR1",6,0},

		{"Analysis 2","AN2",6,0},
		{"Physik 2","PH2",5,0},
		{"Grundlagen der Elektrotechnik 2","ET2",7,0},
		{"Elektronik 1","EL1",5,0},
		{"Programmieren 2","PR2",5,0},

		{"Numerik und Stochastik","NS",5,0},
		{"Signale und Systeme 1","SS1",5,0},
		{"Elektronik 2", "EL2",5,0},
		{"Objektorientierte Programmierung","OP",6,0},
		{"Digitaltechnik","DI",6,0},

		{"Signale und Systeme 2","SS2",6,0},
		{"Regelungstechnik","RT",6,0},
		{"Mikroprozessortechnik","MP",6,0},
		{"Elektronik 3","EL3",6,0},
		{"Steuerungstechnik","ST",6,0},

		{}
	};
	//fillData(fach);
	printf("%s", fach[1].Modulbezeichnung);
	return 0;
}
