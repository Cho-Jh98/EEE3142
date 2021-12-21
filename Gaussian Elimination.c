#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void permutation(double** matrix, int col, int row1, int row2);
void print_matrix(double** matrix, int row, int col);
void gauss_jordan(double** matrix, int row, int col, int n_time);
double** make_random_matrix(double** matrix, int row, int col);

int main(int argc, const char * argv[]) {

    int row, col, n_time;
    srand((unsigned int)time(NULL));
    
    printf("원하는 행렬의 크기를 입력하세요(스페이스바로 구분): ");
    scanf("%d %d", &row, &col);
    
    
    if(row > 10 || col > 10){ // 행렬 최대 크기 제한
        printf("행렬의 크기가 10x10 이상입니다\n");
        return 0;
    }
    
    n_time = (row < col) ? row : col; // pivot의 최대 개수
    
    double **matrix;
    /* 2차원 배열에 입력값 만큼 메모리 할당 */
    matrix = (double**)malloc(sizeof(double*) * (row+1));
    for(int i = 0; i < row; i++){
        matrix[i] = (double*)malloc(sizeof(double) * (col+1));
    }
    
    /* 임의의 계수를 갖는 행렬 생성 */
    matrix = make_random_matrix(matrix, row, col);
    
    printf("\n초기 행렬\n");
    print_matrix(matrix, row, col);
    printf("\n\n");
    
    gauss_jordan(matrix, row, col, n_time);
    
    printf("가우스-조던 소거법\n");
    print_matrix(matrix, row, col);

    return 0;
}


void print_matrix(double** matrix, int row, int col){
    
    int i, j;
    
    for(i = 0; i<row; i++){
        for(j = 0; j<col; j++){
            if(matrix[i][j] == -0)
                matrix[i][j] = 0;
            printf("%8.2f", matrix[i][j]);
        }
        printf("\n");
    }
}

void permutation(double** matrix, int col, int row1, int row2){
    
    double* temp_array;
    
    temp_array = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = temp_array;
}

void gauss_jordan(double** matrix, int row, int col, int n_time){

    int i, j, k;
    double ratio = 1, multiply = 1;
    
    for(i = 0; i<n_time; i++){
        
        if(!matrix[i][i]){ // matrix의 i번째 계수가 0인 경우 permuation
            for(j = i+1; j<row; j++){
                if(matrix[j][i]){ // 0이 아닌 계수 찾기 (row별로 찾는다)
                    permutation(matrix, col, i, j);
                    break;
                }
            }
            i--; // elimination이 진행되지 않았으므로 i값 초기화
        }
        
        else{
            ratio = 1/matrix[i][i]; // matrix[i][i]값이 바뀔 것이니 미리 ratio에 저장
        }
        
        /* (i, j)위치의 원소를 1로 바꿔준다. */
        for(j = 0; j < row; j++){
            matrix[i][j] *= ratio;
        }
        
        /* ratio를 이용해 reduction 진행 */
        for(j = i+1; j<row; j++){
            multiply = matrix[j][i]; // matrix[j][i]값이 바뀔 것이니 미리 multily에 저장
            for(k = 0; k<col; k++){
                matrix[j][k] -= matrix[i][k] * multiply;
            }
        }
    }
    
    printf("가우스 소거법\n");
    print_matrix(matrix, row, col);
    printf("\n\n");
    
    /* 여기서 부더 조던 소거법 */
    /* 아래서부터 올라가면서 마찬가지로 ratio를 이용해 reduction 진행 */
    for(i=n_time-1; i>0; i--){
        for(j=i-1; j>=0; j--){
            ratio = matrix[j][i];
            
            for(k=i;k<n_time; k++)
                matrix[j][k] -= ratio * matrix[i][k]; // pivot들이 1이므로 ratio만 곱해서 빼주면 된다.
        }
    }
}

double** make_random_matrix(double** matrix, int row, int col){
    
    int i, j;
    for(i = 0; i<row; i++){
        for(j = 0; j<col; j++){
            matrix[i][j] = ((-1)*(rand() % 2 + 1) * rand() % 9 + 1);
        }
    }
    return matrix;
}
