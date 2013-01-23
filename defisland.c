void putpixel(SDL_Surface *surface,int x,int y,Uint32 pixel)
{
		int bpp=surface->format->BytesPerPixel;
		Uint8 *p =(Uint 8 *)surface ->pixels +y*surface ->pitch +x*bpp;
		switch(bpp)
		{
				case 1:
					 *p=(Uint8)pixel;break;
				case 2:
					 *(Uint16 *)p=(Uint8)pixel;break;
				case 3:
					 if(SDL_BYTEORDER==SDL_BIG_ENDIAN)
						{
						p[0]=(Uint8)pixel&0xff;
						p[1]=((Uint8)pixel>>8)&0xff;
						p[2]=((Uint8)pixel>>16)&oxff;
						}
						break;
				case4 :
					  *(Uint32 *)p=pixel;break;
			}
}

void putcc16(SDL_Surface *surface,int x,int y,int wid,float xt,float yt,unsighed char b,unsigned char g,unsigned char r,unsigned char backb,unsigned char backg,unsigned char backr, char *str)
{
	unsigned zcode,bcode;
	int i,j,k,rec;
	long len;
	unsigned char buf[32];
	
	while(*str)
	{
		if((*str&0x80)&&(*(str+1)&0x80))
		{
		zcode=(*str-0xa1)&07f;
		bcode=(*(str+1)-0xa1)&0x07f;
		rec=zcode*94+bcode;
		len=rec*32L;
		fseek(hzk16fp,len,SEEK_SET);
		fread(buf,1,32,hzk16fp);
		for(i=0;i<16;i++)
			for(j=0;j<2;j++)
				for(k=0;k<8;k++)
					if(buf[i*2+j]>>(7-k)&1)
						putpixel(surface,x+(int)((j*8+k)*xt),y+(int)(i*yt),(Uint32)(b<<0)+(Uint32)(g<<8)+(Uint32)(r<<16));
					else
						putpixel(surface,x+(int)(j*8+k)*xt),y+(int)(i*yt),(Uint32)(backb<<0)+(Uint32)(backg<<8)+(Uint32)(backr<<16));
	x=x+(int)(16*xt)+wid;
	str+=2;
	}
	else
	{
		fseek(ase16fp,(*str)*16,SEEK_SET);
		fread(buf,1,16,asc16fp);
		for(i=0;i<16;i++)
			for(j=0;j<8;j++)
				if(buf[i]>>(7-j)&1)
				putpixel(surface,x+(int)(j*xt),y+(int)(i*yt),(Uint32)(b<<0)+(Uint32)(g<<8)+(Uint32)(r<<16));
				else
				putpixel(surface,x+(int)(j*xt),y+(int)(i*yt),(Uint32)(backb<<0)+(Uint32)(backg<<8)+(Uint32)(backr<<16));
	x=x+(int)(8*xt)+wid;
	str+=1;
		}
	}
}
















