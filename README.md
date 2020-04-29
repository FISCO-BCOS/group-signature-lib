# group-signature-lib

![](https://github.com/FISCO-BCOS/FISCO-BCOS/raw/master/docs/images/FISCO_BCOS_Logo.svg?sanitize=true)

[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](http://makeapullrequest.com)
[![GitHub issues](https://img.shields.io/github/issues/FISCO-BCOS/group-signature-lib.svg)](https://github.com/FISCO-BCOS/group-signature-lib/issues)
[![All releases](https://img.shields.io/github/release/FISCO-BCOS/group-signature-lib.svg)](https://github.com/FISCO-BCOS/group-signature-lib/releases/latest)
![](https://img.shields.io/github/license/FISCO-BCOS/group-signature-lib) 

签名库基于[PBC Library](https://crypto.stanford.edu/pbc/)分别实现了[BBS04](http://crypto.stanford.edu/~dabo/abstracts/groupsigs.html)群签名方案和[LSAG](https://www.semanticscholar.org/paper/Linkable-Spontaneous-Anonymous-Group-Signature-for-Liu-Wei/3c63f7c90d79593fadfce16d54078ec1850bedc9)环签名方案。群/环签名，是一种能隐藏签名者身份的签名算法，在具有匿名性要求的场景中有着广泛的应用前景，例如投标、拍卖、投票等等。

## 算法特性

### 群签名

- 匿名性：群成员用群参数产生签名，其他人仅可验证签名的有效性，并通过签名知道签名者所属群组，却无法获取签名者身份信息；
- 不可伪造性：只有群成员才能生成有效可被验证的群签名；
- 不可链接性：给定两个签名，无法判断它们是否来自同一个签名者；
- 可追踪性：在监管介入的场景中，群主可通过签名获取签名者身份。

### 环签名

- 不可伪造性：环中其他成员不能伪造真实签名者签名；
- 完全匿名性：没有群主，只有环成员，其他人仅可验证环签名的有效性，但没有人可以获取签名者身份信息。

## 算法流程

### 群签名

1. 创建群：群主执行，生成群公钥，群主私钥和群参数；
2. 加入群：群主执行，群主为群成员生成私钥和证书，其中证书用于证明成员身份；
3. 生成群签名：群成员通过私钥和证书对信息签名；
4. 验证群签名：验证者可通过群公钥和群参数验证签名的有效性；
5. 打开群签名：群主可通过签名信息可获取签名者证书，从而追踪到签名者身份；
6. 撤销群成员：群主可移除群成员，并更新群公钥；
7. 更新私钥：群成员可根据撤销历史更新自己的私钥。

**注：** 可选用不同线性对参数创建群，目前支持A，A1，E和F类型线性对，默认使用A类型线性对

### 环签名

1. 初始化环：由环成员执行，生成环参数，环参数就好比微信面对面建群的密码，任何知道该参数的成员都可以加入该环；
2. 加入环：由环成员执行，通过环参数，获得公私钥对；
3. 生成环签名：环成员使用私钥和其他环成员公钥产生匿名签名，环大小可由用户根据性能和安全性需求自定义指定；
4. 验证环签名：验证者可通过环参数和产生环签名的公钥列表，验证环签名的有效性。

## 签名库使用

### 安装依赖

- Ubuntu

推荐Ubuntu 16.04以上版本，16.04以下的版本没有经过测试。

```bash
$ sudo apt install -y flex patch bison libgmp-dev byacc
```

- CentOS

推荐使用CentOS7以上版本。

```bash
$ sudo yum install -y flex patch bison gmp-static byacc
```

- macOS

推荐xcode10以上版本。macOS依赖包安装依赖于[Homebrew](https://brew.sh/)。

```bash
$ brew install flex bison gmp byacc
```

### 安装签名库

```bash
# 下载源码
git clone https://github.com/FISCO-BCOS/group-signature-lib.git
# 创建目录
cd group-signature-lib && mkdir -p build && cd build
# CentOS请使用cmake3
cmake ..
# 编译，可使用-j4加速
make 
# 安装库到系统目录
make install
```

### 接口说明

详见[接口文档](doc/interface.md)。

## 贡献代码

- 我们欢迎并非常感谢您的贡献，请参阅[代码贡献流程](CONTRIBUTING.md)。
- 如项目对您有帮助，欢迎star支持！

## 加入社区

**FISCO BCOS开源社区**是国内活跃的开源社区，社区长期为机构和个人开发者提供各类支持与帮助。已有来自各行业的数千名技术爱好者在研究和使用FISCO BCOS。如您对FISCO BCOS开源技术及应用感兴趣，欢迎加入社区获得更多支持与帮助。

![](https://raw.githubusercontent.com/FISCO-BCOS/LargeFiles/master/images/QR_image.png)

## License

![license](https://img.shields.io/github/license/FISCO-BCOS/group-signature-lib.svg)

group-signature-lib的开源协议为[APACHE LICENSE 2.0](http://www.apache.org/licenses/). 详情参考[LICENSE](./LICENSE)。
