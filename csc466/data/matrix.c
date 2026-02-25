#include <stdio.h>

void getMatrixElements(int matrix[][2]) {
   printf("\nEnter elements: \n");
   for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
         printf("Enter a%d%d: ", i + 1, j + 1);
         scanf("%d", &matrix[i][j]);
      }
   }
}

// function to multiply two matrices
void multiplyMatrices(int first[][2], int second[][2], int result[][2]) {
   // Initializing elements of matrix mult to 0.
   for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
         result[i][j] = 0;
      }
   }

   // Multiplying first and second matrices and storing it in result
   for (int k = 0; k < 2; k++) {
      for (int i = 0; i < 2; i++) {
         for (int j = 0; j < 2; j++) {
            result[i][j] += first[i][k] * second[k][j];
         }
      }
   }
}

// function to display the matrix
void display(int result[][2]) {

   printf("\nOutput Matrix:\n");
   for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
         printf("%d  ", result[i][j]);
         if (j == 1)
            printf("\n");
      }
   }
}

int main() {
   int first[2][2], second[2][2], result[2][2];

   getMatrixElements(first);
   getMatrixElements(second);
   multiplyMatrices(first, second, result);
   display(result);

   return 0;
}