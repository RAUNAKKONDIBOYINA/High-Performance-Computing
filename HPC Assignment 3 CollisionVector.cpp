// Compile in terminal using.       cd Desktop/Programs && g++ -std=c++11 "HPC3 CollisionVector.cpp" -o a
// Run with argument using          ./a ReservatioinTable.txt



#include<bits/stdc++.h>
using namespace std;
const int mx = 1e5, mod = 1e9 + 7;
#define ll long long
#define ld long double


unordered_map<int,set<vector<int>>> simpleCycles;

void dfs(unordered_map<int,vector<pair<int,int>>> mp,unordered_map<int,int> visited,vector<int> a,int node,int j)
{
	if(visited[node]!=0)
	{
		simpleCycles[node].insert(vector<int>(a.begin()+visited[node]-1, a.end()));
		return;
	}
	visited[node]=j;
	for (int i = 0; i < mp[node].size(); ++i)
	{
		a.push_back(mp[node][i].second);
		dfs(mp,visited,a,mp[node][i].first,j+1);
		a.pop_back();
	}
}


int main(int argc, char* argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
// #ifndef ONLINE_JUDGE
	freopen(argv[1], "r", stdin);
	// freopen(argv[2], "w", stdout);
// #endif
	// string filename = argv[1];
 //            ifstream in(filename);
 //            in.open(filename);
	string s;
	set<int> st;
	int optimalMAL=0,Xs=0;
	while(!getline(cin,s).eof())
	{
		// cout<<s<<endl;
		Xs=0;
		for (int i = 0; i < s.length(); ++i)
		{
			if (s[i]=='X')
			{
				Xs++;
				for (int j = i+1; j < s.length(); ++j)
				{
					
					if (s[j]=='X')
					{
						st.insert((j-i)/2);
					}
				}
			}
		}
		if(optimalMAL<Xs)
		{
			optimalMAL=Xs;
		}

	}
	// std::vector<int> colv(int(*st.rbegin())+1,0);
	int colv=0;
	
	for(auto it:st)
	{
		// cout<<it<<endl;
		colv=colv|(1<<(it-1));
	}
	vector<int> Forbidden;
	vector<int> Permissible;
	int temp=colv,n=1;
	string colvs;
	while(temp!=0)
	{
		if ((temp&1)==1)
		{
			Forbidden.push_back(n);
		}
		else
		{
			Permissible.push_back(n);
		}
		n++;
		colvs+=(temp&1)+'0';
		temp=temp>>1;
	}
	reverse(colvs.begin(),colvs.end());
	cout<<"Collision Vector : "<<colvs<<endl;
	
	cout<<"Forbidden \t: ";
	
	for(auto it:Forbidden)
	{
		cout<<it<<" ";
		
	}
	cout<<"\nPermissible \t: ";
	
	for(auto it:Permissible)
	{
		cout<<it<<" ";
		
	}
	cout<<""<<endl;
	
	unordered_map<int,vector<pair<int,int>>> mp;
	int nd;
	temp=0;
	queue<int> q;
	unordered_map<int,int> visited;
	q.push(colv);
	visited[colv]=1;
	while(!q.empty())
	{
		nd=q.front();
		int wt=0;
		while(1)
		{
			temp=nd>>wt;
			if((temp&1)==0)
			{
				int temp2= (temp>>1)|colv;
				mp[nd].push_back(make_pair(temp2,++wt));
				if (visited[temp2]==0)
				{
					q.push(temp2);
					visited[temp2]=1;
				}
				if (temp==0)
				{
					break;
				}
			}
			else
			{
				wt++;
			}
		}
		q.pop();
	}
	// for(auto it:mp)
	// {
	// 	cout<<(it.first)<<" "<<endl;
	// 	for(auto it2:it.second)
	// 	{
	// 		cout<<it2.first<<":"<<it2.second<<" ";
			
	// 	}
	// 	cout<<""<<endl;
		
	// }
	// cout<<""<<endl;
	
	visited.clear();
	std::vector<int> a;
	dfs(mp,visited,a,colv,1);
	unordered_map<int,vector<int>> greedyCycles;
	std::vector<int> min;
	int sum=0;
	float minAvLt=INT_MAX,MAL=INT_MAX;
	cout<<"SimpleCycle \t: AverageLatency"<<endl;
	for(auto it:simpleCycles)
	{
		
		minAvLt=INT_MAX;
		for(auto it2:it.second)
		{
			sum=0;
			for(auto it3:it2)
			{
				cout<<it3<<" ";

				sum+=it3;
			}
			// if (it2.size()>2)
			// {
			// 	cout<<"\t";
				
			// }
			float averageLatency=float(sum/float(it2.size()));
			for (int i = 0; i < 2; ++i)
			{
				cout<<"\t";
				
			}
			cout<<": "<<averageLatency<<endl;
			if(averageLatency<minAvLt)
			{
				min=it2;
				minAvLt=averageLatency;
			}
			if (averageLatency<MAL)
			{
				MAL=averageLatency;
			}
		}
		greedyCycles[it.first]=min;
		// cout<<"Greedy : \t\t";
		
		// for(auto it2:min)
		// {
		// 	cout<<it2<<" ";
			
		// }
		// cout<<""<<endl;
		
	}
	cout<<""<<endl;
	
	cout<<"Greedy Cycles"<<endl;
	
	for(auto it:greedyCycles)
	{
		for(auto it2:it.second)
		{
			cout<<it2<<" ";
			
		}
		cout<<""<<endl;
		
	}
	
	cout<<"\nMAL : "<<MAL<<endl;
	cout<<"OptimalMAL : "<<optimalMAL<<endl;
	
	
	// cout<<colv<<endl;
	
	return 0;
}
