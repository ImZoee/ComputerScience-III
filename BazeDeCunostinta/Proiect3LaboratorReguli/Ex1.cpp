
#include <iostream>
#include <string>

using namespace std;

class Mama {
public:
	string mama;
	string copil;
};

class Frate {
public:
	string frate1;
	string frate2;
};

class Sot {
public:
	string sot1;
	string sot2;
};

class Copil {
public:
	string copil;
	string parinte;
};

const int MAX_FAPTE = 100;

class Bunic {
public:
	string bunic;
	string nepot;
};

class Ver {
public:
	string ver1;
	string ver2;
};

string gasestePartener(const Sot listaSoti[], int nSoti, const string &persoana) {
	for (int i = 0; i < nSoti; ++i) {
		if (listaSoti[i].sot1 == persoana) {
			return listaSoti[i].sot2;
		}
		if (listaSoti[i].sot2 == persoana) {
			return listaSoti[i].sot1;
		}
	}
	return ""; 
}

void afiseazaCopii(const Copil listaCopii[], int nCopii) {
	cout << "Lista de copii:\n";
	for (int i = 0; i < nCopii; ++i) {
		cout << "Copil: " << listaCopii[i].copil << "\tParinte: " << listaCopii[i].parinte << "\n";
	}
}

void afiseazaFrati(const Frate listaFrati[], int nFrati) {
	cout << "\nLista de frati:\n";
	for (int i = 0; i < nFrati; ++i) {
		cout << "Frati: " << listaFrati[i].frate1 << " " << listaFrati[i].frate2 << "\n";
	}
}

void afiseazaBunici(const Bunic listaBunici[], int nBunici) {
	cout << "\nLista de bunici:\n";
	for (int i = 0; i < nBunici; ++i) {
		cout << "Bunic: " << listaBunici[i].bunic << "\tNepot: " << listaBunici[i].nepot << "\n";
	}
}

void afiseazaVeri(const Ver listaVeri[], int nVeri) {
	cout << "\nLista de veri:\n";
	for (int i = 0; i < nVeri; ++i) {
		cout << "Veri: " << listaVeri[i].ver1 << " " << listaVeri[i].ver2 << "\n";
	}
}

int main() {
	Mama listaMame[MAX_FAPTE];
	Sot listaSoti[MAX_FAPTE];
	Frate listaFrati[MAX_FAPTE];
	Copil listaCopii[MAX_FAPTE];
	Bunic listaBunici[MAX_FAPTE];
	Ver listaVeri[MAX_FAPTE];

	int nMame = 0;
	int nSoti = 0;
	int nFrati = 0;
	int nCopii = 0;
	int nBunici = 0;
	int nVeri = 0;


	listaMame[nMame++] = {"Roberta", "Costin"};
	listaMame[nMame++] = {"Roberta", "Ana"};
	listaMame[nMame++] = {"Cosmina", "Andrei"};
	listaMame[nMame++] = {"Cosmina", "Cristina"};

	listaSoti[nSoti++] = {"Roberta", "Gheorghe"};
	listaSoti[nSoti++] = {"Cosmina", "Catalin"};


	listaMame[nMame++] = {"Maria", "Roberta"};
	listaSoti[nSoti++] = {"Maria", "Petru"};
	listaMame[nMame++] = {"Lidia", "Cosmina"};
	listaSoti[nSoti++] = {"Lidia", "Sorin"};

	listaMame[nMame++] = {"Maria", "Sorina"};
	listaSoti[nSoti++] = {"Sorina", "Mihai"};
	listaMame[nMame++] = {"Sorina", "Paul"};
	listaMame[nMame++] = {"Sorina", "Daria"};

	listaMame[nMame++] = {"Elena", "Mara"};
	listaMame[nMame++] = {"Elena", "Vlad"};
	listaSoti[nSoti++] = {"Elena", "Dan"};

	listaMame[nMame++] = {"Nora", "Elena"};
	listaSoti[nSoti++] = {"Nora", "Danut"};

	listaMame[nMame++] = {"Irina", "Bogdan"};
	listaSoti[nSoti++] = {"Irina", "Tudor"};

	listaMame[nMame++] = {"Olga", "Irina"};
	listaSoti[nSoti++] = {"Olga", "Mircea"};

	for (int i = 0; i < nMame; ++i) {
		for (int j = i + 1; j < nMame; ++j) {
			if (listaMame[i].mama == listaMame[j].mama) {
				string a = listaMame[i].copil;
				string b = listaMame[j].copil;
				if (b < a) { string tmp = a; a = b; b = tmp; }
				bool exista = false;
				for (int k = 0; k < nFrati; ++k) {
					if (listaFrati[k].frate1 == a && listaFrati[k].frate2 == b) { exista = true; break; }
				}
				if (!exista) {
					listaFrati[nFrati].frate1 = a;
					listaFrati[nFrati].frate2 = b;
					++nFrati;
				}
			}
		}
	}

	// Deducere copii-parinti
	for (int i = 0; i < nMame; ++i) {
		listaCopii[nCopii].copil = listaMame[i].copil;
		listaCopii[nCopii].parinte = listaMame[i].mama;
		++nCopii;

		string partener = gasestePartener(listaSoti, nSoti, listaMame[i].mama);
		if (!partener.empty()) {
			listaCopii[nCopii].copil = listaMame[i].copil;
			listaCopii[nCopii].parinte = partener;
			++nCopii;
		}
	}

	// Deducere bunici
	for (int i = 0; i < nMame; ++i) {
		const string &mamaCopil = listaMame[i].mama;
		const string &copil = listaMame[i].copil;
		for (int j = 0; j < nMame; ++j) {
			if (listaMame[j].copil == mamaCopil) {
				const string &bunic = listaMame[j].mama;
				bool exista = false;
				for (int k = 0; k < nBunici; ++k) {
					if (listaBunici[k].bunic == bunic && listaBunici[k].nepot == copil) { exista = true; break; }
				}
				if (!exista) {
					listaBunici[nBunici++] = {bunic, copil};
				}
				string partener = gasestePartener(listaSoti, nSoti, bunic);
				if (!partener.empty()) {
					exista = false;
					for (int k = 0; k < nBunici; ++k) {
						if (listaBunici[k].bunic == partener && listaBunici[k].nepot == copil) { exista = true; break; }
					}
					if (!exista) {
						listaBunici[nBunici++] = {partener, copil};
					}
				}
			}
		}
	}

	// Deducere veri 
	for (int i = 0; i < nCopii; ++i) {
		for (int j = i + 1; j < nCopii; ++j) {
			if (listaCopii[i].parinte == listaCopii[j].parinte) continue; 
			bool parintiiSuntFrati = false;
			for (int k = 0; k < nFrati; ++k) {
				if ((listaFrati[k].frate1 == listaCopii[i].parinte && listaFrati[k].frate2 == listaCopii[j].parinte) ||
					(listaFrati[k].frate2 == listaCopii[i].parinte && listaFrati[k].frate1 == listaCopii[j].parinte)) {
					parintiiSuntFrati = true;
					break;
				}
			}
			if (!parintiiSuntFrati) continue;

			string a = listaCopii[i].copil;
			string b = listaCopii[j].copil;
			if (b < a) { string tmp = a; a = b; b = tmp; }
			bool exista = false;
			for (int k = 0; k < nVeri; ++k) {
				if (listaVeri[k].ver1 == a && listaVeri[k].ver2 == b) { exista = true; break; }
			}
			if (!exista) {
				listaVeri[nVeri++] = {a, b};
			}
		}
	}

	afiseazaCopii(listaCopii, nCopii);
	afiseazaFrati(listaFrati, nFrati);
	afiseazaBunici(listaBunici, nBunici);
	afiseazaVeri(listaVeri, nVeri);

	return 0;
}

