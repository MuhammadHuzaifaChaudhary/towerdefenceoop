#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <cstdlib>
#include <random>
#include "blockDestruction.h"
#include "gameover.h"
#include "GameWindowElements.h"

#pragma once

using namespace std;
using namespace sf;
const int boardHeight = 20;
const int boardWidth = 10;
const int blockSize = 40;
const float centre = (boardWidth * blockSize) / 2;
int gameBoard[boardWidth][boardHeight] = {0};
int currentPieceID = rand() % 7;
int nextPieceID = rand() % 7;
int pieceRotation;
int selectColor;

const int TShape_0[4][4] = {
	{0, 0, 0, 0},
	{0, 1, 0, 0},
	{1, 1, 1, 0},
	{0, 0, 0, 0}};
const int TShape_1[4][4] = {
	{0, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 1, 0, 0}};
const int TShape_2[4][4] = {
	{0, 0, 0, 0},
	{1, 1, 1, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0}};
const int TShape_3[4][4] = {
	{0, 0, 0, 0},
	{0, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 0, 0}};

const int LShape_0[4][4] = {
	{0, 0, 0, 0},
	{0, 0, 2, 0},
	{2, 2, 2, 0},
	{0, 0, 0, 0}};
const int LShape_1[4][4] = {
	{0, 0, 0, 0},
	{0, 2, 0, 0},
	{0, 2, 0, 0},
	{0, 2, 2, 0}};
const int LShape_2[4][4] = {
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{2, 2, 2, 0},
	{2, 0, 0, 0}};
const int LShape_3[4][4] = {
	{0, 0, 0, 0},
	{2, 2, 0, 0},
	{0, 2, 0, 0},
	{0, 2, 0, 0}};

const int IShape_0[4][4] = {
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{3, 3, 3, 3},
	{0, 0, 0, 0}};
const int IShape_1[4][4] = {
	{0, 0, 3, 0},
	{0, 0, 3, 0},
	{0, 0, 3, 0},
	{0, 0, 3, 0}};
const int IShape_2[4][4] = {
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{3, 3, 3, 3},
	{0, 0, 0, 0}};
const int IShape_3[4][4] = {
	{0, 0, 3, 0},
	{0, 0, 3, 0},
	{0, 0, 3, 0},
	{0, 0, 3, 0}};

const int BoxShape_0[4][4] = {
	{0, 0, 0, 0},
	{0, 4, 4, 0},
	{0, 4, 4, 0},
	{0, 0, 0, 0}};
const int BoxShape_1[4][4] = {
	{0, 0, 0, 0},
	{0, 4, 4, 0},
	{0, 4, 4, 0},
	{0, 0, 0, 0}};
const int BoxShape_2[4][4] = {
	{0, 0, 0, 0},
	{0, 4, 4, 0},
	{0, 4, 4, 0},
	{0, 0, 0, 0}};
const int BoxShape_3[4][4] = {
	{0, 0, 0, 0},
	{0, 4, 4, 0},
	{0, 4, 4, 0},
	{0, 0, 0, 0}};

const int ZShape_0[4][4] = {
	{0, 0, 0, 0},
	{5, 5, 0, 0},
	{0, 5, 5, 0},
	{0, 0, 0, 0}};
const int ZShape_1[4][4] = {
	{0, 0, 0, 0},
	{0, 0, 5, 0},
	{0, 5, 5, 0},
	{0, 5, 0, 0}};
const int ZShape_2[4][4] = {
	{0, 0, 0, 0},
	{5, 5, 0, 0},
	{0, 5, 5, 0},
	{0, 0, 0, 0}};
const int ZShape_3[4][4] = {
	{0, 0, 0, 0},
	{0, 0, 5, 0},
	{0, 5, 5, 0},
	{0, 5, 0, 0}};

const int SShape_0[4][4] = {
	{0, 0, 0, 0},
	{0, 6, 6, 0},
	{6, 6, 0, 0},
	{0, 0, 0, 0}};
const int SShape_1[4][4] = {
	{0, 0, 0, 0},
	{0, 6, 0, 0},
	{0, 6, 6, 0},
	{0, 0, 6, 0}};
const int SShape_2[4][4] = {
	{0, 0, 0, 0},
	{0, 6, 6, 0},
	{6, 6, 0, 0},
	{0, 0, 0, 0}};
const int SShape_3[4][4] = {
	{0, 0, 0, 0},
	{0, 6, 0, 0},
	{0, 6, 6, 0},
	{0, 0, 6, 0}};

const int JShape_0[4][4] = {
	{0, 0, 0, 0},
	{7, 0, 0, 0},
	{7, 7, 7, 0},
	{0, 0, 0, 0}};
const int JShape_1[4][4] = {
	{0, 0, 0, 0},
	{0, 7, 0, 0},
	{0, 7, 0, 0},
	{7, 7, 0, 0}};
const int JShape_2[4][4] = {
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{7, 7, 7, 0},
	{0, 0, 7, 0}};
const int JShape_3[4][4] = {
	{0, 0, 0, 0},
	{0, 7, 7, 0},
	{0, 7, 0, 0},
	{0, 7, 0, 0}};

Color getColor(int selectColor)
{
	switch (selectColor)
	{
	case 1:
		return Color::Red;
	case 2:
		return Color::Cyan;
	case 3:
		return Color::Green;
	case 4:
		return Color::Yellow;
	case 5:
		return Color::Magenta;
	case 6:
		return Color::Blue;
	case 7:
		return Color::Black;
	default:
		return Color::White; // ADD a default return color here
	}
}
int currentPiece[4][4] = {0};
int xValue = 0;
int yValue = 0;

void Copy(int destination[4][4], const int source[4][4])
{
	for (int x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 4; ++y)
		{
			destination[x][y] = source[x][y];
		}
	}
}

bool canMove(int textX, int testY, const int piece[4][4])
{
	for (int x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 4; ++y)
		{
			if (piece[x][y] != 0)
			{
				int boardX = textX + x;
				int boardY = testY + y;

				if (boardX < 0 or boardX >= boardWidth)
				{
					return false;
				}
				if (boardY >= boardHeight)
				{
					return false;
				}
				if (gameBoard[boardX][boardY] != 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}

void Rotate()
{
	int nextRotation = (pieceRotation + 1) % 4; // we get 0,1,2,3 and it repeats from 0 till 3.
	int testPiece[4][4];						// an array to store

	// below are cases to see rotation and each number represents a rotation. 0, 90, 180, 270, and back to 0 or 360(same thing). copies the piece of rotation to testpiece
	switch (currentPieceID)
	{
	case 0:
		if (nextRotation == 0)
			Copy(testPiece, TShape_0);
		else if (nextRotation == 1)
			Copy(testPiece, TShape_1);
		else if (nextRotation == 2)
			Copy(testPiece, TShape_2);
		else if (nextRotation == 3)
			Copy(testPiece, TShape_3);
		break;
	case 1:
		if (nextRotation == 0)
			Copy(testPiece, LShape_0);
		else if (nextRotation == 1)
			Copy(testPiece, LShape_1);
		else if (nextRotation == 2)
			Copy(testPiece, LShape_2);
		else if (nextRotation == 3)
			Copy(testPiece, LShape_3);
		break;
	case 2:
		if (nextRotation == 0)
			Copy(testPiece, IShape_0);
		else if (nextRotation == 1)
			Copy(testPiece, IShape_1);
		else if (nextRotation == 2)
			Copy(testPiece, IShape_2);
		else if (nextRotation == 3)
			Copy(testPiece, IShape_3);
		break;
	case 3:
		if (nextRotation == 0)
			Copy(testPiece, BoxShape_0);
		else if (nextRotation == 1)
			Copy(testPiece, BoxShape_1);
		else if (nextRotation == 2)
			Copy(testPiece, BoxShape_2);
		else if (nextRotation == 3)
			Copy(testPiece, BoxShape_3);
		break;
	case 4:
		if (nextRotation == 0)
			Copy(testPiece, ZShape_0);
		else if (nextRotation == 1)
			Copy(testPiece, ZShape_1);
		else if (nextRotation == 2)
			Copy(testPiece, ZShape_2);
		else if (nextRotation == 3)
			Copy(testPiece, ZShape_3);
		break;
	case 5:
		if (nextRotation == 0)
			Copy(testPiece, SShape_0);
		else if (nextRotation == 1)
			Copy(testPiece, SShape_1);
		else if (nextRotation == 2)
			Copy(testPiece, SShape_2);
		else if (nextRotation == 3)
			Copy(testPiece, SShape_3);
		break;
	case 6:
		if (nextRotation == 0)
			Copy(testPiece, JShape_0);
		else if (nextRotation == 1)
			Copy(testPiece, JShape_1);
		else if (nextRotation == 2)
			Copy(testPiece, JShape_2);
		else if (nextRotation == 3)
			Copy(testPiece, JShape_3);
		break;
	}
	if (canMove(xValue, yValue, testPiece))
	{
		Copy(currentPiece, testPiece); // copies the rotation piece to current piece where test piece is the rotation piece as copied above in the cases
		pieceRotation = nextRotation;  // chnges rotation so that when rotation key presses again, it wont stay the same
	}
}

void Spawn(bool &GameOver)
{
	if (GameOver)
	{
		currentPieceID = nextPieceID;
		nextPieceID = rand() % 7;
		pieceRotation = 0;

		switch (currentPieceID)
		{
		case 0:
			Copy(currentPiece, TShape_0);
			break;
		case 1:
			Copy(currentPiece, LShape_0);
			break;
		case 2:
			Copy(currentPiece, IShape_0);
			break;
		case 3:
			Copy(currentPiece, BoxShape_0);
			break;
		case 4:
			Copy(currentPiece, ZShape_0);
			break;
		case 5:
			Copy(currentPiece, SShape_0);
			break;
		case 6:
			Copy(currentPiece, JShape_0);
			break;
		}

		xValue = (boardWidth / 2) - 2;
		yValue = 0.f;
		selectColor = rand() % 8 + 1;
		GameOver = gameOver(gameBoard);
	}
	else
	{
		cout << "Game Over!" << endl;
	}
}

void placePiece(int &RowDestroyed, bool &gameOver)
{
	for (int x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 4; ++y)
		{
			int element = currentPiece[x][y];

			if (element != 0)
			{
				int boardX = xValue + x;
				int boardY = yValue + y;
				gameBoard[boardX][boardY] = element;
			}
		}
	}

	Spawn(gameOver);
}

void BlockDisplay(RenderWindow &window, int nextPieceID) // display the nextBlock
{

	// These coordinates define the top-left corner where the 4x4 array starts drawing.
	const float CONTAINER_X = 420.0f; // Custom X coordinate (e.g., to the right of the grid)
	const float CONTAINER_Y = 550.0f; // Custom Y coordinate

	// --- 1. Identify the Block Shape Array ---

	// Pointer to a 4x4 integer array (used to select the correct shape)
	const int (*pieceArray)[4][4];
	int pieceColorID = nextPieceID + 1; // Color ID is usually 1-7 (Piece ID 0-6)

	// Select the correct shape array based on the ID (using the 0-rotation state)
	switch (nextPieceID)
	{
	case 0:
		pieceArray = &TShape_0;
		break;
	case 1:
		pieceArray = &LShape_0;
		break;
	case 2:
		pieceArray = &IShape_0;
		break;
	case 3:
		pieceArray = &BoxShape_0;
		break;
	case 4:
		pieceArray = &ZShape_0;
		break;
	case 5:
		pieceArray = &SShape_0;
		break;
	case 6:
		pieceArray = &JShape_0;
		break;
	default:
		return;
	}

	// --- 2. Setup Drawing Objects ---

	// Use a temporary RectangleShape for drawing each block
	RectangleShape block(Vector2f{float(blockSize), float(blockSize)});
	block.setOutlineColor(Color::Black);
	

	// --- 3. Draw Individual Blocks ---

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			// Check if the current cell in the shape array is part of the piece
			if ((*pieceArray)[x][y] != 0)
			{
				// Set the correct color for the piece
				block.setFillColor(getColor(pieceColorID));

				// Calculate position: [Container Start] + [Grid Index * Block Size]
				float drawX = CONTAINER_X + (x * blockSize);
				float drawY = CONTAINER_Y + (y * blockSize);

				block.setPosition(Vector2f{drawX, drawY+10});
				window.draw(block);
			}
		}
	}
}

void updateandDrawGame(RenderWindow &window, Clock &gameClock, float &timeSinceLastFall, float Speed, float startofgrid, int &RowsDestroyed, bool &GameOver, int &nextpieceid)
{

	const int RED = 1;
	const int CYAN = 2;
	const int GREEN = 3;
	const int YELLOW = 4;
	const int PURPLE = 5;
	const int BLUE = 6;
	const int BLACK = 7;

	VertexArray mySquare(PrimitiveType::Triangles, 6);
	if (GameOver)
	{
		float elapsedTime = gameClock.restart().asSeconds();
		timeSinceLastFall += elapsedTime;
		if (timeSinceLastFall >= Speed)
		{
			if (canMove(xValue, yValue + 1, currentPiece))
			{
				yValue++;
			}
			else
			{
				placePiece(RowsDestroyed, GameOver);
			}
			timeSinceLastFall = 0.0f;
		}
	}
	// window.clear() and window.display are in main file
	mySquare.clear();

	for (int x = 0; x < boardWidth; ++x)
	{
		for (int y = 0; y < boardHeight; ++y)
		{
			int element = gameBoard[x][y];
			if (element != 0)
			{
				Color pieceColor = getColor(element);

				float leftX = x * blockSize;
				float rightX = leftX + blockSize;
				float topY = (y * blockSize) + 100.f;
				float bottomY = topY + blockSize;

				mySquare.append(Vertex{Vector2f(leftX, topY), pieceColor});
				mySquare.append(Vertex{Vector2f(rightX, topY), pieceColor});
				mySquare.append(Vertex{Vector2f(leftX, bottomY), pieceColor});
				mySquare.append(Vertex{Vector2f(leftX, bottomY), pieceColor});
				mySquare.append(Vertex{Vector2f(rightX, topY), pieceColor});
				mySquare.append(Vertex{Vector2f(rightX, bottomY), pieceColor});
			}
		}
	}

	for (int x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 4; ++y)
		{
			int element = currentPiece[x][y];
			if (element != 0)
			{
				Color pieceColor = getColor(element);

				int boardX = xValue + x;
				int boardY = yValue + y;

				float leftX = boardX * blockSize;
				float rightX = leftX + blockSize;
				float topY = (boardY * blockSize) + startofgrid;
				float bottomY = topY + blockSize;

				mySquare.append(Vertex{Vector2f(leftX, topY), pieceColor});
				mySquare.append(Vertex{Vector2f(rightX, topY), pieceColor});
				mySquare.append(Vertex{Vector2f(leftX, bottomY), pieceColor});
				mySquare.append(Vertex{Vector2f(leftX, bottomY), pieceColor});
				mySquare.append(Vertex{Vector2f(rightX, topY), pieceColor});
				mySquare.append(Vertex{Vector2f(rightX, bottomY), pieceColor});
			}
		}
	}
	RowCheck(gameBoard, RowsDestroyed); // blockDestruction.h
	window.draw(mySquare);
}
