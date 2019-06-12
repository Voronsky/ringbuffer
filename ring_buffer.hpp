#include <stdlib.h>

template <class T>
class RingBuffer{
    public:
        RingBuffer(size_t queue_size) :  buffer(new T[queue_size]), max_size(queue_size)
        {} 

        ~RingBuffer(){
            front = rear = 0;
            max_size = 0;
            free(buffer);
        }

        void Push(const T & value);
        void Pop(); 
        bool Full();
        bool Empty();
        const size_t Size();
        T& Front();
        T& Back();
        const bool operator < (const RingBuffer<T>& rhs);
        const bool operator > (const RingBuffer<T>& rhs);
        const bool operator == (const RingBuffer<T>& rhs);
        const bool operator >= (const RingBuffer<T>& rhs);
        const bool operator <= (const RingBuffer<T>& rhs);

    private:
        size_t front = 0;
        size_t rear = 0;
        T *buffer;
        size_t max_size;
};
       
/**
* @brief Pushes type T onto the ring buffer queue
* 
* @param value 
*/
template<class T>
void RingBuffer<T>::Push(const T & value){
    if(!Full()){
        /*RingBuffer is empty*/
        if(front == 0 && rear == 0){
            rear++;
            buffer[front] = value;
        } /*front has been popped but rear has reached max size*/
        else if(front!=0 && rear==max_size){
           rear = 0;
           buffer[rear] = value;
        }
        else{
            buffer[rear] = value;
            rear++;
        }
    }
}        

/**
* @brief "pops" the front front by moving head, allowing
* the former head index to be overwritten as by design
* 
*/
template<class T>
void RingBuffer<T>::Pop(){
    if(!Empty()){
        if(front < max_size - 1){
            front = (front+1) % max_size;
        }
        else{ 
        /* we reached the end, set back to 0 */
            front = 0; 
        }
    }
}

/**
 * @brief returns a boolean value if the queue is full or not
 * 
 * @tparam T 
 * @return true 
 * @return false 
 */
template<class T>
bool RingBuffer<T>::Full(){
   bool full = false;
   /*Nothing has been popped - tail is last possible element*/
   if(front==0 && rear == max_size){
        full = true; 
    }            
    /* if we've already gone a circle */
    if(this->Size()==max_size){
        full = true;
    }
    return full;
}

/**
 * @brief returns a boolean value if the queue is empty or not
 * 
 * @tparam T 
 * @return true 
 * @return false 
 */
template<class T>
bool RingBuffer<T>::Empty(){
    bool empty = false;
    if(front==0 && rear==0){
        empty = true; 
    }
    return empty;
}

/**
 * @brief returns the size of the queue, that is how many elements are in the queue
 * 
 * @tparam T 
 * @return size_t 
 */
template<class T>
const size_t RingBuffer<T>::Size(){
    if(rear == max_size && front == 0){
        return max_size;
    }
    else if(front!=0 && front<rear){
        return rear - front;
    }
    else if(front < rear ){
        return rear;
    }
    else if(front==rear){
        return 0;
    }
    else if(front > rear)
    {
        return (max_size - front) + rear + 1;
    }
    else{
        return 0;
    }
}

/**
 * @brief returns a reference to the front of the queue
 * 
 * @tparam T 
 * @return RingBuffer<T>& 
 */
template<class T>
T& RingBuffer<T>::Front(){
    return this->buffer[front];
}

/**
 * @brief returns a reference to the back of the queue
 * 
 * @tparam T 
 * @return RingBuffer<T>& 
 */
template<class T>
T& RingBuffer<T>::Back(){
    if(rear!=0){
        return this->buffer[rear-1];
    }
    else{ /*if we've gone full circle */
        return this->buffer[rear];
    }
}

/**
 * @brief  returns true or false if the lhs is < the rhs
 * 
 * @tparam T 
 * @param rhs 
 * @return true 
 * @return false 
 */
template<class T>
const bool RingBuffer<T>::operator <( const RingBuffer<T>& rhs){
    return ((this->Size() < rhs.Size()) ? true: false);
}

/**
 * @brief returns true or false if the lhs is > the rhs
 * 
 * @tparam T 
 * @param rhs 
 * @return true 
 * @return false 
 */
template<class T>
const bool RingBuffer<T>::operator >(const RingBuffer<T>& rhs){
    return !(this->Size() < rhs.size());
}

/**
 * @brief returns true or false if lhs == rhs
 * 
 * @tparam T 
 * @param rhs 
 * @return true 
 * @return false 
 */
template<class T>
const bool RingBuffer<T>::operator == (const RingBuffer<T>& rhs){
    int itr = 0;
    auto lhs_size = this->Size();
    auto rhs_size = rhs.Size();
    if(lhs_size < rhs_size || lhs_size > rhs_size){
        return false;
    }
    while(itr!=rhs_size){
        if(this->buffer[itr] != rhs.buffer[itr]){
            return false;
        }
        itr++;
    }
    
    return true;
}

/**
 * @brief returns true or false if lhs >= rhs
 * 
 * @tparam T 
 * @param rhs 
 * @return true 
 * @return false 
 */
template<class T>
const bool RingBuffer<T>::operator >= (const RingBuffer<T>& rhs){
    return ((this->Size()>=rhs.Size() ? true:false));
}


/**
 * @brief returns true or false if lhs <= rhs
 * 
 * @tparam T 
 * @param rhs 
 * @return true 
 * @return false 
 */
template<class T>
const bool RingBuffer<T>::operator <= (const RingBuffer<T>& rhs){
    return ((this->Size()>=rhs.Size() ? true:false));
}