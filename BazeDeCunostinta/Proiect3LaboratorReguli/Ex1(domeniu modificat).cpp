#include <iostream>
#include <string>

using namespace std;

class LeadRelation {
public:
    string lead;
    string member;
};

class BuddyPair {
public:
    string lead1;
    string lead2;
};

class PeerPair {
public:
    string peer1;
    string peer2;
};

class Membership {
public:
    string member;
    string manager;
};

class Seniority {
public:
    string senior;
    string junior;
};

class CrossTeamPeer {
public:
    string person1;
    string person2;
};

const int MAX_FACTS = 150;

string gasesteBuddy(const BuddyPair listaBuddy[], int nBuddy, const string &persoana) {
    for (int i = 0; i < nBuddy; ++i) {
        if (listaBuddy[i].lead1 == persoana) {
            return listaBuddy[i].lead2;
        }
        if (listaBuddy[i].lead2 == persoana) {
            return listaBuddy[i].lead1;
        }
    }
    return "";
}

void afiseazaMembri(const Membership listaMembri[], int nMembri) {
    cout << "\nRelatii manager - membru:\n";
    for (int i = 0; i < nMembri; ++i) {
        cout << "Membru: " << listaMembri[i].member << "\tManager: " << listaMembri[i].manager << "\n";
    }
}

void afiseazaPerechi(const PeerPair listaPerechi[], int nPerechi, const string &titlu) {
    cout << "\n" << titlu << ":\n";
    for (int i = 0; i < nPerechi; ++i) {
        cout << listaPerechi[i].peer1 << " - " << listaPerechi[i].peer2 << "\n";
    }
}

void afiseazaSeniori(const Seniority listaSeniori[], int nSeniori) {
    cout << "\nRelatii senior - junior:\n";
    for (int i = 0; i < nSeniori; ++i) {
        cout << "Senior: " << listaSeniori[i].senior << "\tJunior: " << listaSeniori[i].junior << "\n";
    }
}

void afiseazaCross(const CrossTeamPeer listaCross[], int nCross) {
    cout << "\nCross-team peers:\n";
    for (int i = 0; i < nCross; ++i) {
        cout << listaCross[i].person1 << " - " << listaCross[i].person2 << "\n";
    }
}

int main() {
    LeadRelation listaLeads[MAX_FACTS];
    BuddyPair listaBuddy[MAX_FACTS];
    PeerPair listaPeers[MAX_FACTS];
    Membership listaMembri[MAX_FACTS];
    Seniority listaSeniori[MAX_FACTS];
    CrossTeamPeer listaCross[MAX_FACTS];

    int nLeads = 0;
    int nBuddy = 0;
    int nPeers = 0;
    int nMembri = 0;
    int nSeniori = 0;
    int nCross = 0;

    listaLeads[nLeads++] = {"Andrei", "Rares"};
    listaLeads[nLeads++] = {"Andrei", "Mihnea"};
    listaLeads[nLeads++] = {"Bianca", "Ilie"};
    listaLeads[nLeads++] = {"Bianca", "Sabina"};

    listaBuddy[nBuddy++] = {"Andrei", "Dorian"};
    listaBuddy[nBuddy++] = {"Bianca", "Larisa"};

    listaLeads[nLeads++] = {"Claudia", "Andrei"};
    listaLeads[nLeads++] = {"Claudia", "Bianca"};
    listaLeads[nLeads++] = {"Claudia", "Filip"};
    listaBuddy[nBuddy++] = {"Claudia", "Horia"};

    listaLeads[nLeads++] = {"Dan", "Claudia"};
    listaLeads[nLeads++] = {"Dan", "Iulia"};
    listaLeads[nLeads++] = {"Dan", "Vlad"};
    listaBuddy[nBuddy++] = {"Dan", "Paula"};

    listaLeads[nLeads++] = {"Dorian", "Teodora"};
    listaLeads[nLeads++] = {"Dorian", "Victor"};

    listaLeads[nLeads++] = {"Larisa", "Octav"};
    listaLeads[nLeads++] = {"Larisa", "Zara"};

    listaLeads[nLeads++] = {"Horia", "Patric"};
    listaLeads[nLeads++] = {"Horia", "Carina"};

    listaLeads[nLeads++] = {"Evelin", "Dan"};
    listaLeads[nLeads++] = {"Evelin", "Sonia"};
    listaBuddy[nBuddy++] = {"Evelin", "Tudor"};

    listaLeads[nLeads++] = {"Mara", "Evelin"};
    listaLeads[nLeads++] = {"Mara", "Ruben"};
    listaBuddy[nBuddy++] = {"Mara", "Cristi"};

    for (int i = 0; i < nLeads; ++i) {
        for (int j = i + 1; j < nLeads; ++j) {
            if (listaLeads[i].lead == listaLeads[j].lead) {
                string a = listaLeads[i].member;
                string b = listaLeads[j].member;
                if (b < a) { string tmp = a; a = b; b = tmp; }
                bool exista = false;
                for (int k = 0; k < nPeers; ++k) {
                    if (listaPeers[k].peer1 == a && listaPeers[k].peer2 == b) { exista = true; break; }
                }
                if (!exista) {
                    listaPeers[nPeers].peer1 = a;
                    listaPeers[nPeers].peer2 = b;
                    ++nPeers;
                }
            }
        }
    }

    for (int i = 0; i < nLeads; ++i) {
        listaMembri[nMembri].member = listaLeads[i].member;
        listaMembri[nMembri].manager = listaLeads[i].lead;
        ++nMembri;

        string buddy = gasesteBuddy(listaBuddy, nBuddy, listaLeads[i].lead);
        if (!buddy.empty()) {
            listaMembri[nMembri].member = listaLeads[i].member;
            listaMembri[nMembri].manager = buddy;
            ++nMembri;
        }
    }

    for (int i = 0; i < nLeads; ++i) {
        const string &manager = listaLeads[i].lead;
        const string &junior = listaLeads[i].member;
        for (int j = 0; j < nLeads; ++j) {
            if (listaLeads[j].member == manager) {
                const string &senior = listaLeads[j].lead;
                bool exista = false;
                for (int k = 0; k < nSeniori; ++k) {
                    if (listaSeniori[k].senior == senior && listaSeniori[k].junior == junior) { exista = true; break; }
                }
                if (!exista) {
                    listaSeniori[nSeniori++] = {senior, junior};
                }
                string buddy = gasesteBuddy(listaBuddy, nBuddy, senior);
                if (!buddy.empty()) {
                    exista = false;
                    for (int k = 0; k < nSeniori; ++k) {
                        if (listaSeniori[k].senior == buddy && listaSeniori[k].junior == junior) { exista = true; break; }
                    }
                    if (!exista) {
                        listaSeniori[nSeniori++] = {buddy, junior};
                    }
                }
            }
        }
    }

    for (int i = 0; i < nMembri; ++i) {
        for (int j = i + 1; j < nMembri; ++j) {
            if (listaMembri[i].manager == listaMembri[j].manager) continue;
            bool manageriSuntColegii = false;
            for (int k = 0; k < nPeers; ++k) {
                if ((listaPeers[k].peer1 == listaMembri[i].manager && listaPeers[k].peer2 == listaMembri[j].manager) ||
                    (listaPeers[k].peer2 == listaMembri[i].manager && listaPeers[k].peer1 == listaMembri[j].manager)) {
                    manageriSuntColegii = true;
                    break;
                }
            }
            if (!manageriSuntColegii) continue;

            string a = listaMembri[i].member;
            string b = listaMembri[j].member;
            if (b < a) { string tmp = a; a = b; b = tmp; }
            bool exista = false;
            for (int k = 0; k < nCross; ++k) {
                if (listaCross[k].person1 == a && listaCross[k].person2 == b) { exista = true; break; }
            }
            if (!exista) {
                listaCross[nCross++] = {a, b};
            }
        }
    }

    afiseazaMembri(listaMembri, nMembri);
    afiseazaPerechi(listaPeers, nPeers, "Colegii pe acelasi lead");
    afiseazaSeniori(listaSeniori, nSeniori);
    afiseazaCross(listaCross, nCross);

    return 0;
}
