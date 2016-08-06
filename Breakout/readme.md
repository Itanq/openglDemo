
## 介绍

用C++语言基于OpenGL3.3实现的一款经典电子游戏**Breakout**。

---

### 玩法

这个项目实现了经典游戏breakout的全部效果，能够实现球与砖块、水泥砖、玩家操作的挡板、掉下的具有相应属性的木板以及屏幕边缘之间的**碰撞检测**。

并根据不同的物体碰撞作出不同的碰撞反应。比如：球碰撞到砖块之后，砖块会被消除，而碰到其他的物体则向一定的角度反弹。

此外，每次碰撞的时候都会根据碰撞物的不同发出不同的声音，同时小球撞击到水泥砖的时候，游戏界面会出现抖动现象，并且略微模糊。

操作按键：
>   A or Left:      向左移动
    D or Right:     向右移动
    space:          发射小球

当你消除了所有的可消除砖块且没有掉下去则获胜。游戏共分为四个等级，难度递增，玩家也可以自己通过修改levels/\*.lvl文件来自定义等级。


### 特效

通过自定义一个**粒子系统**来产生小球移动时的尾部特效。移动的速度越快，尾部的特效就越长。


## 游戏效果图

![1](https://img1.doubanio.com/view/photo/photo/public/p2371955579.jpg)
![2](https://img3.doubanio.com/view/photo/photo/public/p2371955576.jpg)
![3](https://img3.doubanio.com/view/photo/photo/public/p2371956024.jpg)
![4](https://img3.doubanio.com/view/photo/photo/public/p2371955581.jpg)

