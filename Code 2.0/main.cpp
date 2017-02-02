#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <vector>
using namespace std;
#include "Graph.hpp"

#define NRM "\x1B[0m"
#define C0 "\x1B[40m"
#define C1 "\x1B[100m"
#define C2 "\x1B[47m"
#define C3 "\x1B[107m"
#define C4 "\x1B[7m"

#define MAX_CRYSTALS_NUM 19
#define MAX_EDGE_PER_CRYSTAL MAX_CRYSTALS_NUM

void p(int *dist, int i, char *panel, int space);
void draw(int *d);

// int main(int argc, char *argv[]) {
// 
//    int edges[MAX_CRYSTALS_NUM][MAX_EDGE_PER_CRYSTAL + 1] = {{-1},
//                                                             {3, 4, 2, 7, 6, 5, 16, 15, 18, -1},
//                                                             {4, 9, 8, 7, 6, 1, 3, -1},
//                                                             {12, 11, 4, 2, 1, 16, 15, 18, 13, -1},
//                                                             {11, 10, 9, 2, 1, 3, 12, -1},
//                                                             {1, 6, 16, -1},
//                                                             {1, 2, 7, 5, -1},
//                                                             {2, 9, 8, 6, 1, -1},
//                                                             {9, 7, 2, -1},
//                                                             {10, 8, 7, 2, 4, 11, -1},
//                                                             {9, 4, 11, -1},
//                                                             {10, 9, 4, 3, 12, -1},
//                                                             {11, 4, 3, 18, 13, -1},
//                                                             {12, 3, 18, 17, -1},
//                                                             {16, 5, -1},
//                                                             {18, 3, 1, 16, -1},
//                                                             {15, 18, 3, 1, 6, 5, 14, -1},
//                                                             {13, 18, -1},
//                                                             {17, 13, 12, 3, 1, 16, 15, -1}};
// 
//    int **edgesP = new int*[MAX_CRYSTALS_NUM];
//    for(int i=0; i<MAX_CRYSTALS_NUM; i++) {
//        edgesP[i] = new int[MAX_EDGE_PER_CRYSTAL + 1];
//        int j=0;
//        while(1) {
//            edgesP[i][j] = edges[i][j];
//            j++;
//            if(edges[i][j] == -1) {
//                edgesP[i][j] = edges[i][j];
//                break;
//            }
//        }
//    }
//    std::cout << "start of thing\n";
//    Graph g(edgesP, MAX_CRYSTALS_NUM);
//    for(int i=0;i < MAX_CRYSTALS_NUM; i++) {
//        delete[] edgesP[i];
//    }
//    delete[] edgesP;
//    cout << "END\n";
// 
//    return EXIT_SUCCESS;
// }

int main(int argc, char ** argv) {
    int edges[MAX_CRYSTALS_NUM][MAX_EDGE_PER_CRYSTAL + 1] = {{-1}, {7, 4, 2, 18, 15, 3, 16, 6, 5, -1}, {8, 9, 7, 6, 4, 3, 1, -1}, {11, 13, 12, 4, 2, 18, 16, 15, 1, -1}, {10, 12, 11, 9, 3, 2, 1, -1}, {14, 16, 6, 1, -1}, {7, 2, 16, 5, 1, -1}, {9, 8, 6, 2, 1, -1}, {9, 7, 2, -1}, {11, 10, 8, 7, 4, 2, -1}, {11, 9, 4, -1}, {10, 9, 12, 4, 3, -1}, {11, 4, 18, 13, 3, -1}, {17, 18, 12, 3, -1}, {16, 5, -1}, {18, 16, 3, 1, -1}, {14, 18, 15, 3, 6, 5, 1, -1}, {18, 13, -1}, {17, 13, 12, 16, 15, 3, 1, -1}};

    Graph g(edges,19);
    int scanfFlag = 1;
    int src = 0;
    int *d = NULL;
    
    // Recalculates distance
    d = g.calcDist(src);
    // Draws the mosaic
    draw(d);

    delete[] d;
    
    while(src != -1 && scanfFlag == 1) {
       printf("\nEnter origin: ");
       scanfFlag = scanf("%d", &src);

       if(src < 0 || src > MAX_CRYSTALS_NUM) {
          src = 0;
       }

       // Recalculates distance
       d = g.calcDist(src);
       // Clears the screen
       system("clear");
       // Draws the mosaic
       draw(d);

       delete[] d;
    }

}

void p(int *dist, int i, const char *panel, int space) {

   int len = strlen(panel) / 3;
   int j = 0;

   for(j = 0; j < len; j++) {
      if(dist[i] == 0) {
         printf(C0 " " NRM);
      } else if(dist[i] == 1) {
         printf(C1 " " NRM);
      } else if(dist[i] == 2) {
         printf(C2 " " NRM);
      } else if(dist[i] == 3) {
         printf(C3 " " NRM);
      } else if(dist[i] >= 4) {
         printf(C4 " " NRM);
      }
   }

   for(j = 0; j < space; j++) {
      printf(" ");
   }
   if(space == 0) {
      printf("\n");
   }
}

void draw(int *d) {

    // for(int i=0; i<MAX_CRYSTALS_NUM; i++) {
    //     cout << d[i] << " ";
    // }
    // cout <<endl;
            p(d,10,"██████████",2);                    p(d,9,"███████████████",3);                     p(d,8,"██████████",0);
printf("  "); p(d,10,"███████",2);                    p(d,9,"█████████████████",3);                     p(d,8,"███████",0);   
p(d,11,"█",3);  p(d,10,"███",3);                     p(d,9,"███████████████████",3);                     p(d,8,"███",4);p(d,7,"█",0);
            p(d,11,"███",6);                        p(d,9,"█████████████████████",6);                        p(d,7,"████",0);
            p(d,11,"██████",2);                    p(d,9,"███████████████████████",2);                    p(d,7,"███████",0);
            p(d,11,"██████",4);                      p(d,9,"███████████████████",4);                      p(d,7,"███████",0);
            p(d,11,"██████",1);         p(d,4,"██",2);p(d,9,"█████████████████",2);p(d,2,"██",1);         p(d,7,"███████",0);
            p(d,11,"██████",1);         p(d,4,"███",3); p(d,9,"█████████████",3); p(d,2,"███",1);         p(d,7,"███████",0);
            p(d,11,"██████",1);         p(d,4,"█████",3); p(d,9,"██████████",2);p(d,2,"█████",1);         p(d,7,"███████",0);
            p(d,11,"██████",1);         p(d,4,"███████",2);p(d,9,"███████",2);p(d,2,"███████",1);         p(d,7,"███████",0);
            p(d,11,"██████",1);         p(d,4,"████████",3); p(d,9,"███",2);p(d,2,"█████████",1);         p(d,7,"███████",0);
printf("  "); p(d,11,"████",1);         p(d,4,"██████████",5);             p(d,2,"██████████",1);         p(d,7,"████",0);
            p(d,12,"█",4);p(d,11,"█",1);p(d,4,"████████████",1);         p(d,2,"████████████",1); p(d,7,"█",4);p(d,6,"██",0);
            p(d,12,"███",4);            p(d,4,"████████████",1);         p(d,2,"████████████",3);           p(d,6,"█████",0);
            p(d,12,"██████",3);           p(d,4,"██████████",1);         p(d,2,"██████████",3);           p(d,6,"███████",0);
            p(d,12,"█████",2);p(d,3,"█",2);p(d,4,"█████████",1);         p(d,2,"█████████",2);p(d,1,"█",2);p(d,6,"██████",0);
            p(d,12,"█████",2);p(d,3,"███",2);p(d,4,"███████",1);         p(d,2,"███████",2);p(d,1,"███",2);p(d,6,"██████",0);
            p(d,12,"█████",2);p(d,3,"████",3); p(d,4,"█████",1);         p(d,2,"█████",3); p(d,1,"████",2);p(d,6,"██████",0);
            p(d,12,"█████",2);p(d,3,"██████",2);p(d,4,"████",1);         p(d,2,"████",2);p(d,1,"██████",2);p(d,6,"██████",0);
            p(d,12,"█████",2);p(d,3,"████████",2);p(d,4,"██",1);         p(d,2,"██",2);p(d,1,"████████",2);p(d,6,"██████",0);
printf("  "); p(d,12,"███",2);p(d,3,"█████████",2);p(d,4,"█",1);         p(d,2,"█",2);p(d,1,"█████████",2);p(d,6,"███",0);
            p(d,13,"█",6);    p(d,3,"███████████",3);                               p(d,1,"███████████",6)    ;p(d,5,"██",0);
            p(d,13,"████",3); p(d,3,"████████████",1);                             p(d,1,"████████████",3); p(d,5,"█████",0);
            p(d,13,"█████",4);  p(d,3,"██████████",1);                             p(d,1,"██████████",4);  p(d,5,"██████",0);
            p(d,13,"████",2);p(d,18,"██",2);p(d,3,"█████████",1);       p(d,1,"█████████",2);p(d,16,"██",2);p(d,5,"█████",0);
            p(d,13,"███",2);p(d,18,"█████",2);p(d,3,"███████",1);       p(d,1,"███████",3); p(d,16,"████",2);p(d,5,"████",0);
            p(d,13,"██",2);p(d,18,"███████",2);p(d,3,"██████",1);       p(d,1,"██████",2);p(d,16,"███████",2);p(d,5,"███",0);
            p(d,13,"█",2);p(d,18,"██████████",2);p(d,3,"████",1);       p(d,1,"████",2);p(d,16,"██████████",2);p(d,5,"██",0);
printf("  ");            p(d,18,"████████████",3); p(d,3,"██",1);       p(d,1,"██",3); p(d,16,"████████████",2);p(d,5,"█",0);
printf(" ");            p(d,18,"███████████████",2);p(d,3,"█",1);       p(d,1,"█",2); p(d,16,"███████████████",0);
                       p(d,18,"█████████████████",5);                                p(d,16,"██████████████████",0);
printf(" ");            p(d,18,"████████████████",5);                                p(d,16,"█████████████████",0);
printf("  ");            p(d,18,"█████████████",3);        p(d,15,"███",3);            p(d,16,"██████████████",0);
            p(d,17,"█",2);p(d,18,"███████████",2);       p(d,15,"███████",2);           p(d,16,"████████████",2);p(d,14,"█",0);
            p(d,17,"██",2);p(d,18,"████████",2);       p(d,15,"██████████",2);           p(d,16,"██████████",2);p(d,14,"██",0);
            p(d,17,"███",2);p(d,18,"█████",2);       p(d,15,"██████████████",2);           p(d,16,"███████",2);p(d,14,"███",0);

/*

   // FIX UP THIS PIXEL DRAWING (COPY RIGHT TO LEFT, AND MAP IT ONTO "DRAW")

   printf("██████████  ███████████████   ██████████\n"
          "  ███████  █████████████████   ███████  \n"
          "█   ███   ███████████████████   ███    █\n"
          "███      █████████████████████      ████\n"
          "██████  ███████████████████████  ███████\n"
          "██████    ███████████████████    ███████\n"
          "██████ ██  █████████████████  ██ ███████\n"
          "██████ ███   █████████████   ███ ███████\n"
          "██████ █████   ██████████  █████ ███████\n"
          "██████ ███████  ███████  ███████ ███████\n"
          "██████ ████████   ███  █████████ ███████\n"
          "  ████ ██████████     ██████████ ████   \n"
          "█    █ ████████████ ████████████ █    ██\n"
          "███    ████████████ ████████████   █████\n"
          "██████   ██████████ ██████████   ███████\n"
          "█████  █  █████████ █████████  █  ██████\n"
          "█████  ███  ███████ ███████  ███  ██████\n"
          "█████  ████   █████ █████   ████  ██████\n"
          "█████  ██████  ████ ████  ██████  ██████\n"
          "█████  ████████  ██ ██  ████████  ██████\n"
          "  ███  █████████  █ █  █████████  ███   \n"
          "█      ███████████   ███████████      ██\n"
          "████   ████████████ ████████████   █████\n"
          "█████    ██████████ ██████████    ██████\n"
          "████  ██  █████████ █████████  ██  █████\n"
          "███  █████  ███████ ███████   ████  ████\n"
          "██  ███████  ██████ ██████  ███████  ███\n"
          "█  ██████████  ████ ████  ██████████  ██\n"
          "  ████████████   ██ ██   ████████████  █\n"
          " ███████████████  █ █  ███████████████  \n"
          "█████████████████     ██████████████████\n"
          " ████████████████     █████████████████ \n"
          "  █████████████   ███   ██████████████  \n"
          "█  ███████████  ███████  ████████████  █\n"
          "██  ████████  ██████████  ██████████  ██\n"
          "███  █████  ██████████████  ███████  ███\n");
*/

}