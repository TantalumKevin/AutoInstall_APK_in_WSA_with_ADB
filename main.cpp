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
        //argc>=1
        //argv第一个内容为主程序地址
        if(argc-1)
            cout<<"已检测到 "<<argc-1<<" 个apk文件,安装启动中……请稍后"<<endl;
        else
            cout<<"未检测到apk文件,请检查输入"<<endl;
        char install[1024] = "adb install \"";
        for(int i = 1;i<argc;i++)
        {
            char install[1024] = "adb install \"";
            cout<<"正在安装第 "<<i<<" 个安装包: "<<endl<<argv[i]<<endl;
            strcat(install,argv[i]);
            strcat(install,"\"");
            strcpy(ptr,install);
            cout<<"正在安装中，请稍后……"<<endl;
            if ((file = _popen(ptr, "r")) != NULL)
            //执行一次指令
                while (fgets(cmd, 1024, file) != NULL)
                {    //读一行输出
                    if(!strcmp(cmd,"Performing Streamed Install\n"))
                        continue;
                    else if(!strcmp(cmd,"Success\n"))
                        cout<<"安装成功"<<endl;
                    else
                    {
                        cout<<cmd;
                        cout<<"安装时遇到问题"<<endl;
                    }
                }
        }
    }
    _pclose(file);
    system("pause");
    return 0;
}