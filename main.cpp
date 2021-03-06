#include<iostream>
#include<string.h>

using std::cout;
using std::cin;

void evaluate(char* cmd) {
    char* ptrMem;
    ptrMem = new char[30000]; // Allocate memory for program, 30000 bytes currently, maybe a vector would be better for dynamic memory size?
    char* ptr;
    ptr = ptrMem;
    char* cins;
    bool inLoop = false;
    cins = cmd;
    ptrdiff_t bytes = cins-cmd;
    int cmdlen = strlen(cmd);
    while (true) { 
        if (inLoop == false) { // Skips calculation if in a loop, small speed improvement
            bytes = cins-cmd; // Calculate memory between current instruction and last instruction
            if (bytes > cmdlen-1) break; // Probably faster than comparing memory between last instruction and current instruction
        }
        switch (*cins) {
            case '>':
                ++ptr;
                break;
            case '<':
                --ptr;
                break;
            case '+':
                ++(*ptr);
                break;
            case '-':
                --(*ptr);
                break;
            case '.':
                cout << *ptr;
                break;
            case ',':
                cin >> *ptr;
                break;
            case '[':
                inLoop = true;
                if (*ptr == 0) {
                    inLoop = false;
                    int depth = 1;
                    while (depth != 0) {
                        ++cins;
                        if (*cins == '[') ++depth;
                        else if (*cins == ']') --depth;
                    }
                }
                break;
            case ']':
                int depth = 1;
                while (depth != 0) {
                    --cins;
                    if (*cins == ']') ++depth;
                    else if (*cins == '[') --depth;
                }
                --cins;
                break;
        };
    ++cins;
    }
    delete ptrMem;
}

int main(int argc, char** argv) {
    char* cmd;
    cmd = new char[100000];
    //cmd = argv[1];
    int index = 0;
    bool newline = true;
    bool isComment = false;
    int i = 0;
    for (int i = 0; i < strlen(argv[1]); i++) {
        if (argv[1][i] == '%') newline = false; // Handle comments
        if (argv[1][i] == '\n') newline = true;
        if (argv[1][i] == '#') {
            if (isComment) isComment=false;
            else isComment=true;
        }
        // This parses the instructions into cmd array
        if ((argv[1][i] == '>' || argv[1][i] == '<' || argv[1][i] == '+' || argv[1][i] == '-' || argv[1][i] == '[' || argv[1][i] == ']' || argv[1][i] == ',' || argv[1][i] == '.') && newline && isComment == false) {
            cmd[index] = argv[1][i];
            index++;
        }
    }
    evaluate(cmd); // Call evaluation
    delete[] cmd;
}
