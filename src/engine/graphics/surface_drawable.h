#ifndef SURFACE_DRAWABLE_H
#define SURFACE_DRAWABLE_H

class Surface;

class SurfaceDrawable
{
public:
    SurfaceDrawable() = default;
    virtual ~SurfaceDrawable() = default;

protected:
    friend class Surface;

    virtual void draw(Surface& surface) const = 0;
};

#endif //SURFACE_DRAWABLE_H
