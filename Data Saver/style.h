#pragma once


void SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE); // Get Handle
	SetConsoleScreenBufferSize(Handle, coord); // Set Buffer Size
	SetConsoleWindowInfo(Handle, TRUE, &Rect); // Set Window Size
}



void printIntro()
{

	//							CONSOLE STYLE
//#################################################################################
	SetConsoleTitle("TITOLO");

	int Alpha = 80;
	CONSOLE_FONT_INFOEX cf = {
		0
	};
	cf.cbSize = sizeof cf;
	cf.dwFontSize.X = 6;
	cf.dwFontSize.Y = 12;
	wcscpy_s(cf.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, &cf);

	SetWindow(105, 30);

	/*SMALL_RECT windowSize = { 0, 0, 70, 50 };
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);*/
	//#################################################################################

	std::system("cls");
	std::cout << std::endl;
	std::cout << "TESTO INTRO" << std::endl;

	return;
}


///-------------------^^ COSE CUSTOM ^^--------------------------
///-------------------^^ COSE CUSTOM ^^--------------------------