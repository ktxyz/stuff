#include <map>
#include <iostream>
template<typename K, typename V>
class interval_map {
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K,V> m_map;
public:
    // constructor associates whole range of K with val
    interval_map(V const& val)
    : m_valBegin(val)
    {}

    bool check_canonicity() {
        V key = m_valBegin;
        for(auto it = m_map.begin(); it != m_map.end(); ++it) {
            if (it->second == key)
                return false;
            key = it->second;
        }
        return true;
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
        if (!(keyBegin < keyEnd))
            return;

        // Close right
        auto right_it = m_map.upper_bound(keyEnd);
        auto right_val = m_valBegin;
        if (right_it != m_map.end() && right_it != m_map.begin())
            right_val = std::prev(right_it)->second;
        else
            right_val = m_valBegin;
        
        if (!(right_val == val))
            m_map.insert_or_assign(keyEnd, right_val);

        // Close left
        m_map.insert_or_assign(keyBegin, val);
        auto left_it = m_map.find(keyBegin);

        // Clear inside
        m_map.erase(m_map.upper_bound(keyBegin), m_map.lower_bound(keyEnd));

        left_it = m_map.find(keyBegin);
        if (!(right_val == val))
            right_it = m_map.find(keyEnd);
        else
            right_it = std::next(left_it);
        
        if (right_it != m_map.end() && left_it != m_map.end() && left_it->second == right_it->second)
            right_it = m_map.erase(right_it);

        // Clear left
        while(left_it != m_map.begin() && left_it != m_map.end() && left_it->second == std::prev(left_it)->second)
            left_it = m_map.erase(left_it);

        // Clear right
        while(right_it != m_map.end() && std::next(right_it) != m_map.end() && std::next(right_it)->second == right_it->second)
            right_it = m_map.erase(right_it);
        
        // remove beginning
        while(m_map.begin() != m_map.end() && m_map.begin()->second == m_valBegin)
            m_map.erase(m_map.begin());
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        auto it=m_map.upper_bound(key);
        if(it==m_map.begin()) {
            return m_valBegin;
        } else {
            return (--it)->second;
        }
    }
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.