#include <vector>
#include <iostream>
#include <unordered_map>
#include <climits>
#include <algorithm>

using namespace std;

class BellmanFord {
public :

    // complexity O(V*E)
    vector<string> shortestPath(string start, string target, vector<string> vertices,
				vector<tuple<string, string, int>> edges){
	unordered_map<string, int> distances;
	unordered_map<string, string> comeFrom;

	for(auto s : vertices)
	    distances[s] = s == start ? 0 : INT_MAX;

	string from, to;
	int cost;
	for(int i = 0; i < vertices.size() - 1; i++){
	    for(auto t : edges){
		tie(from, to, cost) = t;
		if(distances[from] < distances[to] - cost){
		    distances[to] = distances[from] + cost;
		    comeFrom[to] = from;
		}
		swap(from, to); // assume undirected graph
		if(distances[from] < distances[to] - cost){
		    distances[to] = distances[from] + cost;
		    comeFrom[to] = from;
		}
	    }
	}
	
	for(auto t : edges){
	    tie(from, to, cost) = t;
	    if(distances[from] < distances[to] - cost)
		return {};
	}
	
	return retrievePath(comeFrom, start, target);
    }
    
    vector<string> retrievePath(unordered_map<string, string> &comeFrom, string start, string target){
	vector<string> path;
	while(comeFrom.count(target)){
	    path.push_back(target);
	    target = comeFrom[target];
	}
	path.push_back(start);
	reverse(path.begin(), path.end());
	return path;
    }

};

int main(){
    vector<string> vertices = {"0", "1", "2", "3", "4", "5", "6", "7", "8"};
    vector<tuple<string, string, int>> edges = {
	make_tuple("0", "1", 4),
	make_tuple("0", "7", 8),
	make_tuple("1", "7", 11),
	make_tuple("1", "2", 8),
	make_tuple("7", "6", 1),
	make_tuple("7", "8", 7),
	make_tuple("2", "8", 2),
	make_tuple("8", "6", 6),
	make_tuple("2", "3", 7),
	make_tuple("2", "5", 4),
	make_tuple("6", "5", 2),
	make_tuple("3", "5", 14),
	make_tuple("3", "4", 9),
	make_tuple("5", "4", 10)
    };
    BellmanFord bf;
    auto path = bf.shortestPath("2", "7", vertices, edges);
    for(auto &s : path)
	cout << s << ' ';
    cout << endl;

    return 0;
}
