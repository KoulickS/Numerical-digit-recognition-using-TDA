#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
int func(int h, int w, int* a, int i, int j, int c)
{
 
}
unsigned char* read_bmp(char *fname, int* _w, int* _h)
{
 unsigned char head[54];
 FILE *f=fopen(fname,"rb");
 //BMP header is 54 bytes
 fread(head,1,54,f);
 int w=head[18]+(((int)head[19]) << 8)+(((int)head[20]) << 16)+(((int)head[21]) << 24);
 int h=head[22]+(((int)head[23]) << 8)+(((int)head[24]) << 16)+(((int)head[25]) << 24);
 //lines are aligned on 4-byte boundary 
 int lineSize = (w / 8 + (w / 8) % 4);
 int fileSize=lineSize * h;
 unsigned char *img, *data;
 img =(unsigned char*)malloc(w * h), data =(unsigned char*)malloc(fileSize);
 //skip the header
 fseek(f,54,SEEK_SET);
 //skip palette - two rgb quads, 8 bytes
 fseek(f,8,SEEK_CUR);
 //read data
 fread(data,1,fileSize,f);
 //decode bits
 int i, j, k, rev_j;
 for(j=0, rev_j=h-1;j<h;j++,rev_j--)
    {
     for(i=0;i<w/8;i++)
        {
         int fpos= j * lineSize + i, pos = rev_j * w + i * 8;
         for(k=0;k<8;k++)
            {
             img[pos+(7-k)]=(data[fpos] >> k) & 1;
			}
		}
	}
 free(data);
 *_w = w; *_h = h;
 return img;
}
int main()
{
 int w, h, i, j, c1=0, c2=0, c3=0, c4=0, c5=0, c6=0;
 unsigned char* img=read_bmp("crop1.png",&w,&h);
 int array[w][h], x, y;
  for(i=0;i<w;i++)
  {
   for(j=0;j<h;j++)
      {
          printf("%d",img[i][j]);
	  }
   printf("\n");
  }
  //printf("%d  %d\n",x,y);
 
 //printf("%d  %d",h,w);
 return 0;
}

