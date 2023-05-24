### HW7 Review


#### STL Container and Algorithm
1. Be careful with empty container when adding elements into it! (Iterator Adaptor needed)
```
std::vector<int> v;
std::copy(source.begin(), source.end()), back_iter(v)); // back_iter needed
```

2. Be careful when interacting with 2 containers: **length** of them matters!(Pay attention to the assumption an stl function puts on the length of the containers)
```
std::transform(m_coeffs.begin(), m_coeffs.end(), rhs.m_coeffs.begin(), m_coeffs.begin(), std::plus<double>());
```
Assumption: there is no `last2` because the function assumes that the length of the slice starting from `begin2`is greter or equal than the `distance(last1 - begin1)`; However, if `rhs` is shorter than the `m_coeffs`, than there will be undefined behavior 
