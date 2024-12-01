// STRUCNY POPIS:
//
// V tejto ukazke su naprogramovane 2 triedy:
//
//    Trieda 'Movie'
//
//    Reprezentuje film v databaze filmov.
//
//    Jej atributmi su:
//       * nazov filmu 'title' (C retazec)
//       * rok vydania 'year'
//       * hodnotenie filmu 'rating'
//
//    Jej metodami su:
//       * konstruktory (default, parametricky a kopirovaci)
//       * destruktor
//       * nastavovacie metody, tzv. setters
//       * metody na vratenie atributov, tzv. getters
//       * metoda 'print' na vypis informacii o filme
//
// -----------------------------------------------------------------
//
//    Trieda 'MovieDB'
//
//    Reprezentuje databazu filmov a k nej asociovane operacie.
//
//    Jej atributmi su:
//       * pole filmov 'db' (obsahuje objekty typu 'Movie')
//       * aktualny pocet filmov v databaze 'count'
//
//    Jej metodami su:
//       * default konstruktor
//       * metoda 'add' na pridanie filmu do databazy
//       * metoda 'search' na vyhladanie filmu v databaze podla klucoveho slova
//       * metoda 'print' na vypis databazy filmov


#define DB_COUNT 5 // maximalny pocet filmov v DB
#define LEN 100

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

// definicia triedy 'Movie'
class Movie {
private:
    char title[LEN]; // nazov filmu
    int year; // rok vydania filmu
    int rating; // percentualne hodnotenie filmu 0 az 100 %

public:
    // default a zaroven parametricky konstruktor
    // poznamka: vytvori sa hlboka kopia nazvu filmu
    Movie(const char *title = nullptr, const int year = -1, const int rating = -1) :
            year(year),
            rating(rating) {
        if (title) {
            strcpy(this->title, title);
        }
        else{
            memset(this->title, '\0', LEN);
        };
    }

    // copy konstruktor - hlboka kopia objektu 'other'
    Movie(const Movie &other) :
            year(other.year),
            rating(other.rating) {
        if (other.title) {
            strcpy(this->title, other.title);
        }
    }


    // set metoda pre atribut 'title'
    void setTitle(const char *title) {
        // ak novy nazov neexistuje
        if (!title) {
            return;
        }
        // nastavime novy nazov
        strcpy(this->title, title);
    }

    // set metoda pre atribut 'year'
    void setYear(const int year) {
        this->year = year;
    }

    // set metoda pre atribut 'rating'
    void setRating(const int rating) {
        this->rating = rating;
    }

    // get metoda pre atribut 'title'
    const char *getTitle() const {
        return this->title; // vrati sa len smernik, nie hlboka kopia
    }

    // get metoda pre atribut 'year'
    int getYear() const {
        return this->year;
    }

    // get metoda pre atribut 'rating'
    int getRating() const {
        return this->rating;
    }

    // metoda na vytlacenie informacii o filme do konzoly
    void print() const {
        cout << left << setw(25) << this->title;
        cout << setw(7) << this->year;
        cout << this->rating << " %";
        cout << endl;
    }
};

// definicia triedy 'MovieDB'
class MovieDB {
private:
    Movie db[DB_COUNT]; // pole filmov, t.j. databaza
    std::size_t count; // aktualny pocet filmov v DB

public:
    // default konstruktor
    MovieDB() :
            count(0) {
    }

    // metoda na pridavanie noveho filmu s dodanymi atributmi do DB
    void add(const char *title, const int year, const int rating) {
        if (this->count < DB_COUNT) {
            this->db[this->count].setTitle(title);
            this->db[this->count].setYear(year);
            this->db[this->count].setRating(rating);
            this->count++;
        }
    }

    // metoda na vyhladavanie filmu v DB
    // poznamka: vrati sa film pri prvej zhode
    const Movie *searchByTitle(const char *keyword) const {
        for (std::size_t i = 0; i < this->count; i++) {
            if (strstr(this->db[i].getTitle(), keyword)) {
                return &this->db[i];
            }
        }
        return nullptr;
    }

    // metoda na vypis DB filmov do konzoly
    void print() const {
        cout << endl << "Movie DB" << endl;
        cout << "-----------------------------------------" << endl;
        for (std::size_t i = 0; i < this->count; i++) {
            this->db[i].print();
        }
        cout << endl;
    }
};

// funkcia na testovanie prace s triedou 'Movie'
void test_movie() {
    // 1. Test default konstruktora
    Movie m1;

    // 2. Test parametrickeho konstruktora
    Movie m2("Toy Story", 1995, 83);

    // 3. Test kopirovacieho konstruktora
    Movie example("Joker", 2019, 90);
    Movie m3(example); // tu sa vola kopirovaci konstruktor

    // 4. Test metod na nastavenie atributov (setters)
    Movie example2("Sin City", 2005, 80);
    example2.setRating(85);
    example2.setTitle("Titanic");
    example2.setYear(1997);

    // 5. Test metod na vratenie atributov (getters)
    // int movie_rating = example.getRating();
    // const char *movie_title = example.getTitle();
    // int movie_year = example.getYear();

    // 6. Test metody na vypis filmu
    example2.print();

    // 7. Desktruktory objektov sa budu volat po ukonceni funkcie v obratenom poradi:
    //    example2 -> m3 -> example -> m2 -> m1
    // Mozete si to otestovat bud v Debug rezime alebo pridanim vypisov do destruktora.
}

// funkcia na testovanie prace s triedou 'MovieDB'
void test_movie_db() {
    // 1. Test default konstruktora
    MovieDB db;

    // 2. Test metody 'add'
    db.add("Lion King", 2019, 77);
    db.add("Finding Nemo", 2003, 86);
    db.add("Interstellar", 2014, 86);

    // 3. Test metody 'print' na vypis databazy filmov
    db.print();

    // 4. Interaktivny test metody 'search' na vyhladanie filmu v databaze
    char keyword[100];
    cout << "Hladaj film podla klucoveho slova: ";
    cin >> keyword;
    const Movie *result = db.searchByTitle(keyword);
    if (result) {
        result->print();
    } else {
        cout << "Nic sa nenaslo" << endl;
    }
}

// testovanie
int main() {
    test_movie();
    test_movie_db();
    return 0;
}
