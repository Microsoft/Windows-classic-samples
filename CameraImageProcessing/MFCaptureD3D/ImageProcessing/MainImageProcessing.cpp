/*	�Ʀ�v���B�z�D�禡
	Develop by Jimmy HU <s103360021@gmail.com>
	This program is licensed under GNU General Public License v3.
*/

//-----include header files, �ޤJ���Y��-----
#include "MainImageProcessing.h"										//	�ޤJ���Y��MainImageProcessing.h

//-----funtion implementation, �Ƶ{����@-----
void MainImageProcessing(unsigned char* InputImage, unsigned int ImageSizeX, unsigned int ImageSizeY)
//	MainImageProcessing�Ƶ{��
{																		//	�i�JMainImageProcessing�Ƶ{��
	if (ImageSizeX == 0 || ImageSizeY == 0)
	{
		return;
	}
	BMP24RGBIMAGE RGBImage1;											//	�ŧiRGBImage1�Ω�BMP24RGB���A�Ϲ���ƳB�z
	RGBImage1.XSIZE = ImageSizeX;										//	�ǻ�XSIZE��T
	RGBImage1.YSIZE = ImageSizeY;										//	�ǻ�YSIZE��T
	RGBImage1.IMAGE_DATA = RGBQUADtoBMP24RGB((RGBQUAD*)InputImage, ImageSizeX, ImageSizeY);
	//	�ǻ��v�����

	//-----�ͦ��v���ɦW-----
	char* FileName = NULL;
	char* FileNameBMP = NULL;
	int Counter = 1;
	FileName = (char*)malloc(100 * sizeof(char));
	FileNameBMP = (char*)malloc(100 * sizeof(char));
	do
	{
		sprintf(FileName, "%s%d", "Output", Counter);
		sprintf(FileNameBMP, "%s%s", FileName, ".BMP");
		Counter = Counter + 1;
	} while (FileExistCheck(FileNameBMP));

	BmpWriteV1(ArrayToRAWImage(RGBImage1.IMAGE_DATA, RGBImage1.XSIZE, RGBImage1.YSIZE), RGBImage1.XSIZE, RGBImage1.YSIZE, FileName);
	//	�I�sBmpToGraylevel�N�v���ର�Ƕ���A�I�sArrayToRAWImage�Ƶ{���NAnalysisData�ഫ�^BMP�v����Ʈ榡��HBmpWrite�Ƶ{���g�JBMP��
	free((void*)RGBImage1.IMAGE_DATA);
	RGBImage1.IMAGE_DATA = NULL;
	free((void*)FileName);
	FileName = NULL;
	free((void*)FileNameBMP);
	FileNameBMP = NULL;
	return;																//	����MainImageProcessing�Ƶ{��
}																		//	����MainImageProcessing�Ƶ{��

//----BMP���ɤj�p(Byte)Ū���Ƶ{��----
unsigned long BmpReadFilesize(const char *filename, const bool FilenameExtension)
//	BmpReadFilesize�Ƶ{��
{																		//	�i�JBMP���ɤj�p(Byte)Ū���Ƶ{��
	//***�ˬd�Ƶ{���ǤJ�ɦW***
	if(filename == NULL)												//	�Y��Jfilename��NULL
	{																	//	�i�Jif�ԭz
		printf("�ɮ׸��|��J��NULL\n");									//	���"�ɮ׸��|��J��NULL"�ô���
		return 0;														//	�^�Ǽƭ�0�A�õ����Ƶ{��
	}																	//	����if�ԭz
	//***�Ѧ�FilenameExtension�ܼƱ����ɦW�B�z�覡***
	char fname_bmp[MAX_PATH];											//	�ŧi�ɮצW��fname_bmp�}�C�ܼ�(�̦hMAX_PATH�Ӧr��) 
	if(FilenameExtension == false)										//	�Y��J�Ѽ�fname_bmp������ɦW
	{																	//	�i�Jif�ԭz
		sprintf(fname_bmp, "%s.bmp", filename);							//	���ͧ����ɮ׸��|�æs���fname_bmp�}�C
	}																	//	����if�ԭz
	else																//	�Y��J�Ѽ�fname_bmp�w�]�t���ɦW
	{																	//	�i�Jelse�ԭz
		strcpy(fname_bmp,filename);										//	������J�ɦW���|
	}																	//	����else�ԭz
	printf("���bŪ���U�C�ɮפj�p(Byte)�G%s\n",fname_bmp);				//	��ܵ{�����檬�A
	FILE *fp;															//	�ŧi�ɮ׫���fp�ϰ��ܼ�
	fp = fopen(fname_bmp, "rb");										//	�Hrb(�G�i��Ū��)�Ҧ��}���ɮ�
	if (fp==NULL)														//	�Y�}���ɮץ��� 
	{																	//	�i�Jif�ԭz 
		printf("Ū���ɮץ��ѡI\n");										//	��ܿ��~�T�� 
		return -1;														//	�Ǧ^-1�A�õ����Ƶ{�� 
	}																	//	����if�ԭz	 
	unsigned char header[54]; 											//	�ŧi���Y�]�wheader�}�C 
	fread(header, sizeof(unsigned char), 54, fp);						//	Ū�����Y�]�w
	unsigned long BmpRead_file_size;									//	�ŧiŪ��BMP�Ϥ��ɮפj�p(Byte)�ܼơA���A��unsigned long 
	BmpRead_file_size= header[2] + (header[3] << 8) + ( header[4] << 16) + ( header[5] << 24);
	//	�p���JBMP�Ϥ��ɮפj�p(Byte�A�줸��) 
	fclose(fp);															//	�����ɮ�
	return BmpRead_file_size;											//	�N�p��X�ɮפj�p�ƭ�(Byte)�Ǧ^ 
}																		//	����BMP���ɤj�p(Byte)Ū���Ƶ{�� 
//----BMP����xsize(�e��)Ū���Ƶ{��----
unsigned long BmpReadXSize(const char *filename, const bool FilenameExtension)
//	BMP����xsize(�e��)Ū���Ƶ{��
{																		//	�i�JBMP����xsize(�e��)Ū���Ƶ{��
	char fname_bmp[MAX_PATH];											//	�ŧi�ɮצW��fname_bmp�}�C�ܼ�(�̦hMAX_PATH�Ӧr��) 
	if(FilenameExtension == false)										//	�Y��J�Ѽ�fname_bmp������ɦW
	{																	//	�i�Jif�ԭz
		sprintf(fname_bmp, "%s.bmp", filename);							//	���ͧ����ɮ׸��|�æs���fname_bmp�}�C
	}																	//	����if�ԭz
	else																//	�Y��J�Ѽ�fname_bmp�w�]�t���ɦW
	{																	//	�i�Jelse�ԭz
		strcpy(fname_bmp,filename);										//	������J�ɦW���|
	}																	//	����else�ԭz
	printf("���bŪ���U�C�ɮ�xsize(�e��)�G%s\n",fname_bmp);				//	��ܵ{�����檬�A
	FILE *fp;															//	�ŧi�ɮ׫���fp�ϰ��ܼ�
	fp = fopen(fname_bmp, "rb");										//	�Hrb(�G�i��Ū��)�Ҧ��}���ɮ�
	if (fp==NULL)														//	�Y�}���ɮץ��� 
	{																	//	�i�Jif�ԭz 
		printf("Ū���ɮץ��ѡI\n");										//	��ܿ��~�T�� 
		return -1;														//	�Ǧ^-1�A�õ����Ƶ{�� 
	}																	//	����if�ԭz	 
	unsigned char header[54]; 											//	�ŧi���Y�]�wheader�}�C 
	fread(header, sizeof(unsigned char), 54, fp);						//	Ū�����Y�]�w
	unsigned long BmpReadXSize;											//	�ŧiŪ��BMP�Ϥ��ɮת�x(�e��)�j�p(����)�ܼơA���A��unsigned long 
	BmpReadXSize= header[18] + (header[19] << 8) + ( header[20] << 16) + ( header[21] << 24);
	//	�p���JBMP�Ϥ��ɮ�x(�e��)�j�p(����) 
	fclose(fp);															//	�����ɮ�
	return BmpReadXSize;												//	�N�p��XBMP�Ϥ��ɮ�x(�e��)�j�p(����)�ƭȶǦ^ 
}																		//	����BMP����xsize(�e��)Ū���Ƶ{�� 

//----BMP����ysize(����)Ū���Ƶ{��----
unsigned long BmpReadYSize(const char *filename, const bool FilenameExtension)
//	BMP����ysize(����)Ū���Ƶ{��
{																		//	�i�JBMP����ysize(����)Ū���Ƶ{��
	char fname_bmp[MAX_PATH];											//	�ŧi�ɮצW��fname_bmp�}�C�ܼ�(�̦hMAX_PATH�Ӧr��) 
	if(FilenameExtension == false)										//	�Y��J�Ѽ�fname_bmp������ɦW
	{																	//	�i�Jif�ԭz
		sprintf(fname_bmp, "%s.bmp", filename);							//	���ͧ����ɮ׸��|�æs���fname_bmp�}�C
	}																	//	����if�ԭz
	else																//	�Y��J�Ѽ�fname_bmp�w�]�t���ɦW
	{																	//	�i�Jelse�ԭz
		strcpy(fname_bmp,filename);										//	������J�ɦW���|
	}																	//	����else�ԭz
	printf("���bŪ���U�C�ɮ�ysize(����)�G%s\n",fname_bmp);				//	��ܵ{�����檬�A
	FILE *fp;															//	�ŧi�ɮ׫���fp�ϰ��ܼ�
	fp = fopen(fname_bmp, "rb");										//	�Hrb(�G�i��Ū��)�Ҧ��}���ɮ�
	if (fp==NULL)														//	�Y�}���ɮץ��� 
	{																	//	�i�Jif�ԭz 
		printf("Ū���ɮץ��ѡI\n");										//	��ܿ��~�T�� 
		return -1;														//	�Ǧ^-1�A�õ����Ƶ{�� 
	}																	//	����if�ԭz	 
	unsigned char header[54]; 											//	�ŧi���Y�]�wheader�}�C 
	fread(header, sizeof(unsigned char), 54, fp);						//	Ū�����Y�]�w
	unsigned long BmpReadYSize;											//	�ŧiŪ��BMP�Ϥ��ɮת�y(����)�j�p(����)�ܼơA���A��unsigned long 
	BmpReadYSize= header[22] + (header[23] << 8) + ( header[24] << 16) + ( header[25] << 24);
	//	�p���JBMP�Ϥ��ɮ�y(����)�j�p(����) 
	fclose(fp);															//	�����ɮ�
	return BmpReadYSize;												//	�N�p��XBMP�Ϥ��ɮ�y(����)�j�p(����)�ƭȶǦ^ 
}																		//	����BMP����ysize(����)Ū���Ƶ{�� 
//----BMP����Ū���Ƶ{��---- 
char BmpRead(unsigned char *image,const int xsize,const int ysize, const char *filename, const bool FilenameExtension)
{																		//	�i�JBMP����Ū���Ƶ{��
	char fname_bmp[MAX_PATH];											//	�ŧi�ɮצW��fname_bmp�}�C�ܼ�(�̦hMAX_PATH�Ӧr��) 
	if(FilenameExtension == false)										//	�Y��J�Ѽ�fname_bmp������ɦW
	{																	//	�i�Jif�ԭz
		sprintf(fname_bmp, "%s.bmp", filename);							//	���ͧ����ɮ׸��|�æs���fname_bmp�}�C
	}																	//	����if�ԭz
	else																//	�Y��J�Ѽ�fname_bmp�w�]�t���ɦW
	{																	//	�i�Jelse�ԭz
		strcpy(fname_bmp,filename);										//	������J�ɦW���|
	}																	//	����else�ԭz
	unsigned char FillingByte;											//	�ŧi��R�줸���ܼ�
	FillingByte = BmpFillingByteCalc(xsize);							//	�I�sBmpFillingByteCalc�Ƶ{���p���R���줸�ռƶq
	printf("���bŪ���ɮסG%s\n",fname_bmp);								//	��ܵ{�����檬�A
	FILE *fp;															//	�ŧi�ɮ׫���fp�ϰ��ܼ�
	fp = fopen(fname_bmp, "rb");										//	�Hrb(�G�i��Ū��)�Ҧ��}���ɮ�
	if (fp==NULL)														//	�Y�}���ɮץ��� 
	{																	//	�i�Jif�ԭz 
		printf("Ū���ɮץ��ѡI\n");										//	��ܿ��~�T�� 
		return -1;														//	�Ǧ^-1�A�õ����Ƶ{�� 
	}																	//	����if�ԭz	 
	unsigned char header[54]; 											//	�ŧi���Y�]�wheader�}�C 
	fread(header, sizeof(unsigned char), 54, fp);						//	Ū�����Y�]�w
	fread(image, sizeof(unsigned char), (size_t)(long)(xsize * 3 + FillingByte)*ysize, fp);
	//	Ū�����ɸ�� 
	fclose(fp);															//	�����ɮ� 
	return 0;															//	�Ǧ^0�õ����Ƶ{�� 
}																		//	����BMP����Ū���Ƶ{��
BMPIMAGE BmpFileRead(const char *filename, const bool FilenameExtension)
//	BmpFileRead�Ƶ{��
{																		//	�i�JBmpFileRead�Ƶ{��
	BMPIMAGE OutputData;												//	�ŧi��X��ƪŶ�
	strcpy(OutputData.FILENAME, "");									//	��l��OutputData
	OutputData.XSIZE = 0;												//	��l��OutputData
	OutputData.YSIZE = 0;												//	��l��OutputData
	OutputData.IMAGE_DATA = NULL;										//	��l��OutputData
	//***�ˬd�Ƶ{���ǤJ�ɦW***
	if(filename == NULL)												//	�Y��Jfilename��NULL
	{																	//	�i�Jif�ԭz
		printf("�ɮ׸��|��J��NULL\n");									//	���"�ɮ׸��|��J��NULL"�ô���
		return OutputData;												//	�^��OutputData�A�õ����Ƶ{��
	}																	//	����if�ԭz
	//***���ɦW���***
	char fname_bmp[MAX_PATH];											//	�ŧi�ɮצW��fname_bmp�}�C�ܼ�(�̦hMAX_PATH�Ӧr��) 
	if(FilenameExtension == false)										//	�Y��J�Ѽ�fname_bmp������ɦW
	{																	//	�i�Jif�ԭz
		sprintf(fname_bmp, "%s.bmp", filename);							//	���ͧ����ɮ׸��|�æs���fname_bmp�}�C
	}																	//	����if�ԭz
	else																//	�Y��J�Ѽ�fname_bmp�w�]�t���ɦW
	{																	//	�i�Jelse�ԭz
		strcpy(fname_bmp,filename);										//	������J�ɦW���|
	}																	//	����else�ԭz
	//***�T�{�ɮצs�b�ΥiŪ��***
	if (FileExistCheck(fname_bmp) == false)								//	�Y�ɮפ��s�b 
	{																	//	�i�Jif�ԭz 
		printf("�ɮ�%s���s�b�I\n",fname_bmp);							//	��ܿ��~�T�� 
		return OutputData;												//	�^��OutputData�A�õ����Ƶ{��
	}																	//	����if�ԭz	 
	if (FileReadPermissionCheck(fname_bmp) == false)					//	�Y�ɮפ��iŪ��
	{																	//	�i�Jif�ԭz 
		printf("Ū���ɮ׿��~�I\n");										//	��ܿ��~�T��
		return OutputData;												//	�^��OutputData�A�õ����Ƶ{��
	}																	//	����if�ԭz
	//***��J���ɸ�T��OutputData***
	strcpy(OutputData.FILENAME, fname_bmp);								//	��J�ɮ׸��|(�t���ɦW)
	OutputData.XSIZE = (unsigned int)BmpReadXSize(OutputData.FILENAME,true);
	//	Ū����JBMP���ɼe��(���|�w�]�t���ɦW) 
	OutputData.YSIZE = (unsigned int)BmpReadYSize(OutputData.FILENAME,true);
	//	Ū����JBMP���ɰ���(���|�w�]�t���ɦW) 
	if( (OutputData.XSIZE == -1) || (OutputData.YSIZE == -1) )			//	�YXSIZE��YSIZE��-1(�N��Ū���ɮץ���)	
	{																	//	�i�Jif�ԭz 
		printf("Ū�����ɤj�p��T����!");								//	���"Ū�����ɤj�p��T����!"
		return OutputData;												//	�^��OutputData�A�õ����Ƶ{��
	}																	//	����if�ԭz
	else																//	�YXSIZE�PYSIZE�Ҥ���-1(���`Ū���ɮ�)
	{																	//	�i�Jelse�ԭz 
		printf("��J���ɼe�סG%d\n",OutputData.XSIZE);					//	��ܿ�J���ɼe�׼ƭ� 
		printf("��J���ɰ��סG%d\n",OutputData.YSIZE);					//	��ܿ�J���ɰ��׼ƭ� 
		printf("��J�v���j�p(Byte)�G%d\n",(size_t)OutputData.XSIZE * OutputData.YSIZE * 3);
		//	��ܿ�J�v���j�p�ƭ�(Byte) 
		OutputData.FILLINGBYTE = BmpFillingByteCalc(OutputData.XSIZE);	//	�I�sBmpFillingByteCalc�Ƶ{���p���R���줸�ռƶq
		OutputData.IMAGE_DATA = (unsigned char*)malloc((OutputData.XSIZE * 3 + OutputData.FILLINGBYTE) * OutputData.YSIZE * sizeof(unsigned char));
		//	�p��ëإ߼v���j�p�Ŷ� 
		if (OutputData.IMAGE_DATA == NULL) 								//	�Y�إ߼v���Ŷ����� 
		{																//	�i�Jif�ԭz 
			printf("�O������t���~!");									//	���"�O������t���~!" 
			return OutputData;											//	�^��OutputData�A�õ����Ƶ{��
		}																//	����if�ԭz 
		else															//	�Y���o�Ϳ��~ 
		{																//	�i�Jelse�ԭz 
			int loop_num = 0;											//	�ŧi�ϰ��ܼ�loop_num�Ѱj��ϥ� 
			for(loop_num=0;loop_num<((OutputData.XSIZE * 3 + OutputData.FILLINGBYTE) * OutputData.YSIZE);loop_num++)
			//	�Hfor�j���l�ƨC�ӹ��� 
			{															//	�i�Jfor�j�� 
				OutputData.IMAGE_DATA[loop_num]=255;						//	��J�w�]������m�ƭ� 
			}															//	����for�j�� 
			BmpRead(OutputData.IMAGE_DATA, OutputData.XSIZE, OutputData.YSIZE, OutputData.FILENAME,true);
			//	Ū�����ɸ��
		}																//	����else�ԭz
	}																	//	����else�ԭz
	return OutputData;													//	�^��Ū�����
}																		//	����BmpFileRead�Ƶ{��
//----BMP���ɼg�J�Ƶ{��---- 
/*	BmpWriteV1�Ƶ{���{������BMP���ɼg�J�Aheader�}�C��BMP���ɤ����Y 
 *
 *
 */
 
int BmpWriteV1(const unsigned char *image,const int xsize,const int ysize,const char *filename) 
{																		//	�i�JBmpWriteV1(BMP���ɼg�J)�Ƶ{�� 
	unsigned char FillingByte;											//	�ŧi��R�줸���ܼ�(FillingByte)
	FillingByte = BmpFillingByteCalc(xsize);							//	�I�sBmpFillingByteCalc�Ƶ{���p���R���줸�ռƶq
	unsigned char header[54] = 											//	�ŧi���Y�]�wheader�}�C(�@54Bytes)
	{																	//	header�}�C��l�ȳ]�w 
	0x42, 0x4d, 0, 0, 0, 0, 0, 0, 0, 0,									//	header�}�C��l�ȳ]�w
	54, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0, 		//	header�}�C��l�ȳ]�w
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 		//	header�}�C��l�ȳ]�w
	0, 0, 0, 0															//	header�}�C��l�ȳ]�w
	};																	//	header�}�C��l�ȳ]�w
	unsigned long file_size = (long)xsize * (long)ysize * 3 + 54;		//	�ŧifile_size�ܼơA�]�w�ɮפj�p 
	unsigned long width, height;										//	�ŧiwidth�Pheight��unsigned long���A�ܼơA�Ω�p��Ϲ��ɮ׼e�סB����
	char fname_bmp[MAX_PATH];											//	�ŧi�ܼƥΥH�O����X�Ϥ��������ɦW(�̦hMAX_PATH�Ӧr��) 
	header[2] = (unsigned char)(file_size &0x000000ff);					//	�p�����Y��T(�Ϲ��ɮפj�p)
	header[3] = (file_size >> 8) & 0x000000ff;							//	�p�����Y��T(�Ϲ��ɮפj�p)
	header[4] = (file_size >> 16) & 0x000000ff;							//	�p�����Y��T(�Ϲ��ɮפj�p)
	header[5] = (file_size >> 24) & 0x000000ff;							//	�p�����Y��T(�Ϲ��ɮפj�p)
	
	width = xsize;														//	�N�Ϲ��e�׸�T��Jwidth�ܼ�
	header[18] = width & 0x000000ff;									//	�p�����Y��T(�Ϲ��e��)
	header[19] = (width >> 8) &0x000000ff;								//	�p�����Y��T(�Ϲ��e��)
	header[20] = (width >> 16) &0x000000ff;								//	�p�����Y��T(�Ϲ��e��)
	header[21] = (width >> 24) &0x000000ff;								//	�p�����Y��T(�Ϲ��e��)
	 
	height = ysize;														//	�N�Ϲ����׸�T��Jheight�ܼ�
	header[22] = height &0x000000ff;									//	�p�����Y��T(�Ϲ�����)
	header[23] = (height >> 8) &0x000000ff;								//	�p�����Y��T(�Ϲ�����)
	header[24] = (height >> 16) &0x000000ff;							//	�p�����Y��T(�Ϲ�����)
	header[25] = (height >> 24) &0x000000ff;							//	�p�����Y��T(�Ϲ�����)
	sprintf(fname_bmp, "%s.bmp", filename);								//	���͹��ɧ����ɦW���|
	FILE *fp;															//	�ŧi�ɮ׫���fp�ϰ��ܼơA�ΥH�O���g�J���ɸ��| 
	if (!(fp = fopen(fname_bmp, "wb"))) 								//	���եH�G�i��Ū�ɤ覡�}�ҹ��ɡA�Y�L�k���\�}��
	{																	//	�i�Jif�ԭz
		return -1;														//	�^��-1�A�õ����Ƶ{��
	}																	//	����if�ԭz
	
	fwrite(header, sizeof(unsigned char), 54, fp);						//	�g�JBMP�������Y��T(54Bytes)
	fwrite(image, sizeof(unsigned char), (size_t)(long)(xsize * 3 + FillingByte)*ysize, fp);
	//	�g�JBMP���ɼv�����
	fclose(fp);															//	�����ɮ׫���
	free((void*)image);
	image = NULL;
	return 0;															//	�Ǧ^0�õ����Ƶ{��
}																		//	����BmpWriteV1(BMP���ɼg�J)�Ƶ{��
int BmpWriteV2(const BMPIMAGE OutputFile)								//	BmpWriteV2�Ƶ{��
{																		//	�i�JBmpWriteV2�Ƶ{��
	return BmpWriteV1(OutputFile.IMAGE_DATA, OutputFile.XSIZE, OutputFile.YSIZE, OutputFile.FILENAME);
	//	�NOutputFile���c�ѪR���U���ѼƶǤJBmpWriteV1�Ƶ{��
}																		//	����BmpWriteV2�Ƶ{��
void ViewBMPImage(const char *filename)									//	ViewBMPImage�Ƶ{��
{																		//	�i�JViewBMPImage�Ƶ{��
	#ifdef _WIN32														//	�Y�sĶ���Ҭ�Windows�t��
		if(filename==NULL)												//	�Y�ǤJ��filename���Ь�NULL
		{																//	�i�Jif�ԭz
			return;														//	�����Ƶ{��
		}																//	����if�ԭz
		char fname_bmp[MAX_PATH];										//	�ŧi�ɮצW��fname_bmp�}�C�ܼ�(�̦hMAX_PATH�Ӧr��) 
		sprintf(fname_bmp, "%s%s.BMP",FILE_ROOT_PATH ,filename);		//	�إ߱��}�ҹ��ɤ������ɦW(�̦hMAX_PATH�Ӧr��)
		char RunCommand[MAX_PATH+100];									//	�ŧi����}�ҹ��ɫ��O�r���ܼ�
		sprintf(RunCommand, "%s%s","\"C:\\WINDOWS\\system32\\rundll32.exe\" C:\\WINDOWS\\system32\\shimgvw.dll,ImageView_Fullscreen ",fname_bmp);
		#ifdef DebugMode												//	�Y���w�q��DebugMode(�����Ҧ�)
			printf("�}�ҹ��ɫ��O�G%s\n",RunCommand);					//	��ܶ}�ҹ��ɫ��O�ô���
		#endif															//	����ifdef�ԭz
		system(RunCommand);												//	����system��ơA�}�ҹ���
	#endif																//	����ifdef�ԭz
	#ifdef linux														//	�Y�sĶ���Ҭ�Linux�t��
		if(filename==NULL)												//	�Y�ǤJ��filename���Ь�NULL
		{																//	�i�Jif�ԭz
			return;														//	�����Ƶ{��
		}																//	����if�ԭz
		char fname_bmp[MAX_PATH];										//	�ŧi�ɮצW��fname_bmp�}�C�ܼ�(�̦hMAX_PATH�Ӧr��) 
		sprintf(fname_bmp, "%s%s.BMP",FILE_ROOT_PATH ,filename);		//	�إ߱��}�ҹ��ɤ������ɦW(�̦hMAX_PATH�Ӧr��)
		char RunCommand[MAX_PATH+100];									//	�ŧi����}�ҹ��ɫ��O�r���ܼ�
		sprintf(RunCommand, "%s%s","eog ",fname_bmp);					//	�}�ҫ��w����
		#ifdef DebugMode												//	�Y���w�q��DebugMode(�����Ҧ�)
			printf("�}�ҹ��ɫ��O�G%s\n",RunCommand);					//	��ܶ}�ҹ��ɫ��O�ô���
		#endif															//	����ifdef�ԭz
		system(RunCommand);												//	����system��ơA�}�ҹ���
	#endif																//	����ifdef�ԭz
	
}																		//	����ViewBMPImage�Ƶ{��

BMP24RGB *InitialIMGArray(const int xsize, const int ysize)				//	InitialIMGArray�Ƶ{��
{																		//	�i�JInitialIMGArray�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData��BMP24RGB���Ы��A�ܼ�
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData(�G��)���аO����j�p
	if(OutputData == NULL)												//	�YOutput���ū���
	{																	//	�i�Jif�ԭz
		printf("�O������t���~!");										//	���"�O������t���~"
		return NULL;													//	�^��NULL�A�õ����Ƶ{��
	}																	//	����if�ԭz
	int LoopNumber1,LoopNumber2;										//	�ŧiLoopNumber1�PLoopNumber2�A�Ω�j��p��
	for(LoopNumber1 = 0;LoopNumber1<ysize;LoopNumber1++)				//	�Hfor�j��̧ǳB�z�Ϲ�����
	{																	//	�i�Jfor�j��
		for(LoopNumber2 = 0;LoopNumber2<xsize;LoopNumber2++)			//	�Hfor�j��̧ǳB�z�Ϲ�����
		{																//	�i�Jfor�j��
			OutputData[LoopNumber1*xsize + LoopNumber2].R = 0;			//	��JR�������
			OutputData[LoopNumber1*xsize + LoopNumber2].G = 0;			//	��JG�������
			OutputData[LoopNumber1*xsize + LoopNumber2].B = 0;			//	��JB�������
		}																//	����for�j��
	}																	//	����for�j��
	return OutputData;													//	�^�ǥͦ����G
}																		//	����InitialIMGArray�Ƶ{��

BMP24RGB *RGBQUADtoBMP24RGB(const RGBQUAD* InputRGBQUADImage, const int xsize, const int ysize)
//	RGBQUADtoBMP24RGB�Ƶ{��
{																		//	�i�JRGBQUADtoBMP24RGB�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData��BMP24RGB���Ы��A�ܼ�
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData(�G��)���аO����j�p
	if (OutputData == NULL)												//	�YOutput���ū���
	{																	//	�i�Jif�ԭz
		printf("�O������t���~!");										//	���"�O������t���~"
		return NULL;													//	�^��NULL�A�õ����Ƶ{��
	}																	//	����if�ԭz
	int LoopNumber1, LoopNumber2;										//	�ŧiLoopNumber1�PLoopNumber2�A�Ω�j��p��
	for (LoopNumber1 = 0; LoopNumber1<ysize; LoopNumber1++)				//	�Hfor�j��̧ǳB�z�Ϲ�����
	{																	//	�i�Jfor�j��
		for (LoopNumber2 = 0; LoopNumber2<xsize; LoopNumber2++)			//	�Hfor�j��̧ǳB�z�Ϲ�����
		{																//	�i�Jfor�j��
			OutputData[LoopNumber1*xsize + LoopNumber2].R = 			//	��JR�������
				InputRGBQUADImage[(ysize - LoopNumber1) * xsize + LoopNumber2].rgbRed;
			OutputData[LoopNumber1*xsize + LoopNumber2].G = 			//	��JG�������
				InputRGBQUADImage[(ysize - LoopNumber1) * xsize + LoopNumber2].rgbGreen;
			OutputData[LoopNumber1*xsize + LoopNumber2].B = 			//	��JB�������
				InputRGBQUADImage[(ysize - LoopNumber1) * xsize + LoopNumber2].rgbBlue;
		}																//	����for�j��
	}																	//	����for�j��
	return OutputData;													//	�^���ഫ���G
}																		//	����RGBQUADtoBMP24RGB�Ƶ{��

RGBQUAD* BMP24RGBtoRGBQUAD(const BMP24RGB* InputBMP24RGBImage, const int xsize, const int ysize)
{
	RGBQUAD *OutputData;												//	�ŧiOutputData��BMP24RGB���Ы��A�ܼ�
	OutputData = (RGBQUAD*)malloc(xsize * ysize * sizeof(RGBQUAD));		//	�t�mOutputData(�G��)���аO����j�p
	if (OutputData == NULL)												//	�YOutput���ū���
	{																	//	�i�Jif�ԭz
		printf("�O������t���~!");										//	���"�O������t���~"
		return NULL;													//	�^��NULL�A�õ����Ƶ{��
	}																	//	����if�ԭz
	int LoopNumber1, LoopNumber2;										//	�ŧiLoopNumber1�PLoopNumber2�A�Ω�j��p��
	for (LoopNumber1 = 0; LoopNumber1<ysize; LoopNumber1++)				//	�Hfor�j��̧ǳB�z�Ϲ�����
	{																	//	�i�Jfor�j��
		for (LoopNumber2 = 0; LoopNumber2<xsize; LoopNumber2++)			//	�Hfor�j��̧ǳB�z�Ϲ�����
		{																//	�i�Jfor�j��
			OutputData[(ysize - LoopNumber1) * xsize + LoopNumber2].rgbRed = 
				InputBMP24RGBImage[LoopNumber1*xsize + LoopNumber2].R;	//	��JR�������
			OutputData[(ysize - LoopNumber1) * xsize + LoopNumber2].rgbGreen = 
				InputBMP24RGBImage[LoopNumber1*xsize + LoopNumber2].G;	//	��JG�������
			OutputData[(ysize - LoopNumber1) * xsize + LoopNumber2].rgbBlue = 
				InputBMP24RGBImage[LoopNumber1*xsize + LoopNumber2].B;	//	��JB�������
		}																//	����for�j��
	}																	//	����for�j��
	return OutputData;													//	�^���ഫ���G
}

BMP24RGB *RAWImageToArray(const unsigned char *image, const int xsize, const int ysize)
//	BMP���ɸ�Ʀܰ}�C�ഫ�Ƶ{��
{																		//	�i�JBMP���ɸ�Ʀܰ}�C�ഫ�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData��BMP24RGB���Ы��A�ܼ�
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData(�G��)���аO����j�p
	if(OutputData == NULL)												//	�YOutput���ū���
	{																	//	�i�Jif�ԭz
		printf("�O������t���~!");										//	���"�O������t���~"
		return NULL;													//	�^��NULL�A�õ����Ƶ{��
	}																	//	����if�ԭz
	unsigned char FillingByte;											//	�ŧiFillingByte�ϰ��ܼ�
	FillingByte = BmpFillingByteCalc(xsize);							//	�I�sBmpFillingByteCalc�Ƶ{���p���R���줸�ռƶq
	int LoopNumber1,LoopNumber2;										//	�ŧiLoopNumber1�PLoopNumber2�A�Ω�j��p��
	for(LoopNumber1 = 0;LoopNumber1<ysize;LoopNumber1++)				//	�Hfor�j��̧ǳB�z�Ϲ�����
	{																	//	�i�Jfor�j��
		for(LoopNumber2 = 0;LoopNumber2<xsize;LoopNumber2++)			//	�Hfor�j��̧ǳB�z�Ϲ�����
		{																//	�i�Jfor�j��
			OutputData[LoopNumber1*xsize + LoopNumber2].R = 			//	��JR�������
			image[3*(LoopNumber1 * xsize + LoopNumber2) + LoopNumber1 * FillingByte + 2];
			OutputData[LoopNumber1*xsize + LoopNumber2].G = 			//	��JG�������
			image[3*(LoopNumber1 * xsize + LoopNumber2) + LoopNumber1 * FillingByte + 1];
			OutputData[LoopNumber1*xsize + LoopNumber2].B = 			//	��JB�������
			image[3*(LoopNumber1 * xsize + LoopNumber2) + LoopNumber1 * FillingByte + 0];
		}																//	����for�j��
	}																	//	����for�j��
	return OutputData;													//	�^���ഫ���G
}																		//	����BMP���ɸ�Ʀܰ}�C�ഫ�Ƶ{��

unsigned char *ArrayToRAWImage(const BMP24RGB* InputData,const int xsize,const int ysize)
//	ArrayToRAWImage�Ƶ{��
{																		//	�i�JArrayToRAWImage�Ƶ{��
	unsigned char FillingByte;											//	�ŧiFillingByte�ϰ��ܼ�
	FillingByte = BmpFillingByteCalc(xsize);							//	�I�sBmpFillingByteCalc�Ƶ{���p���R���줸�ռƶq
	unsigned char *OutputData;											//	�ŧiOutputData�O���ഫ�������
	OutputData = (unsigned char*)malloc((xsize * 3 + FillingByte) * ysize * sizeof(unsigned char));
	//	�t�mOutputData���аO����j�p
	if(OutputData == NULL)												//	�YOutput���ū���
	{																	//	�i�Jif�ԭz
		printf("�O������t���~!");										//	���"�O������t���~"
		return NULL;													//	�^��NULL�A�õ����Ƶ{��
	}																	//	����if�ԭz
	int LoopNumber1,LoopNumber2;										//	�ŧiLoopNumber1�PLoopNumber2�A�Ω�j��p��
	//***��l��OutputData���и��***
	for(LoopNumber1 = 0;LoopNumber1<ysize;LoopNumber1++)				//	�Hfor�j��̧Ǫ�l��OutputData���и�Ƭ�0
	{																	//	�i�Jfor�j��
		for(LoopNumber2 = 0;LoopNumber2<(xsize * 3 + FillingByte);LoopNumber2++)
		//	�Hfor�j��̧Ǫ�l��OutputData���и�Ƭ�0
		{																//	�i�Jfor�j��
			OutputData[LoopNumber1 * (xsize * 3 + FillingByte) + LoopNumber2] = 0;
		}																//	����for�j��
	}																	//	����for�j��
	//***��J�Ϲ���Ʀ�OutputData***
	for(LoopNumber1 = 0;LoopNumber1<ysize;LoopNumber1++)				//	�Hfor�j��̧ǳB�z�Ϲ�����
	{																	//	�i�Jfor�j��
		for(LoopNumber2 = 0;LoopNumber2<xsize;LoopNumber2++)			//	�Hfor�j��̧ǳB�z�Ϲ�����
		{																//	�i�Jfor�j��
			OutputData[3*(LoopNumber1 * xsize + LoopNumber2) + LoopNumber1 * FillingByte + 2]
			= InputData[LoopNumber1*xsize + LoopNumber2].R;				//	��JR�������
			OutputData[3*(LoopNumber1 * xsize + LoopNumber2) + LoopNumber1 * FillingByte + 1]
			= InputData[LoopNumber1*xsize + LoopNumber2].G;				//	��JG�������
			OutputData[3*(LoopNumber1 * xsize + LoopNumber2) + LoopNumber1 * FillingByte + 0]
			= InputData[LoopNumber1*xsize + LoopNumber2].B;				//	��JB�������
		}																//	����for�j��
	}																	//	����for�j��
	return OutputData;													//	�^���ഫ���G
}																		//	����ArrayToRAWImage�Ƶ{��

HSV *BMP24RGBToHSV(const BMP24RGB *InputData,const int xsize,const int ysize)
//	BMP24RGBToHSV�Ƶ{��
{																		//	�i�JBMP24RGBToHSV�Ƶ{��
	HSV *OutputData;													//	�ŧiOutputData��HSV���Ы��A�ܼ�
	OutputData = (HSV*)malloc(xsize * ysize * sizeof(HSV));				//	�t�mOutputData���аO����j�p
	if(OutputData == NULL)												//	�YOutput���ū���
	{																	//	�i�Jif�ԭz
		printf("�O������t���~!");										//	���"�O������t���~"
		return NULL;													//	�^��NULL�A�õ����Ƶ{��
	}																	//	����if�ԭz
	int LoopNumber1,LoopNumber2;										//	�ŧiLoopNumber1�PLoopNumber2�A�Ω�j��p��
	//***OutputData���Ъ�l��***
	for(LoopNumber1 = 0;LoopNumber1<ysize;LoopNumber1++)				//	�Hfor�j��̧��ഫ�Ϲ��������
	{																	//	�i�Jfor�j��
		for(LoopNumber2 = 0;LoopNumber2<xsize;LoopNumber2++)			//	�Hfor�j��̧��ഫ�Ϲ��������
		{																//	�i�Jfor�j��
			OutputData[LoopNumber1 * xsize + LoopNumber2].H = 0;		//	��l��OutputData�����ܼ�
			OutputData[LoopNumber1 * xsize + LoopNumber2].S = 0;		//	��l��OutputData�����ܼ�
			OutputData[LoopNumber1 * xsize + LoopNumber2].V = 0;		//	��l��OutputData�����ܼ�
		}																//	����for�j��
	}																	//	����for�j��
	for(LoopNumber1 = 0;LoopNumber1<ysize;LoopNumber1++)				//	�Hfor�j��̧��ഫ�Ϲ��������
	{																	//	�i�Jfor�j��
		for(LoopNumber2 = 0;LoopNumber2<xsize;LoopNumber2++)			//	�Hfor�j��̧��ഫ�Ϲ��������
		{																//	�i�Jfor�j��
			unsigned char Red,Green,Blue;								//	�ŧiRed,Green,Blue�ܼơA�O���������
			Red = InputData[LoopNumber1 * xsize + LoopNumber2].R;		//	��JRed���
			Green = InputData[LoopNumber1 * xsize + LoopNumber2].G;		//	��JGreen���
			Blue = InputData[LoopNumber1 * xsize + LoopNumber2].B;		//	��JBlue���
			//***�Ƨ�RGB�������***
			unsigned char *SortArray;									//	�ŧiSortArray��unsigned char���A���СA�ѹ�����RGB�ƧǨϥ�
			SortArray = (unsigned char *)malloc( 3 * sizeof(unsigned char) );
			SortArray[0] = Red;											//	�N����R��ƶ�JSortArray
			SortArray[1] = Green;										//	�N����G��ƶ�JSortArray
			SortArray[2] = Blue;										//	�N����B��ƶ�JSortArray
			//printf("%d,%d,%d\n",SortArray[0],SortArray[1],SortArray[2]);//	���Ū�����
			SortArray = UCharBubbleSort(SortArray, 3, 0);				//	�I�sUCharBubbleSort�ƧǰƵ{���i��Ƨ�(�Ѥp�ܤj)
			//printf("%d,%d,%d\n",SortArray[0],SortArray[1],SortArray[2]);//	��ܱƧǫ���
			unsigned char Max,Mid,Min;									//	�ŧiMax,Mid,Min�ܼơA�O���Ƨǧ����������
			Max = SortArray[2];											//	��JMax�ƭ�
			Mid = SortArray[1];											//	��JMid�ƭ�
			Min = SortArray[0];											//	��JMin�ƭ�
			//system("pause");
			//***�p��H***
			long double H1 = acos(0.5 * ((Red - Green) + (Red - Blue)) /
							 sqrt(((pow((Red - Green), 2.0)) + 
							 (Red - Blue) * (Green - Blue)))) * (180.0 / M_PI);
			if( Max == Min )											//	�YMax=Min
			{															//	�i�Jif�ԭz
				OutputData[LoopNumber1 * xsize + LoopNumber2].H = 0.0;	//	�]�wH=0
			}															//	����if�ԭz
			else if(Blue <= Green)										//	�YBlue(�Ŧ⦨��)�p�󵥩�Green(��⦨��)
			{															//	�i�Jelse if�ԭz
				OutputData[LoopNumber1 * xsize + LoopNumber2].H = H1;
			}															//	����else if�ԭz
			else														//	�YMax������Min�BBlue�j��Green
			{															//	�i�Jelse�ԭz
				OutputData[LoopNumber1 * xsize + LoopNumber2].H = 360.0-H1;
			}															//	����else�ԭz
			//***�p��S***
			if(Max == 0)												//	�YMax=0
			{															//	�i�Jif�ԭz
				OutputData[LoopNumber1 * xsize + LoopNumber2].S = 0.0;	//	��JS�ƭ�
			}															//	����if�ԭz
			else														//	�YMax����0
			{															//	�i�Jelse�ԭz
				OutputData[LoopNumber1 * xsize + LoopNumber2].S =
				1.0 - ( (long double)Min / (long double)Max);			//	�p��S�ƭ�
			}															//	����else�ԭz
			//***�p��V***
			OutputData[LoopNumber1 * xsize + LoopNumber2].V =
			SortArray[2];												//	�p��V�ƭ�
			free(SortArray);											//	����SortArray�Ŷ�
			
			#ifdef DebugMode											//	�Y���w�q��DebugMode(�����Ҧ�)
				printf("\n�ഫ���G�G\n��l����\t�ഫ�ṳ��\n");
				printf("R=%d\t\tHue=\t\t",InputData[LoopNumber1 * xsize + LoopNumber2].R);
				ShowLongDouble(OutputData[LoopNumber1 * xsize + LoopNumber2].H);
				printf("\nG=%d\t\tSaturation=\t",InputData[LoopNumber1 * xsize + LoopNumber2].G);
				ShowLongDouble(OutputData[LoopNumber1 * xsize + LoopNumber2].S);
				printf("\nB=%d\t\tValue=\t\t",InputData[LoopNumber1 * xsize + LoopNumber2].B);
				ShowLongDouble(OutputData[LoopNumber1 * xsize + LoopNumber2].V);
				printf("\n");
				system("pause");
			#endif														//	����ifdef�ԭz
		}																//	����for�j��
	}																	//	����for�j��
	return OutputData;													//	�^��OutputData�A�õ����Ƶ{��
}																		//	����BMP24RGBToHSV�Ƶ{��
BMP24RGB *HSVToBMP24RGB(const HSV *InputData,const int xsize,const int ysize)
//	HSVToBMP24RGB�Ƶ{��
{																		//	�i�JHSVToBMP24RGB�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData��HSV���Ы��A�ܼ�
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData���аO����j�p
	if(OutputData == NULL)												//	�YOutput���ū���
	{																	//	�i�Jif�ԭz
		printf("�O������t���~!");										//	���"�O������t���~"
		return NULL;													//	�^��NULL�A�õ����Ƶ{��
	}																	//	����if�ԭz
	int LoopNumber1,LoopNumber2;										//	�ŧiLoopNumber1�PLoopNumber2�A�Ω�j��p��
	//***OutputData���Ъ�l��***
	for(LoopNumber1 = 0;LoopNumber1<ysize;LoopNumber1++)				//	�Hfor�j��̧��ഫ�Ϲ��������
	{																	//	�i�Jfor�j��
		for(LoopNumber2 = 0;LoopNumber2<xsize;LoopNumber2++)			//	�Hfor�j��̧��ഫ�Ϲ��������
		{																//	�i�Jfor�j��
			OutputData[LoopNumber1 * xsize + LoopNumber2].R = 0;		//	��l��OutputData�����ܼ�
			OutputData[LoopNumber1 * xsize + LoopNumber2].G = 0;		//	��l��OutputData�����ܼ�
			OutputData[LoopNumber1 * xsize + LoopNumber2].B = 0;		//	��l��OutputData�����ܼ�
		}																//	����for�j��
	}																	//	����for�j��
	for(LoopNumber1 = 0;LoopNumber1<ysize;LoopNumber1++)				//	�Hfor�j��̧��ഫ�Ϲ��������
	{																	//	�i�Jfor�j��
		for(LoopNumber2 = 0;LoopNumber2<xsize;LoopNumber2++)			//	�Hfor�j��̧��ഫ�Ϲ��������
		{																//	�i�Jfor�j��
			long double H,S,Max;										//	�ŧiH�BS�PMax������ׯB�I�ƥΥH�O����e�������
			H = InputData[LoopNumber1 * xsize + LoopNumber2].H;			//	��JH���
			S = InputData[LoopNumber1 * xsize + LoopNumber2].S;			//	��JS���
			Max = InputData[LoopNumber1 * xsize + LoopNumber2].V;		//	��JMax���
			unsigned char hi = floor( H / 60.0);						//	�p��hi
			long double f = (H / 60.0) - hi;							//	�p��f
			long double Min,q,t;
			Min = Max * (1.0 - S);
			q = Max * (1.0 - f * S);
			t = Max * (1.0 - (1.0 - f) * S);
			if(hi == 0)													//	�Yhi=0
			{															//	�i�Jif�ԭz
				OutputData[LoopNumber1 * xsize + LoopNumber2].R = Max;	//	��JR���
				OutputData[LoopNumber1 * xsize + LoopNumber2].G = t;	//	��JG���
				OutputData[LoopNumber1 * xsize + LoopNumber2].B = Min;	//	��JB���
			}															//	����if�ԭz
			else if(hi == 1)											//	�Yhi=1
			{															//	�i�Jelse if�ԭz
				OutputData[LoopNumber1 * xsize + LoopNumber2].R = q;	//	��JR���
				OutputData[LoopNumber1 * xsize + LoopNumber2].G = Max;	//	��JG���
				OutputData[LoopNumber1 * xsize + LoopNumber2].B = Min;	//	��JB���
			}															//	����else if�ԭz
			else if(hi == 2)											//	�Yhi=2
			{															//	�i�Jelse if�ԭz
				OutputData[LoopNumber1 * xsize + LoopNumber2].R = Min;	//	��JR���
				OutputData[LoopNumber1 * xsize + LoopNumber2].G = Max;	//	��JG���
				OutputData[LoopNumber1 * xsize + LoopNumber2].B = t;	//	��JB���
			}															//	����else if�ԭz
			else if(hi == 3)											//	�Yhi=3
			{															//	�i�Jelse if�ԭz
				OutputData[LoopNumber1 * xsize + LoopNumber2].R = Min;	//	��JR���
				OutputData[LoopNumber1 * xsize + LoopNumber2].G = q;	//	��JG���
				OutputData[LoopNumber1 * xsize + LoopNumber2].B = Max;	//	��JB���
			}															//	����else if�ԭz
			else if(hi == 4)											//	�Yhi=4
			{															//	�i�Jelse if�ԭz
				OutputData[LoopNumber1 * xsize + LoopNumber2].R = t;	//	��JR���
				OutputData[LoopNumber1 * xsize + LoopNumber2].G = Min;	//	��JG���
				OutputData[LoopNumber1 * xsize + LoopNumber2].B = Max;	//	��JB���
			}															//	����else if�ԭz
			else if(hi == 5)											//	�Yhi=5
			{															//	�i�Jelse if�ԭz
				OutputData[LoopNumber1 * xsize + LoopNumber2].R = Max;	//	��JR���
				OutputData[LoopNumber1 * xsize + LoopNumber2].G = Min;	//	��JG���
				OutputData[LoopNumber1 * xsize + LoopNumber2].B = q;	//	��JB���
			}															//	����else if�ԭz
		}																//	����for�j��
	}																	//	����for�j��
	return OutputData;													//	�^�ǹB�⵲�G
}																		//	����HSVToBMP24RGB�Ƶ{��
bool ImageDataToTxt(const char *file_name,const BMP24RGB *image,const int xsize,const int ysize)
//	ImageDataToTxt�Ƶ{���A�Ω�N�Ϲ��v����Ƽg�Jtxt��
{																		//	�i�JImageDataToTxt�Ƶ{��
	char fname_txt[MAX_PATH];											//	�ŧi�Ϥ���ưO���ɤ������ɦW(�̦hMAX_PATH�Ӧr��)
	sprintf(fname_txt, "%s.txt", file_name);							//	�إ߹Ϥ���ưO���ɤ������ɦW(�̦hMAX_PATH�Ӧr��)
	if(FileWrite(fname_txt,"","w") == False)							//	���իإ��ɮסA�Y�ɮ׫إߥ���
	{																	//	�i�Jif�ԭz
		return False;													//	�^��False�õ����Ƶ{����^
	}																	//	����if�ԭz
	long long int loop_num;												//	�ŧiloop_num�ϰ��ܼƨѰj��ϥ�
	char WriteStringTemp[50];											//	�ŧiWriteStringTemp�r��A�Ω�Ȧs�g�J���
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧Ǽg�J�Ϲ����
	{																	//	�i�Jfor�j��
		sprintf(WriteStringTemp,"��%d�ӹ���R=%d\t",loop_num,image[loop_num].R);
		//	�ͦ��g�J�r����
		if(FileWrite(fname_txt,WriteStringTemp,"a")==False)				//	���ռg�J���
		{																//	�i�Jif�ԭz
			return False;												//	�^��False�õ����Ƶ{����^
		}																//	����if�ԭz
		sprintf(WriteStringTemp,"��%d�ӹ���G=%d\t",loop_num,image[loop_num].G);
		//	�ͦ��g�J�r����
		if(FileWrite(fname_txt,WriteStringTemp,"a")==False)				//	���ռg�J���
		{																//	�i�Jif�ԭz
			return False;												//	�^��False�õ����Ƶ{����^
		}																//	����if�ԭz
		sprintf(WriteStringTemp,"��%d�ӹ���B=%d\n",loop_num,image[loop_num].B);
		//	�ͦ��g�J�r����
		if(FileWrite(fname_txt,WriteStringTemp,"a")==False)				//	���ռg�J���
		{																//	�i�Jif�ԭz
			return False;												//	�^��False�õ����Ƶ{����^
		}																//	����if�ԭz
	}																	//	����for�j��
	return True;														//	�^��True�õ����Ƶ{����^
}																		//	����ImageDataToTxt�Ƶ{��
bool HSVDataToTxt(const char *file_name,const HSV *image,const int xsize,const int ysize)
//	HSVDataToTxt�Ƶ{���A�Ω�NHSV���A�v����Ƽg�Jtxt��
{																		//	�i�JHSVDataToTxt�Ƶ{��
	char fname_txt[MAX_PATH];											//	�ŧi�Ϥ���ưO���ɤ������ɦW(�̦hMAX_PATH�Ӧr��)
	sprintf(fname_txt, "%s.txt", file_name);							//	�إ߹Ϥ���ưO���ɤ������ɦW(�̦hMAX_PATH�Ӧr��)
	if(FileWrite(fname_txt,"","w") == False)							//	���իإ��ɮסA�Y�ɮ׫إߥ���
	{																	//	�i�Jif�ԭz
		return False;													//	�^��False�õ����Ƶ{����^
	}																	//	����if�ԭz
	long long int loop_num;												//	�ŧiloop_num�ϰ��ܼƨѰj��ϥ�
	char WriteStringTemp[50];											//	�ŧiWriteStringTemp�r��A�Ω�Ȧs�g�J���
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧Ǽg�J�Ϲ����
	{																	//	�i�Jfor�j��
		sprintf(WriteStringTemp,"��%d�ӹ���H=%f\t",loop_num,(float)image[loop_num].H);
		//	�ͦ��g�J�r����
		if(FileWrite(fname_txt,WriteStringTemp,"a")==False)				//	���ռg�J���
		{																//	�i�Jif�ԭz
			return False;												//	�^��False�õ����Ƶ{����^
		}																//	����if�ԭz
		sprintf(WriteStringTemp,"��%d�ӹ���S=%f\t",loop_num,(float)image[loop_num].S);
		//	�ͦ��g�J�r����
		if(FileWrite(fname_txt,WriteStringTemp,"a")==False)				//	���ռg�J���
		{																//	�i�Jif�ԭz
			return False;												//	�^��False�õ����Ƶ{����^
		}																//	����if�ԭz
		sprintf(WriteStringTemp,"��%d�ӹ���V=%f\n",loop_num,(float)image[loop_num].V);
		//	�ͦ��g�J�r����
		if(FileWrite(fname_txt,WriteStringTemp,"a")==False)				//	���ռg�J���
		{																//	�i�Jif�ԭz
			return False;												//	�^��False�õ����Ƶ{����^
		}																//	����if�ԭz
	}																	//	����for�j��
	return True;														//	�^��True�õ����Ƶ{����^
}																		//	����HSVDataToTxt�Ƶ{��
BMP24RGB *ImgDifference2(const BMP24RGB *InputData1,const BMP24RGB *InputData2,const int xsize,const int ysize)
//	ImgDifference2�Ƶ{��
{																		//	�i�JImgDifference2�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData��BMP24RGB���Ы��A�ܼ�
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(HSV));		//	�t�mOutputData���аO����j�p
	if(OutputData == NULL)												//	�YOutput���ū���
	{																	//	�i�Jif�ԭz
		printf("�O������t���~!");										//	���"�O������t���~"
		return NULL;													//	�^��NULL�A�õ����Ƶ{��
	}																	//	����if�ԭz
	int LoopNumber1,LoopNumber2;										//	�ŧiLoopNumber1�PLoopNumber2�A�Ω�j��p��
	//***OutputData���Ъ�l��***
	for(LoopNumber1 = 0;LoopNumber1<ysize;LoopNumber1++)				//	�Hfor�j��̧��ഫ�Ϲ��������
	{																	//	�i�Jfor�j��
		for(LoopNumber2 = 0;LoopNumber2<xsize;LoopNumber2++)			//	�Hfor�j��̧��ഫ�Ϲ��������
		{																//	�i�Jfor�j��
			OutputData[LoopNumber1 * xsize + LoopNumber2].R = 0;		//	��l��OutputData�����ܼ�
			OutputData[LoopNumber1 * xsize + LoopNumber2].G = 0;		//	��l��OutputData�����ܼ�
			OutputData[LoopNumber1 * xsize + LoopNumber2].B = 0;		//	��l��OutputData�����ܼ�
		}																//	����for�j��
	}																	//	����for�j��
	for(LoopNumber1 = 0;LoopNumber1<ysize;LoopNumber1++)				//	�Hfor�j��̧��ഫ�Ϲ��������
	{																	//	�i�Jfor�j��
		for(LoopNumber2 = 0;LoopNumber2<xsize;LoopNumber2++)			//	�Hfor�j��̧��ഫ�Ϲ��������
		{																//	�i�Jfor�j��
			unsigned char Red1,Green1,Blue1;							//	�ŧiRed1,Green1,Blue1�ܼơA�O���������
			Red1 = InputData1[LoopNumber1 * xsize + LoopNumber2].R;		//	��JInputData1��Red���
			Green1 = InputData1[LoopNumber1 * xsize + LoopNumber2].G;	//	��JInputData1��Green���
			Blue1 = InputData1[LoopNumber1 * xsize + LoopNumber2].B;	//	��JInputData1��Blue���
			unsigned char Red2,Green2,Blue2;							//	�ŧiRed2,Green2,Blue2�ܼơA�O���������
			Red2 = InputData2[LoopNumber1 * xsize + LoopNumber2].R;		//	��JInputData2��Red���
			Green2 = InputData2[LoopNumber1 * xsize + LoopNumber2].G;	//	��JInputData2��Green���
			Blue2 = InputData2[LoopNumber1 * xsize + LoopNumber2].B;	//	��JInputData2��Blue���
			OutputData[LoopNumber1 * xsize + LoopNumber2].R = fabs(Red1 - Red2);
			//	�N��J���InputData1�PInputData2�i��۴�B��è�����ȫ��JOutputData
			OutputData[LoopNumber1 * xsize + LoopNumber2].G = fabs(Green1 - Green2);
			//	�N��J���InputData1�PInputData2�i��۴�B��è�����ȫ��JOutputData
			OutputData[LoopNumber1 * xsize + LoopNumber2].B = fabs(Blue1 - Blue2);
			//	�N��J���InputData1�PInputData2�i��۴�B��è�����ȫ��JOutputData
		}																//	����for�j��
	}																	//	����for�j��
	return OutputData;													//	�^��OutputData�A�õ����Ƶ{��
}																		//	����ImgDifference2�Ƶ{��
BMP24RGB *BMP24RGB2or(const BMP24RGB *InputData1,const BMP24RGB *InputData2,const int xsize,const int ysize)
//	BMP24RGB2or�Ƶ{��
{																		//	�i�JBMP24RGB2or�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData��BMP24RGB���Ы��A�ܼ�
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(HSV));		//	�t�mOutputData���аO����j�p
	if(OutputData == NULL)												//	�YOutput���ū���
	{																	//	�i�Jif�ԭz
		printf("�O������t���~!");										//	���"�O������t���~"
		return NULL;													//	�^��NULL�A�õ����Ƶ{��
	}																	//	����if�ԭz
	int LoopNumber1,LoopNumber2;										//	�ŧiLoopNumber1�PLoopNumber2�A�Ω�j��p��
	//***OutputData���Ъ�l��***
	for(LoopNumber1 = 0;LoopNumber1<ysize;LoopNumber1++)				//	�Hfor�j��̧��ഫ�Ϲ��������
	{																	//	�i�Jfor�j��
		for(LoopNumber2 = 0;LoopNumber2<xsize;LoopNumber2++)			//	�Hfor�j��̧��ഫ�Ϲ��������
		{																//	�i�Jfor�j��
			OutputData[LoopNumber1 * xsize + LoopNumber2].R = 0;		//	��l��OutputData�����ܼ�
			OutputData[LoopNumber1 * xsize + LoopNumber2].G = 0;		//	��l��OutputData�����ܼ�
			OutputData[LoopNumber1 * xsize + LoopNumber2].B = 0;		//	��l��OutputData�����ܼ�
		}																//	����for�j��
	}																	//	����for�j��
	for(LoopNumber1 = 0;LoopNumber1<ysize;LoopNumber1++)				//	�Hfor�j��̧��ഫ�Ϲ��������
	{																	//	�i�Jfor�j��
		for(LoopNumber2 = 0;LoopNumber2<xsize;LoopNumber2++)			//	�Hfor�j��̧��ഫ�Ϲ��������
		{																//	�i�Jfor�j��
			unsigned char Red1,Green1,Blue1;							//	�ŧiRed1,Green1,Blue1�ܼơA�O���������
			Red1 = InputData1[LoopNumber1 * xsize + LoopNumber2].R;		//	��JInputData1��Red���
			Green1 = InputData1[LoopNumber1 * xsize + LoopNumber2].G;	//	��JInputData1��Green���
			Blue1 = InputData1[LoopNumber1 * xsize + LoopNumber2].B;	//	��JInputData1��Blue���
			unsigned char Red2,Green2,Blue2;							//	�ŧiRed2,Green2,Blue2�ܼơA�O���������
			Red2 = InputData2[LoopNumber1 * xsize + LoopNumber2].R;		//	��JInputData2��Red���
			Green2 = InputData2[LoopNumber1 * xsize + LoopNumber2].G;	//	��JInputData2��Green���
			Blue2 = InputData2[LoopNumber1 * xsize + LoopNumber2].B;	//	��JInputData2��Blue���
			OutputData[LoopNumber1 * xsize + LoopNumber2].R = Red1 | Red2;
			//	�N��J���InputData1�PInputData2�i��OR�B����JOutputData
			OutputData[LoopNumber1 * xsize + LoopNumber2].G = Green1 | Green2;
			//	�N��J���InputData1�PInputData2�i��OR�B����JOutputData
			OutputData[LoopNumber1 * xsize + LoopNumber2].B = Blue1 | Blue2;
			//	�N��J���InputData1�PInputData2�i��OR�B����JOutputData
		}																//	����for�j��
	}																	//	����for�j��
	return OutputData;													//	�^��OutputData�A�õ����Ƶ{��
}																		//	����BMP24RGB2or�Ƶ{��
BMP24RGB *BmpToGraylevel(const BMP24RGB *image,const int xsize,const int ysize)
//	BMP�Ϥ������Ƕ��Ƶ{��
{																		//	�i�JBMP�Ϥ������Ƕ��Ƶ{��
	BMP24RGB *GraylevelImage;											//	�ŧiGraylevelImage�����ܼơA�O���Ƕ��ഫ��Ϲ����
	GraylevelImage = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));
	//	�t�mGraylevelImage���аO����j�p
	if (GraylevelImage == NULL) 										//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz 
	long long int loop_num;												//	�ŧiloop_num�ϰ��ܼƨѰj��ϥ�
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧ǭp��Ϲ������Ƕ���
	{																	//	�i�Jfor�j��
		GraylevelImage[loop_num].R = (image[loop_num].R + image[loop_num].G + image[loop_num].B) / 3;
		//	�p��Ƕ��ഫ������
		GraylevelImage[loop_num].G = (image[loop_num].R + image[loop_num].G + image[loop_num].B) / 3;
		//	�p��Ƕ��ഫ������
		GraylevelImage[loop_num].B = (image[loop_num].R + image[loop_num].G + image[loop_num].B) / 3;
		//	�p��Ƕ��ഫ������
	}																	//	����for�j��
    return GraylevelImage;												//	�^�ǦǶ��ഫ���G
}																		//	����BMP�Ϥ������Ƕ��Ƶ{��
BMP24RGB *BmpConvolution33(const BMP24RGB *image,const int xsize,const int ysize,const long double Mask[])
//	BmpConvolution33�Ƶ{��
{																		//	�i�JBmpConvolution33�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData�����ܼơA�O���Ϲ���ƹB�⵲�G
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData���аO����j�p
	if (OutputData == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz 
	long double weighting = 0;											//	�ŧi�ê�l��weighting(�v��)�ܼ�
	long long int loop_num;												//	�ŧiloop_num�ϰ��ܼƨѰj��ϥ�
	for(loop_num = 0; loop_num < 3 * 3;loop_num = loop_num + 1)			//	�Hfor�j��p���v���֭p��
	{																	//	�i�Jfor�j��
		weighting = weighting + Mask[loop_num];							//	�έp�v��
	}																	//	����for�j��
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧ǭp��Ϲ�����
	{																	//	�i�Jfor�j��
		if( (loop_num < xsize) || ( (loop_num % xsize) == 0) || ( ((loop_num + 1) % xsize) == 0) || (loop_num >= (xsize*(ysize-1))))
		//	�˴�����I����
		//	(loop_num >= (xsize*(ysize-1)))		------->	|-�СССССС�|
		//													|				|
		//	( (loop_num % xsize) == 0)			------->	|				|	<-------	( ((loop_num + 1) % xsize) == 0)
		//													|				|
		//	(loop_num < xsize)					------->	|-�СССССС�|
		{																//	�i�Jif�ԭz
			OutputData[loop_num].R = image[loop_num].R;					//	����I���B�z
			OutputData[loop_num].G = image[loop_num].G;					//	����I���B�z
			OutputData[loop_num].B = image[loop_num].B;					//	����I���B�z
		}																//	����if�ԭz
		else															//	�Y�D����I����
		{																//	�i�Jelse�ԭz
			OutputData[loop_num].R = (
				image[loop_num+xsize-1].R	* Mask[6] + image[loop_num+xsize].R	* Mask[7] + image[loop_num+xsize+1].R	* Mask[8] +
				image[loop_num-1].R 		* Mask[3] + image[loop_num].R		* Mask[4] + image[loop_num+1].R 		* Mask[5] +
				image[loop_num-xsize-1].R	* Mask[0] + image[loop_num-xsize].R	* Mask[1] + image[loop_num-xsize+1].R	* Mask[2]
				) / weighting;											//	�p��Convolution
			OutputData[loop_num].G = (
				image[loop_num+xsize-1].G	* Mask[6] + image[loop_num+xsize].G	* Mask[7] + image[loop_num+xsize+1].G	* Mask[8] +
				image[loop_num-1].G 		* Mask[3] + image[loop_num].G		* Mask[4] + image[loop_num+1].G 		* Mask[5] +
				image[loop_num-xsize-1].G	* Mask[0] + image[loop_num-xsize].G	* Mask[1] + image[loop_num-xsize+1].G	* Mask[2]
				) / weighting;											//	�p��Convolution
			OutputData[loop_num].B = (
				image[loop_num+xsize-1].B	* Mask[6] + image[loop_num+xsize].B	* Mask[7] + image[loop_num+xsize+1].B	* Mask[8] +
				image[loop_num-1].B 		* Mask[3] + image[loop_num].B		* Mask[4] + image[loop_num+1].B 		* Mask[5] +
				image[loop_num-xsize-1].B	* Mask[0] + image[loop_num-xsize].B	* Mask[1] + image[loop_num-xsize+1].B	* Mask[2]
				) / weighting;											//	�p��Convolution
		}																//	����else�ԭz
	}																	//	����for�j��
    return OutputData;													//	�^�ǹB�⵲�G
}																		//	����BmpConvolution33�Ƶ{��
BMP24RGB *BmpConvolution55(const BMP24RGB *image,const int xsize,const int ysize,const long double Mask[])
//	BmpConvolution55�Ƶ{��
{																		//	�i�JBmpConvolution55�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData�����ܼơA�O���Ϲ���ƹB�⵲�G
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData���аO����j�p
	if (OutputData == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz 
	long double weighting = 0;											//	�ŧi�ê�l��weighting(�v��)�ܼ�
	long long int loop_num;												//	�ŧiloop_num�ϰ��ܼƨѰj��ϥ�
	for(loop_num = 0; loop_num < 5 * 5;loop_num = loop_num + 1)			//	�Hfor�j��p���v���֭p��
	{																	//	�i�Jfor�j��
		weighting = weighting + Mask[loop_num];							//	�έp�v��
	}																	//	����for�j��
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧ǭp��Ϲ�����
	{																	//	�i�Jfor�j��
		if( (loop_num < 2 * xsize) || 
			( (loop_num % xsize) == 0) ||
			( (loop_num % xsize) == 1) ||
			( ((loop_num + 1) % xsize) == 0) ||
			( ((loop_num + 2) % xsize) == 0) ||
			(loop_num >= (xsize*(ysize-2))) )
		//	�˴�����I����
		{																//	�i�Jif�ԭz
			OutputData[loop_num].R = image[loop_num].R;					//	����I���B�z
			OutputData[loop_num].G = image[loop_num].G;					//	����I���B�z
			OutputData[loop_num].B = image[loop_num].B;					//	����I���B�z
		}																//	����if�ԭz
		else															//	�Y�D����I����
		{																//	�i�Jelse�ԭz
			OutputData[loop_num].R = (
				image[loop_num+2*xsize-2].R	* Mask[20] + image[loop_num+2*xsize-1].R	* Mask[21] + image[loop_num+2*xsize].R	* Mask[22] + image[loop_num+2*xsize+1].R	* Mask[23] + image[loop_num+2*xsize+2].R	* Mask[24] +
				image[loop_num+1*xsize-2].R	* Mask[15] + image[loop_num+1*xsize-1].R	* Mask[16] + image[loop_num+1*xsize].R	* Mask[17] + image[loop_num+1*xsize+1].R	* Mask[18] + image[loop_num+1*xsize+2].R	* Mask[19] +
				image[loop_num-0*xsize-2].R	* Mask[10] + image[loop_num-0*xsize-1].R	* Mask[11] + image[loop_num-0*xsize].R	* Mask[12] + image[loop_num-0*xsize+1].R	* Mask[13] + image[loop_num-0*xsize+2].R	* Mask[14] +
				image[loop_num-1*xsize-2].R	* Mask[ 5] + image[loop_num-1*xsize-1].R	* Mask[6]  + image[loop_num-1*xsize].R	* Mask[ 7] + image[loop_num-1*xsize+1].R	* Mask[ 8] + image[loop_num-1*xsize+2].R	* Mask[ 9] +
				image[loop_num-2*xsize-2].R	* Mask[ 0] + image[loop_num-2*xsize-1].R	* Mask[1]  + image[loop_num-2*xsize].R	* Mask[ 2] + image[loop_num-2*xsize+1].R	* Mask[ 3] + image[loop_num-2*xsize+2].R	* Mask[ 4]
				) / weighting;											//	�p��Convolution
			OutputData[loop_num].G = (
				image[loop_num+2*xsize-2].G	* Mask[20] + image[loop_num+2*xsize-1].G	* Mask[21] + image[loop_num+2*xsize].G	* Mask[22] + image[loop_num+2*xsize+1].G	* Mask[23] + image[loop_num+2*xsize+2].G	* Mask[24] +
				image[loop_num+1*xsize-2].G	* Mask[15] + image[loop_num+1*xsize-1].G	* Mask[16] + image[loop_num+1*xsize].G	* Mask[17] + image[loop_num+1*xsize+1].G	* Mask[18] + image[loop_num+1*xsize+2].G	* Mask[19] +
				image[loop_num-0*xsize-2].G	* Mask[10] + image[loop_num-0*xsize-1].G	* Mask[11] + image[loop_num-0*xsize].G	* Mask[12] + image[loop_num-0*xsize+1].G	* Mask[13] + image[loop_num-0*xsize+2].G	* Mask[14] +
				image[loop_num-1*xsize-2].G	* Mask[ 5] + image[loop_num-1*xsize-1].G	* Mask[ 6]  + image[loop_num-1*xsize].G	* Mask[ 7] + image[loop_num-1*xsize+1].G	* Mask[ 8] + image[loop_num-1*xsize+2].G	* Mask[ 9] +
				image[loop_num-2*xsize-2].G	* Mask[ 0] + image[loop_num-2*xsize-1].G	* Mask[ 1]  + image[loop_num-2*xsize].G	* Mask[ 2] + image[loop_num-2*xsize+1].G	* Mask[ 3] + image[loop_num-2*xsize+2].G	* Mask[ 4]
				) / weighting;											//	�p��Convolution
			OutputData[loop_num].B = (
				image[loop_num+2*xsize-2].B	* Mask[20] + image[loop_num+2*xsize-1].B	* Mask[21] + image[loop_num+2*xsize].B	* Mask[22] + image[loop_num+2*xsize+1].B	* Mask[23] + image[loop_num+2*xsize+2].B	* Mask[24] +
				image[loop_num+1*xsize-2].B	* Mask[15] + image[loop_num+1*xsize-1].B	* Mask[16] + image[loop_num+1*xsize].B	* Mask[17] + image[loop_num+1*xsize+1].B	* Mask[18] + image[loop_num+1*xsize+2].B	* Mask[19] +
				image[loop_num-0*xsize-2].B	* Mask[10] + image[loop_num-0*xsize-1].B	* Mask[11] + image[loop_num-0*xsize].B	* Mask[12] + image[loop_num-0*xsize+1].B	* Mask[13] + image[loop_num-0*xsize+2].B	* Mask[14] +
				image[loop_num-1*xsize-2].B	* Mask[ 5] + image[loop_num-1*xsize-1].B	* Mask[ 6] + image[loop_num-1*xsize].B	* Mask[ 7] + image[loop_num-1*xsize+1].B	* Mask[ 8] + image[loop_num-1*xsize+2].B	* Mask[ 9] +
				image[loop_num-2*xsize-2].B	* Mask[ 0] + image[loop_num-2*xsize-1].B	* Mask[ 1] + image[loop_num-2*xsize].B	* Mask[ 2] + image[loop_num-2*xsize+1].B	* Mask[ 3] + image[loop_num-2*xsize+2].B	* Mask[ 4]
				) / weighting;											//	�p��Convolution
		}																//	����else�ԭz
	}																	//	����for�j��
    return OutputData;													//	�^�ǹB�⵲�G
}																		//	����BmpConvolution55�Ƶ{��
BMP24RGB *BmpConvolution77(const BMP24RGB *image,const int xsize,const int ysize,const long double Mask[])
//	BmpConvolution77�Ƶ{��
{																		//	�i�JBmpConvolution77�Ƶ{��
	char MaskSize = 7;													//	�ŧiMaskSize(Mask�j�p�ܼơA�O��Mask���)��7
	BMP24RGB *OutputData;												//	�ŧiOutputData�����ܼơA�O���Ϲ���ƹB�⵲�G
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData���аO����j�p
	if (OutputData == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz 
	long double weighting = 0;											//	�ŧi�ê�l��weighting(�v��)�ܼ�
	long long int loop_num1;											//	�ŧiloop_num1�ϰ��ܼƨѰj��ϥ�
	for(loop_num1 = 0; loop_num1 < MaskSize * MaskSize;loop_num1 = loop_num1 + 1)
	//	�Hfor�j��p���v���֭p��
	{																	//	�i�Jfor�j��
		weighting = weighting + Mask[loop_num1];						//	�έp�v��
	}																	//	����for�j��
	for(loop_num1 = 0; loop_num1 <(xsize * ysize); loop_num1++)			//	�Hfor�j��̧ǭp��Ϲ�����
	{																	//	�i�Jfor�j��
		int PixelLocationX;												//	�ŧiPixelLocationX�A�O�������I���Ϲ��G���y�Ф���X��V��m
		int PixelLocationY;												//	�ŧiPixelLocationY�A�O�������I���Ϲ��G���y�Ф���Y��V��m
		PixelLocationX = loop_num1 % xsize;								//	�p��PixelLocationX
		PixelLocationY = floor(loop_num1 / xsize);						//	�p��PixelLocationY
		if( (PixelLocationX < floor(MaskSize/2)) || (PixelLocationX > (xsize - floor(MaskSize/2))) ||
			(PixelLocationY < floor(MaskSize/2)) || (PixelLocationY > (ysize - floor(MaskSize/2))) )
		//	�˴�����I����
		{																//	�i�Jif�ԭz
			OutputData[loop_num1].R = image[loop_num1].R;				//	����I���B�z
			OutputData[loop_num1].G = image[loop_num1].G;				//	����I���B�z
			OutputData[loop_num1].B = image[loop_num1].B;				//	����I���B�z
		}																//	����if�ԭz
		else															//	�Y�D����I����
		{																//	�i�Jelse�ԭz
			char loop_num2, loop_num3;									//	�ŧiloop_num2�Bloop_num3�ܼƥH�i��j��p��
			double sum_R = 0;											//	�ŧisum_R�ܼƲέp�����[�v�`�M
			double sum_G = 0;											//	�ŧisum_G�ܼƲέp�����[�v�`�M
			double sum_B = 0;											//	�ŧisum_B�ܼƲέp�����[�v�`�M
			for(loop_num2 = -floor(MaskSize/2); loop_num2 <= floor(MaskSize/2); loop_num2 ++)
			//	�Hfor�j��p��Convolution
			{															//	�i�Jfor�j��
				for(loop_num3 = -floor(MaskSize/2); loop_num3 <= floor(MaskSize/2); loop_num3 ++)
				//	�Hfor�j��p��Convolution
				{														//	�i�Jfor�j��
					sum_R += image[loop_num1+loop_num2*xsize+loop_num3].R *
							 Mask[(int)((loop_num2 + floor(MaskSize/2)) * MaskSize + (loop_num3 + floor(MaskSize/2)))];
					//	�έp�����[�v�`�M
					sum_G += image[loop_num1+loop_num2*xsize+loop_num3].G *
							 Mask[(int)((loop_num2 + floor(MaskSize/2)) * MaskSize + (loop_num3 + floor(MaskSize/2)))];
					//	�έp�����[�v�`�M
					sum_B += image[loop_num1+loop_num2*xsize+loop_num3].B *
							 Mask[(int)((loop_num2 + floor(MaskSize/2)) * MaskSize + (loop_num3 + floor(MaskSize/2)))];
					//	�έp�����[�v�`�M
				}														//	����for�j��
			}															//	����for�j��
			OutputData[loop_num1].R = sum_R / weighting;				//	�p��Convolution
			OutputData[loop_num1].G = sum_G / weighting;				//	�p��Convolution
			OutputData[loop_num1].B = sum_B / weighting;				//	�p��Convolution
		}																//	����else�ԭz
	}																	//	����for�j��
    return OutputData;													//	�^�ǹB�⵲�G
}																		//	����BmpConvolution77�Ƶ{��
BMP24RGB *BmpConvolution(int MaskSize, const BMP24RGB *image,const int xsize,const int ysize,const long double Mask[])
{																		//	�i�JBmpConvolution�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData�����ܼơA�O���Ϲ���ƹB�⵲�G
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData���аO����j�p
	if (OutputData == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz 
	long double weighting = 0;											//	�ŧi�ê�l��weighting(�v��)�ܼ�
	long long int loop_num1;											//	�ŧiloop_num1�ϰ��ܼƨѰj��ϥ�
	for(loop_num1 = 0; loop_num1 < MaskSize * MaskSize;loop_num1 = loop_num1 + 1)
	//	�Hfor�j��p���v���֭p��
	{																	//	�i�Jfor�j��
		weighting = weighting + Mask[loop_num1];						//	�έp�v��
	}																	//	����for�j��
	for(loop_num1 = 0; loop_num1 <(xsize * ysize); loop_num1++)			//	�Hfor�j��̧ǭp��Ϲ�����
	{																	//	�i�Jfor�j��
		int PixelLocationX;												//	�ŧiPixelLocationX�A�O�������I���Ϲ��G���y�Ф���X��V��m
		int PixelLocationY;												//	�ŧiPixelLocationY�A�O�������I���Ϲ��G���y�Ф���Y��V��m
		PixelLocationX = loop_num1 % xsize;								//	�p��PixelLocationX
		PixelLocationY = floor(loop_num1 / xsize);						//	�p��PixelLocationY
		if( (PixelLocationX < floor(MaskSize/2)) || (PixelLocationX > (xsize - floor(MaskSize/2))) ||
			(PixelLocationY < floor(MaskSize/2)) || (PixelLocationY > (ysize - floor(MaskSize/2))) )
		//	�˴�����I����
		{																//	�i�Jif�ԭz
			OutputData[loop_num1].R = image[loop_num1].R;				//	����I���B�z
			OutputData[loop_num1].G = image[loop_num1].G;				//	����I���B�z
			OutputData[loop_num1].B = image[loop_num1].B;				//	����I���B�z
		}																//	����if�ԭz
		else															//	�Y�D����I����
		{																//	�i�Jelse�ԭz
			char loop_num2, loop_num3;									//	�ŧiloop_num2�Bloop_num3�ܼƥH�i��j��p��
			double sum_R = 0;											//	�ŧisum_R�ܼƲέp�����[�v�`�M
			double sum_G = 0;											//	�ŧisum_G�ܼƲέp�����[�v�`�M
			double sum_B = 0;											//	�ŧisum_B�ܼƲέp�����[�v�`�M
			for(loop_num2 = -floor(MaskSize/2); loop_num2 <= floor(MaskSize/2); loop_num2 ++)
			//	�Hfor�j��p��Convolution
			{															//	�i�Jfor�j��
				for(loop_num3 = -floor(MaskSize/2); loop_num3 <= floor(MaskSize/2); loop_num3 ++)
				//	�Hfor�j��p��Convolution
				{														//	�i�Jfor�j��
					sum_R += image[loop_num1+loop_num2*xsize+loop_num3].R *
							 Mask[(int)((loop_num2 + floor(MaskSize/2)) * MaskSize + (loop_num3 + floor(MaskSize/2)))];
					//	�έp�����[�v�`�M
					sum_G += image[loop_num1+loop_num2*xsize+loop_num3].G *
							 Mask[(int)((loop_num2 + floor(MaskSize/2)) * MaskSize + (loop_num3 + floor(MaskSize/2)))];
					//	�έp�����[�v�`�M
					sum_B += image[loop_num1+loop_num2*xsize+loop_num3].B *
							 Mask[(int)((loop_num2 + floor(MaskSize/2)) * MaskSize + (loop_num3 + floor(MaskSize/2)))];
					//	�έp�����[�v�`�M
				}														//	����for�j��
			}															//	����for�j��
			OutputData[loop_num1].R = sum_R / weighting;				//	�p��Convolution
			OutputData[loop_num1].G = sum_G / weighting;				//	�p��Convolution
			OutputData[loop_num1].B = sum_B / weighting;				//	�p��Convolution
		}																//	����else�ԭz
	}																	//	����for�j��
    return OutputData;													//	�^�ǹB�⵲�G
}																		//	����BmpConvolution�Ƶ{��
BMP24RGB *ImageSmoothing33V1(const BMP24RGB *image,const int xsize,const int ysize)
//	ImageSmoothing33V1(BMP����3*3Mask�����o�i)�Ƶ{��
{																		//	�i�JImageSmoothing33V1�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData�����ܼơA�O���Ϲ���ƹB�⵲�G
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData���аO����j�p
	if (OutputData == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz 
	long long int loop_num;												//	�ŧiloop_num�ϰ��ܼƨѰj��ϥ�
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧ǭp��Ϲ�����
	{																	//	�i�Jfor�j��
		if( (loop_num < xsize) || ( (loop_num % xsize) == 0) || ( ((loop_num + 1) % xsize) == 0) || (loop_num >= (xsize*(ysize-1))))
		//	�˴�����I����
		{																//	�i�Jif�ԭz
			OutputData[loop_num].R = image[loop_num].R;					//	����I���B�z
			OutputData[loop_num].G = image[loop_num].G;					//	����I���B�z
			OutputData[loop_num].B = image[loop_num].B;					//	����I���B�z
		}																//	����if�ԭz
		else															//	�Y�D����I����
		{																//	�i�Jelse�ԭz
			OutputData[loop_num].R = (
				image[loop_num+xsize-1].R	* 1 + image[loop_num+xsize].R	* 1 + image[loop_num+xsize+1].R	* 1 +
				image[loop_num-1].R 		* 1 + image[loop_num].R			* 1 + image[loop_num+1].R 		* 1 +
				image[loop_num-xsize-1].R	* 1 + image[loop_num-xsize].R	* 1 + image[loop_num-xsize+1].R	* 1
				) / 9;													//	���ƪk�p��
			OutputData[loop_num].G = (
				image[loop_num+xsize-1].G	* 1 + image[loop_num+xsize].G	* 1 + image[loop_num+xsize+1].G	* 1 +
				image[loop_num-1].G 		* 1 + image[loop_num].G			* 1 + image[loop_num+1].G 		* 1 +
				image[loop_num-xsize-1].G	* 1 + image[loop_num-xsize].G	* 1 + image[loop_num-xsize+1].G	* 1
				) / 9;													//	���ƪk�p��
			OutputData[loop_num].B = (
				image[loop_num+xsize-1].B	* 1 + image[loop_num+xsize].B	* 1 + image[loop_num+xsize+1].B	* 1 +
				image[loop_num-1].B 		* 1 + image[loop_num].B			* 1 + image[loop_num+1].B 		* 1 +
				image[loop_num-xsize-1].B	* 1 + image[loop_num-xsize].B	* 1 + image[loop_num-xsize+1].B	* 1
				) / 9;													//	���ƪk�p��
		}																//	����else�ԭz
	}																	//	����for�j��
    return OutputData;													//	�^�ǹB�⵲�G
}																		//	����ImageSmoothing33V1�Ƶ{��
BMP24RGB *ImageSmoothing33V2(const BMP24RGB *image,const int xsize,const int ysize)
//	ImageSmoothing33V2(BMP����3*3Mask�����o�i)�Ƶ{��
{																		//	�i�JImageSmoothing33V2�Ƶ{��
	long double Mask[3 * 3];											//	�ŧiMask�}�C
	Mask[6] = (long double)1;	Mask[7] = (long double)1;	Mask[8] = (long double)1;
	//	���wMask�B�n�ƭ�
	Mask[3] = (long double)1;	Mask[4] = (long double)1;	Mask[5] = (long double)1;
	//	���wMask�B�n�ƭ�
	Mask[0] = (long double)1;	Mask[1] = (long double)1;	Mask[2] = (long double)1;
	//	���wMask�B�n�ƭ�
    return BmpConvolution33(image, xsize, ysize, Mask);					//	�I�sBmpConvolution33�Ƶ{���p��æ^�ǹB�⵲�G
}																		//	����ImageSmoothing33V2�Ƶ{��
BMP24RGB *ImageSmoothing55(const BMP24RGB *image,const int xsize,const int ysize)
//	ImageSmoothing55(BMP����5*5Mask�����o�i)�Ƶ{��
{																		//	�i�JImageSmoothing55�Ƶ{��
	long double Mask[5 * 5];											//	�ŧiMask�}�C
	Mask[20] = (long double)1;	Mask[21] = (long double)1;	Mask[22] = (long double)1;	Mask[23] = (long double)1;	Mask[24] = (long double)1;
	Mask[15] = (long double)1;	Mask[16] = (long double)1;	Mask[17] = (long double)1;	Mask[18] = (long double)1;	Mask[19] = (long double)1;
	Mask[10] = (long double)1;	Mask[11] = (long double)1;	Mask[12] = (long double)1;	Mask[13] = (long double)1;	Mask[14] = (long double)1;
	Mask[ 5] = (long double)1;	Mask[ 6] = (long double)1;	Mask[ 7] = (long double)1;	Mask[ 8] = (long double)1;	Mask[ 9] = (long double)1;
	Mask[ 0] = (long double)1;	Mask[ 1] = (long double)1;	Mask[ 2] = (long double)1;	Mask[ 3] = (long double)1;	Mask[ 4] = (long double)1;
	//	���wMask�B�n�ƭ�
    return BmpConvolution55(image, xsize, ysize, Mask);					//	�I�sBmpConvolution55�Ƶ{���p��æ^�ǹB�⵲�G
}																		//	����ImageSmoothing55�Ƶ{��
BMP24RGB *ImageSmoothing77(const BMP24RGB *image,const int xsize,const int ysize)
//	ImageSmoothing77(BMP����7*7Mask�����o�i)�Ƶ{��
{																		//	�i�JImageSmoothing77�Ƶ{��
	long double Mask[7 * 7];											//	�ŧiMask�}�C
	char loop_num = 0;													//	�ŧiloop_num�ܼƥΩ�j��p�ơA�ó]�w��l�Ȭ�0
	for(loop_num = 0; loop_num < 7 * 7; loop_num++)						//	�Hfor�j�鵹�wMask�ƭ�
	{																	//	�i�Jfor�j��
		Mask[loop_num] = (long double)1;								//	���wMask�B�n�ƭ�
	}																	//	����for�j��
    return BmpConvolution77(image, xsize, ysize, Mask);					//	�I�sBmpConvolution77�Ƶ{���p��æ^�ǹB�⵲�G
}																		//	����ImageSmoothing77�Ƶ{��
BMP24RGB *ImageSmoothing(const int MaskSize, const BMP24RGB *image, const int xsize, const int ysize)
//	ImageSmoothing(BMP���ɥ����o�i)�Ƶ{��
{																		//	�i�JImageSmoothing�Ƶ{��
	long double *Mask;													//	�ŧiMask����
	Mask = (long double*)malloc(MaskSize * MaskSize * sizeof(long double));
	//	�t�mMask���аO����j�p
	int loop_num = 0;													//	�ŧiloop_num�ܼƥΩ�j��p�ơA�ó]�w��l�Ȭ�0
	for(loop_num = 0; loop_num < MaskSize * MaskSize; loop_num++)		//	�Hfor�j�鵹�wMask�ƭ�
	{																	//	�i�Jfor�j��
		Mask[loop_num] = (long double)1;								//	���wMask�B�n�ƭ�
	}																	//	����for�j��
    return BmpConvolution(MaskSize, image, xsize, ysize, Mask);			//	�I�sBmpConvolution�Ƶ{���p��æ^�ǹB�⵲�G
}																		//	����ImageSmoothing�Ƶ{��
BMP24RGB *MedianFilter33(const BMP24RGB *image,const int xsize,const int ysize)
//	BMP����3*3Mask�����o�i�Ƶ{��
{																		//	�i�JMedianFilter33(BMP����3*3�����o�i)�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData�����ܼơA�O���Ϲ���ƹB�⵲�G
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData���аO����j�p
	if (OutputData == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz 
	long long int loop_num;												//	�ŧiloop_num�ϰ��ܼƨѰj��ϥ�
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧ǭp��Ϲ�����
	{																	//	�i�Jfor�j��
		if( (loop_num < xsize) || ( (loop_num % xsize) == 0) || ( ((loop_num + 1) % xsize) == 0) || (loop_num >= (xsize*(ysize-1))))
		//	�˴�����I����
		{																//	�i�Jif�ԭz
			OutputData[loop_num].R = image[loop_num].R;					//	����I���B�z
			OutputData[loop_num].G = image[loop_num].G;					//	����I���B�z
			OutputData[loop_num].B = image[loop_num].B;					//	����I���B�z
		}																//	����if�ԭz
		else															//	�Y�D����I����
		{																//	�i�Jelse�ԭz
			unsigned char *SortArray;									//	�ŧiSortArray��unsigned char���A���СA�ѹ����ȱƧǨϥ�
			SortArray = (unsigned char*)malloc(9 * sizeof(unsigned char));
			//---R�����Ƨ�---
			SortArray[0] = image[loop_num-xsize-1].R;					//	�N������ƶ�JSortArray�}�C
			SortArray[1] = image[loop_num-xsize].R;						//	�N������ƶ�JSortArray�}�C
			SortArray[2] = image[loop_num-xsize+1].R;					//	�N������ƶ�JSortArray�}�C
			SortArray[3] = image[loop_num-1].R;							//	�N������ƶ�JSortArray�}�C
			SortArray[4] = image[loop_num].R;							//	�N������ƶ�JSortArray�}�C
			SortArray[5] = image[loop_num+1].R;							//	�N������ƶ�JSortArray�}�C
			SortArray[6] = image[loop_num+xsize-1].R;					//	�N������ƶ�JSortArray�}�C
			SortArray[7] = image[loop_num+xsize].R;						//	�N������ƶ�JSortArray�}�C
			SortArray[8] = image[loop_num+xsize+1].R;					//	�N������ƶ�JSortArray�}�C
			//qsort(SortArray, 9, sizeof(unsigned char), Compare);		//	�I�sqsort�ƧǨ��(�w�q��stdlib.h)
			SortArray = UCharBubbleSort(SortArray,9,0);
			OutputData[loop_num].R = SortArray[4];						//	�N�Ƨǫᤤ�ȶ�J�������
			//---G�����Ƨ�---
			SortArray[0] = image[loop_num-xsize-1].G;					//	�N������ƶ�JSortArray�}�C
			SortArray[1] = image[loop_num-xsize].G;						//	�N������ƶ�JSortArray�}�C
			SortArray[2] = image[loop_num-xsize+1].G;					//	�N������ƶ�JSortArray�}�C
			SortArray[3] = image[loop_num-1].G;							//	�N������ƶ�JSortArray�}�C
			SortArray[4] = image[loop_num].G;							//	�N������ƶ�JSortArray�}�C
			SortArray[5] = image[loop_num+1].G;							//	�N������ƶ�JSortArray�}�C
			SortArray[6] = image[loop_num+xsize-1].G;					//	�N������ƶ�JSortArray�}�C
			SortArray[7] = image[loop_num+xsize].G;						//	�N������ƶ�JSortArray�}�C
			SortArray[8] = image[loop_num+xsize+1].G;					//	�N������ƶ�JSortArray�}�C
			//qsort(SortArray, 9, sizeof(unsigned char), Compare);		//	�I�sqsort�ƧǨ��(�w�q��stdlib.h)
			UCharBubbleSort(SortArray,9,0);
			OutputData[loop_num].G = SortArray[4];						//	�N�Ƨǫᤤ�ȶ�J�������
			//---B�����Ƨ�---
			SortArray[0] = image[loop_num-xsize-1].B;					//	�N������ƶ�JSortArray�}�C
			SortArray[1] = image[loop_num-xsize].B;						//	�N������ƶ�JSortArray�}�C
			SortArray[2] = image[loop_num-xsize+1].B;					//	�N������ƶ�JSortArray�}�C
			SortArray[3] = image[loop_num-1].B;							//	�N������ƶ�JSortArray�}�C
			SortArray[4] = image[loop_num].B;							//	�N������ƶ�JSortArray�}�C
			SortArray[5] = image[loop_num+1].B;							//	�N������ƶ�JSortArray�}�C
			SortArray[6] = image[loop_num+xsize-1].B;					//	�N������ƶ�JSortArray�}�C
			SortArray[7] = image[loop_num+xsize].B;						//	�N������ƶ�JSortArray�}�C
			SortArray[8] = image[loop_num+xsize+1].B;					//	�N������ƶ�JSortArray�}�C
			//qsort(SortArray, 9, sizeof(unsigned char), Compare);		//	�I�sqsort�ƧǨ��(�w�q��stdlib.h)
			UCharBubbleSort(SortArray,9,0);
			OutputData[loop_num].B = SortArray[4];						//	�N�Ƨǫᤤ�ȶ�J�������
		}																//	����else�ԭz		
	}																	//	����for�j��
    return OutputData;													//	�^�ǹB�⵲�G
}																		//	����MedianFilter33(BMP����3*3�����o�i)�Ƶ{��
BMP24RGB *GaussianBlur33V1(const BMP24RGB *image,const int xsize,const int ysize,const long double StandardDeviation)
//	GaussianBlur33V1(3*3�����o�i)�Ƶ{��
{																		//	�i�JGaussianBlur33V1�Ƶ{��
	#ifdef DebugMode													//	�Y���w�q��DebugMode(�����Ҧ�)
		printf("StandardDeviation�G");									//	���"StandardDeviation�G"�r��
		ShowLongDouble(StandardDeviation);								//	��ܰƵ{���ǤJ��StandardDeviation(������)
	#endif																//	����ifdef�ԭz
	BMP24RGB *OutputData;												//	�ŧiOutputData�����ܼơA�O���Ϲ���ƹB�⵲�G
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData���аO����j�p
	if (OutputData == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz 
	long double Gaussian00 = NormalDistribution2D(0,0,StandardDeviation);
	//	�I�sNormalDistribution2D�Ƶ{���p�Ⱚ���G������(x=0,y=0,�`�A�������зǰ��t�m=StandardDeviation)
	long double Gaussian01 = NormalDistribution2D(0,1,StandardDeviation);
	//	�I�sNormalDistribution2D�Ƶ{���p�Ⱚ���G������(x=0,y=1,�`�A�������зǰ��t�m=StandardDeviation)�AGaussian01�PGaussian10�ۦP�A�����Эp��
	long double Gaussian11 = NormalDistribution2D(1,1,StandardDeviation);
	//	�I�sNormalDistribution2D�Ƶ{���p�Ⱚ���G������(x=1,y=1,�`�A�������зǰ��t�m=StandardDeviation)
	long double weighting = Gaussian00 + 4 * Gaussian01 + 4 * Gaussian11;
	//	�p���v����
	long long int loop_num;												//	�ŧiloop_num�ϰ��ܼƨѰj��ϥ�
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧ǭp��Ϲ�����
	{																	//	�i�Jfor�j��
		if( (loop_num < xsize) || ( (loop_num % xsize) == 0) || ( ((loop_num + 1) % xsize) == 0) || (loop_num >= (xsize*(ysize-1))))
		//	�˴�����I����
		{																//	�i�Jif�ԭz
			OutputData[loop_num].R = image[loop_num].R;					//	����I���B�z
			OutputData[loop_num].G = image[loop_num].G;					//	����I���B�z
			OutputData[loop_num].B = image[loop_num].B;					//	����I���B�z
		}																//	����if�ԭz
		else															//	�Y�D����I����
		{																//	�i�Jelse�ԭz
			OutputData[loop_num].R = (
				image[loop_num+xsize-1].R	* Gaussian11 + image[loop_num+xsize].R	* Gaussian01 + image[loop_num+xsize+1].R	* Gaussian11 +
				image[loop_num-1].R 		* Gaussian01 + image[loop_num].R		* Gaussian00 + image[loop_num+1].R 			* Gaussian01 +
				image[loop_num-xsize-1].R	* Gaussian11 + image[loop_num-xsize].R	* Gaussian01 + image[loop_num-xsize+1].R	* Gaussian11
				) / weighting;											//	�����o�i�p��
			OutputData[loop_num].G = (
				image[loop_num+xsize-1].G	* Gaussian11 + image[loop_num+xsize].G	* Gaussian01 + image[loop_num+xsize+1].G	* Gaussian11 +
				image[loop_num-1].G 		* Gaussian01 + image[loop_num].G		* Gaussian00 + image[loop_num+1].G 			* Gaussian01 +
				image[loop_num-xsize-1].G	* Gaussian11 + image[loop_num-xsize].G	* Gaussian01 + image[loop_num-xsize+1].G	* Gaussian11
				) / weighting;											//	�����o�i�p��
			OutputData[loop_num].B = (
				image[loop_num+xsize-1].B	* Gaussian11 + image[loop_num+xsize].B	* Gaussian01 + image[loop_num+xsize+1].B	* Gaussian11 +
				image[loop_num-1].B 		* Gaussian01 + image[loop_num].B		* Gaussian00 + image[loop_num+1].B 			* Gaussian01 +
				image[loop_num-xsize-1].B	* Gaussian11 + image[loop_num-xsize].B	* Gaussian01 + image[loop_num-xsize+1].B	* Gaussian11
				) / weighting;											//	�����o�i�p��
		}																//	����else�ԭz
	}																	//	����for�j��
    return OutputData;													//	�^�ǹB�⵲�G
}																		//	����GaussianBlur33V1�Ƶ{��
BMP24RGB *GaussianBlur33V2(const BMP24RGB *image,const int xsize,const int ysize,const long double StandardDeviation)
//	GaussianBlur33V2(3*3�����o�i)�Ƶ{��
{																		//	�i�JGaussianBlur33V2�Ƶ{��
	long double Mask[9];												//	�ŧiMask�}�C
	Mask[6] = NormalDistribution2D(-1,1,StandardDeviation);		Mask[7] = NormalDistribution2D(0,1,StandardDeviation);	Mask[8] = NormalDistribution2D(1,1,StandardDeviation);
	//	���wMask�B�n�ƭ�
	Mask[3] = NormalDistribution2D(-1,0,StandardDeviation);		Mask[4] = NormalDistribution2D(0,0,StandardDeviation);	Mask[5] = NormalDistribution2D(1,0,StandardDeviation);
	//	���wMask�B�n�ƭ�
	Mask[0] = NormalDistribution2D(-1,-1,StandardDeviation);	Mask[1] = NormalDistribution2D(0,-1,StandardDeviation);	Mask[2] = NormalDistribution2D(1,-1,StandardDeviation);
	//	���wMask�B�n�ƭ�
    return BmpConvolution33(image, xsize, ysize, Mask);					//	�I�sBmpConvolution33�Ƶ{���p��æ^�ǹB�⵲�G
}																		//	����GaussianBlur33V2�Ƶ{��
BMP24RGB *GaussianBlur(const int MaskSize, const BMP24RGB *image,const int xsize,const int ysize,const long double StandardDeviation)
//	GaussianBlur(�����o�i)�Ƶ{��
{																		//	�i�JGaussianBlur�Ƶ{��
	long double *Mask;													//	�ŧiMask����
	Mask = (long double*)malloc(MaskSize * MaskSize * sizeof(long double));
	//	�t�mMask���аO����j�p
	int loop_num1 = 0;													//	�ŧiloop_num1�ܼƥΩ�j��p�ơA�ó]�w��l�Ȭ�0
	int loop_num2 = 0;													//	�ŧiloop_num2�ܼƥΩ�j��p�ơA�ó]�w��l�Ȭ�0
	for(loop_num1 = -floor(MaskSize/2); loop_num1 <= floor(MaskSize/2); loop_num1 ++)
	//	�Hfor�j��ͦ�Mask�v��
	{																	//	�i�Jfor�j��
		for(loop_num2 = -floor(MaskSize/2); loop_num2 <= floor(MaskSize/2); loop_num2 ++)
		//	�Hfor�j��ͦ�Mask�v��
		{																//	�i�Jfor�j��
			Mask[(int)((loop_num1 + floor(MaskSize/2)) * MaskSize + (loop_num2 + floor(MaskSize/2)))] = 
				NormalDistribution2D((long double) loop_num2, (long double) loop_num1, StandardDeviation);
			//	�p��Mask�v��
		}																//	����for�j��
	}																	//	����for�j��
	return BmpConvolution(MaskSize, image, xsize, ysize, Mask);			//	�I�sBmpConvolution33�Ƶ{���p��æ^�ǹB�⵲�G
}																		//	����GaussianBlur�Ƶ{��
BMP24RGB *GaussianFigure2D(const int xsize,const int ysize,const long double StandardDeviation)
//	GaussianFigure2D(�G��������ƹϧΥͦ�)�Ƶ{��
{																		//	�i�JGaussianFigure2D(�G��������ƹϧΥͦ�)�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData�����ܼơA�O���Ϲ���ƹB�⵲�G
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData���аO����j�p
	if (OutputData == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz 
	int Centerx,Centery;												//	�ŧiCenterx, Centery�O���Ϲ����߮y��
	Centerx = xsize / 2;												//	�p��Centerx�ƭȬ��Ϲ��e��/2
	Centery = ysize / 2;												//	�p��Centery�ƭȬ��Ϲ��e��/2
	long double NormalizeNumber;										//	�ŧiNormalizeNumber(���W�ưѼ�)
	NormalizeNumber = (long double) 127.0 / NormalDistribution2D(0,0,StandardDeviation);
	//	�p�⥿�W�ưѼơA�Ω�N�G�������Ϲ������I���W�Ƭ�255
	int loop_num1, loop_num2;											//	�ŧiloop_num1, loop_num2�ϰ��ܼƨѰj��ϥ�
	for(loop_num1 = 0; loop_num1 < xsize; loop_num1 ++)					//	�H�j��̧ǳB�z����
	{																	//	�i�Jfor�j��
		for(loop_num2 = 0; loop_num2 < ysize; loop_num2 ++)				//	�H�j��̧ǳB�z����
		{																//	�i�Jfor�j��
			long double Data = 
			NormalDistribution2D(fabs(Centerx - loop_num1), fabs(Centery - loop_num2), StandardDeviation) * NormalizeNumber + 128;
			//	�p��Ϲ������Ȩå��W��
			OutputData[ loop_num2 * xsize + loop_num1 ].R = Data;		//	�g�JR���
			OutputData[ loop_num2 * xsize + loop_num1 ].G = Data;		//	�g�JG���
			OutputData[ loop_num2 * xsize + loop_num1 ].B = Data;		//	�g�JB���
		}																//	����for�j��
	}																	//	����for�j��
	return OutputData;													//	�^�ǤG�������Ϲ��ͦ����G
}																		//	����GaussianFigure2D(�G��������ƹϧΥͦ�)�Ƶ{��
long double NormalDistribution2D(long double xlocation,long double ylocation,long double StandardDeviation)
//	NormalDistribution2D(�G���`�A�����p��)�Ƶ{��
{																		//	�i�JNormalDistribution2D�Ƶ{��
	return pow(M_E,-(pow(xlocation,2) + pow(ylocation,2)) / (2 * pow(StandardDeviation,2)))/(2 * M_PI * pow(StandardDeviation,2));
}																		//	����NormalDistribution2D�Ƶ{��
BMP24RGB *ImageOCR(const BMP24RGB *image,const int xsize,const int ysize)
//	ImageOCR(�v��OCR)�Ƶ{��
{																		//	�i�JImageOCR(�v��OCR)�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData�����ܼơA�O���Ϲ���ƹB�⵲�G
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData���аO����j�p
	if (OutputData == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz
	//***��l��OutputData���и��***
	long long int loop_num;												//	�ŧiloop_num�ϰ��ܼƨѰj��ϥ�
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧Ǫ�l��OutputData�Ϲ�����
	{																	//	�i�Jfor�j��
		OutputData[loop_num].R = 128;									//	�]�w������l��
		OutputData[loop_num].G = 128;									//	�]�w������l��
		OutputData[loop_num].B = 128;									//	�]�w������l��
	}																	//	����for�j��
	bool XArray[1700];													//	�ŧiXArray���L�ܼư}�C
	bool YArray[2340];													//	�ŧiYArray���L�ܼư}�C
	//***��l�ƥ��L�ܼư}�C***
	for(loop_num = 0; loop_num < 1700; loop_num++)						//	�Hfor�j���l��XArray���L�ܼư}�C
	{																	//	�i�Jfor�j��
		XArray[loop_num] = false;										//	�Nfalse��JXArray���L�ܼư}�C
	}																	//	����for�j��
	for(loop_num = 0; loop_num < 2340; loop_num++)						//	�Hfor�j���l��YArray���L�ܼư}�C
	{																	//	�i�Jfor�j��
		YArray[loop_num] = false;										//	�Nfalse��JYArray���L�ܼư}�C
	}																	//	����for�j��
	//***�������yOCR�Ϲ�***
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧Ǳ��y�Ϲ�����
	{																	//	�i�Jfor�j��
		//---������ɹ����I(�Nindex�ഫ���G���y��)---
		int PixelLocationX;												//	�ŧiPixelLocationX�A�O�������I���Ϲ��G���y�Ф���X��V��m
		int PixelLocationY;												//	�ŧiPixelLocationY�A�O�������I���Ϲ��G���y�Ф���Y��V��m
		PixelLocationX = loop_num % xsize;								//	�p��PixelLocationX
		PixelLocationY = floor(loop_num / xsize);						//	�p��PixelLocationY
		if( (PixelLocationX < 150) || (PixelLocationX > (xsize - 150)) || (PixelLocationY < 150) || (PixelLocationY > (ysize - 150)))
		//	�˴�����I����(�����I�P��ɳ̵u�Z���Y�p��150)
		{																//	�i�Jif�ԭz
			
		}																//	����if�ԭz
		else															//	�Y�D����I����
		{																//	�i�Jelse�ԭz
			if( (image[loop_num].R == 0) || (image[loop_num].G == 0) || (image[loop_num].B == 0) )
			//	�YR�BG�BB�����ȥ��@��0(�i�ର��r)
			{															//	�i�Jif�ԭz
				YArray[PixelLocationY] = true;							//	�N���L�ܼƧאּtrue
			}															//	����if�ԭz
		}																//	����else�ԭz
	}																	//	����for�j��	
	//***�������yOCR�Ϲ�***
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧Ǳ��y�Ϲ�����
	{																	//	�i�Jfor�j��
		int PixelLocationX;												//	�ŧiPixelLocationX�A�O�������I���Ϲ��G���y�Ф���X��V��m
		int PixelLocationY;												//	�ŧiPixelLocationY�A�O�������I���Ϲ��G���y�Ф���Y��V��m
		PixelLocationX = loop_num % xsize;								//	�p��PixelLocationX
		PixelLocationY = floor(loop_num / xsize);						//	�p��PixelLocationY
		if( (PixelLocationX < 150) || (PixelLocationX > (xsize - 150)) || (PixelLocationY < 150) || (PixelLocationY > (ysize - 150)))
		//	�˴�����I����(�����I�P��ɳ̵u�Z���Y�p��150)
		{																//	�i�Jif�ԭz
			
		}																//	����if�ԭz
		else															//	�Y�D����I����
		{																//	�i�Jelse�ԭz
			if( (image[loop_num].R == 0) || (image[loop_num].G == 0) || (image[loop_num].B == 0) )
			//	�YR�BG�BB�����ȥ��@��0(�i�ର��r)
			{															//	�i�Jif�ԭz
				YArray[PixelLocationY] = true;							//	�N���L�ܼƧאּtrue
			}															//	����if�ԭz
		}																//	����else�ԭz
	}																	//	����for�j��	
	//---��X���y���G---
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧Ǫ�l��OutputData�Ϲ�����
	{																	//	�i�Jfor�j��
		int PixelLocationX;												//	�ŧiPixelLocationX�A�O�������I���Ϲ��G���y�Ф���X��V��m
		int PixelLocationY;												//	�ŧiPixelLocationY�A�O�������I���Ϲ��G���y�Ф���Y��V��m
		PixelLocationX = loop_num % xsize;								//	�p��PixelLocationX
		PixelLocationY = floor(loop_num / xsize);						//	�p��PixelLocationY
		if( (XArray[PixelLocationX] == true) && (YArray[PixelLocationY] == true))
		{
			OutputData[loop_num].R = image[loop_num].R;								
			OutputData[loop_num].G = image[loop_num].G;								
			OutputData[loop_num].B = image[loop_num].B;								
		}
	}																	//	����for�j��
	return OutputData;
	#ifdef DebugMode													//	�Y���w�q��DebugMode(�����Ҧ�)
	//---��ܱ��y���G---
	printf("OCR test\n");
	bool temp;
	int CountNum,CountNum2;
	/*temp = XArray[0];
	CountNum=0;
	CountNum2=0;
	printf("XArray:\n%d:",(int)temp);
	for(loop_num = 0; loop_num < 1700; loop_num++)						//	�Hfor�j���l��XArray���L�ܼư}�C
	{																	//	�i�Jfor�j��
		if(XArray[loop_num] == temp)
		{
			CountNum++;
			CountNum2++;
		}
		else
		{
			temp = XArray[loop_num];
			printf("%d(%d)\n%d:",CountNum,CountNum2,(int)temp);
			CountNum=1;
		}
	}																	//	����for�j��
	printf("%d",CountNum);*/
	temp = YArray[0];
	CountNum=0;
	CountNum2=0;
	printf("\nYArray:\n%d:",(int)temp);
	for(loop_num = 0; loop_num < 2340; loop_num++)						//	�Hfor�j���l��YArray���L�ܼư}�C
	{																	//	�i�Jfor�j��
		if(YArray[loop_num] == temp)
		{
			CountNum++;
			CountNum2++;
		}
		else
		{
			temp = YArray[loop_num];
			printf("%d(%d)\n%d:",CountNum,ysize-CountNum2,(int)temp);
			CountNum=1;
		}
	}																	//	����for�j��
	printf("%d",CountNum);
	#endif																//	����ifdef�ԭz
}																		//	����ImageOCR(�v��OCR)�Ƶ{��
BMP24RGB *BMP24RGBGradient(const BMP24RGB *image,const int xsize,const int ysize)
//	BMP24RGBGradient(BMP�Ϥ���Ʊ�׭p��)�Ƶ{��
{																		//	�i�JBMP24RGBGradient(BMP�Ϥ���Ʊ�׭p��)�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData�����ܼơA�O���Ϲ���ƹB�⵲�G
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData���аO����j�p
	if (OutputData == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz 
	long long int loop_num;												//	�ŧiloop_num�ϰ��ܼƨѰj��ϥ�
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧ǭp��Ϲ��������
	{																	//	�i�Jfor�j��
		if( (loop_num < xsize) || ( (loop_num % xsize) == 0) || ( ((loop_num + 1) % xsize) == 0) || (loop_num >= (xsize*(ysize-1))))
		//	�˴�����I����
		{																//	�i�Jif�ԭz
			OutputData[loop_num].R = image[loop_num].R;					//	����I���B�z
			OutputData[loop_num].G = image[loop_num].G;					//	����I���B�z
			OutputData[loop_num].B = image[loop_num].B;					//	����I���B�z
		}																//	����if�ԭz
		else															//	�Y�D����I����
		{																//	�i�Jelse�ԭz
			//***�p��R�����������***
			int Gx = 0, Gy = 0;											//	�ŧi��׭p�⵲�GGx�BGy�A�õ��w��l�Ȭ�0
			Gx = (
				image[loop_num+xsize-1].R	* (-1) + image[loop_num+xsize].R	* 0 + image[loop_num+xsize+1].R	* 1 +
				image[loop_num-1].R 		* (-1) + image[loop_num].R			* 0 + image[loop_num+1].R 		* 1 +
				image[loop_num-xsize-1].R	* (-1) + image[loop_num-xsize].R	* 0 + image[loop_num-xsize+1].R	* 1
				);														//	Gx�p��
			Gy = (
				image[loop_num+xsize-1].R	* (-1) + image[loop_num+xsize].R	* (-1) + image[loop_num+xsize+1].R	* (-1) +
				image[loop_num-1].R 		*   0  + image[loop_num].R			*   0  + image[loop_num+1].R 		*   0  +
				image[loop_num-xsize-1].R	*   1  + image[loop_num-xsize].R	*   1  + image[loop_num-xsize+1].R	*   1
				);														//	Gy�p��
			long double Magnitude, Direction;							//	�ŧiMagnitude�PDirection�ܼưO����פj�p�P��V
			Magnitude = sqrt(pow(Gx, 2) + pow(Gy, 2));					//	�p��Magnitude
			if((Gx > 0) && (Gy >= 0)) 									//	�YGx�j��0�BGy�j�󵥩�0
			{															//	�i�Jif�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI);
				//	�p���פ�V(Direction)�вĤ@�H��
			}															//	����if�ԭz
			else if(Gx < 0)												//	�YGx�p��0										
			{															//	�i�Jelse if�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI) + (long double)180;
				//	�p���פ�V(Direction)�вĤG�H���B�ĤT�H��
			}															//	����else if�ԭz
			else if( (Gx > 0) && (Gy < 0) )								//	�YGx�j��0�BGy�p��0
			{															//	�i�Jelse if�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI) + (long double)360;
				//	�p���פ�V(Direction)�вĥ|�H��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy > 0) )							//	�YGx��0�BGy�j��0
			{															//	�i�Jelse if�ԭz
				Direction = (long double)90;							//	��׬�90��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy < 0) )							//	�YGx��0�BGy�p��0
			{															//	�i�Jelse if�ԭz
				Direction = (long double)270;							//	��׬�270��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy == 0) )							//	�YGx��0�BGy����0
			{															//	�i�Jelse if�ԭz
				Direction = 0;											//	��פ�V���w�q
			}															//	����else if�ԭz
			
			OutputData[loop_num].R = (Magnitude > 255)?255:(Magnitude < 0)?0:(unsigned char)Magnitude;
			//	�N�p�⵲�G��J�������
			
			//***�p��G�����������***
			Gx = (
				image[loop_num+xsize-1].G	* (-1) + image[loop_num+xsize].G	* 0 + image[loop_num+xsize+1].G	* 1 +
				image[loop_num-1].G 		* (-1) + image[loop_num].G			* 0 + image[loop_num+1].G 		* 1 +
				image[loop_num-xsize-1].G	* (-1) + image[loop_num-xsize].G	* 0 + image[loop_num-xsize+1].G	* 1
				);														//	Gx�p��
			Gy = (
				image[loop_num+xsize-1].G	* (-1) + image[loop_num+xsize].G	* (-1) + image[loop_num+xsize+1].G	* (-1) +
				image[loop_num-1].G 		*   0  + image[loop_num].G			*   0  + image[loop_num+1].G 		*   0  +
				image[loop_num-xsize-1].G	*   1  + image[loop_num-xsize].G	*   1  + image[loop_num-xsize+1].G	*   1
				);														//	Gy�p��
			Magnitude = sqrt(pow(Gx, 2) + pow(Gy, 2));					//	�p��Magnitude
			if((Gx > 0) && (Gy >= 0)) 									//	�YGx�j��0�BGy�j�󵥩�0
			{															//	�i�Jif�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI);
				//	�p���פ�V(Direction)�вĤ@�H��
			}															//	����if�ԭz
			else if(Gx < 0)												//	�YGx�p��0										
			{															//	�i�Jelse if�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI) + (long double)180;
				//	�p���פ�V(Direction)�вĤG�H���B�ĤT�H��
			}															//	����else if�ԭz
			else if( (Gx > 0) && (Gy < 0) )								//	�YGx�j��0�BGy�p��0
			{															//	�i�Jelse if�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI) + (long double)360;
				//	�p���פ�V(Direction)�вĥ|�H��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy > 0) )							//	�YGx��0�BGy�j��0
			{															//	�i�Jelse if�ԭz
				Direction = (long double)90;							//	��׬�90��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy < 0) )							//	�YGx��0�BGy�p��0
			{															//	�i�Jelse if�ԭz
				Direction = (long double)270;							//	��׬�270��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy == 0) )							//	�YGx��0�BGy����0
			{															//	�i�Jelse if�ԭz
				Direction = 0;											//	��פ�V���w�q
			}															//	����else if�ԭz
			
			OutputData[loop_num].G = (Magnitude > 255)?255:(Magnitude < 0)?0:(unsigned char)Magnitude;
			//	�N�p�⵲�G��J�������
			
			//***�p��B�����������***
			Gx = (
				image[loop_num+xsize-1].B	* (-1) + image[loop_num+xsize].B	* 0 + image[loop_num+xsize+1].B	* 1 +
				image[loop_num-1].B 		* (-1) + image[loop_num].B			* 0 + image[loop_num+1].B 		* 1 +
				image[loop_num-xsize-1].B	* (-1) + image[loop_num-xsize].B	* 0 + image[loop_num-xsize+1].B	* 1
				);														//	Gx�p��
			Gy = (
				image[loop_num+xsize-1].B	* (-1) + image[loop_num+xsize].B	* (-1) + image[loop_num+xsize+1].B	* (-1) +
				image[loop_num-1].B 		*   0  + image[loop_num].B			*   0  + image[loop_num+1].B 		*   0  +
				image[loop_num-xsize-1].B	*   1  + image[loop_num-xsize].B	*   1  + image[loop_num-xsize+1].B	*   1
				);														//	Gy�p��
			Magnitude = sqrt(pow(Gx, 2) + pow(Gy, 2));					//	�p��Magnitude
			if((Gx > 0) && (Gy >= 0)) 									//	�YGx�j��0�BGy�j�󵥩�0
			{															//	�i�Jif�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI);
				//	�p���פ�V(Direction)�вĤ@�H��
			}															//	����if�ԭz
			else if(Gx < 0)												//	�YGx�p��0										
			{															//	�i�Jelse if�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI) + (long double)180;
				//	�p���פ�V(Direction)�вĤG�H���B�ĤT�H��
			}															//	����else if�ԭz
			else if( (Gx > 0) && (Gy < 0) )								//	�YGx�j��0�BGy�p��0
			{															//	�i�Jelse if�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI) + (long double)360;
				//	�p���פ�V(Direction)�вĥ|�H��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy > 0) )							//	�YGx��0�BGy�j��0
			{															//	�i�Jelse if�ԭz
				Direction = (long double)90;							//	��׬�90��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy < 0) )							//	�YGx��0�BGy�p��0
			{															//	�i�Jelse if�ԭz
				Direction = (long double)270;							//	��׬�270��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy == 0) )							//	�YGx��0�BGy����0
			{															//	�i�Jelse if�ԭz
				Direction = 0;											//	��פ�V���w�q
			}															//	����else if�ԭz
			
			OutputData[loop_num].B = (Magnitude > 255)?255:(Magnitude < 0)?0:(unsigned char)Magnitude;
			//	�N�p�⵲�G��J�������
			
		}																//	����else�ԭz		
	}																	//	����for�j��
    return OutputData;													//	�^�ǹB�⵲�G
}																		//	����BMP24RGBGradient(BMP�Ϥ���Ʊ�׭p��)�Ƶ{��
BMP24RGB *BMP24RGBSobelEdge(const BMP24RGB *image,const int xsize,const int ysize)
//	BMP24RGBSobelEdge(��������l��t����)�Ƶ{��
{																		//	�i�JBMP24RGBSobelEdge(��������l��t����)�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData�����ܼơA�O���Ϲ���ƹB�⵲�G
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData���аO����j�p
	if (OutputData == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz 
	long long int loop_num;												//	�ŧiloop_num�ϰ��ܼƨѰj��ϥ�
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧ǭp��Ϲ��������
	{																	//	�i�Jfor�j��
		if( (loop_num < xsize) || ( (loop_num % xsize) == 0) || ( ((loop_num + 1) % xsize) == 0) || (loop_num >= (xsize*(ysize-1))))
		//	�˴�����I����
		{																//	�i�Jif�ԭz
			OutputData[loop_num].R = image[loop_num].R;					//	����I���B�z
			OutputData[loop_num].G = image[loop_num].G;					//	����I���B�z
			OutputData[loop_num].B = image[loop_num].B;					//	����I���B�z
		}																//	����if�ԭz
		else															//	�Y�D����I����
		{																//	�i�Jelse�ԭz
			//***�p��R�����������***
			int Gx = 0, Gy = 0;											//	�ŧi��׭p�⵲�GGx�BGy�A�õ��w��l�Ȭ�0
			Gx = (
				image[loop_num+xsize-1].R	* (-1) + image[loop_num+xsize].R	* 0 + image[loop_num+xsize+1].R	* 1 +
				image[loop_num-1].R 		* (-2) + image[loop_num].R			* 0 + image[loop_num+1].R 		* 2 +
				image[loop_num-xsize-1].R	* (-1) + image[loop_num-xsize].R	* 0 + image[loop_num-xsize+1].R	* 1
				);														//	Gx�p��
			Gy = (
				image[loop_num+xsize-1].R	* (-1) + image[loop_num+xsize].R	* (-2) + image[loop_num+xsize+1].R	* (-1) +
				image[loop_num-1].R 		*   0  + image[loop_num].R			*   0  + image[loop_num+1].R 		*   0  +
				image[loop_num-xsize-1].R	*   1  + image[loop_num-xsize].R	*   2  + image[loop_num-xsize+1].R	*   1
				);														//	Gy�p��
			long double Magnitude, Direction;							//	�ŧiMagnitude�PDirection�ܼưO����פj�p�P��V
			Magnitude = sqrt(pow(Gx, 2) + pow(Gy, 2));					//	�p��Magnitude
			if((Gx > 0) && (Gy >= 0)) 									//	�YGx�j��0�BGy�j�󵥩�0
			{															//	�i�Jif�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI);
				//	�p���פ�V(Direction)�вĤ@�H��
			}															//	����if�ԭz
			else if(Gx < 0)												//	�YGx�p��0										
			{															//	�i�Jelse if�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI) + (long double)180;
				//	�p���פ�V(Direction)�вĤG�H���B�ĤT�H��
			}															//	����else if�ԭz
			else if( (Gx > 0) && (Gy < 0) )								//	�YGx�j��0�BGy�p��0
			{															//	�i�Jelse if�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI) + (long double)360;
				//	�p���פ�V(Direction)�вĥ|�H��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy > 0) )							//	�YGx��0�BGy�j��0
			{															//	�i�Jelse if�ԭz
				Direction = (long double)90;							//	��׬�90��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy < 0) )							//	�YGx��0�BGy�p��0
			{															//	�i�Jelse if�ԭz
				Direction = (long double)270;							//	��׬�270��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy == 0) )							//	�YGx��0�BGy����0
			{															//	�i�Jelse if�ԭz
				Direction = 0;											//	��פ�V���w�q
			}															//	����else if�ԭz
			
			OutputData[loop_num].R = (Magnitude > 255)?255:(Magnitude < 0)?0:(unsigned char)Magnitude;
			//	�N�p�⵲�G��J�������
			
			//***�p��G�����������***
			Gx = (
				image[loop_num+xsize-1].G	* (-1) + image[loop_num+xsize].G	* 0 + image[loop_num+xsize+1].G	* 1 +
				image[loop_num-1].G 		* (-2) + image[loop_num].G			* 0 + image[loop_num+1].G 		* 2 +
				image[loop_num-xsize-1].G	* (-1) + image[loop_num-xsize].G	* 0 + image[loop_num-xsize+1].G	* 1
				);														//	Gx�p��
			Gy = (
				image[loop_num+xsize-1].G	* (-1) + image[loop_num+xsize].G	* (-2) + image[loop_num+xsize+1].G	* (-1) +
				image[loop_num-1].G 		*   0  + image[loop_num].G			*   0  + image[loop_num+1].G 		*   0  +
				image[loop_num-xsize-1].G	*   1  + image[loop_num-xsize].G	*   2  + image[loop_num-xsize+1].G	*   1
				);														//	Gy�p��
			Magnitude = sqrt(pow(Gx, 2) + pow(Gy, 2));					//	�p��Magnitude
			if((Gx > 0) && (Gy >= 0)) 									//	�YGx�j��0�BGy�j�󵥩�0
			{															//	�i�Jif�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI);
				//	�p���פ�V(Direction)�вĤ@�H��
			}															//	����if�ԭz
			else if(Gx < 0)												//	�YGx�p��0										
			{															//	�i�Jelse if�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI) + (long double)180;
				//	�p���פ�V(Direction)�вĤG�H���B�ĤT�H��
			}															//	����else if�ԭz
			else if( (Gx > 0) && (Gy < 0) )								//	�YGx�j��0�BGy�p��0
			{															//	�i�Jelse if�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI) + (long double)360;
				//	�p���פ�V(Direction)�вĥ|�H��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy > 0) )							//	�YGx��0�BGy�j��0
			{															//	�i�Jelse if�ԭz
				Direction = (long double)90;							//	��׬�90��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy < 0) )							//	�YGx��0�BGy�p��0
			{															//	�i�Jelse if�ԭz
				Direction = (long double)270;							//	��׬�270��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy == 0) )							//	�YGx��0�BGy����0
			{															//	�i�Jelse if�ԭz
				Direction = 0;											//	��פ�V���w�q
			}															//	����else if�ԭz
			
			OutputData[loop_num].G = (Magnitude > 255)?255:(Magnitude < 0)?0:(unsigned char)Magnitude;
			//	�N�p�⵲�G��J�������
			
			//***�p��B�����������***
			Gx = (
				image[loop_num+xsize-1].B	* (-1) + image[loop_num+xsize].B	* 0 + image[loop_num+xsize+1].B	* 1 +
				image[loop_num-1].B 		* (-2) + image[loop_num].B			* 0 + image[loop_num+1].B 		* 2 +
				image[loop_num-xsize-1].B	* (-1) + image[loop_num-xsize].B	* 0 + image[loop_num-xsize+1].B	* 1
				);														//	Gx�p��
			Gy = (
				image[loop_num+xsize-1].B	* (-1) + image[loop_num+xsize].B	* (-2) + image[loop_num+xsize+1].B	* (-1) +
				image[loop_num-1].B 		*   0  + image[loop_num].B			*   0  + image[loop_num+1].B 		*   0  +
				image[loop_num-xsize-1].B	*   1  + image[loop_num-xsize].B	*   2  + image[loop_num-xsize+1].B	*   1
				);														//	Gy�p��
			Magnitude = sqrt(pow(Gx, 2) + pow(Gy, 2));					//	�p��Magnitude
			if((Gx > 0) && (Gy >= 0)) 									//	�YGx�j��0�BGy�j�󵥩�0
			{															//	�i�Jif�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI);
				//	�p���פ�V(Direction)�вĤ@�H��
			}															//	����if�ԭz
			else if(Gx < 0)												//	�YGx�p��0										
			{															//	�i�Jelse if�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI) + (long double)180;
				//	�p���פ�V(Direction)�вĤG�H���B�ĤT�H��
			}															//	����else if�ԭz
			else if( (Gx > 0) && (Gy < 0) )								//	�YGx�j��0�BGy�p��0
			{															//	�i�Jelse if�ԭz
				Direction = atan((long double)Gy / (long double)Gx) * ( 180 / M_PI) + (long double)360;
				//	�p���פ�V(Direction)�вĥ|�H��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy > 0) )							//	�YGx��0�BGy�j��0
			{															//	�i�Jelse if�ԭz
				Direction = (long double)90;							//	��׬�90��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy < 0) )							//	�YGx��0�BGy�p��0
			{															//	�i�Jelse if�ԭz
				Direction = (long double)270;							//	��׬�270��
			}															//	����else if�ԭz
			else if( (Gx == 0) && (Gy == 0) )							//	�YGx��0�BGy����0
			{															//	�i�Jelse if�ԭz
				Direction = 0;											//	��פ�V���w�q
			}															//	����else if�ԭz
			
			OutputData[loop_num].B = (Magnitude > 255)?255:(Magnitude < 0)?0:(unsigned char)Magnitude;
			//	�N�p�⵲�G��J�������
			
		}																//	����else�ԭz		
	}																	//	����for�j��
    return OutputData;													//	�^�ǹB�⵲�G
}																		//	����BMP24RGBSobelEdge(��������l��t����)�Ƶ{��
BMP24RGB *RGBHistogramEqualization(const BMP24RGB *image,const int xsize,const int ysize)
//	RGBHistogramEqualization(RGB�Ƕ��v������ϵ���)�Ƶ{��
{																		//	�i�JRGBHistogramEqualization(RGB�Ƕ��v������ϵ���)�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData�����ܼơA�O���Ϲ���ƹB�⵲�G
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData���аO����j�p
	if (OutputData == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz
	//***��l��OutputData���и��***
	long long int loop_num;												//	�ŧiloop_num�ϰ��ܼƨѰj��ϥ�
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧Ǫ�l��OutputData�Ϲ�����
	{																	//	�i�Jfor�j��
		OutputData[loop_num].R = 0;										//	�]�w������l��
		OutputData[loop_num].G = 0;										//	�]�w������l��
		OutputData[loop_num].B = 0;										//	�]�w������l��
	}																	//	����for�j��
	long long int CountPixel[256];										//	�ŧiCountPixel�}�C�έp�U�����ȥX�{����
	//***�Hfor�j��̧Ǫ�l��CountPixel�έp�Ȭ�0***
	for(loop_num = 0; loop_num < 256; loop_num++)						//	�Hfor�j���l��CountPixel�έp�Ȭ�0
	{																	//	�i�Jfor�j��
		CountPixel[loop_num] = 0;										//	��l��CountPixel�έp�Ȭ�0
	}																	//	����for�j��
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧ǭp��Ϲ�����
	{																	//	�i�Jfor�j��
		CountPixel[image[loop_num].R] = CountPixel[image[loop_num].R] + 1;
		//	�p��R�����ȥX�{����
	}																	//	����for�j��
	unsigned long long int PDF[256],CDF[256];							//	�ŧiPDF�PCDF�}�C�A�p��ӧO�����Ⱦ��v�P�֭p���v
	for(loop_num = 0; loop_num < 256; loop_num++)						//	�Hfor�j��̧ǭp��PDF
	{																	//	�i�Jfor�j��
		PDF[loop_num] = CountPixel[loop_num];							//	�p�⹳����PDF
	}																	//	����for�j��
	//system("pause");
	CDF[0] = PDF[0];													//	��J�����Ȭ�0��CDF
	for(loop_num = 1; loop_num < 256; loop_num++)						//	�Hfor�j��̧ǭp��CDF
	{																	//	�i�Jfor�j��
		CDF[loop_num] = CDF[loop_num - 1] + PDF[loop_num];				//	�p�⹳����CDF
	}																	//	����for�j��
	unsigned char ResultPixel[256];										//	�ŧiResultPixel�}�C�O��HistogramEqualization�ṳ����
	for(loop_num = 0; loop_num < 256; loop_num++)						//	�Hfor�j��̧�HistogramEqualization�ṳ����
	{																	//	�i�Jfor�j��
		ResultPixel[loop_num] = CDF[loop_num] * 255 / (xsize * ysize);	//	�p��HistogramEqualization�ṳ����
	}																	//	����for�j��
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j���X���G��OutputData
	{																	//	�i�Jfor�j��
		OutputData[loop_num].R = ResultPixel[image[loop_num].R];		//	��X���G��OutputData
	}																	//	����for�j��
	
	//***�Hfor�j��̧Ǫ�l��CountPixel�έp�Ȭ�0***
	for(loop_num = 0; loop_num < 256; loop_num++)						//	�Hfor�j���l��CountPixel�έp�Ȭ�0
	{																	//	�i�Jfor�j��
		CountPixel[loop_num] = 0;										//	��l��CountPixel�έp�Ȭ�0
	}																	//	����for�j��
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧ǭp��Ϲ�����
	{																	//	�i�Jfor�j��
		CountPixel[image[loop_num].G] = CountPixel[image[loop_num].G] + 1;
		//	�p��G�����ȥX�{����
	}																	//	����for�j��
	for(loop_num = 0; loop_num < 256; loop_num++)						//	�Hfor�j��̧ǭp��PDF
	{																	//	�i�Jfor�j��
		PDF[loop_num] = CountPixel[loop_num];							//	�p�⹳����PDF
	}																	//	����for�j��
	CDF[0] = PDF[0];													//	��J�����Ȭ�0��CDF
	for(loop_num = 1; loop_num < 256; loop_num++)						//	�Hfor�j��̧ǭp��CDF
	{																	//	�i�Jfor�j��
		CDF[loop_num] = CDF[loop_num - 1] + PDF[loop_num];				//	�p�⹳����CDF
	}																	//	����for�j��
	for(loop_num = 0; loop_num < 256; loop_num++)						//	�Hfor�j��̧�HistogramEqualization�ṳ����
	{																	//	�i�Jfor�j��
		ResultPixel[loop_num] = CDF[loop_num] * 255 / (xsize * ysize);	//	�p��HistogramEqualization�ṳ����
	}																	//	����for�j��
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j���X���G��OutputData
	{																	//	�i�Jfor�j��
		OutputData[loop_num].G = ResultPixel[image[loop_num].G];		//	��X���G��OutputData
	}																	//	����for�j��
	
	//***�Hfor�j��̧Ǫ�l��CountPixel�έp�Ȭ�0***
	for(loop_num = 0; loop_num < 256; loop_num++)						//	�Hfor�j���l��CountPixel�έp�Ȭ�0
	{																	//	�i�Jfor�j��
		CountPixel[loop_num] = 0;										//	��l��CountPixel�έp�Ȭ�0
	}																	//	����for�j��
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧ǭp��Ϲ�����
	{																	//	�i�Jfor�j��
		CountPixel[image[loop_num].B] = CountPixel[image[loop_num].B] + 1;
		//	�p��B�����ȥX�{����
	}																	//	����for�j��
	for(loop_num = 0; loop_num < 256; loop_num++)						//	�Hfor�j��̧ǭp��PDF
	{																	//	�i�Jfor�j��
		PDF[loop_num] = CountPixel[loop_num];							//	�p�⹳����PDF
	}																	//	����for�j��
	CDF[0] = PDF[0];													//	��J�����Ȭ�0��CDF
	for(loop_num = 1; loop_num < 256; loop_num++)						//	�Hfor�j��̧ǭp��CDF
	{																	//	�i�Jfor�j��
		CDF[loop_num] = CDF[loop_num - 1] + PDF[loop_num];				//	�p�⹳����CDF
	}																	//	����for�j��
	for(loop_num = 0; loop_num < 256; loop_num++)						//	�Hfor�j��̧�HistogramEqualization�ṳ����
	{																	//	�i�Jfor�j��
		ResultPixel[loop_num] = CDF[loop_num] * 255 / (xsize * ysize);	//	�p��HistogramEqualization�ṳ����
	}																	//	����for�j��
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j���X���G��OutputData
	{																	//	�i�Jfor�j��
		OutputData[loop_num].B = ResultPixel[image[loop_num].B];		//	��X���G��OutputData
	}																	//	����for�j��
	return OutputData;													//	�^��HistogramEqualization�B�⵲�G
}																		//	����RGBHistogramEqualization(RGB�Ƕ��v������ϵ���)�Ƶ{��
BMP24RGB *BMPHaarWavelet(const BMP24RGB *image,const int xsize,const int ysize, const char mode)
//	BMPHaarWavelet(BMP����Haar�p�i�o�i)�Ƶ{��
{																		//	�i�JBMPHaarWavelet�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData�����ܼơA�O���Ϲ���ƹB�⵲�G
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData���аO����j�p
	if (OutputData == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz 
	long long int loop_num;												//	�ŧiloop_num�ϰ��ܼƨѰj��ϥ�
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧ǭp��Ϲ�����
	{																	//	�i�Jfor�j��
		if( (loop_num < xsize) || ( (loop_num % xsize) == 0) || ( ((loop_num + 1) % xsize) == 0) || (loop_num >= (xsize*(ysize-1))))
		//	�˴�����I����
		{																//	�i�Jif�ԭz
			OutputData[loop_num].R = image[loop_num].R;					//	����I���B�z
			OutputData[loop_num].G = image[loop_num].G;					//	����I���B�z
			OutputData[loop_num].B = image[loop_num].B;					//	����I���B�z
		}																//	����if�ԭz
		else															//	�Y�D����I����
		{																//	�i�Jelse�ԭz
			if(mode==HorizontalHighPass)								//	�Ymode���������q�Ҧ�
			{															//	�i�Jif�ԭz
				OutputData[loop_num].R = abs(
					image[loop_num-1].R 	* (-1) + image[loop_num].R		* 0 + image[loop_num+1].R 	* 1
					);													//	�������q�Ҧ��p��
				OutputData[loop_num].G = abs(
					image[loop_num-1].G 	* (-1) + image[loop_num].G		* 0 + image[loop_num+1].G 	* 1
					);													//	�������q�Ҧ��p��
				OutputData[loop_num].B = abs(
					image[loop_num-1].B 	* (-1) + image[loop_num].B		* 0 + image[loop_num+1].B 	* 1
					);													//	�������q�Ҧ��p��
			}															//	����if�ԭz
			else if(mode==HorizontalLowPass)							//	�Ymode�������C�q�Ҧ�
			{															//	�i�Jelse if�ԭz
				OutputData[loop_num].R = (
					image[loop_num-1].R 	* 1 + image[loop_num].R		* 0 + image[loop_num+1].R 	* 1
					) / 2;												//	�����C�q�Ҧ��p��
				OutputData[loop_num].G = (
					image[loop_num-1].G 	* 1 + image[loop_num].G		* 0 + image[loop_num+1].G 	* 1
					) / 2;												//	�����C�q�Ҧ��p��
				OutputData[loop_num].B = (
					image[loop_num-1].B 	* 1 + image[loop_num].B		* 0 + image[loop_num+1].B 	* 1
					) / 2;												//	�����C�q�Ҧ��p��
			}															//	����else if�ԭz
			else if(mode==VerticalHighPass)								//	�Ymode���������q�Ҧ�
			{															//	�i�Jelse if�ԭz
				OutputData[loop_num].R = abs(
								image[loop_num+xsize].R	* (-1) +
								image[loop_num].R		* 0    +
								image[loop_num-xsize].R	* 1
					);													//	�������q�Ҧ��p��
				OutputData[loop_num].G = abs(
								image[loop_num+xsize].G	* (-1) +
								image[loop_num].G		* 0    +
								image[loop_num-xsize].G	* 1
					);													//	�������q�Ҧ��p��
				OutputData[loop_num].B = abs(
								image[loop_num+xsize].B	* (-1) +
								image[loop_num].B		* 0    +
								image[loop_num-xsize].B	* 1
					);													//	�������q�Ҧ��p��
			}															//	����else if�ԭz
			else if(mode==VerticalLowPass)								//	�Ymode�������C�q�Ҧ�
			{															//	�i�Jelse if�ԭz
				OutputData[loop_num].R = (
								image[loop_num+xsize].R	* 1 +
								image[loop_num].R		* 0 +
								image[loop_num-xsize].R	* 1
					) / 2;												//	�����C�q�Ҧ��p��
				OutputData[loop_num].G = (
								image[loop_num+xsize].G	* 1 +
								image[loop_num].G		* 0 +
								image[loop_num-xsize].G	* 1
					) / 2;												//	�����C�q�Ҧ��p��
				OutputData[loop_num].B = (
								image[loop_num+xsize].B	* 1 +
								image[loop_num].B		* 0 +
								image[loop_num-xsize].B	* 1
					) / 2;												//	�����C�q�Ҧ��p��
			}															//	����else if�ԭz
		}																//	����else�ԭz
	}																	//	����for�j��
    return OutputData;													//	�^�ǹB�⵲�G
}																		//	����BMPHaarWavelet�Ƶ{��
BMP24RGB *BMPHaarWavelet2(const BMP24RGB *image,const int xsize,const int ysize, const char mode)
//	BMPHaarWavelet2(BMP���ɤG��Haar�p�i�o�i)�Ƶ{��
{																		//	�i�JBMPHaarWavelet2�Ƶ{��
	BMP24RGB *OutputData;												//	�ŧiOutputData�����ܼơA�O���Ϲ���ƹB�⵲�G
	OutputData = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputData���аO����j�p
	if (OutputData == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz 
	if(mode == HighHigh)												//	�Y�Ҧ���HighHigh
	{																	//	�i�Jif�ԭz
		OutputData = BMPHaarWavelet(BMPHaarWavelet(image,xsize,ysize,HorizontalHighPass),xsize,ysize,VerticalHighPass);
		//	�I�sBMPHaarWavelet�Ƶ{��HorizontalHighPass�Ҧ��A�A�I�sBMPHaarWavelet�Ƶ{��VerticalHighPass�Ҧ�
	}																	//	����if�ԭz
	else if(mode == HighLow)											//	�Y�Ҧ���HighLow
	{																	//	�i�Jelse if�ԭz
		OutputData = BMPHaarWavelet(BMPHaarWavelet(image,xsize,ysize,HorizontalHighPass),xsize,ysize,VerticalLowPass);
		//	�I�sBMPHaarWavelet�Ƶ{��HorizontalHighPass�Ҧ��A�A�I�sBMPHaarWavelet�Ƶ{��VerticalLowPass�Ҧ�
	}																	//	����else if�ԭz
	else if(mode == LowHigh)											//	�Y�Ҧ���LowHigh
	{																	//	�i�Jelse if�ԭz
		OutputData = BMPHaarWavelet(BMPHaarWavelet(image,xsize,ysize,HorizontalLowPass),xsize,ysize,VerticalHighPass);
		//	�I�sBMPHaarWavelet�Ƶ{��HorizontalLowPass�Ҧ��A�A�I�sBMPHaarWavelet�Ƶ{��VerticalHighPass�Ҧ�
	}																	//	����else if�ԭz
	else if(mode == LowLow)												//	�Y�Ҧ���LowLow
	{																	//	�i�Jelse if�ԭz
		OutputData = BMPHaarWavelet(BMPHaarWavelet(image,xsize,ysize,HorizontalLowPass),xsize,ysize,VerticalLowPass);
		//	�I�sBMPHaarWavelet�Ƶ{��HorizontalLowPass�Ҧ��A�A�I�sBMPHaarWavelet�Ƶ{��VerticalLowPass�Ҧ�
	}																	//	����else if�ԭz
    else if(mode == (HighHigh|HighLow) )								//	�Y�Ҧ���HighHigh�PHighLow�V�M
	{																	//	�i�Jelse if�ԭz
		OutputData = BMP24RGB2or(BMPHaarWavelet(BMPHaarWavelet(image,xsize,ysize,HorizontalHighPass),xsize,ysize,VerticalHighPass),
								 BMPHaarWavelet(BMPHaarWavelet(image,xsize,ysize,HorizontalHighPass),xsize,ysize,VerticalLowPass),
								 xsize,ysize);
		//	�NHighHigh���G�PHighLow���G�V�X(or�B��)
	}																	//	����else if�ԭz
	else if(mode == (HighHigh|LowHigh) )								//	�Y�Ҧ���HighHigh�PLowHigh�V�M
	{																	//	�i�Jelse if�ԭz
		OutputData = BMP24RGB2or(BMPHaarWavelet(BMPHaarWavelet(image,xsize,ysize,HorizontalHighPass),xsize,ysize,VerticalHighPass),
								 BMPHaarWavelet(BMPHaarWavelet(image,xsize,ysize,HorizontalLowPass),xsize,ysize,VerticalHighPass),
								 xsize,ysize);
		//	�NHighHigh���G�PLowHigh���G�V�X(or�B��)
	}																	//	����else if�ԭz
	else if(mode == (HighLow|LowHigh) )									//	�Y�Ҧ���HighLow�PLowHigh�V�M
	{																	//	�i�Jelse if�ԭz
		OutputData = BMP24RGB2or(BMPHaarWavelet(BMPHaarWavelet(image,xsize,ysize,HorizontalHighPass),xsize,ysize,VerticalLowPass),
								 BMPHaarWavelet(BMPHaarWavelet(image,xsize,ysize,HorizontalLowPass),xsize,ysize,VerticalHighPass),
								 xsize,ysize);
		//	�NHighLow���G�PLowHigh���G�V�X(or�B��)
	}																	//	����else if�ԭz
	else if(mode == (HighHigh|HighLow|LowHigh) )						//	�Y�Ҧ���HighHigh�BHighLow�PLowHigh�V�M
	{																	//	�i�Jelse if�ԭz
		OutputData = BMP24RGB2or(BMP24RGB2or(BMPHaarWavelet(BMPHaarWavelet(image,xsize,ysize,HorizontalHighPass),xsize,ysize,VerticalHighPass),
								 BMPHaarWavelet(BMPHaarWavelet(image,xsize,ysize,HorizontalHighPass),xsize,ysize,VerticalLowPass),
								 xsize,ysize),
								 BMPHaarWavelet(BMPHaarWavelet(image,xsize,ysize,HorizontalLowPass),xsize,ysize,VerticalHighPass),
								 xsize,ysize);
		//	�NHighHigh���G�BHighLow���G�PLowHigh���G�V�X(or�B��)
	}																	//	����else if�ԭz
	return OutputData;													//	�^�ǹB�⵲�G
}																		//	����BMPHaarWavelet2�Ƶ{��
HSV *HSVHistogramEqualization(const HSV *image,const int xsize,const int ysize)
//	HSVHistogramEqualization(HSV�v������ϵ���)�Ƶ{��
{																		//	�i�JHSVHistogramEqualization(HSV�v������ϵ���)�Ƶ{��
	HSV *OutputData;													//	�ŧiOutputData�����ܼơA�O���Ϲ���ƹB�⵲�G
	OutputData = (HSV*)malloc(xsize * ysize * sizeof(HSV));				//	�t�mOutputData���аO����j�p
	if (OutputData == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz
	//***��l��OutputData���и��***
	long long int loop_num;												//	�ŧiloop_num�ϰ��ܼƨѰj��ϥ�
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧Ǫ�l��OutputData�Ϲ�����
	{																	//	�i�Jfor�j��
		OutputData[loop_num].H = image[loop_num].H;						//	�]�w������l��
		OutputData[loop_num].S = image[loop_num].S;						//	�]�w������l��
		OutputData[loop_num].V = 0;										//	�]�w������l��
	}																	//	����for�j��
	long long int CountPixel[256];										//	�ŧiCountPixel�}�C�έp�U�����ȥX�{����
	//***�Hfor�j��̧Ǫ�l��CountPixel�έp�Ȭ�0***
	for(loop_num = 0; loop_num < 256; loop_num++)						//	�Hfor�j���l��CountPixel�έp�Ȭ�0
	{																	//	�i�Jfor�j��
		CountPixel[loop_num] = 0;										//	��l��CountPixel�έp�Ȭ�0
	}																	//	����for�j��
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧ǭp��Ϲ�����
	{																	//	�i�Jfor�j��
		CountPixel[(int)(image[loop_num].V)] = CountPixel[(int)(image[loop_num].V)] + 1;
		//	�p��Value�ȥX�{����
	}																	//	����for�j��
	unsigned long long int PDF[256],CDF[256];							//	�ŧiPDF�PCDF�}�C�A�p��ӧO�����Ⱦ��v�P�֭p���v
	for(loop_num = 0; loop_num < 256; loop_num++)						//	�Hfor�j��̧ǭp��PDF
	{																	//	�i�Jfor�j��
		PDF[loop_num] = CountPixel[loop_num];							//	�p�⹳����PDF
	}																	//	����for�j��
	//system("pause");
	CDF[0] = PDF[0];													//	��J�����Ȭ�0��CDF
	for(loop_num = 1; loop_num < 256; loop_num++)						//	�Hfor�j��̧ǭp��CDF
	{																	//	�i�Jfor�j��
		CDF[loop_num] = CDF[loop_num - 1] + PDF[loop_num];				//	�p�⹳����CDF
	}																	//	����for�j��
	unsigned char ResultPixel[256];										//	�ŧiResultPixel�}�C�O��HistogramEqualization�ṳ����
	for(loop_num = 0; loop_num < 256; loop_num++)						//	�Hfor�j��̧�HistogramEqualization�ṳ����
	{																	//	�i�Jfor�j��
		ResultPixel[loop_num] = CDF[loop_num] * 255 / (xsize * ysize);	//	�p��HistogramEqualization�ṳ����
	}																	//	����for�j��
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j���X���G��OutputData
	{																	//	�i�Jfor�j��
		OutputData[loop_num].V = ResultPixel[(int)(image[loop_num].V)];	//	��X���G��OutputData
	}																	//	����for�j��
	return OutputData;													//	�^��HistogramEqualization�B�⵲�G
}																		//	����HSVHistogramEqualization(HSV�v������ϵ���)�Ƶ{��
BMP24RGB *HueToBMP24RGB(const HSV *image,const int xsize,const int ysize)
//	HueToBMP24RGB�Ƶ{��
{																		//	�i�JHueToBMP24RGB�Ƶ{��
	BMP24RGB *OutputImage;												//	�ŧiOutputImage�����ܼơA�O����X�Ϲ����
	OutputImage = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));
	//	�t�mOutputImage���аO����j�p
	if (OutputImage == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz 
	long long int LoopNumber;											//	�ŧiLoopNumber�ϰ��ܼƨѰj��ϥ�
	for(LoopNumber = 0; LoopNumber <(xsize * ysize); LoopNumber++)		//	�Hfor�j��̧ǳB�z�Ϲ�����
	{																	//	�i�Jfor�j��
		OutputImage[LoopNumber].R = image[LoopNumber].H * (long double)255 / (long double)360;
		//	��J�v�����
		OutputImage[LoopNumber].G = image[LoopNumber].H * (long double)255 / (long double)360;
		//	��J�v�����
		OutputImage[LoopNumber].B = image[LoopNumber].H * (long double)255 / (long double)360;
		//	��J�v�����
	}																	//	����for�j��
    return OutputImage;													//	�^�ǿ�X�Ϲ�
}																		//	����HueToBMP24RGB�Ƶ{��
BMP24RGB *SaturationToBMP24RGB(const HSV *image,const int xsize,const int ysize)
//	SaturationToBMP24RGB�Ƶ{��
{																		//	�i�JSaturationToBMP24RGB�Ƶ{��
	BMP24RGB *OutputImage;												//	�ŧiOutputImage�����ܼơA�O����X�Ϲ����
	OutputImage = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));
	//	�t�mOutputImage���аO����j�p
	if (OutputImage == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz 
	long long int LoopNumber;											//	�ŧiLoopNumber�ϰ��ܼƨѰj��ϥ�
	for(LoopNumber = 0; LoopNumber <(xsize * ysize); LoopNumber++)		//	�Hfor�j��̧ǳB�z�Ϲ�����
	{																	//	�i�Jfor�j��
		OutputImage[LoopNumber].R = image[LoopNumber].S * (long double)255;
		//	��J�v�����
		OutputImage[LoopNumber].G = image[LoopNumber].S * (long double)255;
		//	��J�v�����
		OutputImage[LoopNumber].B = image[LoopNumber].S * (long double)255;
		//	��J�v�����
	}																	//	����for�j��
    return OutputImage;													//	�^�ǿ�X�Ϲ�
}																		//	����SaturationToBMP24RGB�Ƶ{��
BMP24RGB *ValueToBMP24RGB(const HSV *image,const int xsize,const int ysize)
//	ValueToBMP24RGB�Ƶ{��
{																		//	�i�JValueToBMP24RGB�Ƶ{��
	BMP24RGB *OutputImage;												//	�ŧiOutputImage�����ܼơA�O����X�Ϲ����
	OutputImage = (BMP24RGB*)malloc(xsize * ysize * sizeof(BMP24RGB));	//	�t�mOutputImage���аO����j�p
	if (OutputImage == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz 
	long long int LoopNumber;											//	�ŧiLoopNumber�ϰ��ܼƨѰj��ϥ�
	for(LoopNumber = 0; LoopNumber <(xsize * ysize); LoopNumber++)		//	�Hfor�j��̧ǳB�z�Ϲ�����
	{																	//	�i�Jfor�j��
		OutputImage[LoopNumber].R = image[LoopNumber].V;				//	��J�v�����
		OutputImage[LoopNumber].G = image[LoopNumber].V;				//	��J�v�����
		OutputImage[LoopNumber].B = image[LoopNumber].V;				//	��J�v�����
	}																	//	����for�j��
    return OutputImage;													//	�^�ǿ�X�Ϲ�
}																		//	����ValueToBMP24RGB�Ƶ{��
HSV *HSVSkin(const HSV *image,const int xsize,const int ysize)
//	HSVSkin(HSV�v���ֽ��L�o)�Ƶ{��
{																		//	�i�JHSVSkin(HSV�v���ֽ��L�o)�Ƶ{��
	HSV *OutputData;													//	�ŧiOutputData�����ܼơA�O���Ϲ���ƹB�⵲�G
	OutputData = (HSV*)malloc(xsize * ysize * sizeof(HSV));				//	�t�mOutputData���аO����j�p
	if (OutputData == NULL) 											//	�Y�إ߼v���Ŷ����� 
	{																	//	�i�Jif�ԭz 
		printf("�O������t���~!");										//	���"�O������t���~!" 
		return NULL;													//	�Ǧ^NULL�A�õ����{�� 
	}																	//	����if�ԭz
	//***��l��OutputData���и��***
	long long int loop_num;												//	�ŧiloop_num�ϰ��ܼƨѰj��ϥ�
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧Ǫ�l��OutputData�Ϲ�����
	{																	//	�i�Jfor�j��
		OutputData[loop_num].H = 0;										//	�]�w������l��
		OutputData[loop_num].S = 0;										//	�]�w������l��
		OutputData[loop_num].V = 0;										//	�]�w������l��
	}																	//	����for�j��
	//***�L�o�ֽ������I***
	for(loop_num = 0; loop_num <(xsize * ysize); loop_num++)			//	�Hfor�j��̧Ǫ�l��OutputData�Ϲ�����
	{																	//	�i�Jfor�j��
		long double HData,SData;										//	�ŧiHData�PSData������ׯB�I�ơA�O�������I��H�PS��T
		HData = image[loop_num].H;										//	��JHData
		SData = image[loop_num].S;										//	��JSData
		if( ( HData >= (long double)15.0 ) &&							//	�YHData�j�󵥩�15
			( HData <= (long double)50.0 ) && 							//	�BHData�p�󵥩�50
			( SData >= (long double)0.23 ) && 							//	�BSData�j�󵥩�0.23
			( SData >= (long double)0.68 ) )							//	�BSData�p�󵥩�0.68
		{																//	�i�Jif�ԭz
			OutputData[loop_num].H = image[loop_num].H;					//	��J�칳����
			OutputData[loop_num].S = image[loop_num].S;					//	��J�칳����
			OutputData[loop_num].V = image[loop_num].V;					//	��J�칳����
		}																//	����if�ԭz
		else															//	�Y������m��T���b�d��
		{																//	�i�Jelse�ԭz
			OutputData[loop_num].H = image[loop_num].H;					//	��J�칳����
			OutputData[loop_num].S = image[loop_num].S;					//	��J�칳����
			OutputData[loop_num].V = image[loop_num].V * (long double)0.3;
			//	��J���Value
		}																//	����else�ԭz
	}																	//	����for�j��
	return OutputData;													//	�^�ǹL�o���G
}																		//	����HSVSkin(HSV�v���ֽ��L�o)�Ƶ{��

unsigned char BmpFillingByteCalc(const unsigned int xsize)				//	BmpFillingByteCalc(BMP���ɶ�ɦ줸�p��)�Ƶ{��
{																		//	�i�JBmpFillingByteCalc�Ƶ{��
	unsigned char FillingByte;											//	�ŧiFillingByte�O����ɦ줸�խp�⵲�G
	FillingByte = ( xsize % 4);											//	�p���ɦ줸�ռƶq
	return FillingByte;													//	�Ǧ^�p�⵲�G
}																		//	����BmpFillingByteCalc�Ƶ{��
bool FileExistCheck(char *file_name)									//	FileExistCheck(�ɮצs�b�ˬd)�Ƶ{��
{																		//	�i�JFileExistCheck(�ɮצs�b�ˬd)�Ƶ{��
	if( access( file_name, F_OK ) != -1 )								//	�Y�ɮצs�b
	{																	//	�i�Jif�ԭz
    	return True;													//	�Ǧ^True
	} 																	//	����if�ԭz
	else 																//	�Y�ɮפ��s�b
	{																	//	�i�Jelse�ԭz
	    return False;													//	�^��false
	}																	//	����else�ԭz
} 																		//	����FileExistCheck(�ɮצs�b�ˬd)�Ƶ{��
bool FileReadPermissionCheck(const char *file_name)						//	FileReadPermissionCheck(�ɮ�Ū���v���ˬd)�Ƶ{��
{																		//	�i�JFileReadPermissionCheck(�ɮ�Ū���v���ˬd)�Ƶ{��
	if( access( file_name, R_OK ) != -1 )								//	�Y�ɮץiŪ��
	{																	//	�i�Jif�ԭz
    	return True;													//	�Ǧ^True
	} 																	//	����if�ԭz
	else 																//	�Y�ɮפ��iŪ��
	{																	//	�i�Jelse�ԭz
	    return False;													//	�^��false
	}																	//	����else�ԭz
} 																		//	����FileReadPermissionCheck(�ɮ�Ū���v���ˬd)�Ƶ{��
bool FileWritePermissionCheck(const char *file_name)					//	FileWritePermissionCheck(�ɮ׼g�J�v���ˬd)�Ƶ{��
{																		//	�i�JFileWritePermissionCheck(�ɮ׼g�J�v���ˬd)�Ƶ{��
	if( access( file_name, W_OK ) != -1 )								//	�Y�ɮץiŪ��
	{																	//	�i�Jif�ԭz
    	return True;													//	�Ǧ^True
	} 																	//	����if�ԭz
	else 																//	�Y�ɮפ��iŪ��
	{																	//	�i�Jelse�ԭz
	    return False;													//	�^��false
	}																	//	����else�ԭz
} 																		//	����FileWritePermissionCheck(�ɮ׼g�J�v���ˬd)�Ƶ{��

bool FileWrite(const char *file_name,const char *input_str,const char *mode)
//	FileWrite(�ɮ׼g�J)�Ƶ{���A�����r�ɮ׼g�J
//	file_name�����g�J�ɮ��ɦW
// 	input_str�����g�J�ɮפ����ЧΦ��r����
//	mode���g�J�ɮ׼Ҧ��]�w�A�i�ǤJ"w"��"a"�A"w"���s�W/�л\�Ҧ��A"a"���X�R�Ҧ�
//	�^�ǵ��G�G�Y�ɮ׼g�J���\�^��True�A�Y�g�J���Ѧ^��False
{																		//	�i�JFileWrite(�ɮ׼g�J)�Ƶ{��
	FILE *file_point;													//	�ŧi�@file_point���СA�����ɮ�Ū�g
	if (strcmp(mode, "w") != 0 && strcmp(mode, "a") != 0 && strcmp(mode, "w+") != 0 && strcmp(mode, "a+") != 0)
	//	�Ymode�ѼƤ���"w"�礣��"a"�礣��"w+"�礣��"a+"
	{																	//	�i�Jif�ԭz
		printf("FileWrite:mode ERROR!\n");								//	���"FileWrite:mode ERROR!"�ô���
		return False;													//	�^��False�õ����Ƶ{����^
	}																	//	����if�ԭz
	if( strcmp(mode, "a") == 0 || strcmp(mode, "a+") == 0 )				//	�Ymode�ѼƬ�"a"��"a+"(�X�R�Ҧ�)
	{																	//	�i�Jif�ԭz
		if (FileWritePermissionCheck(file_name) == False)				//	�Y�ɮ׵L�k�g�J
		{																//	�i�Jif�ԭz
			printf("FileWrite:permission ERROR!\n");					//	���"FileWrite:permission ERROR!"�ô���
			return False;												//	�^��False�õ����Ƶ{����^
		}																//	����if�ԭz
	}																	//	����if�ԭz
	file_point = fopen(file_name, mode);								//	�Hmode�Ҧ����}�ɮ�
	//	fprintf��fputs�y�k�G�ܤ@�ϥ�
	fprintf(file_point, input_str);										//	�Hfprintf�y�k�g�J�ɮ�
	//fputs(input_str, file_point);										//	�Hfputs�y�k�g�J�ɮ�
	fclose(file_point); 												//	�����ɮ�
	return True;														//	�^��True�õ����Ƶ{����^
}																		//	����FileWrite(�ɮ׼g�J)�Ƶ{��

unsigned char *UCharBubbleSort(	const unsigned char *InputData,
								const unsigned long long int InputDataNum,
								const bool Mode)
//	UCharBubbleSort�Ƶ{��
{																		//	�i�JUCharBubbleSort�Ƶ{��
	unsigned char *OutputData;											//	�ŧiOutputData�O����X���
	OutputData = (unsigned char*)malloc( InputDataNum * sizeof(unsigned char) );
	//	�t�mOutputData��X��ƫ��аO����Ŷ�
	unsigned long long int LoopNumber1,LoopNumber2;						//	�ŧiLoopNumber1�PLoopNumber2�A�Ω�j����榸�ƭp��
	for(LoopNumber1=0;LoopNumber1 < InputDataNum;LoopNumber1++)			//	�H�j��̧�
	{																	//	�i�Jfor�j��
		OutputData[LoopNumber1] = InputData[LoopNumber1];				//	�ƻs��Ʀܿ�X���аO����Ŷ�
	}																	//	����for�j��
	for(LoopNumber2 = 1;LoopNumber2 < InputDataNum;LoopNumber2++)		//	�H�j��̧Ǥ���ƭ�
	{																	//	�i�Jfor�j��
		for(LoopNumber1=0;LoopNumber1 < InputDataNum - LoopNumber2;LoopNumber1++)
		//	�H�j��̧Ǥ���ƭ�
		{																//	�i�Jfor�j��
			if( Mode == 0 )												//	�Y�Ҧ����Ѥp�Ʀܤj
			{															//	�i�Jif�ԭz
				if(OutputData[LoopNumber1] > OutputData[LoopNumber1 + 1])
				//	�Y���j���ƭȦb�e
				{														//	�i�Jif�ԭz
					unsigned char TempNumber;							//	�ŧiTempNumber�Ȧs�ܼ�(�Ω�ƭȥ洫)
					TempNumber = OutputData[LoopNumber1];				//	�ƭȥ洫
					OutputData[LoopNumber1] = OutputData[LoopNumber1 + 1];
					//	�ƭȥ洫
					OutputData[LoopNumber1 + 1] = TempNumber;			//	�ƭȥ洫
				}														//	����if�ԭz
			}															//	����if�ԭz
			else if( Mode == 1 )										//	�Y�Ҧ����Ѥj�Ʀܤp
			{															//	�i�Jelse if�ԭz
				if(OutputData[LoopNumber1] < OutputData[LoopNumber1 + 1])
				//	�Y���p���ƭȦb�e
				{														//	�i�Jif�ԭz
					unsigned char TempNumber;							//	�ŧiTempNumber�Ȧs�ܼ�(�Ω�ƭȥ洫)
					TempNumber = OutputData[LoopNumber1];				//	�ƭȥ洫
					OutputData[LoopNumber1] = OutputData[LoopNumber1 + 1];
					//	�ƭȥ洫
					OutputData[LoopNumber1 + 1] = TempNumber;			//	�ƭȥ洫
				}														//	����if�ԭz
			}															//	����else if�ԭz
		}																//	����for�j��
	}																	//	����for�j��
	return OutputData;													//	�^�ǿ�X���
}																		//	����UCharBubbleSort�Ƶ{��

int Compare(const void *data1,const void *data2)						//	Compare�Ƶ{��
{																		//	�i�JCompare�Ƶ{��
	int *ptr1 = (int*)data1;											//	�ŧi*ptr1��ƫ����ܼ�
	int *ptr2 = (int*)data2;											//	�ŧi*ptr2��ƫ����ܼ�
	if(*ptr1 < *ptr2)													//	�Y*ptr1�ƭȸ��p
	{																	//	�i�Jif�ԭz
		return -1;														//	�Ǧ^-1�A�õ����Ƶ{��
	}																	//	����if�ԭz
	else if(*ptr1 > *ptr2)												//	�Y*ptr1�ƭȸ��j
	{																	//	�i�Jelse if�ԭz
		return 1;														//	�Ǧ^1�A�õ����Ƶ{��
	}																	//	����else if�ԭz
	else																//	�Y*ptr1�P*ptr2�ƭȬ۵�
	{																	//	�i�Jelse�ԭz
		return 0;														//	�Ǧ^0�A�õ����Ƶ{��
	}																	//	����else�ԭz	
}																		//	����Compare�Ƶ{��
unsigned long long int CountCharPointStr(const char *Input_string, const bool Detail)	
//	CountCharPointStr(�p��r�����Ъ���)�Ƶ{���A�p��r������(�r��)����
{																		//	�i�JCountCharPointStr�Ƶ{��
	unsigned long long int count_num = 0;								//	�ŧicount_num�ϰ��ܼơA�ó]�w��l�Ȭ�0
	while (Input_string[count_num] != '\0')								//	�Y�D�r�굲��
	{																	//	�i�Jwhile�ԭz
		if(Detail == True)												//	�YDetail�ѼƬ�True
		{																//	�i�Jif�ԭz
			printf("��%d�Ӧr�����G%c\n",count_num + 1,Input_string[count_num]);
			//	��ܭp�ƲӸ`
		}																//	����if�ԭz
		count_num++;													//	�֥[count_num�ܼ�
    }																	//	����while�ԭz
    return count_num;													//	�^��count_num(�r�����Ъ���)�ܼ�
}																		//	����CountCharPointStr�Ƶ{��
void Show_char_point_str(const char *Input_string)						//	Show_char_point_str(��ܦr������)�Ƶ{��
/*	��ܦr�ꤺ�e
	�ޥΰƵ{���G
		CountCharPointStr(�p��r�����Ъ���)�Ƶ{��
*/
{																		//	�i�JShow_char_point_str�Ƶ{��
	unsigned long long int loop_num = 0;								//	�ŧiloop_num�ϰ��ܼƨѰj��ϥΡA�ó]�w��l�Ȭ�0
	for(loop_num = 0; loop_num < CountCharPointStr(Input_string, False); loop_num++)
	{																	//	�i�Jfor�j��
		printf("%c",Input_string[loop_num]);							//	�̧���ܦr��
	}																	//	����for�j��
}																		//	����Show_char_point_str�Ƶ{��
void ShowUCharPointStr(const unsigned char *InputData,unsigned long long int InputDataLen)
//	ShowUCharPointStr(��ܵL���r������)�Ƶ{��
{																		//	�i�JShowUCharPointStr�Ƶ{��
	unsigned long long int LoopNumber = 0;								//	�ŧiLoopNumber�ܼơA�Ω�j��p��
	for(LoopNumber=0;LoopNumber<InputDataLen;LoopNumber++)				//	�Hfor�j��̧���ܨC������
	{																	//	�i�Jfor�j��
		printf("%u,",InputData[LoopNumber]);							//	��ܵL���r�����Ф��e
	}																	//	����for�j��
}																		//	����ShowUCharPointStr�Ƶ{��
void ShowLongDouble(const long double InputNumber)						//	ShowLongDouble�Ƶ{��
{																		//	�i�JShowLongDouble�Ƶ{��
	int TimesNumber = 308;												//	�ŧiTimesNumber�����(int)�ܼơA�ê�l�Ƭ�308
	long double DisplayNumber;											//	�ŧiDisplayNumber�ܼơA�Ω�O����ܼƭ�
	//***�B�z���t��***
	if(InputNumber < 0)													//	�YInputNumber��J�ƭȬ��t��
	{																	//	�i�Jif�ԭz
		DisplayNumber = (long double)0.0 - InputNumber;					//	��JDisplayNumber�ƭ�
		printf("-");													//	��ܭt��"-"
	}																	//	����if�ԭz
	else																//	�YInputNumber��J�ƭȤ����t��
	{																	//	�i�Jelse�ԭz
		DisplayNumber = InputNumber;									//	��JDisplayNumber�ƭ�
	}																	//	����else�ԭz
	//***�h���e��0***
	char DisplayChar='\0';												//	�ŧiDisplayChar���r��(char)���A�A�ê�l�Ƭ��Ŧr��
	DisplayChar = floor(DisplayNumber/(long double)pow(10,TimesNumber)) - pow(10,1) * floor(DisplayNumber/(long double)pow(10,(TimesNumber + 1)));
	//	���X��ܼƭ�
	while((DisplayChar == 0) && (TimesNumber > 0))						//	�Y�ƭȬ�0�BTimesNumber(����)�j��0(�����Ӧ��)
	{																	//	�i�Jwhile�ԭz
		TimesNumber = TimesNumber - 1;									//	����TimesNumber�ܼ�
		DisplayChar = floor(DisplayNumber/(long double)pow(10,TimesNumber)) - pow(10,1) * floor(DisplayNumber/(long double)pow(10,(TimesNumber + 1)));
		//	���X��ܼƭ�
	}																	//	����while�ԭz
	//***��ܼƭ�***
	int DisplayStartTimes = TimesNumber;								//	�ŧiDisplayStartTimes�����(int)�ܼơA�ΥH�O���_�l��ܼƦr����
	int DisplayDigit;													//	�ŧiDisplayDigit�����(int)�ܼơA�ΥH�O����ܦ��
	if(DisplayStartTimes > 14)											//	�YDisplayStartTimes(�_�l��ܼƦr����)�j��14(�Y����ܼƭ�InputNumber�j��10^14)
	{																	//	�i�Jif�ԭz
		DisplayDigit = DisplayStartTimes;								//	���wDisplayDigit��ܦ�Ƭ��_�l��ܼƦr�����
	}																	//	����if�ԭz
	else																//	�Y����ܼƭ�InputNumber���j��10^14
	{																	//	�i�Jelse�ԭz
		DisplayDigit = 14;												//	���wDisplayDigit��ܦ�Ƭ�14��(���Ħ��)
	}																	//	����else�ԭz
	while(TimesNumber >= DisplayStartTimes - DisplayDigit)				//	
	{																	//	�i�Jwhile�ԭz
		if(TimesNumber == -1)											//	�YTimesNumber(����)��-1��
		{																//	�i�Jif�ԭz
			printf(".");												//	��ܤp���I
		}																//	����if�ԭz
		DisplayChar = floor(DisplayNumber/(long double)pow(10,TimesNumber)) - pow(10,1) * floor(DisplayNumber/(long double)pow(10,(TimesNumber + 1)));
		//	���X��ܼƭ�
		if( (DisplayChar >= 0) && (DisplayChar <= 9) )					//	�Y���X���ƭȤ���0~9����
		{																//	�i�Jif�ԭz
			printf("%d",DisplayChar);									//	��ܼƭ�
		}																//	����if�ԭz
		else															//	�Y���X�ƭȿ��~
		{																//	�i�Jelse�ԭz
			break;														//	����while�j��
		}																//	����else�ԭz
		TimesNumber = TimesNumber - 1;									//	����TimesNumber�ܼ�
	}																	//	����while�ԭz
}																		//	����ShowLongDouble�Ƶ{��

void InitialIMGArrayTest(void)											//	InitialIMGArrayTest�Ƶ{��
{																		//	�i�JInitialIMGArrayTest�Ƶ{��
	BmpWriteV1(ArrayToRAWImage(InitialIMGArray(10,10),10,10),10,10,"TestIMG");
	//	��l�v���إߴ���(����InitialIMGArray�Ƶ{���\��)
}																		//	����InitialIMGArrayTest�Ƶ{��
void BmpReadFilesizeTest(void)											//	BmpReadFilesizeTest�Ƶ{��
{																		//	�i�JBmpReadFilesizeTest�Ƶ{��
	//***���`�I�s�覡***
	printf("BmpReadFilesize�Ƶ{������(�L���ɦW)�G%d\n", BmpReadFilesize("LennaTestBMP",false));
	//	�I�sBmpReadFilesize�Ƶ{�����X"LennaTestBMP"BMP���ɤ��j�p
	printf("BmpReadFilesize�Ƶ{������(�t���ɦW)�G%d\n", BmpReadFilesize("LennaTestBMP.bmp",true));
	//	�I�sBmpReadFilesize�Ƶ{�����X"LennaTestBMP"BMP���ɤ��j�p
	//***�ҥ~���p����***
	printf("BmpReadFilesize�Ƶ{���ҥ~���p����1�G%d\n", BmpReadFilesize("LennaTestBMP.bmp",(int)123));
	//	�H�ҥ~���p�I�s�Ƶ{��
}																		//	����BmpReadFilesizeTest�Ƶ{��
void BmpReadXSizeTest(void)												//	BmpReadXSizeTest�Ƶ{��
{																		//	�i�JBmpReadXSizeTest�Ƶ{��
	BMPIMAGE BMPImage1;													//	�ŧiBMP�v��1(BMPImage1)
	printf("�п�JBMP���ɡG");											//	��ܰT��"�п�JBMP���ɡG"
	scanf("%s",&BMPImage1.FILENAME);									//	�ϥΪ̿�J���ɦW�� 
	bool FileCheck;														//	�ŧiFileCheck���L�ܼơA�ΥH�O���ɮ׬O�_�s�b(�Y�ɮצs�b��true)
	FileCheck = FileExistCheck(BMPImage1.FILENAME);						//	�I�sFileExistCheck�Ƶ{���ˬd�ɮ׬O�_�s�b
	if(FileCheck == false)												//	�Y�ɮפ��s�b
	{																	//	�i�Jif�ԭz
		printf("���ɤ��s�b!");											//	���"���ɤ��s�b!"
		return;															//	�{������ 
	}																	//	����if�ԭz
	BMPImage1.XSIZE = (unsigned int)BmpReadXSize(BMPImage1.FILENAME,false);
	//	Ū����JBMP���ɼe�� 
	if(BMPImage1.XSIZE == -1)											//	�YXSIZE��-1(�N��Ū���ɮץ���)	
	{																	//	�i�Jif�ԭz 
		printf("Ū�����ɤj�p��T����!");								//	���"Ū�����ɤj�p��T����!"
		return;															//	�{������ 
	}																	//	����if�ԭz 
	else																//	�YXSIZE����-1(���`Ū���ɮ�)
	{																	//	�i�Jelse�ԭz
		printf("��J���ɼe�סG%d\n",BMPImage1.XSIZE);					//	��ܿ�J���ɼe�׼ƭ� 
		return;															//	�{������ 
	}																	//	����else�ԭz 
}																		//	����BmpReadXSizeTest�Ƶ{��

void BmpReadYSizeTest(void)												//	BmpReadYSizeTest�Ƶ{��
{																		//	�i�JBmpReadYSizeTest�Ƶ{��
	BMPIMAGE BMPImage1;													//	�ŧiBMP�v��1(BMPImage1)
	printf("�п�JBMP���ɡG");											//	��ܰT��"�п�JBMP���ɡG"
	scanf("%s",&BMPImage1.FILENAME);									//	�ϥΪ̿�J���ɦW�� 
	bool FileCheck;														//	�ŧiFileCheck���L�ܼơA�ΥH�O���ɮ׬O�_�s�b(�Y�ɮצs�b��true)
	FileCheck = FileExistCheck(BMPImage1.FILENAME);						//	�I�sFileExistCheck�Ƶ{���ˬd�ɮ׬O�_�s�b
	if(FileCheck == false)												//	�Y�ɮפ��s�b
	{																	//	�i�Jif�ԭz
		printf("���ɤ��s�b!");											//	���"���ɤ��s�b!"
		return;															//	�{������ 
	}																	//	����if�ԭz
	BMPImage1.YSIZE = (unsigned int)BmpReadYSize(BMPImage1.FILENAME,false);
	//	Ū����JBMP���ɰ��� 
	if(BMPImage1.YSIZE == -1)											//	�YYSIZE��-1(�N��Ū���ɮץ���)	
	{																	//	�i�Jif�ԭz 
		printf("Ū�����ɤj�p��T����!");								//	���"Ū�����ɤj�p��T����!"
		return;															//	�{������ 
	}																	//	����if�ԭz 
	else																//	�YYSIZE����-1(���`Ū���ɮ�)
	{																	//	�i�Jelse�ԭz
		printf("��J���ɰ��סG%d\n",BMPImage1.YSIZE);					//	��ܿ�J���ɰ��׼ƭ� 
		return;															//	�{������ 
	}																	//	����else�ԭz 
}																		//	����BmpReadYSizeTest�Ƶ{��

void BmpReadTest(void)													//	BmpReadTest�Ƶ{��
{																		//	�i�JBmpReadTest�Ƶ{��
	char filename[MAX_PATH]="";											//	�ŧifilename�r��
	printf("�п�JBMP����(ex�Gtest)�G");								//	��ܰT��"�п�JBMP����(ex�Gtest)�G"
	scanf("%s",filename);												//	�ϥΪ̿�J���ɦW�� 
	bool FilenameExtension = false;										//	�]�w�ϥΪ̿�J���ɦW�٤��t���ɦW
	//***�ˬd��J�ɦW�O�_�ť�***
	if(filename == NULL)												//	�Y��Jfilename��NULL
	{																	//	�i�Jif�ԭz
		printf("�ɮ׸��|��J��NULL\n");									//	���"�ɮ׸��|��J��NULL"�ô���
		return;															//	�����Ƶ{��
	}																	//	����if�ԭz
	//***���ɦW���***
	char fname_bmp[MAX_PATH];											//	�ŧi�ɮצW��fname_bmp�}�C�ܼ�(�̦hMAX_PATH�Ӧr��) 
	if(FilenameExtension == false)										//	�Y��J�Ѽ�fname_bmp������ɦW
	{																	//	�i�Jif�ԭz
		sprintf(fname_bmp, "%s.bmp", filename);							//	���ͧ����ɮ׸��|�æs���fname_bmp�}�C
	}																	//	����if�ԭz
	else																//	�Y��J�Ѽ�fname_bmp�w�]�t���ɦW
	{																	//	�i�Jelse�ԭz
		strcpy(fname_bmp,filename);										//	������J�ɦW���|
	}																	//	����else�ԭz
	//***�T�{�ɮצs�b�ΥiŪ��***
	if (FileExistCheck(fname_bmp) == false)								//	�Y�ɮפ��s�b 
	{																	//	�i�Jif�ԭz 
		printf("�ɮפ��s�b�I\n");										//	��ܿ��~�T�� 
		return;															//	�����Ƶ{��
	}																	//	����if�ԭz	 
	if (FileReadPermissionCheck(fname_bmp) == false)					//	�Y�ɮפ��iŪ��
	{																	//	�i�Jif�ԭz 
		printf("Ū���ɮ׿��~�I\n");										//	��ܿ��~�T��
		return;															//	�����Ƶ{��
	}																	//	����if�ԭz
	unsigned int XSIZE,YSIZE;											//	�ŧiXSIZE�PYSIZE�ܼưO�����ɼe�׻P����
	XSIZE = (unsigned int)BmpReadXSize(fname_bmp,true);					//	Ū����JBMP���ɼe��(���|�w�]�t���ɦW) 
	YSIZE = (unsigned int)BmpReadYSize(fname_bmp,true);					//	Ū����JBMP���ɰ���(���|�w�]�t���ɦW) 
	if( (XSIZE == -1) || (YSIZE == -1) )								//	�YXSIZE��YSIZE��-1(�N��Ū���ɮץ���)	
	{																	//	�i�Jif�ԭz 
		printf("Ū�����ɤj�p��T����!");								//	���"Ū�����ɤj�p��T����!"
		return;															//	�����Ƶ{��
	}																	//	����if�ԭz
	else																//	�YXSIZE�PYSIZE�Ҥ���-1(���`Ū���ɮ�)
	{																	//	�i�Jelse�ԭz 
		printf("��J���ɼe�סG%d\n",XSIZE);								//	��ܿ�J���ɼe�׼ƭ� 
		printf("��J���ɰ��סG%d\n",YSIZE);								//	��ܿ�J���ɰ��׼ƭ� 
		printf("��J�v���j�p(Byte)�G%d\n",(size_t)XSIZE * YSIZE * 3);	//	��ܿ�J�v���j�p�ƭ�(Byte) 
		char FILLINGBYTE;												//	�ŧiFILLINGBYTE�O�����ɶ�ɦ줸
		FILLINGBYTE = BmpFillingByteCalc(XSIZE);						//	�I�sBmpFillingByteCalc�Ƶ{���p���R���줸�ռƶq
		unsigned char *IMAGE_DATA;										//	�ŧiIMAGE_DATA�L���r�����ХΥH�O���Ϲ����
		IMAGE_DATA = (unsigned char*)malloc((XSIZE * 3 + FILLINGBYTE) * YSIZE * sizeof(unsigned char));
		//	�p��ëإ߼v���j�p�Ŷ� 
		if (IMAGE_DATA == NULL) 										//	�Y�إ߼v���Ŷ����� 
		{																//	�i�Jif�ԭz 
			printf("�O������t���~!");									//	���"�O������t���~!" 
			return;														//	�����Ƶ{��
		}																//	����if�ԭz 
		else															//	�Y���o�Ϳ��~ 
		{																//	�i�Jelse�ԭz 
			int loop_num = 0;											//	�ŧi�ϰ��ܼ�loop_num�Ѱj��ϥ� 
			for(loop_num=0;loop_num<((XSIZE * 3 + FILLINGBYTE) * YSIZE);loop_num++)
			//	�Hfor�j���l�ƨC�ӹ��� 
			{															//	�i�Jfor�j�� 
				IMAGE_DATA[loop_num]=255;								//	��J�w�]������m�ƭ� 
			}															//	����for�j�� 
			BmpRead(IMAGE_DATA, XSIZE, YSIZE, fname_bmp,true);			//	Ū�����ɸ��
		}																//	����else�ԭz
	}																	//	����else�ԭz
	
}																		//	����BmpReadTest�Ƶ{��
void BmpWriteV2Test(void)												//	BmpWriteV2Test�Ƶ{��
{																		//	�i�JBmpWriteV2Test�Ƶ{��
	printf("�п�JBMP����(ex:test)�G");									//	��ܰT��"�п�JBMP����(ex:test)�G"
	char *FilenameString;												//	�ŧiFilenameString�r�����ХΥH�O���ϥΪ̿�J��Ū��������
	FilenameString = (char*)malloc( MAX_PATH * sizeof(char) );			//	�t�mFilenameString�r�����аO����j�p
	scanf("%s",FilenameString);											//	�ϥΪ̿�J���ɦW�� 
	BMPIMAGE BMPImage1;													//	�ŧiBMP�v��1(BMPImage1)
	BMPImage1 = BmpFileRead(FilenameString,false);						//	�I�sBmpFileRead�Ƶ{��Ū��BMP����
	free(FilenameString);												//	����FilenameString�r�����аO����Ŷ�
	printf("%s\n",BMPImage1.FILENAME);									//	���Ū�����ɤ��ɦW
	
	if(BMPImage1.IMAGE_DATA == NULL)									//	�YŪ��BMP���ɵo�Ϳ��~
	{																	//	�i�Jif�ԭz
		printf("���ɪ�����~!");										//	���"���ɪ�����~!" 
		return;															//	�����{�� 
	}																	//	����if�ԭz
	
	//***BmpWriteV2�Ƶ{������***
	sprintf(BMPImage1.FILENAME, "%s", "BmpWriteV2Test");				//	�]�w�g�J���ɦW��
	BmpWriteV2(BMPImage1);												//	�N���ɼg�J���ɮ�
}																		//	����BmpWriteV2Test�Ƶ{��