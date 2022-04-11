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

void doMerge(vector<string>& words, int left, int right)
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

void sortMerge(vector<string>& words, int left, int right)
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

void recieveInput(vector<string>& words)
{
    ifstream orig_file;
    orig_file.open("D:\\Отчеты\\2 семестр Учебная практика\\original1.txt");
    if (!orig_file.is_open())
    {
        cout << "Error accessing the file." << endl;
        return;
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

void recordResult(vector<string>& words)
{
    ofstream result;
    result.open("D:\\Отчеты\\2 семестр Учебная практика\\result1.txt");
    for (int i = 0; i < words.size(); i++)
        result << words[i] << " ";
    result.close();
}

int findInVector(vector< array <int, 2>  > vtr, int number)
{
    for (int i = 0; i < vtr.size(); i++)
    {
        if (vtr[i][0] == number)
            return i;
    }
    return -1;
}

void countAllLengths(vector<string>& words, vector<array <int, 2> >& word_length_count)
{
    for (int i = 0; i < words.size(); i++)
    {
        int finded = findInVector(word_length_count, words[i].length());
        if (finded == -1)
        {
            array<int, 2> values = { words[i].length(), 1 };
            word_length_count.push_back(values);
        }
        else
        {
            word_length_count[finded][1] += 1;
        }
    }
}

void doAndRecordAnalysis(vector<string>& words, int time)
{
    ifstream orig_file;
    ofstream analysis;
    analysis.open("D:\\Отчеты\\2 семестр Учебная практика\\analysis1.txt");
    analysis << "Исходный текст: " << endl;
    orig_file.open("D:\\Отчеты\\2 семестр Учебная практика\\original1.txt");
    while (!orig_file.eof())
    {
        string line;
        getline(orig_file, line);
        analysis << line << endl;
    }
    orig_file.close();
    analysis << endl << "Вариант 18: латиница, по кол-ву символов в слове, по убыванию, учитывать числа, сортировка слиянием.\nКоличество слов: " << words.size()
        << endl << "Время сортировки: " << time << " мс\nСтатистика (количество слов каждой длины):" << endl;
    vector<array <int, 2> > word_length_count;
    countAllLengths(words, word_length_count);
    for (int i = 0; i < word_length_count.size(); i++)
    {

        analysis << word_length_count[i][0] << " - " << word_length_count[i][1] << endl;
    }
}



void PRACTICE()
{
    vector <string> words;

    recieveInput(words);

    int time0 = clock();
    sortMerge(words, 0, words.size() - 1);
    int time = clock() - time0;

    recordResult(words);

    doAndRecordAnalysis(words, time);

}

int main()
{
    setlocale(LC_ALL, "Russian");
    PRACTICE();
}
