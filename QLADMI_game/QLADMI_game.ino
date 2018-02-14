const int col_1 = A0;
const int col_2 = A1;
const int col_3 = A2;
const int col_4 = A3;
const int col_5 = A4;
const int col_6 = A5;

int col1_val;
int col2_val;
int col3_val;
int col4_val;
int col5_val;
int col6_val;
int col7_val;

int black;
int white;

int h = 0;
int j = 0;
int k = 0;
int l = 0;
int m = 0;
int n = 0;
int o = 0;

int matrix[6][7] = {{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  

}

void loop() {
  // put your main code here, to run repeatedly:

  col1_val = analogRead(col_1);
  col2_val = analogRead(col_2);
  col3_val = analogRead(col_3);
  col4_val = analogRead(col_4);
  col5_val = analogRead(col_5);
  col6_val = analogRead(col_6);
  col7_val;
  
  matrix_function(col1_val, matrix, h, 0); 
  matrix_function(col2_val, matrix, j, 1);
  matrix_function(col3_val, matrix, k, 2);
  matrix_function(col4_val, matrix, l, 3);
  matrix_function(col5_val, matrix, m, 4);
  matrix_function(col6_val, matrix, n, 5);
  matrix_function(col7_val, matrix, o, 6);
  
}

void matrix_function(int column_val, int &matrix[6][7], int &i, int col)
{
  if(column_val == black)
  {
    matrix[i][col] = 2;
    i += 1;
  }
  
  else if(column_val == white)
  {
    matrix[i][col] = 1;
    i += 1;
  }
  
}

void default_strategy()
{
  
}

int ThreeInAColumn(int matrix[6][7])
{
  int x = 0;
  int y = 0;
  int z = 0;
  
  
  while(y < 7)
  {
    while(x < 6)
    {
      if(matrix[x][y] == 2)
      {
        z++;
      }
      
      else if(matrix[x][y] == 1)
      {
        z = 0;
      }
      
      else if( z == 3)
      {
        if(x < 6 && matrix[x+1][y] == 0)
        {
          return y;
        }
        
        else
        {
          break;
        }
      }
      
      x++;
    }
    
    y++;
  }

  return 1;  
}

int LookAroundYou(int matrix[][], int colour)
{
  int x = 0;
  int y = 0;
  
  while(x < 6)
  {
    while(y < 7)
    {
      if(matrix[x][y] == colour && (x+1 < 6) && (x-1 >= 0) && (y-1 >= 0) && (y+1 < 7))
      {
        if(matrix[x+1][y] == colour && matrix[x-1][y] == colour)
        {
          if(x+2 < 6)
          {
            if(matrix[x+2][y] == 0)
            {
              return y;
            }
          }
        }
        
        
        else if(matrix[x][y+1] == colour && matrix[x][y-1] == colour)
        {
          if(y-2 >= 0)
          {
            if(matrix[x][y-2] == 0)
            {
              return (y-2);
            }
          }
            
          else if(y+2 < 7)
          {  
            if(matrix[x][y+2] == 0)
            {
              return (y+2);
            }
          }
        }
        
        
        else if(matrix[x+1][y+1] == colour && matrix[x-1][y-1] == colour)
        {
          if(x-2 >= 0 && y-2 >= 0)
          {
            if(matrix[x-2][y-2] == 0)
            {
              return (y-2);
            }
          }
          
          else if(x+2 < 6 && y+2 < 7)
          { 
            if(matrix[x+2][y+2] == 0)
            {
              return (y+2);
            }
          }
          
        }
        
        else if(matrix[x-1][y+1] == colour && matrix[x+1][y-1] == colour)
        {
          if(x-2 >= 0 && y+2 < 7)
          {  
            if(matrix[x-2][y+2] == 0)
            {
              return (y+2);
            }
          }
          
          else if(x+2 < 6 && y-2 >= 0)
          {
            if(matrix[x+2][y-2] == 0)
            {
              return (y-2);
            }
          }
        }
        
        else if(matrix[x][y+1] == 0 && matrix[x][y-1] == colour)
        {
          if(y+2 < 7)
          {  
            if(matrix[x][y+2] == colour)
            {
              return (y+1);
            }
          }
          
        }
        
        else if(matrix[x][y-1] == 0 && matrix[x][y+1] == colour)
        {
          if(y-2 >= 0)
          {
            if(matrix[x][y-2] == colour)
            {
              return (y-1);
            }
          }
        }
        
        else if(matrix[x+1][y+1] == 0 && matrix[x-1][y-1] == colour)
        {
          if(y+2 < 7 && x+2 < 6)
          {
            if(matrix[x+2][y+2] == colour)
            {
              return (y+1);
            }
          }
        }
        
        else if(matrix[x-1][y-1] == 0 && matrix[x-1][y-1] == colour)
        {
          if(y-2 >= 0 x-2 >= 0)
          {
            if(matrix[x-2][y-2] == colour)
            {
              return (y-1);
            }
          }
        }
        
        else if(matrix[x+1][y-1] == 0 && matrix[x-1][y+1] == colour)
        {
          if(y-2 >= 0 && x+2 < 6)
          {
            if(matrix[x+2][y-2] == colour)
            {
              return (y-1);
            }
          }
        }
        
        else if(matrix[x-1][y+1] == 0 && matrix[x+1][y-1] == colour)
        {
          if(y-2 >= 0 x+2 < 6)
          {
            if(matrix[x+2][y-2] == colour)
            {
              return (y+1);
            }
          }
        }
       
          
      }
      y++;
    }
    x++;
  }
  
}


  
