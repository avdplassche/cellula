#ifndef VEC2_HPP
# define VEC2_HPP

class Vec2 {

public:
    Vec2(float x_init, float y_init);
    float x, y;
    Vec2& operator=(const Vec2&);

    void    setValues(float, float);
    void    normalize();
    void    inverse();

private:
    float   dist;


};






#endif // !VEC2_HPP

