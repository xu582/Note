/*
 * @Author: Kinoko 
 * @Date: 2021-12-26 17:25:09 
 * @Last Modified by: Kinoko
 * @Last Modified time: 2021-12-26 17:33:56
 */
#include <stdio.h>
#define NULL 0

typedef struct
{
    int status;
    void (* statusChange)(int );
}T_Device;

T_Device g_Device;

void addCallbackFunc(void (*pstatusChange)(int status)){
    g_Device.statusChange = pstatusChange;
}

void run(){
    g_Device.status = 10;
    if (g_Device.status == 10){
        if (g_Device.statusChange != NULL){
            g_Device.statusChange(g_Device.status);
        }
    }
}


// 用户代码
void callBack(int status){
    printf("callBack\n");
    printf("status = %d\n",status);
}

int main(){
    addCallbackFunc(callBack);
    run();
    return 0;
}