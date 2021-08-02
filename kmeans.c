#include <stdio.h>
#include <stdlib.h>

double distance(double* p1, double* p2, int dimension);
void freeArrays(double** matrixOFpoints, double** centroids, int lines, long k);
int update_point(double** centroids, double* point, long k, int dimension);
void update_centroids(double** centroids, double** matrixOFpoints, long k, int dimension, int lines);
void print_centroids(double** centroids, long k, int dimension);

int main(int argc, char *argv[]){
    int dimension = 1; 
    long max_iter=0; 
    long k = 0;
    double coordinate;
    char c;
    int lines=0;
    int i,j; 
    int tempAns;
    int ans=1;
    char* finishk;
    char* finishm;

    double** matrixOFpoints; 
    double** centroids; 
    
    if (argc <= 1){
       printf("Invalid input");
        return 0; 
    }
    if (argc > 3){
       printf("Invalid input");
        return 0; 
    }
    k = strtol(argv[1], &finishk ,10);
    if (*finishk != '\0' || k <= 0) {
        printf("k - Invalid input");
        return 0;
    }

    if (argc == 2) {
        max_iter = 200; 
    }else{
        max_iter=strtol(argv[2], &finishm, 10);
        if (max_iter <= 0 || *finishm !='\0') {
            printf("max iter - Invalid input");
            return 0;
        }
    }

    while(scanf("%lf%c", &coordinate, &c) == 2){  
        if((c ==',') && lines == 0){
            dimension++;
        }
        if(c == '\n'){
            lines++;
        }
    }

    if (k >= lines) {
        printf("k - Invalid input");
        return 0;
    }

    centroids = (double**)calloc(k, sizeof(double*));
    matrixOFpoints = (double**)calloc(lines, sizeof(double*));

    for(i = 0;i<lines;i++) {
        matrixOFpoints[i] = (double*)calloc(dimension+1, sizeof(double));
    }

    rewind(stdin);
    for (i=0; i<lines; i++){
        for ( j=0; j<dimension; j++){
            scanf("%lf%c", &coordinate, &c);
            matrixOFpoints[i][j] = coordinate;
        }
        matrixOFpoints[i][dimension] = 0.0;
    }

    for(i = 0;i<k;i++) {
        centroids[i] = (double*)calloc(dimension, sizeof(double));
    }
    rewind(stdin);
    for (i=0; i<k; i++){
        for ( j=0; j<dimension; j++){
            scanf("%lf%c", &coordinate, &c);
            centroids[i][j] = coordinate;
        }
    }
    while(max_iter>0){
        tempAns=0;
        for (i=0; i<lines; i++){
            tempAns=update_point(centroids, matrixOFpoints[i], k, dimension);
            if (tempAns==1){
                ans=1;
            }
        }
        update_centroids(centroids, matrixOFpoints, k, dimension, lines);
        if (ans==0){
            break;
        }
        max_iter-=1;
    }
    print_centroids(centroids, k, dimension);
    freeArrays(matrixOFpoints, centroids, lines, k);
    return 0;
}

double distance(double* p1, double* p2, int dimension){
    double sum= 0.0;
    int i;
    for(i = 0; i < dimension; i++){
        sum += (p1[i]-p2[i])*(p1[i]-p2[i]);
    } 
    return sum;
}

int update_point(double** centroids, double* point, long k, int dimension){
    double dis;
    int index=0;
    double minDistance=distance(point, centroids[0], dimension); 
    int i;
    for (i=1; i<k; i++) {
        dis= distance(point, centroids[i], dimension);
        if (dis < minDistance){
            index=i;
            minDistance=dis;
        }
    }
    if ((int)point[dimension]==index){
        return 0;
    }
    point[dimension]=(double)index;
    return 1;
}
void update_centroids(double** centroids, double** matrixOFpoints, long k, int dimension, int lines){
    int Si=0; 
    double* sum=(double*)calloc(dimension, sizeof(double));
    int i, t, j, r;
    for(i=0; i<k; i++){
        Si=0;
        for(t=0; t<dimension; t++){
                    sum[t]=0;
        }
        for(j=0; j<lines; j++){
            if (i==matrixOFpoints[j][dimension]){
                Si+=1;
                for(t=0; t<dimension; t++){
                    sum[t]+=matrixOFpoints[j][t];
                }
            }
        }
        for(r=0; r<dimension; r++){
            centroids[i][r]=sum[r]/Si;
        }
    }
    free(sum);
}
void print_centroids(double** centroids, long k, int dimension){
    int row;
    int column;
    for (row=0; row<k; row++) {
        for (column=0; column<dimension; column++) {
            printf("%.4f", centroids[row][column]);
            if (column != dimension-1) {
                printf(",");
            }
        }
        printf("\n");
    }
}
void freeArrays(double** matrixOFpoints, double** centroids, int lines, long k) {
    int i;
    for (i = 0; i < lines; ++i) {
        free(matrixOFpoints[i]);
    }
    free(matrixOFpoints);

    for (i = 0; i < k; ++i) {
        free(centroids[i]);
    }
    free(centroids);
}
