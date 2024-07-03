#ifndef DRAWABLE_H
#define DRAWABLE_H

class Window;

class Drawable
{
public:
    Drawable() = default;
    virtual ~Drawable() = default;

protected:
    friend class Window;

    virtual void draw(Window& window) const = 0;
};

#endif //DRAWABLE_H
