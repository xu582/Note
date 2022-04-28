# 第3章 创建类型

## 3.4 struct

---

### struct

- struct 和 class 区别：
  - struct 是值类型，class 是引用类型
  - struct 不支持继承（除了隐式的继承了 object，System.ValueType）

1. **struct 的成员**

    - class 能有的成员，struct 也可以有，一下除外：
      - 无参构造函数
      - 字段初始化器
      - 终结器
      - virtual 或 protected 成员

2. **struct 的构建**
   - struct 有一个无参的构造函数，但是不能对其进行重写。它会对字段进行归零操作
   - 当定义 struct 构造函数的时候，必须显式的为每个字段赋值
   - 不可以有字段初始化器

    ```C#
    public struct Point{
        int x,y;
        public Point(int x, int y){ this.x = x; this.y = y; }
    }

    /**/

    Point p1 = new Point();         // p1.x and p1.y Will be 0;
    Point p2 = new Point(1,1);      // p1.x and p1.y will be 1;

    /*******error******/
    public struct Point{
        int x = 1;                          // Illegal: field initializer
        int y;              
        public Point(){}                    // Illegal: parameterless constructor
        public Point(int x){this.x = x;}    // Illegal: must assign field y
    }
    ```
