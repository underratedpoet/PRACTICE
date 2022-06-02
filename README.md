# practice

Задача - создать алгоритм сортировки текста (от 3 тыс. символов до 15 тыс. символов). 
Индивидуальное задание: латиница, по кол-ву символов в слове, по убыванию, учитывать числа, сортировка слиянием.

Была написана функция чтения файла: каждое слово (последовательность символов, разделенная пробелами/переносами строки), перед тем, как быть добавленным в вектор, проверялось на наличие игнорируемых символов, которые, при нахождении, удалялись.
```C++
string redactString(string word) // удаляет из слова несортируемые символы
{
    for (int i = 0; i < word.length(); i++)
    {
        if (!(isalnum(word[i]) and word[i] <= 127))  // если не латинская буква и не цифра, удаляет
        {
            if (word.length() == 1)
                word.erase(i);                       // если длина слова "1", другие параметры для erase
            else {
                word.erase(i, 1);                   
                i--;                                 // после удаления символа следующий символ встает на место с индексом удаленного
            }                                        // поэтому чтобы пройтись и по этому символу, i на след. шаге нужно оставить таким же
        }
    }
    return word;
}

void recieveInput(vector<string> &words,string &path) // проверяет корректность введенного с консоли пути к файлу
{                                                     // и при ошибке просит ввести заново
    ifstream orig_file;
    bool check = false;
    while (check == false) {
        check = true;
        orig_file.open(path);
        if (!orig_file.is_open() or path.substr(path.length()-4, path.length() - 1) != ".txt")
        {
            cout << "Error accessing the file." << endl;
            cout << "Введите полный путь к текстовому файлу" << endl;
            getline(cin, path);
            check = false;
        }
    }


    while (!orig_file.eof()) // пока файл не закончится, добавляет каждое слово (разделенное пробелами или переносми строки) в вектор
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
```
Была написана функция сортировки слиянием: массив (вектор) слов делился на две части (условно, копии массива в этот момент не создавались) до момента, когда часть становилась равной одному слову. Затем, в обратном порядке, части соединялись, сортируясь по убыванию. Копия сортируемой области создавалась только на время ее сортировки.
```C++
void doMerge(vector<string> &words, int left, int right) // сортировка слиянием, принимает правый и левый индексы
{
    vector<string> mid_word;                             // создание и заполнение промежуточного (сортируемая часть соновного) вектора
    for (int i = 0; i <= (right - left); i++)
    {
        mid_word.push_back(words[left + i]);
    }
    int i = 0, j = (right - left) / 2 + 1, q = left;
    while (i <= ((right - left) / 2) or j <= (right - left))
    {
        if (i <= ((right - left) / 2) and j <= (right - left)) // i - проходится по левой половине вектора, j - по правой
        {
            if (mid_word[i].size() > mid_word[j].size())       // сравнивает и ставит минимальное в основной вектор
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
        else if (j > (right - left))                           // вставляет оставшиеся, если в одной из половин слова закончились
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

void sortMerge(vector<string> &words, int left, int right)  // рекурсивное разделение вектора на две части
{
    if (left != right)
    {
        sortMerge(words, left, left + ((right - left) / 2));
        sortMerge(words, left + ((right - left) / 2) + 1, right);// делит на две части
        doMerge(words, left, right);                             // сортирует две отсортированные глубже части
    }
}
```

Был написан алгоритм анализа данных: в текстовый файл выводились исходный текст, индивидуальное задание, количество слов, время сортировки, статистика (количество слов каждой длины).
```C++
void recordResult(vector<string>& words, char origpathnum) // записывает в (созданный на основе названия оригинального файла) файл остортированный вектор слов
{
    ofstream result;
    string txt = ".txt";
    string respath = "D:\\practice_txt_files\\result";
    respath += origpathnum + txt;
    result.open(respath);
    for (int i = 0; i < words.size(); i++)
        result << words[i] << endl;
    result.close();
}

int findInVector(vector <ofwords> vtr, int number)  // проверяет наличие в векторе ofwords (хранящих данные о количестве слов каждой длины)
{                                                   // ofwords с конкретной длиной и возвращает индекс, или -1, если такого еще нет
    for (int i = 0; i < vtr.size(); i++)
    {
        if (vtr[i].length == number)
            return i;
    }
    return -1;
}

void countAllLengths(vector<string> &words, vector<ofwords> &word_length_count) // сохраняет данные о количестве слов каждой длины,
{                                                                               // проходясь по отсортированному массиву
    for (int i = 0; i < words.size(); i++)
    {
        int finded = findInVector(word_length_count, words[i].length());        // если слова такой длины еще не попадалось, добавляет в вектор 
        if (finded == -1)                                                       // ofwords этой длины c count = 1
        {
            ofwords ofwords;
            ofwords.length = words[i].length();
            ofwords.count++;
            word_length_count.push_back(ofwords);
        }
        else
        {
            word_length_count[finded].count++;                                   // если есть, увеличивает счетчик
        }
    }
}

void doAndRecordAnalysis(vector<string> &words, int time, string origpath)       // выводит в (созанный на основе оригинаьного файла) файл и консоль
{                                                                                
    ifstream orig_file;
    ofstream analysis;
    string txt = ".txt";
    string anpath = "D:\\practice_txt_files\\analysis";
    anpath += origpath[origpath.length() - 5] + txt;                             // данные о тексте:
    analysis.open(anpath);
    cout << "Исходный текст: " << endl;
    analysis << "Исходный текст: " << endl;
    orig_file.open(origpath);
    while (!orig_file.eof())                                                     // исходный текст по строкам копирует из оригинального файла
    {
        string line;
        getline(orig_file, line);
        cout << line << endl;
        analysis << line << endl;
    }
    orig_file.close();                                                           // условия варианта
    cout << endl << "Вариант 18: латиница, по кол-ву символов в слове, по убыванию, учитывать числа, сортировка слиянием.\nКоличество слов: " << words.size()
        << endl << "Время сортировки: " << time << " мс\nСтатистика (количество слов каждой длины):" << endl;
    analysis << endl << "Вариант 18: латиница, по кол-ву символов в слове, по убыванию, учитывать числа, сортировка слиянием.\nКоличество слов: " << words.size()
        << endl << "Время сортировки: " << time << " мс\nСтатистика (количество слов каждой длины):" << endl;
    vector<ofwords> word_length_count;                                           // время сортировки
    countAllLengths(words, word_length_count);                                   // данные о количестве слов каждой длины
    for (int i = word_length_count.size()-1; i >= 0; i--)
    {
        cout << word_length_count[i].length << " - " << word_length_count[i].count << endl;
        analysis << word_length_count[i].length << " - " << word_length_count[i].count << endl;
    }
}
```
Отдельные части алгоритма перемещены в функции, функции переименованы.

Вместо двумерного массива создан массив (вектор) классов "ofwords", хранящих данные о количестве слов определенной длины. Добавлен ввод пути к файлу original через консоль, добавлено автоматическое создание имен файлов result и analysis на основе последнего символа файла original (к примеру, для файла original3.txt создавались бы файлы result3.txt и analysis3.txt).
```C++
class ofwords   // класс для хранения количества слов каждой длины
{
public:
 
    int length = 0;
    int count = 0;
};
```
