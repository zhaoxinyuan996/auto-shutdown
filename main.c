#include "time.c"
#include <stdio.h>
#include <windows.h>

// up_down�ؼ�����
#include <commctrl.h>
#pragma comment(lib, "C:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Lib\\ComCtl32.Lib")
#pragma comment(linker,"\"/manifestdependency:type                  = 'win32' \
                                              name                  = 'Microsoft.Windows.Common-Controls' \
                                              version               = '6.0.0.0' \
                                              processorArchitecture = '*' \
                                              publicKeyToken        = '6595b64144ccf1df' \
                                              language              = '*'\"")
#define WIDTH 300
#define HEIGHT 100
#define BUTTON1 01
#define BUTTON2 02
#define INPUT1  11
#define INPUT2  12
#define INPUT3  13
#define INPUT4  14
#define INPUT5  15
#define UPDOWN1 21
#define UPDOWN2 22
#define UPDOWN3 23
#define UPDOWN4 24
#define MAX_INPUT_LEN 70
#define MAX_SECOND_LEN 10
#define SPACE 60

HWND UD1;
HWND UD2;
HWND UD3;
HWND UD4;

HINSTANCE hAppInstance;    //Ӧ�ó���������ΪҪʹ�õĵط�̫����Ҫ�����ȫ�ֱ�������winmain�����и�����ֵ
char cmd[80] = "Shutdown -r -t ";
char secondList[MAX_SECOND_LEN];
int second;

void setupTime(){
    time.day = 0;
    time.hour = 0;
    time.min = 0;
    time.sec = 0;
}
// ���ػ�����
void shutDown(){

//    if (0 < second && second < 315360000){
//        strcat(cmd, itoa(second, secondList, 10));
////        system("shutdown -a");
////        system(cmd);
//        printf("%s\n", secondList);
//        printf("%s", cmd);
//    }

}
void unShutDown(){
//    system("shutdown -a");
}
void CreateText(HDC hdc){
    int start = 100;
    int top = 12;
    TextOut(hdc, 25, top, "����ʱ", 6);
    TextOut(hdc, start, top, "��", 2);
    TextOut(hdc, start + SPACE, top, "ʱ", 2);
    TextOut(hdc, start + SPACE * 2, top, "��", 2);
    TextOut(hdc, start + SPACE * 3, top, "��", 2);
    TextOut(hdc, 50, 50, "������룺", 10);
}
// �������Ϸ��ԣ��Լ���������
void checkInput(HWND hwnd,int nIDDlgItem, HWND ud, int mmax){
    int input;
    if (nIDDlgItem == INPUT1){
        input = (int) GetDlgItemInt(hwnd, nIDDlgItem,NULL,0);
    }else{
        input = SendMessage(ud, UDM_GETPOS32, 0, 0);
    }

    if (input > mmax){
//        SetDlgItemInt(hwnd, nIDDlgItem, mmax,0);
        switch (nIDDlgItem) {
            case INPUT2:
                PostMessage(UD1, UDM_SETPOS32, 0, mmax);
                time.day = mmax;
                break;
            case INPUT3:
                PostMessage(UD2, UDM_SETPOS32, 0, mmax);
                time.hour = mmax;
                break;
            case INPUT4:
                PostMessage(UD3, UDM_SETPOS32, 0, mmax);
                time.min = mmax;
                break;
            case INPUT5:
                PostMessage(UD4, UDM_SETPOS32, 0, mmax);
                time.sec = mmax;
                break;
            default:
            {}
        }
        PostMessage(ud, UDM_SETPOS32, 0, time.day);
    }
    // �� -> time
    if (nIDDlgItem == INPUT1){
        SecondToTime((int) GetDlgItemInt(hwnd, INPUT1,NULL,0));
        PostMessage(UD1, UDM_SETPOS32, 0, time.day);
        PostMessage(UD2, UDM_SETPOS32, 0, time.hour);
        PostMessage(UD3, UDM_SETPOS32, 0, time.min);
        PostMessage(UD4, UDM_SETPOS32, 0, time.sec);
    } else{  // time -> ��
        switch (nIDDlgItem) {
            case INPUT2:
                time.day = input;
                break;
            case INPUT3:
                time.hour = input;
                break;
            case INPUT4:
                time.min = input;
                break;
            case INPUT5:
                time.sec = input;
                break;
            default: {}
        }
        SetDlgItemInt(hwnd, INPUT1, timeToSecond(&time), 0);
    }
}

// ��updown��ť�Ļص�
void callUpDown(HWND hwnd, WPARAM wParam, LPARAM lParam){ // wParam �ؼ�id
    int shift;
    if (((LPNMUPDOWN) lParam)->iDelta >= 0){
        shift = -1;
    } else{
        shift = 1;
    }
    switch (wParam) {
        case UPDOWN1:
        {
            if (0 <= time.day + shift && time.day + shift <= 99){
                time.day += shift;
            }
            PostMessage(UD1, UDM_SETPOS32, 0, time.day);
            break;
        }
        case UPDOWN2:
        {
            if (0 <= time.hour + shift && time.hour + shift <= 23){
                time.hour += shift;
            }
            PostMessage(UD2, UDM_SETPOS32, 0, time.hour);
            break;
        }
        case UPDOWN3:
        {
            if (0 <= time.min + shift && time.min + shift <= 59){
                time.min += shift;
            }
            PostMessage(UD3, UDM_SETPOS32, 0, time.min);
            break;
        }
        case UPDOWN4:
        {
            if (0 <= time.sec + shift && time.sec + shift <= 59){
                time.sec += shift;
            }
            PostMessage(UD4, UDM_SETPOS32, 0, time.sec);
            break;
        }
        default:
        {}
    // ���updown�¼���ˢ���������
    SetDlgItemInt(hwnd, INPUT1, timeToSecond(&time), 0);
    }
}
//������ť
void CreateButton(HWND hwnd){
    CreateWindow (
            TEXT("BUTTON"),
            TEXT("ȷ��"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            200, 50,
            40, 20,
            hwnd,
            (HMENU)BUTTON1,        //�Ӵ���ID
            hAppInstance,         //Ӧ�ó���ľ����
            NULL);
    CreateWindow (
            TEXT("button"),
            TEXT("ȡ��"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            250, 50,
            40, 20,
            hwnd,
            (HMENU)BUTTON2,        //�Ӵ���ID
            hAppInstance,         //Ӧ�ó���ľ����
            NULL);
}

//���������
void CreateInput(HWND hwnd){
    //�ײ������༭��
    CreateWindow (
            TEXT("edit"),
            TEXT(""),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            110, 50,
            MAX_INPUT_LEN, 20,
            hwnd,
            (HMENU)INPUT1,        //�Ӵ���ID
            hAppInstance,         //Ӧ�ó���ľ����
            NULL);
    //�죬ʱ���֣���༭��
    CreateWindow (//��
            TEXT("edit"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            50, 10, 35, 20, hwnd, (HMENU)INPUT2, hAppInstance, NULL);
    UD1 = CreateWindowEx(WS_EX_LEFT | WS_EX_LTRREADING, UPDOWN_CLASS, NULL,
                   WS_CHILDWINDOW | WS_VISIBLE | UDS_AUTOBUDDY |UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK,
                   0, 0, 0, 0, hwnd, (HMENU)UPDOWN1, hAppInstance, NULL);
    CreateWindow (//ʱ
            TEXT("edit"), TEXT("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            50 + SPACE, 10, 35, 20, hwnd, (HMENU)INPUT3, hAppInstance, NULL);
    UD2 = CreateWindowEx(WS_EX_LEFT | WS_EX_LTRREADING, UPDOWN_CLASS, NULL,
                   WS_CHILDWINDOW | WS_VISIBLE | UDS_AUTOBUDDY |UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK,
                   0, 0, 0, 0, hwnd, (HMENU)UPDOWN2, hAppInstance, NULL);
    CreateWindow (//��
            TEXT("edit"), TEXT("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            50 + SPACE * 2, 10, 35, 20, hwnd, (HMENU)INPUT4, hAppInstance, NULL);
    UD3 = CreateWindowEx(WS_EX_LEFT | WS_EX_LTRREADING, UPDOWN_CLASS, NULL,
                   WS_CHILDWINDOW | WS_VISIBLE | UDS_AUTOBUDDY |UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK,
                   0, 0, 0, 0, hwnd, (HMENU)UPDOWN3, hAppInstance, NULL);
    CreateWindow (//��
            TEXT("edit"), TEXT("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            50 + SPACE * 3, 10, 35, 20, hwnd, (HMENU)INPUT5, hAppInstance, NULL);
    UD4 = CreateWindowEx(WS_EX_LEFT | WS_EX_LTRREADING, UPDOWN_CLASS, NULL,
                   WS_CHILDWINDOW | WS_VISIBLE | UDS_AUTOBUDDY |UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK,
                   0, 0, 0, 0, hwnd, (HMENU)UPDOWN4, hAppInstance, NULL);

}
//�����ص�����
LRESULT CALLBACK WindowProc(
        IN  HWND hwnd,
        IN  UINT uMsg,
        IN  WPARAM wParam,
        IN  LPARAM lParam
);

int CALLBACK WinMain(                        //CALLBACK��һ���꣬��ʾ__stdcall��Ҳ������ƽջ��win32����api�������Ǹõ���Լ��
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow
){
    setupTime();
    hAppInstance = hInstance;    //��ȫ�ֱ�����ֵ

    //1.����windowҪ��һ��ʲô���Ĵ���
    TCHAR className[] = "My First Window";     //���ڵ�����
    // ����������Ķ���
    WNDCLASS wndclass = {0};                        //һ��Ҫ�Ƚ�����ֵ��ֵ������RegisterClass�����޷������ã�
    wndclass.hbrBackground = (HBRUSH)COLOR_MENU;                        //���ڵı���ɫ
    wndclass.lpfnWndProc =  WindowProc;                        //���ڹ��̺���
    wndclass.lpszClassName = className;                        //�����������
    wndclass.hInstance = hInstance;                        //���崰�����Ӧ�ó����ʵ�����

    //2.ע�ᴰ����
    RegisterClass(&wndclass);

    //3.����������
    HWND hwnd = CreateWindow(
            className,                //����,�������Լ�����Ĵ���My First Window��Ҳ����ϵͳ����õĴ������簴ťbutton
            TEXT("��ʱ�ػ�"),                //���ڱ���
            WS_SYSMENU,                //���������ʽ
            (GetSystemMetrics(SM_CXSCREEN) - WIDTH) >> 1,                //����ڸ����ڵ�X����
            (GetSystemMetrics(SM_CYSCREEN) - HEIGHT) >> 1,                //����ڸ����ڵ�Y����
            WIDTH,                //���ڵĿ��
            HEIGHT,                //���ڵĸ߶�
            NULL,                //�����ھ����ΪNULL
            NULL,                //�˵������ΪNULL
            hInstance,                //��ǰӦ�ó���ľ��
            NULL);                //��������һ��ΪNULL

    if(hwnd == NULL)                    //�Ƿ񴴽��ɹ�
        return 0;

    CreateButton(hwnd);        //������ť����Ҫ�ڸ����ڴ����ɹ������
    CreateInput(hwnd);          //���������
    SetDlgItemInt(hwnd, INPUT1, timeToSecond(&time),0);

    //4.��ʾ����
    SendMessage(UD1, UDM_SETRANGE, 0, MAKELPARAM(0, 99));
    SendMessage(UD2, UDM_SETRANGE, 0, MAKELPARAM(0, 23));
    SendMessage(UD3, UDM_SETRANGE, 0, MAKELPARAM(0, 59));
    SendMessage(UD4, UDM_SETRANGE, 0, MAKELPARAM(0, 59));
    ShowWindow(hwnd, SW_SHOW);

    //5.��Ϣѭ��
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

//6.�ص��������ɲ���ϵͳ������
/*
������Ϣ������� ���ڻص�������
1�����ڻص��������������Ϣ�����봫��0.
2�����ڻص����������Ϣ����DefWindowProc������.
*/

LRESULT CALLBACK WindowProc(
        IN  HWND hwnd,
        IN  UINT uMsg,
        IN  WPARAM wParam,
        IN  LPARAM lParam
) {
    switch (uMsg) {
        // �˳��¼�
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
            //��ť��Ϣ
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case BUTTON1:
                    second = (int) GetDlgItemInt(hwnd,INPUT1,NULL,0);
                    shutDown();
                    PostQuitMessage(0);
                    break;
                case BUTTON2:
                    unShutDown();
                    PostQuitMessage(0);
                    break;
                case INPUT1:
                    checkInput(hwnd, INPUT1, NULL, 8639999);
                    break;
                case INPUT2:
                    checkInput(hwnd, INPUT2, UD1, 99);
                    break;
                case INPUT3:
                    checkInput(hwnd, INPUT3, UD2, 23);
                    break;
                case INPUT4:
                    checkInput(hwnd, INPUT4, UD3, 59);
                    break;
                case INPUT5:
                    checkInput(hwnd, INPUT5, UD4, 59);
                    break;
                default:
                {}
            }
        }
        // �����ı���ǩ
        case WM_PAINT: {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd, &ps);
            SetTextAlign(hdc, GetTextAlign(hdc) | TA_CENTER);
            CreateText(hdc);
            EndPaint(hwnd, &ps);
            return 0;
        }
        //�����°�ť�¼�
        case WM_NOTIFY:
            callUpDown(hwnd, wParam, lParam);
        default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}




// g++ -mwindows main.c