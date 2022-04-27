# 第3章 创建类型

## 3.3 object

### Object 类型

---

- object（System.Object）是所有类型的终极父类
- 所有类型都可以向上转换为 object

```C#
public class Stack{
    int position;
    object[] data = new object[10];
    public void Push(object obj)    { data[position++] = obj; }
    public object Pop() { return data[--position]; }
}

/*实例*/
Stack stack = new Stack();
stack.Push("sausage");
string s = (string)stack.Pop;       // Downcast, so explicit cast is needed

Console.WriteLine(s);               // sausage
```

- object 是引用类型
- 但值类型可以转换为 Object，反之亦然。（类型统一）

    ```C#
    stack.Push(3);
    int three = (int)stack.Pop();
    ```

- 在值类型和 object 之间转换的时候，CLR必须执行一些特殊的工作，以弥合值类型和引用类型之间语义上的差异，这个过程就叫做装箱和拆箱。

1. **装箱**

   - 装箱就是把值类型的实例转化为引用类型实例的动作
   - 目标引用类型可以是 object，也可以是某个接口

   ```C#
   int x = 9;
   object obj = x;             //Box the int
   ```

2. **拆箱**

   - 拆箱正好相反，把那个对象转化为原来的值类型
   - 拆箱需要显式的转换

   ```C#
   int y = (int)obj;             //unBox the int
   ```

   - 运行时会检查这个值类型和 object 对象的真实类型是否匹配
     - 运行如果不匹配就抛出 InvalidCastException

   ```C#
   object obj = 9;          // 9 is inferred to be of type int 
   long x = (long)obj;      // InvalidCastException

   object obj = 9;
   long x = (int) obj;

   object obj = 3.5;        // 3.5 is inferred to be of type double
   int x = (int) (double)obj;   // x is now 3
   ```

3. **注意**

   - 装箱对于类型统一是非常重要的。但是系统不够完美
   - 数组和泛型只支持引用转换，不支持装箱

    ```C#
    object[] a1 = new string[3];        // Legal
    object[] a2 = new int[3];           // Error
    ```

4. **装箱和拆箱的复制**

   - 装箱会把值类型的实例复制到一个新的对象
   - 拆箱会把这个对象的内容再复制给一个值类型的实例

   ```C#
   int i = 3;
   object boxed = i;
   i = 5;
   Console.WriteLine(boxed);           // 3
   ```

5. **静态和运行时类型检查**

   - C# 的程序既会做静态的类型检查（编译时），也会做运行时的类型检查（CLR）
   - 静态检查：不运行程序的情况下，让编译器保证程序的正确性
   - 运行时的类型检查由 CLR 执行，发生在向下的引用转换或拆箱的时候

    ```C#
    object y = "5";
    int z = (int )y;        // Runtime error, Downcast failed
    ```

    - 运行时检查之所以可以是因为：每个在 heap 上的对象内部都存储了一个类型 token。这个token 可以通过调用 object 的 GetType（）方法获取

6. **GetType 方法与 TypeOf 操作符**

    - 所有 C# 的类型在运行时都是以 System.Type 的实例来展现的
    - 两种方式可以获得 System.Type 对象：
      - 在实例上调用 GetType（）方法
      - 在类型名上使用 typeof 操作符
    - GetType 是在运行时被算出的
    - typeof 是在编译时被算出（静态）（当涉及到泛型类型参数时，它是由 JIT 编译器来解析的）

    - **System.Type**：System.Type 的属性有：类型的名称，Assembly，基类等等。

    ```C#
    using System;
    
    public class Point { public int X, y; }

    class test{
        static void Main(){
            Point p = new Point();
            Console.WriteLine(p.GetType().Name);                // Point
            Console.WriteLine(typeof(Point).Name);              // Point
            Console.WriteLine(p.GetType() == typeof(Point));    // True
            Console.WriteLine(p.X.GetType().Name);              // Int32
            Console.WriteLine(p.Y,GetType().FullName);          // System.Int32
        }
    }
    ```

7. **ToString 方法**

    - ToString（） 方法会返回一个类型实例的默认文本表示
    - 所有的内置类型都重写了该方法

    ```C#
    int x = 1;
    string s = x.ToString();  // s is "1"
    ```

    - 可以在自定义的类型上重写 ToString（）方法
    - 如果不重写该方法，那就会返回该类型的名称

    ```C#
    public class Panda{
        public string Name;
        public override string ToString() => Name;
    }

    /**/
    ...

    Panda p = new Panda{Name = "Petey"};
    Console.WriteLine(p);                   // Petey
    ```

    - 当调用一个重写的 object 成员的时候，例如在值类型上直接调用 ToString（）方法，这时就不会发生装箱操作
    - 但是如果进行了转换，那么装箱操作就会发生

    ```C#
    int x = 1;
    string s1 = x.ToString();       // Calling on nonboxed value

    object box = x;
    string s2 = box.ToString();     //Calling on boxed value
    ```

8. object 的成员列表

    ```C#
    public class Object{
        public Object();

        public extern Type GetType();

        public virtual bool Equals (object obj);
        public static bool Equals (object objA, object objB);
        public static bool ReferenceEquals (object objA, object objB);

        public virtual int GetHashCode();

        public virtual string ToString();

        protected virtual void Finalize();
        protected extern object MemberwiseClone();
    }
    ```