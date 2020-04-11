#include <iostream>
#include <string>
#include <fstream>

// test if valid for cell
using namespace std;

  //helper to print
  void print_board(int board[][9])
  {
      int i=0;
      int j=0;
      for (i=0; i<9; i++)
      {
          for (j=0; j<9; j++)
          {
              if (j == 8)
              {
                  cout<<board[i][j]<<endl;
              }
              else
              {
                  cout<<board[i][j]<<",";
              }
          }
      }
  }

int valid(int board[][9],int number, int row, int col)
{
    //define the math needed to find other 4 points
    //cout<<"here"<<endl;
    int i=0;
    int sector_row = 3*(row/3);
    int sector_col = 3*(col/3);
    int r1 = (row+2)%3;
    int r2 = (row+4)%3;
    int c1 = (col+2)%3;
    int c2 = (col+4)%3;

    // Check in start row and col
    for (i=0; i<9; i++) {
        if (board[i][col] == number)
        {
          return 0;
        }
        if (board[row][i] == number)
        {
          return 0;
        }
    }

    //check other 4 spots
    if(board[r1+sector_row][c1+sector_col] == number)
    {
      return 0;
    }
    if(board[r2+sector_row][c1+sector_col] == number)
    {
      return 0;
    }
    if(board[r1+sector_row][c2+sector_col] == number)
    {
      return 0;
    }
    if(board[r2+sector_row][c2+sector_col] == number)
    {
      return 0;
    }
    return 1;
}



int traverse(int board[9][9], int row, int col)
{
  //base
  if (row==9)
  {
    return 1;
  }

  int next = 1;

      // Check if given

      if (board[row][col])
      {
          if (col == 8)
          {
              if ((traverse(board, row+1, 0))==true)
              {
                return 1;
              }
          }
          else
          {
              if ((traverse(board, row, col+1)) == true)
              {
                 return 1;
              }
          }
          return 0;
      }



 //Iterate through all valid numbers
  // recurse for all valid ones

  while (next<10)
  {
    if (valid(board, next, row, col) == true)
    {
      board[row][col] = next;
      if (col == 8)
      {
        if (traverse(board, row+1, 0)==true)
        {
          return 1;
        }
      }
        else
        {
          if (traverse(board, row, col+1)==true)
          {
            return 1;
          }
        }
        board[row][col] =0;
      }
      next++;
    }
      //cout<<"here"<<endl;
    return 0;
  }

  int main(int argc, char** argv)
  {
    //argv[1]
    ifstream infile;
    string file = argv[1];
    int board[9][9];
    int row = 9;
    int col = 9;
    infile.open(file);
    int k = 0;
    int i = 0;
    string temp = "";
    while (k<row)
    {
      getline(infile, temp);
      {
        for (int j = 0; j<col; j++)
        {
          board[i][j] = temp[j*2] - 48;
        }
        i++;
      }
      k++;
    }

    //cout<<"here"<<end;
    infile.close();

    //start traverling at 0,0
    int start = traverse(board, 0, 0);

    //print board
    print_board(board);

  }
