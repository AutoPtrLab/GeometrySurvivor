#pragma once


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>

//=============================================================
// Wrapper for SDL2
//=============================================================

//logical width and height
constexpr int WIDTH=800; 
constexpr int HEIGHT=600;

//real window size
constexpr int WIN_WIDTH=1280;
constexpr int WIN_HEIGHT=720;

constexpr Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

namespace SDL{

    //new object to make SDL objects memory safe
    using Window = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;

    using Renderer = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;//smart pointer WITH ownership
    using RendererPtr = SDL_Renderer*; //observer-purpose only 

    using Texture = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>; //smart pointer WITH ownership
    using TextPtr = SDL_Texture*; //observer

    using Rect =  SDL_Rect;
    using Event = SDL_Event;

    inline void init(){
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL cant load. Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
        }

    }


    inline void quit(){
        SDL_Quit();
    }
    inline Window CreateWindow(){
        SDL_Window *w = SDL_CreateWindow("GEOMETRY SURVIVOR",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIN_WIDTH,WIN_HEIGHT,0);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
        if(!w){
            printf("Error trying to open the window\n");
            SDL_Quit();
            exit(1);
        }
    
        
        return Window(w, SDL_DestroyWindow);
    }

    inline Renderer CreateRenderer(const Window &w){
        SDL_Renderer *r=SDL_CreateRenderer(w.get(),-1,flags);
        SDL_RenderSetLogicalSize(r, WIDTH, HEIGHT);

        if(!r){
            printf("error trying to open the renderer\n");
            SDL_Quit();
            exit(1);
        }
        
        return Renderer(r, SDL_DestroyRenderer);
    }

    inline Texture LoadTexture(const char* file,const  RendererPtr &r){
        SDL_Texture *t=IMG_LoadTexture(r,file);
        if(!t){
            printf("error trying to create the texture: %s\n",file);
            
            return Texture(nullptr, SDL_DestroyTexture);
            
        }
        return Texture(t, SDL_DestroyTexture);
    }


    inline void RenderClear(Renderer &r){
        SDL_RenderClear(r.get());
    }
    inline void RenderPresent(Renderer &r){
        SDL_RenderPresent(r.get());
    }

    inline void RenderCopy(Renderer &r,TextPtr t, const Rect src, const Rect dest){
        SDL_RenderCopy(r.get(), t, &src, &dest);
    }

}