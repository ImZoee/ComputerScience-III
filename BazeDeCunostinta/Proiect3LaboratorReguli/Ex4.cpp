#include <iostream>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    string genre;
    string pages;
    string language;
    string age;

    bool matches(const string &agePref, const string &langPref,
                 const string &pagesPref, const string &genrePref) const {
        if (!agePref.empty() && age != agePref) return false;
        if (!langPref.empty() && language != langPref) return false;
        if (!pagesPref.empty() && pages != pagesPref) return false;
        if (!genrePref.empty() && genre != genrePref) return false;
        return true;
    }
};

class Library {
public:
    static const int N = 16;
    Book catalog[N];

    Library() {
        catalog[0] = {"The Pianist", "Wladyslaw Szpilman", "memoir", "long", "polish", "adult"};
        catalog[1] = {"The Boy in the Striped Pajamas", "John Boyne", "war", "short", "english", "young"};
        catalog[2] = {"The Fault in Our Stars", "John Green", "young adult", "medium", "english", "young"};
        catalog[3] = {"Looking for Alaska", "John Green", "adventure", "short", "english", "young"};   
        catalog[4] = {"To kill a mockingbird", "Harper Lee", "coming of age", "medium", "english", "child"};
        catalog[5] = {"The Hunger Games", "Suzanne Collins", "fantasy", "long", "english", "young"};
        catalog[6] = {"Catch-22", "Joseph Heller", "fiction", "long", "english", "adult"};
        catalog[7] = {"The Catcher in the Rye", "J.D. Salinger", "coming of age", "short", "english", "child"};
        catalog[8] = {"Pride and Prejudice", "Jane Austen", "romance", "medium", "english", "young"};
        catalog[9] = {"The diary of a young girl", "Anne Frank", "biography", "medium", "dutch", "young"};
        catalog[10] = {"The Great Gatsby", "F.Scott Fitzgerald", "romance", "long", "english", "young"};
        catalog[11] = {"The Time Traveler's Wife", "Audrey Niffenegger", "fantasy", "medium", "english", "young"};
        catalog[12] = {"Twilight", "Stephenie Meyer", "young adult", "long", "english", "young"};
        catalog[13] = {"The Hobbit", "J.R.R. Tolkien", "fantasy", "long", "english", "young"};
        catalog[14] = {"The Godfather", "Mario Puzo", "drama", "medium", "italian", "adult"};
        catalog[15] = {"Nineteen eighty four", "George Orwell", "dystopia", "medium", "english", "adult"};
    }

    void recommend(const string &agePref, const string &langPref,
                   const string &pagesPref, const string &genrePref) const {
        bool any = false;
        cout << "\nCarti recomandate pe baza preferintelor:\n";
        for (int i = 0; i < N; ++i) {
            if (catalog[i].matches(agePref, langPref, pagesPref, genrePref)) {
                any = true;
                cout << " - " << catalog[i].title << " by " << catalog[i].author << "\n";
            }
        }
        if (!any) {
            cout << "Nu am gasit nicio carte potrivita.\n";
        }
    }
};

int main() {
    Library lib;

    string age, language, pages, genre;

    cout << "Varsta (child/young/adult): ";
    getline(cin, age);

    cout << "Limba preferata(english/italian): ";
    getline(cin, language);

    cout << "Dimensiune carte (short/medium/long): ";
    getline(cin, pages);

    cout << "Gen(war/adventure/memoir/fantasy,etc): ";
    getline(cin, genre);

    lib.recommend(age, language, pages, genre);

    return 0;
}
