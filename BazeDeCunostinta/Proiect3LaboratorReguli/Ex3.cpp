#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Student {
private:
	string nume;
	int nrPrezCurs;
	int nrPrezLab;
	double notaProiectLab;
	double notaProbaScrisa;
	double notaProbaPractica;

	static constexpr int pragPrezCurs = 10;     
	static constexpr int pragPrezLab = 10;       
	static constexpr double pragNotaTrecere = 5.0; 

public:
	Student(std::string nume,
			int nrPrezCurs,
			int nrPrezLab,
			double notaProiectLab,
			double notaProbaScrisa,
			double notaProbaPractica)
		: nume(std::move(nume)),
		  nrPrezCurs(nrPrezCurs),
		  nrPrezLab(nrPrezLab),
		  notaProiectLab(notaProiectLab),
		  notaProbaScrisa(notaProbaScrisa),
		  notaProbaPractica(notaProbaPractica) {}

	bool sePoatePrezentaLaExamen() const {
		return nrPrezCurs >= pragPrezCurs && nrPrezLab >= pragPrezLab;
	}

	bool promovatProbaPractica() const {
		return notaProbaPractica >= pragNotaTrecere;
	}

	bool promovatProbaLab() const {
		return notaProiectLab >= pragNotaTrecere;
	}

	bool promovatProbaScrisa() const {
		return notaProbaScrisa >= pragNotaTrecere;
	}

	void estePromovat() const {
		cout << "Student: " << nume << "\n";

		if (!sePoatePrezentaLaExamen()) {
			cout << " - Nu se poate prezenta la examen (prezenta insuficienta).\n\n";
			return;
		}

		cout << " - Se poate prezenta la examen.\n";

		const bool practicOK = promovatProbaPractica();
		const bool labOK = promovatProbaLab();
		const bool scrisOK = promovatProbaScrisa();
		const bool promotPracticScris = practicOK && scrisOK;
		const bool promotLabScris = labOK && scrisOK;

		if (promotPracticScris || promotLabScris) {
			cout << " - A promovat examenul.\n";
			if (promotPracticScris) {
				cout << " - A promovat proba practica si proba scrisa.\n";
			}
			cout << "\n";
		} else {
			cout << " - Nu a promovat examenul.\n\n";
		}
	}
};

int main() {
	vector<Student> studenti = {
		{"Ana", 12, 13, 9.0, 7.5, 8.0},      
		{"Bogdan", 9, 12, 8.0, 6.0, 4.5},    
		{"Carmen", 11, 11, 4.0, 5.5, 6.0},   
		{"Dan", 12, 12, 7.0, 4.0, 9.0}       
	};

	for (const auto &s : studenti) {
		s.estePromovat();
	}

	return 0;
}
