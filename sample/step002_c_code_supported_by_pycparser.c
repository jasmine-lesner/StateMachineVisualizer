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












typedef double _Double;
typedef unsigned int uintptr_t;
typedef int intptr_t;
typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long long int int64_t;
typedef long long int intmax_t;
typedef unsigned char uint8_t;
typedef short unsigned int uint16_t;
typedef unsigned int uint32_t;
typedef long long unsigned int uint64_t;
typedef long long unsigned int uintmax_t;


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

typedef int int_fast16_t;





typedef int int_fast32_t;





typedef unsigned int uint_fast16_t;





typedef unsigned int uint_fast32_t;






typedef double _Double;
typedef int wchar_t;

typedef struct { intmax_t quot, rem; } imaxdiv_t;

intmax_t imaxabs(intmax_t);
imaxdiv_t imaxdiv(intmax_t, intmax_t);

intmax_t strtoimax(const char *restrict, char **restrict, int);
uintmax_t strtoumax(const char *restrict, char **restrict, int);

intmax_t wcstoimax(const wchar_t *restrict, wchar_t **restrict, int);
uintmax_t wcstoumax(const wchar_t *restrict, wchar_t **restrict, int);

typedef struct ES_Event_t {
    ES_EventTyp_t EventType;
    uint16_t EventParam;
}ES_Event;
typedef enum { ES_Timer_ERR = -1,
               ES_Timer_ACTIVE = 1,
               ES_Timer_OK = 0,
               ES_Timer_NOT_ACTIVE = 0
} ES_TimerReturn_t;
void ES_Timer_Init(void);
ES_TimerReturn_t ES_Timer_InitTimer(uint8_t Num, uint32_t NewTime);
ES_TimerReturn_t ES_Timer_SetTimer(uint8_t Num, uint32_t NewTime);







ES_TimerReturn_t ES_Timer_StartTimer(uint8_t Num);
ES_TimerReturn_t ES_Timer_StopTimer(uint8_t Num);
uint32_t ES_Timer_GetTime(void);
typedef uint8_t CheckFunc( void );

typedef CheckFunc (*pCheckFunc);

uint8_t ES_CheckUserEvents( void );
uint8_t InitKeyboardInput(uint8_t Priority);
uint8_t PostKeyboardInput(ES_Event ThisEvent);
ES_Event RunKeyboardInput(ES_Event ThisEvent);
void KeyboardInput_PrintEvents(void);
extern uint8_t const BitNum2ClrMask[];





extern uint8_t const BitNum2SetMask[];
extern uint8_t const Byte2MSBitNum[255];





extern unsigned char _CCR_temp;
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



uint8_t GetMSBitNum( uint8_t Value );


uint8_t GetClearMask( uint8_t BitNum );


uint8_t GetSetMask( uint8_t BitNum );
uint8_t ES_InitQueue( ES_Event * pBlock, unsigned char BlockSize );
uint8_t ES_EnQueueFIFO( ES_Event * pBlock, ES_Event Event2Add );
uint8_t ES_DeQueue( ES_Event * pBlock, ES_Event * pReturnEvent );

uint8_t ES_IsQueueEmpty( ES_Event * pBlock );




uint8_t InitTemplateFSM(uint8_t Priority);
uint8_t PostTemplateFSM(ES_Event ThisEvent);
ES_Event RunTemplateFSM(ES_Event ThisEvent);
void ES_AddTattlePoint(const char * FunctionName, const char * StateName, ES_Event ThisEvent);
void ES_CheckTail(const char *FunctionName);





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






typedef double _Double;
typedef struct { long long __ll; long double __ld; } max_align_t;
typedef unsigned int size_t;
typedef int ptrdiff_t;

typedef enum _BOOL { FALSE = 0, TRUE } BOOL;
typedef enum _BIT { CLEAR = 0, SET } BIT;






typedef signed int INT;
typedef signed char INT8;
typedef signed short int INT16;
typedef signed long int INT32;



  typedef signed long long INT64;



typedef unsigned int UINT;
typedef unsigned char UINT8;
typedef unsigned short int UINT16;




typedef unsigned long int UINT32;


  typedef unsigned long long UINT64;


typedef union
{
    UINT8 Val;
    struct
    {
          UINT8 b0:1;
          UINT8 b1:1;
          UINT8 b2:1;
          UINT8 b3:1;
          UINT8 b4:1;
          UINT8 b5:1;
          UINT8 b6:1;
          UINT8 b7:1;
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
          UINT8 b0:1;
          UINT8 b1:1;
          UINT8 b2:1;
          UINT8 b3:1;
          UINT8 b4:1;
          UINT8 b5:1;
          UINT8 b6:1;
          UINT8 b7:1;
          UINT8 b8:1;
          UINT8 b9:1;
          UINT8 b10:1;
          UINT8 b11:1;
          UINT8 b12:1;
          UINT8 b13:1;
          UINT8 b14:1;
          UINT8 b15:1;
    } bits;
} UINT16_VAL, UINT16_BITS;
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
          UINT8 b0:1;
          UINT8 b1:1;
          UINT8 b2:1;
          UINT8 b3:1;
          UINT8 b4:1;
          UINT8 b5:1;
          UINT8 b6:1;
          UINT8 b7:1;
          UINT8 b8:1;
          UINT8 b9:1;
          UINT8 b10:1;
          UINT8 b11:1;
          UINT8 b12:1;
          UINT8 b13:1;
          UINT8 b14:1;
          UINT8 b15:1;
          UINT8 b16:1;
          UINT8 b17:1;
          UINT8 b18:1;
          UINT8 b19:1;
          UINT8 b20:1;
          UINT8 b21:1;
          UINT8 b22:1;
          UINT8 b23:1;
          UINT8 b24:1;
          UINT8 b25:1;
          UINT8 b26:1;
          UINT8 b27:1;
          UINT8 b28:1;
          UINT8 b29:1;
          UINT8 b30:1;
          UINT8 b31:1;
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
          UINT8 b0:1;
          UINT8 b1:1;
          UINT8 b2:1;
          UINT8 b3:1;
          UINT8 b4:1;
          UINT8 b5:1;
          UINT8 b6:1;
          UINT8 b7:1;
          UINT8 b8:1;
          UINT8 b9:1;
          UINT8 b10:1;
          UINT8 b11:1;
          UINT8 b12:1;
          UINT8 b13:1;
          UINT8 b14:1;
          UINT8 b15:1;
          UINT8 b16:1;
          UINT8 b17:1;
          UINT8 b18:1;
          UINT8 b19:1;
          UINT8 b20:1;
          UINT8 b21:1;
          UINT8 b22:1;
          UINT8 b23:1;
          UINT8 b24:1;
          UINT8 b25:1;
          UINT8 b26:1;
          UINT8 b27:1;
          UINT8 b28:1;
          UINT8 b29:1;
          UINT8 b30:1;
          UINT8 b31:1;
          UINT8 b32:1;
          UINT8 b33:1;
          UINT8 b34:1;
          UINT8 b35:1;
          UINT8 b36:1;
          UINT8 b37:1;
          UINT8 b38:1;
          UINT8 b39:1;
          UINT8 b40:1;
          UINT8 b41:1;
          UINT8 b42:1;
          UINT8 b43:1;
          UINT8 b44:1;
          UINT8 b45:1;
          UINT8 b46:1;
          UINT8 b47:1;
          UINT8 b48:1;
          UINT8 b49:1;
          UINT8 b50:1;
          UINT8 b51:1;
          UINT8 b52:1;
          UINT8 b53:1;
          UINT8 b54:1;
          UINT8 b55:1;
          UINT8 b56:1;
          UINT8 b57:1;
          UINT8 b58:1;
          UINT8 b59:1;
          UINT8 b60:1;
          UINT8 b61:1;
          UINT8 b62:1;
          UINT8 b63:1;
    } bits;
} UINT64_VAL;





typedef void VOID;

typedef char CHAR8;
typedef unsigned char UCHAR8;

typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned long DWORD;


 
typedef unsigned long long QWORD;

typedef signed char CHAR;
typedef signed short int SHORT;
typedef signed long LONG;


 
typedef signed long long LONGLONG;

typedef union
{
    BYTE Val;
    struct
    {
          BYTE b0:1;
          BYTE b1:1;
          BYTE b2:1;
          BYTE b3:1;
          BYTE b4:1;
          BYTE b5:1;
          BYTE b6:1;
          BYTE b7:1;
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
          BYTE b0:1;
          BYTE b1:1;
          BYTE b2:1;
          BYTE b3:1;
          BYTE b4:1;
          BYTE b5:1;
          BYTE b6:1;
          BYTE b7:1;
          BYTE b8:1;
          BYTE b9:1;
          BYTE b10:1;
          BYTE b11:1;
          BYTE b12:1;
          BYTE b13:1;
          BYTE b14:1;
          BYTE b15:1;
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
          BYTE b0:1;
          BYTE b1:1;
          BYTE b2:1;
          BYTE b3:1;
          BYTE b4:1;
          BYTE b5:1;
          BYTE b6:1;
          BYTE b7:1;
          BYTE b8:1;
          BYTE b9:1;
          BYTE b10:1;
          BYTE b11:1;
          BYTE b12:1;
          BYTE b13:1;
          BYTE b14:1;
          BYTE b15:1;
          BYTE b16:1;
          BYTE b17:1;
          BYTE b18:1;
          BYTE b19:1;
          BYTE b20:1;
          BYTE b21:1;
          BYTE b22:1;
          BYTE b23:1;
          BYTE b24:1;
          BYTE b25:1;
          BYTE b26:1;
          BYTE b27:1;
          BYTE b28:1;
          BYTE b29:1;
          BYTE b30:1;
          BYTE b31:1;
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
          BYTE b0:1;
          BYTE b1:1;
          BYTE b2:1;
          BYTE b3:1;
          BYTE b4:1;
          BYTE b5:1;
          BYTE b6:1;
          BYTE b7:1;
          BYTE b8:1;
          BYTE b9:1;
          BYTE b10:1;
          BYTE b11:1;
          BYTE b12:1;
          BYTE b13:1;
          BYTE b14:1;
          BYTE b15:1;
          BYTE b16:1;
          BYTE b17:1;
          BYTE b18:1;
          BYTE b19:1;
          BYTE b20:1;
          BYTE b21:1;
          BYTE b22:1;
          BYTE b23:1;
          BYTE b24:1;
          BYTE b25:1;
          BYTE b26:1;
          BYTE b27:1;
          BYTE b28:1;
          BYTE b29:1;
          BYTE b30:1;
          BYTE b31:1;
          BYTE b32:1;
          BYTE b33:1;
          BYTE b34:1;
          BYTE b35:1;
          BYTE b36:1;
          BYTE b37:1;
          BYTE b38:1;
          BYTE b39:1;
          BYTE b40:1;
          BYTE b41:1;
          BYTE b42:1;
          BYTE b43:1;
          BYTE b44:1;
          BYTE b45:1;
          BYTE b46:1;
          BYTE b47:1;
          BYTE b48:1;
          BYTE b49:1;
          BYTE b50:1;
          BYTE b51:1;
          BYTE b52:1;
          BYTE b53:1;
          BYTE b54:1;
          BYTE b55:1;
          BYTE b56:1;
          BYTE b57:1;
          BYTE b58:1;
          BYTE b59:1;
          BYTE b60:1;
          BYTE b61:1;
          BYTE b62:1;
          BYTE b63:1;
    } bits;
} QWORD_VAL;

void BOARD_Init();
void BOARD_End();







unsigned int BOARD_GetPBClock();

void Roach_Init(void);
char Roach_LeftMtrSpeed(char newSpeed);
char Roach_RightMtrSpeed(char newSpeed);







unsigned int Roach_LightLevel(void);







unsigned int Roach_BatteryVoltage(void);







unsigned char Roach_ReadFrontLeftBumper(void);
unsigned char Roach_ReadFrontRightBumper(void);







unsigned char Roach_ReadRearLeftBumper(void);







unsigned char Roach_ReadRearRightBumper(void);







unsigned char Roach_ReadBumpers(void);
char Roach_LEDSSet(uint16_t pattern);





uint16_t Roach_LEDSGet(void);







char Roach_BarGraph(uint8_t Number);
uint8_t TemplateCheckBattery(void);

uint8_t TestIfDark(void);

uint8_t TestIfLight(void);

uint8_t TestBumpers(void);





typedef double _Double;











typedef int ssize_t;
typedef long long off_t;
typedef struct _IO_FILE FILE;
typedef union _G_fpos64_t {
 char __opaque[16];
 double __align;
} fpos_t;






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


int scanf(const char *restrict, ...);
int fscanf(FILE *restrict, const char *restrict, ...);
int sscanf(const char *restrict, const char *restrict, ...);

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
uint8_t PostTemplateFSM(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}
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
