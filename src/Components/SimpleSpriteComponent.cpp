#include "Components/SimpleSpriteComponent.h"
#include "SDL_wrapper.h"
#include "Entity.h"
#include "Components/TransformComponent.h"
#include "Components/HealthComponent.h"
#include <cmath>


constexpr float  PI = 3.14150f;
inline float deg2rad(float deg){
    return ((deg*PI)/180);
}

SimpleSpriteComponent::SimpleSpriteComponent(){

}

SimpleSpriteComponent::SimpleSpriteComponent(float radius,int sides,SDL::Color color):radius(radius),sides(sides),color(color),firstColor(color)
 ,secColor(color){
    secColor.a /=2;
}

void SimpleSpriteComponent::init(){
    tc=entity->getComponent<TransformComponent>();
    hc=entity->getComponent<HealthComponent>();
    
    
}

void SimpleSpriteComponent::render(SDL::RendererPtr r){

    float x = tc->getPos().x ;
    float y = tc->getPos().y ;
    
    auto auxColor= color;
    auxColor.a=static_cast<Uint8>(auxColor.a*0.60f);
    drawPolygon(x,y,radius,r,auxColor);
    drawPolygon(x,y,radius*0.70f,r,color); 

    if(hc){
        if(hc->getStatus() != &Status::None){
            drawPolygon(x,y,2,r,hc->getStatus()->statusColor);
        }
    }
    

} 

void SimpleSpriteComponent::drawPolygon(float x ,float y,float rad,SDL::RendererPtr r,SDL::Color c){

    std::vector<int> index((sides-2)*3);//number of triangles we need to draw a regular shape is its sides-2()
    //triangule fan rule
    for(int i=0;i<sides-2;i++){
        index[i*3]={0};
        index[i*3+1]={i+1};
        index[i*3+2]={i+2};
    }                
    float angle=deg2rad(360.0f/sides);
    std::vector<SDL_Vertex> vertex(sides);
    
    for(int i=0;i<sides;i++){

        vertex[i]={SDL_FPoint{x+rad*sin(angle*i),y-rad*cos(angle*i)},c,{0,0}}; 
       
    }

    
    SDL_RenderGeometry(r,nullptr,vertex.data(),sides,index.data(),(sides-2)*3);
}