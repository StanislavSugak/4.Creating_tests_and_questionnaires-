#include <iostream>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>

using namespace std;

class Test
{

private:

    vector<string> question;
    vector<vector<string>> answer;
    vector<int> trueanswer;

    bool ReadQuestionAndAnswer(string path)
    {
        ifstream fin;
        string str;

        vector<vector<string>> answers;
        vector<string> temp;

        try
        {
            fin.open(path);

            if (!fin.is_open() || fin.peek() == std::ifstream::traits_type::eof())
            {
                throw "Error";
            }

            int countq = 0;
            int counta = 0;

            while (!fin.eof())
            {
                getline(fin, str);
                if (str.rfind(". ", 0) == 0)
                {
                    if (countq == 0 && counta > 0)
                    {
                        throw "Error";
                    }
                    countq++;

                    if (countq > 1 && counta < 2)
                    {
                        throw "Error";
                    }
                    else
                    {
                        countq = 1;
                        counta = 0;
                    }

                    SetQuestion(str);

                    if (temp.size() != 0)
                    {
                        answers.push_back(temp);
                        temp.clear();
                    }
                }
                else
                {
                    temp.push_back(str);
                    counta++;
                }
            }

            answers.push_back(temp);
            fin.close();

            ReadAnswer(answers);
        }
        catch (const char* exception)
        {
            return false;
        }
        catch (...)
        {
            return false;
        }

    }

    void ReadAnswer(vector<vector<string>> answers)
    {
        for (int i = 0; i < answers.size(); i++)
        {
            SetAnswer(answers[i]);
        }
    }

    bool ReadTrueAnswer(string path)
    {
        ifstream fin;
        string str;
        int i = 0;

        try
        {
            fin.open(path);

            if (!fin.is_open() || fin.peek() == std::ifstream::traits_type::eof())
            {
                throw "Error";
            }

            while (!fin.eof())
            {
                getline(fin, str);

                size_t pos;
                int number = stoi(str, &pos);

                if (str.length() != 0 && stoi(str) > 0 && stoi(str) < 6 && pos == str.length())
                {
                    SetTrueAnswer(stoi(str));
                }
                else
                {
                    throw "Error";
                }

                i++;
            }
            fin.close();
        }
        catch (const char* exception)
        {
            return false;
        }
        catch (...)
        {
            return false;
        }

        return true;
    }

public:

    void SetQuestion(string question) { this->question.push_back(question); }
    void SetAnswer(vector<string> answer) { this->answer.push_back(answer); }
    void SetTrueAnswer(int trueanswer) { this->trueanswer.push_back(trueanswer); }
    void SetQuestion(string question, int i) { this->question[i] = question; }
    void SetAnswer(vector<string> answer, int i) { this->answer[i] = answer; }
    void SetTrueAnswer(int trueanswer, int i) { this->trueanswer[i] = trueanswer; }

    vector<string> GetQuestion() { return question; }
    vector<vector<string>> GetAnswer() { return answer; }
    vector<int> GetTrueAnswer() { return trueanswer; }

    bool ReadTest()
    {
        string path = "Data\\Test";
        string pathquestion = path + "\\test.txt";
        string pathtrueanswer = path + "\\answer.txt";

        if (!ReadQuestionAndAnswer(pathquestion) || !ReadTrueAnswer(pathtrueanswer))
        {
            return false;
        }

        return true;
    }

    void WriteQuestion()
    {
        string path = "Data\\Test\\test.txt";

        ofstream fout;

        fout.open(path);

        for (int i = 0; i < question.size(); i++)
        {
            if (i != 0)
            {
                fout << "\n" << question[i];
            }
            else
            {
                fout << question[i];
            }

            for (int j = 0; j < answer[i].size(); j++)
            {
                fout << "\n" << answer[i][j];
            }
        }

        fout.close();
    }

    void WriteTrueAnswer()
    {
        string path = "Data\\Test\\answer.txt";

        ofstream fout;

        fout.open(path);

        for (int i = 0; i < trueanswer.size(); i++)
        {
            fout << trueanswer[i];
            if (i != trueanswer.size() - 1)
            {
                fout << "\n";
            }
        }

        fout.close();
    }

    void WriteInConsoleQuestion(int number)
    {
        cout << "\n   " << number + 1 << question[number];

        for (int i = 0; i < answer[number].size(); i++)
        {
            cout << "\n   " << i + 1 << ") " << answer[number][i];
        }
    }

    void DeleteQuestion(int number)
    {
        auto iter = question.cbegin();
        auto iter1 = answer.cbegin();
        auto iter2 = trueanswer.cbegin();

        question.erase(iter + number);
        answer.erase(iter1 + number);
        trueanswer.erase(iter2 + number);
    }

};

class Result
{

private:

    string name;
    vector<string> questions;
    vector<string> answers;
    double result;

    bool ReadOnlyResult(string path)
    {
        ifstream fin;
        string str;

        try
        {
            fin.open(path);

            if (!fin.is_open() || fin.peek() == std::ifstream::traits_type::eof())
            {
                throw "Error";
            }

            while (!fin.eof())
            {
                getline(fin, str);

                size_t pos;
                int number = stoi(str, &pos);

                if (str.length() != 0 && stoi(str) >= 0 && stoi(str) <= 100 && pos == str.length())
                {
                    SetResult(stoi(str));
                }
                else
                {
                    throw "Error";
                }
            }

            fin.close();
        }
        catch (const char* exception)
        {
            return false;
        }
        catch (...)
        {
            return false;
        }

        return true;
    }

    bool ReadAnswer(string path)
    {
        ifstream fin;
        string str;

        try
        {
            fin.open(path);

            if (!fin.is_open() || fin.peek() == std::ifstream::traits_type::eof())
            {
                throw "Error";
            }

            while (!fin.eof())
            {
                getline(fin, str);
                if (str.rfind(". ", 0) == 0)
                {
                    SetQuestion(str);

                    getline(fin, str);
                    if (str.rfind(". ", 0) != 0)
                    {
                        SetAnswer(str);
                    }
                    else
                    {
                        throw "Error";
                    }
                }
                else
                {
                    throw "Error";
                }
            }

            fin.close();
        }
        catch (const char* exception)
        {
            return false;
        }
        catch (...)
        {
            return false;
        }

        return true;
    }

public:

    void SetName(string name) { this->name = name; }
    void SetQuestion(string question) { questions.push_back(question); }
    void SetAnswer(string answer) { answers.push_back(answer); }
    void SetResult(double result) { this->result = result; }
    double GetResult() { return result; }
    string GetName() { return name; }

    bool ReadResult(string name)
    {
        string path = "Data\\Users\\" + name;

        string pathresult = path + "\\result.txt";
        string pathanswer = path + "\\answer.txt";

        if (!ReadOnlyResult(pathresult) || !ReadAnswer(pathanswer))
        {
            return false;
        }
        SetName(name);
    }

    void WriteResult()
    {
        string path = "Data\\Users\\" + name + "\\result.txt";

        ofstream fout;

        fout.open(path);

        fout << result;

        fout.close();
    }

    void WriteAnswer()
    {
        string path = "Data\\Users\\" + name + "\\answer.txt";

        ofstream fout;

        fout.open(path);

        for (int i = 0; i < questions.size(); i++)
        {
            if (i != 0)
            {
                fout << "\n" << questions[i];
            }
            else
            {
                fout << questions[i];
            }

            fout << "\n" << answers[i];
        }

        fout.close();
    }

    void CreateAPath()
    {
        string path = "Data\\Users\\" + name;

        filesystem::create_directories(path);

        ofstream o(path + "\\result.txt");
        ofstream o1(path + "\\answer.txt");
    }

};

class Authorization
{

private:

    string login;
    string password;

public:

    void SetLogin(string login) { this->login = login; }
    void SetPassword(string password) { this->password = password; }
    string GetLogin() { return login; }
    string GetPassword() { return password; }

    bool ReadAuthorization()
    {
        string path = "Data\\Administrator\\authorization.txt";

        ifstream fin;
        string str;

        try
        {
            fin.open(path);

            if (!fin.is_open() || fin.peek() == std::ifstream::traits_type::eof())
            {
                throw "Error";
            }

            getline(fin, str);
            str.erase(remove(str.begin(), str.end(), ' '), str.end());

            if (str.length() != 0)
            {
                SetLogin(str);
            }
            else
            {
                throw "Error";
            }

            getline(fin, str);
            str.erase(remove(str.begin(), str.end(), ' '), str.end());

            if (str.length() != 0)
            {
                SetPassword(str);
            }
            else
            {
                throw "Error";
            }

            fin.close();
        }
        catch (const char* exception)
        {
            return false;
        }
        catch (...)
        {
            return false;
        }

        return true;
    }

    void WriteAuthorization()
    {
        string path = "Data\\Administrator\\authorization.txt";

        ofstream fout;

        fout.open(path);

        fout << login << "\n";
        fout << password;

        fout.close();
    }

};

class Program
{

public:

    static void StartMenu()
    {

        Test test;
        vector<Result> result;
        Authorization admin;

        if (!ReadData(result, test, admin))
        {
            return;
        }

        vector<string> menu{ "Select the menu bar...", "Administrator", "User", "Exit", "Press Enter to continue..." };

        bool show = true;

        while (show)
        {
            int option = SelectMenu(menu);

            ClearConsole();
            show = (option == 1 ? Administrator(test, result, admin) :
                option == 2 ? User(test, result) : Exit());

            ClearConsole();
        }

    }

private:

    static bool ReadData(vector<Result>& result, Test& test, Authorization& admin)
    {
        if (!test.ReadTest())
        {
            cout << "\n   An error has occurred! Check the file that contains the test..." << endl;
            return false;
        }
        if (!admin.ReadAuthorization())
        {
            cout << "\n   An error has occurred! Check the file that contains the authorization..." << endl;
            return false;
        }

        vector<string> name = ReadName();

        for (int i = 0; i < name.size(); i++)
        {
            Result temp;

            if (!temp.ReadResult(name[i]))
            {
                return false;
            }

            result.push_back(temp);
        }

        return true;
    }

    static vector<string> ReadName()
    {
        string path = "Data\\Users";

        vector<string> names;
        string name;

        for (const auto& file : std::filesystem::directory_iterator(path))
        {
            name = file.path().string();
            name.erase(0, name.find_first_of("Users\\") + 7); //вырезает с элемента до 

            names.push_back(name);
        }

        return names;
    }

    static bool Administrator(Test& test, vector<Result> result, Authorization& admin)
    {
        if (Entrance(admin))
        {
            vector<string> menu{ "Select the menu bar...", "View test results", "View questions", "Edit a question", "Add a question", "Delete a question", "Change login details", "Logout", "Press Enter to continue..." };

            bool show = true;

            while (show)
            {
                int option = SelectMenu(menu);

                ClearConsole();
                show = (option == 1 ? ViewTestResults(result) :
                    option == 2 ? ViewQuestions(test) :
                    option == 3 ? EditQuestion(test) :
                    option == 4 ? AddQuestion(test) :
                    option == 5 ? DeleteQuestion(test) :
                    option == 6 ? ChangeLoginDetails(admin) : Logout());

                ClearConsole();
            }
        }

        return true;
    }

    static bool Entrance(Authorization admin)
    {
        string login, password;
        cout << "\n   Login: \n\n   Password: \n\n   Press Enter to continue...";

        CursorPosition(10, 1);
        getline(cin, login);

        CursorPosition(13, 3);
        getline(cin, password);

        ClearConsole();
        return CheckEntrance(admin, login, password);
    }

    static bool CheckEntrance(Authorization admin, string login, string password)
    {
        if (admin.GetLogin() == login && admin.GetPassword() == password)
        {
            return true;
        }
        else
        {
            vector<string> menu{ "Incorrect data. Would you like to try again?", "Yes", "No", "Press Enter to continue..." };

            return WarningMenu(menu) ? Entrance(admin) : false;
        }
    }

    static bool ViewTestResults(vector<Result> result)
    {

        vector<string> menu{ "In what order to output the result? Select the menu bar...", "In ascending order", "In descending order", "In alphabetical order", "In reverse alphabetical order","Back", "Press Enter to continue..." };

        bool show = true;

        while (show)
        {
            int option = SelectMenu(menu);

            ClearConsole();
            show = (option == 5 ? false : SortResult(result, menu, option));

            ClearConsole();
        }

        return true;
    }

    static bool SortResult(vector<Result> result, vector<string> menu, int option)
    {
        cout << "\n   List of results " << menu[option] << ":\n";

        if (option == 1 || option == 2)
        {
            SortAndWriteResultByValue(result, option);
        }
        else
        {
            SortAndWriteResultByName(result, option);
        }

        cout << "\n\n   Press Enter to continue...";
        return EnterMenu();
    }

    static void SortAndWriteResultByValue(vector<Result> result, int i)
    {
        for (int i = 0; i < result.size() - 1; i++)
        {
            for (int j = i + 1; j < result.size(); j++)
            {
                if (result[i].GetResult() > result[j].GetResult())
                {
                    swap(result[i], result[j]);
                }
            }
        }

        WriteSortResult(result, i);
    }

    static void SortAndWriteResultByName(vector<Result> result, int i)
    {
        QuickSort(result, 0, result.size() - 1);
        WriteSortResult(result, i);
    }

    static int partition(vector<Result> result, int low, int high)
    {
        string pivot = result[high].GetName();
        int i = low - 1;
        for (int j = low; j <= high - 1; j++)
        {
            if (result[j].GetName() < pivot)
            {
                i++;
                swap(result[i], result[j]);
            }
        }
        swap(result[i + 1], result[high]);
        return (i + 1);
    }

    static void QuickSort(vector<Result> result, int low, int high)
    {
        if (low < high)
        {
            int pivot = partition(result, low, high);
            QuickSort(result, low, pivot - 1);
            QuickSort(result, pivot + 1, high);
        }
    }

    static void WriteSortResult(vector<Result> result, int i)
    {
        if (i % 2 != 0)
        {
            for (int i = 0; i < result.size(); i++)
            {
                cout << "\n   " << result[i].GetName() << " - " << result[i].GetResult() << "%";
            }
        }
        else
        {
            for (int i = result.size() - 1; i > -1; i--)
            {
                cout << "\n   " << result[i].GetName() << " - " << result[i].GetResult() << "%";
            }
        }
    }

    static bool ViewQuestions(Test test)
    {
        SwipeMenu(test);

        return true;
    }

    static bool EditQuestion(Test& test)
    {
        vector<string> menu{ "What do you want to change? Select the menu bar...", "Question", "Answer", "True answer", "Back", "Press Enter to continue..." };

        int number = SwipeMenu(test) - 1;

        bool show = true;

        while (show)
        {
            ClearConsole();
            int option = SelectMenu(menu);

            ClearConsole();
            show = (option == 1 ? EditQuestion(test, number) :
                option == 2 ? EditAnswer(test, number) :
                option == 3 ? EditTrueAnswer(test, number) : false);

            ClearConsole();
        }

        test.WriteQuestion();
        test.WriteTrueAnswer();

        return true;
    }

    static bool EditQuestion(Test& test, int number)
    {
        test.WriteInConsoleQuestion(number);

        try
        {
            string temp;
            cout << "\n\n   Enter a new question: \n";
            cout << "\n   Press Enter to continue...";

            CursorPosition(25, 3 + test.GetAnswer()[number].size());
            getline(cin, temp);

            string checkquestion = temp;
            checkquestion.erase(remove(checkquestion.begin(), checkquestion.end(), ' '), checkquestion.end());

            if (checkquestion.length() == 0)
            {
                throw string{};
            }

            vector<string> menu{ "Are you sure you want to change the question? Select the menu bar...", "Yes", "No", "Press Enter to continue..." };
            if (WarningMenu(menu))
            {
                test.SetQuestion(". " + temp, number);
            }
        }
        catch (const exception& ex)
        {
            CatchAddQuestions(test, number);
        }
        catch (string message)
        {
            CatchAddQuestions(test, number);
        }

        return true;
    }

    static bool CatchAddQuestions(Test& test, int number)
    {
        vector<string> menu{ "Incorrect data entered! Would you like to try again? Select the menu bar...", "Yes", "No", "Press Enter to continue..." };
        if (WarningMenu(menu))
        {
            return EditQuestion(test, number);
        }

        return true;
    }

    static bool EditAnswer(Test& test, int number)
    {
        ClearConsole();
        test.WriteInConsoleQuestion(number);

        string num;

        try
        {
            cout << "\n\n   Enter the question number: ";
            getline(cin, num);

            if (stoi(num) < 1 || stoi(num) > test.GetAnswer()[number].size())
            {
                throw string{};
            }

            string temp;
            cout << "\n   Enter a new question: ";

            cin.ignore();
            getline(cin, temp);

            string checkquestion = temp;
            checkquestion.erase(remove(checkquestion.begin(), checkquestion.end(), ' '), checkquestion.end());
            if (checkquestion.length() == 0)
            {
                throw string{};
            }

            vector<string> menu{ "Are you sure you want to change the answer? Select the menu bar...", "Yes", "No", "Press Enter to continue..." };
            if (WarningMenu(menu))
            {
                vector<string> tempvector = test.GetAnswer()[number];
                tempvector[stoi(num) - 1] = temp;
                test.SetAnswer(tempvector, number);
            }
        }
        catch (const exception& ex)
        {
            CatchEditAnswers(test, number, 0);
        }
        catch (string message)
        {
            CatchEditAnswers(test, number, 0);
        }

        return true;
    }

    static bool EditTrueAnswer(Test& test, int number)
    {
        ClearConsole();
        test.WriteInConsoleQuestion(number);

        cout << "\n\n   The last correct answer: " << test.GetTrueAnswer()[number] << "\n\n   Enter a new true answer: \n" << "\n   Press Enter to continue...";

        CursorPosition(27, 5 + test.GetAnswer()[number].size());

        string temp;

        try
        {
            getline(cin, temp);

            if (stoi(temp) < 1 || stoi(temp) > test.GetAnswer()[number].size())
            {
                throw string{};
            }

            vector<string> menu{ "Are you sure you want to change the true answer? Select the menu bar...", "Yes", "No", "Press Enter to continue..." };
            if (WarningMenu(menu))
            {
                test.SetTrueAnswer(stoi(temp), number);
            }
        }
        catch (const exception& ex)
        {
            CatchEditAnswers(test, number, 1);
        }
        catch (string message)
        {
            CatchEditAnswers(test, number, 1);
        }

        return true;
    }

    static bool CatchEditAnswers(Test& test, int number, int answerortrueanswer)
    {
        vector<string> menu{ "Incorrect data entered! Would you like to try again? Select the menu bar...", "Yes", "No", "Press Enter to continue..." };
        if (WarningMenu(menu))
        {
            return answerortrueanswer == 0 ? EditAnswer(test, number) : EditTrueAnswer(test, number);
        }

        return true;
    }

    static bool AddQuestion(Test& test)
    {
        cout << "\n   Enter the information and Press Enter to continue..." << "\n\n   Enter a new question: " << "\n\n   Enter the number of responses: ";

        string question;
        string checkquestion;
        string countanswer;
        vector<string> answer;
        string trueanswer;

        try
        {
            CursorPosition(25, 3);
            getline(cin, question);

            checkquestion = question;
            checkquestion.erase(remove(checkquestion.begin(), checkquestion.end(), ' '), checkquestion.end());

            if (checkquestion.length() == 0)
            {
                throw string{};
            }

            CursorPosition(34, 5);
            getline(cin, countanswer);

            if (stoi(countanswer) < 1 || stoi(countanswer) > 5)
            {
                throw string{};
            }

            for (int i = 0; i < stoi(countanswer); i++)
            {
                string tempanswer;
                cout << "\n   " << i + 1 << ") ";

                getline(cin, tempanswer);

                checkquestion = tempanswer;
                checkquestion.erase(remove(checkquestion.begin(), checkquestion.end(), ' '), checkquestion.end());

                if (checkquestion.length() == 0)
                {
                    throw string{};
                }

                answer.push_back(tempanswer);
            }

            cout << "\n   Enter the correct answer variation: ";
            getline(cin, trueanswer);

            if (stoi(trueanswer) < 1 || stoi(trueanswer) > stoi(countanswer))
            {
                throw string{};
            }

            vector<string> menu{ "Are you sure you want to change the true answer? Select the menu bar...", "Yes", "No", "Press Enter to continue..." };
            if (WarningMenu(menu))
            {
                AddQuestion(test, ". " + question, answer, stoi(trueanswer));
            }

        }
        catch (const exception& ex)
        {
            CatchAddAnswers(test);
        }
        catch (string message)
        {
            CatchAddAnswers(test);
        }

        return true;
    }

    static bool CatchAddAnswers(Test& test)
    {
        vector<string> menu{ "Incorrect data entered! Would you like to try again? Select the menu bar...", "Yes", "No", "Press Enter to continue..." };
        if (WarningMenu(menu))
        {
            return AddQuestion(test);
        }

        return true;
    }

    static void AddQuestion(Test& test, string question, vector<string> answer, int trueanswer)
    {
        test.SetQuestion(question);
        test.SetAnswer(answer);
        test.SetTrueAnswer(trueanswer);

        test.WriteQuestion();
        test.WriteTrueAnswer();
    }

    static bool DeleteQuestion(Test& test)
    {
        int number = SwipeMenu(test) - 1;

        vector<string> menu{ "Are you sure you want to delete the question? Select the menu bar...", "Yes", "No", "Press Enter to continue..." };

        if (WarningMenu(menu))
        {
            DeleteQuestion(test, number);

            ClearConsole();
            cout << "\n   The question was successfully deleted!\n\n   Press Enter to continue...";
            return EnterMenu();
        }

        return true;
    }

    static void DeleteQuestion(Test& test, int number)
    {
        test.DeleteQuestion(number);
        test.WriteQuestion();
        test.WriteTrueAnswer();
    }

    static bool ChangeLoginDetails(Authorization& admin)
    {
        vector<string> menu{ "What do you want to change? Select the menu bar...", "Login", "Password", "Back", "Press Enter to continue..." };

        bool show = true;

        while (show)
        {
            int option = SelectMenu(menu);

            ClearConsole();
            show = (option != 3 ? ChangeDetailsAuthorization(admin, option) : false);

            ClearConsole();
        }

        admin.WriteAuthorization();
        return true;
    }

    static bool ChangeDetailsAuthorization(Authorization& admin, int option)
    {
        if (option == 1)
        {
            cout << "\n   Enter a new login: \n";
        }
        else
        {
            cout << "\n   Enter a new password: \n";
        }
        cout << "\n   Press Enter to continue...";

        option == 1 ? CursorPosition(22, 1) : CursorPosition(25, 1);

        string temp;
        try
        {
            getline(cin, temp);

            string checkname = temp;
            checkname.erase(remove(checkname.begin(), checkname.end(), ' '), checkname.end());
            if (checkname.length() == 0)
            {
                throw string{};
            }

            vector<string> menu{ "Do you confirm your actions on data changes? Select the menu bar...", "Yes", "No", "Press Enter to continue..." };
            WarningMenu(menu);

            return ChangeDetailsAuthorization(admin, temp, option);
        }
        catch (const exception& ex)
        {
            CatchAuthorization(admin, option);
        }
        catch (string message)
        {
            CatchAuthorization(admin, option);
        }

        return true;
    }

    static bool CatchAuthorization(Authorization& admin, int option)
    {
        vector<string> menu{ "Incorrect data entered! Would you like to try again? Select the menu bar...", "Yes", "No", "Press Enter to continue..." };
        if (WarningMenu(menu))
        {
            return ChangeDetailsAuthorization(admin, option);
        }

        return true;
    }

    static bool ChangeDetailsAuthorization(Authorization& admin, string temp, int option)
    {
        if (option == 1)
        {
            admin.SetLogin(temp);
        }
        else
        {
            admin.SetPassword(temp);
        }

        return true;
    }

    static bool User(Test test, vector<Result>& result)
    {
        vector<string> menu{ "Select the menu bar...", "Take the test", "View results", "Back", "Press Enter to continue..." };

        bool show = true;

        while (show)
        {
            int option = SelectMenu(menu);

            ClearConsole();
            show = (option == 1 ? TakeTheTest(test, result) :
                option == 2 ? ViewTestResults(result) : false);

            ClearConsole();
        }

        return true;
    }

    static bool TakeTheTest(Test test, vector<Result>& result)
    {
        string name;
        vector<string> question;
        Result temp;
        int number;
        int counttrue = 0;

        if (WriteNickname(result, name))
        {
            temp.SetName(name);
            for (int i = 0; i < test.GetQuestion().size(); i++)
            {
                question.push_back(test.GetQuestion()[i]);
                for (int j = 0; j < test.GetAnswer()[i].size(); j++)
                {
                    question.push_back(test.GetAnswer()[i][j]);
                }

                number = MenuQuestion(question, i + 1);

                temp.SetQuestion(question[0]);
                temp.SetAnswer(question[number]);

                if (number == test.GetTrueAnswer()[i])
                {
                    counttrue++;
                }

                question.clear();
            }

            temp.SetResult((double)counttrue * 100 / (double)test.GetQuestion().size());

            return CheckAnswer(result, temp);

        }

        return true;
    }

    static bool CheckAnswer(vector<Result>& result, Result temp)
    {

        vector<string> menu{ "Do you want to save the result? Select the menu bar...", "Yes", "No", "Press Enter to continue..." };
        if (WarningMenu(menu))
        {
            temp.CreateAPath();

            result.push_back(temp);
            for (int i = 0; i < result.size(); i++)
            {
                result[i].WriteAnswer();
                result[i].WriteResult();
            }
        }

        return ShowResult(temp);
    }

    static bool ShowResult(Result temp)
    {
        cout << "\n   Your result: " << temp.GetResult() << "%";
        cout << "\n\n   Press Enter to continue...";

        return EnterMenu();
    }

    static bool WriteNickname(vector<Result> result, string& name)
    {
        try
        {
            string checkname;

            cout << "\n   Enter your nickname: " << "\n\n   Press Enter to continue...";
            CursorPosition(24, 1);
            getline(cin, name);

            checkname = name;
            checkname.erase(remove(checkname.begin(), checkname.end(), ' '), checkname.end());
            if (checkname.length() == 0)
            {
                throw string{};
            }

            for (int i = 0; i < result.size(); i++)
            {
                if (result[i].GetName() == name)
                {
                    throw string{};
                }
            }
        }
        catch (string message)
        {
            return CheckNickname(result, name);
        }

        return true;
    }

    static bool CheckNickname(vector<Result> result, string& name)
    {
        vector<string> menu{ "Incorrect data entered! Would you like to try again? Select the menu bar...", "Yes", "No", "Press Enter to continue..." };
        if (WarningMenu(menu))
        {
            return WriteNickname(result, name);
        }

        return false;
    }

    static int SelectMenu(vector<string> menu)
    {
        int option = 1;
        bool show = true;

        string colorSelect = "\u001b[38;5;240m";
        string colorNoSelect = "\u001b[0m";

        while (show)
        {

            COORD coord = { 0,0 };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

            cout << endl;

            for (int i = 0; i < menu.size(); i++)
            {
                string a = option == i ? " - " + colorSelect + menu[i] + colorNoSelect + " - " : "   " + menu[i] + "   ";
                cout << a << endl;

                if (i == 0 || i == menu.size() - 2)
                {
                    cout << endl;
                }

                CursorOFF();
            }

            switch (_getch())
            {
            case 0x50:
                option = (option == menu.size() - 2 ? 1 : option + 1);
                break;

            case 0x48:
                option = (option == 1 ? menu.size() - 2 : option - 1);
                break;

            case 0x0D:
                show = false;
                return option;

            default:
                break;
            }

        }

        return option;
    }

    static int SwipeMenu(Test test)
    {
        int option = 1;
        bool show = true;

        while (show)
        {
            ClearConsole();

            COORD coord = { 0,0 };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

            cout << "\n   " << option << test.GetQuestion()[option - 1] << endl;

            for (int j = 0; j < test.GetAnswer()[option - 1].size(); j++)
            {
                cout << "   " << j + 1 << ")" << test.GetAnswer()[option - 1][j] << endl;
            }

            cout << "\n   Press Enter to continue or press left/right to move...";
            CursorOFF();

            switch (_getch())
            {
            case 0x4D:
                option = (option == test.GetQuestion().size() ? 1 : option + 1);
                break;

            case 0x4B:
                option = (option == 1 ? test.GetQuestion().size() : option - 1);
                break;

            case 0x0D:
                show = false;
                return option;

            default:
                break;
            }

        }

        return option;
    }

    static int MenuQuestion(vector<string> menu, int number)
    {
        ClearConsole();

        int option = 1;
        bool show = true;

        string colorSelect = "\u001b[38;5;240m";
        string colorNoSelect = "\u001b[0m";

        menu.push_back("Press Enter to continue...");

        while (show)
        {
            COORD coord = { 0,0 };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

            cout << endl;

            cout << "   " << number << menu[0] << "\n\n";

            for (int i = 1; i < menu.size() - 1; i++)
            {
                string a = option == i ? "   " + to_string(i) + ") " + colorSelect + menu[i] + colorNoSelect : "   " + to_string(i) + ") " + menu[i];
                cout << a << endl;

                if (i == menu.size() - 2)
                {
                    cout << endl;
                }

                CursorOFF();
            }
            cout << "   " << menu[menu.size() - 1];

            switch (_getch())
            {
            case 0x50:
                option = (option == menu.size() - 2 ? 1 : option + 1);
                break;

            case 0x48:
                option = (option == 1 ? menu.size() - 2 : option - 1);
                break;

            case 0x0D:
                show = false;
                return option;

            default:
                break;
            }

        }

        return option;
    }

    static bool EnterMenu()
    {
        CursorOFF();

        bool show = true;
        while (show)
        {
            switch (_getch())
            {
            case 0x0D:
                show = false;
                return true;

            default:
                break;
            }
        }

        return true;
    }

    static bool WarningMenu(vector<string> menu)
    {
        ClearConsole();
        CursorOFF();

        bool show = true;

        while (show)
        {
            int option = SelectMenu(menu);

            ClearConsole();
            show = (option == 1 ? true : false);

            return show;

        }

        return true;
    }

    static bool Logout()
    {
        vector<string> menu{ "Do you want to log out of your account? Select the menu bar...", "Yes", "No", "Press Enter to continue..." };

        bool show;
        return show = (SelectMenu(menu) == 1 ? false : true);
    }

    static bool Exit()
    {
        vector<string> menu{ "Do you want to exit the program? Select the menu bar...", "Yes", "No", "Press Enter to continue..." };

        bool show;
        return show = (SelectMenu(menu) == 1 ? false : true);
    }

    static void ClearConsole()
    {
        system("cls");
    }

    static void CursorPosition(int x, int y)
    {
        HANDLE handle;
        COORD coordinates;
        handle = GetStdHandle(STD_OUTPUT_HANDLE);
        coordinates.X = x;
        coordinates.Y = y;
        SetConsoleCursorPosition(handle, coordinates);
    }

    static void CursorOFF()
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO structCursorInfo;
        GetConsoleCursorInfo(handle, &structCursorInfo);
        structCursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(handle, &structCursorInfo);
    }

};

int main()
{
    setlocale(LC_ALL, "Russian"); // Подключение русского языка
    SetConsoleCP(1251);

    Program pr;
    pr.StartMenu();

    return 0;
}
