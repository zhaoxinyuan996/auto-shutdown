#include <stdio.h>
#include <windows.h>

#define WIDTH 200
#define HEIGHT 100
#define BUTTON1 01
#define BUTTON2 02
#define INPUT1  011
#define MAX_INPUT_LEN 70
#define MAX_SECOND_LEN 10

HINSTANCE hAppInstance;    //Ӧ�ó���������ΪҪʹ�õĵط�̫����Ҫ�����ȫ�ֱ�������winmain�����и�����ֵ
char cmd[80] = "Shutdown -r -t ";
char secondList[MAX_SECOND_LEN];
int second;

// ���ػ�����
void shutDown(){
    if (0 < second && second < 315360000){
        strcat(cmd, itoa(second, secondList, 10));
        system("shutdown -a");
        system(cmd);
        printf("%s\n", secondList);
        printf("%s", cmd);
    }
//
}
void unShutDown(){
    system("shutdown -a");
}

//������ť
void CreateButton(HWND hwnd){
    CreateWindow (
            TEXT("button"),
            TEXT("ȷ��"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            100, 50,
            40, 20,
            hwnd,
            (HMENU)BUTTON1,        //�Ӵ���ID
            hAppInstance,         //Ӧ�ó���ľ����                        
            NULL);
    CreateWindow (
            TEXT("button"),
            TEXT("ȡ��"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            150, 50,
            40, 20,
            hwnd,
            (HMENU)BUTTON2,        //�Ӵ���ID
            hAppInstance,         //Ӧ�ó���ľ����
            NULL);
}

//���������
void CreateInput(HWND hwnd){
    CreateWindow (
            TEXT("edit"),
            TEXT("3600"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
            10, 50,
            MAX_INPUT_LEN, 20,
            hwnd,
            (HMENU)INPUT1,        //�Ӵ���ID
            hAppInstance,         //Ӧ�ó���ľ����
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
) {
    switch (uMsg) {

        // �˳��¼�
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
            //��ť��Ϣ
        case WM_COMMAND: {
            if (LOWORD(wParam) == BUTTON1) {

                second = (int) GetDlgItemInt(hwnd,INPUT1,NULL,0);
                shutDown();
                PostQuitMessage(0);
            } else if (LOWORD(wParam) == BUTTON2) {
                unShutDown();
                PostQuitMessage(0);
            }
        }
        default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}




// g++ -mwindows main.c