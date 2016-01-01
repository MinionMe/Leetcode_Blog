class Solution {
public:
    int maxPoints(vector<Point>& points) {
        map<double,int> slope;           //建立斜率与出现次数的映射
        if(points.size() <= 2)          //点的个数小于3时，直接返回点的个数
            return points.size();
 		int n = points.size(),ans = 0;     //ans为最终结果
	    for(int i = 0; i < n - 1; i++)      
	    {
	    	int maxNum = 0;                //记录当前节点对应的斜率出现最多的次数
	    	int same_x = 1;                //记录斜率不存在，即横坐标相等的情况
	    	int samePoint = 0;             //记录重合的点
	        slope.clear();                
	        for(int j = i + 1; j < n; j++)   
	        {
	        	
	      		if (i == j)
	      			continue;	
	      		if (points[i].x == points[j].x && points[i].y == points[j].y) 
	      		{
                    samePoint++;
                    continue;
                }
	      		if (points[i].x == points[j].x)  //斜率不存在   
	      		{
	      			same_x++;
	  				continue;
	      		}
	      		double k = (double)(points[i].y-points[j].y)/(points[i].x-points[j].x);
	      		if (slope.find(k) != slope.end())   //更新当前斜率出现的次数
	      			slope[k]++;
	      		else
	      			slope[k] = 2;
	        }
	        for (map<double,int>::iterator it = slope.begin(); it != slope.end(); ++it)   //找出最大次数的斜率
	        	same_x = max(same_x,it->second);
	        maxNum = same_x + samePoint;
	        ans = max(ans,maxNum);                  //与之前的最大值比较
		} 	    
	    return ans;
    }
};