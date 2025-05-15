#include <bits/stdc++.h>
using namespace std;

class Graph{
    private:
        //mp is adjacency list
        map<int,set<int>> mp;
        vector<int> hype;       ///stores hype value
        vector<int> indeg;
        int n;                  //int number of g->n
    public:
        //constructor with parameters
        Graph(int x){
            //we will x number of nodes
            n=x;
            hype.resize(n+1);
            indeg.resize(n+1,0);
            indeg[0]=-1;
            hype[0]=-1;
        }
        int gethype(int u){
            if (u >= 1 && u <= n) return hype[u];
            return 0;
        }  
        void addhype(){
            for(int i=1;i<=n;i++){
                cin>>hype[i];
            }
        }
        void addedge(int u,int v){
            //directed graph so only one edge
            mp[u].insert(v);
            indeg[v]++;
        }
        vector<int> DFS(){
            vector<int> color(n+1,0);
            vector<int> ans;
            for(int i=1;i<=n;i++){
                if(color[i]==0){
                    DFSvisit(i,color,ans);
                }
            }
            return ans;
        }
        void DFSvisit(int u,vector<int>& color,vector<int> & ans){
            color[u]=1;
            for(auto i:mp[u]){
                if(color[i]==0){
                    DFSvisit(i,color,ans);
                }
            }
            ans.push_back(u);
            color[u]=2;
        }
    friend Graph* makeg_c(Graph * g);
    friend class isCycle;
    friend class indepComponent;
    friend class validOrder;
    friend class maxhype;
};

class GraphAlgorithm{
    public:
        virtual void Query()=0;
};

//Child classes
class isCycle: public GraphAlgorithm{
    Graph * g;
    public:
        //constructor
        isCycle(Graph * G){g=G;}
        void Query(){
            if(iscyclic()){cout<<"YES\n";return;}
            else{cout<<"NO\n";return;}
        }
        bool iscyclic(){
            vector<bool> visited(g->n+1,false);
            vector<bool> stack(g->n+1,false);
            for(int i=1;i<=g->n;i++){   
                if(visited[i]==false){
                    if(helper(i,visited,stack)){return true;} 
                }
            } 
            return false;
        }
        bool helper(int u,vector<bool>&visited,vector<bool>&stack){
            if(stack[u]){return true;}
            visited[u]=true;stack[u]=true;
            //now we will check for adjacents of this node
            for(auto i:g->mp[u]){
                if(visited[i]==false){
                    if(helper(i,visited,stack)){return true;}
                }
                else if(stack[i]){
                    return true;
                }
            }
            stack[u]=false;
            return false;
        }
};

Graph* makeg_c(Graph*g){
    Graph* g_c=new Graph(g->n);
    for(int i=1;i<=g->n;i++){
        for(auto j : g->mp[i]){
            //(i,j) -> (j,i)
            g_c->mp[j].insert(i);
        }
    }
    return g_c;
}

//Query 2
class indepComponent: public GraphAlgorithm{
    Graph * g;
    Graph * g_c;
    public:
        //constructor
        indepComponent(Graph * G){g=G;}
        void Query(){
            findscc();
        }
        void findscc(){
            //will find scc
            //we will do dfs and get the ans array
            vector<int> arr=g->DFS();
            //we have ans we need to find for graph g'
            g_c=makeg_c(g);
            DFS(arr);
            return;
        }
        void DFS(vector<int> & arr){
            vector<int> color(g_c->n+1,0);
            int components=0;
            int max_count=0;
            for(int i=arr.size()-1;i>=0;i--){
                int c=0;
                if(color[arr[i]]==0){
                    DFSvisit(arr[i],color,c);
                    components++;
                    max_count = max(max_count, c);
                }
            }
            cout<<components<<" "<<max_count<<endl;
        }
        void DFSvisit(int u,vector<int>& color,int & c){
            color[u]=1;
            for(auto i:g_c->mp[u]){
                if(color[i]==0){
                    DFSvisit(i,color,c);
                }
            }
            color[u]=2;
            c++;return;
        }
};

class validOrder: public GraphAlgorithm{
    Graph * g;
    public:
        //constructor
        validOrder(Graph *G){
            g=G;
        }
        void Query(){
            vector<int> in_deg = g->indeg;
            priority_queue<int, vector<int>, greater<int>> pq; // Min-heap for lexicographical order
            for(int i=1;i<=g->n;i++) {
                if(in_deg[i]==0) {
                    pq.push(i);
                }
            }
            vector<int> order;
            while (!pq.empty()) {
                int u = pq.top();
                pq.pop();
                order.push_back(u);
                for(auto v:g->mp[u]) {
                    if(--in_deg[v]==0) {
                        pq.push(v);
                    }
                }
            }
            if(order.size()==g->n){
                for(int node:order) {
                    cout<<node<<" ";
                }
            }
            else{cout<<"NO";}
            cout<<endl;
        }
};

class maxhype: public GraphAlgorithm{
    Graph * g;
    Graph* g_c;
    public:
        //constructor
        maxhype(Graph * G){
            g=G;
        }  
        void Query(){
           gethype();
        }
        void gethype(){
            vector<int> arr=g->DFS();
            g_c=makeg_c(g);
            vector<int> color(g->n+1,0);
            vector<int> comp(g->n+1,-1);
            int comp_id=0;
            vector<int> cphype;
            for(int i=arr.size()-1;i>=0;i--){
                int u=arr[i];
                if(color[u]==0){
                    int total_hype=0;
                    DFSvisit(u,color,comp,comp_id,total_hype);
                    cphype.push_back(total_hype);
                    comp_id++;
                }
            }
            vector<set<int>> makeone(comp_id);
            vector<int> indeg(comp_id,0);
            for(int i=1;i<=g->n;i++){
                for(int v:g->mp[i]){
                    int scc_u=comp[i];
                    int scc_v=comp[v];
                    if(scc_u!=scc_v && makeone[scc_u].insert(scc_v).second){
                        indeg[scc_v]++;
                    }
                }
            }
            queue<int> q;
            vector<int> max_hype(comp_id,0);
            for(int i=0;i<comp_id;i++){
                max_hype[i]=cphype[i];
                if(indeg[i]==0)q.push(i);
            }
            int max_total_hype=0;
            while(!q.empty()){
                int u=q.front();
                q.pop();
                max_total_hype=max(max_total_hype, max_hype[u]);
                for (int v:makeone[u]) {
                    max_hype[v]=max(max_hype[v],max_hype[u]+cphype[v]);
                    if(--indeg[v]==0) q.push(v);
                }
            }
            cout<<max_total_hype<<endl;
        }
        void DFSvisit(int u, vector<int>& color, vector<int>& component, int comp_id, int& total_hype) {
            color[u] = 1;
            component[u] = comp_id;
            total_hype += g->gethype(u);
            
            for (int v : g_c->mp[u]) {
                if (color[v] == 0) {
                    DFSvisit(v, color, component, comp_id, total_hype);
                }
            }
        }
};

int main(){
    int n,m;
    cin>>n>>m;
    Graph g(n);
    g.addhype();
    for(int i=0;i<m;i++){
        int u,v;cin>>u>>v;
        g.addedge(u,v);
    }
    int q;
    cin>>q;
    int x;
    while(q--){
        cin>>x;
        if(x==1){
            GraphAlgorithm* G1 = new isCycle(&g);
            G1->Query();
        }
        else if(x==2){
            GraphAlgorithm* G2 = new indepComponent(&g);
            G2->Query();
        }
        else if(x==3){
            GraphAlgorithm* G3 = new validOrder(&g);
            G3->Query();
        }
        else if(x==4){
            GraphAlgorithm* G4 = new maxhype(&g);
            G4->Query();
        }
    }
}
