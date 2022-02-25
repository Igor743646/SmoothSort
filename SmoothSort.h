#pragma once
#include "Utils.h"

using namespace std;

/// <summary>
/// ���������� ���-������� � ������� ��������. (�� ������� ��� ��������� �� �����)
/// </summary>
/// <param name="s">- ������ ������������ �������</param>
/// <returns></returns>
unordered_map<size_t, bool> GenLeonardoNumbers(size_t s) {
    unordered_map<size_t, bool> result;

    size_t a = 1, b = 1;
    result[1] = true;

    while (a + b + 1 <= s) {
        result[1 + a + b] = true;
        size_t temp = 1 + a + b;
        a = b;
        b = temp;
    }

    return result;
}

/// <summary>
/// �������� �������� � ����
/// </summary>
/// <param name="v">- ������ ���������</param>
/// <param name="pos">- ������ ���������� �� �����</param>
/// <param name="start">- ���� ������ ����������� ���</param>
template<class T>
void shift(vector<T>& v, vector<pair<long long, long long>>& pos, size_t start) {
    while (pos[start] != pair{ -1ll, -1ll } and (v[start] < v[pos[start].first] or v[start] < v[pos[start].second])) {
        if (v[start] < v[pos[start].first] and v[start] < v[pos[start].second]) {
            if (v[pos[start].second] < v[pos[start].first]) {
                std::swap(v[start], v[pos[start].first]);
                start = pos[start].first;
            }
            else {
                std::swap(v[start], v[pos[start].second]);
                start = pos[start].second;
            }
        }
        else if (v[start] < v[pos[start].second]) {
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
/// �� ����� ��������� ���� ������� ������ ������������� �������� ����� ������ ����������� ���
/// </summary>
/// <param name="v">- ������ ���������</param>
/// <param name="stack">- ���� ������ ����������� ���</param>
/// <returns>������ ������������� ��������</returns>
template<class T>
size_t index_of_max(const vector<T>& v, const vector<pair<size_t, size_t>>& stack) {
    T max = v[stack[0].second];
    size_t result = stack[0].second;

    for (size_t i = 1; i < stack.size(); i++) {
        if (max < v[stack[i].second]) {
            max = v[stack[i].second];
            result = stack[i].second;
        }
    }

    return result;
}

/// <summary>
/// ������� ���������� 
/// </summary>
/// <param name="v">- ������ ���������</param>
template<class T>
void SmoothSort(vector<T>& v) {
    unordered_map<size_t, bool> leo = GenLeonardoNumbers(v.size());

    // ���� ������ ���� <����� �������� (������ ����), ��������� �� ������ ����>
    vector<pair<size_t, size_t>> stack;
    // ������ pos ������� ��� i'��� �������� ���� ���������� �� ����� � ������ ���������. � ������ ���������� ����� ������ <-1, -1>.
    vector<pair<long long, long long>> pos(v.size());

    // ���� ����
    for (size_t i = 0; i < v.size(); i++) {
        if (stack.size() <= 1) { // ���������� ����� ����
            stack.push_back({ 1, i });
            pos[i] = { -1, -1 };
        }
        else {
            pair<size_t, size_t> last = *stack.rbegin();
            stack.pop_back();
            pair<size_t, size_t> last_last = *stack.rbegin();
            stack.pop_back();

            if (leo.find(last.first + 1 + last_last.first) != leo.end()) { // ���������� ���
                stack.push_back({ last.first + 1 + last_last.first, i });
                pos[i] = { last_last.second, last.second };
                shift(v, pos, i);
            }
            else { // ���������� ����� ����
                stack.push_back(last_last);
                stack.push_back(last);
                stack.push_back({ 1, i });
                pos[i] = { -1, -1 };
            }
        }
    }

    // ������ ����
    while (!stack.empty()) {
        size_t idx_of_max = index_of_max(v, stack);

        std::swap(v[idx_of_max], v[stack[stack.size() - 1].second]);
        shift(v, pos, idx_of_max);

        if (pos[stack[stack.size() - 1].second] == pair{ -1ll, -1ll }) { // �������� ����, ���� ������� �� ������ ��������
            stack.pop_back();
        }
        else { // �������� ����� ����, � � ������ �� ���
            pair<size_t, size_t> temp = stack[stack.size() - 1];
            stack.pop_back();

            stack.push_back({ 1, pos[temp.second].first });
            stack.push_back({ 1, pos[temp.second].second });
        }
    }
}