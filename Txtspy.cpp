#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;
// Change These 
LPCSTR folderPath = R"(.\)"; 
string fileName = "testfile.txt"; 


//


string convert(LPCSTR str){return std::string(str);}
string filePath = convert(folderPath) + "\\" + fileName;
bool off;
vector <string> file;

void toClipboard(HWND hwnd, const string &s){
    OpenClipboard(hwnd);
    EmptyClipboard();
    HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
    if (!hg){
        CloseClipboard();
        return;
    }
    memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
    GlobalUnlock(hg);
    SetClipboardData(CF_TEXT, hg);
    CloseClipboard();
    GlobalFree(hg);
}

void read(){
	while(!off){
        HANDLE changeHandle = FindFirstChangeNotification(folderPath, TRUE, FILE_NOTIFY_CHANGE_LAST_WRITE);
        WaitForSingleObject(changeHandle, INFINITE);
        string line;
        ifstream log (filePath);
        off = true;
        if (log.is_open()){
            while ( getline (log,line) ){
                cout << line << '\n';
                if (!line.empty()){
                file.push_back(line);
                }
            }
            log.close();
        }
        else cout << "TxtSpy --> Unable to open file";
    }
	cout << "TxtSpy --> Copy to Clipboard? (Y/N)\n";
    char x; char y; cin >> x;
    if (x == 'y' || x == 'Y'){
            stringstream ss;
            copy(file.begin(), file.end(), ostream_iterator<std::string>(ss, "\n"));
            cout << "TxtSpy --> Contents of " + fileName + " copied Successfully";
            size_t len = strlen(ss.str().c_str());
            HWND hwnd = GetDesktopWindow();
            toClipboard(hwnd, ss.str());
        }
    cout << endl << "TxtSpy --> Clear Contents of " + fileName +"? (Y/N)\n";
    cin >> y;
    if (y == 'y' || x == 'Y'){
        ofstream clr (filePath);
        clr.open(fileName, ofstream::out | ofstream::trunc);
        clr.close();
        cout << "TxtSpy --> " + fileName + " Cleared Successfully" << endl;
        system("PAUSE");
    }
}
int main (){
    SetConsoleTitle("FileSpy");
    cout << "TxtSpy ~ Saucy\n" << "------------------\n";
	read();
}

