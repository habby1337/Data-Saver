

#include "include.h" //Tutti i vari include
#include "style.h" //lo stile della scheda con i vari sistemi

using namespace std;


//Velocizza l'utilizzo della funzione system
void pulire()
{
	system("cls");
}

//Controlla se la cartella esiste, nel caso non esistesse la crea
void CreaCartella(const char * path)
{ if(!CreateDirectory(path, NULL)){ return; } }


//Sistema di criptografia utilizzato
string EncryptDecrypt(string toEncrypt) 
{
	char key[3] = { 'A', 'Z', 'V' }; //Chiave di criptatura [PERICOLOSO SE SI GUARDA L'ASSEMBLY SI TROVANO LE CHIAVI]
	string output = toEncrypt;

	for(int i = 0; i < toEncrypt.size(); i++){ 
		output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
	}
	return output;
}


//Semplicizza l'utilizzo di system cacls
void cacls(string folder, string state) 
{
	//system("cacls \"data\" /e /p everyone:n");//da cambiare in N o F
	//N = Nega
	//F = Accedi
	system(("cacls \"" + folder + "\" /e /p everyone:" + state ).c_str());
}


//Uscita dal programma
void quit()
{
	cout << magenta <<"Bye.. Bye.." << normale << endl;
	Sleep(3000);
	exit(EXIT_SUCCESS);
}


//Capisce se esiste già un account se si fa fare il login
void GetLogin() 
{
	//classe che contiene le variablili credenziali 
	class credential	
	{
	public:
		string username, passwd, repasswd;
	};

	credential login;

	//prepara il file login.ds
	fstream file("data\\login.ds");	

	//Convalida esistenza file login.ds , per capire se esiste già un account
	if(!file)	
	{
		//Crea la cartella "data"
		CreaCartella("data"); 
		Sleep(500);
		char account_scelta;
		
		pulire();
		cout << giallo << "[REGISTRAZIONE]" << normale << endl;
		cout << "\n" << endl;
		cout << magenta << "ABenvenuto nuovo utente!" << normale << endl;
		cout << "Vuoi creare un account? (S/n) ";
		cin >> account_scelta;

		//scelta se creare o no l'account
		if(account_scelta == 's')	
		{
			ofstream bufferlogincred("data\\login.ds");
			
			cout << "Inserire User ID -> ";
			 cin >> login.username;
		setpw:
			cout << "Inserire la password -> ";
			 cin >> login.passwd;
			cout << "Inserire di nuovo la password -> ";
			 cin >> login.repasswd;

			//convalida le password
			if(login.passwd == login.repasswd)
			{ /*uguali*/ }
			else
			{	//non uguali
				pulire();
				cout << rosso << "[ERRORE] " << normale << "Le password non corrispondono!"<< endl;
				Sleep(1000);
				pulire();
				goto setpw;//lo riporta alla scelta delle passwd
			}

			//convalida se il file è pronto per ricevere dei dati
			if(bufferlogincred.is_open())
			{
				bufferlogincred << login.username;
				bufferlogincred << "\n";
				bufferlogincred << EncryptDecrypt(login.passwd);
				bufferlogincred.close();
				cacls("data", "n");
			}
			else
			{	//Il file non può ricevere input
				cout << rosso <<"[ERRORE] "<< normale << "Unable to open file"<< endl;
			}
			
		}
		//se la scelta dell' account è no
		else if(account_scelta == 'n')
		{
			system("rd /S /Q data");
			quit();

		}else //se l'input inserito non è valido
		{ 
			cout << rosso << "[ERRORE] " << normale << "Input non valido!" << endl;
			Sleep(2000);
			system("rd /S /Q data");
			quit();
		}				
	}
	//se il file "login.ds" esiste fa il login anziché la registrazione
	else
	{
		pulire();
		int tentativi = 3; //Tentativi prima della chiusura di sicurezza del programma
		const int LINE = 3; //la linea del file da leggere
		fstream buffloginextr("data\\login.ds"); //prepara di nuovo il file login.ds
		string outputfile;

		cout << giallo << "[LOGIN]"<< normale << endl;
		cout << "Enter User ID -> ";
		 cin >> login.username;
		tryagain:

		//Check dei tentativi rimasti
		if(tentativi != 0){

		cout << "Enter Your Password -> ";
		 cin >> login.passwd;

		for(int i = 1; i <= LINE; i++){ 
			getline(buffloginextr, outputfile);
		}

			//Convalida se la password è uguale a quella salvata
			if(login.passwd != EncryptDecrypt(outputfile))
			{
				cout << rosso << "[ERRORE] " << normale << "Password sbagliata";
				tentativi--;
				Sleep(1000);
				 pulire();
				goto tryagain;
			}
			else {/*La pw è coretta*/ }
		}
		else{ //Nel caso che i tentativi siano finiti
			cout << rosso << "[ERRORE] " << normale << "Tentativi Esauriti.... Uscita....";
			Sleep(3000);
			pulire();
			quit();
		}
	}
}


//Sbloccaggio o Bloccaggio della directory di salvataggio file 
void CryptDecryptDirectory()
{
	pulire();
	cacls("data", "f");

	 
	const int LINE = 1;
	fstream buffloginextr("data\\login.ds"); //Preparazione file
	string username;

	for(int i = 1; i <= LINE; i++)
	{
		getline(buffloginextr, username);
	}
	cacls("data", "n");
	
	cout << giallo << "[Menu]" << normale << endl;
	
	bool statuscartella = false; //messa qui sennò viene resettata

scelta:

	pulire();
	int scelta = 0;
	
	cout << endl;
	cout << "Ciao " << magenta << username << normale <<" :)" << endl;

	//Convalida se la cartella è bloccata o sbloccata
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

	//Switch decisioni riguardo la cartella di salvataggio dati 
	switch(scelta)
	{
	case 99: //Uscita del programma
		cacls("File_Storage", "n");
		pulire();

		//Convalida se la cartella è bloccata al momento dell'uscita
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
		else{ /*Tutto okei, la cartella è bloccata*/ }
		quit();
		break;


	case 1: //La cartella viene Sbloccata
		cacls("File_Storage", "f");
		pulire();
		cout << verde << "[INFO] " << normale << "Sbloccando..." << endl;
		Sleep(500);
		cout << verde << "[INFO] " << normale << "Sbloccata! " << endl;
		statuscartella = true;
		Sleep(2000);
		goto scelta;
		break;


	case 2: //La catella viene Bloccata
		cacls("File_Storage", "n");
		pulire();
		cout << verde << "[INFO] "<< normale << "Bloccando..."<< endl;
		Sleep(500);
		cout << verde << "[INFO] " << normale << "Bloccata! " << endl;
		statuscartella = false;
		Sleep(2000);
		goto scelta;
		break;


	default: //Opzione di default, per raggioni di sicurezza la cartella viene bloccata se l'input è diverso da "1"
		cacls("File_Storage", "n");
		pulire();
		cout << verde << "[INFO] " << normale << "Bloccando..." << endl;
		Sleep(500);
		cout << verde << "[INFO] " << normale << "Bloccata! "<< endl;
		statuscartella = false;
		Sleep(2000);
		goto scelta;
		break;
	}
}


//Utilizzato per convalidare nuove versioni del programma
void Checkupdate()
{

}


//Funzione main
int main()
{
	
	//Output della intro (la funzione si trova in style.h)
	printIntro();

	//Funzione di login o register
	GetLogin();

	// -_- non credo di doverla spiegare
	CreaCartella("File_Storage");

	//Funzione semplificata di system(cacls )
	cacls("File_Storage", "n");

	//Pulizia schermo
	pulire();

	//Funzione base del programma
	CryptDecryptDirectory();

	//Check degli update
	Checkupdate();
	

	

	 exit(EXIT_SUCCESS);//Uscita con successo

	return 0;
}