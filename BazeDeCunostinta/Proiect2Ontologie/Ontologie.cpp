#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Vehicul{
    protected:
        string marca;
        int anFabricatie;
        string motorizare;
        string serieSasiu;
        
    public:
        Vehicul() {
            marca = "";
            anFabricatie = 0;
            motorizare = "";
            serieSasiu = "";
        }
        
        virtual void afiseaza() {
            cout << "=== VEHICUL ===" << endl;
            cout << "Marca: " << marca << endl;
            cout << "An fabricatie: " << anFabricatie << endl;
            cout << "Motorizare: " << motorizare << endl;
            cout << "Serie sasiu: " << serieSasiu << endl;
        }
        
        virtual ~Vehicul() {}
};

class Autoturism : public Vehicul{
    private:
        string codAutoturism;
        int nrUsi;
        string tipCaroserie;
        
    public:
        Autoturism() : Vehicul() {
            codAutoturism = "";
            nrUsi = 0;
            tipCaroserie = "";
        }
        
        void afiseaza() override {
            cout << "\n=== AUTOTURISM ===" << endl;
            cout << "Marca: " << marca << endl;
            cout << "An fabricatie: " << anFabricatie << endl;
            cout << "Motorizare: " << motorizare << endl;
            cout << "Serie sasiu: " << serieSasiu << endl;
            cout << "Cod autoturism: " << codAutoturism << endl;
            cout << "Numar usi: " << nrUsi << endl;
            cout << "Tip caroserie: " << tipCaroserie << endl;
        }
        
        void citesteDeLaTastatura() {
            cout << "\n--- Introduceti datele autoturismului ---" << endl;
            cout << "Marca: "; 
            cin.ignore();
            getline(cin, marca);
            cout << "An fabricatie: "; cin >> anFabricatie;
            cout << "Motorizare: "; 
            cin.ignore();
            getline(cin, motorizare);
            cout << "Serie sasiu: "; getline(cin, serieSasiu);
            cout << "Cod autoturism: "; getline(cin, codAutoturism);
            cout << "Numar usi: "; cin >> nrUsi;
            cout << "Tip caroserie: "; 
            cin.ignore();
            getline(cin, tipCaroserie);
        }
        
        void seteazaDate(string m, int an, string mot, string serie, string cod, int usi, string tip) {
            marca = m;
            anFabricatie = an;
            motorizare = mot;
            serieSasiu = serie;
            codAutoturism = cod;
            nrUsi = usi;
            tipCaroserie = tip;
        }
};

class Motocicleta : public Vehicul{
    private:
        string codMotocicleta;
        string tipCadru;
        int capacitateCilindrica;
        
    public:
        Motocicleta() : Vehicul() {
            codMotocicleta = "";
            tipCadru = "";
            capacitateCilindrica = 0;
        }
        
        void afiseaza() override {
            cout << "\n=== MOTOCICLETA ===" << endl;
            cout << "Marca: " << marca << endl;
            cout << "An fabricatie: " << anFabricatie << endl;
            cout << "Motorizare: " << motorizare << endl;
            cout << "Serie sasiu: " << serieSasiu << endl;
            cout << "Cod motocicleta: " << codMotocicleta << endl;
            cout << "Tip cadru: " << tipCadru << endl;
            cout << "Capacitate cilindrica: " << capacitateCilindrica << " cc" << endl;
        }
        

        void citesteDinFisier(ifstream &fin) {
            getline(fin, marca);
            fin >> anFabricatie;
            fin.ignore();
            getline(fin, motorizare);
            getline(fin, serieSasiu);
            getline(fin, codMotocicleta);
            getline(fin, tipCadru);
            fin >> capacitateCilindrica;
            fin.ignore();
        }
        
        void seteazaDate(string m, int an, string mot, string serie, string cod, string cadru, int cc) {
            marca = m;
            anFabricatie = an;
            motorizare = mot;
            serieSasiu = serie;
            codMotocicleta = cod;
            tipCadru = cadru;
            capacitateCilindrica = cc;
        }
};

int main() {

    cout << "\n\nDate citite de la tastatura" << endl;
    Autoturism auto2;
    auto2.citesteDeLaTastatura();
    auto2.afiseaza();

    cout << "\n\nDate din program" << endl;
    
    Autoturism auto1;
    auto1.seteazaDate("BMW", 2020, "Diesel 2.0", "WBA12345678901234", "AUTO001", 4, "Sedan");
    auto1.afiseaza();
    
    Motocicleta moto1;
    moto1.seteazaDate("Yamaha", 2019, "Benzina 600cc", "JYARN23E00A000001", "MOTO001", "Sportiv", 600);
    moto1.afiseaza();
    
    cout << "\n\nDate citite din fisier" << endl;
    
    ifstream fin("vehicule.txt");
    if(fin.is_open()) {
        Motocicleta moto2;
        moto2.citesteDinFisier(fin);
        moto2.afiseaza();
        fin.close();
    }
    
    return 0;
}