#include<iostream>
#include<windows.h>
using namespace std;
#include<conio.h>
#include<math.h>
#include<fstream>

void gotoRowCol(int rpos, int cpos)
{
	int xpos=cpos, ypos = rpos;
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void sleep(int m)
{
        for(int j=0;j<m*21000;j++)
        {

        }
}

void init(char  b[],int dim)
{
    for(int i=0;i<dim*dim;i++)
    {
        b[i]='_';
    }
}

void print_board(char b[],int dim)
{
    for(int i=0;i<dim*dim;i++)
    {
       cout<<"   "<<b[i];
       if((i+1)%dim==0)
       {
           cout<<endl;
       }
    }
}
void ask_for_move(int & ri,int & ci,int &turn)
{
    cout<<"Its turn of player "<<turn+1<<endl;
    cout<<"ri:"<<endl;
    cin>>ri;
        cout<<"ci:"<<endl;
    cin>>ci;
}
int towDto1D(int ri,int ci,int dim)
{
    return ((ri-1)*dim+(ci-1));
}
void write_on_board(char board[],int ri,int ci,int dim,char turn)
{
    int index=towDto1D(ri,ci,dim);
    board[index]=turn;
}
void change_turn(int & turn)
{
    if (turn==0)
    {
        turn=1;
    }
    else
    {
        turn=0;
    }
}
bool islegal(char b[],int ri,int ci,int dim)
{

    if((ri>dim || ci >dim )|| (ri<0 || ci <0))
    {
        return false;
    }
    int index=towDto1D(ri,ci,dim);
//    if (b[index]!='_')int index=towDto1D(ri,ci,dim);
    if (b[index]!='_')
    {
        return false;
    }

    return true;
}
bool boolisdraw(char b[],int dim)
{

        for(int i=0;i<dim*dim;i++)
        {
            if (b[i]=='_')
                {
                    return false;
                }
        }


        return true;
}
bool is_vw(char b[],int dim,int turn)
{
    for(int ci=1;ci<=dim;ci++)

    {
    int count=0;
        for(int ri=1;ri<=dim;ri++)
        {
            int index=towDto1D(ri,ci,dim);
            if(b[index]==turn)
            {
                count ++;
            }
        }
    if(count==dim)
    {
        return true;
    }
    }
        return false;
}
bool is_hw(char b[],int dim,int turn)
{

    for(int ri=1;ri<=dim;ri++)

    {
        int count=0;
        for(int ci=1;ci<=dim;ci++)
        {
            int index=towDto1D(ri,ci,dim);
            if(b[index]==turn)
            {
                count ++;
            }
        }
    if(count==dim)
    {
        return true;
    }
    }
        return false;
}
bool is_d1w(char b[],int dim,int turn)
{
    int count=0,ri;
    for(int ci=1;ci<=dim;ci++)

    {

            ri=ci;
            int index=towDto1D(ri,ci,dim);
            if(b[index]==turn)
            {
                count ++;
            }
    }
    if(count==dim)
    {
        return true;
    }
        return false;

}
bool is_d2w(char b[],int dim,int turn)
{
    int count=0;
    int ri=1;
    for(int ci=dim;ci>0;ci--)

    {


            int index=towDto1D(ri,ci,dim);
            if(b[index]==turn)
            {
                count ++;
            }
            ri ++;
    }
    if(count==dim)
    {
        return true;
    }
    return false;

}
bool iswin(char board[],int dim,int turn)
{
    if(is_hw(board,dim,turn) || is_vw(board,dim,turn) || is_d1w(board,dim,turn) || is_d2w(board,dim,turn)==true)
    {
        return true;
    }
}
void write(int & dim,int & turn,char board[])
{
    ofstream ww("game_file.txt");
    ww<<dim<<endl;
    ww<<turn<<endl;
    for(int i=0;i<dim*dim;i ++)
    {
        ww<<board[i]<<endl;
    }
}
void read(int & dim,int & turn,char board[])
{
    ifstream rr("game_file.txt");
    rr>>dim;
    rr>>turn;
    for(int i=0;i<dim*dim;i++)
    {
        rr>>board[i];
    }
}
int main()
{
    char a1;
    cout<<"Enter ri=0 and ci=0 for exit"<<endl;
    cout<<"Press Any key for new game except 'L' OR 'l'"<<endl;
    cout<<"Press 'L' or 'l' for load game"<<endl;
    cin>>a1;
    system("CLS");
    int dim=1,ri,ci,turn=0,v=0;
    char board[dim*dim];
    if(a1=='L' || a1=='l')
    {
        read(dim,turn,board);
        //board[dim];
        //read1(board,dim);
    }
    else
    {
        cout<<"Enter"<<endl<<"dimension:"<<endl;
        cin>>dim;
        turn=0;
        board[dim*dim];
        init (board,dim);

    }

    char p_symbol[2];
    p_symbol[0]='x';
    p_symbol[1]='0';
    write(dim,turn,board);
    do
    {
        gotoRowCol(2,0);
        print_board(board,dim);
        do
        {
             ask_for_move(ri,ci,turn);
             if(ri==0 && ci==0)
             {
                 exit(2);
             }
        }
       while(islegal(board,ri,ci,dim)==false);
       write_on_board(board,ri,ci,dim,p_symbol[turn]);
       gotoRowCol(2,0);
        print_board(board,dim);
        if(iswin(board,dim,p_symbol[turn])==true)
        {
            v++;
            break;
        }
        change_turn(turn);
              write(dim,turn,board);
    }
    while(boolisdraw(board,dim)==false);
    gotoRowCol(3,30);
    if(v==0)
    {
        cout<<"Match darw"<<endl;
    }
    else
    {
        if(turn==0)
        {
            cout<<"Player 1 is winner"<<endl;
        }
        else
        {
             cout<<"Player 2 is winner"<<endl;
        }
    }



}

