#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;

int main(int argc, char** argv)
{
    //argc>=1
    //argv第一个内容为主程序地址
    //cout<<"argc="<<argc<<endl;
    //for(int i = 0;i<=argc;i++)
        //cout<<argv[i]<<endl;
    //int i = system("py");
    //cout<<i<<endl;
    /*
    for(int i = 1;i<argc;i++)
        ;
        */

    FILE *file;

    char ptr[1024] = {0};
    char cmd[1024] = {0}; 
    char out1[1024] = "connected to 127.0.0.1:58526\n",out2[1024] = "already connected to 127.0.0.1:58526\n";
    strcat(ptr, "adb connect \"127.0.0.1:58526\"");
    int flag =1;
    while(flag>0)
        if ((file = _popen(ptr, "r")) != NULL)
            //执行一次指令
            while (fgets(cmd, 1024, file) != NULL)
            {    //读一行输出
                cout << flag;
                //cout <<!strcmp(cmd,out1)<<!strcmp(cmd,out2)<<endl;
                if(!strcmp(cmd,out1)||!strcmp(cmd,out2))
                    flag = 0;
                else if(flag>=50)
                    flag = -1;
                else
                    flag++;
            }
    if (flag==-1)
        cout<<"Here"<<endl;
    _pclose(file);
    return 0;
}