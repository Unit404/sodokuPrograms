#include "SodokuBoard.h"

SodokuBoard::SodokuBoard(std::fstream& ifs)
{
    for(int i = 0;i<9;i++)
    {
        for(int j = 0;j<9;j++)
        {
            if(board[i][j]==0)
            {
                zeroes++;
                for(int num=1;num<=9;num++)
                    possible[i][j][num]=1;

                possible[i][j][0]=9;
            }
            else
            {
                possible[i][j][0]=0;
                for(int num=1;num<=9;num++)
                    possible[i][j][num]=0;
            }
        }
    }
    
    // char c;
    // int i=0, j=0, row=0, col=0;
    // while(ifs)
    // {
    //         i++;
    //         j++;
    //         row=i%9;
    //         col=(i-i%9)/9;
    //         ifs>>c;
    //         // std::cout <<"read character"<<std::endl;
            
    //         // std::cout << c;
    //         if(c<='9' && c>='1')
            
    //         {
    //             board[row][col]=(int)c-'0';
    //             possible[row][col][0]=0;
    //         }
    //         else
    //         {
    //             board[i][j]=0;
    //             for(int num=1;num<=9;num++)
    //                 possible[row][col][num]=1;
    //             possible[row][col][0]=9;
    //         }
    //     }
}
void SodokuBoard::printBoard()
{
    for(int i =0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            std::cout<<board[i][j]<<" ";
            if(j%3==2)
                std::cout<<" ";
        }
        std::cout<<std::endl;
        if(i%3==2)
            std::cout << std::endl;
    }
    std::cout<<"____________________________________________________________________________________"<<std::endl;
}

void SodokuBoard::removePossibility(int row, int col, int target)
{
    if(possible[row][col][target]==0 || board[row][col]!=0)//if we already know that this cell cant be the target, do nothing
        return;
    possible[row][col][target]=0; //update the possibilities to say that the cell cant be the target
    possible[row][col][0]--; //the 0th index of the final sub array is used to indicate how much 
}
void SodokuBoard::updateRow(int row, int target)
{
    for(int col=0;col<9;col++)
    {
         removePossibility(row,col,target);
    }
}

void SodokuBoard::updateColumn(int col, int target)
{
    for(int row=0;row<9;row++)
    {
         removePossibility(row,col,target);
    }
}
void SodokuBoard::updateSector(int row, int col, int target)
{
    // std::cout<<"SECTOR::::::::::: "<<row<<" "<<col<<" "<<target<<std::endl;
    // std::cout<<row-row%3<<" "<<row-row%3+3<< " || " <<(row/3)*3<<" " <<(row/3+1)*3<<std::endl;
    // std::cout<<col-col%3<<" "<<col-col%3+3<< " || " <<(col/3)*3<<" " <<(col/3+1)*3<<std::endl;
    for(int i = row-row%3;i<row-row%3+3;i++)
    {
        for(int j = col-col%3;j<col-col%3+3;j++)
        {
            removePossibility(i,j,target);
        }
    }
}
void SodokuBoard::updatePossibilities()
{
    for(int i =0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            int num=board[i][j];
            if(num==0)
            {
                continue;
            }//if the cell is empty, then skip to next cell because we cant gain any info from it
            else
            {
                updateColumn(j,num);
                updateRow(i,num);
                updateSector(i,j,num);
            }
        }
    }
}
bool SodokuBoard::update()
{
    updatePossibilities();
    bool changed=false;
    for(int i = 0; i< 9;i++)
    {
        for(int j = 0;j<9;j++)
        {
            if(possible[i][j][0]==1)
            {
                zeroes--;
                changed=true;   
                std::cout << i << " " << j<<std::endl;
                for(int num = 1;num<=9;num++)
                    if(possible[i][j][num]==1)
                    {
                        board[i][j]=num;
                        possible[i][j][num]=0;
                        possible[i][j][0]=0;
                        break;
                    }
            }             
        }
    }
    if(!changed)
    {
        checkPossibilities();
    }
    return zeroes!=0;
}

//checks to see if a target possibility only appears once in a given row, if it does, fill in that possiblity
void SodokuBoard::checkRow(int row, int target)
{
    int counter = 0, pos=-1;
    for(int col=0;col<9;col++)
    {
        if(possible[row][col][target]==1)
        {
            counter++;
            pos=col;
            if(counter>=2)
                return;
        }
            
    }
    if(pos==-1){return;}
    for(int i = 0;i<=9;i++)
    {
        possible[row][pos][i]=0;
    }
    zeroes--;
    board[row][pos]=target;
    updateColumn(pos,target);
    updateRow(row,target);
    updateSector(row,pos,target);

}

void SodokuBoard::checkColumn(int col, int target)
{
    int counter = 0, pos=-1;
    for(int row=0;row<9;row++)
    {
        if(possible[row][col][target]==1)
        {
            counter++;
            pos=row;
            if(counter>=2)
                return;
        }
    }
            
    if(pos==-1){return;}
    for(int i = 0;i<=9;i++)
    {
        possible[pos][col][i]=0;
    }
    zeroes--;
    board[pos][col]=target;
    updateColumn(col,target);
    updateRow(pos,target);
    updateSector(pos,col,target);



}

void SodokuBoard::checkSector(int row, int col, int target)
{
    int counter = 0, Rpos=-1, Cpos=-1;
    for(int R = row-row%3; R< row+3-row%3;R++)
    {
        for(int C = col-col%3;C<col+3-col%3;C++)
        {
            if(possible[R][C][target]==1)
            {
                counter++;
                if(counter>=2)
                    return;
                Rpos=R;
                Cpos=C;
            }
        }
    }
    if(Rpos==-1){return;}
    for(int i = 0;i<=9;i++)
    {
        possible[Rpos][Cpos][i]=0;
    }
    zeroes--;
    board[Rpos][Cpos]=target;
    updateColumn(Cpos,target);
    updateRow(Rpos,target);
    updateSector(Rpos,Cpos,target);

}


void SodokuBoard::checkPossibilities()
{
    for(int i = 0;i<9;i++)
    {
        for(int j = 0;j<9;j++)
        {
            if(board[i][j]!=0)
            {
                continue;
            }
            else
            {
                for(int num=1;num<=9;num++)
                {
                    if(possible[i][j][num]==1)
                    {
                        checkRow(i,num);
                        checkColumn(j,num);
                        checkSector(i,j,num);
                    }
                }
            }
        }
    }
}

void SodokuBoard::set(int row, int col, int num)
{
    for(int i = 0;i<=9;i++)
    {
        possible[row][col][i]=0;
    }
    zeroes--;
    board[row][col]=num;
}