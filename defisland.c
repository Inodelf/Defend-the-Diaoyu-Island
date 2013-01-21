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
