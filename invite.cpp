#include <iostream>
#include <fstream>
#include <windows.h>
#include <unistd.h>
using namespace std;

#define SEP "--------------------------------------------------------------------------------"
#define DIR "./data/"

string get_content(string path);
string get_prompt(unsigned short num);
string get_question(unsigned short num);
string get_answer(unsigned short num);
string get_lock(unsigned short num);
string get_taunt(unsigned short num);
string get_hint(unsigned short num);
string get_success(unsigned short num);

void introduction()
{
    cout << SEP << endl;
    cout << "Welcome to the Invite!" << endl;
    cout << SEP << endl;
    sleep(1);
    cout << "There are 4 challenges in this invite that you'll need to solve." << endl;
    cout << "You can paste your answer when you see INPUT> on your screen." << endl;
    cout << "If you're stuck, ask for a 'cheat' from the host." << endl;
    cout << "Host will give you a code which will unlock the hint." << endl;
    cout << "Enough talking, let's see if you can crack this invite! All the best!" << endl;
    cout << SEP << endl;
    sleep(1);
    cout << "Press enter to continue..." << endl;
    cin.ignore();
}

bool challenge(unsigned short num, unsigned short retry)
{
    string question;
    if (retry == 0)
    {
        cout << get_prompt(num) << endl;
        cout << endl;
        question = get_question(num);
        cout << question << endl;
        cout << endl;
    }
    string answer;
    cout << "INPUT> ";
    getline(cin, answer);
    if (answer == get_lock(num))
    {
        cout << get_taunt(num) << endl;
        cout << get_hint(num) << endl;
        return false;
    }
    return answer == get_answer(num);
}

int main()
{
    introduction();
    unsigned short num = 0;
    unsigned short retry = 0;
    while (num < 4)
    {
        if (retry == 0)
        {
            cout << SEP << endl;
            cout << "CHALLENGE-" + to_string(num + 1) << endl;
            cout << SEP << endl;
            cout << endl;
        }
        if (challenge(num, retry))
        {
            cout << get_success(num) << endl;
            num++;
            retry = 0;
        }
        else if (++retry == 5)
        {
            cout << SEP << endl;
            cout << "Disappointed but not surprised! Try again later." << endl;
            sleep(1);
            cout << "https://media.tenor.com/LCvEt6lB5jwAAAAM/himym-ted.gif" << endl;
            cout << SEP << endl;
            break;
        }
        else if (retry == 3)
            cout << "Pathetic! Contact the host if you want a hint!" << endl;
        else
            cout << "Nope! That's not correct!" << endl;
        cout << endl;
    }
    return EXIT_SUCCESS;
}

// ---------- UTILITY METHODS BELOW ----------

string get_content(string path)
{
    string content = "";
    ifstream stream(path);
    getline(stream, content, '\n');
    stream.close();
    return content;
}

string get_prompt(unsigned short num)
{
    return get_content(DIR + to_string(num) + "/prompt.txt");
}

string get_question(unsigned short num)
{
    return get_content(DIR + to_string(num) + "/question.txt");
}

string get_answer(unsigned short num)
{
    return get_content(DIR + to_string(num) + "/answer.txt");
}

string get_lock(unsigned short num)
{
    return get_content(DIR + to_string(num) + "/lock.txt");
}

string get_taunt(unsigned short num)
{
    return get_content(DIR + to_string(num) + "/taunt.txt");
}

string get_hint(unsigned short num)
{
    return get_content(DIR + to_string(num) + "/hint.txt");
}

string get_success(unsigned short num)
{
    return get_content(DIR + to_string(num) + "/success.txt");
}
