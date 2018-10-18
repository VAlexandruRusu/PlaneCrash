#include <math.h>
class Boss1
{
    private:
        float wing1x,wing1y;//point 1 coords
        float wing2x,wing2y;
        float theta;//the angle step
        float length;//length of wing
        float radius;//radius of circle it rotates around
        float theta_increment;
        float xcord;
        float ycord;
        float LDXCorner,LDYCorner,RUXCorner,RUYCorner;
    
    public:
        Boss1(float theta1, float length1, float radius1,float theta_increment1){
           theta=theta1,length=length1,radius=radius1;theta_increment=theta_increment1;
        }
        void setWing1x(float xcord){
            wing1x = xcord;
        }
        void setWing1y(float ycord){
            wing1y = ycord;
        }
        float getWing1x(){
            return wing1x;
        }
        float getWing1y(){
            return wing1y;
        }
        void setWing2x(float xcord){
            wing2x = xcord;
        }
        void setWing2y(float ycord){
            wing2y = ycord;
        }
        float getWing2x(){
            return wing2x;
        }
        float getWing2y(){
            return wing2y;
        }
        void setTheta(float t){
            theta = t;
        }
        float getTheta(){
            return theta;
        }
        void setLength(float l){
            length = l;
        }
        float getLength(){
            return length;
        }
        void setRadius(float r){
            radius = r;
        }
        float getRadius(){
            return radius;
        }
        void setXcord(float x){
            xcord = x;
            updateCorners();
        }
        float getXcord(){
         return xcord;   
        }
        void setYcord(float y){
            ycord = y;
            updateCorners();
        }
        float getYcord(){
         return ycord;   
        }
        void updateWing(){
            wing1x = cos(theta)*radius;
            wing1y = sin(theta)*radius;
            wing2x = cos(theta)*length;
            wing2y = sin(theta)*length;
            theta += theta_increment;
        }
        float getLDXCorner(){
            return LDXCorner;
        }
        float getLDYCorner(){
            return LDYCorner;
        }
        float getRUXCorner(){
            return RUXCorner;
        }
        float getRUYCorner(){
            return RUYCorner;
        }
        
        void updateCorners(){
        LDXCorner = xcord-25;
        LDYCorner = ycord-80;
        RUXCorner = xcord+25;
        RUYCorner = ycord+170;
        
    }
};