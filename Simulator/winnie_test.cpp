// If fails to compile, try sudo ln -s /opt/X11/include/X11 /usr/local/include/X11

// my first program in C++
#include <iostream>
#include <string>
#include "CImg/CImg.h"
#include "Graph.hpp"
#include "RGBtoHSV.hpp"
#include <thread>
using namespace cimg_library;

unsigned NUM_THREADS = std::thread::hardware_concurrency();

#define NUM_CRYSTALS 291
// NOTE: FPS maintenance is disabled, breaks when window dynamically rescales
#define FPS_THRESHOLD 0
#define FPS_TARGET 50
#define MAX_SCALE 5
int SCALE = 3;
int IMG_WIDTH = 0;
int IMG_HEIGHT = 0;
int ORIGINAL_WIDTH = 0;
int ORIGINAL_HEIGHT = 0;

const unsigned char white[] = {255, 255, 255};
const unsigned char black[] = {0, 0, 0};

int lookup[NUM_CRYSTALS][2] = {{2133,1552},{2132,1846},{2047,1972},{2119,2083},{2228,2012},{2320,2181},{2091,2208},{2089,2408},{2230,2342},{2345,2451},{2440,2337},{2524,2169},{2691,2310},{2593,2435},{2859,2417},{3099,2416},{3240,2366},{3382,2450},{3596,2419},{3489,2260},{3234,2202},{3243,2008},{3257,1845},{3464,1884},{3422,2078},{3605,2063},{3685,1900},{3895,1859},{3890,2052},{3698,2175},{3883,2256},{3861,2413},{2081,1394},{2303,1414},{2351,1554},{2250,1704},{2330,1861},{2418,2028},{2505,1889},{2417,1724},{2492,1570},{2583,1722},{2680,1857},{2604,2018},{2747,2128},{2949,2283},{3015,2085},{2810,1979},{2868,1828},{3049,1917},{3065,1772},{2876,1659},{2750,1687},{2690,1514},{2863,1475},{3050,1601},{3031,1368},{3166,1299},{3397,1430},{3399,1570},{3213,1502},{3236,1684},{3481,1710},{3713,1680},{3624,1489},{3862,1438},{3910,1635},{2076,1230},{2270,1253},{2261,1107},{2167,988},{2343,881},{2469,956},{2560,1051},{2460,1196},{2478,1295},{2612,1301},{2604,1420},{2894,1299},{2793,1175},{2710,1032},{2850,886},{3047,950},{2977,1064},{3112,1131},{3276,1073},{3274,899},{3486,839},{3476,998},{3643,942},{3676,805},{3836,803},{3936,895},{3799,1028},{3585,1147},{3413,1205},{3482,1325},{3761,1287},{3921,1171},{2000,1092},{2102,842},{2000,658},{2133,540},{2312,398},{2427,309},{2373,116},{2592,61},{2731,174},{2701,327},{2563,378},{2537,558},{2299,563},{2273,741},{2465,729},{2671,761},{2805,648},{2735,551},{2861,437},{3086,449},{3035,620},{3009,787},{3144,793},{3335,746},{3261,622},{3403,504},{3304,362},{3145,280},{2911,213},{3013,62},{3254,99},{3455,132},{3438,262},{3522,343},{3680,278},{3642,84},{3844,46},{3901,195},{3818,410},{3607,494},{3553,683},{3724,591},{3790,642},{3928,625},{3952,442},{1898,842},{1867,540},{1882,340},{2118,340},{2133,114},{1867,114},{1688,398},{1573,309},{1627,116},{1408,61},{1269,174},{1299,327},{1437,378},{1463,558},{1701,563},{1727,741},{1535,729},{1329,761},{1195,648},{1265,551},{1139,437},{914,449},{965,620},{991,787},{856,793},{665,746},{739,622},{597,504},{696,362},{855,280},{1089,213},{987,62},{746,99},{545,132},{562,262},{478,343},{320,278},{358,84},{156,46},{99,195},{182,410},{393,494},{447,683},{276,591},{210,642},{72,625},{48,442},{1924,1230},{1739,1107},{1833,988},{1657,881},{1531,956},{1440,1051},{1540,1196},{1730,1253},{1697,1414},{1522,1295},{1388,1301},{1396,1420},{1106,1299},{1207,1175},{1290,1032},{1150,886},{953,950},{1023,1064},{888,1131},{724,1073},{726,899},{514,839},{524,998},{357,942},{324,805},{164,803},{64,895},{201,1028},{415,1147},{587,1205},{518,1325},{239,1287},{79,1171},{1919,1394},{1867,1552},{1750,1704},{1649,1554},{1508,1570},{1772,2012},{1583,1724},{1582,2028},{1495,1889},{1417,1722},{1320,1857},{1396,2018},{1253,2128},{1051,2283},{985,2085},{1190,1979},{1132,1828},{951,1917},{935,1772},{1124,1659},{1250,1687},{1310,1514},{1137,1475},{950,1601},{969,1368},{834,1299},{603,1430},{601,1570},{787,1502},{764,1684},{519,1710},{287,1680},{376,1489},{138,1438},{90,1635},{2000,1700},{1868,1846},{1953,1972},{1881,2083},{1670,1861},{1680,2181},{1909,2208},{1911,2408},{1770,2342},{1655,2451},{1560,2337},{1476,2169},{1309,2310},{1407,2435},{1141,2417},{901,2416},{760,2366},{618,2450},{404,2419},{511,2260},{766,2202},{757,2008},{743,1845},{536,1884},{578,2078},{395,2063},{315,1900},{105,1859},{110,2052},{302,2175},{117,2256},{139,2413}};
int edges[NUM_CRYSTALS][NUM_CRYSTALS] = {{259,35,33,32,-1},{259,35,4,2,-1},{261,3,1,-1},{6,4,2,-1},{36,5,3,1,-1},{37,10,8,4,-1},{265,8,7,3,-1},{266,8,6,-1},{9,7,6,5,-1},{10,8,-1},{13,11,9,5,-1},{43,37,12,10,-1},{44,14,13,11,-1},{12,10,-1},{45,12,-1},{45,16,-1},{20,17,15,-1},{18,16,-1},{31,19,17,-1},{29,24,20,18,-1},{46,21,19,16,-1},{49,24,22,20,-1},{61,50,23,21,-1},{62,26,24,22,-1},{25,23,21,19,-1},{29,26,24,-1},{63,27,25,23,-1},{66,28,26,-1},{30,29,27,-1},{30,28,25,19,-1},{31,29,28,-1},{30,18,-1},{224,68,67,0,-1},{75,68,34,0,-1},{40,39,35,33,-1},{36,34,1,0,-1},{39,37,35,4,-1},{38,36,11,5,-1},{43,41,39,37,-1},{40,38,36,34,-1},{77,41,39,34,-1},{53,42,40,38,-1},{52,47,43,41,-1},{44,42,38,11,-1},{47,45,43,12,-1},{46,44,15,14,-1},{49,47,45,20,-1},{48,46,44,42,-1},{52,51,49,47,-1},{50,48,46,21,-1},{55,51,49,22,-1},{54,52,50,48,-1},{53,51,48,42,-1},{77,54,52,41,-1},{78,55,53,51,-1},{61,56,54,50,-1},{78,60,57,55,-1},{84,60,58,56,-1},{96,64,59,57,-1},{62,60,58,-1},{61,59,57,56,-1},{62,60,55,22,-1},{63,61,59,23,-1},{66,64,62,26,-1},{96,65,63,58,-1},{97,66,64,-1},{65,63,27,-1},{191,99,69,32,-1},{74,69,33,32,-1},{72,70,68,67,-1},{100,99,71,69,-1},{113,112,72,70,-1},{114,73,71,69,-1},{80,74,72,-1},{75,73,68,-1},{76,74,33,-1},{79,77,75,-1},{76,53,40,-1},{79,56,54,-1},{83,80,78,76,-1},{81,79,73,-1},{120,114,82,80,-1},{121,86,83,81,-1},{84,82,79,-1},{85,83,57,-1},{95,88,86,84,-1},{122,87,85,82,-1},{139,90,88,86,-1},{94,89,87,85,-1},{93,91,90,88,-1},{141,91,89,87,-1},{92,90,89,-1},{93,91,-1},{98,94,92,89,-1},{97,95,93,88,-1},{96,94,85,-1},{97,95,64,58,-1},{98,96,94,65,-1},{97,93,-1},{193,191,70,67,-1},{144,112,101,70,-1},{144,100,-1},{111,-1},{146,111,104,-1},{109,105,103,-1},{147,106,104,-1},{107,105,-1},{127,108,106,-1},{117,109,107,-1},{110,108,104,-1},{116,113,111,109,-1},{112,110,103,102,-1},{113,111,100,71,-1},{114,112,110,71,-1},{115,113,81,72,-1},{119,116,114,-1},{117,115,110,-1},{127,118,116,108,-1},{126,125,119,117,-1},{123,120,118,115,-1},{121,119,81,-1},{123,122,120,82,-1},{139,123,121,86,-1},{124,122,121,119,-1},{138,132,125,123,-1},{131,126,124,118,-1},{129,127,125,118,-1},{128,126,117,107,-1},{129,127,-1},{130,128,126,-1},{134,131,129,-1},{132,130,125,-1},{133,131,124,-1},{138,136,134,132,-1},{135,133,130,-1},{136,134,-1},{137,135,133,-1},{143,140,138,136,-1},{139,137,133,124,-1},{140,138,122,87,-1},{141,139,137,-1},{142,140,90,-1},{143,141,-1},{142,137,-1},{193,159,101,100,-1},{158,-1},{149,147,103,-1},{148,146,105,-1},{152,149,147,-1},{150,148,146,-1},{158,151,149,-1},{156,152,150,-1},{153,151,148,-1},{154,152,-1},{174,155,153,-1},{164,156,154,-1},{157,155,151,-1},{163,160,158,156,-1},{159,157,150,145,-1},{194,160,158,144,-1},{194,161,159,157,-1},{206,195,162,160,-1},{166,163,161,-1},{164,162,157,-1},{174,165,163,155,-1},{173,172,166,164,-1},{170,167,165,162,-1},{206,168,166,-1},{207,170,169,167,-1},{211,186,170,168,-1},{171,169,168,166,-1},{185,179,172,170,-1},{178,173,171,165,-1},{176,174,172,165,-1},{175,173,164,154,-1},{176,174,-1},{177,175,173,-1},{181,178,176,-1},{179,177,172,-1},{180,178,171,-1},{185,183,181,179,-1},{182,180,177,-1},{183,181,-1},{184,182,180,-1},{190,187,185,183,-1},{186,184,180,171,-1},{212,187,185,169,-1},{188,186,184,-1},{215,189,187,-1},{190,188,-1},{189,184,-1},{224,192,99,67,-1},{198,195,193,191,-1},{194,192,144,99,-1},{195,193,160,159,-1},{196,194,192,161,-1},{205,197,195,-1},{200,198,196,-1},{224,199,197,192,-1},{227,225,200,198,-1},{201,199,197,-1},{204,202,200,-1},{245,228,201,-1},{248,246,204,-1},{208,205,203,201,-1},{206,204,196,-1},{207,205,167,161,-1},{211,208,206,168,-1},{209,207,204,-1},{249,210,208,-1},{220,213,211,209,-1},{212,210,207,169,-1},{215,213,211,186,-1},{219,214,212,210,-1},{218,216,215,213,-1},{216,214,212,188,-1},{217,215,214,-1},{218,216,-1},{223,219,217,214,-1},{222,220,218,213,-1},{221,219,210,-1},{256,250,222,220,-1},{257,223,221,219,-1},{222,218,-1},{225,198,191,32,-1},{259,226,224,199,-1},{260,230,227,225,-1},{229,228,226,199,-1},{233,229,227,202,-1},{232,230,228,227,-1},{263,231,229,226,-1},{270,264,232,230,-1},{235,233,231,229,-1},{245,234,232,228,-1},{244,239,235,233,-1},{270,236,234,232,-1},{271,239,237,235,-1},{274,273,238,236,-1},{279,241,239,237,-1},{240,238,236,234,-1},{244,243,241,239,-1},{280,242,240,238,-1},{281,247,243,241,-1},{246,244,242,240,-1},{245,243,240,234,-1},{246,244,233,202,-1},{247,245,243,203,-1},{253,248,246,242,-1},{252,249,247,203,-1},{252,250,248,209,-1},{256,251,249,221,-1},{254,252,250,-1},{253,251,249,248,-1},{281,254,252,247,-1},{282,255,253,251,-1},{285,258,256,254,-1},{257,255,250,221,-1},{258,256,222,-1},{286,257,255,-1},{260,225,1,0,-1},{263,261,259,226,-1},{262,260,2,-1},{265,263,261,-1},{264,262,260,230,-1},{269,267,263,231,-1},{267,266,262,6,-1},{267,265,7,-1},{268,266,265,264,-1},{269,267,-1},{272,270,268,264,-1},{271,269,235,231,-1},{273,272,270,236,-1},{271,269,-1},{271,237,-1},{275,237,-1},{279,276,274,-1},{277,275,-1},{290,278,276,-1},{288,283,279,277,-1},{280,278,275,238,-1},{283,281,279,241,-1},{282,280,253,242,-1},{285,283,281,254,-1},{284,282,280,278,-1},{288,285,283,-1},{286,284,282,255,-1},{287,285,258,-1},{289,288,286,-1},{289,287,284,278,-1},{290,288,287,-1},{289,277,-1}};

// ------------------
// Initialising graph
// ------------------
Graph g(edges, NUM_CRYSTALS);

// ----------------
// Initialising GUI
// ----------------
int t = 0, tP = 0, temp = 0, fps = 0;
CImg<unsigned char> src("src.bmp");
CImg<unsigned char> img(src);

// -------------------
// Available functions
// -------------------
void checkCoordinates(CImg<unsigned char> &img);
void setPixel(CImg<unsigned char> &img, int x, int y, int r, int g, int b);
void getPixel(CImg<unsigned char> &img, int x, int y, int *r, int *g, int *b);
void colourCrystal(CImg<unsigned char> &img, int crystalNum, int r, int g, int b, CImg<unsigned char> &src);
int blackChecker(CImg<unsigned char> &src, int x, int y);

// -------------
// Thread worker
// -------------
void threadJob(int thid, int t, int *d) {

    int start = (float)NUM_CRYSTALS/(float)NUM_THREADS*(float)thid;
    int end = (float)NUM_CRYSTALS/(float)NUM_THREADS*(float)(thid+1)+1;

    // ===============================================================
    // Multithreaded code to simulate goes here.
    //     
    // NOTE: Split all your loops up to start and end using the above 
    //       provided start and end variables to take advantage of 
    //       threaded code.
    // ===============================================================
    // ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

    // // Sample jumping gradient code
    // for(int i = start; i < end; i++) {
    //     float temp = (float) d[i] / 50 * NUM_CRYSTALS;
    //     if(i == t) {
    //         colourCrystal(img, i, 255, 255, 255, src);
    //     } else {
    //         colourCrystal(img, i, temp, temp, temp, src);
    //     }
    //     // colourCrystal(img, i, rand()%256, rand()%256, rand()%256, src);
    // }

    /*
    // Sample shimmering centric gradient code
    for(int i = start; i < end; i++) {
        double hue = ((float)d[i]/50)*360 + t;
        if(hue >= 360) hue = hue - 360;
        rgb curr = hsv2rgb(hue, 
                           (float)(rand()%21)/100+0.8,
                           1-(float)d[i]/14);
        // std::cout << "R:" << curr.r << "G:" << curr.g << "B:" << curr.b << std::endl;
        colourCrystal(img, i, curr.r, curr.g, curr.b, src);
    }
    */   
    // ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
    // ===============================================================
}

int main(int argc,char **argv) {

    std::cout << "Simulator starting..." << std::endl;
    std::cout << "Thread count: " << NUM_THREADS << std::endl;

    // --------------------
    // Initialising threads
    // --------------------
    std::thread *thread = new std::thread[NUM_THREADS];

    // ----------------
    // Initialising GUI
    // ----------------
    IMG_WIDTH = img.width() / SCALE;
    IMG_HEIGHT = img.height() / SCALE;
    ORIGINAL_WIDTH = IMG_WIDTH * SCALE;
    ORIGINAL_HEIGHT = IMG_HEIGHT * SCALE;
    src.resize(IMG_WIDTH, IMG_HEIGHT);
    img.resize(IMG_WIDTH, IMG_HEIGHT);
    // checkCoordinates(img);

    // ----------------------
    // Creates display window
    // ----------------------
    CImgDisplay disp(img, "Simulator [Click anywhere to exit]");
    // disp.toggle_fullscreen();

    // ----------------
    // Enters draw loop
    // ----------------
    int *d = NULL;
    int lenPath = 0;
    int *l = NULL;
    d = g.calcDist(259);
    while(!disp.is_closed() && !disp.button() && !disp.is_keyQ() && !disp.is_keyESC()) {

        // ===============================================================
        // Single-threaded code to simulate goes here.
        //     
        // NOTE: Pay close attention to what's being threaded and not,
        //       only thread parallel operations.
        // ===============================================================
        // ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

        // winter test
        for(int j = 0; j < 25; j++) { 
            for(int i = 0; i < NUM_CRYSTALS; i++) {
                //getPixel(img, (float)lookup[i][0]/4000*IMG_WIDTH, 
                //               (float)lookup[i][1]/4000*IMG_WIDTH, 
                //                &darkR, &darkG, &darkB);
                if (i % (j+3) == 0) {
                    colourCrystal(img, i, 255, 255, 255, src);
                } else {
                    colourCrystal(img, i, 0, rand()%256, 255,src);
                }
            }
            sleep(1);
            disp.display(img).resize(false).wait(1000 / FPS_TARGET);        
        }

        // // Sample muzz light program, with image retention effect
        // l = g.calcLine(rand()%NUM_CRYSTALS, rand()%NUM_CRYSTALS, &lenPath);
        // int tempR = rand()%256;            
        // int tempG = rand()%256;
        // int tempB = rand()%256;
        // int darkR = 0;
        // int darkG = 0;
        // int darkB = 0;
        // for(int i = 0; i < NUM_CRYSTALS; i++) {
        //     getPixel(img, (float)lookup[i][0]/4000*IMG_WIDTH, 
        //                   (float)lookup[i][1]/4000*IMG_WIDTH, 
        //              &darkR, &darkG, &darkB);
        //     colourCrystal(img, i, darkR/1.1,
        //                           darkG/1.1, 
        //                           darkB/1.1, src);   
        // }
        // if(t % 5 == 0) {
        //     for(int i = 0; i < lenPath; i++) {
        //         colourCrystal(img, l[i], tempR,
        //                                  tempG, 
        //                                  tempB, src);
        //     }
        // }
        // t++;
        // delete[] l;


        // ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
        // ===============================================================
        


        // NOTE: tP is time parameter for parallel code
        // d = g.calcDist(tP);
        // ---------------------
        // Starts thread workers
        // ---------------------
        for(int i = 0; i < NUM_THREADS; i++) {
            thread[i] = std::thread(threadJob, i, tP, d);
        }
        // Pauses main until threads all finish
        for(int i = 0; i < NUM_THREADS; i++) {
            thread[i].join();
        }
        // delete[] d;
        // if(++tP > (NUM_CRYSTALS - 1)) tP = 0;
        if(++tP > 360 - 1) tP = 0;

        // Dodgy play and pause mechanism
        if(disp.is_key1()) {
            std::cout << "Paused for 1 second." << std::endl;
            disp.wait(1000);
        } else if(disp.is_key2()) {
            std::cout << "Paused for 2 second." << std::endl;
            disp.wait(2000);
        } else if(disp.is_key3()) {
            std::cout << "Paused for 3 second." << std::endl;
            disp.wait(3000);
        } else if(disp.is_key4()) {
            std::cout << "Paused for 4 second." << std::endl;
            disp.wait(4000);
        } else if(disp.is_key5()) {
            std::cout << "Paused for 5 second." << std::endl;
            disp.wait(5000);
        } else if(disp.is_key6()) {
            std::cout << "Paused for 6 second." << std::endl;
            disp.wait(6000);
        } else if(disp.is_key7()) {
            std::cout << "Paused for 7 second." << std::endl;
            disp.wait(7000);
        } else if(disp.is_key8()) {
            std::cout << "Paused for 8 second." << std::endl;
            disp.wait(8000);
        } else if(disp.is_key9()) {
            std::cout << "Paused for 9 second." << std::endl;
            disp.wait(9000);
        }
        
        // ---------------------------------------------------------------
        // Display current animation framerate, and refresh display window
        // ---------------------------------------------------------------            
        temp = fps;
        fps = disp.frames_per_second();
        if(temp != fps) {
            std::cout << "FPS: " << fps << "/" << FPS_TARGET << std::endl;
        }
        if(fps != 0 && fps < FPS_THRESHOLD && SCALE <= MAX_SCALE) {
            std::cout << "Downscaling to maintain fps" << SCALE << std::endl;
            SCALE++;
            IMG_WIDTH = ORIGINAL_WIDTH / SCALE;
            IMG_HEIGHT = ORIGINAL_HEIGHT / SCALE;
            src.resize(IMG_WIDTH, IMG_HEIGHT);
            img.resize(IMG_WIDTH, IMG_HEIGHT);
            std::cout << IMG_WIDTH << "x" << IMG_HEIGHT << std::endl;
        }
        //img.draw_text(5,5,"%u frames/s",white,0,0.5f,13,(unsigned int)disp.frames_per_second());
        disp.display(img).resize(false).wait(1000 / FPS_TARGET);
    }

    // Frees thread handler
    delete[] thread;

    delete[] d;

    return 0;
}

void checkCoordinates(CImg<unsigned char> &img) {
    for(int i = 0; i < NUM_CRYSTALS; i++) {
        for(int j = -10/SCALE; j < 10/SCALE; j++) {
            for(int k = -10/SCALE; k < 10/SCALE; k++) {
                setPixel(img, (float)lookup[i][0]/4000*IMG_WIDTH + j, (float)lookup[i][1]/4000*IMG_WIDTH + k, 230, 230, 230);
                if(j == k || j == - k) {
                    setPixel(img, (float)lookup[i][0]/4000*IMG_WIDTH + j, (float)lookup[i][1]/4000*IMG_WIDTH + k, 0, 0, 0);
                }
            }
        }
        int x = (float)lookup[i][0]/4000*IMG_WIDTH;
        int y = (float)lookup[i][1]/4000*IMG_WIDTH;

        img.draw_text(x-5,y-5,"%u",black,0,0.5f,13,(unsigned int)i);
    }
}

void setPixel(CImg<unsigned char> &img, int x, int y, int r, int g, int b) {
    if(x < 0 || y < 0 || x >= IMG_WIDTH || y >= IMG_HEIGHT) return;
    img(x, y, 0) = r; // red
    img(x, y, 1) = g; // green
    img(x, y, 2) = b; // blue
}

void getPixel(CImg<unsigned char> &img, int x, int y, int *r, int *g, int *b) {
    if(x < 0 || y < 0 || x >= IMG_WIDTH || y >= IMG_HEIGHT) return;
    (*r) = img(x, y, 0); // red
    (*g) = img(x, y, 1); // green
    (*b) = img(x, y, 2); // blue
}

//for just one crystal atm
//from the highest pixel, colour that crystal, go right until black, note the pixel, go left until no more, go back, go right until no more, go back to middle, repeat
//from the lowest pixel, colour that then keep going up until it hits the colour its trying to colour.
void colourCrystal(CImg<unsigned char> &img, int crystalNum, int r, int g, int b, CImg<unsigned char> &src) {

    int x = (float)lookup[crystalNum][0]/4000*IMG_WIDTH;
    int y = (float)lookup[crystalNum][1]/4000*IMG_WIDTH;

    // // Alternate method, fills in based on existing values
    // unsigned char colour[3];
    // colour[0] = rand() % 256;
    // colour[1] = rand() % 256;
    // colour[2] = rand() % 256;
    // img.draw_fill(x, y, colour);

    // Preferred method, fills in based on source values
    int gucci = 1;
    int x_temp = x;
    int x_temp2 = x;
    int y_temp = y;
    //go down
    while(gucci == 1) {
        while(blackChecker(src, x, y) != 1) {
            setPixel(img, x, y,  r, g, b);
            x++;
        }
        x = x_temp;
        while(blackChecker(src, x, y) != 1) {
            setPixel(img, x, y,  r, g, b);
            x--;
        }
        x++;
        gucci = 0;
        while(blackChecker(src, x, y) != 1) {
            if(blackChecker(src, x, y+1) != 1) {
                gucci = 1;
                x_temp = x;
                break;
            }
            x++;
        }
        if(gucci == 0) break;
        else y++;
    }
    gucci = 1; x = x_temp2; x_temp = x_temp2; y = y_temp;
    //goes up
    while(gucci == 1) {
        while(blackChecker(src, x, y) != 1) {
            setPixel(img, x, y,  r, g, b);
            x++;
        }

        x = x_temp;

        while(blackChecker(src, x, y) != 1) {
            setPixel(img, x, y,  r, g, b);
            x--;
        }
        x++;
        gucci = 0;
        while(blackChecker(src, x, y) != 1) {
            if(blackChecker(src, x, y-1) != 1) {
                gucci = 1;
                x_temp = x;
                break;
            }
            x++;
        }
        if(gucci == 0) break;
        else y--;
    }
}

int blackChecker(CImg<unsigned char> &img, int x, int y) {
    if(x < 0 || y < 0 || x >= IMG_WIDTH || y >= IMG_HEIGHT) return 0;
    int r, g, b;
    getPixel(img, x , y, &r, &g, &b);
    if(r == 0 && g == 0 && b == 0) return 1;
    else return 0;
}