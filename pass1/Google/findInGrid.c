#include <stdio.h>
#include <string.h>
#include <math.h>


#define TRUE  1
#define FALSE 0

typedef unsigned char bool;

typedef struct POS {
    unsigned char pres;
    unsigned char row;
    unsigned char col;
    struct POS *next;
}POS;

int CountPaths (char *grid[], char *find);
int CaculatePos (char *find, char *grid[], POS *find_dist);
bool Accessable (POS *from, POS *to);
int CountPathSub (char *find, int m, POS *find_dist, int ci, POS *p);
int CountPathSubx (char *find, POS *find_dist);
int printPOS (char *findSet, POS *find_dist);

char *grid0[] = {"ABC", "FED","GHI"}; 
char  find0[] = {"ABCDEFGHI"};

char *grid1[] = {"ABC", "FED", "GAI"};
char  find1[] = {"ABCDEA"};

char *grid2[] = {"ABC", "DEF","GHI"};
char  find2[] = {"ABCD"};

char *grid3[] = {"AA", "AA"};
char  find3[] = {"AAAA"};

char *grid4[] = {"ABABA", "BABAB", "ABABA", "BABAB", "ABABA"};

char  find4[] = {"ABABABBA"};

char *grid5[] = {"AAAAA", "AAAAA","AAAAA","AAAAA","AAAAA"};
char  find5[] = {"AAAAAAAAAAA"};

char *grid6[] = {"AB","CD"};
char  find6[] = {"AA"};

int printPOS (char *findSet, POS *find_dist) {
    int i;
    char pf[255];
    int m = strlen (findSet);

    memset (pf, 0, 255 * sizeof (char));

    for (i = 0; i < m; i++) {
        if (pf[findSet[i]])
            continue;

        printf ("findSet[%d]: %c  - POS: ", i, findSet[i]);
        
        if (find_dist[findSet[i]].pres) {
            pf[findSet[i]] = TRUE;
            POS *p = &(find_dist[findSet[i]]);
            printf ("(%u,%u); ", find_dist[findSet[i]].row, find_dist[findSet[i]].col);
            
            p = p->next;
            while (p) {
                printf ("(%u,%u); ", p->row, p->col);
                p = p->next;
            }
        }
        printf ("\n");
    }

    return 1;
}

POS find_dist[255]; 

int main() {

#if 1 /* testing to verify CaculatePos. */
    int i;
    
   
    printf ("\n************************ grid0 *****************************\n");
    memset (find_dist, 0, 255 * sizeof (POS));
    CaculatePos (find0, grid0, find_dist);
    printPOS (find0, find_dist);
    
    printf ("\n************************ grid1 *****************************\n");
    memset (find_dist, 0, 255 * sizeof (POS));
    CaculatePos (find1, grid1, find_dist);
    printPOS (find1, find_dist);

    printf ("\n************************ grid2 *****************************\n");
    memset (find_dist, 0, 255 * sizeof (POS));
    CaculatePos (find2, grid2, find_dist);
    printPOS (find2, find_dist);

    printf ("\n************************ grid3 *****************************\n");
    memset (find_dist, 0, 255 * sizeof (POS));
    CaculatePos (find3, grid3, find_dist);
    printPOS (find3, find_dist);

    printf ("\n************************ grid4 *****************************\n");
    memset (find_dist, 0, 255 * sizeof (POS));
    CaculatePos (find4, grid4, find_dist);
    printPOS (find4, find_dist);

    printf ("\n************************ grid5 *****************************\n");
    memset (find_dist, 0, 255 * sizeof (POS));
    CaculatePos (find5, grid5, find_dist);
    printPOS (find5, find_dist);

    printf ("\n************************ grid6 *****************************\n");
    memset (find_dist, 0, 255 * sizeof (POS));
    CaculatePos (find6, grid6, find_dist);
    printPOS (find6, find_dist);
#endif 

    CountPaths (grid3, find3);

    return 1;
}

void InsertToDist (POS *find_dist, unsigned char pos, int row, int col) {
    POS *p = &(find_dist[pos]);
    
    if (p->pres)
    {
        while (p->next) p = p->next;
        p->next = (POS *)malloc (sizeof (POS));
        p->next->pres = TRUE;
        p->next->row = row;
        p->next->col = col;
        p->next->next = NULL;
    }
    else
    {
        p->pres = TRUE;
        p->row = row;
        p->col = col;
        p->next = NULL;
    }
        
    return;
}

int CountPaths (char *grid[], char *find) {
    int n = (int)strlen(grid[0]);
    int m = (int)strlen(find);
    int i;
    
    CaculatePos (find, grid, find_dist);
    
    /*int pathCnt = CountPathSubx (find, m, find_dist, 0, &find_dist[find[0]]); */
    int pathCnt = CountPathSubx (find, find_dist);

    printf ("pathCnt = %d\n", pathCnt);
    
}

/* */
int CountPathSubx (char *find, POS *find_dist, int ci, POS *p) {

}

/* refer to Data structure: hui shuo */
int CountPathSub (char *find, int m, POS *find_dist, int ci, POS *p)
{
   static int pathCnt = 0;
   
   while (p && p->pres) {
       POS *q = &(find_dist [find [ci+1]]);
       while (q && q->pres) {
           if (Accessable (p, q)) {
               ci++;
               if (ci == m - 1) {
                   /* find[ci] is the last character in find. */
                   pathCnt++;
                   if (pathCnt > 1000000000)
                       pathCnt = -1;

                   return pathCnt;
               }
               CountPathSub (find, m, find_dist, ci, q);
           }
           q = q->next;
       }
       p = p->next;
   }
   return pathCnt;
}

int CaculatePos (char *find, char *grid[], POS *find_dist) {
    int i,j, k;
    int m = strlen (find);
    int n = strlen (grid[0]);

    /* Caculate find's each character's position in grid. 
     * Store the position in find_dist.
     * */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            /* for every character in grid...*/
            for (k = 0; k < m; k++) {
                if (grid[i][j] == find[k]) {
                    /* if it is in find's set, record it. */
                    InsertToDist (find_dist, grid[i][j], i, j);
                    break;
                }
                /* else go a head */
            }
            /* this character is not in find's set, no need to record it. */
        }

    return 1;

}


bool Accessable (POS *from, POS *to)
{
    if (!from->pres || !to->pres)
        return FALSE;
    
    int rowf = from->row, colf = from->col;
    int rowt = to->row, colt = to->col;

    if (from->row == to->row && from->col == to->col)
        return FALSE;
 
    int diff_row = rowf - rowt;
    int diff_col = colf - colt;

    if (diff_row < 0)
        diff_row *= (-1);
    if (diff_col < 0)
        diff_col *= (-1);

    if ((diff_row < 2) && (diff_col < 2))
        return TRUE;
    
    return FALSE;
}
