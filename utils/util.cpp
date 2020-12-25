//
// Created by 周蜀杰 on 2020/12/25.
//
#include "util.h"

void sleepMS(int microseconds){
    this_thread::sleep_for(chrono::microseconds(microseconds));
}

double getTime() {
    return glfwGetTime();
}

int exec(const char *in, char *out) {
    // 通过管道把结果输出到内存
    FILE *pipe = popen(in, "r"); // 第一个参数是指令字符串，第二个参数是模式（r：读，w：写）
    // _popen函数用于执行一条指令并把结果输出到内存中的文件对象
    if (!pipe)
        return 0;  // 无输出，直接返回
    char buff[128] = {0};
    while (!feof(pipe))
        // 从文件中读取一行
        if (fgets(buff, 128, pipe))
            // 连接字符串
            strcat(out, buff);
    pclose(pipe);
    return 1;
}

bool endsWith(string str,string sub){
    return str.rfind(sub) == (str.length() - sub.length());
}

int getAnswer(char sig) {
	switch (sig) {
		case 'U':
			return 0;
		case 'D':
			return 1;
		case 'L':
			return 2;
		case 'R':
			return 3;
		case 'F':
			return 4;
		case 'B':
			return 5;
	}
	return -1;
}