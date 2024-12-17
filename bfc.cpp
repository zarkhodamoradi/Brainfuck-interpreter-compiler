#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stack>

using namespace std;
void Compile_bf(const string &code, const string &outputFileName)
{
    ofstream outFile(outputFileName);
    if (!outFile.is_open())
    {
        cerr << "Error: Unable to open file '" << outputFileName << "' for writing." << endl;
        return;
    }
    outFile << "#include <iostream>\n"
            << "#include <vector>\n"
            << "using namespace std ;"
            << "int main(){\n"
            << "      const int tapeSize=1000 ;\n"
            << "      vector <int> tape(tapeSize , 0);\n"
            << "      int pointer =0 ;\n\n";
    stack<int> loopStack;
    for (size_t i = 0; i < code.size(); i++)
    {
        char command = code[i];
        switch (command)
        {
        case '>':
            outFile << "     pointer++;\n";
            outFile << "     if(pointer>=tapeSize) {\n"
                    << "     cerr << \"Pointer out of bound!\" << endl ;\n"
                    << "     return 1 ; \n"
                    << "     }\n";
            break;
        case '<':
            outFile << "     pointer--;\n";
            outFile << "     if(pointer < 0 ) {\n"
                    << "     cerr << \"Pointer out of bound!\" << endl ;\n"
                    << "     return 1 ; \n"
                    << "     }\n";
            break;
        case '+':
            outFile << "     tape[pointer]++;\n";
            break;
        case '-':
            outFile << "     tape[pointer]--;\n";
            break;
        case '.':
            outFile << "     cout << (char)tape[pointer];\n";
            break;
        case ',':
            outFile << "    tape[pointer] = cin.get();\n";
            break;
        case '[':
            loopStack.push(i);
            outFile << "    while (tape[pointer]) {\n";
            break;
        case ']':
            if (loopStack.empty())
            {
                cerr << "Syntax Error: Unmatched ']' at position " << i << endl;
                outFile.close();
                return;
            }
            loopStack.pop();
            outFile << "    }\n";
            break;
        default:
            break;
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
    Compile_bf(code, outputFile);

    return 0;
}
