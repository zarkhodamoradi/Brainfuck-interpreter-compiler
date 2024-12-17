#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <stack>

using namespace std;

void compile_opt(const string &code, const string &outputFileName)
{
    string optimized;
    int i = 0;
    char command;
    ofstream outFile(outputFileName);
    if (!outFile.is_open())
    {
        cerr << "Error: Unable to open file '" << outputFileName << "' for writing." << endl;
        return;
    }
    outFile << "#include <iostream>\n"
            << " #include <cstdint> \n"
            << "using namespace std ;\n"
            // << "void checkOutOfBound(const int & pointer , const int & tapeSize){\n"
            // << "     if(pointer>=tapeSize || pointer <0) {\n"
            // << "     cerr << \"Pointer out of bound!\" << endl ;\n"
            // << "     exit(0) ; \n"
            // << "     } }\n"
            << "int main(){\n"
            << "        const int tapeSize=1000 ;\n"
            << "        uint8_t tape[tapeSize]={0} ;\n"
            << "        int pointer =0 ;\n\n";

    stack<int> loopStack;
    while (i < code.size())
    {
        command = code[i];
        if (command == ' ' || command == '\n')
            continue;
        if (command == '[' && i + 4 < code.size() && code[i + 1] == '-' && code[i + 2] == '>')
        {
            vector<pair<int, int>> multipliers;

            uint8_t count = 0;
            int offset = 1;
            int j = i + 3;
            while (j < code.size() && (code[j] == '+' || code[j] == '-' || code[j] == '>'))
            {
                if (code[j] == '+')
                    count++;
                else if (code[j] == '-')
                    count--;
                else if (code[j] == '>')
                {
                    multipliers.push_back({offset, count});
                    count = 0;
                    offset++;
                }

                j++;
                if (code[j] == '<')
                {
                    multipliers.push_back({offset, count});
                    break;
                }
            }

            while (j < code.size() && code[j] == '<')
            {
                offset--;
                j++;
            }
            if (j < code.size() && code[j] == ']' && offset == 0)
            {
                while (!multipliers.empty())
                {
                    int count = multipliers.back().second;
                    if (count != 0)
                    {

                        outFile << "        tape[pointer + (" << to_string(multipliers.back().first) << ")] += tape[pointer] * " << to_string(multipliers.back().second) << ";\n";
                    }
                    multipliers.pop_back();
                }
                outFile << "        tape[pointer] = 0;\n";
                i = j + 1;
                continue;
            }
        }
        if (command == '[' && i + 4 < code.size() && code[i + 1] == '>')
        {
            vector<pair<int, int>> multipliers;

            uint8_t count = 0;
            int offset = 1;
            int j = i + 2;
            while (j < code.size() && (code[j] == '+' || code[j] == '-' || code[j] == '>'))
            {
                if (code[j] == '+')
                    count++;
                else if (code[j] == '-')
                    count--;
                else if (code[j] == '>')
                {
                    multipliers.push_back({offset, count});
                    count = 0;
                    offset++;
                }

                j++;
                if (code[j] == '<')
                {
                    multipliers.push_back({offset, count});
                    break;
                }
            }

            while (j < code.size() && code[j] == '<')
            {
                offset--;
                j++;
            }
            if (j + 1 < code.size() && code[j] == '-' && code[j + 1] == ']' && offset == 0)
            {
                while (!multipliers.empty())
                {
                    int count = multipliers.back().second;
                    if (count != 0)
                    {
                        outFile << "        tape[pointer + (" << to_string(multipliers.back().first) << ")] += tape[pointer] * " << to_string(multipliers.back().second) << ";\n";
                    }
                    multipliers.pop_back();
                }
                outFile << "        tape[pointer] = 0;\n";
                i = j + 2;
                continue;
            }
        }
        if (command == '[' && i + 4 < code.size() && code[i + 1] == '<' )
        {
            vector<pair<int, int>> multipliers;

            uint8_t count = 0;
            int offset = 1;
            int j = i + 2;
            while (j < code.size() && (code[j] == '+' || code[j] == '-' || code[j] == '<') )
            {
                if (code[j] == '+')
                    count++;
                else if (code[j] == '-')
                    count--;
                else if (code[j] == '<')
                {
                    multipliers.push_back({offset, count});
                    count = 0;
                    offset++;
                }

                j++;
                if (code[j] == '>')
                {
                    multipliers.push_back({offset, count});
                    break;
                }
            }

            while (j < code.size() && code[j] == '>')
            {
                offset--;
                j++;
            }
            if (j + 1 < code.size() && code[j] == '-' && code[j + 1] == ']' && offset == 0)
            {
                while (!multipliers.empty())
                {
                    int count = multipliers.back().second;
                    if (count != 0)
                    {
                        outFile << "        tape[pointer - (" << to_string(multipliers.back().first) << ")] += tape[pointer] * " << to_string(multipliers.back().second) << ";\n";
                    }
                    multipliers.pop_back();
                }
                outFile << "        tape[pointer] = 0;\n";
                i = j + 2;
                continue;
            }
        }
        if (command == '[' && i + 4 < code.size() && code[i + 1] == '-' && code[i + 2] == '<')
        {
            vector<pair<int, int>> multipliers;

            uint8_t count = 0;
            int offset = 1;
            int j = i + 3;
            while (j < code.size() && (code[j] == '+' || code[j] == '-' || code[j] == '<'))
            {
                if (code[j] == '+')
                    count++;
                else if (code[j] == '-')
                    count--;
                else if (code[j] == '<')
                {

                    multipliers.push_back({offset, count});

                    count = 0;
                    offset++;
                }

                j++;
                if (code[j] == '>')
                {
                    multipliers.push_back({offset, count});
                    break;
                }
            }

            while (j < code.size() && code[j] == '>')
            {
                offset--;
                j++;
            }
            if (j < code.size() && code[j] == ']' && offset == 0)
            {
                while (!multipliers.empty())
                {
                    int count = multipliers.back().second;
                    if (count != 0)
                    {
                        outFile << "        tape[pointer - (" << to_string(multipliers.back().first) << ")] += tape[pointer] * " << to_string(multipliers.back().second) << ";\n";
                    }
                    multipliers.pop_back();
                }
                outFile << "        tape[pointer] = 0;\n";
                i = j + 1;
                continue;
            }
        }

        // if (command == '[' && i + 4 < code.size() && code[i + 1] == '-' && code[i + 2] == '>')
        // {

        //     int count = 0;
        //     int j = i + 2;
        //     while (j < code.size() && (code[j] == '+' || code[j] == '-'))
        //     {
        //         if (code[j] == '+')
        //             count++;
        //         else
        //             count--;
        //         j++;
        //     }
        //     if (j + 1 < code.size() && code[j] == '<' && code[j + 1] == ']')
        //     {
        //         outFile << "        tape[pointer + 1] = tape[pointer] * " << count << ";\n";
        //         outFile << "        tape[pointer] = 0;\n";
        //         i = j + 2;
        //         continue;
        //     }
        // }
        // if (i + 4 < code.size() && command == '[' && code[i + 1] == '>')
        // {
        //     int count = 0;
        //     int j = i + 2;
        //     while (j < code.size() && (code[j] == '+' || code[j] == '-'))
        //     {
        //         if (code[j] == '+')
        //             count++;
        //         else
        //             count--;
        //         j++;
        //     }
        //     if (j + 2 < code.size() && code[j] == '<' && code[j + 1] == '-' && code[j + 2] == ']')
        //     {
        //         outFile << "        tape[pointer + 1] = tape[pointer] * " << to_string(count) << ";\n";
        //         outFile << "        tape[pointer] = 0;\n";
        //         i = j + 3;
        //         continue;
        //     }
        // }
        if (command == '+' || command == '-')
        {
            int count = 0;
            while (i < code.size() && (code[i] == '+' || code[i] == '-'))
            {
                if (code[i] == '+')
                    count++;
                else
                    count--;
                i++;
            }
            if (count != 0)
            {
                outFile << (count > 0 ? string("        tape[pointer] += ") + to_string(count) + ";\n"
                                      : string("        tape[pointer] -= ") + to_string(-count) + ";\n");
            }
        }

        else if (command == '>' || command == '<')
        {
            int count = 0;
            while (i < code.size() && (code[i] == '>' || code[i] == '<'))
            {
                if (code[i] == '>')
                    count++;
                else
                    count--;

                i++;
            }
            if (count != 0)
            {
                outFile << (count > 0 ? string("        pointer += ") + to_string(count) + ";\n"
                                      : string("        pointer -= ") + to_string(-count) + ";\n");
              //  outFile << "checkOutOfBound(pointer , tapeSize);\n";
            }
        }

        else if (command == '[' && i + 2 < code.size() && code[i + 1] == '-' && code[i + 2] == ']')
        {
            outFile << "        tape[pointer] = 0;\n";
            i += 3;
        }
        else if (command == '[' && i + 2 < code.size() && code[i + 1] == '<' && code[i + 2] == ']')
        {
            outFile << "      if(tape[pointer]!=0)  pointer= 0;\n";
            i += 3;
        }
        else if (command == '[' && i + 2 < code.size() && code[i + 1] == '>' && code[i + 2] == ']')
        {
            outFile << "      if(tape[pointer]!=0)  pointer= tapeSize-1;\n";
            i += 3;
        }

        else if (command == '.')
        {
            outFile << "        cout << (char)tape[pointer];\n";
            i++;
        }
        else if (command == ',')
        {
            outFile << "    tape[pointer] = cin.get();\n";
            i++;
        }
        else if (command == '[')
        {
            loopStack.push(i);
            outFile << "    while (tape[pointer]) {\n";
            i++;
        }
        else if (command == ']')
        {
            if (loopStack.empty())
            {
                cerr << "Syntax Error: Unmatched ']' at position " << i << endl;
                outFile.close();
                return;
            }
            loopStack.pop();
            outFile << "    }\n";
            i++;
        }
    }
    if (!loopStack.empty())
    {
        cerr << "Syntax Error: Unmatched '[' in the code." << endl;
        outFile.close();
        return;
    }

    outFile << "    return 0;\n";
    outFile << "}\n";

    outFile.close();
    cout << "Compilation successful. C++ code written to '" << outputFileName << "'." << endl;
}

int main(int argc, char *argv[])
{
    string inputFile;
    string outputFile;

    if (argc != 4 && argc != 3)
    {
        cerr << "Usage: " << argv[0] << " -o <output_file> <input_file>" << endl;
        cerr << "       " << argv[0] << " <input_file> -o <output_file>" << endl;
        return 1;
    }

    int c;
    while (1)
    {
        c = getopt(argc, argv, "o:");
        if (c < 0)
            break;
        switch (c)
        {
        case 'o':
            outputFile = optarg;
            break;
        default:
            cerr << "Usage: " << argv[0] << " [-o output_file] input_file\n";
            return 1;
        }
    }
    if (optind < argc)
    {
        inputFile = argv[optind];
    }

    if (outputFile.empty())
    {
        cerr << "Error: Output file not specified\n";
        return 1;
    }

    ifstream input(inputFile);
    if (!input.is_open())
    {
        cerr << "Error: Unable to open input file '" << inputFile << "'" << endl;
        return 1;
    }

    string code;
    string line;
    while (getline(input, line))
    {
        code += line;
    }
    input.close();
    compile_opt(code, outputFile);

    return 0;
}
