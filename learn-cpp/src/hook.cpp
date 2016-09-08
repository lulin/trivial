
#include "hook.h"
// #include <map>

#ifdef GTEST
#include <gtest/gtest.h>
#endif

#ifdef GTEST_INCLUDE_GTEST_GTEST_H_
#ifdef OHMTEST
#include "OhmColor.hpp"
#include "gtestcolors.h"
#define HOOK_TRUE(v) CEXPECT_TRUE(v)
#else
#define HOOK_TRUE(v) EXPECT_TRUE(v)
#endif //OHMTEST
#else
#define HOOK_TRUE(v)
#endif //GTEST_INCLUDE_GTEST_GTEST_H_

using namespace std;

#ifdef WIN32
#include"Windows.h"

#define FLATJMPCODE_LENGTH 5
#define FLATJMPCMD_LENGTH  1
#define FLATJMPCMD         0xe9

//typedef unsigned char BYTE;
//typedef bool BOOL;
//typedef unsigned long DWORD;

//BYTE g_apiBackup[FLATJMPCODE_LENGTH + FLATJMPCMD_LENGTH];

BOOL set_hook(LPVOID ApiFun, LPVOID HookFun, uint8_t *bak = NULL)
{
    BOOL    IsSuccess = FALSE;
    DWORD   TempProtectVar;
    MEMORY_BASIC_INFORMATION MemInfo;

    VirtualQuery(ApiFun, &MemInfo, sizeof(MEMORY_BASIC_INFORMATION));

    if (VirtualProtect(MemInfo.BaseAddress, MemInfo.RegionSize,
        PAGE_EXECUTE_READWRITE, &MemInfo.Protect))
    {
        memcpy((void*)bak, (const void*)ApiFun, FLATJMPCODE_LENGTH + FLATJMPCMD_LENGTH);

        *(BYTE*)ApiFun = FLATJMPCMD;
        *(DWORD*)((BYTE*)ApiFun + FLATJMPCMD_LENGTH) = (DWORD)HookFun -
            (DWORD)ApiFun - FLATJMPCODE_LENGTH;

        VirtualProtect(MemInfo.BaseAddress, MemInfo.RegionSize,
            MemInfo.Protect, &TempProtectVar);

        IsSuccess = TRUE;
    }

    return IsSuccess;
}

BOOL un_hook(LPVOID ApiFun,uint8_t *bak)
{
    BOOL    IsSuccess = FALSE;
    DWORD   TempProtectVar;
    MEMORY_BASIC_INFORMATION MemInfo;

    VirtualQuery(ApiFun, &MemInfo, sizeof(MEMORY_BASIC_INFORMATION));

    if (VirtualProtect(MemInfo.BaseAddress, MemInfo.RegionSize,
        PAGE_EXECUTE_READWRITE, &MemInfo.Protect))
    {
        memcpy((void*)ApiFun, (const void*)bak, FLATJMPCODE_LENGTH + FLATJMPCMD_LENGTH);

        VirtualProtect(MemInfo.BaseAddress, MemInfo.RegionSize,
            MemInfo.Protect, &TempProtectVar);

        IsSuccess = TRUE;
    }

    return IsSuccess;
}

#else
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdint.h>
    #include <string.h>
    #include <sys/mman.h>
    #include <errno.h>
    #include <unistd.h>

    #define MACHINE_CODE_LEN 12
    void set_hook(void *to_mock_func, void *mock_func, uint8_t *bak = NULL)
    {
		uint8_t machine_code[] = {
                //movq $0x0, %rax, 8 Bype zeros are 64 bit immediate value
                0x48, 0xb8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
                //jmpq *%rax
                0xff, 0xe0
            };
			
        int pagesize = sysconf(_SC_PAGE_SIZE);
        if (pagesize == -1)
        {
            exit(errno);
        }

        uint8_t *mem = (uint8_t *) to_mock_func;
        void *p = (uint8_t*) (mem - ((uint64_t) mem % pagesize));
        if (mprotect(p, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC))
        {
            perror("mprotect error");
            exit(errno);
        }
        void *p1 = NULL;
        uint64_t s = pagesize - ((uint64_t) mem % pagesize);
        if(s < sizeof(machine_code))
        {
            p1 = (uint8_t*) (mem + s);
            if (mprotect(p1, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC))
            {
                perror("mprotect error");
                exit(errno);
            }
        }

        //Change immediate value to be the addr of mock
        if(NULL != bak)
        {
            memcpy(bak, mem, sizeof(machine_code));
        }
		
        memcpy(machine_code + 2, &mock_func, sizeof(void *));
        memcpy(mem, machine_code, sizeof(machine_code));

        if (mprotect(p, pagesize, PROT_EXEC))
        {
            perror("mprotect error");
            exit(errno);
        }
        if(p1)
        {
            if (mprotect(p1, pagesize, PROT_EXEC))
            {
                perror("mprotect error");
                exit(errno);
            }
        }
    }
	
	void un_hook(void *to_mock_func,uint8_t *bak)
    {
        uint8_t machine_code[] = {
                //movq $0x0, %rax 8 Bype zeros are 64 bit immediate value
                0x48, 0xb8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
                //jmpq *%rax
                0xff, 0xe0
            };

        int pagesize = sysconf(_SC_PAGE_SIZE);
        if (pagesize == -1)
        {
            exit(errno);
        }

        uint8_t *mem = (uint8_t *) to_mock_func;
        void *p = (uint8_t*) (mem - ((uint64_t) mem % pagesize));
        if (mprotect(p, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC))
        {
            perror("mprotect error");
            exit(errno);
        }
        void *p1 = NULL;
        uint64_t s = pagesize - ((uint64_t) mem % pagesize);
        if(s < sizeof(machine_code))
        {
            p1 = (uint8_t*) (mem + s);
            if (mprotect(p1, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC))
            {
                perror("mprotect error");
                exit(errno);
            }
        }

        //memcpy(machine_code + 2, &to_mock_func, sizeof(to_mock_func));
        memcpy(mem, bak, sizeof(machine_code));

        if (mprotect(p, pagesize, PROT_EXEC))
        {
            perror("mprotect error");
            exit(errno);
        }
        if(p1)
        {
            if (mprotect(p1, pagesize, PROT_EXEC))
            {
                perror("mprotect error");
                exit(errno);
            }
        }
    }
    


#endif

bool set_global_hook(void *to_mock_func, void *mock_func)
{
    set_hook(to_mock_func, mock_func);
    return true;
}

typedef struct
{
    void *to_mock_fun;
    uint8_t bak_machine_code[MACHINE_CODE_LEN];
}LOCAL_HOOK_BAK_STRU;


//std::set<void *,LOCAL_HOOK_BAK_STRU> gmpLocalHook;
#define MAX_LOCAL_HOOK_NUM 100
LOCAL_HOOK_BAK_STRU gLocalHook[MAX_LOCAL_HOOK_NUM];
uint32_t gulLocalHookNum = 0;
LOCAL_HOOK_BAK_STRU *getEmptyLocalHook()
{
    uint32_t ulLoop = 0;
    for(ulLoop = 0; ulLoop < MAX_LOCAL_HOOK_NUM; ulLoop++)
    {
        if(gLocalHook[ulLoop].to_mock_fun == NULL)
        {
            gulLocalHookNum++;
            return &gLocalHook[ulLoop];
        }
    }

    return NULL;
}
LOCAL_HOOK_BAK_STRU *findLocalHook(void *to_mock_func)
{
    uint32_t ulLoop = 0;
    for(ulLoop = 0; ulLoop < MAX_LOCAL_HOOK_NUM; ulLoop++)
    {
        if(gLocalHook[ulLoop].to_mock_fun == to_mock_func)
        {
            return &gLocalHook[ulLoop];
        }
    }
    return NULL;
}

void deleteLocalHook(void *to_mock_func)
{
    uint32_t ulLoop = 0;
    for(ulLoop = 0; ulLoop < MAX_LOCAL_HOOK_NUM; ulLoop++)
    {
        if(gLocalHook[ulLoop].to_mock_fun == to_mock_func)
        {
             gLocalHook[ulLoop].to_mock_fun = NULL;
             gulLocalHookNum--;
             return;
        }
    }
    return ;
}

void releaseLocalHook(LOCAL_HOOK_BAK_STRU * stru)
{
    stru->to_mock_fun = NULL;
    gulLocalHookNum--;
    return ;
}

int set_local_hook(void *to_mock_func, void *mock_func)
{    
    LOCAL_HOOK_BAK_STRU *tmp = findLocalHook(to_mock_func);

    if(tmp != NULL)
    {
        printf("This function had been hooked, please unhook it before!\n");
        HOOK_TRUE(0);
        return -1;
    }

    tmp = getEmptyLocalHook();

    if(NULL == tmp)
    {
        printf("LocalHook is full!\n");
        HOOK_TRUE(0);
        return -1;
    }
    tmp->to_mock_fun = to_mock_func;
    
    set_hook(to_mock_func, mock_func, tmp->bak_machine_code);

    return tmp-gLocalHook;
}
bool un_local_hook(void *to_mock_func)
{
    LOCAL_HOOK_BAK_STRU *tmp = findLocalHook(to_mock_func);

    if(tmp == NULL)
    {
        printf("find this function fail!\n");
        HOOK_TRUE(0);
        return false;
    }
    
    un_hook(to_mock_func, tmp->bak_machine_code);

    releaseLocalHook(tmp);

    return true;
}

void init_local_hook()
{
    memset(gLocalHook, 0, sizeof(gLocalHook));
    gulLocalHookNum = 0;
}

int check_local_hook()
{
    uint32_t ulLoop = 0;

    HOOK_TRUE(gulLocalHookNum == 0);
    if(gulLocalHookNum > 0)
    {
        printf("gulLocalHookNum:%u\n",gulLocalHookNum);
        for(ulLoop = 0; ulLoop < MAX_LOCAL_HOOK_NUM; ulLoop++)
        {
            if(gLocalHook[ulLoop].to_mock_fun != NULL)
            {
                 printf("local-hook[%d] is not empty!\n",ulLoop);
            }
        }
    }
    return gulLocalHookNum;
}


