#include <stdio.h>
#include <graphics.h>


void setFont() {
	LOGFONT f; //字体变量
	gettextstyle(&f); //获取当前的字体
	f.lfHeight = 12; //字体的高度
	f.lfWeight = 0;  //字体的宽度
	strcpy(f.lfFaceName, "黑体");
	f.lfQuality = ANTIALIASED_QUALITY;//抗锯齿
	settextstyle(&f);
}

int main(void) {
	char str[256];
	printf("请输入要说的话:");
	scanf_s("%s", str, sizeof(str));  //汉字字符串


	initgraph(400, 50); //创建窗口

	IMAGE img; // 图片变量
	//加载图片到内存
	loadimage(&img, "m1.png");
	int width = img.getwidth();  //获取图片宽度
	int height = img.getheight(); // 获取图片高度

	
	// 需要把汉字字符串变成多个子字符串
	//  "你好"=> "你"  "好"
	//下面拆3个char  没个一个汉字
	int count = strlen(str) / 2;
	char **data = (char**)malloc(sizeof(char*) * count);
	for (int i = 0; i < count; i++)
	{
		data[i] = (char*)malloc(sizeof(char) * 3);
		strncpy(data[i], &str[i * 2], 2);
		data[i][2] = 0;
	}

	//动态内存分配
	int* pix = (int*)malloc(sizeof(int) * width * height);
	if (pix == NULL) {
		printf("内存分配失败！ \n");
		return 1;
	}

	SetWorkingImage(&img);// 设置图片操作的工作区
	int k = 0;
	//循环取像素
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			pix[k++] = getpixel(j, //水平坐标
							i);   //垂直坐标
		}
	}

	//画汉字    画在一张大图片里面
	SetWorkingImage();  //恢复默认工作区

	IMAGE imgDest;  // 目标图片
	imgDest.Resize(width * 12, height * 12);  //设置图片大小 每个像素放大12行12列
	SetWorkingImage(&imgDest);  // 设置工作区域
	int index = 0;
	setFont();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{   
			//设置准备绘制的文本颜色
			settextcolor(pix[i * width + j]);

			//在指定位置写字符串
			outtextxy(j*12,i*12,"我爱你");
			index = (index + 1) % count;
		}
	}
	SetWorkingImage(); //恢复默认工作区
	//把绘制完的图片保存到love.jpg
	saveimage("love.jpg", &imgDest);
	//用系统的画图软件打开
	system("mspaint.exe love.jpg");


	free(data); //释放内存
	closegraph(); //关闭窗口
	return 0;
}