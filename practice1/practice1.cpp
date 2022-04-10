#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <clocale>
#include <ctime>
using namespace std;

void merge_sort(vector<string>& words, int left, int right)
{
    if (left != right)
    {
        merge_sort(words, left, left + ((right - left) / 2));
        merge_sort(words, left + ((right - left) / 2) + 1, right);
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
}


void PRACTICE()
{
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
    int time0 = clock();
    merge_sort(words, 0, words.size() - 1);
    int time = clock() - time0;
    ofstream result;
    result.open("D:\\Отчеты\\2 семестр Учебная практика\\result1.txt");
    for (int i = 0; i < words.size(); i++)
        result << words[i] << " ";
    result << endl << time << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    PRACTICE();
}
