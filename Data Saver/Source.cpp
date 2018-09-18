

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
	 system("exit");
	
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

		 system("cls");
		cout << giallo << "[REGISTRAZIONE]" << normale << endl;
		cout << "\n" << endl;
		cout << magenta << "ABenvenuto nuovo utente!" << normale << endl;

		cout << "Vuoi creare un account? (S/n) ";
		cin >> account_scelta;

		if(account_scelta == 's')
		{
			cout << "Inserire User ID -> ";
			 cin >> login.username;
		setpw:
			cout << "Inserire la password -> ";
			 cin >> login.passwd;
			cout << "Inserire di nuovo la password -> ";
			 cin >> login.repasswd;


			if(login.passwd == login.repasswd)
			{

			}
			else
			{
				 system("cls");
				cout << rosso << "[ERRORE] " << normale << "Le password non corrispondono!"<< endl;
				Sleep(1000);
				 system("cls");
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

		 system("cls");
		int tentativi = 3;
		const int LINE = 3;
		fstream buffloginextr("data\\login.ds");
		string outputfile;

		cout << giallo << "[LOGIN]"<< normale << endl;
		cout << "Enter User ID -> ";
		 cin >> login.username;
		tryagain:

		if(tentativi != 0){

		cout << "Enter Your Password -> ";
		 cin >> login.passwd;

		
		
		
		

		for(int i = 1; i <= LINE; i++){ 
			getline(buffloginextr, outputfile);
		}

		
		

		
			if(login.passwd != EncryptDecrypt(outputfile))
			{
				cout << rosso << "[ERRORE] " << normale << "Password sbagliata";
				tentativi--;
				Sleep(1000);
				 system("cls");
				goto tryagain;
			}
			else
			{
				//La pw è coretta
			}
		
		

		}else{ 
			cout << rosso << "[ERRORE] " << normale << "Tentativi Esauriti.... Uscita....";
			Sleep(3000);
			 system("cls");
			quit();
		}

	}
}



void CryptDecryptDirectory()
{
	 system("cls");
	 
	const int LINE = 1;
	fstream buffloginextr("data\\login.ds");
	string username;
	for(int i = 1; i <= LINE; i++)
	{
		getline(buffloginextr, username);
	}
	cout << giallo << "[Menu]" << normale << endl;
	
	bool statuscartella = false; //messa qui sennò viene resettata
scelta:
	system("cls");
	int scelta = 0;
	
	

	cout << endl;
	cout << "Ciao " << magenta << username << normale <<" :)" << endl;
	if(statuscartella == true)
	{


		cout << "La cartella e' " << verde << "Sbloccatta"<< normale << "." << endl;
	}
	else
	{

		cout << "La cartella e' " << rosso << "Bloccata" << normale << "." << endl;
	}
	
	cout << "" << endl;
	cout << celeste << "1. " << normale << "Sblocca la cartella." << endl;
	cout << celeste << "2. " << normale << "Blocca la cartella." << endl;
	cout << celeste << "99. "<< normale << "Esci." << endl;
	cout << endl;
	cout << "Scelta: ";
	cin >> scelta;

	switch(scelta)
	{
	case 99:
		system("cacls \"File_Storage\" /e /p everyone:n");
		system("cls");
		if(statuscartella == true){
			cout << endl;
			cout << endl;
			cout << giallo <<"[ATTENZIONE]"<< normale << " Ehy hai lasciato la cartella sbloccata, la blocchero' io per te :)" << endl;
			Sleep(2000);
			cout << verde << "[INFO] " << normale << "Bloccata! " << endl;
			Sleep(1000);
			cout << endl;
			cout << endl;
		}
		else
		{

		}
		quit();
		break;
	case 1:
		system("cacls \"File_Storage\" /e /p everyone:f");
		system("cls");
		cout << verde << "[INFO] " << normale << "Sbloccando..." << endl;
		Sleep(500);
		cout << verde << "[INFO] " << normale << "Sbloccata! " << endl;
		statuscartella = true;
		Sleep(2000);
		goto scelta;
		break;
	case 2:
		system("cacls \"File_Storage\" /e /p everyone:n");
		system("cls");
		cout << verde << "[INFO] "<< normale << "Bloccando..."<< endl;
		Sleep(500);
		cout << verde << "[INFO] " << normale << "Bloccata! " << endl;
		statuscartella = false;
		Sleep(2000);
		goto scelta;
		break;
	default:
		system("cacls \"File_Storage\" /e /p everyone:n");
		system("cls");
		cout << verde << "[INFO] " << normale << "Bloccando..." << endl;
		Sleep(500);
		cout << verde << "[INFO] " << normale << "Bloccata! "<< endl;
		statuscartella = false;
		Sleep(2000);
		goto scelta;
		break;
	}

	
}

void checkupdate()
{

}

int main()
{
	
	CreaCartella("File_Storage");
	CreaCartella("data");
	 system("cacls \"File_Storage\" /e /p everyone:n");//da cambiare in N o F
	 system("cls");
	printIntro();
	 system("pause"); //TOGLIERE
	GetLogin();
	CryptDecryptDirectory();

	

	


	 system("pause");
	return 0;
}