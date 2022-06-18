#include<iostream>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
using namespace std;

int main(int argc, char** argv)
{
    FILE *file;
    SetConsoleOutputCP(CP_UTF8);
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
                cout <<"正在尝试第 "<<flag<<" 次建立ADB调试连接"<<endl;
                //cout <<!strcmp(cmd,out1)<<!strcmp(cmd,out2)<<endl;
                if(!strcmp(cmd,out1)||!strcmp(cmd,out2))
                    flag = 0;
                else if(flag>=10)
                    flag = -1;
                else
                    flag++;
            }
    if (flag==-1)
    {
        cout<<"连接建立失败,请检查WSA运行情况!"<<endl;
        cout<<"返回代码(-1):ADB连接被拒绝."<<endl;
    }
    else if(flag==0)
    {
        cout<<"连接成功,正在尝试安装……"<<endl;
        for(int i = 1;i<argc;i++)
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
        }
    }
    _pclose(file);
    return 0;
}