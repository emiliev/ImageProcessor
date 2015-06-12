#ifndef PIXEL_H
#define PIXEL_H


class Pixel
{
    public:
        Pixel();
        Pixel(int, int, int);
        Pixel(Pixel const &);
        Pixel& operator=(Pixel const &);

        ~Pixel();

        void setRGB(int,int,int);
        int getRed();
        int getBlue();
        int getGreen();
    protected:
    private:

    int red;
    int green;
    int blue;

    void copyFrom(Pixel const &);
};

#endif // PIXEL_H
