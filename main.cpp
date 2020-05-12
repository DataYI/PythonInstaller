#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <direct.h>


using namespace std;

void run(char* command) {
    bool status = system(command);
    if (status == false) {
        cout << "command subprocess is not launched\n" << endl;
    }
//    else if (WIFEXITED(status)) {
//        WIFSIGNALED
//    }
    return ;
}

void getCmdResult(const string& strCmd)//传参string格式命令，返回值string格式；
{


    char buf[10240] = { 0 };
    FILE* pf = NULL;
    if ((pf = _popen(strCmd.c_str(), "r")) == NULL)
    {
        return;
    }

    string strResult;
    while (fgets(buf, sizeof buf, pf))
    {
        strResult += buf;
    }

    _pclose(pf);

    unsigned int iSize = strResult.size();
    if (iSize > 0 && strResult[iSize - 1] == '\n')
    {
        strResult = strResult.substr(0, iSize - 1);
    }
    cout << strResult << endl;
    return;
}


//char* concatChar(char text1[], char text2[]) {
//    char buff[1024];
//    memset(buff, 0, sizeof(buff));
//    strcpy(buff, text1);
//    strcat(buff, text2);
//    return buff;
//}

const char* concatChar(string text1, string text2) {
    string temp = text1 + text2;
    return temp.c_str();
}


void pipSourceSetup() {
    // 在%appdata%新建pip目录
    char* appdataDir;
    appdataDir = getenv("APPDATA");
    string pip = "/piptest";
    const char* pipDir;
    pipDir = concatChar(string(appdataDir), pip);
    mkdir(pipDir);
    // 写入pip.ini文件
    fstream pipFile;
    pipFile.open(string(pipDir) + "./pip.ini", fstream::out);
    string text = "[global]\ntimeout = 60\nindex-url = http://pypi.douban.com/simple\ntrusted-host = pypi.douban.com\n";
    pipFile << text;
    pipFile.close();
    return;
}



int main() {
    //    system("ipconfig");
    //system("ipconfig");
    //cout << "hello" << endl;
    //system("pause");
    // 安装python
    getCmdResult(":/test.exe -o \"abc\" -s \"def\"");
    // 设置pip源
    pipSourceSetup();
    // pip安装包
    getCmdResult("pip install --user pillow");
    getCmdResult("pip install --user qrcode");
    getCmdResult("pip install --user pygame");
    return 0;
}
