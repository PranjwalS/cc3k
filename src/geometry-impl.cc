import geometry;

export std::pair<int, int> operator+(const std::pair<int, int>& lhs, 
                                    const std::pair<int, int>& rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}