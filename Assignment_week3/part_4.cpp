#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

enum Warrior_type
{
  ICEMAN,
  NINJA,
  DRAGON,
  LION,
  WOLF
};


class Warrior{
public:
    int id;
    int strength;
    int aggressivity;
    Warrior(int a,int b,int c):id(a),strength(b),aggressivity(c){}
};

class Headquarter{
private:
    string name;
    int count;
    int life;
    vector<Warrior> dragon;
    vector<Warrior> ninja;
    vector<Warrior> iceman;
    vector<Warrior> lion;
    vector<Warrior> wolf;
    vector<Warrior_type> create_seq;
    vector<int> strength_list;
public:
    Headquarter(string s, int M,vector<Warrior_type> create_seq,vector<int> strength_list):name(s),count(0),life(M),create_seq(create_seq),strength_list(strength_list){ }
    
    bool new_Warrior(int count_time){
        bool success = false;
        
        if(create_seq.empty()){
            return 0;
        }
        int choice_num = create_seq.size();
        int choice = count%create_seq.size();
        Warrior_type ty;
        
        while(choice_num>0 && !success){
            ty = create_seq[choice];
            if(ty == DRAGON && life >= strength_list[0]){
                count++;
                Warrior warr(count,strength_list[0],0);
                life -= strength_list[0];
                dragon.push_back(warr);
                success = true;
            }else if(ty == NINJA && life >= strength_list[1]){
                count++;
                Warrior warr(count,strength_list[1],0);
                life -= strength_list[1];
                ninja.push_back(warr);
                success = true;
            }else if(ty == ICEMAN && life >= strength_list[2]){
                count++;
                Warrior warr(count,strength_list[2],0);
                life -= strength_list[2];
                iceman.push_back(warr);
                success = true;
            }else if(ty == LION && life >= strength_list[3]){
                count++;
                Warrior warr(count,strength_list[3],0);
                life -= strength_list[3];
                lion.push_back(warr);
                success = true;
            }else if(ty == WOLF && life >= strength_list[4]){
                count++;
                Warrior warr(count,strength_list[4],0);
                life -= strength_list[4];
                wolf.push_back(warr);
                success = true;
            }else{
                choice_num--;
                choice = (choice+1)%5;
            }
            
        }
        
        print_result(count_time,ty,success);
        return success;    
        
    }
    
    void print_result(int count_time,Warrior_type ty,bool success){
        int strength = 0;
        string war;
        int size = 0;
        if(success){
            switch(ty){
                case DRAGON:
                    war = "dragon";
                    strength = strength_list[0];
                    size = dragon.size();
                    break;
                case NINJA:
                    war = "ninja";
                    strength = strength_list[1];
                    size = ninja.size();
                    break;
                case ICEMAN:
                    war = "iceman";
                    strength = strength_list[2];
                    size = iceman.size();
                    break;
                case LION:
                    war = "lion";
                    strength = strength_list[3];
                    size = lion.size();
                    break;
                case WOLF:
                    war = "wolf";
                    strength = strength_list[4];
                    size = wolf.size();
                    break;
                default:
                    cout << "Input is wrong!" << endl;
            }
            
            printf("%03d ",count_time);
            cout << name << " "<< war << " " << count << " born with strength " << strength << ",";
            cout << size << " " << war << " in " << name << " headquarter" << endl;
        }else{
            printf("%03d ",count_time);
            cout << name << " headquarter stops making warriors"<< endl;
        }
    }
};

int main(){
    int total_cases = 0;
    int M;
    int hour=0;
    Warrior_type red[5] = {ICEMAN,LION,WOLF,NINJA,DRAGON};
    Warrior_type blue[5] = {LION,DRAGON,NINJA,ICEMAN,WOLF};
    vector<Warrior_type> create_seq_red(red,red+5);
    vector<Warrior_type> create_seq_blue(blue,blue+5);
    vector<int > strength_list(5,0);
    
    cin >> total_cases;
    for(int i=0;i<total_cases;i++){
        hour = 0;
        cin >> M;
        for(int j=0;j<5;j++){
            cin >> strength_list[j]; 
        }
        cout << "Case:" << i+1 << endl;
        Headquarter red_head("red",M,create_seq_red,strength_list);
        Headquarter blue_head("blue",M,create_seq_blue,strength_list);
        bool red_create = true;
        bool blue_create = true;
        while(red_create || blue_create){
            if(red_create){
                red_create = red_head.new_Warrior(hour);
            }
            if(blue_create){
                blue_create = blue_head.new_Warrior(hour);
            }
            hour++;
        }
    }
}