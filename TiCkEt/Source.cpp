#pragma once
#include<string>
#include<string.h>
#include<iostream>
#include <cstdlib>
#include<fstream>
#include<vector>
using namespace std;

//Interfata
class File
{
public:
	virtual void writeFile(fstream& file) = 0;
	virtual void readFile(fstream& file) = 0;
};

class Bilet : public File
{
private:
	int pretBilet;

	// tipBilet se refera la zona la care a fost cumparat biletul (ex Categoria 1, Categoria 2, Peluza)
	char tipBilet;

	int rand;

	int loc;

	static int id;

	int idBilet;

	friend class Eveniment;
public:
	//constructor fara parametri
	Bilet()
	{
		pretBilet = 0;
		tipBilet = NULL;
		rand = 0;
		loc = 0;
		idBilet = ++id;
	}

	//constructor cu parametri
	Bilet(char tipBilet, int pret, int rand, int loc) :Bilet()
	{
		this->tipBilet = tipBilet;
		this->pretBilet = pret;
		this->tipBilet = tipBilet;
		this->rand = rand;
		this->loc = loc;
	}

	//constructor de copiere
	Bilet(const Bilet& b) :Bilet()
	{
		this->tipBilet = b.tipBilet;
		this->pretBilet = b.pretBilet;
		this->rand = b.rand;
		this->loc = b.loc;
	}

	//getter pret bilet

	int getPb()
	{
		return this->pretBilet;
	}
	//getter loc
	int getLoc()
	{
		return this->loc;
	}
	//getter tip Bilet
	char getTp()
	{
		return tipBilet;
	}

	//getter rand
	int getRand() {
		return rand;
	}

	//setter  pret Bilet
	void setPb(int pretBilet)
	{
		this->pretBilet = pretBilet;
	}
	//setter nr Bilet
	void setLoc(int loc)
	{
		this->loc = loc;
	}

	// Setter rand
	void setRand(int) {
		this->rand = rand;
	}

	//setter tip Bilet
	void setTp(char tipBilet)
	{
		this->tipBilet = tipBilet;
	}

	~Bilet()
	{
		id--;
	}

	void writeFile(fstream& file)
	{
		//int pretBilet;
		file.write((char*)&this->pretBilet, sizeof(int));
	
		//char tipBilet;
		file.write((char*)&this->tipBilet, sizeof(char));

		//int rand;
		file.write((char*)&this->rand, sizeof(int));

		//int loc;
		file.write((char*)&this->loc, sizeof(int));
		
		//int idBilet;
		file.write((char*)&this->idBilet, sizeof(int));
	}

	void readFile(fstream& file)
	{
		//citire int pretBilet;
		file.read((char*)&this->pretBilet, sizeof(int));

		//char tipBilet;
		file.read((char*)&this->tipBilet, sizeof(char));

		//int rand;
		file.read((char*)&this->rand, sizeof(int));

		//int loc;
		file.read((char*)&this->loc, sizeof(int));

		//int idBilet;
		file.read((char*)&this->idBilet, sizeof(int));
	}
	friend ostream& operator<<(ostream& out, Bilet& B);
	friend istream& operator>>(istream& in, Bilet& B);
	friend ofstream& operator<<(ofstream& out, const Bilet& B);
	friend ifstream& operator>>(ifstream& in, Bilet& B);

};

int Bilet::id = 0;
//operator <<
ostream& operator<<(ostream& out, Bilet& B)
{
	out << "============ BILET #" << B.idBilet << "============\n";
	out << "Pretul biletului este:" << B.pretBilet << endl;
	out << "Tipul biletului este:" << B.tipBilet << endl;
	out << "Locul biletului este:" << B.loc << endl;
	out << "Randul biletului este:" << B.rand << endl;
	out << "================================\n";
	return out;
}

istream& operator >> (istream& in, Bilet& B) {


	cout << "Pretul biletului este: ";
	in >> B.pretBilet;

	cout << "Tipul biletului este: ";

	in >> B.tipBilet;

	cout << "Locul biletului este: ";
	in >> B.loc;

	cout << "Randul biletului este: ";
	in >> B.rand;

	return in;
}
	ofstream& operator<<(ofstream & out, const Bilet& B)
	{
		out<< B.pretBilet;
		out << B.tipBilet;;
		out<< B.rand;
		out<< B.loc;
		out << B.idBilet;
		return out;
	}

	ifstream& operator>>(ifstream& in, Bilet&B)
	{
		in >> B.pretBilet;
		in >> B.tipBilet;
		in >> B.rand;
		in >> B.loc;
		in >> B.idBilet;
		return in;
		
	}

class Locatie : public File
{
private:

	// Numarul maxim de locuri din locatie
	int nrMaximLocuri;

	// Nr de zone

	int nrZone;

	// Array ce retine numarul de randuri pentru fiecare locatie in parte

	// nrRanduri[i] = numarul de randuri pe care le are are zona cu numarul de identificare i 

	int* nrRanduri;

	// Array ce retine denumirile zonelor

	char** zone;

	// Matrice (array bidimensional) ce retine numarul de scaune de pe un anumit rand dintr-o anumita zona

	// nrScaune[i][j] = numarul de scaune pe care le are randul j din zona i

	int** nrScaune;
	friend class Eveniment;

public:
	//constructor fara parametri
	Locatie()
	{
		nrMaximLocuri = 0;
		nrZone = 0;
		nrRanduri = NULL;
		nrScaune = NULL;
		zone = NULL;
	}

	//constructor cu parametri
	Locatie(int nrMaximLocuri, int nrZone, int* nrRanduri, char** zone, int** nrScaune)
	{
		this->nrMaximLocuri = nrMaximLocuri;
		this->nrZone = nrZone;
		this->nrRanduri = new int[nrZone];
		for (int i = 0; i < nrZone; i++) {
			this->nrRanduri[i] = nrRanduri[i];
		}
		zone = new char* [nrZone];
		for (int i = 0; i < nrZone; i++) {
			this->zone[i] = new char[strlen(zone[i]) + 1];
			strcpy(this->zone[i], zone[i]);
		}

		this->nrScaune = new int* [nrZone];
		for (int i = 0; i < nrZone; i++) {
			this->nrScaune[i] = new int[this->nrRanduri[i]];
			for (int j = 0; j < this->nrRanduri[i]; j++) {
				this->nrScaune[i][j] = nrScaune[i][j];
			}
		}

	}

	//constructor de copiere
	Locatie(const Locatie& l)
	{

		this->nrMaximLocuri = l.nrMaximLocuri;
		this->nrZone = l.nrZone;
		this->nrRanduri = new int[l.nrZone];
		for (int i = 0; i < l.nrZone; i++) {
			this->nrRanduri[i] = l.nrRanduri[i];
		}

		zone = new char* [l.nrZone];
		for (int i = 0; i < l.nrZone; i++) {
			this->zone[i] = new char[strlen(l.zone[i]) + 1];
			strcpy(this->zone[i], l.zone[i]);
		}

		this->nrScaune = new int* [l.nrZone];
		for (int i = 0; i < l.nrZone; i++) {
			this->nrScaune[i] = new int[this->nrRanduri[i]];
			for (int j = 0; j < this->nrRanduri[i]; j++) {
				this->nrScaune[i][j] = l.nrScaune[i][j];
			}
		}
	}

	//getter nr maxim locuri
	int getMaximLocuri() {
		return this->nrMaximLocuri;
	}

	////getter nrzone
	int getNrZone()
	{
		return this->nrZone;
	}

	//getter nrRanduri
	int* getnrRanduri()
	{
		return nrRanduri;
	}
	//getter zone
	char** getzone()
	{
		return zone;
	}
	//getter nrScaune
	int** getNrScaune()
	{
		return nrScaune;
	}
	//setter nr max locuri
	void setmax(int max)
	{
		nrMaximLocuri = max;
	}
	//setter nr zone
	void setnrzone(int zn)
	{
		nrZone = zn;
	}
	//setter nrRanduri
	void setnrRanduri(int* rand)
	{
		if (nrRanduri != nullptr)
		{
			delete[]this->nrRanduri;
		}
		for (int i = 0; i < *rand; i++)
			this->nrRanduri[i] = nrRanduri[i];
	}
	//setter zone
	void setzone(char** zon)
	{
		if (zone != nullptr)
		{
			delete[]zone;
		}
		this->zone = zon;
	}
	//setter nrScaune
	void setnrScaune(int** scaun)
	{
		if (nrScaune != nullptr)
		{
			delete[]nrScaune;
		}
		nrScaune = scaun;
	}

	//destrucor
	~Locatie()
	{

		if (nrRanduri != 0)
		{
			delete[]this->nrRanduri;
		}
		this->nrRanduri = nullptr;

		//Dezalocare memorie alocata dinamic pentru zone
		for (int i = 0; i < nrZone; i++) {
			delete[] this->zone[i];
		}

		delete[] this->zone;


		// Dealocare memorie alocata dinamic pentru nr scaune

		for (int i = 0; i < nrZone; i++) {
			delete[] this->nrScaune[i];
		}

		delete[] this->nrScaune;

	}

	//operator=
	Locatie& operator=(const Locatie& l)
	{
		if (nrMaximLocuri > 0)
		{
			this->nrMaximLocuri = l.nrMaximLocuri;
		}
		else
			nrMaximLocuri = 0;

		if (nrZone > 0)
		{
			this->nrZone = l.nrZone;
		}
		else nrZone = 0;

		delete[] this->nrRanduri;

		this->nrRanduri = new int[l.nrZone];
		for (int i = 0; i < l.nrZone; i++) {
			this->nrRanduri[i] = l.nrRanduri[i];
		}

		delete[] this->zone;

		zone = new char* [l.nrZone];
		for (int i = 0; i < l.nrZone; i++) {
			this->zone[i] = new char[strlen(l.zone[i]) + 1];
			strcpy(this->zone[i], l.zone[i]);
		}

		delete[] this->nrScaune;

		this->nrScaune = new int* [l.nrZone];
		for (int i = 0; i < l.nrZone; i++) {
			this->nrScaune[i] = new int[this->nrRanduri[i]];
			for (int j = 0; j < this->nrRanduri[i]; j++) {
				this->nrScaune[i][j] = l.nrScaune[i][j];
			}
		}
		return (*this);
	}

	void writeFile(fstream& file)
	{
		//int nrMaximLocuri;
		file.write((char*)&this->nrMaximLocuri, sizeof(int));
		
		//int nrZone;
		file.write((char*)&this->nrZone, sizeof(int));
		
		//int* nrRanduri;
		file.write((char*)&nrZone, sizeof(int));
		
		//char** zone;
		file.write((char*)&zone, sizeof(char));

		//int** nrScaune;
		file.write((char*)&nrScaune, sizeof(int));
	}

	void readFile(fstream& file)
	{
		//int nrMaximLocuri;
		file.read((char*)&this->nrMaximLocuri, sizeof(int));

		//int nrZone;
		file.read((char*)&this->nrZone, sizeof(int));

		//int* nrRanduri;
		file.read((char*)&nrZone, sizeof(int));

		//char** zone;
		file.read((char*)&zone, sizeof(char));

		//int** nrScaune;
		file.read((char*)&nrScaune, sizeof(int));
	}

	friend ostream& operator<<(ostream& out, Locatie& L);
	friend istream& operator>>(istream& in, Locatie& L);
	friend ofstream& operator<<(ofstream& out, Locatie& L);
	friend ifstream& operator>>(ifstream& in, Locatie& L);
};

//operator <<

ostream& operator << (ostream& out, Locatie& L)
{



	out << "===============LOCATIE===============\n";
	out << "Nr maxim de locuri :" << L.nrMaximLocuri << endl;
	out << "Numarul de zone :" << L.nrZone << endl;

	for (int i = 0; i < L.nrZone; i++) {

		out << "Zona " << L.zone[i] << endl;
		out << "Pentru zona curenta exista un numar de randuri egal cu  " << L.nrRanduri[i] << endl;

		out << "Numarul de scaune per rand este urmatorul:" << endl;


		for (int j = 0; j < L.nrRanduri[i]; j++) {
			cout << "Randul cu numarul " << j << " : " << L.nrScaune[i][j] << endl;
		}

	}

	out << "===============LOCATIE===============\n";

	return out;
}
//operator >>
istream& operator >> (istream& in, Locatie& L)
{
	cout << "Nr maxim de locuri: ";
	in >> L.nrMaximLocuri;
	cout << "Nr zone: ";
	in >> L.nrZone;

	L.nrRanduri = new int[L.nrZone + 1];
	L.nrScaune = new int* [L.nrZone + 1];
	L.zone = new char* [L.nrZone + 1];

	for (int i = 0; i < L.nrZone; i++) {
		cout << "Introduceti datele pentru zona cu numarul " << i << ":\n";

		cout << "Introduceti numele zonei: ";

		L.zone[i] = new char[255];

		in >> L.zone[i];

		cout << "Numarul de randuri din zona curenta: ";
		in >> L.nrRanduri[i];


		L.nrScaune[i] = new int[L.nrRanduri[i]];

		for (int j = 0; j < L.nrRanduri[i]; j++) {
			cout << "Introduceti numarul de scaune de pe randul cu numarul " << j << ":";
			in >> L.nrScaune[i][j];
		}
	}

	return in;
}

ofstream& operator<<(ofstream& out, Locatie& L)
{
	out << L.nrMaximLocuri;
	out << L.nrZone;
	out << L.zone;
	out << L.nrRanduri;
	out << L.nrScaune;

	return out;
}

ifstream& operator>>(ifstream& in, Locatie& L)
{

	in >> L.nrMaximLocuri;
	in >> L.nrZone;

	L.nrRanduri = new int[L.nrZone + 1];
	L.nrScaune = new int* [L.nrZone + 1];
	L.zone = new char* [L.nrZone + 1];

	for (int i = 0; i < L.nrZone; i++) {
		
		L.zone[i] = new char[255];

		in >> L.zone[i];

		in >> L.nrRanduri[i];

		L.nrScaune[i] = new int[L.nrRanduri[i]];

		for (int j = 0; j < L.nrRanduri[i]; j++) {
			in >> L.nrScaune[i][j];
		}
	}
	return in;
}

//Is a 
class Peluza :public Locatie
{
private:
	char* numePeluza;

public:
	Peluza() :Locatie()
	{
		this->numePeluza = new char[strlen("//") + 1];
		strcpy(this->numePeluza, "//");
	}

	Peluza(const char* zona, int nrRanduri, int nrScaun, const char* numePeluza) :Locatie()
	{
		this->numePeluza = new char[strlen(numePeluza) + 1];
		strcpy(this->numePeluza, numePeluza);
	}

	Peluza(const Peluza& L):Locatie()
	{
		this->numePeluza = new char[strlen(L.numePeluza) + 1];
		strcpy(this->numePeluza, L.numePeluza);
	}
	~Peluza()
	{
		delete[]this->numePeluza;
	}
	friend ostream& operator<<(ostream& out, const Peluza& P)
	{
		out << "Numele peluzei este:" << P.numePeluza;
		return out;
	}
};


class Eveniment: public File
{

public:

	struct data_t {
		int zi;
		int luna;
		int an;
	};

	struct timp_t {
		int ora;
		int minut; 
	};

private:
	char* denumire;
	data_t data;
	timp_t ora;

	int nrBilete;
	Bilet* bilete;
	Locatie locatie;

public:
	//constructor fara parametri
	Eveniment()
	{
		denumire = 0;
		data = data_t();
		ora = timp_t();
		nrBilete = 0;
		bilete = NULL;
		locatie = Locatie();
	}
	//constructor cu parametri
	Eveniment(char* den, data_t data, timp_t ora, int id, int nrBilete, Bilet* bilete, Locatie locatie)
	{
		delete[] this->denumire;

		this->denumire = new char[strlen(den) + 1];
		strcpy(denumire, den);

		this->data = data;
		this->ora = ora;

		this->nrBilete = nrBilete;

		delete[] this->bilete;

		this->bilete = new Bilet[nrBilete];

		for (int i = 0; i < nrBilete; i++) {
			this->bilete[i] = bilete[i];
		}

		this->locatie = locatie;
	}

	//constructor de copiere
	Eveniment(const Eveniment& e)
	{
		this->data = e.data;
		this->ora = e.ora;

		delete[] this->denumire;

		this->denumire = new char[strlen(e.denumire) + 1];

		strcpy(denumire, e.denumire);

		this->nrBilete = e.nrBilete;

		delete[] this->bilete;

		this->bilete = new Bilet[e.nrBilete];

		for (int i = 0; i < e.nrBilete; i++) {
			this->bilete[i] = e.bilete[i];
		}


		this->locatie = e.locatie;
	}

	//getter denumire
	char* getDenumire() {
		char* Den = new char[strlen(this->denumire) + 1];
		strcpy(Den, this->denumire);
		return Den;
	}

	//getter data
	data_t getData() {
		return this->data;
	}
	//getter ora
	timp_t getOra() {
		return this->ora;
	}

	//setter denumire
	void setDenumire(char* den) {
		if (denumire != nullptr)
		{
			delete[] denumire;
		}
		this->denumire = new char[strlen(den) + 1];
		strcpy(denumire, den);
	}
	//setter data
	void setData(data_t  data)
	{
		data = data;
	}
	//setter ora
	void setOra(timp_t ora) {
		ora = ora;
	}

	//operator =
	Eveniment& operator=(Eveniment& ev)
	{
		delete[] this->denumire;
		this->denumire = new char[strlen(ev.denumire) + 1];
		strcpy(denumire, ev.denumire);
		this->data = ev.data;
		this->ora = ev.ora;

		this->nrBilete = ev.nrBilete;

		delete[] this->bilete;

		this->bilete = new Bilet[ev.nrBilete];

		for (int i = 0; i < ev.nrBilete; i++) {
			this->bilete[i] = ev.bilete[i];
		}

		this->locatie = ev.locatie;

		return(*this);
	}

	//operator[]
	char operator[](int i) {
		if (i < 0 || i >= strlen(this->denumire)) {
			throw "invalid";
		}
		else {
			return this->denumire[i];
		}
	}

	~Eveniment()
	{
		if (denumire != nullptr)
		{
			delete[] this->denumire;
		}

		if (bilete != nullptr) {
			delete[] this->bilete;
		}

		this->denumire = nullptr;
		this->bilete = nullptr;
	}

	void readFile(fstream& file) {
		//char* denumire;
		delete[] this->denumire;
		int lg = 0;
		file.read((char*)&lg, sizeof(int));
		this->denumire = new char[lg];
		file.read(this->denumire, lg);
		
		file.read((char*)&this->data.zi, sizeof(int));
		file.read((char*)&this->data.luna, sizeof(int));
		file.read((char*)&this->data.an, sizeof(int));
		
		file.read((char*)&this->ora.ora, sizeof(int));
		file.read((char*)&this->ora.minut, sizeof(int));
		//int nrBilete;
		file.read((char*)&this->nrBilete, sizeof(int));

	}

	void writeFile(fstream& file)
	{
		file << "===============EVENIMENT===============\n";
		file << "Denumirea evenimentuluie este:" << this->denumire << endl;
		file << "Data evenimentului este:" << this->data.zi << " " << this->data.luna << " " << this->data.an << endl;
		file << "Ora evenimentului este:" << this->ora.ora << " " << this->ora.minut << endl;

		file << "Biletele emise pentru acest eveniment sunt:" << endl;
		for (int i = 0; i < this->nrBilete; i++) {
			file << this->bilete[i] << endl;
		}

		file << this->locatie;

		file << "===============EVENIMENT===============\n";

	}
	friend ostream& operator<<(ostream& out, Eveniment& E);
	friend istream& operator>>(istream& in, Eveniment& E);
	friend ofstream& operator<<(ofstream& out, Eveniment& E);
	friend ifstream& operator>>(ifstream& in, Eveniment& E);
	
};
//operator <<
ostream& operator<<(ostream& out, Eveniment& E)
{

	out << "===============EVENIMENT===============\n";
	out << "Denumirea evenimentuluie este:" << E.denumire << endl;
	out << "Data evenimentului este(zi, luna, an):" << E.data.zi << "." << E.data.luna << "." << E.data.an << endl;
	out << "Ora evenimentului este (ora, minut):" << E.ora.ora << ":" << E.ora.minut << endl;

	out << "Biletele emise pentru acest eveniment sunt:" << endl;
	for (int i = 0; i < E.nrBilete; i++) {
		out << E.bilete[i] << endl;
	}

	out << E.locatie;

	out << "===============EVENIMENT===============\n";

	return out;
}

//operatorul >>
istream& operator>>(istream& in, Eveniment& E)
{
	E.denumire = new char[1000];

	cout << "Denumirea evenimentului:";
	in >> E.denumire;
	cout << "Data evenimentului (zi, luna, an):";
	in >> E.data.zi >> E.data.luna >> E.data.an;
	cout << "Ora evenimentului (ora, minut):";
	in >> E.ora.ora >> E.ora.minut;

	cout << "Introduceti datele corespuzatoare locatiei evenimentului:\n";

	in >> E.locatie;


	cout << "Introduceti nr de bilete pe care doriti sa le emiteti pentru eveniment:";
	in >> E.nrBilete;

	E.bilete = new Bilet[E.nrBilete];

	for (int i = 0; i < E.nrBilete; i++) {
		cout << "Introducere datele pentru biletul cu numarul " << i << ":\n";
		in >> E.bilete[i];
	}

	return in;
}

ofstream& operator<<(ofstream&out, Eveniment& E)
{
	out << E.denumire << ",";
	out << E.data.zi << E.data.luna << E.data.an << ",";
	out << E.ora.ora << E.ora.minut << ",";
	out << E.locatie << ",";
	out << E.nrBilete << ",";
	out << E.bilete << ",";
	return out;
}

ifstream& operator>>(ifstream& in, Eveniment& E)
{
	delete[]E.denumire;
	char denumire[20];
	in>> denumire;
	E.denumire = new char[strlen(denumire) + 1];
	strcpy(E.denumire, denumire);
	in>> E.data.zi >> E.data.luna >> E.data.an;
	in>> E.ora.ora >> E.ora.minut;
	in>> E.locatie;
	in >> E.nrBilete;
	return in;

}

//Has a
class Concert : public Eveniment
{
private:
	char artist;
	vector<Eveniment*> eveniment;
public:
	Concert()
		{
			this->artist = 0;
		}
	Concert(char artist)
	{
		this->artist = artist;
	}
	Concert(const Concert& C)
	{
		this->artist = C.artist;
		this->eveniment = C.eveniment;
	}

~Concert()
	{
	artist = 0;
	for (int i = 0; i < eveniment.size(); i++)
		eveniment.pop_back();
	}

void adaugare_eveniment(Eveniment* E)
{
	this->eveniment.push_back(E);
}
friend ostream& operator<<(ostream& out, const Concert& C)
{
	out << "\Nume artist:" << C.artist << endl;
	return out;
}

};


int main()
{

	Eveniment e;
	cin >> e;
	cout << e;


	//Bilet b;

	//cin >> b;

	//cout << b;


	/*Locatie l;

	cin >> l;

	cout << l;*/

	return 0;

}