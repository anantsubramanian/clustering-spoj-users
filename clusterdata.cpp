#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <tr1/unordered_map>

using namespace std;

double similarity(vector<string> &user1, vector<string> &user2)
{
	// total won't be 0, atleast not for the top 1000 users
	tr1::unordered_map<string, bool> present;
	int total = 0, common = 0;
	for(int i = 0; i < user1.size(); i++)
	{
		total++;
		present[user1[i]] = true;
	}
	for(int i = 0; i < user2.size(); i++)
	{
		if(present.find(user2[i]) != present.end())
			common++;
		else
			total++;
	}
	return ((double) common) / total;
}

typedef pair<int, int> ii;
typedef pair<ii, double> iid;

tr1::unordered_map<int, string> userid;
vector< vector<string> > problems;
vector<iid> links;
vector<iid> finalgraph;
vector<bool> userincluster;

vector<int> heads;

bool comp(iid a, iid b)
{
	return a.second > b.second;		
}

int compresspath(int i)
{
	if (heads[i] == i)
		return i;
	else return heads[i] = compresspath(heads[i]);
}

int main()
{
	ios_base::sync_with_stdio(false);
	int curuser = 0;
	int numclusters = 0;
	char verbose;
	bool shouldprint = false;
	cout<<"Enter number of clusters: ";
	cin>>numclusters;
	cout<<"Verbose clustering? (y = yes, n = no): ";
	cin>>verbose;
	if (verbose == 'y' || verbose == 'Y')
		shouldprint = true;
	ifstream fin("parsed_data.dat");
	ofstream fout("clustered_data.dat");
	while(!fin.eof())
	{
		string username;
		int problemcount;
		fin>>username>>problemcount;
		if(fin.eof())
			break;
		userid[curuser] = username;
		heads.push_back(curuser);
		userincluster.push_back(false);
		problems.push_back(vector<string>());
		for(int i = 0; i < problemcount; i++)
		{
			string problem;
			fin>>problem;
			problems[curuser].push_back(problem);
		}
		curuser++;
	}
	if(curuser < numclusters)
	{
		cerr<<"Error! Too many clusters mentioned. Please review data and try again.\n";
		return 1;
	}
	for(int i = 0; i < curuser; i++)
	{
		for(int j = i+1; j < curuser; j++)
		{
			double sim = similarity(problems[i], problems[j]);
			links.push_back(iid(ii(i, j), sim));
		}
		if (shouldprint)
			cout<<i+1<<". Done similarity computations for "<<userid[i]<<".\n";
	}
	sort(links.begin(), links.end(), comp);
	int edgecount = curuser-1;
	int numedges = 0;
	for(int i = 0; i < links.size(); i++)
	{
		iid temp = links[i];
		int u = temp.first.first;
		int v = temp.first.second;
		heads[u] = compresspath(heads[u]);
		heads[v] = compresspath(heads[v]);
		if(heads[u] == heads[v])
			continue;
		else
		{
			if (heads[heads[u]] < heads[heads[v]])
				heads[heads[v]] = heads[u];
			else
				heads[heads[u]] = heads[v];
			finalgraph.push_back(iid(ii(u, v), temp.second));
			edgecount--;
			numedges++;
		}
		if(edgecount <= 0)
			break;
	}
	numedges -= (numclusters-1);
	for(int i = 0; i < numedges; i++)
	{
		if (shouldprint)
			cout<<userid[finalgraph[i].first.first]<<" to "<<userid[finalgraph[i].first.second]<<" with similarity "<<finalgraph[i].second<<"\n";
		fout<<userid[finalgraph[i].first.first]<<" "<<userid[finalgraph[i].first.second]<<" "<<finalgraph[i].second<<"\n";
		userincluster[finalgraph[i].first.first] = true;
		userincluster[finalgraph[i].first.second] = true;
	}
	for(int i = 0; i < userincluster.size(); i++)
		if (!userincluster[i])
		{
			cout<<userid[i]<<"\n";
			fout<<userid[i]<<"\n";
		}
	fin.close();
	fout.close();
	return 0;
}
