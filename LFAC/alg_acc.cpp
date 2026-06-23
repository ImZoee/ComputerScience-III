#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Automaton {
	vector<string> states;                  
	vector<string> alphabet;                
	vector<int> finals;                    
	int start = -1;                         
	vector<vector<vector<int>>> delta;      
};

// Afiseaza o multime de stari in forma { q0, q1, ... }.
void printStateSet(const set<int>& st, const vector<string>& names) {
	cout << "{ ";
	bool first = true;
	for (int idx : st) {
		if (!first) {
			cout << ", ";
		}
		cout << names[idx];
		first = false;
	}
	cout << " }";
}
void addTransition(Automaton& A, int from, int symbolIndex, int to) {
	vector<int>& dest = A.delta[from][symbolIndex];
	if (find(dest.begin(), dest.end(), to) == dest.end()) {
		dest.push_back(to);
	}
}

// Q = {q0, q1, q2, q3, q4}
// Sigma = {0, 1}
// q0 = q0
// F = {q3}
Automaton build() {
	Automaton A;
	A.states = {"q0", "q1", "q2", "q3", "q4"};
	A.alphabet = {"0", "1"};
	A.start = 0;      // q0
	A.finals = {3};   // q3

	A.delta.assign((int)A.states.size(), vector<vector<int>>((int)A.alphabet.size()));

	// Tranzitii din componenta accesibila.
	addTransition(A, 0, 0, 1); // q0 --0--> q1
	addTransition(A, 0, 1, 0); // q0 --1--> q0
	addTransition(A, 1, 0, 1); // q1 --0--> q1
	addTransition(A, 1, 1, 2); // q1 --1--> q2
	addTransition(A, 2, 0, 3); // q2 --0--> q3
	addTransition(A, 2, 1, 2); // q2 --1--> q2

	// Componenta izolata (neaccesibila din q0).
	addTransition(A, 4, 0, 4); // q4 --0--> q4
	addTransition(A, 4, 1, 4); // q4 --1--> q4

	return A;
}

void printAutomatonSummary(const Automaton& A) {
	cout << "A = (Q, Sigma, delta, q0, F)\n";
	cout << "Q = ";
	set<int> allStates;
	for (int i = 0; i < (int)A.states.size(); i++) {
		allStates.insert(i);
	}
	printStateSet(allStates, A.states);
	cout << "\n";

	cout << "Sigma = { ";
	for (int i = 0; i < (int)A.alphabet.size(); i++) {
		if (i) {
			cout << ", ";
		}
		cout << A.alphabet[i];
	}
	cout << " }\n";

	cout << "q0 = " << A.states[A.start] << "\n";
	cout << "F = ";
	set<int> finalsSet(A.finals.begin(), A.finals.end());
	printStateSet(finalsSet, A.states);
	cout << "\n";
}

set<int> runACC(const Automaton& A, bool showSteps) {
	// P1: Q0 = {q0}
	set<int> Qi;
	Qi.insert(A.start);
	int i = 0;

	while (true) {
		// ===== P2: Q(i+1) = Qi ∪ { toti succesorii } =====
		// Pasul 2 calculeaza multimea noua prin adaugarea tuturor starilor
		set<int> Qnext = Qi;  // Qnext incepe ca o copie a lui Qi

		// Pentru fiecare stare q din multimea Qi
		for (int q : Qi) {
			// Pentru fiecare simbol a din alfabetul Sigma
			for (int a = 0; a < (int)A.alphabet.size(); a++) {
				// Pentru fiecare stare p care este succesor al lui q via simbolul a
				// (adica p ∈ δ(q, a))
				for (int p : A.delta[q][a]) {
					Qnext.insert(p);  // Adaugam p in Qnext
				}
			}
		}

		// ===== P3: Daca Q(i+1) ≠ Qi, incrementeaza i si reiau P2 =====
		// Pasul 3 verifica daca am gasit stari noi in P2.
		if (Qnext != Qi) {
			// Am gasit stari noi, deci nu am atins punct fix
			if (showSteps) {
				cout << "P3. TEST: Q" << (i + 1) << " ≠ Q" << i << "\n";
				cout << "    => Stari NOI descoperite!\n";
				cout << "    => i := " << (i + 1) << " si revenim la P2\n";
			}
			Qi = Qnext;    // Actualizam Qi cu noua multime
			i++;           // Incrementam contorul itera
			continue;      // Reiau buclei la P2 cu noua multime
		}

		// ===== P4: Qa = Qi, STOP. =====
		// Pasul 4 este pasul final.
		if (showSteps) {
			cout << "\n=== P4. REZULTAT FINAL ===\n";
			cout << "Qa = Q" << i << " = ";
			printStateSet(Qi, A.states);
			cout << "\n";
			cout << "Starile accesibile din q0 sunt: ";
			printStateSet(Qi, A.states);
			cout << "\n";
		}
		return Qi; 
	}
}

int main() {
	Automaton A = build();

	set<int> Qa = runACC(A, false);
	cout << "Qa = ";
	printStateSet(Qa, A.states);
	cout << "\n";

	return 0;
}
