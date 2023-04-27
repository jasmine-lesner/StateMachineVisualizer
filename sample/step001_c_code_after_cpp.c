# 1 "TemplateFSM.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "TemplateFSM.c"
# 31 "TemplateFSM.c"
# 1 "ES_Configure.h" 1
# 36 "ES_Configure.h"
typedef enum {
    ES_NO_EVENT, ES_ERROR,
    ES_INIT,
    ES_ENTRY,
    ES_EXIT,
    ES_KEYINPUT,
    ES_LISTEVENTS,
    ES_TIMEOUT,
    ES_TIMERACTIVE,
    ES_TIMERSTOPPED,

    BATTERY_CONNECTED,
    BATTERY_DISCONNECTED,
    LIGHT_TO_DARK,
    DARK_TO_LIGHT,
    BUMPER_PRESSED,
    BUMPER_RELEASED,
    NUMBEROFEVENTS,
} ES_EventTyp_t;

static const char *EventNames[] = {
 "ES_NO_EVENT",
 "ES_ERROR",
 "ES_INIT",
 "ES_ENTRY",
 "ES_EXIT",
 "ES_KEYINPUT",
 "ES_LISTEVENTS",
 "ES_TIMEOUT",
 "ES_TIMERACTIVE",
 "ES_TIMERSTOPPED",
 "BATTERY_CONNECTED",
 "BATTERY_DISCONNECTED",
 "LIGHT_TO_DARK",
 "DARK_TO_LIGHT",
 "BUMPER_PRESSED",
 "BUMPER_RELEASED",
 "NUMBEROFEVENTS",
};
# 32 "TemplateFSM.c" 2
# 1 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Framework.h" 1
# 18 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Framework.h"
# 1 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\inttypes.h" 1 3 4







# 1 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\features.h" 1 3 4
# 9 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\inttypes.h" 2 3 4
# 1 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\stdint.h" 1 3 4
# 20 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\stdint.h" 3 4
# 1 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 1 3 4





# 5 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef double _Double;
# 118 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef unsigned int uintptr_t;
# 152 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef int intptr_t;
# 177 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef signed char int8_t;
# 191 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef short int int16_t;
# 205 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef int int32_t;
# 219 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef long long int int64_t;
# 233 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef long long int intmax_t;
# 247 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef unsigned char uint8_t;
# 261 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef short unsigned int uint16_t;
# 275 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef unsigned int uint32_t;
# 289 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef long long unsigned int uint64_t;
# 313 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef long long unsigned int uintmax_t;
# 21 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\stdint.h" 2 3 4


typedef int int_fast8_t;





typedef long long int int_fast64_t;





typedef signed char int_least8_t;





typedef short int int_least16_t;





typedef int int_least32_t;





typedef long long int int_least64_t;





typedef unsigned int uint_fast8_t;





typedef long long unsigned int uint_fast64_t;





typedef unsigned char uint_least8_t;





typedef short unsigned int uint_least16_t;





typedef unsigned int uint_least32_t;





typedef long long unsigned int uint_least64_t;
# 331 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\stdint.h" 3 4
# 1 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\stdint.h" 1 3 4

typedef int int_fast16_t;





typedef int int_fast32_t;





typedef unsigned int uint_fast16_t;





typedef unsigned int uint_fast32_t;
# 332 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\stdint.h" 2 3 4
# 10 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\inttypes.h" 2 3 4


# 1 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 1 3 4




typedef double _Double;
# 26 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef int wchar_t;
# 13 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\inttypes.h" 2 3 4

typedef struct { intmax_t quot, rem; } imaxdiv_t;

intmax_t imaxabs(intmax_t);
imaxdiv_t imaxdiv(intmax_t, intmax_t);

intmax_t strtoimax(const char *restrict, char **restrict, int);
uintmax_t strtoumax(const char *restrict, char **restrict, int);

intmax_t wcstoimax(const wchar_t *restrict, wchar_t **restrict, int);
uintmax_t wcstoumax(const wchar_t *restrict, wchar_t **restrict, int);
# 19 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Framework.h" 2
# 1 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Events.h" 1
# 23 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Events.h"

# 23 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Events.h"
typedef struct ES_Event_t {
    ES_EventTyp_t EventType;
    uint16_t EventParam;
}ES_Event;
# 20 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Framework.h" 2
# 1 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Timers.h" 1
# 32 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Timers.h"
typedef enum { ES_Timer_ERR = -1,
               ES_Timer_ACTIVE = 1,
               ES_Timer_OK = 0,
               ES_Timer_NOT_ACTIVE = 0
} ES_TimerReturn_t;
# 45 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Timers.h"
void ES_Timer_Init(void);
# 55 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Timers.h"
ES_TimerReturn_t ES_Timer_InitTimer(uint8_t Num, uint32_t NewTime);
# 64 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Timers.h"
ES_TimerReturn_t ES_Timer_SetTimer(uint8_t Num, uint32_t NewTime);







ES_TimerReturn_t ES_Timer_StartTimer(uint8_t Num);
# 81 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Timers.h"
ES_TimerReturn_t ES_Timer_StopTimer(uint8_t Num);
# 90 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Timers.h"
uint32_t ES_Timer_GetTime(void);
# 21 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Framework.h" 2
# 1 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_CheckEvents.h" 1
# 21 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_CheckEvents.h"
typedef uint8_t CheckFunc( void );

typedef CheckFunc (*pCheckFunc);

uint8_t ES_CheckUserEvents( void );
# 22 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Framework.h" 2
# 1 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_General.h" 1
# 23 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Framework.h" 2
# 1 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_KeyboardInput.h" 1
# 21 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_KeyboardInput.h"
uint8_t InitKeyboardInput(uint8_t Priority);
# 31 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_KeyboardInput.h"
uint8_t PostKeyboardInput(ES_Event ThisEvent);
# 44 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_KeyboardInput.h"
ES_Event RunKeyboardInput(ES_Event ThisEvent);
# 53 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_KeyboardInput.h"
void KeyboardInput_PrintEvents(void);
# 24 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Framework.h" 2
# 1 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_LookupTables.h" 1
# 29 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_LookupTables.h"
extern uint8_t const BitNum2ClrMask[];





extern uint8_t const BitNum2SetMask[];
# 44 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_LookupTables.h"
extern uint8_t const Byte2MSBitNum[255];
# 25 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Framework.h" 2
# 1 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Port.h" 1





extern unsigned char _CCR_temp;
# 26 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Framework.h" 2
# 1 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_PostList.h" 1
# 22 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_PostList.h"
typedef uint8_t PostFunc_t( ES_Event );

typedef PostFunc_t (*pPostFunc);

uint8_t ES_PostList00( ES_Event);
uint8_t ES_PostList01( ES_Event);
uint8_t ES_PostList02( ES_Event);
uint8_t ES_PostList03( ES_Event);
uint8_t ES_PostList04( ES_Event);
uint8_t ES_PostList05( ES_Event);
uint8_t ES_PostList06( ES_Event);
uint8_t ES_PostList07( ES_Event);
# 27 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Framework.h" 2
# 1 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_PriorTables.h" 1



uint8_t GetMSBitNum( uint8_t Value );


uint8_t GetClearMask( uint8_t BitNum );


uint8_t GetSetMask( uint8_t BitNum );
# 28 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Framework.h" 2
# 1 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Queue.h" 1
# 24 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Queue.h"
uint8_t ES_InitQueue( ES_Event * pBlock, unsigned char BlockSize );
uint8_t ES_EnQueueFIFO( ES_Event * pBlock, ES_Event Event2Add );
uint8_t ES_DeQueue( ES_Event * pBlock, ES_Event * pReturnEvent );

uint8_t ES_IsQueueEmpty( ES_Event * pBlock );
# 29 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Framework.h" 2
# 1 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_ServiceHeaders.h" 1
# 13 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_ServiceHeaders.h"
# 1 "C:\\Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X/ES_Configure.h" 1
# 14 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_ServiceHeaders.h" 2




# 1 "C:\\Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X/TemplateFSM.h" 1
# 26 "C:\\Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X/TemplateFSM.h"
# 1 "C:\\Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X/ES_Configure.h" 1
# 27 "C:\\Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X/TemplateFSM.h" 2
# 53 "C:\\Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X/TemplateFSM.h"
uint8_t InitTemplateFSM(uint8_t Priority);
# 64 "C:\\Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X/TemplateFSM.h"
uint8_t PostTemplateFSM(ES_Event ThisEvent);
# 79 "C:\\Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X/TemplateFSM.h"
ES_Event RunTemplateFSM(ES_Event ThisEvent);
# 19 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_ServiceHeaders.h" 2
# 30 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Framework.h" 2
# 1 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_TattleTale.h" 1
# 25 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_TattleTale.h"
void ES_AddTattlePoint(const char * FunctionName, const char * StateName, ES_Event ThisEvent);
# 36 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_TattleTale.h"
void ES_CheckTail(const char *FunctionName);
# 31 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/ES_Framework.h" 2





typedef enum {
              Success = 0,
              FailedPost = 1,
              FailedRun,
              FailedPointer,
              FailedIndex,
              FailedInit
} ES_Return_t;

ES_Return_t ES_Initialize( void );


ES_Return_t ES_Run( void );
uint8_t ES_PostAll( ES_Event ThisEvent );
uint8_t ES_PostToService( uint8_t WhichService, ES_Event ThisEvent);
# 33 "TemplateFSM.c" 2

# 1 "TemplateFSM.h" 1
# 35 "TemplateFSM.c" 2
# 1 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/BOARD.h" 1
# 12 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/BOARD.h"
# 1 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\lega-c\\generictypedefs.h" 1 3 4
# 63 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\lega-c\\generictypedefs.h" 3 4
# 1 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\stddef.h" 1 3 4
# 26 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\stddef.h" 3 4
# 1 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 1 3 4





# 5 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef double _Double;
# 51 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef struct { long long __ll; long double __ld; } max_align_t;
# 104 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef unsigned int size_t;
# 132 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef int ptrdiff_t;
# 27 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\stddef.h" 2 3 4
# 64 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\lega-c\\generictypedefs.h" 2 3 4

typedef enum _BOOL { FALSE = 0, TRUE } BOOL;
typedef enum _BIT { CLEAR = 0, SET } BIT;






typedef signed int INT;
typedef signed char INT8;
typedef signed short int INT16;
typedef signed long int INT32;



__extension__ typedef signed long long INT64;



typedef unsigned int UINT;
typedef unsigned char UINT8;
typedef unsigned short int UINT16;




typedef unsigned long int UINT32;


__extension__ typedef unsigned long long UINT64;


typedef union
{
    UINT8 Val;
    struct
    {
        __extension__ UINT8 b0:1;
        __extension__ UINT8 b1:1;
        __extension__ UINT8 b2:1;
        __extension__ UINT8 b3:1;
        __extension__ UINT8 b4:1;
        __extension__ UINT8 b5:1;
        __extension__ UINT8 b6:1;
        __extension__ UINT8 b7:1;
    } bits;
} UINT8_VAL, UINT8_BITS;

typedef union
{
    UINT16 Val;
    UINT8 v[2];
    struct
    {
        UINT8 LB;
        UINT8 HB;
    } byte;
    struct
    {
        __extension__ UINT8 b0:1;
        __extension__ UINT8 b1:1;
        __extension__ UINT8 b2:1;
        __extension__ UINT8 b3:1;
        __extension__ UINT8 b4:1;
        __extension__ UINT8 b5:1;
        __extension__ UINT8 b6:1;
        __extension__ UINT8 b7:1;
        __extension__ UINT8 b8:1;
        __extension__ UINT8 b9:1;
        __extension__ UINT8 b10:1;
        __extension__ UINT8 b11:1;
        __extension__ UINT8 b12:1;
        __extension__ UINT8 b13:1;
        __extension__ UINT8 b14:1;
        __extension__ UINT8 b15:1;
    } bits;
} UINT16_VAL, UINT16_BITS;
# 185 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\lega-c\\generictypedefs.h" 3 4
typedef union
{
    UINT32 Val;
    UINT16 w[2];
    UINT8 v[4];
    struct
    {
        UINT16 LW;
        UINT16 HW;
    } word;
    struct
    {
        UINT8 LB;
        UINT8 HB;
        UINT8 UB;
        UINT8 MB;
    } byte;
    struct
    {
        UINT16_VAL low;
        UINT16_VAL high;
    }wordUnion;
    struct
    {
        __extension__ UINT8 b0:1;
        __extension__ UINT8 b1:1;
        __extension__ UINT8 b2:1;
        __extension__ UINT8 b3:1;
        __extension__ UINT8 b4:1;
        __extension__ UINT8 b5:1;
        __extension__ UINT8 b6:1;
        __extension__ UINT8 b7:1;
        __extension__ UINT8 b8:1;
        __extension__ UINT8 b9:1;
        __extension__ UINT8 b10:1;
        __extension__ UINT8 b11:1;
        __extension__ UINT8 b12:1;
        __extension__ UINT8 b13:1;
        __extension__ UINT8 b14:1;
        __extension__ UINT8 b15:1;
        __extension__ UINT8 b16:1;
        __extension__ UINT8 b17:1;
        __extension__ UINT8 b18:1;
        __extension__ UINT8 b19:1;
        __extension__ UINT8 b20:1;
        __extension__ UINT8 b21:1;
        __extension__ UINT8 b22:1;
        __extension__ UINT8 b23:1;
        __extension__ UINT8 b24:1;
        __extension__ UINT8 b25:1;
        __extension__ UINT8 b26:1;
        __extension__ UINT8 b27:1;
        __extension__ UINT8 b28:1;
        __extension__ UINT8 b29:1;
        __extension__ UINT8 b30:1;
        __extension__ UINT8 b31:1;
    } bits;
} UINT32_VAL;



typedef union
{
    UINT64 Val;
    UINT32 d[2];
    UINT16 w[4];
    UINT8 v[8];
    struct
    {
        UINT32 LD;
        UINT32 HD;
    } dword;
    struct
    {
        UINT16 LW;
        UINT16 HW;
        UINT16 UW;
        UINT16 MW;
    } word;
    struct
    {
        __extension__ UINT8 b0:1;
        __extension__ UINT8 b1:1;
        __extension__ UINT8 b2:1;
        __extension__ UINT8 b3:1;
        __extension__ UINT8 b4:1;
        __extension__ UINT8 b5:1;
        __extension__ UINT8 b6:1;
        __extension__ UINT8 b7:1;
        __extension__ UINT8 b8:1;
        __extension__ UINT8 b9:1;
        __extension__ UINT8 b10:1;
        __extension__ UINT8 b11:1;
        __extension__ UINT8 b12:1;
        __extension__ UINT8 b13:1;
        __extension__ UINT8 b14:1;
        __extension__ UINT8 b15:1;
        __extension__ UINT8 b16:1;
        __extension__ UINT8 b17:1;
        __extension__ UINT8 b18:1;
        __extension__ UINT8 b19:1;
        __extension__ UINT8 b20:1;
        __extension__ UINT8 b21:1;
        __extension__ UINT8 b22:1;
        __extension__ UINT8 b23:1;
        __extension__ UINT8 b24:1;
        __extension__ UINT8 b25:1;
        __extension__ UINT8 b26:1;
        __extension__ UINT8 b27:1;
        __extension__ UINT8 b28:1;
        __extension__ UINT8 b29:1;
        __extension__ UINT8 b30:1;
        __extension__ UINT8 b31:1;
        __extension__ UINT8 b32:1;
        __extension__ UINT8 b33:1;
        __extension__ UINT8 b34:1;
        __extension__ UINT8 b35:1;
        __extension__ UINT8 b36:1;
        __extension__ UINT8 b37:1;
        __extension__ UINT8 b38:1;
        __extension__ UINT8 b39:1;
        __extension__ UINT8 b40:1;
        __extension__ UINT8 b41:1;
        __extension__ UINT8 b42:1;
        __extension__ UINT8 b43:1;
        __extension__ UINT8 b44:1;
        __extension__ UINT8 b45:1;
        __extension__ UINT8 b46:1;
        __extension__ UINT8 b47:1;
        __extension__ UINT8 b48:1;
        __extension__ UINT8 b49:1;
        __extension__ UINT8 b50:1;
        __extension__ UINT8 b51:1;
        __extension__ UINT8 b52:1;
        __extension__ UINT8 b53:1;
        __extension__ UINT8 b54:1;
        __extension__ UINT8 b55:1;
        __extension__ UINT8 b56:1;
        __extension__ UINT8 b57:1;
        __extension__ UINT8 b58:1;
        __extension__ UINT8 b59:1;
        __extension__ UINT8 b60:1;
        __extension__ UINT8 b61:1;
        __extension__ UINT8 b62:1;
        __extension__ UINT8 b63:1;
    } bits;
} UINT64_VAL;





typedef void VOID;

typedef char CHAR8;
typedef unsigned char UCHAR8;

typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned long DWORD;


__extension__
typedef unsigned long long QWORD;

typedef signed char CHAR;
typedef signed short int SHORT;
typedef signed long LONG;


__extension__
typedef signed long long LONGLONG;

typedef union
{
    BYTE Val;
    struct
    {
        __extension__ BYTE b0:1;
        __extension__ BYTE b1:1;
        __extension__ BYTE b2:1;
        __extension__ BYTE b3:1;
        __extension__ BYTE b4:1;
        __extension__ BYTE b5:1;
        __extension__ BYTE b6:1;
        __extension__ BYTE b7:1;
    } bits;
} BYTE_VAL, BYTE_BITS;

typedef union
{
    WORD Val;
    BYTE v[2];
    struct
    {
        BYTE LB;
        BYTE HB;
    } byte;
    struct
    {
        __extension__ BYTE b0:1;
        __extension__ BYTE b1:1;
        __extension__ BYTE b2:1;
        __extension__ BYTE b3:1;
        __extension__ BYTE b4:1;
        __extension__ BYTE b5:1;
        __extension__ BYTE b6:1;
        __extension__ BYTE b7:1;
        __extension__ BYTE b8:1;
        __extension__ BYTE b9:1;
        __extension__ BYTE b10:1;
        __extension__ BYTE b11:1;
        __extension__ BYTE b12:1;
        __extension__ BYTE b13:1;
        __extension__ BYTE b14:1;
        __extension__ BYTE b15:1;
    } bits;
} WORD_VAL, WORD_BITS;

typedef union
{
    DWORD Val;
    WORD w[2];
    BYTE v[4];
    struct
    {
        WORD LW;
        WORD HW;
    } word;
    struct
    {
        BYTE LB;
        BYTE HB;
        BYTE UB;
        BYTE MB;
    } byte;
    struct
    {
        WORD_VAL low;
        WORD_VAL high;
    }wordUnion;
    struct
    {
        __extension__ BYTE b0:1;
        __extension__ BYTE b1:1;
        __extension__ BYTE b2:1;
        __extension__ BYTE b3:1;
        __extension__ BYTE b4:1;
        __extension__ BYTE b5:1;
        __extension__ BYTE b6:1;
        __extension__ BYTE b7:1;
        __extension__ BYTE b8:1;
        __extension__ BYTE b9:1;
        __extension__ BYTE b10:1;
        __extension__ BYTE b11:1;
        __extension__ BYTE b12:1;
        __extension__ BYTE b13:1;
        __extension__ BYTE b14:1;
        __extension__ BYTE b15:1;
        __extension__ BYTE b16:1;
        __extension__ BYTE b17:1;
        __extension__ BYTE b18:1;
        __extension__ BYTE b19:1;
        __extension__ BYTE b20:1;
        __extension__ BYTE b21:1;
        __extension__ BYTE b22:1;
        __extension__ BYTE b23:1;
        __extension__ BYTE b24:1;
        __extension__ BYTE b25:1;
        __extension__ BYTE b26:1;
        __extension__ BYTE b27:1;
        __extension__ BYTE b28:1;
        __extension__ BYTE b29:1;
        __extension__ BYTE b30:1;
        __extension__ BYTE b31:1;
    } bits;
} DWORD_VAL;



typedef union
{
    QWORD Val;
    DWORD d[2];
    WORD w[4];
    BYTE v[8];
    struct
    {
        DWORD LD;
        DWORD HD;
    } dword;
    struct
    {
        WORD LW;
        WORD HW;
        WORD UW;
        WORD MW;
    } word;
    struct
    {
        __extension__ BYTE b0:1;
        __extension__ BYTE b1:1;
        __extension__ BYTE b2:1;
        __extension__ BYTE b3:1;
        __extension__ BYTE b4:1;
        __extension__ BYTE b5:1;
        __extension__ BYTE b6:1;
        __extension__ BYTE b7:1;
        __extension__ BYTE b8:1;
        __extension__ BYTE b9:1;
        __extension__ BYTE b10:1;
        __extension__ BYTE b11:1;
        __extension__ BYTE b12:1;
        __extension__ BYTE b13:1;
        __extension__ BYTE b14:1;
        __extension__ BYTE b15:1;
        __extension__ BYTE b16:1;
        __extension__ BYTE b17:1;
        __extension__ BYTE b18:1;
        __extension__ BYTE b19:1;
        __extension__ BYTE b20:1;
        __extension__ BYTE b21:1;
        __extension__ BYTE b22:1;
        __extension__ BYTE b23:1;
        __extension__ BYTE b24:1;
        __extension__ BYTE b25:1;
        __extension__ BYTE b26:1;
        __extension__ BYTE b27:1;
        __extension__ BYTE b28:1;
        __extension__ BYTE b29:1;
        __extension__ BYTE b30:1;
        __extension__ BYTE b31:1;
        __extension__ BYTE b32:1;
        __extension__ BYTE b33:1;
        __extension__ BYTE b34:1;
        __extension__ BYTE b35:1;
        __extension__ BYTE b36:1;
        __extension__ BYTE b37:1;
        __extension__ BYTE b38:1;
        __extension__ BYTE b39:1;
        __extension__ BYTE b40:1;
        __extension__ BYTE b41:1;
        __extension__ BYTE b42:1;
        __extension__ BYTE b43:1;
        __extension__ BYTE b44:1;
        __extension__ BYTE b45:1;
        __extension__ BYTE b46:1;
        __extension__ BYTE b47:1;
        __extension__ BYTE b48:1;
        __extension__ BYTE b49:1;
        __extension__ BYTE b50:1;
        __extension__ BYTE b51:1;
        __extension__ BYTE b52:1;
        __extension__ BYTE b53:1;
        __extension__ BYTE b54:1;
        __extension__ BYTE b55:1;
        __extension__ BYTE b56:1;
        __extension__ BYTE b57:1;
        __extension__ BYTE b58:1;
        __extension__ BYTE b59:1;
        __extension__ BYTE b60:1;
        __extension__ BYTE b61:1;
        __extension__ BYTE b62:1;
        __extension__ BYTE b63:1;
    } bits;
} QWORD_VAL;
# 13 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/BOARD.h" 2
# 76 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/BOARD.h"

# 76 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/BOARD.h"
void BOARD_Init();
# 85 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/BOARD.h"
void BOARD_End();







unsigned int BOARD_GetPBClock();
# 36 "TemplateFSM.c" 2

# 1 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/roach.h" 1
# 41 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/roach.h"
void Roach_Init(void);
# 51 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/roach.h"
char Roach_LeftMtrSpeed(char newSpeed);
# 60 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/roach.h"
char Roach_RightMtrSpeed(char newSpeed);







unsigned int Roach_LightLevel(void);







unsigned int Roach_BatteryVoltage(void);







unsigned char Roach_ReadFrontLeftBumper(void);
# 93 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/roach.h"
unsigned char Roach_ReadFrontRightBumper(void);







unsigned char Roach_ReadRearLeftBumper(void);







unsigned char Roach_ReadRearRightBumper(void);







unsigned char Roach_ReadBumpers(void);
# 127 "C:\\Users/chris/OneDrive/Desktop/ECE118/include/roach.h"
char Roach_LEDSSet(uint16_t pattern);





uint16_t Roach_LEDSGet(void);







char Roach_BarGraph(uint8_t Number);
# 38 "TemplateFSM.c" 2
# 1 "C:\\Users/chris/OneDrive/Desktop/MPLAB_Projects/EventChecking.X/TemplateEventChecker.h" 1
# 29 "C:\\Users/chris/OneDrive/Desktop/MPLAB_Projects/EventChecking.X/TemplateEventChecker.h"
# 1 "C:\\Users/chris/OneDrive/Desktop/MPLAB_Projects/EventChecking.X/ES_Configure.h" 1
# 30 "C:\\Users/chris/OneDrive/Desktop/MPLAB_Projects/EventChecking.X/TemplateEventChecker.h" 2
# 60 "C:\\Users/chris/OneDrive/Desktop/MPLAB_Projects/EventChecking.X/TemplateEventChecker.h"
uint8_t TemplateCheckBattery(void);

uint8_t TestIfDark(void);

uint8_t TestIfLight(void);

uint8_t TestBumpers(void);
# 39 "TemplateFSM.c" 2
# 1 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\stdio.h" 1 3 4
# 22 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\stdio.h" 3 4
# 1 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 1 3 4





# 5 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef double _Double;







typedef __builtin_va_list va_list;




typedef __builtin_va_list __isoc_va_list;
# 145 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef int ssize_t;
# 336 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef long long off_t;
# 506 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\bits\\alltypes.h" 3 4
typedef struct _IO_FILE FILE;
# 23 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\stdio.h" 2 3 4
# 50 "c:\\program files\\microchip\\xc32\\v4.10\\pic32mx\\include\\musl\\stdio.h" 3 4
typedef union _G_fpos64_t {
 char __opaque[16];
 double __align;
} fpos_t;

extern __attribute__((section(".data._stdout"))) FILE *const *_stdout;
extern __attribute__((section(".data._stderr"))) FILE *const *_stderr;
extern __attribute__((section(".data._stdin"))) FILE *const *_stdin;





FILE *fopen(const char *restrict, const char *restrict);
FILE *freopen(const char *restrict, const char *restrict, FILE *restrict);
int fclose(FILE *);

int remove(const char *);
int rename(const char *, const char *);

int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
void clearerr(FILE *);

int fseek(FILE *, long, int);
long ftell(FILE *);
void rewind(FILE *);

int fgetpos(FILE *restrict, fpos_t *restrict);
int fsetpos(FILE *, const fpos_t *);

size_t fread(void *restrict, size_t, size_t, FILE *restrict);
size_t fwrite(const void *restrict, size_t, size_t, FILE *restrict);

int fgetc(FILE *);
int getc(FILE *);
int getchar(void);
int ungetc(int, FILE *);

int fputc(int, FILE *);
int putc(int, FILE *);
int putchar(int);

char *fgets(char *restrict, int, FILE *restrict);




int fputs(const char *restrict, FILE *restrict);
int puts(const char *);

int printf(const char *restrict, ...);
int fprintf(FILE *restrict, const char *restrict, ...);
int sprintf(char *restrict, const char *restrict, ...);
int snprintf(char *restrict, size_t, const char *restrict, ...);

int vprintf(const char *restrict, __isoc_va_list);
int vfprintf(FILE *restrict, const char *restrict, __isoc_va_list);
int vsprintf(char *restrict, const char *restrict, __isoc_va_list);
int vsnprintf(char *restrict, size_t, const char *restrict, __isoc_va_list);

int scanf(const char *restrict, ...);
int fscanf(FILE *restrict, const char *restrict, ...);
int sscanf(const char *restrict, const char *restrict, ...);
int vscanf(const char *restrict, __isoc_va_list);
int vfscanf(FILE *restrict, const char *restrict, __isoc_va_list);
int vsscanf(const char *restrict, const char *restrict, __isoc_va_list);

void perror(const char *);

int setvbuf(FILE *restrict, char *restrict, int, size_t);
void setbuf(FILE *restrict, char *restrict);

char *tmpnam(char *);
FILE *tmpfile(void);




FILE *fmemopen(void *restrict, size_t, const char *restrict);
FILE *fdopen(int, const char *);
int fileno(FILE *);
int fseeko(FILE *, off_t, int);
off_t ftello(FILE *);
int getc_unlocked(FILE *);
int getchar_unlocked(void);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);






char *tempnam(const char *, const char *);



void setbuffer(FILE *, char *, size_t);
void setlinebuf(FILE *f);
int fgetc_unlocked(FILE *);
int fputc_unlocked(int, FILE *);
int fflush_unlocked(FILE *);
size_t fread_unlocked(void *, size_t, size_t, FILE *);
size_t fwrite_unlocked(const void *, size_t, size_t, FILE *);
int feof_unlocked(FILE *);
int ferror_unlocked(FILE *);
int fileno_unlocked(FILE *);
int asprintf(char **, const char *, ...);
int vasprintf(char **, const char *, __isoc_va_list);
# 40 "TemplateFSM.c" 2
# 49 "TemplateFSM.c"

# 49 "TemplateFSM.c"
unsigned char previousBumpers = 0;







void goForward(int speed)
{
    Roach_RightMtrSpeed(speed);
    Roach_LeftMtrSpeed(speed);
}

void stopMovement()
{
    Roach_RightMtrSpeed(0);
    Roach_LeftMtrSpeed(0);
}

void backUpRight(int speed)
{
    Roach_RightMtrSpeed(-1 * (speed-20));
    Roach_LeftMtrSpeed(-1 * speed);
}

void backUpLeft(int speed)
{
    Roach_RightMtrSpeed(-1 * speed);
    Roach_LeftMtrSpeed(-1 * (speed-20));
}

void turnRight (int speed)
{
    Roach_RightMtrSpeed(speed - 20);
    Roach_LeftMtrSpeed(speed);
}

void turnLeft (int speed)
{
    Roach_RightMtrSpeed(speed);
    Roach_LeftMtrSpeed(speed - 20);
}
# 100 "TemplateFSM.c"
typedef enum {
    InitPState,
    Hiding,
    Moving,
    Getting_Unstuck,
} TemplateFSMState_t;

static const char *StateNames[] = {
 "InitPState",
 "Hiding",
 "Moving",
 "Getting_Unstuck",
};


static TemplateFSMState_t CurrentState = InitPState;
static uint8_t MyPriority;
# 133 "TemplateFSM.c"
uint8_t InitTemplateFSM(uint8_t Priority)
{
    MyPriority = Priority;

    CurrentState = InitPState;

    if (ES_PostToService(MyPriority, (ES_Event){ES_INIT,0x0000}) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}
# 155 "TemplateFSM.c"
uint8_t PostTemplateFSM(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}
# 172 "TemplateFSM.c"
ES_Event RunTemplateFSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE;
    TemplateFSMState_t nextState;

    ES_AddTattlePoint(__FUNCTION__,StateNames[CurrentState],ThisEvent);

    switch (CurrentState) {
    case InitPState:
        if (ThisEvent.EventType == ES_INIT)
        {




            nextState = Hiding;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;

    case Hiding:
        switch (ThisEvent.EventType) {

            case ES_ENTRY:
                break;

            case ES_EXIT:
                break;

            case DARK_TO_LIGHT:
                goForward(100);

                nextState = Moving;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;

            default:
                break;
        }
        break;

    case Moving:
        if (ThisEvent.EventType == LIGHT_TO_DARK)
        {
            stopMovement();
            nextState = Hiding;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }

        if (ThisEvent.EventType == BUMPER_PRESSED)
        {
           if(ThisEvent.EventParam == 1)
           {
               previousBumpers = 1;
               backUpRight(90);
                ES_Timer_InitTimer(0,3000);
                nextState = Getting_Unstuck;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
           }
           else if(ThisEvent.EventParam == 2)
           {
                previousBumpers = 2;
                backUpLeft(90);
                ES_Timer_InitTimer(0,3000);
                nextState = Getting_Unstuck;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
           }
           else if(ThisEvent.EventParam == 4)
           {
                turnLeft(90);
                ES_Timer_InitTimer(0,3000);
                nextState = Getting_Unstuck;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
           }
           else if(ThisEvent.EventParam == 8)
           {
                turnRight(90);
                ES_Timer_InitTimer(0,3000);
                nextState = Getting_Unstuck;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
           }
        }
        break;

    case Getting_Unstuck:
        if (ThisEvent.EventType == LIGHT_TO_DARK)
        {
            stopMovement();
            nextState = Hiding;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }

        if (ThisEvent.EventType == ES_TIMEOUT && ThisEvent.EventParam == 0)
        {
            if(Roach_ReadBumpers() == 0)
            {
                goForward(100);
                nextState = Moving;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            } else {
                ES_Timer_InitTimer(0,3000);
            }
        }
# 292 "TemplateFSM.c"
        break;

    default:
        break;
    }
    if (makeTransition == TRUE) {

        RunTemplateFSM((ES_Event){ES_EXIT,0x0000});
        CurrentState = nextState;
        RunTemplateFSM((ES_Event){ES_ENTRY,0x0000});
    }
    ES_CheckTail(__FUNCTION__);
    return ThisEvent;
}
