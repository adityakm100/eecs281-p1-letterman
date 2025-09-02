#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <getopt.h>
using namespace std;

struct Options {
    bool changeCheck;
    bool lengthCheck;
    bool swapCheck;
    bool queueCheck;
    bool stackCheck;
    bool outputCheck = true; //true means word mode, false is modification mode
    string beginWord;
    string endWord;
    int stackCounter = 0;
    int queueCounter = 0;
    int beginCounter = 0;
    int endCounter = 0;

};  // Options{}

void getOptions(int argc, char **argv, Options &options) {
    // These are used with getopt_long()
    opterr = static_cast<int>(false);  // Let us handle all error output for command line options
    int choice = 0;
    int index = 0;
    options = options;
    // bool wMode = true;
    

    option longOptions[] = {
        {"begin" , required_argument, nullptr, 'b'}, 
        {"help" , no_argument,       nullptr, 'h'},
        {"queue", no_argument,       nullptr, 'q'},
        {"stack", no_argument,       nullptr, 's'},
        {"end",   required_argument, nullptr, 'e'},
        {"output", required_argument, nullptr, 'o'},
        {"change", no_argument,       nullptr, 'c'},
        {"length", no_argument,       nullptr, 'l'},
        {"swap",   no_argument,       nullptr, 'p'},
        {nullptr, 0, nullptr, '\0'},
    };  // longOptions[]
    // NOLINTEND

    // Filled in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "b:hqse:o:clp", static_cast<option *>(longOptions), &index)) != -1) {
        switch (choice) {
        case 'h':
            cout << "This program is called Letterman. The objective of this program is for Letterman, using your inputs, to be able to go from your designated starting word to your designated ending word. " << endl;
            exit(0);
            break;

        case 'q': { 
            options.queueCounter++; 
            options.queueCheck = true;
            if ((options.queueCheck && options.stackCheck)|| options.queueCounter > 1) {
                cerr << "Conflicting or duplicate stack and queue specified\n" << flush;
                exit(1);
            }
            //TODO: Implement BFS
            break;
            }  //case q
        
        case 's': {
            options.stackCounter++;
            options.stackCheck = true;
            if ((options.queueCheck && options.stackCheck) || options.stackCounter > 1) {
                cerr << "Conflicting or duplicate stack and queue specified\n" << flush;
                exit(1);
            }
            break;
            //TODO: Implement DFS
        } //case s
        case 'o': {
            string arg {optarg};
            if (arg != "W" && arg != "M") {
                cerr << "Error: invalid option\n" << flush;
                exit(1);
            }
            if (arg == "M") {
                options.outputCheck = false;
            }   
            break;
        } //case o
        case 'b': {
            string arg {optarg};
            //NEED TO CHECK IF BEGIN WORD IS SPECIFIED AND IN THE DICTIONARY IF SPECIFIED
            options.beginWord = arg;
            options.beginCounter++;
            if(options.beginCounter > 1) {
                cerr << "You can't set begin more than once in the same command" << flush;
                exit(1);
            }
            break;
        }
        case 'e': {
            string arg {optarg};
            //NEED TO CHECK IF END WORD IS SPECIFIED AND IN THE DICTIONARY IF SPECIFIED
            options.endWord = arg;
            options.endCounter++;
            if(options.endCounter > 1) {
                cerr << "You can't set end more than once in the same command" << flush;
                exit(1);
            }
            break;
        }
        case 'c': {
            options.changeCheck = true;
            break;
        }
        case 'p': {
            options.swapCheck = true;
            break;
        }
        case 'l': {
            options.lengthCheck = true;
            break;
        }
        default:
        cerr << "Error: invalid option\n" << flush;
        exit(1);
        break;

    }  // switch ..choice  
    

        
    }  // while
    if (!options.queueCheck && !options.stackCheck) {
        cerr << "Must specify one of stack or queue\n" << flush;
        exit(1);
    }
    if(!options.changeCheck && !options.lengthCheck && !options.swapCheck) {
        cerr << "Must specify at least one modification mode (change length swap)\n" << flush;
        exit(1);
    }
}  // getOptions()

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Options options;
    getOptions(argc, argv, options);
    return 0;
}

    