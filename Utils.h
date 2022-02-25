#pragma once
#include<iostream>
#include<vector>
#include<unordered_map>

template<class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    for (auto& a : v) {
        out << a << " ";
    }
    return out;
}

template<class T, class K>
std::ostream& operator<<(std::ostream& out, const std::unordered_map<T, K>& v) {
    for (auto& [key, val] : v) {
        out << "{" << key << " : " << val << "}, ";
    }
    return out;
}

template<class T, class K>
std::ostream& operator<<(std::ostream& out, const std::pair<T, K>& v) {
    out << "<" << v.first << ", " << v.second << ">";
    return out;
}

void print() {
    std::cout << std::endl;
}

template<class T>
void print(T obj) {
    std::cout << obj << std::endl;
}

template<class T, class... Args>
void print(T obj, Args... args) {
    std::cout << obj << " ";
    print(args...);
}