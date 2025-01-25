
#include <Windows.h>

#define internal static
#define local_persist static
#define global_variable static

// TODO: This is a global for now.
global_variable bool Running;

internal void
Win32resizeDIBSection(int Width, int Height)
{
    BITMAPINFO BitmapInfo;
    BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
    BitmapInfo.biWitdh = Width;
    BitmapInfo.biHeight = Height;

    void* BitmapMemory;
    HBITMAP BitmapHandle = CreateDIBSection(
        DeviceContext, &BitmapInfo,
        DIB_RGB_COLORS,
        &BitmapMemory,
        0, 0);

}

internal void 
Win32UpdateWindow(HDC DeviceContext, int X, int Y, int Width, int Height);
{
    StretchDIBits(DeviceContext, 
                    X, Y, Width, Height,
                    X, Y, Width, Height,
                    const VOID* lpBits,
                    const BITMAPINFO* lpBitsInfo,
                    DIB_RGBCOLORS, SRCCOPY);
}

LRESULT CALLBACK
Win32MainWindowCallback(
    HWND Window,
    UINT Message,
    WPARAM WParam,
    LPARAM LParam)
{
    LRESULT Result = 0;

    switch (Message
        )
    {
    case WM_SIZE:
    {
        RECT ClientRect;
        GetClientRect(Window, &ClientRect);
        int Width = ClientRect.right - ClientRect.left;
        int Height = ClientRect.bottom - ClientRect.top;
        ResizeDIBSection(Width, Height);
    } break;

    case WM_ACTIVATEAPP:
    {
        Running = false;
    } break;

    case WM_CLOSE:
    {
        // TODO: Handle this with a message to the user
        Running = false;
    } break;

    case WM_DESTROY:
    {
        // TODO: Handle this as an error - recreate window?
        Running = false;
    } break;

    case WM_PAINT:
    {
        PAINTSTRUCT Paint;
        HDC DeviceContext = BeginPaint(Window, &Paint);
        int X = Paint.rcPaint.left;
        int Y = Paint.rcPaint.top;
        int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
        int Width = Paint.rcPaint.right - Paint.rcPaint.left;
        Win32UpdateWIndow(DeviceContext, X, Y, Width, Height);
        EndPaint(Window, &Paint);
        if (Operation == WHITENESS)
        {
            Operation = BLACKNESS;
        }
        else
        {
            Operation = WHITENESS;
        }
        EndPaint(Window, &Paint);
    } break;



    default:
    {
        //OutputDebugString("default\n")
        Result = DefWindowProc(Window, Message, WParam, LParam);
    } break;
    }
    return (Result);
}

int CALLBACK
WinMain(HINSTANCE Instance,
    HINSTANCE PrevInstance,
    LPSTR CommandLine,
    int ShowCode)
{
    WNDCLASS WindowClass = {};

    //WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    WindowClass.lpfnWndProc = Win32MainWindowCallback;
    WindowClass.hInstance = Instance;
    //WindowClass.hIcon;
    WindowClass.lpszClassName = "HandmadeHeroWindowClass";

    if (RegisterClassA(&WindowClass))
    {
        HWND WindowHandle =
            CreateWindowExA(
                0,
                WindowClass.lpszClassName,
                "Handmade Hero",
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                0,
                0,
                Instance,
                0);
        if (WindowHandle)
        {
            Running = true;
            while (Running)
            {
                MSG Message;
                BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
                if (MessageResult > 0)
                {
                    TranslateMessage(&Message);
                    DispatchMessage(&Message);
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
        }

    }
    else
    {
        //TODO: Logging
    }

    RegisterClassA(&WindowClass);


    return(0);
}
