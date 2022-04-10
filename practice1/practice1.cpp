#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <clocale>
#include <time.h>
using namespace std;



void PRACTICE()
{
    clock_t time1 = clock(), time2;
    ifstream orig_file;
    orig_file.open("D:\\Отчеты\\2 семестр Учебная практика\\original1.txt");
    if (!orig_file)
    {
        cout << "Error accessing the file." << endl;
        return;
    }
    vector <string> words;
    int words_count = 0;
    while (!orig_file.eof())
    {
        string new_word;
        orig_file >> new_word;
        for (int i = 0; i < new_word.length(); i++)
        {
            if (!(isalnum(new_word[i]) and new_word[i] <= 127))
            {
                if (new_word.length() == 1)
                    new_word.erase(i);
                else {
                    new_word.erase(i, 1);
                    i--;
                }
            }
        }
        if (new_word.length() > 0) {
            words.push_back(new_word);
            words_count++;
        }
    }
    orig_file.close();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    PRACTICE();
}
