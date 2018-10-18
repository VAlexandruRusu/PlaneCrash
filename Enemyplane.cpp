class Enemyplane
{
private:
    float x,y,LDXCorner,LDYCorner,RUXCorner,RUYCorner;
public:
    void setX(int xc){
        x = xc;
        updateCorners();
    }
    void setY(int yc){
        y = yc;
        updateCorners();
    }
    void setCords(int xc, int yc){
        x = xc;
        y = yc;
        updateCorners();
    }
    void updateCorners(){
        LDXCorner = x-35;
        LDYCorner = y-40;
        RUXCorner = x+35;
        RUYCorner = y+85;
        
    }
    float getX(){
        return x;
    }
    float getY(){
        return y;
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
    
};