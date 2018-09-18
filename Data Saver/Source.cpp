#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <limits>

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




int GetLogin()
{
	class credential
	{

	public:
		string username, passwd, repasswd;

	private:

	};

	credential login;

	fstream file("data\\login.ds");
	if(!file)
	{


		

		//se il file non esiste
		//fai registrazione
		//TOGLIERE
		cout << "Il File non esiste";

		system("pause");

		

		cout << "Benvenuto Nuovo utente" << endl;

		cout << "User name: ";
		cin >> login.username;
		setpw:
		cout << "Password: ";
		cin >> login.passwd;
		cout << "Re passwd: ";
		cin >> login.repasswd;
		
		cout << login.passwd << endl;
		cout << login.repasswd << endl;

		system("pause");


		if(login.passwd == login.repasswd)
		{
			
		}
		else
		{
			system("cls");
			cout << "le password non corrispondono!" << endl;
			Sleep(1000);
			goto setpw;
			
			

		}
		ofstream bufferlogincred("data\\login.ds");
		if(bufferlogincred.is_open())
		{
			bufferlogincred << login.username;
			bufferlogincred << "\n";
			bufferlogincred << EncryptDecrypt(login.passwd);
			bufferlogincred.close();
		}
		else cout << "Unable to open file";

		
	}
	else
	{
		//TOGLIERE
		cout << "Il File esiste";
		system("pause");
		//va al login

		int tentativi = 3;
		const int LINE = 3;
		fstream buffloginextr("data\\login.ds");
		string outputfile;

		cout << "Login " << endl;
		cout << "Username: ";
		cin >> login.username;
		tryagain:

		if(tentativi != 0){

		cout << "Passwd: ";
		cin >> login.passwd;

		
		
		
		

		for(int i = 1; i <= LINE; i++){ 
			getline(buffloginextr, outputfile);
		}

		
		//TOGLIERE
		cout << EncryptDecrypt(outputfile) << endl;
		cout << login.passwd << endl;

		
			if(login.passwd != EncryptDecrypt(outputfile))
			{
				cout << "password sbagliata";
				tentativi--;
				goto tryagain;
			}
			else
			{
				cout << "password uguale";
			}
		
		

		}else{ 
			cout << "Tentativi Esauriti.... Uscita....";
			system("pause");	//TOGLIERE
			return EXIT_FAILURE;
		}

	}
}



void CryptDecryptDirectory()
{

	const int LINE = 1;
	fstream buffloginextr("data\\login.ds");
	string username;
	for(int i = 1; i <= LINE; i++)
	{
		getline(buffloginextr, username);
	}

	cout << "Ciao " << username << ":)" << endl;

	int scelta;


	cout << "Menu: " << endl;
	cout << "1. Sblocca la cartella." << endl;
	cout << "2. Blocca la cartella." << endl;






}

int main()
{

	CreaCartella("File_Storage");
	CreaCartella("data");
	system("cacls \"File_Storage\" /e /p everyone:n");//da cambiare in N o F
	system("cls");
	
	GetLogin();
	CryptDecryptDirectory();

	

	


	system("pause");
	return 0;
}