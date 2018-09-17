#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <locale>
#include <map>
#include <cmath>        //abs
#include <cstdlib>
#include <sstream>

//int DS[60][60] = {0};
                       //Global data structure array, this is shitty code will be changed later

struct node{
    int value;
    std::string out;
};

node DS[1000][1000];

void initialize(){
for(int i = 0; i < 1000; i++)
    for(int j = 0; j < 1000; j++)
    {
        DS[i][j].value = 0;
        DS[i][j].out = " ";
    }
}


void printDS(void){                         //Quick print function for array
        for (int i = 0; i < 15; i++){
        for (int j = 0; j < 15; j++){
            // if(DS[i][j].value != 0 || !DS[i][j].out.empty())
            // {
            std::cout << DS[i][j].value << "\t";
            // std::cout << DS[i][j].out << std::endl;
            // }
        }
        std::cout << std::endl;
    }
}

/*void printcheck(std::string message)
{
    std::cout << message << std::endl;
}*/

std::string output(std::string type, std::string s,  int x, int y)
{
    std::stringstream ss, ss2;
    ss << x;
    ss2 << y;
    std::string xstr = ss.str();
    std::string ystr = ss2.str();
    //std::string xstr = std::to_string(x);
    //std::string ystr = std::to_string(y);
    if(type == "D")
        return "Delete " + xstr;
    else if(type == "I")
        return "Insert " + s + " before " + xstr;
    else if(type == "S")
       return "Substitute " + s + " at " + xstr;
    else if(type == "T")
        return "Transpose " + xstr + "-" + ystr;
}
bool leftHand(std::string str, int n)
{
    if(str[n] == '1'||str[n] =='2'||str[n] =='3'||str[n] =='4'||str[n] =='5'||
                          str[n] =='q'||str[n] =='w'||str[n] =='e'||str[n] =='r'||str[n] =='t'||
                          str[n] =='a'|| str[n] == 's' || str[n] =='d'||str[n] =='f'||str[n] =='g'||str[n] =='z'||
                          str[n] =='x'||str[n] =='c'||str[n] =='v'||str[n] =='b')
        return true;
    else
        return false;
}

bool rightHand(std::string str, int n)
{
    if(str[n]  =='6'||str[n] =='7'||str[n] =='8'||str[n] =='9'||str[n] =='0'||
                      str[n] =='y'||str[n] =='u'||str[n] =='i'||str[n] =='o'||str[n] =='p'||
                      str[n] =='h'||str[n] =='j'||str[n] =='k'||str[n] =='l'||str[n] ==';'||
                      str[n] =='n'||str[n] =='m'||str[n] ==','||str[n] =='.')
        return true;
    else
        return false;
}

bool bottomRow(std::string str, int n)
{
    if(str[n] == 'z'||str[n] =='x'||str[n] =='c'||str[n] =='v'||str[n] =='b'||
                      str[n] =='n'||str[n] =='m'||str[n] ==','||str[n] =='.')
        return true;
    else
        return false;
}

bool sameHand(std::string a, int x, std::string b, int y)
{
    if((rightHand(a, x) && rightHand(b, y)) || (leftHand(a, x) && leftHand(b, y)))
        return true;
    else
        return false;
}

int finger(std::string str, int n)//same finger other hand returns the same value
{
    if(str[n] == 'q'|| str[n] =='a'||str[n] == 'z'||str[n] == '1')
        return 1;
    if(str[n] == 'w' || str[n] =='s' || str[n] =='x' ||str[n] == '2' )
        return 2;
    if(str[n] == 'e' ||str[n] == 'd' || str[n] == 'c' || str[n] == '3' )
        return 3;
    if(str[n] == 'r' || str[n] =='f' ||str[n] == 'v' || str[n] =='t' || str[n] =='g' || str[n] =='b' ||str[n] == '4' ||str[n] == '5'  )
        return 5;
    if(str[n] == 'y' || str[n] =='h' || str[n] =='n' || str[n] =='u' ||str[n] =='j' ||str[n] == 'm' ||str[n] == '6' || str[n] =='7' )
        return 5;
    if(str[n] == 'i' || str[n] =='k' || str[n] ==',' || str[n] =='8' )
        return 3;
    if(str[n] == 'o' || str[n] =='l' ||str[n] == '.' ||str[n] == '9' )
        return 2;
    if(str[n] == 'p' ||str[n] == ';' || str[n] =='0')
        return 1;
}

int distance(char key1, char key2){

    std::map < char, int > keyboard;

    char symbols[40] =  {   '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
                            'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
                            'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
                            'z', 'x', 'c', 'v', 'b', 'n', 'n', 'm', ',', '.'};


    for (int i = 0; i < 41; i++){       //Assigns each character a value 0-40
        keyboard[symbols[i]] = i;
    }

    int row2 = keyboard[key2] / 10,     //Integer division trucates the 1's place, gives me the row value
        row1 = keyboard[key1] / 10,
        col2 = keyboard[key2] % 10,     //Modulo by 10 gives me the 1's place, gives me the column value
        col1 = keyboard[key1] % 10;

    int distance = std::max(abs(row2 - row1), abs(col2 - col1));    //Given distance function

    return distance;
}

int insert(std::string target, std::string typostring, int i, int j) {
    if(target[i] != typostring[j] && typostring[j] != '\0') {
        if(typostring[j-1] == typostring[j]){   //repeated char from typo string, because target -> typo


                return 1;
        }
        else if(bottomRow(typostring, j-1) && typostring[j] == ' ' && typostring[j] != '\0') {      //space after key on bottom row

                return 2;
        }

        else if(!bottomRow(typostring, j-1) && typostring[j] == ' ' ) {     //space after something else
               return 6;
        }

        else if (j == 0 && ((sameHand(typostring, j, typostring, j+1))
                        && typostring[j] != typostring[j+1])){              // BEFORE/AFTER KEY ON SAME HAND, if start of string

                // std::cout << "DISTANCE1" << std::endl;                   //commented out test code to determine which dist is being called
                return distance(target[i], typostring[j]);
        }
        else if (j != 0 && (((sameHand(typostring, j, typostring, j-1))
                        || ((sameHand(typostring, j, typostring, j+1))))
                        && typostring[j] != typostring[j+1])){              // BEFORE/AFTER KEY ON SAME HAND, not start of string


                // std::cout << "DISTANCE2" << std::endl;                   //commented out test code to determine which dist is being called
                return distance(target[i], typostring[j]);
        }


        else if((j == 0 && (!sameHand(typostring, j, typostring, j+1)))) {  //  BEFORE/AFTER KEY ON OPPOSITE HAND, if start of string

             return 5;
        }
        else if((j != 0 && (!sameHand(typostring, j, typostring, j-1))
                        || (!sameHand(typostring, j, typostring, j+1)))) {  //  BEFORE/AFTER KEY ON OPPOSITE HAND, not start of string                                                                                               // on oppisite hand

             return 5;
        }

        else if(typostring[j + 1] == ' '){

            return 6;
        }

        else {
            return 9001;
        }
    }

    else {return 9002;}
}

int del(std::string target, std::string typostring, int i, int j)
{

    if(target[i] != typostring[j] && target[i] != '\0')
    {

        if(typostring[j] == '\0')
        {
            if(i = 0)
            {
                return 6;
            }
            else if(target[i-1] == target[i])   //repeated char from typo string, because target -> typo
            {
                return 1;
            }
            else if(sameHand(target, i, typostring, j-1) && target[i] != typostring[j-1]) // character after one on same hand
            {
                return 2;
            }

            else if(target[i] == ' ' && typostring[j] != ' ') //delete a space ***how can typostring[j] = space = /0?
            {
                return 3;
            }

            else if((!sameHand(target,i, typostring, j-1)) || (target[i-1] == ' '))
            {
                return 6;            //character after space or a key from a different hand
            }
            else return 7001;

        }
        else
        {
            if(target[0] != typostring[0])//delete first character in string
            {
                // std::cout << "F." << std::endl;
                return 6;
            }
            else if(typostring[j-1] == typostring[j])   //repeated char from typo string, because target -> typo
            {
                return 1;
            }
            else if(sameHand(target, i, typostring, j-1) && target[i] != typostring[j-1]) // character after one on same hand
            {
                return 2;
            }
            else if(target[i] == ' ' && typostring[j] != ' ') //delete a space
            {
                return 3;
            }
            else if((!sameHand(target, i, typostring, j-1)) || (typostring[j-1] == ' '))
            {
                // std::cout << "F." << std::endl;
                return 6;            //character after space or a key from a different hand
            }
            else return 8001;

        }
    }
    else{
        return 9001;
    }
    // if(target[0] != typostring[0])           //This was breaking things?
      // return 0;
}

int sub(std::string target, std::string typostring, int i, int j)
{
    if(typostring[j] != target[i] && target[i] != '\0'&& typostring[j] != '\0')
    {

        if(!sameHand(typostring, j, target, i) && (finger(target, i) == finger(typostring, j))) //same finger other hand
        {
            // if (typostring[j] == 'f')    std::exit(0);
            return 1;
        }

        else if(sameHand(typostring, j, target, i) && target[i] != typostring[j]) // key for another on same hand
        {


            // if (typostring[j] == 'f')    std::exit(0);
            return distance(typostring[j], target[i]);
        }
        else if(!sameHand(typostring, j, target, i) && (finger(target, i) != finger(typostring, j)))// other finger different hand  FIX THIS
        {
            // if (typostring[j] == 'f')    std::exit(0);
            return 5;
        }

        else if(typostring[j]== ' ' || target[i] == ' ') //space for anythin or anything for space
        {
             // if (typostring[j] == 'f')   std::exit(0);
             return 6;
        }

        else{
            return 9001;
        }
    }
    else return 9001;
}

int transpose(std::string target, std::string typostring, int i, int j)
{
    std::string s(1,target[i]);
    DS[i][j].out = output("T",s,j,j+1);
    if(target[i]== typostring[j+1] && target[i+1] == typostring[j])
    {
        if(!sameHand(typostring, j, typostring, j+1)){// transpose letters on different hands
            return 1;
        }
        else if(target[i] == ' ' || target[j] == ' '){ // space transposed with something
            return 3;
        }
        else if(sameHand(typostring, j, typostring, j+1)){//transpose same hand
            return 2;
        }
    }
   return 9001;
}

int cost(std::string target, std::string typostring, int i, int j, bool *TransPointer)
{

    std::string s(1,typostring[j]);
    int costIns = insert(target, typostring, i, j);
    int costDel = del(target, typostring, i, j);
    int costSub = sub(target, typostring, i, j);
    int costTns = transpose(target, typostring, i, j);


    int min = std::min(costIns, std::min(costDel, std::min(costSub, costTns)));


    if (min == costTns){
        DS[i][j].out = output("T",s,j,j+1);
        *TransPointer = 1;
        return min;
    }

    // else if (min == costIns && min == costSub && min == 1){
        // DS[i][j].out = output("S",s,j,j+1);
        // return min;
    // }

    else if (min == costIns){
        DS[i][j].out = output("I",s,j,j+1 );
        return min;
    }

    else if (min == costSub){
        // if (typostring[j] == 'a')    std::exit(0);
        DS[i][j].out = output("S",s,j,j+1);
        return min;
    }

    else if (min == costDel){
        // if (typostring[j] == 'a')    std::exit(0);
        DS[i][j].out = output("D",s,j,j+1);
        return min;
    }

    else return 9001;

}

void debug(std::string s, char a, char b, int i, int j){
}


node typo(std::string target, std::string typostring, int i, int j)
{

    if (DS[i][j].value != 0){
        debug("[MEMO] DS value found, return", target[i], typostring[j], i, j);
        return DS[i][j];
    }

    if (target[i] == '\0' && typostring[j] == '\0'){
        debug("[EOL] END OF LINE FOR BOTH STRINGS, return", target[i], typostring[j], i, j);
        DS[i][j].value = 0;                                       //When both strings are at end
        DS[i][j].out = "";
        return DS[i][j];
    }

    else if (target[i] == typostring[j]){
        debug("[EQL] Characters are equal", target[i], typostring[j], i, j);

        node next = typo(target, typostring, i + 1, j + 1);

        DS[i][j].value = next.value;  //When chars are equal
        DS[i][j].out = next.out;
        return DS[i][j];
    }

    else if (target[i] == '\0' && typostring[j] != '\0'){
        debug("[INS] Target is at end, insert", target[i], typostring[j], i, j);
        bool *p, b = 0; p = &b;
        node path = typo(target, typostring, i, j + 1);
        DS[i][j].value = path.value + cost(target, typostring, i, j, p);
        DS[i][j].out.append("\n");
        DS[i][j].out.append(path.out);
        // DS[i][j].value =  typo(target, typostring, i, j + 1).value + insert(target, typostring, i, j);       //End of Target string
        // std::cout << "INSERT = " << insert(target, typostring, i, j) << std::endl;
        return DS[i][j];
    }

    else if (target[i] != '\0' && typostring[j] == '\0'){
        debug("[DEL] typostring is at end, delete", target[i], typostring[j], i, j);
        bool *p, b = 0; p = &b;
        node path = typo(target, typostring, i + 1, j);
        DS[i][j].value = path.value + cost(target, typostring, i, j, p);
        DS[i][j].out.append("\n");
        DS[i][j].out.append(path.out);

  // DS[i][j].value = typo(target, typostring, i + 1, j).value + del(target, typostring, i, j);      //End of typostring string
        // std::cout << "DELETE = " << del(target, typostring, i, j) << std::endl;
        return DS[i][j];
    }

    debug("[MIN] Branch 3 ways at Min function", target[i], typostring[j], i, j);

        bool *TransPointer, b = 0;          //Creates bool pointer/placeholder val, default 0
        TransPointer = &b;
        int inc = 1, costVal = cost(target, typostring, i, j, TransPointer);    //Calls/stores cost, defines typo() index incrementer
        if(*TransPointer){++inc;}                   //If transpose was the most optimal cost() choice, typo() increments indexes by +2

        node paths[3];
        paths[0] = typo(target, typostring, i + inc, j);
        paths[1] = typo(target, typostring, i, j + inc);
        paths[2] = typo(target, typostring, i + inc, j + inc);

        // std::cout << "OUT OF LOOP 1 DS[i][j].out = \n----\n" << DS[i][j].out << "\n----\n" << std::endl;
        DS[i][j].out.append("\n");
        DS[i][j].value = std::min(paths[0].value, std::min(paths[1].value, paths[2].value));

        for (int iter = 0; iter < 3; iter++){
            // std::cout << "paths[" << iter << "].out =  " << paths[iter].out << std::endl;
            if (paths[iter].value == DS[i][j].value){
                DS[i][j].out.append(paths[iter].out);
                break;
            }
        }
        // std::cout << "OUT OF LOOP 2 DS[i][j].out = \n----\n" << DS[i][j].out << "\n----\n" << std::endl;

        DS[i][j].value += costVal;

        return DS[i][j];
}

int main()
{
     std::fstream file;
     std::ofstream outFile;
     std::string target, typostring;
     file.open("input.txt");

     std::string OP;
     std::getline(file, OP);
     int numOP = stoi(OP);

    std::string blankLine = " ";
    outFile.open("output.txt");
    int i = 0;
    while (i < numOP)
    {
      std::getline(file, target);
      std::getline(file, typostring);
      initialize();
      typo(target, typostring, 0,0);
    //  printDS();
      i++;

      std::getline(file, blankLine);
      outFile << DS[0][0].value << "\n" << DS[0][0].out << "\n";
    }
    file.close();
    outFile.close();

  //  std::cout << "FINAL OUT STATEMENT:  \n----\n" << DS[0][0].out << "\n----\n" << std::endl;
  //  std::cout << "FINAL VAL STATEMENT: " << DS[0][0].value << std::endl;
}
