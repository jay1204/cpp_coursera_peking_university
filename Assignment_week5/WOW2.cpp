#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <map>

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

class Dragon:public Warrior{
public:
    int weap;
    float morale;
    Dragon(int id,int stren,int aggress,int life):Warrior(id,stren,aggress){
        weap = id%3;
        morale = ((float)life)/stren;
    }
    
    void output(){
        map<int,string> weapon;
        weapon[0] = "sword";
        weapon[1] = "bomb";
        weapon[2] = "arrow";
        cout << "It has a " << weapon[weap] << ",and it's morale is ";
        printf("%.2f\n",morale);
    }
};

class Ninja:public Warrior{
public:
    int weap1;
    int weap2;
    Ninja(int id,int stren,int aggress):Warrior(id,stren,aggress){
        weap1 = id%3;
        weap2 = (id+1)%3;
    }
    void output(){
        map<int,string> weapon;
        weapon[0] = "sword";
        weapon[1] = "bomb";
        weapon[2] = "arrow";
        cout << "It has a " << weapon[weap1] << " and a "<<weapon[weap2]<<endl;
    }
};

class Iceman:public Warrior{
public:
    int weap;
    Iceman(int id,int stren,int aggress):Warrior(id,stren,aggress){
        weap  = id%3;
    }
    void output(){
        map<int,string> weapon;
        weapon[0] = "sword";
        weapon[1] = "bomb";
        weapon[2] = "arrow";
        cout << "It has a " << weapon[weap] << endl;
    }
};

class Lion:public Warrior{
public:
    int loyal;
    Lion(int id,int stren,int aggress,int life):Warrior(id,stren,aggress){
        loyal = life;
    }
    
    void output(){
        cout << "It's loyalty is "<< loyal<< endl;
    }
};

class Headquarter{
private:
    string name;
    int count;
    int life;
    vector<Dragon> dragon;
    vector<Ninja> ninja;
    vector<Iceman> iceman;
    vector<Lion> lion;
    vector<Warrior> wolf;
    vector<Warrior_type> create_seq;
    vector<int> strength_list;
    int turn;
public:
    Headquarter(string s, int M,vector<Warrior_type> create_seq,vector<int> strength_list):name(s),count(0),life(M),create_seq(create_seq),strength_list(strength_list),turn(0){ }
    
    bool new_Warrior(int count_time){
        bool success = false;
        
        if(create_seq.empty()){
            return 0;
        }
        int choice_num = create_seq.size();
        turn  = turn%5;
        Warrior_type ty;
        
        while(choice_num>0 && !success){
            ty = create_seq[turn];
            if(ty == DRAGON && life >= strength_list[0]){
                count++;
                turn++;
                Dragon warr(count,strength_list[0],0,life-strength_list[0]);
                life -= strength_list[0];
                dragon.push_back(warr);
                success = true;
                print_success(count_time,ty);
                warr.output();
            }else if(ty == NINJA && life >= strength_list[1]){
                count++;
                turn++;
                Ninja warr(count,strength_list[1],0);
                life -= strength_list[1];
                ninja.push_back(warr);
                success = true;
                print_success(count_time,ty);
                warr.output();
            }else if(ty == ICEMAN && life >= strength_list[2]){
                count++;
                turn++;
                Iceman warr(count,strength_list[2],0);
                life -= strength_list[2];
                iceman.push_back(warr);
                success = true;
                print_success(count_time,ty);
                warr.output();
            }else if(ty == LION && life >= strength_list[3]){
                count++;
                turn++;
                Lion warr(count,strength_list[3],0,life-strength_list[3]);
                life -= strength_list[3];
                lion.push_back(warr);
                success = true;
                print_success(count_time,ty);
                warr.output();
            }else if(ty == WOLF && life >= strength_list[4]){
                count++;
                turn++;
                Warrior warr(count,strength_list[4],0);
                life -= strength_list[4];
                wolf.push_back(warr);
                success = true;
                print_success(count_time,ty);
            }else{
                choice_num--;
                turn = (turn+1)%5;
            }
            
        }
        
        if(!success)
            print_failure(count_time);
        return success;    
        
    }
    
    void print_success(int count_time,Warrior_type ty){
        int strength = 0;
        string war;
        int size = 0;
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
        
    }
    
    void print_failure(int count_time){
        printf("%03d ",count_time);
        cout << name << " headquarter stops making warriors"<< endl;
    }
};

int main(){
    int total_cases = 0;

    int hour=0;
    Warrior_type red[5] = {ICEMAN,LION,WOLF,NINJA,DRAGON};
    Warrior_type blue[5] = {LION,DRAGON,NINJA,ICEMAN,WOLF};
    vector<Warrior_type> create_seq_red(red,red+5);
    vector<Warrior_type> create_seq_blue(blue,blue+5);
    
    
    cin >> total_cases;
    int M[total_cases];
    vector<vector<int> > strength_list(total_cases,vector<int>(5,0));
    
    for(int i=0;i<total_cases;i++){
        cin >> M[i];
        for(int j=0;j<5;j++){
            cin >> strength_list[i][j]; 
        }
        
    }
    
    for(int i=0;i<total_cases;i++){
        hour=0;
        cout << "Case:" << i+1 << endl;
        Headquarter red_head("red",M[i],create_seq_red,strength_list[i]);
        Headquarter blue_head("blue",M[i],create_seq_blue,strength_list[i]);
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