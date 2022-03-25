#pragma once
#include<vector>
#include<unordered_map>

namespace SmoothSort {

    /// <summary>
    /// Generate a hash-table with Leonardo numbers up to the given number.
    /// </summary>
    /// <param name="s">- the number</param>
    /// <returns>Hash-table with Leonardo numbers</returns>
    std::unordered_map<size_t, bool> GenerateLeonardoNumbers(size_t s) {
        std::unordered_map<size_t, bool> result;

        size_t a = 1, b = 1;
        result[1] = true;

        while (a + b + 1 <= s) {
            (a, b) = (b, 1 + a + b);
            result[b] = true;
        }

        return result;
    }

    /// <summary>
    /// Shifting an element in the heap
    /// </summary>
    /// <param name="v">- sortable vector</param>
    /// <param name="pos">- pointer vector</param>
    /// <param name="start">- stack of leonard heap roots</param>
    template<class T, class CMP>
    void shift(std::vector<T>& v, std::vector<std::pair<long long, long long>>& pos, size_t start, CMP compare = std::less<T>{}) {
        while (pos[start] != std::pair{ -1ll, -1ll } and (compare(v[start], v[pos[start].first]) or compare(v[start], v[pos[start].second]))) {
            if (compare(v[start], v[pos[start].first]) and compare(v[start], v[pos[start].second])) {
                if (compare(v[pos[start].second], v[pos[start].first])) {
                    std::swap(v[start], v[pos[start].first]);
                    start = pos[start].first;
                }
                else {
                    std::swap(v[start], v[pos[start].second]);
                    start = pos[start].second;
                }
            }
            else if (compare(v[start], v[pos[start].second])) {
                std::swap(v[start], v[pos[start].second]);
                start = pos[start].second;
            }
            else {
                std::swap(v[start], v[pos[start].first]);
                start = pos[start].first;
            }
        }
    }

    /// <summary>
    /// Finds the index of the maximum element among the roots of the Leonard heaps during backtracking
    /// </summary>
    /// <param name="v">- sortable vector</param>
    /// <param name="stack">- stack of leonard heap roots</param>
    /// <returns>Index of maximum element</returns>
    template<class T, class CMP>
    size_t index_of_max(const std::vector<T>& v, const std::vector<std::pair<size_t, size_t>>& stack, CMP compare = std::less<T>{}) {
        T max = v[stack[0].second];
        size_t result = stack[0].second;

        for (size_t i = 1; i < stack.size(); i++) {
            if (compare(max, v[stack[i].second])) {
                max = v[stack[i].second];
                result = stack[i].second;
            }
        }

        return result;
    }

    /// <summary>
    /// Smooth Sort 
    /// </summary>
    /// <param name="v">- sortable vector</param>
    template<class T, class CMP = std::less<T>>
    void sort(std::vector<T>& v, CMP compare = std::less<T>{}) {
        std::unordered_map<size_t, bool> leo = GenerateLeonardoNumbers(v.size());

        // stack stores pair <leonardo number (heap size), pointer to heap root>
        std::vector<std::pair<size_t, size_t>> stack;
        // vector pos stores for the i'th element a pair of pointers to the left and right subtrees. Stores <-1, -1> if there are no children.
        std::vector<std::pair<long long, long long>> pos(v.size());

        // Heap composition
        for (size_t i = 0; i < v.size(); i++) {
            if (stack.size() <= 1) { // adding a new heap
                stack.push_back({ 1, i });
                pos[i] = { -1, -1 };
            }
            else {
                std::pair<size_t, size_t> last = *stack.rbegin();
                stack.pop_back();
                std::pair<size_t, size_t> last_last = *stack.rbegin();
                stack.pop_back();

                if (leo.find(last_last.first + 1 + last.first) != leo.end()) { // join heaps
                    stack.push_back({ last_last.first + 1 + last.first, i });
                    pos[i] = { last_last.second, last.second };
                    shift(v, pos, i, compare);
                }
                else { // adding a new heap
                    stack.push_back(last_last);
                    stack.push_back(last);
                    stack.push_back({ 1, i });
                    pos[i] = { -1, -1 };
                }
            }
        }

        // Heap decomposition
        while (!stack.empty()) {
            size_t idx_of_max = index_of_max(v, stack, compare);

            std::swap(v[idx_of_max], v[stack[stack.size() - 1].second]);
            shift(v, pos, idx_of_max, compare);

            if (pos[stack[stack.size() - 1].second] == std::pair{ -1ll, -1ll }) { // removing the heap if it consists of one element
                stack.pop_back();
            }
            else { // deleting the root of the heap, and splitting it into two
                std::pair<size_t, size_t> temp = stack[stack.size() - 1];
                stack.pop_back();
                stack.push_back({ 1, pos[temp.second].first });
                stack.push_back({ 1, pos[temp.second].second });
            }
        }
    }

}