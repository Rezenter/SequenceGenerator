#include <iostream>

using namespace std;


void printArray(int arr[], int to, int from = 0){
    cout << "Array = {";
    for(int i = from; i < to; ++i){
        cout << arr[i];
        if(i != to - 1){
            cout << ", ";
        }
    }
    cout << "}" << endl;
}

int main()
{
    int from, to;
    int length = 0;
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
            int arr[length];
            for(int i = 0; i < length; ++i){
                arr[i] = from + (rand() % (to - from + 1));
            }
            printArray(arr, length);
            string shuffleNeeded = "y"; //можно задать вид положительного ответа: 1, Y, y, true... Любой другой == нет
            string answer = "y";
            while(answer == shuffleNeeded){
                cout << "Shuffle array?(Y/N)" << endl;
                cin >> answer;
                if(answer == shuffleNeeded){
                    cout << "Shuffling..." << endl;
                    for(int i = 0; i < length; ++i){
                        int newIndex = rand() % length;
                        if(newIndex != i){
                            //следующие три строчки можно заменить на swap(...)
                            int tmp = arr[i];
                            arr[i] = arr[newIndex];
                            arr[newIndex] = tmp;
                        }
                    }
                    printArray(arr, length);
                }else{
                    cout << "Shuffle isn`t requested." << endl;
                }
            }
            cout << "Sorting..." << endl;
            for(int i = 0; i < length; ++i){
                int ind = i;
                for(int j = i + 1; j < length; ++j){
                    if(arr[ind] < arr[j]){
                        ind = j;
                    }
                }
                if(ind != i){
                    //следующие три строчки можно заменить на swap(...)
                    int tmp = arr[i];
                    arr[i] = arr[ind];
                    arr[ind] = tmp;
                }

            }
            printArray(arr, length);
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
                for(int i = 0; i < length; ++i){
                    if((arr[i] >= from) && (arr[i] < to) && (arr[i] % 2 == 1)){
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
                cout << "Sequence length = " << maxLen << endl;
                printArray(arr, maxIndex + maxLen, maxIndex);
                cout << "Done." << endl;
            }else {
                cout << "Invalid boundaries" << endl;
            }
        }else{
            cout << "Invalid boundaries" << endl;
        }
    }else{
        cout << "Invalid array length." << endl;
    }
    cout << endl;
    return 0;
}
