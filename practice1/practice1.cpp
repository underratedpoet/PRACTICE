//#include <thread>
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <clocale>
#include <ctime>
using namespace std;

class ofwords
{
public:
 
    int length = 0;
    int count = 0;
};


void doMerge(vector<string> &words, int left, int right)
{
    vector<string> mid_word;
    for (int i = 0; i <= (right - left); i++)
    {
        mid_word.push_back(words[left + i]);
    }
    int i = 0, j = (right - left) / 2 + 1, q = left;
    while (i <= ((right - left) / 2) or j <= (right - left))
    {
        if (i <= ((right - left) / 2) and j <= (right - left))
        {
            if (mid_word[i].size() > mid_word[j].size())
            {
                words[q] = mid_word[i];
                q++;
                i++;
            }
            else
            {
                words[q] = mid_word[j];
                q++;
                j++;
            }
        }
        else if (j > (right - left))
        {
            words[q] = mid_word[i];
            q++;
            i++;
        }
        else if (i > ((right - left) / 2))
        {
            words[q] = mid_word[j];
            q++;
            j++;
        }
    }

}

void sortMerge(vector<string> &words, int left, int right)
{
    if (left != right)
    {
        sortMerge(words, left, left + ((right - left) / 2));
        sortMerge(words, left + ((right - left) / 2) + 1, right);
        doMerge(words, left, right);
    }
}

/*
void threads_and_sort(vector<string>& words)
{
    int parts = words.size() / 4;
    thread thr1(merge_sort, ref(words), 0, words.size() / 2 - 1);
    thread thr2(merge_sort, ref(words), words.size() / 2, words.size() - 1);
    thr1.join();
    thr2.join();
    merge(words, 0, words.size() - 1);
}
*/  

string redactString(string word)
{
    for (int i = 0; i < word.length(); i++)
    {
        if (!(isalnum(word[i]) and word[i] <= 127))
        {
            if (word.length() == 1)
                word.erase(i);
            else {
                word.erase(i, 1);
                i--;
            }
        }
    }
    return word;
}

void recieveInput(vector<string> &words,string &path)
{
    ifstream orig_file;
    bool check = false;
    while (check == false) {
        check = true;
        orig_file.open(path);
        if (!orig_file.is_open())
        {
            cout << "Error accessing the file." << endl;
            cout << "Введите полный путь к текстовому файлу" << endl;
            getline(cin, path);
            check = false;
        }
    }


    while (!orig_file.eof())
    {
        string new_word;
        orig_file >> new_word;
        new_word = redactString(new_word);
        if (new_word.length() > 0) {
            words.push_back(new_word);
        }
    }
    orig_file.close();
}

void recordResult(vector<string>& words, char origpathnum)
{
    ofstream result;
    string txt = ".txt";
    string respath = "D:\\practice_txt_files\\result";
    respath += origpathnum + txt;
    cout << respath;
    result.open(respath);
    for (int i = 0; i < words.size(); i++)
        result << words[i] << " ";
    result.close();
}

int findInVector(vector <ofwords> vtr, int number)
{
    for (int i = 0; i < vtr.size(); i++)
    {
        if (vtr[i].length == number)
            return i;
    }
    return -1;
}

void countAllLengths(vector<string> &words, vector<ofwords> &word_length_count)
{
    for (int i = 0; i < words.size(); i++)
    {
        int finded = findInVector(word_length_count, words[i].length());
        if (finded == -1)
        {
            ofwords ofwords;
            ofwords.length = words[i].length();
            ofwords.count++;
            word_length_count.push_back(ofwords);
        }
        else
        {
            word_length_count[finded].count++;
        }
    }
}

void doAndRecordAnalysis(vector<string> &words, int time, string origpath)
{
    ifstream orig_file;
    ofstream analysis;
    string txt = ".txt";
    string anpath = "D:\\practice_txt_files\\analysis";
    anpath += origpath[origpath.length() - 5] + txt;
    cout << anpath;
    analysis.open(anpath);
    cout << "Исходный текст: " << endl;
    analysis << "Исходный текст: " << endl;
    orig_file.open(origpath);
    while (!orig_file.eof())
    {
        string line;
        getline(orig_file, line);
        cout << line << endl;
        analysis << line << endl;
    }
    orig_file.close();
    cout << endl << "Вариант 18: латиница, по кол-ву символов в слове, по убыванию, учитывать числа, сортировка слиянием.\nКоличество слов: " << words.size()
        << endl << "Время сортировки: " << time << " мс\nСтатистика (количество слов каждой длины):" << endl;
    analysis << endl << "Вариант 18: латиница, по кол-ву символов в слове, по убыванию, учитывать числа, сортировка слиянием.\nКоличество слов: " << words.size()
        << endl << "Время сортировки: " << time << " мс\nСтатистика (количество слов каждой длины):" << endl;
    vector<ofwords> word_length_count;
    countAllLengths(words, word_length_count);
    for (int i = word_length_count.size()-1; i >= 0; i--)
    {
        cout << word_length_count[i].length << " - " << word_length_count[i].count << endl;
        analysis << word_length_count[i].length << " - " << word_length_count[i].count << endl;
    }
}



void doPractice()
{
    cout << "Введите полный путь к текстовому файлу" << endl;
    string path;
    getline(cin, path);

    vector <string> words;

    recieveInput(words,path);

    int time0 = clock();
    sortMerge(words, 0, words.size() - 1);
    int time = clock() - time0;

    recordResult(words,path[path.length()-5]);

    doAndRecordAnalysis(words, time, path);

}

int main()
{
    setlocale(0, "");
    doPractice();
}

/* 1 - 13160, 75
   2 - 4306, 25
   3 - 7309, 42 
   4 - 
   5 - 
   6 - 
   7 - 
   8 - 
   9 - 
   10 - 
*/