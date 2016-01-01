
class MedianFinder {
public:
	std::multiset<int> m_left;
	std::multiset<int> m_right;
    // Adds a number into the data structure.
    void addNum(int num) {
    	if (m_left.size() == m_right.size())         //判断两边容量大小
    	{
    		if (m_right.size()&&num > *m_right.begin())     //如果右边不为空，且新插入的值比右边最小值大，进行调整
    		{                                               //将右边的最小值放入左边，新值插入右边
    			m_right.insert(num);
    			int temp = *m_right.begin();
    			m_left.insert(temp);
    			m_right.erase(m_right.begin());
    		}
    		else 
    			m_left.insert(num);
    	}
    	else                                       
    	{
    		if (num < *m_left.rbegin())                      //同样进行判断，如果比左边最大值小，插入左边，进行调整
    		{
    			m_left.insert(num);
    			int temp = *m_left.rbegin();
    			m_right.insert(temp);
    			m_left.erase(--m_left.end());
    		}
    		else 
    			m_right.insert(num);
    	}  
    }

    // Returns the median of current data stream
    double findMedian() {
        return m_left.size()==m_right.size()?(*m_left.rbegin() + *m_right.begin())/(double)2:*m_left.rbegin(); 
    }
};
