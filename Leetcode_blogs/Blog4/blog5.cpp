class Solution {
private:
    struct node {
        int x, y;
        string type;
        node(int _x, int _y, string _type) : x(_x), y(_y), type(_type) {}
    };
    
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) 
    {
        vector<node> height;
        for (int i = 0; i < buildings.size(); i++) 
        {
            height.push_back(node(buildings[i][0], buildings[i][2], "LEFT"));
            height.push_back(node(buildings[i][1], buildings[i][2], "RIGHT"));
        }
        sort(height.begin(), height.end(),f);
        multiset<int> heap;
        heap.insert(0);
        vector<pair<int, int>> res;
        int pre = 0, cur = 0;
        for (int i = 0; i < height.size(); i++) 
        {
            if (height[i].type == "LEFT") 
            {
                heap.insert(height[i].y);
            } 
            else 
            {
                heap.erase(heap.find(height[i].y));
            }   
            cur = *heap.rbegin();
            if (cur != pre) 
            {
                res.push_back({height[i].x, cur});
                pre = cur;
            }
        }
        return res;
    }
    static bool f(const node &a, const node &b) 
    {
        if (a.x != b.x) 
            return a.x < b.x;
        else if (a.type == "LEFT" && b.type == "LEFT") 
            return a.y > b.y;
        else if (a.type == "RIGHT" && b.type == "RIGHT") 
            return a.y < b.y;
        else 
            return a.type == "LEFT";
    }
};

class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) 
    {
        vector<pair<int, int>> height;
        for (int i = 0; i < buildings.size(); i++) 
        {
            height.push_back({buildings[i][0], -buildings[i][2]});
            height.push_back({buildings[i][1], buildings[i][2]});
        }
        sort(height.begin(), height.end());
        multiset<int> heap;
        heap.insert(0);
        vector<pair<int, int>> res;
        int pre = 0, cur = 0;
        for (int i = 0; i < height.size(); i++) 
        {
            if (height[i].second < 0) 
            {
                heap.insert(-height[i].second);
            } 
            else 
            {
                heap.erase(heap.find(height[i].second));
            }   
            cur = *heap.rbegin();
            if (cur != pre) 
            {
                res.push_back({height[i].first, cur});
                pre = cur;
            }
        }
        return res;
    }
};