#ifndef RGBTOHSV_H
#define RGBTOHSV_H

// --------------------------
// RGB to HSV conversion code
// --------------------------
typedef struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
} rgb;

//typedef struct {
//    double h;       // angle in degrees
//    double s;       // a fraction between 0 and 1
//    double v;       // a fraction between 0 and 1
//} hsv;
//
//static hsv   rgb2hsv(rgb in);

//static rgb   hsv2rgb(hsv in);

int rgb2hsv(int r, int g, int b)
{
	rgb in = {(double)r/255, (double)g/255, (double)b/255};

    double out;
    double min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    delta = max - min;

    if( in.r >= max )                         // > is bogus, just keeps compilor happy
        out = ( in.g - in.b ) / delta;        // between yellow & magenta
    else
    if( in.g >= max )
        out = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
    else
        out = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan

    out = out * 60.0;                              // degrees
    
    if( out < 0.0 )
        out += 360.0;
        

    out = (((double)out / (double)360) * (double)255);
    
    return (int)out;
}


//rgb hsv2rgb(double h, double s, double v)
//{
//	hsv in = {h, s, v};
//
//    double      hh, p, q, t, ff;
//    long        i;
//    rgb         out;
//
//    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
//        out.r = in.v;
//        out.g = in.v;
//        out.b = in.v;
//        return out;
//    }
//    hh = in.h;
//    if(hh >= 360.0) hh = 0.0;
//    hh /= 60.0;
//    i = (long)hh;
//    ff = hh - i;
//    p = in.v * (1.0 - in.s);
//    q = in.v * (1.0 - (in.s * ff));
//    t = in.v * (1.0 - (in.s * (1.0 - ff)));
//
//    switch(i) {
//    case 0:
//        out.r = in.v;
//        out.g = t;
//        out.b = p;
//        break;
//    case 1:
//        out.r = q;
//        out.g = in.v;
//        out.b = p;
//        break;
//    case 2:
//        out.r = p;
//        out.g = in.v;
//        out.b = t;
//        break;
//
//    case 3:
//        out.r = p;
//        out.g = q;
//        out.b = in.v;
//        break;
//    case 4:
//        out.r = t;
//        out.g = p;
//        out.b = in.v;
//        break;
//    case 5:
//    default:
//        out.r = in.v;
//        out.g = p;
//        out.b = q;
//        break;
//    }
//    out.r = out.r * 255;
//    out.g = out.g * 255;
//    out.b = out.b * 255;
//    return out;
//}

#endif
