#ifndef _SDL_svg
#define _SDL_svg
#ifdef _SDL_H
    #define NANOSVG_IMPLEMENTATION
    #include "nanosvg/src/nanosvg.h"
    #define NANOSVGRAST_IMPLEMENTATION
    #include "nanosvg/src/nanosvgrast.h"

    inline SDL_Surface* SDL_LoadSVGFromFile(const char* file,float scale=1) {
      NSVGimage* image=NULL;
	    NSVGrasterizer* rast=NULL;
      unsigned char* pixel_data=NULL;
      int w;
      int h;
      SDL_Surface* sur=NULL;
      /* Convert SVG to NSVGimage throw NanoSVG */
      image=nsvgParseFromFile(file,"px",96.0f);
      /* Success? */
      if(image!=NULL) {
        w=(int)image->width;
	      h=(int)image->height;
	      rast=nsvgCreateRasterizer();
	      pixel_data=(unsigned char*)malloc(w*h*4);
	      nsvgRasterize(rast,image,0,0,scale,pixel_data,w,h,w*4);
        /* This is where the "magic" happens */
        sur=SDL_CreateRGBSurfaceFrom((void*)pixel_data,w,h,32,4*w,0x000000ff,0x0000ff00,0x00ff0000,0xff000000);
		    SDL_SetSurfaceBlendMode(sur,SDL_BLENDMODE_BLEND);
      } else {
        SDL_SetError("Unable to load SVG Image!");
      }
      return sur;
    }
#endif
#endif
