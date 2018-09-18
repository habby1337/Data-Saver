

#include "include.h" //Tutti i vari include
#include "style.h" //lo stile della scheda con i vari sistemi

using namespace std;



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
	cout << magenta <<"Bye.. Bye.." << normale << endl;
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
		cout << giallo << "[REGISTRAZIONE]" << normale << endl;
		cout << "\n" << endl;
		cout << magenta << "ABenvenuto nuovo utente!" << normale << endl;

		cout << "Vuoi creare un account? (S/n) ";
		cin >> account_scelta;

		if(account_scelta == 's')
		{
			cout << "Inserire User ID -> ";
			std::cin >> login.username;
		setpw:
			cout << "Inserire la password -> ";
			std::cin >> login.passwd;
			cout << "Inserire di nuovo la password -> ";
			std::cin >> login.repasswd;


			if(login.passwd == login.repasswd)
			{

			}
			else
			{
				std::system("cls");
				cout << rosso << "[ERRORE] " << normale << "Le password non corrispondono!"<< endl;
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
				cout << rosso <<"[ERRORE] "<< normale << "Unable to open file"<< endl;
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

		cout << giallo << "[LOGIN]"<< normale << endl;
		cout << "Enter User ID -> ";
		std::cin >> login.username;
		tryagain:

		if(tentativi != 0){

		cout << "Enter Your Password -> ";
		std::cin >> login.passwd;

		
		
		
		

		for(int i = 1; i <= LINE; i++){ 
			getline(buffloginextr, outputfile);
		}

		
		

		
			if(login.passwd != EncryptDecrypt(outputfile))
			{
				cout << rosso << "[ERRORE] " << normale << "Password sbagliata";
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
			cout << rosso << "[ERRORE] " << normale << "Tentativi Esauriti.... Uscita....";
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
	cout << giallo << "[Menu]" << normale << endl;
	
	

	int scelta;

	cout << endl;
	cout << "Ciao " << magenta << username << normale <<" :)" << endl;
	cout << "" << endl;
	cout << celeste << "1. " << normale << "Sblocca la cartella." << endl;
	cout << celeste << "2. " << normale << "Blocca la cartella." << endl;
	cout << celeste << "99. "<< normale << "Esci." << endl;
	cout << endl;
	cout << "Scelta: ";
	std::cin >> scelta;

	switch(scelta)
	{
	case 99:
		quit();
		break;
	case 1:
		std::system("cacls \"File_Storage\" /e /p everyone:f");
		cout << "unlocking..." << endl;;
		break;
	case 2:
		std::system("cacls \"File_Storage\" /e /p everyone:n");
		cout << "locking..." << endl;
		break;
	default:
		std::system("cacls \"File_Storage\" /e /p everyone:n");
		cout << "locking..." << endl;
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