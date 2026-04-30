#pragma once


#include <SDL2/SDL.h>
#include <memory>

//=============================================================
// Wrapper for SDL2
//=============================================================

//logical width and height
constexpr int WIDTH=480; 
constexpr int HEIGHT=270;

//real window size
constexpr int WIN_WIDTH=1280;
constexpr int WIN_HEIGHT=720;

constexpr Uint32 Rendererflags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

namespace SDL{

    //---TYPEDEFS-----------

    //new object to make SDL objects memory safe
    using Window = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;

    using Renderer = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;//smart pointer WITH ownership
    using RendererPtr = SDL_Renderer*; //observer-purpose only 

    using Texture = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>; //smart pointer WITH ownership
    using TextPtr = SDL_Texture*; //observer

    using Rect =  SDL_Rect;
    using FRect =  SDL_FRect;
    using Event = SDL_Event;
    using Color= SDL_Color;

    inline auto renderClear(RendererPtr r)        { return SDL_RenderClear(r); }
    inline auto renderPresent(RendererPtr r)       { return SDL_RenderPresent(r); }
    inline auto renderDrawRect(RendererPtr r,Rect rect){return SDL_RenderDrawRect(r, &rect); }
    inline auto renderFillRect(RendererPtr r, Rect rect){return SDL_RenderFillRect(r,&rect); }
    inline auto renderFillRectF(RendererPtr r, FRect rect){return SDL_RenderFillRectF(r,&rect); }
    inline auto setRenderDrawColor(RendererPtr ren,Uint8 r ,Uint8 b,Uint8 g,Uint8 a){return SDL_SetRenderDrawColor(ren,r,b,g,a);}

    //colors
    namespace Colors{
        
        inline constexpr SDL_Color Red   = {255, 0, 0, 255};
        inline constexpr SDL_Color Green = {0, 255, 0, 255};
        inline constexpr SDL_Color Blue  = {0, 0, 255, 255};
        inline constexpr SDL_Color Clear = {0, 0, 0, 0};
        inline constexpr SDL_Color NeonPink    = {255, 0, 255, 255};   
        inline constexpr SDL_Color Electric    = {255, 255, 30, 255};   
        inline constexpr SDL_Color Toxic       = {57, 255, 20, 255};   
        inline constexpr SDL_Color SunFlower   = {241, 196, 15, 255};  
        inline constexpr SDL_Color Pumpkin     = {211, 84, 0, 255};    
        inline constexpr SDL_Color VoidDust = {75, 0, 130, 50};
        inline constexpr SDL_Color Ice         ={224, 255, 255, 255};
        inline constexpr SDL_Color Fire = {255, 80, 0, 255};
        inline constexpr SDL_Color Player = {0, 255, 128, 255};
        inline constexpr SDL_Color NeonPurple = {180, 0, 255, 255};

    }
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
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
        if(!w){
            printf("Error trying to open the window\n");
            SDL_Quit();
            exit(1);
        }
    
        
        return Window(w, SDL_DestroyWindow);
    }

    inline Renderer CreateRenderer(const Window &w){
        SDL_Renderer *r=SDL_CreateRenderer(w.get(),-1,Rendererflags);
        SDL_RenderSetLogicalSize(r, WIDTH, HEIGHT);
        SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND); //active blendmode for transparency
        if(!r){
            printf("error trying to open the renderer\n");
            SDL_Quit();
            exit(1);
        }
        
        return Renderer(r, SDL_DestroyRenderer);
    }

/*     inline Texture LoadTexture(const char* file,RendererPtr r){
        SDL_Texture *t=IMG_LoadTexture(r,file);
        if(!t){
            printf("error trying to create the texture: %s\n",file);
            
            return Texture(nullptr, SDL_DestroyTexture);
            
        }
        return Texture(t, SDL_DestroyTexture);
    } */


    inline void RenderClear(RendererPtr r){
        SDL_RenderClear(r);
    }
    inline void RenderPresent(RendererPtr r){
        SDL_RenderPresent(r);
    }

    inline void RenderCopy(RendererPtr r,TextPtr t, Rect* src,Rect* dest){
        SDL_RenderCopy(r, t, src, dest);
    }

}