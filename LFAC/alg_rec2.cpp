#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Fiecare multime M_i este modelata ca un vector de siruri unice.

struct Rule {
    string left;   // membrul stang al productiei
    string right;  // membrul drept; "" inseamna epsilon
};

// Verifica apartenenta unui sir la o "multime" reprezentata prin vector.
bool existsIn(const vector<string>& v, const string& s) {
    for (int i = 0; i < (int)v.size(); i++) {
        if (v[i] == s) {
            return true;
        }
    }
    return false;
}

// Adauga un element doar daca nu este deja prezent.
void addUnique(vector<string>& v, const string& s) {
    if (!existsIn(v, s)) {
        v.push_back(s);
    }
}

// Folosit in pasul P2: pentru cuvantul vid avem nevoie de productia S -> e.
bool hasStartToEpsilon(const vector<Rule>& P, const string& S) {
    for (int i = 0; i < (int)P.size(); i++) {
        if (P[i].left == S && P[i].right.empty()) {
            return true;
        }
    }
    return false;
}

// Daca exista productii epsilon pe neterminali diferiti de S,
// unele derivari valide necesita temporar cu 1 simbol in plus.
bool hasNonStartEpsilonRule(const vector<Rule>& P, const string& S) {
    for (int i = 0; i < (int)P.size(); i++) {
        if (P[i].left != S && P[i].right.empty()) {
            return true;
        }
    }
    return false;
}

// Genereaza toate secventele beta obtinute intr-un singur pas: alpha -> beta.
// Pastram doar secvente cu lungime <= maxLen, exact ca in P4.
vector<string> deriveOneStep(const string& alpha, const vector<Rule>& P, int maxLen) {
    vector<string> out;

    for (int ir = 0; ir < (int)P.size(); ir++) {
        const Rule& r = P[ir];
        int n = (int)alpha.size();
        int m = (int)r.left.size();

        if (m == 0) {
            continue;
        }

        for (int pos = 0; pos + m <= n; pos++) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (alpha[pos + j] != r.left[j]) {
                    match = false;
                    break;
                }
            }

            if (!match) {
                continue;
            }

            string beta = alpha.substr(0, pos) + r.right + alpha.substr(pos + m);
            if ((int)beta.size() <= maxLen) {
                addUnique(out, beta);
            }
        }
    }

    return out;
}

// Afiseaza multimea M_i in format usor de urmarit in consola.
void printSet(const vector<string>& M, int idx) {
    cout << "M" << idx << " = { ";
    for (int i = 0; i < (int)M.size(); i++) {
        if (M[i].empty()) {
            cout << "e";
        } else {
            cout << M[i];
        }

        if (i + 1 < (int)M.size()) {
            cout << ", ";
        }
    }
    cout << " }\n";
}

// Executa algoritmul REC pentru un cuvant w.
// Intoarce true daca w este gasit in multimea stabilizata M_i.
bool recAlgorithm(const string& w, const vector<Rule>& P, const string& S, bool showSteps) {
    int l = (int)w.size();

    // P1 + P2
    if (l == 0) {
        bool ok = hasStartToEpsilon(P, S);
        if (showSteps) {
            cout << "\nCuvant testat: e (|w|=0)\n";
            cout << "P2: " << (ok ? "S -> e exista" : "S -> e nu exista") << "\n";
        }
        return ok;
    }

    // Pentru gramatica de aici (A -> e), folosim o marja mica de lungime
    // ca sa evitam respingeri false ale unor cuvinte valide.
    int maxIntermediateLen = l;
    if (hasNonStartEpsilonRule(P, S)) {
        maxIntermediateLen = l + 1;
    }

    // P3
    vector<string> Mi;
    Mi.push_back(S);
    int i = 0;

    if (showSteps) {
        cout << "\nCuvant testat: " << w << " (|w|=" << l << ")\n";
        printSet(Mi, i);
    }

    while (true) {
        // P4
        // Construim M_{i+1} din M_i printr-un pas de derivare pentru fiecare alpha din M_i.
        vector<string> Mnext = Mi;
        for (int ia = 0; ia < (int)Mi.size(); ia++) {
            vector<string> generated = deriveOneStep(Mi[ia], P, maxIntermediateLen);
            for (int ig = 0; ig < (int)generated.size(); ig++) {
                addUnique(Mnext, generated[ig]);
            }
        }

        if (showSteps) {
            printSet(Mnext, i + 1);
        }

        // P5
        // Daca nu mai apar elemente noi, am ajuns la punct fix si ne oprim.
        if (Mnext == Mi) {
            break;
        }

        Mi = Mnext;
        i = i + 1;
    }

    // P6
    return existsIn(Mi, w);
}

int main() {
    // Gramatica este codata direct in program.
    // Pentru alte exemple poti modifica aceasta lista de productii.
    // Gramatica din exemplu:
    // 1) S -> 1A1
    // 2) A -> 1A
    // 3) A -> 0A
    // 4) A -> e
    // 5) S -> 1
    vector<Rule> P;
    P.push_back({"S", "1A1"});
    P.push_back({"A", "1A"});
    P.push_back({"A", "0A"});
    P.push_back({"A", ""});
    P.push_back({"S", "1"});

    string S = "S";

    // Citim cuvantul testat. Conventie: "e" reprezinta epsilon.
    cout << "Introdu cuvantul w (foloseste e pentru epsilon): ";
    string w;
    cin >> w;
    if (w == "e") {
        w.clear();
    }

    bool ok = recAlgorithm(w, P, S, true);
    if (ok) {
        cout << "DA (w apartine L(G))\n";
    } else {
        cout << "NU (w nu apartine L(G))\n";
    }

    return 0;
}