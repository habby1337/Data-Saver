#pragma once

char rosso[] = { 0x1b, '[', '1', ';', '9', '1', 'm', 0 };
char normale[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
char giallo[] = { 0x1b, '[', '2', ';', '9', '3', 'm', 0 };
char magenta[] = { 0x1b, '[', '2', ';', '9', '5', 'm', 0 };
char celeste[] = { 0x1b, '[', '2', ';', '9', '6', 'm', 0 };
char verde[] = { 0x1b, '[', '2', ';', '9', '2', 'm', 0 };

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
	SetConsoleTitle("Data Saver [Made with <3 by Fede.Tensi aka Habby]");

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
	 std::cout <<  std::endl;
		 std::cout << giallo <<"     ____  _____ "<< normale <<  std::endl;
		 std::cout << giallo <<"    / __ \\/ ___/ "<< normale <<  std::endl;
		 std::cout << celeste <<"   / / / /\__  \\   "<< normale <<  std::endl;
		 std::cout << magenta <<"  / /_/ /___/ /   "<< normale <<  std::endl;
		 std::cout << magenta <<" /_____//____/    "<< normale <<  std::endl;
		 std::cout << "                  Data Saver..." <<  std::endl;
		 std::cout << "                    made with " << rosso << "<3" << normale << " by " << magenta << "Habby" << normale << std::endl;
	 std::cout <<  std::endl;
	 std::cout <<  std::endl;
	 std::cout <<  std::endl;
	 std::cout <<  std::endl;

	
	return;
}


///-------------------^^ COSE CUSTOM ^^--------------------------
///-------------------^^ COSE CUSTOM ^^--------------------------