#include <stdio.h>
#include <graphics.h>


void setFont() {
	LOGFONT f; //�������
	gettextstyle(&f); //��ȡ��ǰ������
	f.lfHeight = 12; //����ĸ߶�
	f.lfWeight = 0;  //����Ŀ��
	strcpy(f.lfFaceName, "����");
	f.lfQuality = ANTIALIASED_QUALITY;//�����
	settextstyle(&f);
}

int main(void) {
	char str[256];
	printf("������Ҫ˵�Ļ�:");
	scanf_s("%s", str, sizeof(str));  //�����ַ���


	initgraph(400, 50); //��������

	IMAGE img; // ͼƬ����
	//����ͼƬ���ڴ�
	loadimage(&img, "m1.png");
	int width = img.getwidth();  //��ȡͼƬ���
	int height = img.getheight(); // ��ȡͼƬ�߶�

	
	// ��Ҫ�Ѻ����ַ�����ɶ�����ַ���
	//  "���"=> "��"  "��"
	//�����3��char  û��һ������
	int count = strlen(str) / 2;
	char **data = (char**)malloc(sizeof(char*) * count);
	for (int i = 0; i < count; i++)
	{
		data[i] = (char*)malloc(sizeof(char) * 3);
		strncpy(data[i], &str[i * 2], 2);
		data[i][2] = 0;
	}

	//��̬�ڴ����
	int* pix = (int*)malloc(sizeof(int) * width * height);
	if (pix == NULL) {
		printf("�ڴ����ʧ�ܣ� \n");
		return 1;
	}

	SetWorkingImage(&img);// ����ͼƬ�����Ĺ�����
	int k = 0;
	//ѭ��ȡ����
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			pix[k++] = getpixel(j, //ˮƽ����
							i);   //��ֱ����
		}
	}

	//������    ����һ�Ŵ�ͼƬ����
	SetWorkingImage();  //�ָ�Ĭ�Ϲ�����

	IMAGE imgDest;  // Ŀ��ͼƬ
	imgDest.Resize(width * 12, height * 12);  //����ͼƬ��С ÿ�����طŴ�12��12��
	SetWorkingImage(&imgDest);  // ���ù�������
	int index = 0;
	setFont();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{   
			//����׼�����Ƶ��ı���ɫ
			settextcolor(pix[i * width + j]);

			//��ָ��λ��д�ַ���
			outtextxy(j*12,i*12,"�Ұ���");
			index = (index + 1) % count;
		}
	}
	SetWorkingImage(); //�ָ�Ĭ�Ϲ�����
	//�ѻ������ͼƬ���浽love.jpg
	saveimage("love.jpg", &imgDest);
	//��ϵͳ�Ļ�ͼ�����
	system("mspaint.exe love.jpg");


	free(data); //�ͷ��ڴ�
	closegraph(); //�رմ���
	return 0;
}