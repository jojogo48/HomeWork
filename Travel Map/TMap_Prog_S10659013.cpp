#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>
#include <memory.h>
#include <cmath>


#define MAX 9999.9
#define MIN -1
#define LEFT_TO_RIGHT 1
#define RIGHT_TO_LEFT -1
#define PI                      3.1415926
#define EARTH_RADIUS            6378.137
#define MILLION                 1e6
using namespace std;


typedef struct{
    int     poi_index;
    int     closest_line_index;
    double  closest_line_distan;
    double  line_poi_inner_prod;
}not_in_convexhull_poi;



class Point
{
    public:
        Point();
        explicit Point(string name,double x,double y,int index);
        double get_x();
        double get_y();
        string get_name();
        int get_index();
        void set_x(double x);
        void set_y(double y);
        void set_name(string name);
        void set_index(int index);
        friend double calc_distance(Point& ,Point&);
    private:
        int index{-1};
        string name;
        double x{0.0};
        double y{0.0};
};

class Line
{
    private:
        Point* a;
        Point* b;
        double slope;
        double bias;
        double delta_x;
        double delta_y;
    public:
        explicit Line (Point& ,Point&);
        Line(const Point&);
        ~Line();
        Point* get_pointa();
        Point* get_pointb();
        double get_delta_x();
        double get_delta_y();
        double inner_product(Point&);
        int compare(Point&);
        double calc_distance(Point &);
};

class Graph
{
    public:
        Graph(int);
        void connect(int ,int );
        void remove(int, int);
        vector<int> traversal(int);
        bool** get_graph();
        void print();
    private:
        bool ** graph;
        int size=0;
};








//------------------------------function--------------------------------



template<class t>
void       swap(t* list,int i,int j);
template<class t>
void       selection_sort(vector<t>& list,bool (*is_in_order)(t a,t b));

void       printl(int* list,int size);
void       printv(vector<int> list,int end);
int        find_biggest(int* list,int *direction,int size,int start);
void       reverse(int* list,int* direction,int size,int k,int start);
int*       find_shortest_path(int *list, int size,double& min);
double     triangle_area(double dx_1,double dy_1,double dx_2,double dy_2);
Graph*     find_convex_hull(int& trav_index);
bool       is_poi_in_order(not_in_convexhull_poi,not_in_convexhull_poi);
double     calc_rad(double d);
double*    WGS2flat(double lon, double lat);
vector<vector<int>> find_clique(double r,int k);
void comb(vector<int> all,int* subset,int subset_size,int start,int end,int n,Graph* g,vector<vector<int>>& total_g,bool* is_connect_poi);

//---------------------------------Global Variable-------------------------------------
double**           g_graph_distance;
Point**            g_poi;
Graph*             g_graph;
int                num_of_poi;




int main()
{

//---------------------------------General Variable--------------------------------------
    int    traversal_index=0;

//----------------------------------Read File--------------------------------------------

    {
        string file_name;

        cout<<"Enter file name........";
        cin>>file_name;


        string        line;
        fstream       file;
        stringstream  ss;

        file.open(file_name, ios::in);

        getline(file, line);

        ss<<line;
        ss>>num_of_poi;
        cout<<num_of_poi<<endl;


        //------------------------------- Global Variable Declear--------------------------
        g_poi             = new Point*[num_of_poi];
        g_graph_distance  = new double*[num_of_poi];

        for(int i = 0;i < num_of_poi; i++)
        {
            g_graph_distance[i] = new double[num_of_poi]();
            memset(g_graph_distance[i], 0, num_of_poi * sizeof(double));
        }

        //-------------------------------End Global Variable Declear------------------------

        const int   arg_numb = 3;
        string*     buffer   = new string[arg_numb];

        for(int i = 0;i < num_of_poi; i++)
        {
            getline(file, line);

            ss.str("");
            ss.clear();

            ss<<line;

            for(int j = 0;j < arg_numb; j++)
            {
                getline(ss, buffer[j], ',');
            }

            double  lon  =    atof(buffer[1].c_str());
            double  lat  =    atof(buffer[2].c_str());
            double* cord =    WGS2flat(lon,lat);

            g_poi[i] = new Point(buffer[0],cord[0]/1000, cord[1]/1000, i);

            cout<<'('+to_string(i + 1)+')'<<"  "<<line<<endl;
        }

        delete[] buffer;
        file.close();
    }
//----------------------------------End Read File--------------------------------------------


//----------------------------------Problem 1--------------------------------------------
    {

        int    most_close_poi_index[2];
        double min_distance = MAX;
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        for(int i=0;i < num_of_poi-1; i++)
        {
            for(int j = i + 1; j < num_of_poi; j++)
            {
                g_graph_distance[i][j] = calc_distance(*g_poi[i], *g_poi[j]);
                g_graph_distance[j][i] = g_graph_distance[i][j];

                if(min_distance > g_graph_distance[i][j])
                {
                    min_distance            = g_graph_distance[i][j];
                    most_close_poi_index[0] = i;
                    most_close_poi_index[1] = j;
                }
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_used = MILLION*(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000.0;
        cout<<"-----------------------------------------"<<endl;

        cout<<g_poi[most_close_poi_index[0]]->get_name()<<" 1與"<<g_poi[most_close_poi_index[1]]->get_name()<<"距離最近 ";

        cout<<"距離為:"<<min_distance<<" km"<<endl<<endl;
        cout<<"執行時間: "<<time_used/1000.0<<" ms"<<endl;
        cout<<"-----------------------------------------"<<endl;


    }


//----------------------------------Problem 2--------------------------------------------

    {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        g_graph = find_convex_hull(traversal_index);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_used = MILLION*(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000.0;
    }

    {
        double         hull_area               = 0;
        double         farthest_distance       = MIN;
        vector<int>    result                  = g_graph->traversal(traversal_index);
        int            farthest_poi_index[2];
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        for(int i = 0; i < result.size()-1; i++)
        {
            for(int j = i + 1; j < result.size(); j++)
            {
                if(farthest_distance < g_graph_distance[result[i]][result[j]])
                {
                    farthest_distance     = g_graph_distance[result[i]][result[j]];
                    farthest_poi_index[0] = result[i];
                    farthest_poi_index[1] = result[j];
                }
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_used = MILLION*(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000.0;



        clock_gettime(CLOCK_MONOTONIC, &start);
        Line* t_l1 = new Line(*g_poi[result[0]], *g_poi[result[1]]);

        for(int i = 2;i < result.size() ; i++)
        {
            Line* t_l2   =    new Line(*g_poi[result[0]],*g_poi[result[i]]);
            hull_area   +=   triangle_area(t_l1->get_delta_x() ,
                                           t_l1->get_delta_y() ,
                                           t_l2->get_delta_x() ,
                                           t_l2->get_delta_y() );
            delete t_l1;
            t_l1 = t_l2;
        }
        delete t_l1;
        clock_gettime(CLOCK_MONOTONIC, &end);
        time_used = MILLION*(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000.0;


        cout<<"convex hull start ....\n";
        printv(result,traversal_index);
        cout<<g_poi[farthest_poi_index[0]]->get_name()<<" 與"<<g_poi[farthest_poi_index[1]]->get_name()<<" 距離最遠"<<endl;
        cout<<"最遠距離為: "<<farthest_distance<<" km"<<endl;
        cout<<"Convex hull 面積為: "<<hull_area<<" km^2"<<endl;

        cout<<"-----------------------------------------"<<endl;
    }

//----------------------------------Problem 3 (a)-------------------------------------------
    {
        int*   list         = new int[num_of_poi+1];
        int*   shorest_path;
        double min_distance;
        struct timespec start, end;

        cout<<"Enter start poi to find shortest path....";
        cin>>traversal_index;
        traversal_index -= 1;
        cout<<"-----------------------------------------"<<endl;
        cout<<"exhaustive search + brute-force algorithm"<<endl;


        int temp = 1;
        for(int i=0;i<num_of_poi;i++)
        {
                if(i != traversal_index)
                {
                    list[temp] = i;
                    temp++;
                }
        }

        list[0]                 = traversal_index;
        list[num_of_poi]        = traversal_index;

        clock_gettime(CLOCK_MONOTONIC, &start);
        shorest_path = find_shortest_path(list,num_of_poi+1,min_distance);
        clock_gettime(CLOCK_MONOTONIC, &end);

        double time_used = MILLION*(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000.0;

        printl(shorest_path,num_of_poi+1);
        cout<<"最短距離為: "<<min_distance<<" km"<<endl;
        cout<<"花費時間: "<<time_used/1000<<" ms"<<endl;
        delete shorest_path;

    }

//----------------------------------Problem 3 (b)-------------------------------------------

    {
        cout<<"-----------------------------------------"<<endl;
        cout<<"Convex-Hull-TSP Algorithm "<<endl;

        Graph*          p3_graph                       = new Graph(num_of_poi);
        int             start_traversal_poi;
        bool            is_in_convex[num_of_poi];
        vector<Line*>   convex_hull_line;
        struct timespec start, end;

        vector<not_in_convexhull_poi> line_poi_pair_vec;

         clock_gettime(CLOCK_MONOTONIC, &start);

        {
            p3_graph = find_convex_hull(start_traversal_poi);
        }

        {

            vector<int>  convex_hull            = p3_graph->traversal(start_traversal_poi);
            int          last_convex_hull_index = convex_hull[convex_hull.size()-1];

            memset(is_in_convex, true,sizeof(is_in_convex));


            for(int i = 0;i < convex_hull.size()-1; i++)
            {
                is_in_convex[convex_hull[i]] = false;
                Line* temp                   = new Line(*g_poi[convex_hull[i]],
                                                        *g_poi[convex_hull[i+1]]);
                convex_hull_line.push_back(temp);
            }

            is_in_convex[last_convex_hull_index] = false;
            convex_hull_line.push_back(new Line(*g_poi[last_convex_hull_index],*g_poi[convex_hull[0]]));

        }

        {
            for(int i = 0;i < num_of_poi; i++)
            {
                if(!is_in_convex[i])
                {

                    continue;
                }

                double  min_dis = MAX ;
                int     min_index  =-1;
                double  t_dis;

                for(int j = 0;j < convex_hull_line.size(); j++)
                {
                    t_dis=convex_hull_line[j]->calc_distance(*g_poi[i]);

                    if(t_dis<min_dis)
                    {
                        min_dis   =  t_dis;
                        min_index = j;
                    }
                }

                not_in_convexhull_poi n_c;

                n_c.poi_index           = i;
                n_c.closest_line_index  = min_index;
                n_c.closest_line_distan = t_dis;
                n_c.line_poi_inner_prod = abs(convex_hull_line[min_index]->inner_product(*g_poi[i]));

                    line_poi_pair_vec.push_back(n_c);
            }
            selection_sort(line_poi_pair_vec,is_poi_in_order);

        }


        {
            int line_poi_pair_vec_size = line_poi_pair_vec.size();
            int counter                = 0;


            while(counter<line_poi_pair_vec_size)
            {
                int line_index  = line_poi_pair_vec[counter].closest_line_index;
                int start_poi   = convex_hull_line[line_index]->get_pointb()->get_index();
                int connect_poi = line_poi_pair_vec[counter].poi_index;
                int end_poi     = convex_hull_line[line_index]->get_pointa()->get_index();

                p3_graph->remove(start_poi,end_poi);
                p3_graph->connect( start_poi,connect_poi);

                while(++counter < line_poi_pair_vec_size &&
                      line_poi_pair_vec[counter].closest_line_index == line_index)
                {
                    start_poi   = connect_poi;
                    connect_poi = line_poi_pair_vec[counter].poi_index;

                    p3_graph->connect(start_poi, connect_poi);
                }

                p3_graph->connect(connect_poi, end_poi);

            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end);


        vector<int> p3_hull = p3_graph->traversal(traversal_index);
        double dis          = 0;

        for(int i = 0;i < p3_hull.size() - 1; i++)
        {
            dis += g_graph_distance[p3_hull[i]][p3_hull[i+1]];
        }
        dis += g_graph_distance[p3_hull[p3_hull.size()-1]][p3_hull[0]];

        double time_used = MILLION*(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000.0;

        printv(p3_hull, p3_hull[0]);
        cout<<"距離為: "<<dis<<" km"<<endl;
        cout<<"所花費時間"<<time_used/1000.0<<" ms"<<endl;
    }


//----------------------------------Problem 4-----------------------------------------------

    {
        double r;
        int    k;


        cout<<"-----------------------------------------"<<endl;
        cout<<"Enter range R ....";
        cin>>r;
        cout<<"Enter group poi number K .....";
        cin>>k;
        struct timespec start, end;

        vector<vector<int>> clique;

        clock_gettime(CLOCK_MONOTONIC, &start);
        clique=find_clique(r,k);
        clock_gettime(CLOCK_MONOTONIC, &end);

        double time_used1 = MILLION*(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000.0;

        for(int i=0;i<clique.size();i++)
        {
            cout<<"Group "<<i+1<<" center: ("<<clique[i][0]+1<<") "<<g_poi[clique[i][0]]->get_name()<<endl;
            printv(clique[i],clique[i][0]);
        }

        int start_center;
        cout<<"Which group center you want to start travel.......";
        cin>>start_center;
        start_center--;

        clock_gettime(CLOCK_MONOTONIC, &start);
        int* center_path = new int[clique.size()+1];
        center_path[0] = start_center;
        center_path[clique.size()]=start_center;
        int pointer=1;
        for(int i=0;i<clique.size();i++)
        {
            if(clique[i][0]!=start_center)
            {
                center_path[pointer++] = clique[i][0];
            }
        }

        double min_dis;
        int * shorest_center_path;
        vector<int> shorest_path;
        shorest_center_path = find_shortest_path(center_path,clique.size()+1,min_dis);

        for(int i =0;i<clique.size();i++)
        {


            vector<int> temp;
            for(int j=0;j<clique.size();j++)
            {
                if(clique[j][0] == shorest_center_path[i])
                {
                    temp = clique[j];

                    break;
                }
            }

            int* inner_path = new int[temp.size()+1];

            inner_path[temp.size()] = shorest_center_path[i];
            for(int j=0;j<temp.size();j++)
            {
                inner_path[j] = temp[j];
            }

            double t_min;
            int* inner_shorest= find_shortest_path(inner_path,temp.size()+1,t_min);

            min_dis += t_min;
            for(int j=0;j<temp.size()+1;j++)
            {
                shorest_path.push_back(inner_shorest[j]);
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_used2 = MILLION*(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000.0;
       cout<<"花費時間: "<<(time_used1+time_used2)/1000.0<<endl;
        cout<<"路程為: "<<endl;
        printv(shorest_path,shorest_center_path[0]);
        cout<<"總路徑長為: "<<min_dis<<" km"<<endl;


    }


    system("pause");
    return 0;
}

//-------------------------------Point class implement-------------------------------------
Point::Point(){}
Point::Point(string name,double x, double y,int index):x(x),y(y),name(name),index(index){}
double Point::get_y(){return this->y;}
double Point::get_x(){return this->x;}
int Point::get_index(){return this->index;}
string Point::get_name(){return this->name;}
void Point::set_x(double x){this->x=x;}
void Point::set_y(double y){this->y=y;}
void Point::set_name(string name){this->name=name;}
void Point::set_index(int index){this->index=index;}
double calc_distance(Point& a,Point& b){
        double x_diff = (a.x - b.x)  ;
        double y_diff = (a.y - b.y) ;

        return sqrt(pow(x_diff,2)+pow(y_diff,2));
}


//-------------------------------Line class implement-------------------------------------
Line::Line(Point& a,Point& b)
{
    this->a=new Point(a.get_name(),a.get_x(),a.get_y(),a.get_index());
    this->b=new Point(b.get_name(),b.get_x(),b.get_y(),b.get_index());
    this->delta_y=( this->a->get_y() - this->b->get_y()) ;
    this->delta_x=( this->a->get_x() - this->b->get_x()) ;
    this->slope=this->delta_y/this->delta_x;
    this->bias = this->a->get_y() - (this->slope* this->a->get_x());
}
Line::~Line()
{
    delete this->a;
    delete this->b;
}
Point* Line::get_pointa(){return this->a;}
Point* Line::get_pointb(){return this->b;}
double Line::get_delta_x(){return this->delta_x;}
double Line::get_delta_y(){return this->delta_y;}
double Line::inner_product(Point& c)
{
    return this->delta_x * (c.get_x()-b->get_x()) + this->delta_y * (c.get_y()-b->get_y());
}
int Line::compare(Point& c){
    double temp = this->delta_x*(c.get_y()-b->get_y()) -
                  this->delta_y*(c.get_x()-b->get_x()) ;
    if((temp>0&&(this->delta_x>0) ||
       (temp<0&&(this->delta_x<0))))
        return -1;
    else if(temp==0)
        return 0;
    else
        return 1;
}
double Line::calc_distance(Point& c)
{
    return abs((this->slope*c.get_x())-c.get_y()+this->bias)/sqrt(pow(this->slope,2)+1);
}


//-------------------------------Graph class implement-------------------------------------

Graph::Graph(int n)
{
    this->size = n;
    this->graph = new bool*[n];
    for(int i=0;i<n;i++)
    {
        (this->graph)[i]=new bool[n]();
    }
}
bool** Graph::get_graph(){return this->graph;}
void Graph::connect(int a,int b)
{
    (this->graph)[a][b]=true;
    (this->graph)[b][a]=true;
}
void Graph::remove(int a,int b){
    (this->graph)[a][b]=false;
    (this->graph)[b][a]=false;
}
vector<int> Graph::traversal(int i)
{

    bool visited[this->size]={false};
    vector<int> stack,result;
    stack.push_back(i);
    visited[i]=true;
    while(!stack.empty())
    {
        i=stack.back();
        result.push_back(i);
        stack.pop_back();
        for(int j=0;j<this->size;j++){
            if(this->graph[i][j]&&!visited[j]){
                visited[j]=true;
                stack.push_back(j);
            }
        }
    }
    return result;
}
void Graph::print()
{
    for(int i=0;i<this->size;i++)
    {
        for(int j=0;j<this->size;j++)
        {
            cout<<this->graph[i][j]<<" ";
        }
        cout<<endl;
    }
}


//-------------------------------function implement-------------------------------------

void printv(vector<int> list, int end)
{
    for(int i = 0; i < list.size(); i++)
    {
        cout<<"("<<list[i]+1<<") "<<g_poi[list[i]]->get_name()<<endl;
        cout<<"    | "<<endl;
    }
    cout<<"("<<end+1<<") "<<g_poi[end]->get_name()<<endl;
}

void printl(int* list, int size)
{
    for(int i = 0; i < size - 1; i++)
    {
        cout<<"("<<list[i]+1<<") "<<g_poi[list[i]]->get_name()<<endl;
        cout<<"    | "<<endl;
    }
    cout<<"("<<list[size-1]+1<<") "<<g_poi[list[size-1]]->get_name()<<endl;
}

double calc_rad(double d)
{
    return d * PI / 180.0;
}



double* WGS2flat(double lon, double lat)
{
        double L = calc_rad(lon);
        double l = L - calc_rad(120);
        double B = calc_rad(lat);
        double cosb = cos(B);
        double sinb = sin(B);

        double a = EARTH_RADIUS * 1000;
        // 地球短半?
        double b = 6356752.3142451793;
        double t = tan(B);
        // double r = 3600 * 180 / Math.PI;
        double e2 = (pow(a, 2) - pow(b, 2)) / pow(a, 2);
        double e12 = (pow(a, 2) - pow(b, 2)) / pow(b, 2);
        double n2 = e12 * pow(cosb, 2);
        double N = a / sqrt(1 - e2 * pow(sinb, 2));

        double x = 6367449.1458 * B - 32009.8185 * cosb * sinb - 133.9975
                * cosb * pow(sinb, 3) - 0.6975 * cosb * pow(sinb, 5);
        double X = x + N / 2 * t * pow(cosb, 2) * pow(l, 2) + N / 24
                * t * pow(cosb, 4)
                * (5 - pow(t, 2) + 9 * n2 + 4 * pow(n2, 2))
                * pow(l, 4);
        double Y = N * cosb * l + N / 6 * pow(cosb, 3)
                * (1 - pow(t, 2) + n2) * pow(l, 3);

        double* coord =new double[2] {X, Y};
        coord[0] = X;
        coord[1] = Y;

        return coord;
}

double triangle_area(double dx_1, double dy_1, double dx_2, double dy_2)
{
    return (1.0/2) * (abs((dx_1 * dy_2) - (dy_1 * dx_2)));
}

template<class t>
void swap(t* list, int i, int j)
{
    t temp  = list[i];
    list[i] = list[j];
    list[j] = temp;
}
int find_biggest(int* list, int* direction, int size, int start)
{
    int k   = -1;
    int max = -1;

    for(int i = start;i < start + size; i++)
    {
        int j = i + direction[i];

        if(j < start || j >= start + size)
        {
            continue;
        }
        if(list[i] > max && list[i] > list[j])
        {
            k   = i;
            max = list[i];
        }
    }
    return k;
}

void reverse(int* list, int* dirction, int size, int k,int start)
{
    for(int i = start; i < start + size; i++)
    {
        if(list[i] > list[k])
        {
            dirction[i] *= -1;
        }
    }
}

int* find_shortest_path(int *list, int size, double& min)
{
    int     dirction[size];
    int*    min_list;
    int     start                  = 1;
    double  current_total_distance = 0;

    min_list = new int[size];

    for(int i = 0; i < size; i++)
    {
        dirction[i] = RIGHT_TO_LEFT;
        min_list[i] = list[i];
    }
    dirction[0]      = 0;
    dirction[size-1] = 0;
    min = 0;

    for(int i = 0;i < size - 1; i++)
    {
        min += g_graph_distance[list[i]][list[i+1]];
    }

    current_total_distance = min;
    for(int k = find_biggest(list, dirction, size-2,start);
            k != -1;
            k = find_biggest(list, dirction, size-2, start))
    {

        int next_move                 = k + dirction[k];
        int k_rever_direction_index   = k - dirction[k];
        int next_move_direction_index = next_move + dirction[k];

        current_total_distance -= g_graph_distance[list[k]][list[k_rever_direction_index]];
        current_total_distance -= g_graph_distance[list[next_move]][list[next_move_direction_index]];

        swap(list, next_move, k);
        swap(dirction, next_move, k);
        reverse(list,dirction,size-2,next_move,start);

        current_total_distance += g_graph_distance[list[k]][list[k_rever_direction_index]];
        current_total_distance += g_graph_distance[list[next_move]][list[next_move_direction_index]];

        if(min > current_total_distance)
        {
            min = current_total_distance;
            for(int i = 0;i < size; i++)
            {
                min_list[i] = list[i];
            }
        }
    }
    return min_list;

}

template<class t>
void selection_sort(vector<t>& list,bool (*is_in_order)(t a,t b))
{
    for(int i = 0; i < (signed)list.size()-1; i++)
    {

        int min_index = i;
        for(int j = i + 1; j<list.size(); j++)
        {
            if(!is_in_order(list[min_index],list[j]))
            {
                min_index = j;
            }
        }
        if(min_index != i)
        {
            swap(list[min_index],list[i]);
        }
    }
}

bool is_poi_in_order(not_in_convexhull_poi a,not_in_convexhull_poi b)
{

    if(a.closest_line_index < b.closest_line_index)
    {
        return true;
    }

    if(a.closest_line_index == b.closest_line_index &&
       a.line_poi_inner_prod < b.line_poi_inner_prod)
    {
        return true;
    }

    if(a.closest_line_index  == b.closest_line_index &&
       a.line_poi_inner_prod == b.line_poi_inner_prod &&
       a.closest_line_distan < b.closest_line_distan)
    {
        return true;
    }

    return false;
}

vector<vector<int>> find_clique(double r,int k)
{
    Graph* connect_graph = new Graph(num_of_poi);
    bool* is_connect_poi = new bool[num_of_poi];
    memset(is_connect_poi,false,num_of_poi*sizeof(bool));


    for(int i=0;i<num_of_poi-1;i++)
    {
        for(int j=i+1;j<num_of_poi;j++)
        {
            if(g_graph_distance[i][j]<=r)
            {
                is_connect_poi[i]=true;
                is_connect_poi[j]=true;
                connect_graph->connect(i,j);
            }
        }

    }


    vector<int> connect_poi;
    for(int i=0;i<num_of_poi;i++)
    {
        if(is_connect_poi[i])
        {
            connect_poi.push_back(i);
        }
    }
    vector<vector<int>> total_group;

    int  connect_size= connect_poi.size();

    while(connect_size>=k)
    {

        int* subset = new int[connect_size];
        comb(connect_poi,subset,connect_size,0,connect_poi.size(),connect_size,connect_graph,total_group,is_connect_poi);
            //int* trav_list = connect_graph->traversal(trav_index);
        connect_poi.clear();

        for(int i=0;i<num_of_poi;i++)
        {
            if(is_connect_poi[i])
            {
                connect_poi.push_back(i);
            }
        }

        if(connect_size>connect_poi.size())
        {
            connect_size = connect_poi.size();
        }else
        {
            connect_size--;
        }


    }
    return total_group;
}

void comb(vector<int> all,int* subset,int subset_size,int start,int end,int n,Graph* g,vector<vector<int>>& total_g,bool* is_connect_poi)
{

   if(n==1)
   {

       for(int i=start;i<end;i++)
       {
           bool push = true;
           subset[subset_size-1] = all[i];

           for(int j=0;j<subset_size-1&&push;j++)
           {
               for(int k=j+1;k<subset_size&&push;k++)
               {
                   if((!(g->get_graph()[subset[j]][subset[k]]))
                      || (!is_connect_poi[subset[j]]) || (!is_connect_poi[subset[k]]))
                   {
                       push = false;
                   }
               }
           }

           if(push)
           {
            vector<int> copy_subset;
            for(int j=0;j<subset_size;j++)
            {
                is_connect_poi[subset[j]] = false;
                copy_subset.push_back(subset[j]);
            }
            total_g.push_back(copy_subset);
           }
       }
   }else
   {
        for(int i=start;i<end;i++)
        {
            subset[subset_size-n] = all[i];
            comb(all,subset,subset_size,i+1,end,n-1,g,total_g,is_connect_poi);
        }
   }
}

Graph* find_convex_hull(int& trav_index)
{
        Graph*  f_graph = new Graph(num_of_poi);

        for(int i = 0;i < num_of_poi - 1; i++)
        {
            for(int j = i + 1;j < num_of_poi; j++)
            {
                int    check_in_same_side = 0;
                int    last               = 0;
                Line*  templ              = new Line(*g_poi[i], *g_poi[j]);


                for(int k = 0; k < num_of_poi; k++)
                {
                    if(i == k || j == k)
                    {
                        continue;
                    }
                    check_in_same_side += templ->compare(*g_poi[k]);

                    if(last > abs(check_in_same_side))
                    {
                        break;
                    }
                    last = check_in_same_side;
                }

                if(abs(check_in_same_side) == num_of_poi-2)
                {
                    trav_index = i;
                    f_graph->connect(i,j);
                }else
                {
                delete templ;
                }
            }
        }

        return f_graph;

}

