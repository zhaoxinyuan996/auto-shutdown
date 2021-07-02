#include <stdio.h>
#include <windows.h>
//#include "script.c"

#define WIDTH 200
#define HEIGHT 100

void ShutDown(){
    system("dir");
}
HINSTANCE hAppInstance;    //Ӧ�ó���������ΪҪʹ�õĵط�̫����Ҫ�����ȫ�ֱ�������winmain�����и�����ֵ

//������ť
void CreateButton(HWND hwnd)
{
    HWND hwndPushButton;
    HWND hwndCheckBox;
    HWND hwndRadio;

    hwndPushButton = CreateWindow (
            TEXT("button"),
            TEXT("��ͨ��ť"),
    //WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,                            
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            100, 50,
            80, 20,
            hwnd,
            (HMENU)1001,        //�Ӵ���ID                    
            hAppInstance,         //Ӧ�ó���ľ����                        
            NULL);

    hwndRadio = CreateWindow (
            TEXT("button"),
            TEXT("��ѡ��ť"),
    //WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON | BS_AUTORADIOBUTTON,                            
            WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON  ,
            10, 70,
            80, 20,
            hwnd,
            (HMENU)1003,        //�Ӵ���ID                    
            hAppInstance,
            NULL);
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
            TEXT("�ҵĵ�һ������"),                //���ڱ���
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


    //4.��ʾ����
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
)
{
    switch(uMsg)
    {
        //������Ϣ                            
        case WM_CREATE:
        {
//            printf("WM_CREATE %d %d\n",wParam,lParam);
            CREATESTRUCT* createst = (CREATESTRUCT*)lParam;
//            printf("CREATESTRUCT %s\n",createst->lpszClass);

            return 0;
        }
        // �˳��¼�
        case WM_DESTROY:
        {
            printf("WM_DESTROY %d %d\n",wParam,lParam);
            PostQuitMessage(0);

            return 0;
        }
            //�����¼�
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
            //��ť��Ϣ
        case WM_COMMAND:
        {
            return DefWindowProc(hwnd,uMsg,wParam,lParam);
        }
    }
    return DefWindowProc(hwnd,uMsg,wParam,lParam);
}






// g++ -mwindows winapp.c