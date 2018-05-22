#include <iostream>
#include <windows.h>

using namespace std;

//here are global variables, they can be accessed from every
bool loaded = false;
int length = 0;
int* arrayPointer = NULL; //empty pointer to an array, memory is not allocated yet.
int l = 0; //subsequence boundaries
int r = 0;

int firstLevelMenu(){
    cout << "\nMain Menu\n";
    cout << "Please make your choice by inputing a valid number\n";
    cout << "1 - Generate array\n";
    cout << "2 - Load array from a file\n";
    cout << "3 - Generate array and save to a file\n";
    cout << "4 - Clear console\n";
    cout << "5 - Exit\n";
    cout << "\nSelection: ";
    int selection = 0;
    cin >> selection;
    return selection;
}

void printArray(int from = 0, int to = length){
    cout << "Array = {";
    for(int i = from; i < to; ++i){
        cout << arrayPointer[i];
        if(i != to - 1){
            cout << ", ";
        }
    }
    cout << "}" << endl;
}

void generete(){
    //copypasted from the old main
    int from, to;
    cout << "Enter array length: ";
    cin >> length;
    if(length > 0){
        cout << "Input value boundaries:" << endl;
        cout << "   from: ";
        cin >> from;
        cout << "   to: ";
        cin >> to;
        cout << endl;
        if(from < to){
            arrayPointer = new int[length]; //allocate memory
            for(int i = 0; i < length; ++i){
                arrayPointer[i] = from + (rand() % (to - from + 1));
            }
            printArray();
            loaded = true;
            l = 0;
            r = 0;
        }else{
            cout << "Invalid boundaries" << endl;
        }
    }else{
        cout << "Invalid length" << endl;
    }
}

void load(){
    bool fileExists = true;
    if(fileExists){
        //...load from file here
        loaded = true;
        l = 0;
        r = 0;

        //i dont want to read files, so i will add a bypass for tests
        generete();
        //remove, when loading will be implemented
    }else{
        cout << "File not found" << endl;
    }
}

bool save(int from = 0, int to = length){ //save subarray, default = all
    bool saved = false;
    //...
    //some saving code i dont want to write
    return saved;
}

void clearConsole(char fill = ' ') {  //not mine, googled it
    COORD tl = {0,0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}

int secondLevelMenu(){
    cout << "\nAuxillary Menu\n";
    cout << "Please make your choice by inputing a valid number\n";
    cout << "1 - Forget array and go to main menu\n";
    cout << "2 - Shuffle array\n";
    cout << "3 - Sort array\n";
    cout << "4 - Find the longest odd subsequence\n";
    cout << "5 - Save subsequence to a file\n";
    cout << "6 - Clear console\n";
    cout << "7 - Exit\n";
    cout << "\nSelection: ";
    int selection = 0;
    cin >> selection;
    return selection;
}

void firstLevelLoop(){
    bool exit = false;
    while((!exit) && (!loaded)){
        switch (firstLevelMenu()) {
        case 1:
            generete();
            break;
        case 2:
            load(); //can be written right here without separeted void()
            break;
        case 3:
            generete();
            cout<< "Saved? " << save() << endl;
            break;
        case 4:
            clearConsole();
            break;
        case 5:
            exit = true;
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
    while(!exit){
        switch (secondLevelMenu()) {
        case 1:
            exit = true;
            delete [] arrayPointer; //deallocate memory
            arrayPointer = NULL;
            length = 0;
            loaded = false;
            l = 0;
            r = 0;
            firstLevelLoop();
            break;
        case 2:
            //copypasted from the old main
            cout << "Shuffling..." << endl;
            for(int i = 0; i < length; ++i){
                int newIndex = rand() % length;
                if(newIndex != i){
                    //следующие три строчки можно заменить на swap(...)
                    int tmp = arrayPointer[i];
                    arrayPointer[i] = arrayPointer[newIndex];
                    arrayPointer[newIndex] = tmp;
                }
            }
            printArray();
            break;
        case 3:
            //copypasted from the old main
            cout << "Sorting..." << endl;
            for(int i = 0; i < length; ++i){
                int ind = i;
                for(int j = i + 1; j < length; ++j){
                    if(arrayPointer[ind] < arrayPointer[j]){
                        ind = j;
                    }
                }
                if(ind != i){
                    //следующие три строчки можно заменить на swap(...)
                    int tmp = arrayPointer[i];
                    arrayPointer[i] = arrayPointer[ind];
                    arrayPointer[ind] = tmp;
                }

            }
            printArray();
            break;
        case 4:
            {//needed to create a scope for variables declaration
                //copypasted from the old main
                int from = 0;
                int to = 0;
                cout << "Input filter boundaries:" << endl;
                cout << "   from(included): ";//левая граница включена
                cin >> from;
                cout << "   to(excluded): ";//правая граница исключена
                cin >> to;
                cout << endl;
                if(from < to){
                    cout << "Finding longest odd subsequence..." << endl;
                    int maxIndex = 0;
                    int maxLen = 0;
                    int index = 0;
                    int len = 0;
                    for(int i = 0; i < length; ++i){ //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!fix!!!!!!!!!!!!!!!!!!!!!
                        if((arrayPointer[i] >= from) && (arrayPointer[i] < to) && (arrayPointer[i] % 2 == 1)){
                            if(len == 0){
                                index = i;
                            }
                            ++len;
                        }else{
                            if(maxLen < len){
                                maxLen = len;
                                maxIndex = index;
                            }
                            len = 0;
                        }
                    }
                    if(maxLen < len){
                        maxLen = len;
                        maxIndex = index;
                    }
                    l = maxIndex;
                    r = maxIndex + maxLen;
                    cout << "Sequence length = " << maxLen << endl;
                    printArray(l, r);
                }else{
                    cout << "Invalid boundaries.";
                }
                break;
            }
        case 5:
            if(l != r){
                cout << "Saved? " << save(l, r) << endl;
            }else{
                cout << "Subsequence not found yet! For Science, You Monster.\n";
            }
            break;
        case 6:
            clearConsole();
            break;
        case 7:
            exit = true;
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
}

int main(){
    firstLevelLoop();
    delete [] arrayPointer; //deallocate memory
    arrayPointer = NULL;
    return 0;
}
