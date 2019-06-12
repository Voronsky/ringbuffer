#include "ring_buffer.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(){
    RingBuffer<int> queue(3);
    queue.Push(1);
    assert(queue.Size() == 1);
    queue.Push(2);
    assert(queue.Size() == 2);
    queue.Push(3);
    assert(queue.Full() == true);
    assert(queue.Empty() == false);
    assert(queue.Size() == 3);
    assert(queue.Front() == 1);
    assert(queue.Back() == 3);
    assert(queue.Size() == 3);
    queue.Pop();
    assert (queue.Front() == 2);
    assert (queue.Size() == 2);
    assert (queue.Back() == 3);
    queue.Push(4);
    assert(queue.Back() == 4);
    assert(queue.Size() == 3);
    queue.Pop();
    queue.Pop();
    queue.Pop();
    assert(queue.Empty() == true);
    assert(queue.Full() == false);
    queue.Push(1);
    queue.Push(2);
    assert(queue.Size() == 2);
    queue.Pop();
    assert(queue.Size() == 1);

    return 0;
}