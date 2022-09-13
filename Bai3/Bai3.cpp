#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>
#include <tlhelp32.h>
#include <algorithm>
#include <map>
#include <string>
#include<stack>
double time1 = 0;
double time2 = 0;
double time3 = 0;
using namespace std;
namespace fs = std::filesystem;
//Cac ham su dung API CreateThread
DWORD WINAPI DoStuff(LPVOID lpParameter)
{
    
    // The new thread will start here
    auto startTime = std::chrono::high_resolution_clock::now();
    ifstream ifs("C://Users//duyhu//source//repos//Bai3//Bai3//1.txt.txt");
    if (!ifs) {
        cout << "Error: file not opened." << endl;
    }
    char chr;
    int count = 0;
    while (ifs >> chr) {
        count++;
    }
    //Đóng file
    ifs.close();
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
    //cout << "Thread 1 : Giai nhi" << endl;
    //cout << "Giai nhi - Thoi gian hoan thanh tien trinh 1 : " << elapsed.count() / (double)1000000 << endl;
    time1 = elapsed.count() / (double)1000000;

    return 0;
}
DWORD WINAPI Read_File_txt(LPVOID lpParameter)
{
  
    auto startTime = std::chrono::high_resolution_clock::now();
    int count{ };
    std::filesystem::path p1{ "C:/Users/duyhu/source/repos/Bai3/Bai3" };
    for (auto& p : std::filesystem::directory_iterator(p1))
    {
        ++count;
    }

    //std::cout << "So tep trong thu muc " << p1 << "la : " << count << '\n';
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
    //cout << "Thread 2 : Giai nnhat" << endl;
    //cout << "Giai nhat  - Thoi gian hoan thanh tien trinh 2 : " << elapsed.count() / (double)1000000 << endl;
    time2 = elapsed.count() / (double)1000000;
    return 0;
}
DWORD FindProcessId(const std::wstring& processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    Process32First(processesSnapshot, &processInfo);
    if (!processName.compare(processInfo.szExeFile))
    {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32Next(processesSnapshot, &processInfo))
    {
        if (!processName.compare(processInfo.szExeFile))
        {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }

    CloseHandle(processesSnapshot);
    return 0;
}
int GetCurrentThreadCount()
{
    // first determine the id of the current process
    DWORD const  id = FindProcessId(L"explorer.exe"); // explorere.exe id
    // then get a process list snapshot.
    HANDLE const  snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    // initialize the process entry structure.
    PROCESSENTRY32 entry = { 0 };
    entry.dwSize = sizeof(entry);

    // get the current process info.
    BOOL  ret = true;
    ret = Process32First(snapshot, &entry);
    while (ret && entry.th32ProcessID != id) {
        ret = Process32Next(snapshot, &entry);
    }
    CloseHandle(snapshot);
    return ret
        ? entry.cntThreads
        : -1;
}
DWORD WINAPI Count_Thread(LPVOID lpParameter)
{

    auto startTime = std::chrono::high_resolution_clock::now();
    int a = GetCurrentThreadCount();
    //cout << "So thread trong process la : " << a << endl;
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
    //cout << "Thread 3 : Giai ba" << endl;
    //cout << "Giai ba - Thoi gian hoan thanh tien trinh 3 : " << elapsed.count() / (double)1000000 << endl;
    time3 = elapsed.count() / (double)1000000;
    return 0;
}
//Cac ham su dung thu vien Thread
/*void WINAPI Read_File_txt()
{
    auto startTime = std::chrono::high_resolution_clock::now();
    ifstream ifs("C://Users//duyhu//source//repos//Bai3//Bai3//1.txt.txt");
    if (!ifs) {
        cout << "Error: file not opened." << endl;
    }
    char chr;
    int count = 0;
    while (ifs >> chr) {
        count++;
    }
    //Đóng file
    ifs.close();
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
    cout << "Thread 1 : Giai nhi" << endl;
    cout << "Giai nhi - Thoi gian hoan thanh tien trinh 1 : " << elapsed.count() / (double)1000000 << endl;
    // The new thread will start here
    
}
void Count_File() {
    auto startTime = std::chrono::high_resolution_clock::now();
    int count{ };
    std::filesystem::path p1{ "C:/Users/duyhu/source/repos/Bai3/Bai3" };
    for (auto& p : std::filesystem::directory_iterator(p1))
    {
        ++count;
    }

    //std::cout << "So tep trong thu muc " << p1 << "la : " << count << '\n';
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
    cout << "Thread 2 : Giai nnhat" << endl;
    cout << "Giai nhat  - Thoi gian hoan thanh tien trinh 2 : " << elapsed.count() / (double)1000000 << endl;
}
DWORD FindProcessId(const std::wstring& processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    Process32First(processesSnapshot, &processInfo);
    if (!processName.compare(processInfo.szExeFile))
    {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32Next(processesSnapshot, &processInfo))
    {
        if (!processName.compare(processInfo.szExeFile))
        {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }

    CloseHandle(processesSnapshot);
    return 0;
}

int GetCurrentThreadCount()
{
    // first determine the id of the current process
    DWORD const  id = FindProcessId(L"explorer.exe"); // explorere.exe id
    // then get a process list snapshot.
    HANDLE const  snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    // initialize the process entry structure.
    PROCESSENTRY32 entry = { 0 };
    entry.dwSize = sizeof(entry);

    // get the current process info.
    BOOL  ret = true;
    ret = Process32First(snapshot, &entry);
    while (ret && entry.th32ProcessID != id) {
        ret = Process32Next(snapshot, &entry);
    }
    CloseHandle(snapshot);
    return ret
        ? entry.cntThreads
        : -1;
}
void Count_Thread() {
    auto startTime = std::chrono::high_resolution_clock::now();
    int a = GetCurrentThreadCount();
    //cout << "So thread trong process la : " << a << endl;
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
    cout << "Thread 3 : Giai ba" << endl;
    cout << "Giai ba - Thoi gian hoan thanh tien trinh 3 : " << elapsed.count() / (double)1000000 << endl;
}*/
void Out_Prize(double a, double b, double c) {
    map<string, double> mymap = {
        {"tien trinh 1" , a},
        {"tien trinh 2" , b},
        {"tien trinh 3" , c}
    };
    vector<std::pair<string, double> > arr;
    for (const auto& item : mymap) {
        arr.emplace_back(item);
    }
    std::sort(arr.begin(), arr.end(),
        [](const auto& x, const auto& y) {return x.second < y.second; });
    auto& x = arr[0];
    cout << "Giai nhat : " << x.first << endl;
    auto& y = arr[1];
    cout << "Giai nhi : " << y.first << endl;
    auto& z = arr[2];
    cout << "Giai ba : " << z.first << endl;

}
int main() {
    
    //Cach 1 : Su dung thu vien thread
   /*std::thread t1(Read_File_txt);
    std::thread t2(Count_File);
    std::thread t3(Count_Thread); 
    t1.join();
    t2.join();
    t3.join();
    system("pause");
    return 0;
    */
    //Cach 2 : su dung API CreateThread
    HANDLE hThread = CreateThread(
        NULL,    // Thread attributes
        0,       // Stack size (0 = use default)
        DoStuff, // Thread start address
        NULL,    // Parameter to pass to the thread
        0,       // Creation flags
        NULL);   // Thread id
    if (hThread == NULL)
    {
        // Thread creation failed.
        // More details can be retrieved by calling GetLastError()
        return 1;
    }
    
    //WaitForSingleObject(hThread, INFINITE);

    // Thread handle must be closed when no longer needed
    CloseHandle(hThread);


    HANDLE hThread_1 = CreateThread(
        NULL,    // Thread attributes
        0,       // Stack size (0 = use default)
        Read_File_txt, // Thread start address
        NULL,    // Parameter to pass to the thread
        0,       // Creation flags
        NULL);   // Thread id
    if (hThread_1 == NULL)
    {
        // Thread creation failed.
        // More details can be retrieved by calling GetLastError()
        return 1;
    }

    //WaitForSingleObject(hThread_1, INFINITE);

    // Thread handle must be closed when no longer needed
    CloseHandle(hThread_1);
    HANDLE hThread_2 = CreateThread(
        NULL,    // Thread attributes
        0,       // Stack size (0 = use default)
        Count_Thread, // Thread start address
        NULL,    // Parameter to pass to the thread
        0,       // Creation flags
        NULL);   // Thread id
    if (hThread_2 == NULL)
    {
        // Thread creation failed.
        // More details can be retrieved by calling GetLastError()
        return 1;
    }
    WaitForSingleObject(hThread_2, INFINITE);

    // Thread handle must be closed when no longer needed
    CloseHandle(hThread_2);
    cout << "Tien trinh 1 : " << time1 << endl;
    cout << "Tien trinh 2 : " << time2 << endl;
    cout << "Tien trinh 3 : " << time3 << endl;
    Out_Prize(time1, time2, time3);
    system("pause");
    return 0;
}