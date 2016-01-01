class Solution {
public:
    int maxPoints(vector<Point>& points) {
        map<double,int> slope;           //����б������ִ�����ӳ��
        if(points.size() <= 2)          //��ĸ���С��3ʱ��ֱ�ӷ��ص�ĸ���
            return points.size();
 		int n = points.size(),ans = 0;     //ansΪ���ս��
	    for(int i = 0; i < n - 1; i++)      
	    {
	    	int maxNum = 0;                //��¼��ǰ�ڵ��Ӧ��б�ʳ������Ĵ���
	    	int same_x = 1;                //��¼б�ʲ����ڣ�����������ȵ����
	    	int samePoint = 0;             //��¼�غϵĵ�
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
	      		if (points[i].x == points[j].x)  //б�ʲ�����   
	      		{
	      			same_x++;
	  				continue;
	      		}
	      		double k = (double)(points[i].y-points[j].y)/(points[i].x-points[j].x);
	      		if (slope.find(k) != slope.end())   //���µ�ǰб�ʳ��ֵĴ���
	      			slope[k]++;
	      		else
	      			slope[k] = 2;
	        }
	        for (map<double,int>::iterator it = slope.begin(); it != slope.end(); ++it)   //�ҳ���������б��
	        	same_x = max(same_x,it->second);
	        maxNum = same_x + samePoint;
	        ans = max(ans,maxNum);                  //��֮ǰ�����ֵ�Ƚ�
		} 	    
	    return ans;
    }
};