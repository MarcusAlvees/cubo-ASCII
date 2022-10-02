#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

float A, B, C;
float cubeWidth = 20;
int _width = 160, _height = 44;
float zBuffer[160 * 44];
char buffer[160 * 44];
int _backgroundASCIICode = '.';
float _camDistance = 100;
float z1 = 50;
int idx;


float ooz;
int xp, yp;

float incrementSpeed = 0.4;
float x, y, z;

// Matriz de Rotação
float calcularX(int i, int j, int k) {
	return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
		j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calcularY(int i, int j, int k) {
	return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
		j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
		i * cos(B) * sin(C);
}

float calcularZ(int i, int j, int k) {
	return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}


void CalcularFace(float cubeX, float cubeY, float cubeZ, int ch) {
	x = calcularX(cubeX, cubeY, cubeZ);
	y = calcularY(cubeX, cubeY, cubeZ);
	z = calcularZ(cubeX, cubeY, cubeZ) + _camDistance;

	ooz = 1 / z;

	xp = (int)(_width / 2 + z1 * ooz * x * 2);
	yp = (int)(_height / 2 + z1 * ooz * y);

	idx = xp + yp * _width;
	if (idx >= 0 && idx < _width * _height) {
		if (ooz > zBuffer[idx]) {
			zBuffer[idx] = ooz;
			buffer[idx] = ch;
		}
	}
}

int main()
{
	system("cls");
	while (1) {
		memset(buffer, _backgroundASCIICode, _width * _height);
		memset(zBuffer, 0, _width * _height * 4);
		cubeWidth = 20;
		for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
			for (float cubeY = -cubeWidth; cubeY < cubeWidth;
				cubeY += incrementSpeed) {
				CalcularFace(cubeX, cubeY, -cubeWidth, '@');
				CalcularFace(cubeWidth, cubeY, cubeX, '$');
				CalcularFace(-cubeWidth, cubeY, -cubeX, '~');
				CalcularFace(-cubeX, cubeY, cubeWidth, '#');
				CalcularFace(cubeX, -cubeWidth, -cubeY, ';');
				CalcularFace(cubeX, cubeWidth, cubeY, '+');
			}
		}
		printf("\x1b[H");
		//system("cls");
		for (int k = 0; k < _width * _height; k++) {
			putchar(k % width ? buffer[k] : 10);
		}		
		A += 0.025;
		B += 0.025;
		C += 0.15;
	}
	return 0;
}