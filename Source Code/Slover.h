#ifndef SLOVER_H
#define SLOVER_H
# include <QString>
# include <QDebug>


class State_Set {
private:
    int fa[105], n;
public:
    void Init(int n) {
        this -> n = n;
        for (int i = 1; i <= n; ++i)
            fa[i] = i;
    }

    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    void Union(int State1, int State2) {
        int SetofState1 = find(State1);
        int SetofState2 = find(State2);
        if (SetofState1 == SetofState2)
            return ;
        fa[SetofState2] = SetofState1;
    }

    bool Query(int State1, int State2) {
        return find(State1) == find(State2) ;
    }
} ;

class State_Map {
private:
    int State_trans[20][20], State_Num, Input_Num;
    int Ans[20][20];
    State_Set State_Reduce_Set;
    bool vis[20][20];
public:
    void Init(int Snum, int input_num, int NS_array[][20], int output_array[][20]) {
        memset(vis, 0, sizeof vis);

        State_Reduce_Set.Init(Snum);
        State_Num = Snum;
        Input_Num = input_num;

        int NS, z;
        for (int PS = 1; PS <= State_Num; ++PS) {
            for (int input = 0; input < Input_Num; ++input) {
                NS = NS_array[PS - 1][input];
                z = output_array[PS - 1][input];
                State_trans[PS][input] = NS << 1 | z;
            }
        }
    }

    bool Output(int State, int input) {
        return State_trans[State][input] & 1;
    }

    int Next_State(int State, int input) {
        return State_trans[State][input] >> 1;
    }

    bool Cmp(int State1, int State2, bool input) {
        return (Next_State(State1, input) == Next_State(State2, input)) || (Next_State(State1, input) == State2 && Next_State(State2, input) == State1);
    }

    bool Judge(int State1, int State2) {
        if (State1 > State2) std::swap(State1, State2);

        if (State_Reduce_Set.Query(State1, State2)) return true;

        if (vis[State1][State2])
            return true;

        for (int i = 0; i < Input_Num; ++i)
            if (Output(State1, i) != Output(State2, i))
                return false;

        vis[State1][State2] = true;

        for (int input = 0; input < Input_Num; ++input) {
            if (Cmp(State1, State2, input))
                continue;
            if (Judge(Next_State(State1, input), Next_State(State2, input)))
                continue;
            vis[State1][State2] = false;
            return false;
        }

        return State_Reduce_Set.Union(State1, State2), true;

    }

    void Solver(int &cnt, int *id, int PS_Array[][20], int output_Array[][20]) {
        for (int i = 1; i <= State_Num; ++i)
            for (int j = i + 1; j <= State_Num; ++j)
                Judge(i, j);

//        for (int i = 1; i <= State_Num; ++i)
//            for (int j = i + 1; j <= State_Num; ++j)
//                if (State_Reduce_Set.Query(i, j))
//                    printf("%d ~= %d\n", i, j);

        cnt = 0;
        for (int i = 1; i <= State_Num; ++i)
            if (State_Reduce_Set.find(i) == i) {
                id[cnt] = i - 1;
                // printf("S%d ", i);
                //qDebug() << i;
                for (int input = 0; input < Input_Num; ++input) {
                    Ans[cnt][input] = State_Reduce_Set.find(State_trans[i][input] >> 1) << 1 | Output(i, input);
                    PS_Array[cnt][input] = Ans[cnt][input] >> 1;
                    output_Array[cnt][input] = Ans[cnt][input] & 1;
                    // printf("%d/%d%c", Ans[cnt][input] >> 1, Ans[cnt][input] & 1, " \n"[input == Input_Num - 1]);

                }
                cnt ++ ;
            }
//        for (int i = 1; i <= cnt; ++i) {
//            printf("S%d ", id[i]);
//            for (int input = 0; input < Input_Num; ++input) {
//                printf("%d/%d%c", PS_Array[i][input], output_Array[i][input], " \n"[input == Input_Num - 1]);
//            }
//        }
    }

} ;

#endif // SLOVER_H
