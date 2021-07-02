#include <stdio.h>
#include <windows.h>
//#include "script.c"

#define WIDTH 200
#define HEIGHT 100

void ShutDown(){
    system("dir");
}
HINSTANCE hAppInstance;    //应用程序句柄，因为要使用的地方太多需要定义成全局变量；在winmain函数中给它赋值

//创建按钮
void CreateButton(HWND hwnd)
{
    HWND hwndPushButton;
    HWND hwndCheckBox;
    HWND hwndRadio;

    hwndPushButton = CreateWindow (
            TEXT("button"),
            TEXT("普通按钮"),
    //WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,                            
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            100, 50,
            80, 20,
            hwnd,
            (HMENU)1001,        //子窗口ID                    
            hAppInstance,         //应用程序的句柄，                        
            NULL);

    hwndRadio = CreateWindow (
            TEXT("button"),
            TEXT("单选按钮"),
    //WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON | BS_AUTORADIOBUTTON,                            
            WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON  ,
            10, 70,
            80, 20,
            hwnd,
            (HMENU)1003,        //子窗口ID                    
            hAppInstance,
            NULL);
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
            TEXT("我的第一个窗口"),                //窗口标题
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


    //4.显示窗口
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
)
{
    switch(uMsg)
    {
        //窗口消息                            
        case WM_CREATE:
        {
//            printf("WM_CREATE %d %d\n",wParam,lParam);
            CREATESTRUCT* createst = (CREATESTRUCT*)lParam;
//            printf("CREATESTRUCT %s\n",createst->lpszClass);

            return 0;
        }
        // 退出事件
        case WM_DESTROY:
        {
            printf("WM_DESTROY %d %d\n",wParam,lParam);
            PostQuitMessage(0);

            return 0;
        }
            //键盘事件
        case WM_KEYUP:
        {
            printf("WM_KEYUP %d %d\n",wParam,lParam);

            return 0;
        }
        case WM_KEYDOWN:
        {
            printf("WM_KEYDOWN %d %d\n",wParam,lParam);

            return 0;
        }
            //按钮消息
        case WM_COMMAND:
        {
            return DefWindowProc(hwnd,uMsg,wParam,lParam);
        }
    }
    return DefWindowProc(hwnd,uMsg,wParam,lParam);
}






// g++ -mwindows winapp.c