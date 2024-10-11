#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <cstddef>
#include <cstdlib>
#include <queue>

class Pool {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    
    Pool(std::size_t size) noexcept : pool_size(size) {
        pool = malloc(size);
        pool_capacity = size;
        empty.push({pool, size});
    }
    template <typename U> Pool(const Pool<U>&) noexcept {}

    void* allocate(std::size_t n) {
        if (pool_capacity < n) {
            return nullptr;
        }
        auto chunk = std::move(empty.front());
        chunk.second -= n;
        chunk.first = (void*) ((unsigned long long) chunk.first + n);
        pool_capacity -= n;
        empty.pop();
        if(chunk.second > 0) {
            empty.push(chunk);
        }
        return chunk.first;
    }

    void deallocate(T* p, std::size_t n) noexcept {

    }
private:
    std::queue<std::pair<void*, size_t>> empty;
    void* pool{nullptr};
    std::size_t pool_size{0};
    std::size_t pool_capacity{0};

};

template <typename T> 
class Allocator {
public:
    Allocator() = delete;
    Allocator(Pool& pool) noexcept : pool(pool) {}

private:
    Pool& pool;
};

#endif // ALLOCATOR_H