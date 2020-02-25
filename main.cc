#include <algorithm>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
using namespace std;

struct book
{
    int id;
    int score;

    book(int id, int score) :
        id(id), score(score)
    {}

    bool operator> (const struct book &other) const {
        return score > other.score;
    }
};

struct bookPtrCompare
{
    bool operator()(const shared_ptr<struct book> b1,
                    const shared_ptr<struct book> b2) const
    {
        return *b1 > *b2;
    }
};

struct lib
{
    int id;
    int nbBooks;
    int daysForSignup;
    int booksPerDay;
    vector<shared_ptr<struct book>> books;

    bool operator< (const struct lib &other) const {
        return daysForSignup < other.daysForSignup;
    }
};

struct submission
{
    int nbSignedUp;
    vector<int> libs;
    vector<int> nbBooks;
    vector<vector<int>> books;

    void dump()
    {
        cout << nbSignedUp << "\n";
        for (int i = 0; i < nbSignedUp; ++i)
        {
            cout << libs[i] << " " << nbBooks[i] << "\n";

            for (int j = 0; j < nbBooks[i]; ++j)
            {
                cout << books[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

const char *inputFilename;

int nbTotalBooks = 0;
int nbLibs = 0;
int daysForScan = 0;

vector<struct lib> libs;
vector<shared_ptr<struct book>> allBooks;

struct submission sb;

void parse()
{
    fstream f;
    f.open(inputFilename);
    f >> nbTotalBooks;
    f >> nbLibs;
    f >> daysForScan;

    int score;
    for (int i = 0; i < nbTotalBooks; ++i)
    {
        f >> score;
        allBooks.push_back(make_shared<struct book>(i, score));
    }

    for (int i = 0; i < nbLibs; ++i)
    {
        struct lib l;
        l.id = i;
        f >> l.nbBooks;
        f >> l.daysForSignup;
        f >> l.booksPerDay;
        for (int j = 0; j < l.nbBooks; ++j)
        {
            int iBook;
            f >> iBook;
            l.books.push_back(allBooks[iBook]);
        }
        libs.push_back(l);
    }
}

void scan()
{
    sort(libs.begin(), libs.end());
    for (auto itLib = libs.begin(); itLib != libs.end(); ++itLib)
    {
        sort(itLib->books.begin(), itLib->books.end(), bookPtrCompare());
    }

}

void buildSubmission()
{
    sb.nbSignedUp = libs.size();
    for (auto itLib = libs.begin(); itLib != libs.end(); ++itLib)
    {
        sb.libs.push_back(itLib->id);
        sb.nbBooks.push_back(itLib->nbBooks);

        auto booksLib = vector<int>();
        for (auto itBook = itLib->books.begin(); itBook != itLib->books.end(); ++itBook)
        {
            booksLib.push_back((*itBook)->id);
        }

        sb.books.push_back(booksLib);
    }
}

int main(int argc, char **argv)
{
    (void)argc;
    inputFilename = argv[1];
    parse();
    scan();
    buildSubmission();
    sb.dump();
    return 0;
}
