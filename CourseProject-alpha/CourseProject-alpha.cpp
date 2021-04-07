// CourseProject-alpha.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "CourseProject-alpha.h"
#include <wchar.h>
#include"commdlg.h"
#include<stdio.h>
#include <string.h>
#include<iostream>
#include <string>
#include<Windows.h>

using namespace std;

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define _CRT_SECURE_NO_WARNINGS


#pragma warning(disable: 4996)
#define MAX_LOADSTRING 100
#define ID_color IDC_COURSEPROJECTALPHA
// Global Variables:
struct  Person
{
int ID;
    WCHAR FULL_Name[50];
    WCHAR Address[60];
    WCHAR Phone[13];
    WCHAR Birthday[13];
    WCHAR Notes[100];
    WCHAR Email[30];
};


int index = 0;
//int j;
Person p[100];
WCHAR Full_Name_Search[50];
RECT rt;
HWND hWnd;
WCHAR TEXT_View[5000] = { L"FULL Name \t Email \t\t Address \t\t Phone \t\t  Birthday \t Notes \r\n\n" };
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hView, hName, hEmail, hAddress, hPhone, hBirthday, hNotes, hName_search;
HWND HBNew, HBAdd, HBEdit, HBRemove, HBSearch, HBSave, HBClear, HBSearchdlg, HBCancel, HBOpen;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    DialogProcedure(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void displayDilog(HWND);
void registerDialogClass(HINSTANCE);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_COURSEPROJECTALPHA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COURSEPROJECTALPHA));

    MSG msg;
    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int) msg.wParam;
}
//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COURSEPROJECTALPHA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_COURSEPROJECTALPHA);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    registerDialogClass(hInst);

   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, L"Address Book", WS_OVERLAPPEDWINDOW,
       200, 200, 1400, 700, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
void display_File(wchar_t* Path) {
    FILE* file;
    file = _wfopen(Path, L"a+ t");
    fseek(file, 0, SEEK_END);
    int _size = ftell(file) ;
    rewind(file);
    wchar_t* data = new wchar_t[_size + 1];
    fread(data, _size, 1, file);
    data[_size] = L'\0';
    SetWindowText(hView, data);
    fclose(file);
}
void open_file(HWND hWnd) {

    OPENFILENAME ofn;
    WCHAR file_name[100];
    ZeroMemory(&ofn, sizeof(OPENFILENAME));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = file_name;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = L"All Files\0*.*\0Source Files\0*.CPP\Text Files\0*.Txt\0";
    ofn.nFilterIndex = 1;
    GetOpenFileName(&ofn);
    
    display_File(ofn.lpstrFile);

}
void Write_File(wchar_t* Path) {

    FILE* file;
    file = _wfopen(Path, L"w");
    int sizee = sizeof(TEXT_View);

    fwrite(TEXT_View, sizee + 1, 1, file);
    fclose(file);

}
void Save_file(HWND hWnd) {

    OPENFILENAME ofn;
    wchar_t file_name[100];
    ZeroMemory(&ofn, sizeof(OPENFILENAME));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = file_name;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 1000;
    ofn.lpstrFilter = L"All Files\0*.*\0Source Files\0*.CPP\Text Files\0*.Txt\0";
    ofn.nFilterIndex = 1;
    GetSaveFileName(&ofn);

    Write_File(ofn.lpstrFile);
}
void createWind(HWND hWnd) {
    hView = CreateWindowW(L"edit", L"", WS_CHILD | WS_VISIBLE | ES_LEFT |WS_HSCROLL|WS_VSCROLL | WS_BORDER | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_READONLY | ES_MULTILINE, 25, 100, 750, 480, hWnd, NULL, hInst, nullptr);

    hName = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, 950, 140, 300, 30, hWnd, NULL, NULL, NULL);
    hEmail = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, 950, 190, 300, 30, hWnd, NULL, NULL, NULL);
    hAddress = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, 950, 240, 300, 30, hWnd, NULL, NULL, NULL);
    hPhone = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, 950, 290, 300, 30, hWnd, NULL, NULL, NULL);
    hBirthday = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, 950, 340, 300, 30, hWnd, NULL, NULL, NULL);
    hNotes = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, 900, 430, 450, 150, hWnd, NULL, NULL, NULL);
}
void createbtn(HWND hWnd) {
    HBNew = CreateWindow(L"BUTTON", L" Add", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 625, 600, 100, 20, hWnd, (HMENU)1, hInst, NULL);
    HBEdit = CreateWindow(L"BUTTON", L" Edit", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 735, 600, 100, 20, hWnd, (HMENU)2, hInst, NULL);
    HBRemove = CreateWindow(L"BUTTON", L" Remove", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 845, 600, 100, 20, hWnd, (HMENU)3, hInst, NULL);
    HBSearch = CreateWindow(L"BUTTON", L" Search", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 955, 600, 100, 20, hWnd, (HMENU)4, hInst, NULL);
    HBSave = CreateWindow(L"BUTTON", L" Save", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 1065, 600, 100, 20, hWnd, (HMENU)5, hInst, NULL);
    HBClear = CreateWindow(L"BUTTON", L" Clear", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 1175, 600, 100, 20, hWnd, (HMENU)6, hInst, NULL);
    HBOpen = CreateWindow(L"BUTTON", L" Open", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 515, 600, 100, 20, hWnd, (HMENU)7, hInst, NULL);
}
void Getter() {  
    p[index].ID = index;
    GetWindowText(hName, p[index].FULL_Name, 50);
    GetWindowText(hEmail, p[index].Email, 30);
    GetWindowText(hAddress, p[index].Address, 60);
    GetWindowText(hPhone, p[index].Phone, 13);
    GetWindowText(hBirthday, p[index].Birthday, 13);
    GetWindowText(hNotes, p[index].Notes, 100);

     SetWindowTextW(hName, L"");
     SetWindowTextW(hEmail, L"");
     SetWindowTextW(hAddress, L"");
     SetWindowTextW(hPhone, L"");
     SetWindowTextW(hBirthday, L"");
     SetWindowTextW(hNotes, L"");
     index++;
 }

int Shearch_Person(wstring name) {
    for (int i = 0; i <= index; i++)
    {
        if (p[i].FULL_Name == name )
        {
            return p[i].ID;
        }
        
    }

}

void Clear() {
    SetWindowTextW(hName, L"");
    SetWindowTextW(hEmail, L"");
    SetWindowTextW(hAddress, L"");
    SetWindowTextW(hPhone, L"");
    SetWindowTextW(hBirthday, L"");
    SetWindowTextW(hNotes, L"");
}
void display() {

    wcscpy(TEXT_View, L"-FULL Name \t -Email \t\t          -Address \t          -Phone \t-Birthday \t        -Notes\r\n\r\n");

    for (int i = 0; i < index; i++)
    {
         wcscat(TEXT_View, L"\r\n");
        wcscat(TEXT_View, p[i].FULL_Name);

        wstring str = p[i].FULL_Name;
        int V = size(str);
        for (int i0 = V; i0 < 20; i0++)
        {
            wcscat(TEXT_View, L" ");
        }//wcscat(TEXT_View, L"-");

        
        wcscat(TEXT_View, p[i].Email);

        wstring str1 = p[i].Email;
        int V1 = size(str1);
        for (int i1 = V1; i1 < 30; i1++)
        {
            wcscat(TEXT_View, L" ");
        }//wcscat(TEXT_View, L"-");

        
        wcscat(TEXT_View, p[i].Address);

        wstring str2 = p[i].Address;
        int V2 = size(str2);
        for (int i2 = V2; i2 < 20; i2++)
        {
            wcscat(TEXT_View, L" ");
        }//wcscat(TEXT_View, L"-");

        
        wcscat(TEXT_View, p[i].Phone);
        
        wstring str3 = p[i].Phone;
        int V3 = size(str3);
        for (int i3 = V3; i3 < 15; i3++)
        {
            wcscat(TEXT_View, L" ");
        }//wcscat(TEXT_View, L"-");

        wcscat(TEXT_View, p[i].Birthday);
        
        wstring str4 = p[i].Birthday;
        int V4 = size(str4);
        for (int i = V4; i < 15; i++)
        {
            wcscat(TEXT_View, L" ");
        }//wcscat(TEXT_View, L"-");

        wcscat(TEXT_View, p[i].Notes);

        SetWindowTextW(hView, TEXT_View);
    }
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: {    
        createbtn(hWnd);
        createWind(hWnd);
    }
    case WM_COMMAND:
    {
        switch (LOWORD(wParam)) {
        case 1: {
             Getter();
             display();            
            break;
        }
        case 2: {
            GetWindowText(hName, Full_Name_Search, 50);
            int j = Shearch_Person(Full_Name_Search);
            GetWindowText(hName, p[j].FULL_Name, 50);
            GetWindowText(hEmail, p[j].Email, 30);
            GetWindowText(hAddress, p[j].Address, 60);
            GetWindowText(hPhone, p[j].Phone, 13);
            GetWindowText(hBirthday, p[j].Birthday, 13);
            GetWindowText(hNotes, p[j].Notes, 100);

            display();
            Clear();
            break;
        }
        case 3: {          
            GetWindowText(hName, Full_Name_Search, 50);
           int k = Shearch_Person(Full_Name_Search);
            for ( int i =k; i <= index -1 ; i++)
            {              
                p[i] = p[i+1];
                p[i].ID--;                
            }wcscpy(TEXT_View, L"FULL Name \t Email \t Address \t Phone \t  Birthday \t Notes \r\n\r\n");
            for (int i = 0; i < index -1; i++)
            {                
                wcscat(TEXT_View, L"\r\n");
                wcscat(TEXT_View, p[i].FULL_Name);
                wcscat(TEXT_View, L"-\t-");
                wcscat(TEXT_View, p[i].Email);
                wcscat(TEXT_View, L"-\t-");
                wcscat(TEXT_View, p[i].Address);
                wcscat(TEXT_View, L"-\t-");
                wcscat(TEXT_View, p[i].Phone);
                wcscat(TEXT_View, L"-\t-");
                wcscat(TEXT_View, p[i].Birthday);
                wcscat(TEXT_View, L"-\t-");
                wcscat(TEXT_View, p[i].Notes);                
            }            
            SetWindowTextW(hView, TEXT_View);
            Clear();
            index--;
            break;
        }
        case 4: {
            displayDilog(hWnd);
            break;
        }
        case 5:
            Save_file(hWnd);
            break;
        case 6:
        {
            Clear();
            break;
        }
        case 7:
        {
            open_file(hWnd);
            break;
        }        
    }
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            TextOut(hdc, 80, 80, L"PEOPLE", _tcslen(L"PEOPLE"));
            TextOut(hdc, 900, 80, L"INFORMATION", _tcslen(L"INFORMATION"));
            TextOut(hdc, 840, 150, L"FULL NAME", _tcslen(L"FULL NAME"));
            TextOut(hdc, 840, 200, L"EMAIL Address", _tcslen(L"EMAIL Address"));
            TextOut(hdc, 840, 250, L"HOME Address", _tcslen(L"HOME Address"));
            TextOut(hdc, 840, 300, L"Phone N° ", _tcslen(L"Phone N° "));
            TextOut(hdc, 840, 350, L"BirthDay", _tcslen(L"BirthDay"));
            TextOut(hdc, 840, 400, L"Additional Notes", _tcslen(L"Additional Notes"));

            SetWindowTextW(hView, TEXT_View);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
void registerDialogClass(HINSTANCE hInst)
{
    WNDCLASSW dialog = { 0 };
    dialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
    dialog.hCursor = LoadCursor(NULL, IDC_ARROW);
    dialog.hInstance = hInst;
    dialog.lpszClassName = L"myDialogClass";
    dialog.lpfnWndProc = DialogProcedure;

    RegisterClassW(&dialog);
}
void displayDilog(HWND hWnd) {

    CreateWindowW(L"myDialogClass", L"Search", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 400, 600, 300, hWnd, NULL, NULL, NULL);

}
LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_CREATE: {

        hName_search = CreateWindowW(L"Edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, 200, 108, 300, 22, hWnd, NULL, NULL, NULL);
        HBSearchdlg = CreateWindow(L"BUTTON", L" Search", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 150, 200, 100, 20, hWnd, (HMENU)11, hInst, NULL);
        HBCancel = CreateWindow(L"BUTTON", L" Cancel", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 300, 200, 100, 20, hWnd, (HMENU)12, hInst, NULL);
        break;
    }

    case WM_COMMAND:

    {

        switch (LOWORD(wp)) {

        case 11: {
                GetWindowText(hName_search, Full_Name_Search, 50);
                int j = Shearch_Person(Full_Name_Search);
                if (j == -1)
                {
                    break;
                }
                SetWindowTextW(hName, p[j].FULL_Name);
                SetWindowTextW(hEmail, p[j].Email);
                SetWindowTextW(hAddress, p[j].Address);
                SetWindowTextW(hPhone, p[j].Phone);
                SetWindowTextW(hBirthday, p[j].Birthday);
                SetWindowTextW(hNotes, p[j].Notes);
                DestroyWindow(hWnd);
                break;
        }

        case 12: DestroyWindow(hWnd);
            break;
}
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        TextOut(hdc, 50, 108, L"Enter Full Name :", _tcslen(L"Enter Full Name :"));
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
        break;
    }

}