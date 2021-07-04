#include "time.c"
#include <stdio.h>
#include <windows.h>

// up_down控件引用
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

HWND INP;
HWND UD1;
HWND UD2;
HWND UD3;
HWND UD4;

HINSTANCE hAppInstance;    //应用程序句柄，因为要使用的地方太多需要定义成全局变量；在winmain函数中给它赋值
char cmd[80] = "Shutdown -s -t ";
char secondList[MAX_SECOND_LEN];
int second;

void setupTime(){
    time.day = 0;
    time.hour = 0;
    time.min = 0;
    time.sec = 0;
}

// 开关机函数
void shutDown(){
    itoa(second, secondList, 10);
    strcat(cmd, secondList);
        system("shutdown -a");
        system(cmd);
    printf("%s\n", secondList);
    printf("%s", cmd);
}
void unShutDown(){
    system("shutdown -a");
}

void updateInput(HWND wind){
    char t[10];
    itoa(timeToSecond(&time),t, 10);
    SendMessage(wind, WM_SETTEXT, 0, (LPARAM)TEXT(t));
}

void CreateText(HDC hdc){
    int start = 100;
    int top = 12;
    TextOut(hdc, 25, top, "倒计时", 6);
    TextOut(hdc, start, top, "天", 2);
    TextOut(hdc, start + SPACE, top, "时", 2);
    TextOut(hdc, start + SPACE * 2, top, "分", 2);
    TextOut(hdc, start + SPACE * 3, top, "秒", 2);
    TextOut(hdc, 50, 50, "换算成秒：", 10);
}
// 检查输入合法性，以及数据联动
void checkInput(HWND hwnd,int nIDDlgItem, int mmax){
//    printf("0");
    int input;
    input = (int) GetDlgItemInt(hwnd, nIDDlgItem,NULL,0);
    if (input > mmax){
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
    }
    // time -> 秒
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
    updateInput(INP);

}

// 按updown按钮的回调
void callUpDown(WPARAM wParam, LPARAM lParam){ // wParam 控件id
    int shift;
    if (((LPNMUPDOWN) lParam)->iDelta >= 0){
        shift = -1;
    } else{
        shift = 1;
    }

    switch (wParam) {
        case UPDOWN1:
        {
            if (time.day + shift < 0){
                time.day = 99;
            } else if(time.day + shift > 99){
                time.day = 0;
            } else{
                time.day += shift;
            }
            PostMessage(UD1, UDM_SETPOS32, 0, time.day);
            break;
        }
        case UPDOWN2:
        {
            if (time.hour + shift < 0){
                time.hour = 23;
            } else if(time.hour + shift > 23){
                time.hour = 0;
            } else{
                time.hour += shift;
            }
            PostMessage(UD2, UDM_SETPOS32, 0, time.hour);
            break;
        }
        case UPDOWN3:
        {
            if (time.min + shift < 0){
                time.min = 59;
            } else if(time.min + shift > 59){
                time.min = 0;
            } else{
                time.min += shift;
            }
            PostMessage(UD3, UDM_SETPOS32, 0, time.min);
            break;
        }
        case UPDOWN4:
        {
            if (time.sec + shift < 0){
                time.sec = 59;
            } else if(time.sec + shift > 59){
                time.sec = 0;
            } else{
                time.sec += shift;
            }
            PostMessage(UD4, UDM_SETPOS32, 0, time.sec);
            break;
        }
        default:
        {}
    }
    // 点击updown事件后刷新下面的秒 这个不用写，数值改变后会出发消息事件，消息事件中会统一处理
//    updateInput(hwnd, INP, 0, 0);
}
// 创建按钮
// (HMENU)BUTTON2,        //子窗口ID
// hAppInstance,         //应用程序的句柄，
void CreateButton(HWND hwnd){
    CreateWindow (
            TEXT("BUTTON"), TEXT("确认"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            200, 50,
            40, 20,
            hwnd, (HMENU)BUTTON1, hAppInstance, NULL);
    CreateWindow (
            TEXT("button"), TEXT("取消"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            250, 50,
            40, 20,
            hwnd, (HMENU)BUTTON2, hAppInstance, NULL);
}

//创建输入框
void CreateInput(HWND hwnd){
    //底部秒数编辑框
    INP = CreateWindow (
            TEXT("edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON, // | ES_NUMBER, 仅限键入数字，复制粘贴不管用
            110, 50,
            MAX_INPUT_LEN, 20,
            hwnd, (HMENU)INPUT1, hAppInstance, NULL);
    //天，时，分，秒编辑框
    CreateWindow (//天
            TEXT("edit"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            50, 10, 35, 20, hwnd, (HMENU)INPUT2, hAppInstance, NULL);
    UD1 = CreateWindowEx(WS_EX_LEFT | WS_EX_LTRREADING, UPDOWN_CLASS, NULL,
                   WS_CHILDWINDOW | WS_VISIBLE | UDS_AUTOBUDDY |UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK,
                   0, 0, 0, 0, hwnd, (HMENU)UPDOWN1, hAppInstance, NULL);
    CreateWindow (//时
            TEXT("edit"), TEXT("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            50 + SPACE, 10, 35, 20, hwnd, (HMENU)INPUT3, hAppInstance, NULL);
    UD2 = CreateWindowEx(WS_EX_LEFT | WS_EX_LTRREADING, UPDOWN_CLASS, NULL,
                   WS_CHILDWINDOW | WS_VISIBLE | UDS_AUTOBUDDY |UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK,
                   0, 0, 0, 0, hwnd, (HMENU)UPDOWN2, hAppInstance, NULL);
    CreateWindow (//分
            TEXT("edit"), TEXT("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            50 + SPACE * 2, 10, 35, 20, hwnd, (HMENU)INPUT4, hAppInstance, NULL);
    UD3 = CreateWindowEx(WS_EX_LEFT | WS_EX_LTRREADING, UPDOWN_CLASS, NULL,
                   WS_CHILDWINDOW | WS_VISIBLE | UDS_AUTOBUDDY |UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK,
                   0, 0, 0, 0, hwnd, (HMENU)UPDOWN3, hAppInstance, NULL);
    CreateWindow (//秒
            TEXT("edit"), TEXT("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            50 + SPACE * 3, 10, 35, 20, hwnd, (HMENU)INPUT5, hAppInstance, NULL);
    UD4 = CreateWindowEx(WS_EX_LEFT | WS_EX_LTRREADING, UPDOWN_CLASS, NULL,
                   WS_CHILDWINDOW | WS_VISIBLE | UDS_AUTOBUDDY |UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK,
                   0, 0, 0, 0, hwnd, (HMENU)UPDOWN4, hAppInstance, NULL);

}
//声明回调函数
LRESULT CALLBACK WindowProc(
        IN  HWND hwnd,
        IN  UINT uMsg,
        IN  WPARAM wParam,
        IN  LPARAM lParam
);

int CALLBACK WinMain(                        //CALLBACK是一个宏，表示__stdcall，也就是内平栈，win32所有api函数都是该调用约定
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow
){
    setupTime();
    hAppInstance = hInstance;    //给全局变量赋值

    //1.告诉window要画一个什么样的窗口
    TCHAR className[] = "My First Window";     //窗口的类名
    // 创建窗口类的对象
    WNDCLASS wndclass = {0};                        //一定要先将所有值赋值，否则RegisterClass函数无法起作用；
    wndclass.hbrBackground = (HBRUSH)COLOR_MENU;                        //窗口的背景色
    wndclass.lpfnWndProc =  WindowProc;                        //窗口过程函数
    wndclass.lpszClassName = className;                        //窗口类的名字
    wndclass.hInstance = hInstance;                        //定义窗口类的应用程序的实例句柄

    //2.注册窗口类
    RegisterClass(&wndclass);

    //3.创建窗口类
    HWND hwnd = CreateWindow(
            className,                //类名,可以用自己定义的窗口My First Window，也可用系统定义好的窗口例如按钮button
            TEXT("定时关机"),                //窗口标题
            WS_SYSMENU,                //窗口外观样式
            (GetSystemMetrics(SM_CXSCREEN) - WIDTH) >> 1,                //相对于父窗口的X坐标
            (GetSystemMetrics(SM_CYSCREEN) - HEIGHT) >> 1,                //相对于父窗口的Y坐标
            WIDTH,                //窗口的宽度
            HEIGHT,                //窗口的高度
            NULL,                //父窗口句柄，为NULL
            NULL,                //菜单句柄，为NULL
            hInstance,                //当前应用程序的句柄
            NULL);                //附加数据一般为NULL

    if(hwnd == NULL)                    //是否创建成功
        return 0;

    CreateButton(hwnd);        //创建按钮，需要在父窗口创建成功后调用
    CreateInput(hwnd);          //创建输入框
    SetDlgItemInt(hwnd, INPUT1, timeToSecond(&time),0);

    //4.显示窗口
    SendMessage(UD1, UDM_SETRANGE, 0, MAKELPARAM(0, 99)); // 这4个命令必须有，要不事件消息会乱发导致判断出错，除非重写默认回调
    SendMessage(UD2, UDM_SETRANGE, 0, MAKELPARAM(0, 23));
    SendMessage(UD3, UDM_SETRANGE, 0, MAKELPARAM(0, 59));
    SendMessage(UD4, UDM_SETRANGE, 0, MAKELPARAM(0, 59));
    EnableWindow(INP,0); // 这里先置灰把。  编辑这个没实际意义
    ShowWindow(hwnd, SW_SHOW);

    //5.消息循环
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

//6.回调函数，由操作系统来调用
/*
窗口消息处理程序 窗口回调函数：
1、窗口回调函数处理过的消息，必须传回0.
2、窗口回调不处理的消息，由DefWindowProc来处理.
*/

LRESULT CALLBACK WindowProc(
        IN  HWND hwnd,
        IN  UINT uMsg,
        IN  WPARAM wParam,
        IN  LPARAM lParam
) {
    switch (uMsg) {
        // 退出事件
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
            //按钮消息
        case WM_COMMAND: {
            switch (HIWORD(wParam)) {
                // 数值改变
                case EN_CHANGE:
                    switch (LOWORD(wParam)) {
                        case INPUT2:
                            checkInput(hwnd, INPUT2, 99);
                            break;
                        case INPUT3:
                            checkInput(hwnd, INPUT3, 23);
                            break;
                        case INPUT4:
                            checkInput(hwnd, INPUT4, 59);
                            break;
                        case INPUT5:
                            checkInput(hwnd, INPUT5, 59);
                            break;
                    };
            }
            switch (LOWORD(wParam)) {
                case BUTTON1:
                    second = (int) GetDlgItemInt(hwnd,INPUT1,NULL,0);
                    if (0 < second && second < 315360000){
                        shutDown();
                        PostQuitMessage(0);
                    }
                    break;
                case BUTTON2:
                    unShutDown();
                    PostQuitMessage(0);
                    break;
                default:
                {}
            }
        }
        // 创建文本标签
        case WM_PAINT: {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd, &ps);
            SetTextAlign(hdc, GetTextAlign(hdc) | TA_CENTER);
            CreateText(hdc);
            EndPaint(hwnd, &ps);
            return 0;
        }
        //按上下按钮事件
        case WM_NOTIFY:
            callUpDown(wParam, lParam);
        default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}




// g++ -mwindows main.c