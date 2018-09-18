

#include "include.h" //Tutti i vari include
#include "style.h" //lo stile della scheda con i vari sistemi

using namespace std;

char rosso[] = { 0x1b, '[', '1', ';', '9', '1', 'm', 0 };
char normale[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
char giallo[] = { 0x1b, '[', '2', ';', '9', '3', 'm', 0 };
char magenta[] = { 0x1b, '[', '2', ';', '9', '5', 'm', 0 };
char celeste[] = { 0x1b, '[', '2', ';', '9', '6', 'm', 0 };

//Controlla se la cartella esiste, nel caso non esistesse la crea
void CreaCartella(const char * path)
{
	if(!CreateDirectory(path, NULL))
	{
		return;
	}
}


string EncryptDecrypt(string toEncrypt)
{
	char key[3] = { 'K', 'C', 'Q' }; //Chiave di criptatura
	string output = toEncrypt;

	for(int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

	
	return output;
}

void quit()
{
	std::cout << magenta <<"Bye.. Bye.." << normale << endl;
	Sleep(3000);
	std::system("exit");
	
}


void GetLogin()
{
	

	class credential
	{
	public:
		string username, passwd, repasswd;

	};


	credential login;

	fstream file("data\\login.ds");
	if(!file)
	{
		char account_scelta;
		ofstream bufferlogincred("data\\login.ds");

		std::system("cls");
		std::cout << giallo << "[REGISTRAZIONE]" << normale << endl;
		std::cout << "\n" << endl;
		std::cout << magenta << "ABenvenuto nuovo utente!" << normale << endl;

		std::cout << "Vuoi creare un account? (S/n) ";
		std::cin >> account_scelta;

		if(account_scelta == 's')
		{
			std::cout << "Inserire User ID -> ";
			std::cin >> login.username;
		setpw:
			std::cout << "Inserire la password -> ";
			std::cin >> login.passwd;
			std::cout << "Inserire di nuovo la password -> ";
			std::cin >> login.repasswd;


			if(login.passwd == login.repasswd)
			{

			}
			else
			{
				std::system("cls");
				std::cout << rosso << "[ERRORE] " << normale << "Le password non corrispondono!"<< endl;
				Sleep(1000);
				std::system("cls");
				goto setpw;



			}

			if(bufferlogincred.is_open())
			{
				bufferlogincred << login.username;
				bufferlogincred << "\n";
				bufferlogincred << EncryptDecrypt(login.passwd);
				bufferlogincred.close();
			}
			else
			{
				std::cout << rosso <<"[ERRORE] "<< normale << "Unable to open file"<< endl;
			}
		}
		else if(account_scelta == 'n')
		{
			quit();
		}else{
		}

		
			
		

		
		
	}
	else
	{

		std::system("cls");
		int tentativi = 3;
		const int LINE = 3;
		fstream buffloginextr("data\\login.ds");
		string outputfile;

		std::cout << giallo << "[LOGIN]"<< normale << endl;
		std::cout << "Enter User ID -> ";
		std::cin >> login.username;
		tryagain:

		if(tentativi != 0){

		std::cout << "Enter Your Password -> ";
		std::cin >> login.passwd;

		
		
		
		

		for(int i = 1; i <= LINE; i++){ 
			getline(buffloginextr, outputfile);
		}

		
		

		
			if(login.passwd != EncryptDecrypt(outputfile))
			{
				std::cout << rosso << "[ERRORE] " << normale << "Password sbagliata";
				tentativi--;
				Sleep(1000);
				std::system("cls");
				goto tryagain;
			}
			else
			{
				//La pw è coretta
			}
		
		

		}else{ 
			std::cout << rosso << "[ERRORE] " << normale << "Tentativi Esauriti.... Uscita....";
			Sleep(3000);
			std::system("cls");
			quit();
		}

	}
}



void CryptDecryptDirectory()
{
	std::system("cls");
	const int LINE = 1;
	fstream buffloginextr("data\\login.ds");
	string username;
	for(int i = 1; i <= LINE; i++)
	{
		getline(buffloginextr, username);
	}
	std::cout << giallo << "[Menu]" << normale << endl;
	
	

	int scelta;

	std::cout << endl;
	std::cout << "Ciao " << magenta << username << normale <<" :)" << endl;
	std::cout << "" << endl;
	std::cout << celeste << "1. " << normale << "Sblocca la cartella." << endl;
	std::cout << celeste << "2. " << normale << "Blocca la cartella." << endl;
	std::cout << celeste << "99. "<< normale << "Esci." << endl;
	std::cout << endl;
	std::cout << "Scelta: ";
	std::cin >> scelta;

	switch(scelta)
	{
	case 99:
		quit();
		break;
	case 1:
		std::system("cacls \"File_Storage\" /e /p everyone:f");
		std::cout << "unlocking..." << endl;;
		break;
	case 2:
		std::system("cacls \"File_Storage\" /e /p everyone:n");
		std::cout << "locking..." << endl;
		break;
	default:
		std::system("cacls \"File_Storage\" /e /p everyone:n");
		std::cout << "locking..." << endl;
		break;
	}

	
}

int main()
{
	
	CreaCartella("File_Storage");
	CreaCartella("data");
	std::system("cacls \"File_Storage\" /e /p everyone:n");//da cambiare in N o F
	std::system("cls");
	printIntro();
	std::system("pause"); //TOGLIERE
	GetLogin();
	CryptDecryptDirectory();

	

	


	std::system("pause");
	return 0;
}