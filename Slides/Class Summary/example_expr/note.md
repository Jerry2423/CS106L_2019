# Notes about NodeBase

说明：此题整个面向对象的设计体现出了一种递归的特性，值得参考

**关于eval函数overload**
对于`Constant`对象的`eval`其实是不需要参数的，但是父类对`eval(double x)`的定义是体现了参数的，根据overload virtual函数的规则，子类函数，返回值类型，const，参数的类型与个数应该是相同的。那么`Constant`对象的`eval`仍然需要有一个`double`的参数，为了解决这个问题可以`eval(double)`用`double`占个位置但不命名来满足形式上的一致性

**关于forward转发的应用**
代码中经常出现`std::make_shared<UnaryOperator>('-', operand);`这里有转发的想法：`std::make_shared`将`('-', operand)`括号里面的参数转发到了`UnaryOperator`的constructor里面去了，所以`UnaryOperator`也要有对应的constructor：
```
UnaryOperator(char op, const Expr &operand) : m_op{op}, m_operand{operand} {}
```

