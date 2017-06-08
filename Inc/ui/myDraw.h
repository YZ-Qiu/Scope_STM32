#ifndef _MY_DRAW_H_
#define _MY_DRAW_H_

//HV stand for Horizontal , Vertical
inline void drawDotLineHV(int x1,int y1,int x2,int y2,color_t color)
{
	int i;
	int cnt=DOT_ON;
	if(x1==x2)
	{
		for(i=y1;i<=y2;i++)
		{
			if(cnt != 0)
			{
        		gdispDrawPixel(x1, i,color);
				cnt--;
			}
			else
			{
				i+=DOT_OFF;
				cnt =DOT_ON;
			}
		}
	}
	else if(y1==y2)
	{
		for(i=x1;i<=x2;i++)
		{
			if(cnt != 0)
			{
        		gdispDrawPixel(i, y1,color);
				cnt--;
			}
			else
			{
				i+=DOT_OFF;
				cnt = DOT_ON;
			}
		}
	}
	
}
#endif