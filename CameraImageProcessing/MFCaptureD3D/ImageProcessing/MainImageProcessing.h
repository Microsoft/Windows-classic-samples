/*	�Ʀ�v���B�z�D�禡
	Develop by Jimmy HU <s103360021@gmail.com>
	This program is licensed under GNU General Public License v3.
*/

//-----include header files, �ޤJ���Y��-----
#include "DIPDefine.h"													//	�ޤJ���Y��DIPDefine.h
#include <math.h>														//	�ޤJ���Y��math.h
#include <stdbool.h>													//	�ޤJ���Y��stdbool.h
#include <stdio.h>														//	�ޤJ���Y��stdio.h
#include <stdlib.h>														//	�ޤJ���Y��stdlib.h
#include <string.h>														//	�ޤJ���Y��string.h
#include "..\\unistd.h"													//	�ޤJ���Y��unistd.h
#include "Conversion.h"

//-----funtion declaration, �Ƶ{���ŧi��-----
/*	MainImageProcessing�Ƶ{�����g��y�v���D�n�B�z�y�{�A
	�Ƶ{����J��(�ݳB�z��RGB�v��, �ݳB�zRGB�v�����e��, �ݳB�zRGB�v��������)
*/
void MainImageProcessing(unsigned char* InputImage, unsigned int ImageSizeX, unsigned int ImageSizeY);


/*  BmpReadFilesize�Ƶ{���N��J���|�����ɤj�pŪ�X�öǦ^
	�Ƶ{����J����Ū���j�p�����ɸ��|(const char *���A�r��A����Ū�����ɦW, FilenameExtension���ɦW��T)
	�Ƶ{����X�����ɤj�p(unsigned long���A)
 */
unsigned long BmpReadFilesize(const char *, const bool);				//	�ŧiBMP���ɤj�p(Byte)Ū���Ƶ{��BmpReadFilesize

/*  BmpReadXSize�Ƶ{���N��J���|������xsize(�e��)Ū�X�öǦ^
	�Ƶ{����J����Ū���e�פj�p�����ɸ��|(const char *���A�A����Ū�����ɦW,FilenameExtension���ɦW��T)
	�Ƶ{����X�����ɼe��(unsigned long���A)
 */
unsigned long BmpReadXSize(const char *, const bool);					//	�ŧiBMP����xsize(�e��)Ū���Ƶ{��BmpReadXSize

/*  BmpReadYSize�Ƶ{���N��J���|������ysize(����)Ū�X�öǦ^
	�Ƶ{����J����Ū�����פj�p�����ɸ��|(const char *���A�A����Ū�����ɦW,FilenameExtension���ɦW��T)
	�Ƶ{����X�����ɰ���(unsigned long���A)
 */
unsigned long BmpReadYSize(const char *, const bool);					//	�ŧiBMP����ysize(����)Ū���Ƶ{��BmpReadYSize
/*	BmpRead�Ƶ{���Ω�Ū��BMP����
	�Ƶ{����J��(���s���l���ɸ�Ƥ�unsigned char���A����,��Ū�����ɤ��e��,��Ū�����ɤ�����,��Ū�������ɸ��|,FilenameExtension���ɦW��T)
	�Ƶ{����X�G�Y���QŪ�����ɫh�Ǧ^0�A�Ϥ��Ǧ^-1
 */
char BmpRead(unsigned char*,const int,const int, const char *, const bool);
//	�ŧiBmpRead(BMP����Ū��)�Ƶ{��
/*	BmpFileRead�Ƶ{����XBmpFillingByteCalc(BMP���ɶ�ɦ줸�p��)�Ƶ{���B
	BmpReadFilesize(BMP�����ɮפj�pŪ��)�Ƶ{���B
	BmpReadXSize(BMP�����ɮ׼e��Ū��)�Ƶ{���B
	BmpReadYSize(BMP�����ɮװ���Ū��)�Ƶ{���P
	BmpRead(BMP�����ɮ�Ū��)�Ƶ{�����\��A�Ω�Ū��BMP����
	�Ƶ{����J��(��Ū�������ɸ��|)�A�p�G"test.bmp"
	�Ƶ{����X��BMPIMAGE�v����Ƶ��c(�Ӽv����Ƶ��c�]�t�ɦW(FILENAME)�B
	�Ϲ��e��(XSIZE)�B�Ϲ�����(YSIZE)�B��ɦ줸(FILLINGBYTE)�P�Ϲ����(IMAGE_DATA))
 */
BMPIMAGE BmpFileRead(const char *, const bool);							//	�ŧiBmpFileRead�Ƶ{��
/*	BmpWriteV1�Ƶ{���Ω�g�JBMP����
	�Ƶ{����J��(���g�J���ɤ�unsigned char���A���и��,���g�J���ɤ��e��,���g�J���ɤ�����,���g�J�����ɸ��|)
	�Ƶ{����X�G�Y���Q�g�J���ɫh�Ǧ^0�A�Ϥ��Ǧ^-1
 */
int BmpWriteV1(const unsigned char*,const int,const int,const char*); 	//	�ŧiBmpWriteV1(BMP���ɼg�J)�Ƶ{��
/*	BmpWriteV2�Ƶ{���Ω�g�JBMP����
	���Ƶ{���NBmpWriteV1�Ƶ{������J�ѼƵ��c�ơA�HBMPIMAGE���c���ɸ�ƶǤJ�A���ϥΤ����W����i
	��@�W���I�sBmpWriteV1�Ƶ{���i����ɼg�J
	�Ƶ{����J��(���g�J��BMPIMAGE���c���ɸ��)
	�Ƶ{����X�G�Y���Q�g�J���ɫh�Ǧ^0�A�Ϥ��Ǧ^-1
 */
int BmpWriteV2(const BMPIMAGE); 										//	�ŧiBmpWriteV2(BMP���ɼg�J)�Ƶ{��
/*	ViewBMPImage�Ƶ{���Ω�I�s�Ϥ��˵����}�ҹ���
	�Ƶ{����J�����}���˵������ɵ�����|(�t�XFILE_ROOT_PATH�Φ�������|)
	�Ƶ{����J��void(�L)
 */
void ViewBMPImage(const char *);										//	�ŧiViewBMPImage(BMP�Ϥ��˵�)�Ƶ{��(�HWindows�Ϥ��˵����}��)
/*	InitialIMGArray�Ƶ{���Ω�ͦ�BMP24RGB�����ܼơA�ñN���ƪ�l�Ƭ�0
	�Ƶ{����J��(���ͦ�BMP24RGB�����ܼƤ��Ϲ��e��,���ͦ�BMP24RGB�����ܼƤ��Ϲ�����)
	�Ƶ{����X���ͦ���BMP24RGB�����ܼ�
 */
BMP24RGB *InitialIMGArray(const int, const int);						//	�ŧiInitialIMGArray�Ƶ{��
/*	RAWImageToArray�Ƶ{���N�Ӧ�BMP���ɤ��Ϲ�����ഫ��RGB���A�G���}�C�A
	�ഫ�᪺�@��BMP24RGB���A�G���}�C�N��@�i�v���A�䤤�G
	__________________
	|                |
	|                |
	|                |
	|                |
	|                |
	|                |
	|________________|
	 �����Ĥ@����
	 
 */
BMP24RGB *RGBQUADtoBMP24RGB(const RGBQUAD* InputRGBQUADImage, const int xsize, const int ysize);
RGBQUAD* BMP24RGBtoRGBQUAD(const BMP24RGB* InputBMP24RGBImage, const int xsize, const int ysize);
BMP24RGB *RAWImageToArray(const unsigned char*, const int, const int);	//	�ŧiRAWImageToArray(BMP���ɸ�Ʀܰ}�C�ഫ)�Ƶ{��
/*	ArrayToRAWImage�Ƶ{���Ω�NRGB���A�Ϲ��G���}�C�ഫ�ܲŦXBMP���ɮ榡���Ϲ����(�t��ɦ줸)
	�Ƶ{����J��(RGB���A�Ϲ��G���}�C,�Ϲ��e��,�Ϲ�����)
	�Ƶ{����X���L���r������(unsigned char *)���A�A�ŦXBMP���ɮ榡���Ϲ����(�t��ɦ줸)
 */
unsigned char *ArrayToRAWImage(const BMP24RGB*,const int,const int);	//	�ŧi�}�C��BMP���ɸ���ഫ�Ƶ{��

/*	BMP24RGBToHSV�Ƶ{���Ω�NBMP24RGB���A��RGB��������ഫ��HSV��m�Ŷ�
	�Ƶ{����J��(���ഫ��HSV��BMP24RGB���A�Ϲ����,���ഫ��HSV��BMP24RGB���A�Ϲ��e��,���ഫ��HSV��BMP24RGB���A�Ϲ�����)
	�Ƶ{����X����BMP24RGB��m�Ŷ��ഫ��HSV�������v�����
 */
HSV *BMP24RGBToHSV(const BMP24RGB*,const int,const int);				//	�ŧiBMP24RGB���A��HSV�ഫ�Ƶ{��
/*	HSVToBMP24RGB�Ƶ{���Ω�NHSV���A����������ഫ��BMP24RGB��m�Ŷ�
	�Ƶ{����J��(���ഫ��BMP24RGB��HSV���A�Ϲ����,���ഫ��BMP24RGB��HSV���A�Ϲ��e��,���ഫ��BMP24RGB��HSV���A�Ϲ�����)
	�Ƶ{����X����HSV��m�Ŷ��ഫ��BMP24RGB�������v�����
 */
BMP24RGB *HSVToBMP24RGB(const HSV*,const int,const int);				//	�ŧiBMP24RGB���A��HSV�ഫ�Ƶ{��
/*	ImageDataToTxt�Ƶ{���Ω�N�Ϲ��v����Ƽg�Jtxt��
	�Ƶ{����J��(���g�J��txt�ɮ׸��|,���g�J���Ϲ��v�����,���g�J���Ϲ��v���e��,���g�J���Ϲ��v������)
	�Ƶ{����X�G�Y���Q�g�J�ɮ׫h�Ǧ^true�A�Ϥ��Ǧ^false
	�g�J�ɮ׸���|�Ҧp�U�G
		��0�ӹ���R=175	��0�ӹ���G=255	��0�ӹ���B=92
		��1�ӹ���R=176	��1�ӹ���G=255	��1�ӹ���B=92
		��2�ӹ���R=177	��2�ӹ���G=255	��2�ӹ���B=93
		��3�ӹ���R=178	��3�ӹ���G=255	��3�ӹ���B=93
		��4�ӹ���R=179	��4�ӹ���G=255	��4�ӹ���B=94
		��5�ӹ���R=180	��5�ӹ���G=255	��5�ӹ���B=95
		��6�ӹ���R=181	��6�ӹ���G=255	��6�ӹ���B=95
		��7�ӹ���R=181	��7�ӹ���G=255	��7�ӹ���B=96
		��8�ӹ���R=182	��8�ӹ���G=255	��8�ӹ���B=96
		��9�ӹ���R=183	��9�ӹ���G=255	��9�ӹ���B=97
	�U�@�N�Ƶ{���w�p
 */
bool ImageDataToTxt(const char*,const BMP24RGB*,const int,const int);	//	�ŧiImageDataToTxt(�Ϲ��v����Ƽg�Jtxt��)�Ƶ{��
/*	HSVDataToTxt�Ƶ{���Ω�NHSV���A�v����Ƽg�Jtxt��
	�g�J�ɮ׸���|�Ҧp�U�G
		��0�ӹ���H=89.391197	��0�ӹ���S=0.639216	��0�ӹ���V=255.000000
		��1�ӹ���H=88.985390	��1�ӹ���S=0.639216	��1�ӹ���V=255.000000
		��2�ӹ���H=88.775009	��2�ӹ���S=0.635294	��2�ӹ���V=255.000000
		��3�ӹ���H=88.366875	��3�ӹ���S=0.635294	��3�ӹ���V=255.000000
		��4�ӹ���H=88.151466	��4�ӹ���S=0.631373	��4�ӹ���V=255.000000
		��5�ӹ���H=87.933411	��5�ӹ���S=0.627451	��5�ӹ���V=255.000000
		��6�ӹ���H=87.520569	��6�ӹ���S=0.627451	��6�ӹ���V=255.000000
		��7�ӹ���H=87.712685	��7�ӹ���S=0.623529	��7�ӹ���V=255.000000
		��8�ӹ���H=87.297371	��8�ӹ���S=0.623529	��8�ӹ���V=255.000000
		��9�ӹ���H=87.071434	��9�ӹ���S=0.619608	��9�ӹ���V=255.000000
	�Ƶ{����J��(���g�J��txt�ɮ׸��|,���g�J��HSV���A�v�����,���g�J���Ϲ��v���e��,���g�J���Ϲ��v������)
	�Ƶ{����X�G�Y���Q�g�J�ɮ׫h�Ǧ^true�A�Ϥ��Ǧ^false	
 */
bool HSVDataToTxt(const char*, const HSV*, const int, const int);		//	�ŧiHSVDataToTxt(HSV���A�v����Ƽg�Jtxt��)�Ƶ{��
/*	ImgDifference2�Ƶ{���Ω�����BMP24RGB���A�Ϲ��������t(�۴�)�B��
	�B���k���O�G
	A���@5*5�Ϲ��A������Ʀp�U�G
		-				-
		|	10	20	30	|
		|	40	10	20	|
		|	70	40	50	|
		-				-
	
	B���@5*5�Ϲ��A������Ʀp�U�G
		-				-
		|	5	10	15	|
		|	20	5	10	|
		|	35	20	25	|
		-				-
	
	�h�Ϲ�A-B�i�I�sImgDifference2�A�I�s��k�p�GImgDifference2(A, B, 5, 5);
	�B�⵲�G���G
		-				-
		|	5	10	15	|
		|	20	5	10	|
		|	35	20	25	|
		-				-
	���Ҽ{�۴�t�Ƥ����p�A�i���k�B���������
	���Ƶ{���N�Ϲ�������R�BG�BB�������O�B�z�A�t��k�ۦP
 */
BMP24RGB *ImgDifference2(const BMP24RGB*,const BMP24RGB*,const int,const int);
/*	BMP24RGB2or�Ƶ{���Ω�����BMP24RGB���A�Ϲ�������OR�B��
	���Ƶ{���N�Ϲ�������R�BG�BB�������O�B�z�A�t��k�ۦP
	�Ƶ{����J��(���i��or�B�⤧�ӷ��v��1, ���i��or�B�⤧�ӷ��v��2, �ӷ��v���e��, �ӷ��v������)
	�Ƶ{����X�����湳��or�B��ᤧ���G
 */
BMP24RGB *BMP24RGB2or(const BMP24RGB*,const BMP24RGB*,const int,const int);
//	�ŧiBMP24RGB2or(��BMP24RGB���A�Ϲ����or�B��)�Ƶ{��
/*	BmpToGraylevel�Ƶ{���Ω�NBMP24RGB���A�Ϲ��ର�Ƕ��Ϲ�(Graylevel Image)
	�B���k���O�G
		R = (R + G + B) / 3
		G = (R + G + B) / 3
		B = (R + G + B) / 3
	�Ƶ{����J��(���ഫ�ܦǶ���BMP24RGB���A�Ϲ����, ���ഫ�ܦǶ����Ϲ��e��, ���ഫ�ܦǶ����Ϲ�����)
	�Ƶ{����X���ഫ���Ƕ��ᤧBMP24RGB���A�Ϲ����
 */
BMP24RGB *BmpToGraylevel(const BMP24RGB*, const int, const int);		//	�ŧiBMP�Ϥ������Ƕ��Ƶ{��
/*	BmpConvolution33�Ω�p�⵹�w3*3�B�n�P��J�Ϲ��i��P�n(Convolution)�A
	����T�W�ӻ��A�P�n�L�{�����N�B�n½��A�����Ƶ{�����i��½��A�ȶi��ۭ�
	�|�Ҩӻ��G
		�Y�ǤJ��3*3�B�n��
			--		--
			| 1 1 1	 |
			| 1 1 1	 |
			| 1 1 1	 |
			--		--
		�@�Ϲ�3*3�϶������Ȧp�U�G
		-				-
		|	10	20	30	|
		|	40	10	20	|
		|	70	40	50	|
		-				-
		�p��P�n=(10*1+20*1+30*1+40*1+10*1+20*1+70*1+40*1+50*1)/9(���H�B�n�v���`�M)=290/9=32.2222
		
		3*3�B�n�ǤJ�覡���@�}�C�G
			���]�}�C�W�٬�Mask�A�ƭȳ]�w�|�Ҧp�U�G
			--							--
			| Mask[6] Mask[7] Mask[8]	 |
			| Mask[3] Mask[4] Mask[5]	 |
			| Mask[0] Mask[1] Mask[2]	 |
			--							--
			�ѥ��U���}�l�s����0�A�ѥ��ܥk�A�ѤU�ܤW���W
		
	���Ƶ{���N�Ϲ�������R�BG�BB�������O�B�z�A�t��k�ۦP
	�Ƶ{����J��(���i��Convolution�B�⤧BMP24RGB���A�v��, ���i��Convolution�B�⤧BMP24RGB���A�Ϲ����e��, ���i��Convolution�B�⤧BMP24RGB���A�Ϲ�������, Convolution��Mask)
	�Ƶ{����X������Convolution�B��ᤧ���G
 */
BMP24RGB *BmpConvolution33(const BMP24RGB*,const int,const int,const long double[]);
//	�ŧiBmpConvolution33(�Ϲ�3*3�B�n�P�n)�Ƶ{��
/*	BmpConvolution55�Ω�p�⵹�w5*5�B�n�P��J�Ϲ��i��P�n(Convolution)�A
	����T�W�ӻ��A�P�n�L�{�����N�B�n½��A�����Ƶ{�����i��½��A�ȶi��ۭ�
	�|�Ҩӻ��G
		�Y�ǤJ��5*5�B�n��
			--			--
			| 1 1 1 1 1	 |
			| 1 1 1	1 1	 |
			| 1 1 1	1 1	 |
			| 1 1 1	1 1	 |
			| 1 1 1	1 1	 |
			--			--
		�@�Ϲ�5*5�϶������Ȧp�U�G
		--						--
		|	99	96	82	24	78	 |
		|	9	20	3	28	94	 |
		|	33	35	40	52	66	 |
		|	37	34	27	26	69	 |
		|	29	1	67	31	47	 |
		--						--
		�p��P�n=(	99 * 1 + 96 * 1 + 82 * 1 + 24 * 1 + 78 * 1 + 
					9 * 1 + 20 * 1 + 3 * 1 + 28 * 1 + 94 * 1 + 
					33 * 1 + 35 * 1 + 40 * 1 + 52 * 1 + 66 * 1 + 
					37 * 1 + 34 * 1 + 27 * 1 + 26 * 1 + 69 * 1 + 
					29 * 1 + 1 * 1 + 67 * 1 + 31 * 1 + 47)/25(���H�B�n�v���`�M)=1127 / 25 = 45.08
		
		5*5�B�n�ǤJ�覡���@�}�C�G
			���]�}�C�W�٬�Mask�A�ƭȳ]�w�|�Ҧp�U�G
			--												--
			| Mask[20] Mask[21] Mask[22] Mask[23] Mask[24]	 |
			| Mask[15] Mask[16] Mask[17] Mask[18] Mask[19]	 |
			| Mask[10] Mask[11] Mask[12] Mask[13] Mask[14]	 |
			| Mask[ 5] Mask[ 6] Mask[ 7] Mask[ 8] Mask[ 9]	 |
			| Mask[ 0] Mask[ 1] Mask[ 2] Mask[ 3] Mask[ 4]	 |
			--												--
			�ѥ��U���}�l�s����0�A�ѥ��ܥk�A�ѤU�ܤW���W
			
	���Ƶ{���N�Ϲ�������R�BG�BB�������O�B�z�A�t��k�ۦP
	�Ƶ{����J��(���i��Convolution�B�⤧BMP24RGB���A�v��, ���i��Convolution�B�⤧BMP24RGB���A�Ϲ����e��, ���i��Convolution�B�⤧BMP24RGB���A�Ϲ�������, Convolution��Mask)
	�Ƶ{����X������Convolution�B��ᤧ���G
 */
BMP24RGB *BmpConvolution55(const BMP24RGB*,const int,const int,const long double[]);
//	�ŧiBmpConvolution55(�Ϲ�5*5�B�n�P�n)�Ƶ{��
/*	BmpConvolution77�Ω�p�⵹�w7*7�B�n�P��J�Ϲ��i��P�n(Convolution)�A
	����T�W�ӻ��A�P�n�L�{�����N�B�n½��A�����Ƶ{�����i��½��A�ȶi��ۭ�
	�|�Ҩӻ��G
		�Y�ǤJ��7*7�B�n��
			--			   --
			| 1 1 1 1 1 1 1	|
			| 1 1 1	1 1 1 1	|
			| 1 1 1	1 1 1 1	|
			| 1 1 1	1 1 1 1	|
			| 1 1 1	1 1 1 1	|
			| 1 1 1	1 1 1 1	|
			| 1 1 1	1 1 1 1	|
			--			   --
		�@�Ϲ�7*7�϶������Ȧp�U�G
		--							   --
		|	99	96	82	24	78	20	84	|
		|	9	20	3	28	94	54	43	|
		|	33	35	40	52	66	73	12	|
		|	37	34	27	26	69	41	93	|
		|	29	1	67	31	47	55	34	|
		|	50	109	200	197	140	29	22	|
		|	184	13	238	97	170	253	239	|
		--							   --
		�p��P�n=(	99 * 1 + 96 * 1 + 82 * 1 + 24 * 1 + 78 * 1 + 20 * 1 + 84 * 1 +
					9 * 1 + 20 * 1 + 3 * 1 + 28 * 1 + 94 * 1 + 54 * 1 + 43 * 1 +
					33 * 1 + 35 * 1 + 40 * 1 + 52 * 1 + 66 * 1 + 73 * 1 + 12 * 1 + 
					37 * 1 + 34 * 1 + 27 * 1 + 26 * 1 + 69 * 1 + 41 * 1 + 93 * 1 + 
					29 * 1 + 1 * 1 + 67 * 1 + 31 * 1 + 47 * 1 + 55 * 1 + 34 * 1 + 
					50 * 1 + 109 * 1 + 200 * 1 + 197 * 1 + 140 * 1 + 29 * 1 + 22 * 1 + 
					184 * 1 + 13 * 1 + 238 * 1 + 97 * 1 + 170 * 1 + 253 * 1 + 239
					)/( 7 * 7 )(���H�B�n�v���`�M) =
					3577 / 49 = 73
		
		7*7�B�n�ǤJ�覡���@�}�C�G
			���]�}�C�W�٬�Mask�A�ƭȳ]�w�|�Ҧp�U�G
			--																	--
			|	Mask[42] Mask[43] Mask[44] Mask[45] Mask[46] Mask[47] Mask[48]	 |
			|	Mask[35] Mask[36] Mask[37] Mask[38] Mask[39] Mask[40] Mask[41] 	 |
			|	Mask[28] Mask[29] Mask[30] Mask[31] Mask[32] Mask[33] Mask[34]	 |
			|	Mask[21] Mask[22] Mask[23] Mask[24] Mask[25] Mask[26] Mask[27]	 |
			|	Mask[14] Mask[15] Mask[16] Mask[17] Mask[18] Mask[19] Mask[20]	 |
			|	Mask[ 7] Mask[ 8] Mask[ 9] Mask[10] Mask[11] Mask[12] Mask[13]	 |
			|	Mask[ 0] Mask[ 1] Mask[ 2] Mask[ 3] Mask[ 4] Mask[ 5] Mask[ 6]	 |
			--																	--
			�ѥ��U���}�l�s����0�A�ѥ��ܥk�A�ѤU�ܤW���W
	
	���Ƶ{���N�Ϲ�������R�BG�BB�������O�B�z�A�t��k�ۦP
	�Ƶ{����J��(���i��Convolution�B�⤧BMP24RGB���A�v��, ���i��Convolution�B�⤧BMP24RGB���A�Ϲ����e��, ���i��Convolution�B�⤧BMP24RGB���A�Ϲ�������, Convolution��Mask)
	�Ƶ{����X������Convolution�B��ᤧ���G
 */
BMP24RGB *BmpConvolution77(const BMP24RGB*,const int,const int,const long double[]);
//	�ŧiBmpConvolution77(�Ϲ�7*7�B�n�P�n)�Ƶ{��
/*	BmpConvolution�Ω�p�⵹�w���w�j�p�B�n�P��J�Ϲ��i��P�n(Convolution)�A
	����T�W�ӻ��A�P�n�L�{�����N�B�n½��A�����Ƶ{�����i��½��A�ȶi��ۭ��C
	�B�n�ǤJ�覡���@�}�C�A�ѥ��U���}�l�s����0�A�ѥ��ܥk�A�ѤU�ܤW���W�C
	���Ƶ{���N�Ϲ�������R�BG�BB�������O�B�z�A�t��k�ۦP�C
	���Ƶ{����J�ѼƸ��h�A�̧ǻ����p�U�G
	�Ĥ@���ѼƬ�Convolution�B�n�j�p�A�Y���i��P�n���B�n��7*7�A�h�ӰѼƶǤJ7
	�ĤG���ѼƬ����i��Convolution�B�⤧BMP24RGB���A�v��
	�ĤT���ѼƬ����i��Convolution�B�⤧BMP24RGB���A�Ϲ����e��
	�ĥ|���ѼƬ����i��Convolution�B�⤧BMP24RGB���A�Ϲ�������
	�Ĥ����ѼƬ�Convolution��Mask��ơA�ݻP�Ĥ@���Ѽưt�X�A�Y�Ĥ@���ѼƶǤJ7�A�h�ӳBMask���@7*7�j�p���}�C
	�Ƶ{����J��(Convolution�B�n�j�p, ���i��Convolution�B�⤧BMP24RGB���A�v��, ���i��Convolution�B�⤧BMP24RGB���A�Ϲ����e��, ���i��Convolution�B�⤧BMP24RGB���A�Ϲ�������, Convolution��Mask)
	�Ƶ{����X������Convolution�B��ᤧ���G
 */
BMP24RGB *BmpConvolution(const int, const BMP24RGB*,const int,const int,const long double[]);
//	�ŧiBmpConvolution(�Ϲ��P�n)�Ƶ{��
/*	ImageSmoothing33V1(ImageSmoothing33 Version 1)�Ƶ{���Ω�p��BMP24RGB���A�Ϲ���3*3Mask�����o�i
	�B��ɨϥΤ�3*3 Mask�p�U�G
		-				-
		|	1/9	1/9	1/9	|
		|	1/9	1/9	1/9	|
		|	1/9	1/9	1/9	|
		-				-
	�|�ҦӨ��G
	�@�Ϲ�3*3�϶������Ȧp�U�G
		-				-
		|	10	20	30	|
		|	40	10	20	|
		|	70	40	50	|
		-				-
	�p�⥭���o�i�o�������Ȭ�10/9+20/9+30/9+40/9+10/9+20/9+70/9+40/9+50/9=290/9=32.2222
	���Ƶ{���N�Ϲ�������R�BG�BB�������O�B�z�A�t��k�ۦP
	�Ƶ{����J��(���i�業���o�i��BMP24RGB���A�Ϲ����,���i�業���o�i���Ϲ��e��,���i�業���o�i���Ϲ�����)
	�Ƶ{����X���i�業���o�i�ᤧBMP24RGB���A�Ϲ����
 */
BMP24RGB *ImageSmoothing33V1(const BMP24RGB*,const int,const int);		//	�ŧiImageSmoothing33V1(BMP����3*3Mask�����o�i Version 1)�Ƶ{��
/*	ImageSmoothing33V2(ImageSmoothing33 Version 2)�Ƶ{���Ω�p��BMP24RGB���A�Ϲ���3*3Mask�����o�i
	�B��ϥ�BmpConvolution33�Ƶ{����{
	�Ƶ{����J��(���i�業���o�i��BMP24RGB���A�Ϲ����,���i�業���o�i���Ϲ��e��,���i�業���o�i���Ϲ�����)
	�Ƶ{����X���i�業���o�i�ᤧBMP24RGB���A�Ϲ����
 */
BMP24RGB *ImageSmoothing33V2(const BMP24RGB*,const int,const int);		//	�ŧiImageSmoothing33V2(BMP����3*3Mask�����o�i Version 2)�Ƶ{��
/*	ImageSmoothing55�Ƶ{���Ω�p��BMP24RGB���A�Ϲ���5*5Mask�����o�i
	�B��ϥ�BmpConvolution55�Ƶ{����{
	�Ƶ{����J��(���i�業���o�i��BMP24RGB���A�Ϲ����,���i�業���o�i���Ϲ��e��,���i�業���o�i���Ϲ�����)
	�Ƶ{����X���i�業���o�i�ᤧBMP24RGB���A�Ϲ����
 */
BMP24RGB *ImageSmoothing55(const BMP24RGB*,const int,const int);		//	�ŧiImageSmoothing55(BMP����5*5Mask�����o�i)�Ƶ{��
/*	ImageSmoothing77�Ƶ{���Ω�p��BMP24RGB���A�Ϲ���7*7Mask�����o�i
	�B��ϥ�BmpConvolution77�Ƶ{����{
	�Ƶ{����J��(���i�業���o�i��BMP24RGB���A�Ϲ����,���i�業���o�i���Ϲ��e��,���i�業���o�i���Ϲ�����)
	�Ƶ{����X���i�業���o�i�ᤧBMP24RGB���A�Ϲ����
 */
BMP24RGB *ImageSmoothing77(const BMP24RGB*,const int,const int);		//	�ŧiImageSmoothing77(BMP����7*7Mask�����o�i)�Ƶ{��
/*	ImageSmoothing�Ƶ{���Ω�p��BMP24RGB���A�Ϲ������w�j�pMask�����o�i
	�B��ϥ�BmpConvolution�Ƶ{����{
	�Ĥ@���ǤJ�ѼƬ����i�業���o�i��Mask�j�p�A�Y���i�業���o�i���B�n��7*7�A�h�ӰѼƶǤJ7
	�Ƶ{����J��(���i�業���o�i��Mask�j�p,���i�業���o�i��BMP24RGB���A�Ϲ����,���i�業���o�i���Ϲ��e��,���i�業���o�i���Ϲ�����)
	�Ƶ{����X���i�業���o�i�ᤧBMP24RGB���A�Ϲ����
 */
BMP24RGB *ImageSmoothing(const int, const BMP24RGB*,const int,const int);
//	�ŧiImageSmoothing(BMP���ɥ����o�i)�Ƶ{��
/*	MedianFilter33�Ƶ{���Ω�p��BMP24RGB���A�Ϲ���3*3Mask�����o�i
	�Ƶ{����J��(���i�椤���o�i��BMP24RGB���A�Ϲ����,���i�椤���o�i���Ϲ��e��,���i�椤���o�i���Ϲ�����)
	�Ƶ{����X���i�椤���o�i�ᤧBMP24RGB���A�Ϲ����
 */
BMP24RGB *MedianFilter33(const BMP24RGB*,const int,const int);			//	�ŧiMedianFilter33(BMP����3*3�����o�i)�Ƶ{��
/*	GaussianBlur33V1(3*3�����o�i Version 1)�Ƶ{���Ω�p��BMP24RGB���A�Ϲ���Ƥ������ҽk
	�ѦҦۺ���ʬ�Ghttps://zh.wikipedia.org/wiki/%E9%AB%98%E6%96%AF%E6%A8%A1%E7%B3%8A
	���Ƶ{���N�Ϲ�������R�BG�BB�������O�B�z�A�t��k�ۦP
	�Ƶ{����J��(���i�氪���o�i��BMP24RGB���A�Ϲ����,���i�氪���o�i���Ϲ��e��,���i�氪���o�i���Ϲ�����,�`�A�������зǰ��t�m)
	�Ƶ{����X���i�氪���o�i�ᤧBMP24RGB���A�Ϲ����
 */
BMP24RGB *GaussianBlur33V1(const BMP24RGB*,const int,const int,const long double);
//	�ŧiGaussianBlur33V1(3*3�����o�i Version 1)�Ƶ{��
/*	GaussianBlur33V2(3*3�����o�i Version 2)�Ƶ{���Ω�p��BMP24RGB���A�Ϲ���Ƥ������ҽk
	�ѦҦۺ���ʬ�Ghttps://zh.wikipedia.org/wiki/%E9%AB%98%E6%96%AF%E6%A8%A1%E7%B3%8A
	���Ƶ{���N�Ϲ�������R�BG�BB�������O�B�z�A�t��k�ۦP
	�B��ϥ�BmpConvolution33�Ƶ{����{
	�Ƶ{����J��(���i�氪���o�i��BMP24RGB���A�Ϲ����,���i�氪���o�i���Ϲ��e��,���i�氪���o�i���Ϲ�����,�`�A�������зǰ��t�m)
	�Ƶ{����X���i�氪���o�i�ᤧBMP24RGB���A�Ϲ����
 */
BMP24RGB *GaussianBlur33V2(const BMP24RGB*, const int, const int, const long double);
//	�ŧiGaussianBlur33V2(3*3�����o�i Version 2)�Ƶ{��
/*	GaussianBlur�Ƶ{���Ω�p����N�j�p�������o�i
	�ѦҦۺ���ʬ�Ghttps://zh.wikipedia.org/wiki/%E9%AB%98%E6%96%AF%E6%A8%A1%E7%B3%8A
	���Ƶ{���N�Ϲ�������R�BG�BB�������O�B�z�A�t��k�ۦP
	�B��ϥ�BmpConvolution�Ƶ{����{
	���Ƶ{����J�ѼƸ��h�A�̧ǻ����p�U�G
	�Ĥ@���ѼƬ������o�iConvolution�B�n�j�p�A�Y���i��P�n���B�n��7*7�A�h�ӰѼƶǤJ7
	�ĤG���ѼƬ����i�氪���o�i��BMP24RGB���A�Ϲ����
	�ĤT���ѼƬ����i�氪���o�i���Ϲ��e��
	�ĥ|���ѼƬ����i�氪���o�i���Ϲ�����
	�Ĥ����ѼƬ��`�A�������зǰ��t�m
	�Ƶ{����J��(�����o�i�B�n�j�p,���i�氪���o�i��BMP24RGB���A�Ϲ����,���i�氪���o�i���Ϲ��e��,���i�氪���o�i���Ϲ�����,�`�A�������зǰ��t�m)
	�Ƶ{����X���i�氪���o�i�ᤧBMP24RGB���A�Ϲ����
 */
BMP24RGB *GaussianBlur(const int, const BMP24RGB*, const int, const int, const long double);
//	�ŧiGaussianBlur(�����o�i)�Ƶ{��
/*	GaussianFigure2D�Ƶ{���Ω󲣥ͤG��������ƹϧ�
	�G�������Ϲ����߬��p�ȡA�v���V�~����A�]���ӹϹ����߬��զ�A�H�P�߶�V�~����
	�G�������p��ϥ�NormalDistribution2D�Ƶ{��
	�Ƶ{����J��(���ͦ��G�������Ϲ��e��, ���ͦ��G�������Ϲ�����, �����������зǰ��t�m)
	�Ƶ{����X���G��������BMP24RGB���A�Ϲ����
 */
BMP24RGB *GaussianFigure2D(const int, const int, const long double);	//	�ŧiGaussianFigure2D(�G�������Ϲ�)�ͦ��Ƶ{��
/*	NormalDistribution2D(�G���`�A�����p��)�Ƶ{���Ω�p��G���`�A�����ƭ�
	�����p�U�G
		pow(M_E,-(pow(xlocation,2) + pow(ylocation,2)) / (2 * pow(StandardDeviation,2)))/(2 * M_PI * pow(StandardDeviation,2))
	������xlocation�Bylocation���G���y�СAStandardDeviation���`�A�������зǰ��t�m
	�Ƶ{����J��(xlocation,ylocation,StandardDeviation)
	�Ƶ{����X���G���`�A�����p�⵲�G
 */
long double NormalDistribution2D(long double, long double, long double);//	�ŧiNormalDistribution2D(�G���`�A�����p��)�Ƶ{��
BMP24RGB *ImageOCR(const BMP24RGB*,const int,const int);				//	�ŧiImageOCR(�v��OCR)�Ƶ{��
/*	BMP24RGBGradient�Ƶ{���Ω�p��BMP24RGB���A�Ϲ���Ƥ����
	�B���k��
		Step1�G�p��XGx(X��V���)�PGy(Y��V���)�A�p���k�|�Ҧp�U�G
		
		�@�Ϲ�3*3�϶������Ȧp�U�G
		-				-
		|	10	20	30	|
		|	40	10	20	|
		|	70	40	50	|
		-				-
		
		�h�G
		Gx = 	-				-	-				-
				|	10	20	30	|	|	-1	0	1	|
				|	40	10	20	| * |	-1	0	1	| = 10 * (-1) + 40 * (-1) + 70 * (-1) + 
				|	70	40	50	|	|	-1	0	1	|	20 *   0  + 10 *   0  + 40 *   0  + 
				-				-	-				-	30 *   1  + 20 *   1  + 50 *   1  = -20
				
		Gy = 	-				-	-				-
				|	10	20	30	|	|	-1	-1	-1	|
				|	40	10	20	| * |	 0	 0	 0	| = 10 * (-1) + 20 * (-1) + 30 * (-1) + 
				|	70	40	50	|	|	 1	 1	 1	|	40 *   0  + 10 *   0  + 20 *   0  + 
				-				-	-				-	70 *   1  + 40 *   1  + 50 *   1  = 100
		
		Step2�G�p���פj�p(Magnitude)�P��V(Direction)
		�ǥ�Gx�PGy�p���פj�p(Magnitude)�P��V(Direction)�A�b����V(Direction)������(deg)
		�j�p(Magnitude)���Ȱ쬰[-765,765]
		��V(Direction)�gatan��ƭp�⤧�Ȱ쬰[-90�X,90�X]�A����ڤW�ݦҼ{Gx�PGx�����t���H�M�w��V�A
		�Y(Gx>0)�B(Gy>0)�A�h��V(Direction)�d�򤶩�0~90��
			ex�G��Gx=1�AGy=1�ɡAatan(1) = 0.785398163 rad = 45 deg�A��V(Direction) = 45 deg
			��(Gx>0)�B(Gy>0)�ɡA��V(Direction) = atan( Gy / Gx )(deg)
		�Y(Gx<0)�B(Gy>0)�A�h��V(Direction)�d�򤶩�90~180��
			ex�G��Gx=-1�AGy=1�ɡAatan(-1) = -0.785398163 rad = -45 deg�A����V(Direction)����135 deg
			��(Gx<0)�B(Gy>0)�ɡA��V(Direction) = atan( Gy / Gx )(deg) + 180�X
		�Y(Gx<0)�B(Gy<0)�A�h��V(Direction)�d�򤶩�180~270��
			ex�G��Gx=-1�AGy=-1�ɡAatan(1) = 0.785398163 rad = 45 deg�A����V(Direction)����225 deg
			��(Gx<0)�B(Gy<0)�ɡA��V(Direction) = atan( Gy / Gx )(deg) + 180�X
		�Y(Gx>0)�B(Gy<0)�A�h��V(Direction)�d�򤶩�270~360��
			ex�G��Gx=1�AGy=-1�ɡAatan(-1) = -0.785398163 rad = -45 deg�A����V(Direction)����315 deg
			��(Gx>0)�B(Gy<0)�ɡA��V(Direction) = atan( Gy / Gx )(deg) + 360�X
		�W�z�|�����ׯS�ʥi�k�Ǭ��G
		�Y(Gx>0)�A�h��V(Direction)�d�򤶩�-90~90��(�Ĥ@�B�|�H���A�k�b����)		�ĤG�H��|�Ĥ@�H��
		�Y(Gx<0)�A�h��V(Direction)�d�򤶩�90~270��(�ĤG�B�T�H���A���b����)		-----------------
																				�ĤT�H��|�ĥ|�H��
		
		�]���ϥ�atan��ƭp��ɡA�Y(Gx<0)�h�p�⵲�G��+180�סA�h��V(Direction)���Ȱ쬰[-90,270]�A
		���ɥ��b���������׬����T�A���k�b���������׭Ȱ쬰[-90,90]�A��k�b����������<0�ɡA�ݱN�Ө���+360
		
		�G�o�G
		Magnitude = ( Gx ^ 2 + Gy ^ 2 ) ^ 0.5										//	�p���פj�p(Magnitude)
		Direction = atan( Gy / Gx ) * (180 / PI) 		if (Gx > 0) and (Gy >= 0)	//	�p���פ�V(Direction)�вĤ@�H��
					atan( Gy / Gx ) * (180 / PI) + 180�X	if Gx < 0					//	�p���פ�V(Direction)�вĤG�H���B�ĤT�H��
					atan( Gy / Gx ) * (180 / PI) + 360�X	if (Gx > 0) and (Gy < 0)	//	�p���פ�V(Direction)�вĥ|�H��
							 90							if (Gx = 0) and (Gy > 0)	//	90�X���p
							270							if (Gx = 0) and (Gy < 0)	//	270�X���p
							0(Nan?)						if (Gx = 0) and (Gy = 0)	//	��Gx��0�BGy�笰0�ɡA��פ�V�L�k�w�q

		���Ƶ{���N�Ϲ�������R�BG�BB�������O�B�z�A�t��k�ۦP
		
	�Ƶ{����J��(���p���פ�BMP24RGB���A�Ϲ����,���p���פ��Ϲ��e��,���p���פ��Ϲ�����)
	�Ƶ{����X���p���׫ᤧBMP24RGB���A�Ϲ����
 */
BMP24RGB *BMP24RGBGradient(const BMP24RGB*,const int,const int);		//	�ŧiBMP24RGBGradient(BMP�Ϥ���Ʊ�׭p��)�Ƶ{��
/*	BMP24RGBSobelEdge�Ƶ{���Ω�Sobel(��������l)��t����
	�B���k��
		Step1�G�p��XGx(��V��t�˴�)�PGy(�a�V��t�˴�)�A�p���k�|�Ҧp�U�G
		
		�@�Ϲ�3*3�϶������Ȧp�U�G
		--				--
		|	10	20	30	 |
		|	40	10	20	 |
		|	70	40	50	 |
		--				--
		
		�h�G
		Gx = 	-				-	-				-
				|	10	20	30	|	|	-1	0	1	|
				|	40	10	20	| * |	-2	0	2	| = 10 * (-1) + 40 * (-2) + 70 * (-1) + 
				|	70	40	50	|	|	-1	0	1	|	20 *   0  + 10 *   0  + 40 *   0  + 
				-				-	-				-	30 *   1  + 20 *   2  + 50 *   1  = -40
				
		Gy = 	-				-	-				-
				|	10	20	30	|	|	-1	-2	-1	|
				|	40	10	20	| * |	 0	 0	 0	| = 10 * (-1) + 20 * (-2) + 30 * (-1) + 
				|	70	40	50	|	|	 1	 2	 1	|	40 *   0  + 10 *   0  + 20 *   0  + 
				-				-	-				-	70 *   1  + 40 *   2  + 50 *   1  = 120
		
		Step2�G�p���פj�p(Magnitude)�P��V(Direction)
		�ǥ�Gx�PGy�p���פj�p(Magnitude)�P��V(Direction)�A�b����V(Direction)������(deg)
		�j�p(Magnitude)���Ȱ쬰[-765,765]
		��V(Direction)�gatan��ƭp�⤧�Ȱ쬰[-90�X,90�X]�A����ڤW�ݦҼ{Gx�PGx�����t���H�M�w��V�A
		�Y(Gx>0)�B(Gy>0)�A�h��V(Direction)�d�򤶩�0~90��
			ex�G��Gx=1�AGy=1�ɡAatan(1) = 0.785398163 rad = 45 deg�A��V(Direction) = 45 deg
			��(Gx>0)�B(Gy>0)�ɡA��V(Direction) = atan( Gy / Gx )(deg)
		�Y(Gx<0)�B(Gy>0)�A�h��V(Direction)�d�򤶩�90~180��
			ex�G��Gx=-1�AGy=1�ɡAatan(-1) = -0.785398163 rad = -45 deg�A����V(Direction)����135 deg
			��(Gx<0)�B(Gy>0)�ɡA��V(Direction) = atan( Gy / Gx )(deg) + 180�X
		�Y(Gx<0)�B(Gy<0)�A�h��V(Direction)�d�򤶩�180~270��
			ex�G��Gx=-1�AGy=-1�ɡAatan(1) = 0.785398163 rad = 45 deg�A����V(Direction)����225 deg
			��(Gx<0)�B(Gy<0)�ɡA��V(Direction) = atan( Gy / Gx )(deg) + 180�X
		�Y(Gx>0)�B(Gy<0)�A�h��V(Direction)�d�򤶩�270~360��
			ex�G��Gx=1�AGy=-1�ɡAatan(-1) = -0.785398163 rad = -45 deg�A����V(Direction)����315 deg
			��(Gx>0)�B(Gy<0)�ɡA��V(Direction) = atan( Gy / Gx )(deg) + 360�X
		�W�z�|�����ׯS�ʥi�k�Ǭ��G
		�Y(Gx>0)�A�h��V(Direction)�d�򤶩�-90~90��(�Ĥ@�B�|�H���A�k�b����)		�ĤG�H��|�Ĥ@�H��
		�Y(Gx<0)�A�h��V(Direction)�d�򤶩�90~270��(�ĤG�B�T�H���A���b����)		-----------------
																				�ĤT�H��|�ĥ|�H��
		
		�]���ϥ�atan��ƭp��ɡA�Y(Gx<0)�h�p�⵲�G��+180�סA�h��V(Direction)���Ȱ쬰[-90,270]�A
		���ɥ��b���������׬����T�A���k�b���������׭Ȱ쬰[-90,90]�A��k�b����������<0�ɡA�ݱN�Ө���+360
		
		�G�o�G
		Magnitude = ( Gx ^ 2 + Gy ^ 2 ) ^ 0.5										//	�p���פj�p(Magnitude)
		Direction = atan( Gy / Gx ) * (180 / PI) 		if (Gx > 0) and (Gy >= 0)	//	�p���פ�V(Direction)�вĤ@�H��
					atan( Gy / Gx ) * (180 / PI) + 180�X	if Gx < 0					//	�p���פ�V(Direction)�вĤG�H���B�ĤT�H��
					atan( Gy / Gx ) * (180 / PI) + 360�X	if (Gx > 0) and (Gy < 0)	//	�p���פ�V(Direction)�вĥ|�H��
							 90							if (Gx = 0) and (Gy > 0)	//	90�X���p
							270							if (Gx = 0) and (Gy < 0)	//	270�X���p
							0(Nan?)						if (Gx = 0) and (Gy = 0)	//	��Gx��0�BGy�笰0�ɡA��פ�V�L�k�w�q
		
		���Ƶ{���N�Ϲ�������R�BG�BB�������O�B�z�A�t��k�ۦP
		
		�ѦҦۺ���ʬ�Ghttps://zh.wikipedia.org/wiki/%E7%B4%A2%E8%B2%9D%E7%88%BE%E7%AE%97%E5%AD%90
 */
BMP24RGB *BMP24RGBSobelEdge(const BMP24RGB*,const int,const int);		//	�ŧiBMP24RGBSobelEdge(BMP�Ϥ����Sobel��t����)�Ƶ{��
/*	RGBHistogramEqualization�Ƶ{���Ω��BMP24RGB���A�v���i��Histogram Equalization(����ϵ���)
	�B���k���O��R�BG�BB�i�湳���Ȳέp�B�ֿn�A���OHistogram Equalization(����ϵ���)�A���Ӥ�k�i��ɭP�Ϲ��C�����
	�Ƶ{����J��(���i�檽��ϵ��Ƥ�BMP24RGB���A�v�����,�v���e��,�v������)
	�Ƶ{����X������ϵ��ƫᤧBMP24RGB���A�v�����
 */
BMP24RGB *RGBHistogramEqualization(const BMP24RGB*,const int,const int);//	�ŧiRGBHistogramEqualization(RGB�Ƕ��v������ϵ���)�Ƶ{��
/*	BMPHaarWavelet�Ƶ{���Ω��BMP24RGB���A�v���i�櫢���p�i�ഫ
	�B���k���O��R�BG�BB�i�櫢���p�i�ഫ�A��Ҧ��]�w�Ѽ�(Mode)�A�t�XHaarWaveletMode���X�ŧi�G
	HaarWaveletMode���X�ŧiHorizontalHighPass(�������q�o�i)�BHorizontalLowPass(�����C�q�o�i)�BVerticalHighPass(�������q�o�i)�PVerticalLowPass(�����C�q�o�i)
	�|�ؼҦ��A���O�����p�U�G
		- HorizontalHighPass(�������q�o�i)�Ҧ�
		�p��������������t�ȡA�Y�����������t���U�j�A�h��X�����ȷU�j�A�ϥξB�n��
						--				--
						|	-1,	0,	1	 |
						--				--
		�G�g�L�ӼҦ���X�Ϥ��N�O�d�������z
		- HorizontalLowPass(�����C�q�o�i)�Ҧ�
		�p��������������ȡA�ϥξB�n��
						--					--
						|	0.5,	0,	0.5	 |
						--					--
		�㦳������V�ҽk���ĪG
		- VerticalHighPass(�������q�o�i)
		�p�⫫�����������t�ȡA�Y�����������t���U�j�A�h��X�����ȷU�j�A�ϥξB�n��
						--		--
						|	-1	 |
						|	0	 |
						|	1	 |
						--		--
		�G�g�L�ӼҦ���X�Ϥ��N�O�d�������z
		- VerticalLowPass(�����C�q�o�i)
		�p�⫫�����������ȡA�ϥξB�n��
						--		--
						|	0.5	 |
						|	0	 |
						|	0.5	 |
						--		--
		�㦳������V�ҽk���ĪG
	�Ƶ{����J��(���i��Haar Wavelet��BMP24RGB���A�v�����,�v���e��,�v������,Haar�p�i�ഫ�Ҧ�)
	�Ƶ{����X��Haar�p�i�ഫ�ᤧBMP24RGB���A�v�����
 */
BMP24RGB *BMPHaarWavelet(const BMP24RGB*,const int,const int, const char);
/*	BMPHaarWavelet2�Ƶ{���Ω��BMP24RGB���A�v���i��G������(Haar)�p�i�ഫ
	�B���k�����p�U�G
		�ѩ�Ϲ����G�����c�AHaar�p�i�o�i��V�i���������o�i�P�����o�i�A
		�ӰƵ{������G������(Haar)�p�i�ഫ��
 */
BMP24RGB *BMPHaarWavelet2(const BMP24RGB*,const int,const int, const char);
/*	HSVHistogramEqualization�Ƶ{���Ω��HSV���A�v���i��Histogram Equalization(����ϵ���)
	�B���k�ȹ��HSV��m�Ŷ���Value�i��Histogram Equalization(����ϵ���)
	�Ƶ{����J��(���i�檽��ϵ��Ƥ�HSV���A�v�����,�v���e��,�v������)
	�Ƶ{����X������ϵ��ƫᤧHSV���A�v�����
 */
HSV *HSVHistogramEqualization(const HSV*,const int,const int);			//	�ŧiHSVHistogramEqualization(HSV�v������ϵ���)�Ƶ{��

/*	HueToBMP24RGB�Ƶ{���Ω�NHSV���A�v����Ƥ���Hue��ƨ��X��JBMP24RGB�Ϲ�
	�ѩ󥻵{�����ϥ�HSV��m�Ŷ���Hue�Ȱ쬰0��360�A��BMP24RGB���A��R�BG�BB���Ȱ쬰0��255
	�G�O�G
		R=Hue * 255 / 360�FG=Hue * 255 / 360�FB=Hue * 255 / 360
	�Y�i�����NHue��J��BMP24RGB���A
	�Ƶ{����J��(HSV���A�v�����,HSV���A�v���e��,HSV���A�v������)
	�Ƶ{����X������HSV���A�v����Hue��J�oBMP24RGB�Ϲ����
 */
BMP24RGB *HueToBMP24RGB(const HSV*,const int,const int);				//	�ŧiHueToBMP24RGB�Ƶ{��
/*	SaturationToBMP24RGB�Ƶ{���Ω�NHSV���A�v����Ƥ���Saturation��ƨ��X��JBMP24RGB�Ϲ�
	�ѩ󥻵{�����ϥ�HSV��m�Ŷ���Saturation�Ȱ쬰0��1�A��BMP24RGB���A��R�BG�BB���Ȱ쬰0��255
	�G�O�G
		R=Saturation * 255�FG=Saturation * 255�FB=Saturation * 255
	�Y�i�����NSaturation��J��BMP24RGB���A
	�Ƶ{����J��(HSV���A�v�����,HSV���A�v���e��,HSV���A�v������)
	�Ƶ{����X������HSV���A�v����Saturation��J�oBMP24RGB�Ϲ����
 */
BMP24RGB *SaturationToBMP24RGB(const HSV*,const int,const int);			//	�ŧiSaturationToBMP24RGB�Ƶ{��
/*	ValueToBMP24RGB�Ƶ{���Ω�NHSV���A�v����Ƥ���Value��ƨ��X��JBMP24RGB�Ϲ�
	�ѩ󥻵{�����ϥ�HSV��m�Ŷ���Value�Ȱ쬰0��255�ABMP24RGB���A��R�BG�BB���Ȱ�笰0��255
	�G�����O�G
		R=Value�FG=Value�FB=Value
	�Y�i�����NValue��J��BMP24RGB���A
	�Ƶ{����J��(HSV���A�v�����,HSV���A�v���e��,HSV���A�v������)
	�Ƶ{����X������HSV���A�v����Value��J�oBMP24RGB�Ϲ����
 */
BMP24RGB *ValueToBMP24RGB(const HSV*,const int,const int);				//	�ŧiValueToBMP24RGB�Ƶ{��
/*	HSVSkin�Ƶ{���Ω�z�LHSV��m�Ŷ���T���A�ѵ��w��H�BS�BV���d��L�o�X�ֽ���T
	�b���Ƶ{�����]�wH�d��15��50�FS�d��0.23��0.68�F�Z������m��T�b���d�򤤬ҫO�d�칳����T�A
	�b�d��~�h��������(Value)��T(��X������Value=�칳��Value*0.3)
	�Ƶ{����J��(HSV���A�v�����,HSV���A�v���e��,HSV���A�v������)
	�Ƶ{����X���L�o�ֽ���T��HSV���A�v��
 */
HSV *HSVSkin(const HSV*,const int,const int);							//	�ŧiHSVSkin�Ƶ{��
/*	BmpFillingByteCalc(BMP���ɸ�ư϶�ɦ줸�p��)�Ƶ{��
 */
unsigned char BmpFillingByteCalc(const unsigned int);					//	�ŧiBmpFillingByteCalc(�p���R�줸�դj�p)�Ƶ{��
bool FileExistCheck(char *);											//	�ŧiFileExistCheck(�ɮצs�b�ˬd)�Ƶ{��
bool FileReadPermissionCheck(const char *);								//	�ŧiFileReadPermissionCheck(�ɮ�Ū���v���ˬd)�Ƶ{��
bool FileWritePermissionCheck(const char *);							//	�ŧiFileWritePermissionCheck(�ɮ׼g�J�v���ˬd)�Ƶ{��
bool FileWrite(const char *,const char *,const char *);					//	�ŧiFileWrite(�ɮ׼g�J)�Ƶ{���A�����r�ɮ׼g�J
/*	UCharBubbleSort�Ƶ{���Ω�Ƨ�unsigned char�ƭȰ}�C
	�Ƶ{����J��(���ƧǤ�unsigned char�ƭȫ���(�ӫ��Чt�����r��),���ƧǼƭȭӼ�,�ƧǤ覡)
	�b���ƧǤ覡��J0���Ѥp�ܤj�ƧǡF��J1���Ѥj�ܤp�Ƨ�
	�Ƶ{����X���Ƨǧ�����unsigned char�ƭȫ���
 */
unsigned char *UCharBubbleSort(const unsigned char *,const unsigned long long int,const bool);
int Compare(const void *,const void *);									//	�ŧiCompare�Ƶ{��(��qsort�ƧǨϥ�)
/**	CountCharPointStr�Ƶ{��
	�ӰƵ{���Ω�p��r����Ъ��סF
	�Ĥ@���ѼƬ����p����פ��r��F
	�ĤG���ѼƬ��O�_��ܭp��Ӹ`��bool�ܼơA�Y��JTure�h��ܭp��Ӹ`�A�Ϥ��h�L
	�p�GCountCharPointStr("ABC", False)�A�i�o���׬�3
	�p�GCountCharPointStr("123456789a", True)�A�i���
	��1�Ӧr�����G1
	��2�Ӧr�����G2
	��3�Ӧr�����G3
	��4�Ӧr�����G4
	��5�Ӧr�����G5
	��6�Ӧr�����G6
	��7�Ӧr�����G7
	��8�Ӧr�����G8
	��9�Ӧr�����G9
	��10�Ӧr�����Ga	
	�ño���׬�10
**/
unsigned long long int CountCharPointStr(const char *, const bool);
void Show_char_point_str(const char *);									//	�ŧiShow_char_point_str(��ܦr������)�Ƶ{��
/*	ShowUCharPointStr�Ƶ{���Ω���ܵL���r�����Ф��e
	�Ƶ{����J��(����ܤ��e���L���r������,�L���r�����Ъ���)
	�Ƶ{����X��void
 */
void ShowUCharPointStr(const unsigned char *,unsigned long long int);	//	�ŧiShowUCharPointStr(��ܵL���r������)�Ƶ{��
/*	ShowLongDouble�Ƶ{���Ω����long double(���B�I��)�ƭ�
	��long double(���B�I��)�i�O����1.7��10^(-308)~��1.7��10^308�d�򤺪��ƭ�
	�ѩ�ShowLongDouble�Ƶ{���B�z�P�B��W�ƭȼe�׬�64�줸
	�]���i�B�z��InputNumber�̤j�W����2^64-1
	�Ƶ{����J������ܤ�long double���A�ƭ�
	�Ƶ{����X��void
 */
void ShowLongDouble(const long double InputNumber);						//	�ŧiShowLongDouble�Ƶ{��
/*	InitialIMGArrayTest�Ƶ{���Ω����InitialIMGArray�Ƶ{��
	�����հƵ{������J�B��X�Ҭ�void�A�Ҧ��ѼƬҳ]�p����հƵ{�����A
	�H�[��ϥΰƵ{���һݫŧi�P�y�k
	�Ƶ{����J��void
	�Ƶ{����X��void
 */
void InitialIMGArrayTest(void);											//	�ŧiInitialIMGArrayTest�Ƶ{��
/*	BmpReadFilesizeTest�Ƶ{���Ω����BmpReadFilesize�Ƶ{��
	�����հƵ{������J�B��X�Ҭ�void�A�Ҧ��ѼƬҳ]�p����հƵ{�����A
	�H�[��ϥΰƵ{���һݫŧi�P�y�k
	���Ƶ{���]�tBmpReadFilesize�Ƶ{����إΪk�п�J�ɮ׸��|�]�t���ɦW�P���t���ɦW
	�Ƶ{����J��void
	�Ƶ{����X��void
 */
void BmpReadFilesizeTest(void);
/*	BmpReadXSizeTest�Ƶ{���Ω����BmpReadXSize�Ƶ{��
	�����հƵ{������J�B��X�Ҭ�void�A�Ҧ��ѼƬҳ]�p����հƵ{�����A
	�H�[��ϥΰƵ{���һݫŧi�P�y�k
	�Ƶ{����J��void
	�Ƶ{����X��void
 */
void BmpReadXSizeTest(void);											//	�ŧiBmpReadXSizeTest�Ƶ{��
/*	BmpReadYSizeTest�Ƶ{���Ω����BmpReadYSize�Ƶ{��
	�����հƵ{������J�B��X�Ҭ�void�A�Ҧ��ѼƬҳ]�p����հƵ{�����A
	�H�[��ϥΰƵ{���һݫŧi�P�y�k
	�Ƶ{����J��void
	�Ƶ{����X��void
 */
void BmpReadYSizeTest(void);											//	�ŧiBmpReadYSizeTest�Ƶ{��
/*	BmpReadTest�Ƶ{���Ω����BmpRead�Ƶ{��
	�����հƵ{������J�B��X�Ҭ�void�A�Ҧ��ѼƬҳ]�p����հƵ{�����A
	�H�[��ϥΰƵ{���һݫŧi�P�y�k
	�Ƶ{����J��void
	�Ƶ{����X��void
 */
void BmpReadTest(void);													//	�ŧiBmpReadTest�Ƶ{��
/*	BmpWriteV2Test�Ƶ{���Ω����BmpWriteV2�Ƶ{��
	�����հƵ{������J�B��X�Ҭ�void�A�Ҧ��ѼƬҳ]�p����հƵ{�����A
	�H�[��ϥΰƵ{���һݫŧi�P�y�k
	�Ƶ{����J��void
	�Ƶ{����X��void
 */
void BmpWriteV2Test(void);												//	�ŧiBmpWriteV2Test�Ƶ{��