

#include "include.h" //Tutti i vari include
#include "style.h" //lo stile della scheda con i vari sistemi

using namespace std;


//classe che contiene le variablili credenziali 
class credential
{
public:
	string username, passwd, repasswd;
	string  folder_name;
};

credential login;

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
	std::cout << magenta <<"Bye.. Bye.." << normale << endl;
	Sleep(3000);
	exit(EXIT_SUCCESS);
}

string space2underscore(string text)
{
	for(int i = 0; i < text.length(); i++)
	{
		if(isspace(text[i]))
			text[i] = '_';
	}
	return text;
}

//Capisce se esiste già un account se si fa fare il login
void GetLogin() 
{
	

	

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
		std::cout << giallo << "[REGISTRAZIONE]" << normale << endl;
		std::cout << "\n" << endl;
		std::cout << magenta << "ABenvenuto nuovo utente!" << normale << endl;
		std::cout << "Vuoi creare un account? (S/n) ";
		cin >> account_scelta;


		//scelta se creare o no l'account
		if(account_scelta == 's')	
		{
			ofstream bufferlogincred("data\\login.ds");
			
			
			std::cout << "Inserire nome della cartella -> ";
			cin.ignore();
			std::getline(std::cin, login.folder_name);
			
				


			std::cout << "Inserire User ID -> ";
			 cin >> login.username;
		setpw:
			std::cout << "Inserire la password -> ";
			 cin >> login.passwd;

			 char c = ' ';
			 while(c != 13) //Fa un loop finche non viene premuto il tasto "ENTER"
			 {
				 c = _getch();
				 if(c == 13)
					 break;

				 if(c == 8)
				 {
					 if(login.passwd.size() != 0)   //Cancella solo se c'è un input 
					 {
						 cout << "\b \b";
						 login.passwd.erase(login.passwd.size() - 1);
					 }
				 }

				 if((c > 47 && c < 58) || (c > 64 && c < 91) || (c > 96 && c < 123))  //ASCii per integer e alfanumerici 
				 {
					 login.passwd += c;
					 cout << "*";
				 }
			 }


			std::cout << "Inserire di nuovo la password -> ";
			 cin >> login.repasswd;
			 
			 char c1 = ' ';
			 while(c1 != 13) //Fa un loop finche non viene premuto il tasto "ENTER"
			 {
				 c1 = _getch();
				 if(c1 == 13)
					 break;

				 if(c1 == 8)
				 {
					 if(login.repasswd.size() != 0)   //Cancella solo se c'è un input 
					 {
						 cout << "\b \b";
						 login.repasswd.erase(login.repasswd.size() - 1);
					 }
				 }

				 if((c1 > 47 && c1 < 58) || (c1 > 64 && c1 < 91) || (c1 > 96 && c1 < 123))  //ASCii per integer e alfanumerici 
				 {
					 login.repasswd += c1;
					 cout << "*";
				 }
			 }




			//convalida le password
			if(login.passwd == login.repasswd)
			{ /*uguali*/ }
			else
			{	//non uguali
				pulire();
				std::cout << rosso << "[ERRORE] " << normale << "Le password non corrispondono!"<< endl;
				Sleep(1000);
				pulire();
				goto setpw;//lo riporta alla scelta delle passwd
			}

			//convalida se il file è pronto per ricevere dei dati
			if(bufferlogincred.is_open())
			{
				bufferlogincred << space2underscore(login.folder_name);
				bufferlogincred << "\n";
				bufferlogincred << login.username;
				bufferlogincred << "\n";
				bufferlogincred << EncryptDecrypt(login.passwd);
				bufferlogincred.close();
				cacls("data", "n");
			}
			else
			{	//Il file non può ricevere input
				std::cout << rosso <<"[ERRORE] "<< normale << "Unable to open file"<< endl;
			}
			
		}
		//se la scelta dell' account è no
		else if(account_scelta == 'n')
		{
			system("rd /S /Q data");
			quit();

		}else //se l'input inserito non è valido
		{ 
			std::cout << rosso << "[ERRORE] " << normale << "Input non valido!" << endl;
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
		

	tryagain:
		std::cout << giallo << "[LOGIN]"<< normale << endl;
		std::cout << "Enter User ID -> ";
		cin >> login.username;
		
		 const int LINE = 2; //la linea del file da leggere
		 fstream buffusername("data\\login.ds"); //prepara di nuovo il file login.ds
		 string outputUsername;

		 for(int i = 1; i <= LINE; i++)
		 {
			 getline(buffusername, outputUsername);
		 }

		 //Convalida se la password è uguale a quella salvata
		 if(login.username != outputUsername)
		 {
			 std::cout << rosso << "[ERRORE] " << normale << "UserName sbagliato";
			 tentativi--;
			 Sleep(1000);
			 pulire();
			 goto tryagain;
		 }
		 else {/*l'username è coretto*/ }

		//Check dei tentativi rimasti
		if(tentativi != 0){

		std::cout << "Enter Your Password -> ";

		 char c2 = ' ';
		 while(c2 != 13) //Fa un loop finche non viene premuto il tasto "ENTER"
		 {
			 c2 = _getch();
			 if(c2 == 13)
				 break;

			 if(c2 == 8)
			 {
				 if(login.passwd.size() != 0)   //Cancella solo se c'è un input 
				 {
					 cout << "\b \b";
					 login.passwd.erase(login.passwd.size() - 1);
				 }
			 }

			 if((c2 > 47 && c2 < 58) || (c2 > 64 && c2 < 91) || (c2 > 96 && c2 < 123))  //ASCii per integer e alfanumerici 
			 {
				 login.passwd += c2;
				 cout << "*";
			 }
		 }
		
		 const int LINE = 3; //la linea del file da leggere
		 fstream buffloginextr("data\\login.ds"); //prepara di nuovo il file login.ds
		 string outputfile;

		for(int i = 1; i <= LINE; i++){ 
			getline(buffloginextr, outputfile);
		}


			//Convalida se la password è uguale a quella salvata
			if(EncryptDecrypt(login.passwd) != outputfile)
			{
				std::cout << rosso << "[ERRORE] " << normale << "Password sbagliata";
				tentativi--;
				Sleep(1000);
				pulire();
				goto tryagain;
			}
			else {/*La pw è coretta*/ }
		}
		else{ //Nel caso che i tentativi siano finiti
			std::cout << rosso << "[ERRORE] " << normale << "Tentativi Esauriti.... Uscita....";
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

	
	

	const int LINE_FolderName = 1;
	fstream buffFolderName("data\\login.ds"); //Preparazione file
	//Prende il nome della cartella
	for(int i = 1; i <= LINE_FolderName; i++)
	{
		getline(buffFolderName, login.folder_name);
	}


	const char *folder = login.folder_name.c_str();
	cout << folder << endl;
	CreaCartella(folder);


	const int LINE_Username = 2;
	fstream buffUsername("data\\login.ds"); //Preparazione file
	string username;

	for(int i = 1; i <= LINE_Username; i++)
	{
		getline(buffUsername, username);
	}
	cacls("data", "n");
	
	std::cout << giallo << "[Menu]" << normale << endl;
	
	bool statuscartella = false; //messa qui sennò viene resettata

scelta:

	pulire();
	int scelta = 0;
	
	std::cout << endl;
	std::cout << "Ciao " << magenta << username << normale <<" :)" << endl;

	//Convalida se la cartella è bloccata o sbloccata
	if(statuscartella == true)
	{
		std::cout << "La cartella e' " << verde << "Sbloccatta"<< normale << "." << endl;
	}
	else
	{
		std::cout << "La cartella e' " << rosso << "Bloccata" << normale << "." << endl;
	}
	
	std::cout << "" << endl;
	std::cout << celeste << "1. " << normale << "Sblocca la cartella." << endl;
	std::cout << celeste << "2. " << normale << "Blocca la cartella." << endl;
	std::cout << celeste << "99. "<< normale << "Esci." << endl;
	std::cout << endl;
	std::cout << "Scelta: ";
	cin >> scelta;

	//Switch decisioni riguardo la cartella di salvataggio dati 
	switch(scelta)
	{
	case 99: //Uscita del programma
		cacls(login.folder_name, "n");
		pulire();

		//Convalida se la cartella è bloccata al momento dell'uscita
		if(statuscartella == true){
			std::cout << endl;
			std::cout << endl;
			std::cout << giallo <<"[ATTENZIONE]"<< normale << " Ehy hai lasciato la cartella sbloccata, la blocchero' io per te :)" << endl;
			Sleep(2000);
			std::cout << verde << "[INFO] " << normale << "Bloccata! " << endl;
			Sleep(1000);
			std::cout << endl;
			std::cout << endl;
		}
		else{ /*Tutto okei, la cartella è bloccata*/ }
		quit();
		break;


	case 1: //La cartella viene Sbloccata
		cacls(login.folder_name, "f");
		pulire();
		std::cout << verde << "[INFO] " << normale << "Sbloccando..." << endl;
		Sleep(500);
		std::cout << verde << "[INFO] " << normale << "Sbloccata! " << endl;
		statuscartella = true;
		Sleep(2000);
		goto scelta;
		break;


	case 2: //La catella viene Bloccata
		cacls(login.folder_name, "n");
		pulire();
		std::cout << verde << "[INFO] "<< normale << "Bloccando..."<< endl;
		Sleep(500);
		std::cout << verde << "[INFO] " << normale << "Bloccata! " << endl;
		statuscartella = false;
		Sleep(2000);
		goto scelta;
		break;


	default: //Opzione di default, per raggioni di sicurezza la cartella viene bloccata se l'input è diverso da "1"
		cacls(login.folder_name, "n");
		pulire();
		std::cout << verde << "[INFO] " << normale << "Bloccando..." << endl;
		Sleep(500);
		std::cout << verde << "[INFO] " << normale << "Bloccata! "<< endl;
		statuscartella = false;
		Sleep(2000);
		goto scelta;
		break;
	}
}


//Utilizzato per convalidare nuove versioni del programma
void Checkupdate()
{
	CURL* buffer;
	CURLcode risultato;

	buffer = curl_easy_init();
	curl_easy_setopt(buffer, CURLOPT_URL, "https://habby1337.github.io/datasaver/version.txt");
	curl_easy_setopt(buffer, CURLOPT_HEADER, 1);
	curl_easy_setopt(buffer, CURLOPT_WRITEDATA, NULL);
	curl_easy_setopt(buffer, CURLOPT_WRITEFUNCTION, NULL);



	risultato = curl_easy_perform(buffer);

	curl_easy_cleanup(buffer);


	//cout << risultato;


}


//Funzione main
int main()
{
	/*
	//Output della intro (la funzione si trova in style.h)
	printIntro();

	//Funzione di login o register
	GetLogin();

	//Funzione semplificata di system(cacls )
	cacls(login.folder_name, "n");

	//Pulizia schermo
	pulire();

	//Funzione base del programma
	CryptDecryptDirectory();
	*/
	//Check degli update
	Checkupdate();

	system("pause"); //TOGLIERE
	
	exit(EXIT_SUCCESS);//Uscita con successo

	return 0;
}