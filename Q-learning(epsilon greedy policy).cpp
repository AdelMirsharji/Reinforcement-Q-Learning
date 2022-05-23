#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

class State{
    public:
    int num;
    int x;
    int y;
    int d;

    void print(){
        cout << endl << "State-" << num << " cor:" << endl << "X = " << x << endl << "Y = " << y << endl << "Dam = " << d << endl;
    }

    void set_state(int num, int x, int y, int d){
        this->num = num;
        this->x = x;
        this->y = y;
        this->d = d;
    }

    State(int num, int x, int y, int d){
        this->num = num;
        this->x = x;
        this->y = y;
        this->d = d;
    }
};

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int my_max(int a , int b, int c, int d){
    int max = a;

    if(b > max)
        max = b;
    if(c > max)
        max = c;
    if(d > max)
        max = d;

    return max;
}

double my_max2(double a , double b, double c, double d){
    int max = a;

    if(b > max)
        max = b;
    if(c > max)
        max = c;
    if(d > max)
        max = d;

    return max;
}

void calculate_q(State start,vector<double> &q_values,vector<int> &can_go,double q_table[50][4],int reward[25],double alpha, double gama){
    int initial_state_id = start.num;
    int initial_ev;
    int initial_odd;
    if(initial_state_id % 2 == 0){
        initial_ev = initial_state_id;
        initial_odd = initial_state_id + 1;
    }
    if(initial_state_id % 2 != 0){
        initial_ev = initial_state_id - 1;
        initial_odd = initial_state_id;
    }
    
    //goes to left
    int q_left_id = initial_state_id - 2;
    double q_left;
    int left_reward;
    if(initial_ev == 0 || initial_ev == 10 || initial_ev == 20 || initial_ev == 30 || initial_ev == 40){
        q_left = -100;
        q_table[initial_state_id][0] = -100;
        q_values.push_back(q_left);
        can_go.push_back(0);
    }
    else{
        if(q_left_id % 2 == 0)
            left_reward = reward[q_left_id/2];
        if(q_left_id % 2 != 0)
            left_reward = reward[(q_left_id-1)/2];

        if(left_reward == -10){
            if(start.d == 0)
                left_reward = 0;
        }

        double m1 = my_max(q_table[q_left_id][0], q_table[q_left_id][1], q_table[q_left_id][2], q_table[q_left_id][3]);

        q_left = ((1 - alpha) *q_table[initial_state_id][0]) + (alpha * (left_reward + gama * m1));
        q_table[initial_state_id][0] = q_left;
        q_values.push_back(q_left);
        can_go.push_back(1);
    }

    //goes right
    int q_right_id = initial_state_id + 2;
    double q_right;
    int right_reward;
    if(initial_odd == 9 || initial_odd == 19 || initial_odd == 29 || initial_odd == 39 || initial_odd == 49){
        q_right = -100;
        q_table[initial_state_id][1] = -100;
        q_values.push_back(q_right);
        can_go.push_back(0);
    }
    else{
        if(q_right_id % 2 == 0)
            right_reward = reward[q_right_id/2];
        if(q_right_id % 2 != 0)
            right_reward = reward[(q_right_id-1)/2];

        if(right_reward == -10){
            if(start.d == 0)
                right_reward == 0;
        }

        double m2 = my_max(q_table[q_right_id][0],q_table[q_right_id][1],q_table[q_right_id][2],q_table[q_right_id][3]);
        q_right = ((1 - alpha) *q_table[initial_state_id][1]) + (alpha * (right_reward + gama * m2));
        q_table[initial_state_id][1] = q_right;
        q_values.push_back(q_right);
        can_go.push_back(1);
    }

    //goes up
    int q_up_id = initial_state_id - 10;
    double q_up;
    int up_reward;
    if(initial_ev == 0 || initial_ev == 2 || initial_ev == 4 || initial_ev == 6 || initial_ev == 8){
        q_up = -100;
        q_table[initial_state_id][2] = -100;
        q_values.push_back(q_up);
        can_go.push_back(0);
    }
    else{
        if(q_up_id % 2 == 0)
            up_reward = reward[q_up_id/2];
        if(q_up_id % 2 != 0)
            up_reward = reward[(q_up_id-1)/2];

        if(up_reward == -10){
            if(start.d == 0)
                up_reward = 0;
        }

        double m3 = my_max(q_table[q_up_id][0],q_table[q_up_id][1],q_table[q_up_id][2],q_table[q_up_id][3]);
        q_up = ((1 - alpha) *q_table[initial_state_id][2]) + (alpha * (up_reward + gama * m3));
        q_table[initial_state_id][2] = q_up;
        q_values.push_back(q_up);
        can_go.push_back(1);
    }

    //goes down
    int q_down_id = initial_state_id + 10;
    double q_down;
    int down_reward;
    if(initial_ev == 40 || initial_ev == 42 || initial_ev == 44 || initial_ev == 46 || initial_ev == 48){
        q_down = -100;
        q_table[initial_state_id][3] = -100;
        q_values.push_back(q_down);
        can_go.push_back(0);
    }
    else{
        if(q_down_id % 2 == 0)
            down_reward = reward[q_down_id/2];
        if(q_down_id % 2 != 0)
            down_reward = reward[(q_down_id-1)/2];

        if(down_reward == -10){
            if(start.d == 0)
                down_reward = 0;
        }

        double m4 = my_max(q_table[q_down_id][0],q_table[q_down_id][1],q_table[q_down_id][2],q_table[q_down_id][3]);
        q_down = ((1 - alpha) *q_table[initial_state_id][3]) + (alpha * (down_reward + gama * m4));
        q_table[initial_state_id][3] = q_down;
        q_values.push_back(q_down);
        can_go.push_back(1);
    }
}

int main(){

    double Q_table[50][4] = {0};
    int reward[25] = {0};
    reward[0] = +10;
    reward[7] = -10;
    int episode_number = 1000;
    double learning_rate = 0.1;
    double discount_rate = 0.5;
    double epsilon = 0.2;
    cout << endl << "Please enter needed informations:" << endl;
    cout << "Numebr of episodes = ";
    cin >> episode_number;
    cout << "Learning rate = ";
    cin >> learning_rate;
    cout << "Discount rate = ";
    cin >> discount_rate;
    cout << "Epsilon rate = ";
    cin >> epsilon;

    vector<State> states;
    int counter = 0;
    for(int i = 0 ; i < 5 ; ++i){
        for(int j = 0 ; j < 5 ; ++j){
            for(int k = 0 ; k < 2 ; ++k){
                State s(counter,i,j,k);
                states.push_back(s);
                counter++;
            }
        }
    }

    int initial_state_x = rand() % (5+1 - 0) + 0;
    int initial_state_y = rand() % (5+1 - 0) + 0;
    cout << endl << "Random start state:" << endl << "x = " << initial_state_x << "   Y = " << initial_state_y << endl;

    State start_state(0,0,0,0);
    for(State st : states){
        if(st.x == initial_state_x){
            if(st.y == initial_state_y){
                if(st.d == 0)
                    start_state.set_state(st.num,st.x,st.y,0);
            } 
        }
    }
    start_state.print();

    vector<double> q_values;
    vector<int> can_go;
    double max_q;
    int next_state_num;
    int next_state_x;
    int next_state_y;
    int next_state_d;
    int wall_in_right = 0;
    int wall_in_left = 0;
    int m;
    int p1;

    for(int step = 0 ; step <= episode_number ; ++step){
        wall_in_left = 0;
        wall_in_right = 0;
        if(start_state.num == 0 || start_state.num == 1){
            cout << endl << "Target reached the goal" << endl;
            break;
        }
        if(start_state.num == 0 || start_state.num == 5 || start_state.num == 10)
            wall_in_right = 1;
        if(start_state.num == 6 || start_state.num == 11)
            wall_in_left = 1;
        if(start_state.num == 1){
            wall_in_left = 1;
            wall_in_right = 1;
        }
        

        q_values.clear();
        can_go.clear();
        calculate_q(start_state,q_values,can_go,Q_table,reward,learning_rate,discount_rate);
        max_q = my_max2(q_values[0],q_values[1],q_values[2],q_values[3]);
        double p = fRand(0.0,1.0);
        if(p > epsilon){
            for(m = 0 ; m < 4 ; m++){
                if(max_q == q_values[m]){
                    switch (m){
                    case 0:
                        next_state_num = start_state.num - 2;
                        next_state_x = start_state.x;
                        next_state_y = start_state.y - 1;
                        if(next_state_x == 0 && next_state_y == 1)
                            next_state_d == 0;
                        else
                            next_state_d = start_state.d;
                        break;

                    case 1:
                        next_state_num = start_state.num + 2;
                        next_state_x = start_state.x;
                        next_state_y = start_state.y + 1;
                        if(next_state_x == 0 && next_state_y == 1)
                            next_state_d == 0;
                        else
                            next_state_d = start_state.d;
                        break;

                    case 2:
                        next_state_num = start_state.num - 10;
                        next_state_x = start_state.x - 1;
                        next_state_y = start_state.y;
                        if(next_state_x == 0 && next_state_y == 1)
                            next_state_d == 0;
                        else
                            next_state_d = start_state.d;
                        break;

                    case 3:
                        next_state_num = start_state.num + 10;
                        next_state_x = start_state.x + 1;
                        next_state_y = start_state.y;
                        if(next_state_x == 0 && next_state_y == 1)
                            next_state_d == 0;
                        else
                            next_state_d = start_state.d;
                        break;
                    
                    default:
                        break;
                    }

                break;
                }
            }
            start_state.set_state(next_state_num,next_state_x,next_state_y,next_state_d);
            start_state.print();
        }
        
        else if(p < epsilon){
            p1 = rand() % (3+1 - 0) + 0;
            switch (p1){
                case 0:
                    next_state_num = start_state.num - 2;
                    next_state_x = start_state.x;
                    next_state_y = start_state.y - 1;
                    if(next_state_x == 0 && next_state_y == 1)
                        next_state_d == 0;
                    else
                        next_state_d = start_state.d;
                    break;

                case 1:
                    next_state_num = start_state.num - 2;
                    next_state_x = start_state.x;
                    next_state_y = start_state.y + 1;
                    if(next_state_x == 0 && next_state_y == 1)
                        next_state_d == 0;
                    else
                        next_state_d = start_state.d;
                    break;

                case 2:
                    next_state_num = start_state.num - 10;
                    next_state_x = start_state.x - 1;
                    next_state_y = start_state.y;
                    if(next_state_x == 0 && next_state_y == 1)
                        next_state_d == 0;
                    else
                        next_state_d = start_state.d;
                    break;

                case 3:
                    next_state_num = start_state.num + 10;
                    next_state_x = start_state.x + 1;
                    next_state_y = start_state.y;
                    if(next_state_x == 0 && next_state_y == 1)
                        next_state_d == 0;
                    else
                        next_state_d = start_state.d;
                    break;
                
                default:
                    break;
            }
            start_state.set_state(next_state_num,next_state_x,next_state_y,next_state_d);
        }

        if(wall_in_right){
            if(p > epsilon){
                if(m == 0){
                    cout << endl << "Hitted a wall in left!" << endl;
                }
            }
            if(p < epsilon){
                if(p1 == 0){
                     cout << endl << "Hitted a wall in left!" << endl;
                }
            }
        }

        if(wall_in_left){
            if(p > epsilon){
                if(m == 1){
                    cout << endl << "Hitted a wall in right!" << endl;
                }
            }
            if(p < epsilon){
                if(p1 == 1){
                     cout << endl << "Hitted a wall in right!" << endl;
                }
            }
        }
    }

    int x_counter = 1;
    int xx = 0,yy = -1,dd = 1;
    cout << endl << "*************************************************";
    cout << endl << "Actions:" << "  Left" << "  Right" << "  Up" << "  Down" <<endl << endl;
    for(int i = 0 ; i < 50 ; ++i){
            if(i % 2 != 0)
                dd = 1;
            else
                dd = 0;
            if(x_counter == 11){
                x_counter = 1;
                xx++;
            }
            if(i % 2 == 0){
                yy++;
            }
            if(yy == 5)
                yy = 0;

        cout << "State-" << i << "(" << xx << ", " << yy << ", " << dd << "):  ";
        x_counter++;
        for(int j = 0 ; j < 4 ; j++){
            cout << Q_table[i][j] << " ";
        }
        cout << endl;
    }
}
