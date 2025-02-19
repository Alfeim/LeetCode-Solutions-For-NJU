/********************************************
作者:Alfeim
题目:LFU缓存
时间消耗:340ms
解题思路:双向链表 + 哈希表
********************************************/
class LFUCache {
public:
    struct buckets{
        int freq;
        buckets *prev;
        buckets *next;
        list<int> keys;   
        buckets():freq(0),prev(nullptr),next(nullptr){};    //默认构造
        buckets(int f):freq(f){};                           //带参构造,实际f也只能为1                                
    };
    
    LFUCache(int capacity):Capacity(capacity){
        head = new buckets;
        tail = new buckets;
        head->next = tail;
        tail->prev= head;
    }
    
    /*
    int get(int key)
    
    如果存在对应键的记录 就更新该key的频率,并返回其值
    
    否则返回-1
    
    */
    int get(int key){
        if(Capacity == 0)
            return - 1;
        
        if(values.count(key) == 0)
            return -1;
        
        update(key,values[key]);
        return values[key];
    }
    
    
     /*
    void put(int key,int value)
    
    如果不存在该key的记录,就执行插入操作
    
    插入前先判断当前容量是否已经超出最大容量,如果是则先执行删除操作--删除的是头节点的下一个bucket中的末尾元素,也就是出现频率最少且最近的那个
    
    如果已经有了该key的记录,就执行update操作
    
    */
    
    void put(int key, int value) {
        if( values.count(key) == 0){           //如果不存在该元素，执行插入    
            if(values.size() >= Capacity)     //如果当前容量超过最大容量,执行删除
                remove_from_head();
            
            insert(key,value);                //插入新元素  
        }else{
            update(key,value);                     //如果该元素已经存在,就更新
        }
    }
    
    
    /*
    void remove_from_head()
    
    因为按照题意只会删除频率最低的元素,所以一定是删除头节点的下一元素(不存在就不删)
    
    如果头节点的下一元素非空,就将该bucket的末尾元素弹出,并删除在valuesMap和keyFreq中的记录
    
    如果弹出末尾元素后,该bucket对应容器也空了,就要同时删除该bucket,并删除在FreqMap中对应的记录
    
    */
    void remove_from_head(){
        if(head->next != tail){
            int todelete = head->next->keys.back();
            head->next->keys.pop_back();
            values.erase(todelete);
            keyFreq.erase(todelete);
            if(head->next->keys.empty()){                
                 Freq.erase(head->next->freq);
                 
                 head->next->next->prev = head;
                 head->next = head->next->next;
            }
        }
    }
    
    
    
    
    /*
     void insert(int key,int value)
     
     插入操作,由于是新插入的,所以其对应的freq一定是1
     
     首先判断是否存在频率为1的bucket(直接看头元素的下一元素对应的freq是否为1即可)
     
     如果不存在频率为1的bucket,就新建一个,同时新增FreqMap中的记录
     
     然后往其对应的bucket中填入该key,并更新keyFreqMap和valuesMap中的记录
        
    */
    void insert(int key,int value){
        buckets *newbucket;
        if(head->next == tail || head->next->freq != 1){
            newbucket = new buckets(1);
            newbucket->next = head->next;
            newbucket->prev = head;
            head->next->prev = newbucket;
            head->next = newbucket;
            Freq[1] = newbucket;
        }else{
            newbucket = head->next;
        }
        newbucket->keys.push_front(key);
        keyFreq[key] = 1;
        values[key] = value;
    }
    
    /*
     void update(int key)
     
     更新某个key,本题中也就是让其freq+1
     
     首先找到新的freq对应的桶
     
     如果新的freq对应的桶不存在,就新建一个桶并插入到当前桶之后,同时更新对应的FreqMap中的记录
     
     然后往新的桶内填入该key,并删除旧桶内该key的信息,然后更新该key的频率
    
    */

    void update(int key,int value){
        buckets* cur = Freq[keyFreq[key]];   
        buckets *newbucket;          
        if(Freq.count(cur->freq + 1) == 0){   
            newbucket = new buckets();
            Freq[cur->freq + 1] = newbucket;
            newbucket->prev = cur;
            newbucket->next = cur->next;
            cur->next->prev = newbucket; 
            cur->next = newbucket;
            newbucket->freq = cur->freq + 1;
        }else{
            newbucket = Freq[cur->freq + 1];     
        }
        remove_key_from_bucket(cur,key);    
        newbucket->keys.push_front(key);              
        keyFreq[key] = newbucket->freq ;
        values[key] = value;
    }
    
     /*
     void remove_key_from_bucket(buckets *node , int key)
     
     从指定的桶内删除某个key
     
     如果删除后该桶内没有其他key,就把该桶删除,同时更新FreqMap中的记录
    
    */
    void remove_key_from_bucket(buckets *node , int key){
        node->keys.remove(key);
        if(node->keys.empty()){
            node->next->prev = node->prev;
            node->prev->next = node->next;
            Freq.erase(node->freq);
        }
    }

private:
    unordered_map<int,buckets*> Freq;   //每个频率对应的桶
    unordered_map<int,int> keyFreq;     //每个key的频率
    unordered_map<int,int> values;      //每个key对应的value
    int Capacity;                       //容量
    buckets *head;                      //头节点
    buckets *tail;                      //尾节点
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
