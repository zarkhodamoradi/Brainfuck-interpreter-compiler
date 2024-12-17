#include <iostream>
#include <fstream>
#include <cstdint>
#include <stack>
using namespace std;

void interpretCode(string &code)
{

    const int tapeSize = 100000;
    uint8_t tape[tapeSize] = {0};
    int pointer = 0;
    stack<char> st;
    stack<int> loop;
    for (int i = 0; i < code.size(); i++)
    {

        if (code[i] == ' ' || code[i] == '\n')
            continue;
        else if (code[i] == '>')
        {
            pointer++;
            if (pointer >= tapeSize)
            {
                cerr << "Pointer out of bound" << endl;
                pointer = tapeSize - 1;
                return;
            }
        }
        else if (code[i] == '<')
        {
            pointer--;
            if (pointer < 0)
            {
                cerr << "Pointer out of bound" << endl;
                pointer = 0;
                return;
            }
        }
        else if (code[i] == '+')
        {
          // tape[pointer] = (tape[pointer] + 1 ) % 256;
          tape[pointer]++ ; 
        }
        else if (code[i] == '-')
        {
            tape[pointer]--; 
           // tape[pointer] = (tape[pointer] - 1 + 256) % 256;
        }
        else if (code[i] == '.')
        {
            cout << (char)tape[pointer];
        }
        else if (code[i] == ',')
        {
            tape[pointer] = cin.get();
        }
        else if (code[i] == '[')
        {

            if (tape[pointer] == 0)
            {
                st.push(code[i]);
                i++;
                while (!st.empty() && i < code.size())
                {
                    if (code[i] == '[')
                    {
                        st.push(code[i]);
                    }
                    else if (code[i] == ']')
                    {
                        if (!st.empty() && st.top() == '[')
                        {
                            st.pop();
                        }
                        else
                        {
                            cerr << "Syntax Error: '[' at position " << i << "is unmatched." << endl;
                            return;
                        }
                    }
                    i++;
                }
                if (!st.empty())
                {
                    cerr << "Syntax Error: '[' at position " << i << "is unmatched." << endl;
                    return;
                }
                i--;
            }
            else
            {
                int temp = i;
                st.push(code[i]);
                temp++;
                while (!st.empty() && temp < code.size())
                {
                    if (code[temp] == '[')
                    {
                        st.push(code[temp]);
                    }
                    else if (code[temp] == ']')
                    {
                        if (!st.empty() && st.top() == '[')
                        {
                            st.pop();
                        }
                        else
                        {
                            cerr << "Unmatched [ at position " << temp << endl;
                            return;
                        }
                    }
                    temp++;
                }
                if (!st.empty())
                {
                    cerr << "Unmatched [ at position " << temp << endl;
                    return;
                }

                loop.push(i);
            }
        }
        else if (code[i] == ']')
        {
            if (loop.empty())
            {
                cerr << "Unmatched ] at position " << i << endl;
                return;
            }
            if (tape[pointer] == 0)
            {
                loop.pop();
            }
            else
            {
                i = loop.top();
            }
        }
        else
        {
            cerr << "Syntax error at " << i << endl;
        }
    }
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Unable to open file '" << filename << "'" << endl;
        return 1;
    }

    string code, line;
    while (getline(file, line))
    {
        code += line;
    }
    file.close();
    interpretCode(code);
}