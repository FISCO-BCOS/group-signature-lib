
# 接口说明

## 群签名接口

群签名算法接口定义在`group_sig/algorithm/GroupSig.h`文件中，各个接口说明如下：

- 接口名称：**create_group_default**

- 接口功能说明：使用默认参数创建群

- 参数说明

  | 输入参数     | 类型      | 说明               |
  | ------------ | --------- | ------------------ |
  | 无           |           |                    |
  | **输出参数** | **类型**  | **说明**           |
  | 返回值       | GroupInfo | 结构体，记录群信息 |

  ```c++
  // 结构体信息
  struct GroupInfo
  {
  	string gpk;    // 群公钥
  	string gmsk;   // 群主私钥
  	string gamma;  // 群私钥
  	string param;  // 群参数
  	GroupInfo() {}
  	GroupInfo(string &in1, string &in2, string &in3, string &in4):gpk(in1), gmsk(in2), gamma(in3), param(in4) {}
  };
  ```

- 接口名称：**create_group**

- 接口功能说明：通过指定参数创建群

- 参数说明

  | 输入参数      | 类型      | 说明                      |
  | ------------- | --------- | ------------------------- |
  | pbc_param_str | string    | 支持A, A1, E和F类型线性对 |
  | **输出参数**  | **类型**  | **说明**                  |
  | 返回值        | GroupInfo | 结构体，记录群信息        |

  示例如下：

  - A类型线性对： "{"linear_type": "a", "r_bits_len": 256, "q_bits_len":256}"
  - A1类型线性对："{"linear_type":"a_one", "order":512}"
  - E类型线性对："{"linear_type":"e", "q_bits_len": 512, "r_bits_len":512}"
  - F类型线性对："{"linear_type":"f", "bit_len": 256}"

- 接口名称：**group_member_join**

- 接口功能说明：群主为群成员生成公私钥对

- 参数说明

  | 输入参数     | 类型     | 说明           |
  | ------------ | -------- | -------------- |
  | param_info   | string   | 群参数         |
  | gmsk_info    | string   | 群主私钥       |
  | gpk_info     | string   | 群公钥         |
  | gamma_info   | string   | 群私钥         |
  | **输出参数** | **类型** | **说明**       |
  | 返回值       | string   | 成员私钥和证书 |

- 接口名称：**group_sig**

- 接口功能说明：群成员签名

- 参数说明

  | 输入参数     | 类型     | 说明           |
  | ------------ | -------- | -------------- |
  | gpk_info     | string   | 群公钥         |
  | sk_info      | string   | 成员私钥和证书 |
  | param_info   | string   | 群参数         |
  | message      | string   | 消息           |
  | **输出参数** | **类型** | **说明**       |
  | 返回值       | string   | 群签名         |

- 接口名称：**group_verify**

- 接口功能说明：群成员签名

- 参数说明

  | 输入参数     | 类型     | 说明     |
  | ------------ | -------- | -------- |
  | sig          | string   | 群签名   |
  | message      | string   | 消息     |
  | gpk_info     | string   | 群公钥   |
  | param_info   | string   | 群参数   |
  | **输出参数** | **类型** | **说明** |
  | 返回值       | bool     | 验证结果 |

- 接口名称：**open_cert**

- 接口功能说明：群成员签名

- 参数说明

  | 输入参数     | 类型     | 说明     |
  | ------------ | -------- | -------- |
  | sig          | string   | 群签名   |
  | message      | string   | 消息     |
  | gpk_info     | string   | 群公钥   |
  | gmsk_info    | string   | 群主私钥 |
  | param_info   | string   | 群参数   |
  | **输出参数** | **类型** | **说明** |
  | 返回值       | string   | 证书     |

- 接口名称：**revoke_member**

- 接口功能说明：撤销群成员

- 参数说明

  | 输入参数     | 类型     | 说明                   |
  | ------------ | -------- | ---------------------- |
  | gpk_info     | string   | 群公钥                 |
  | param_info   | string   | 消息                   |
  | revoke_info  | string   | 被撤销成员的私钥和证书 |
  | gamma_info   | string   | 群私钥                 |
  | **输出参数** | **类型** | **说明**               |
  | 返回值       | string   | 新的群公钥             |

- 接口名称：**revoke_update_private_key**

- 接口功能说明：群成员更新私钥

- 参数说明

  | 输入参数     | 类型     | 说明                                 |
  | ------------ | -------- | ------------------------------------ |
  | sk_info      | string   | 成员私钥和证书                       |
  | param_info   | string   | 群参数                               |
  | revoke_list  | string   | 撤销列表                             |
  | g1_list      | string   | 撤销历史中所有更新后的群公钥的g1列表 |
  | gpk_info     | string   | 成员所属群的群公钥                   |
  | **输出参数** | **类型** | **说明**                             |
  | 返回值       | string   | 新的成员私钥和证书                   |

## 环签名接口

群签名算法接口定义在`group_sig/algorithm/RingSig.h`文件中，各个接口说明如下：

- 接口名称：**setup_ring**

- 接口功能说明：通过指定参数创建环

- 参数说明

  | 输入参数     | 类型     | 说明           |
  | ------------ | -------- | -------------- |
  | bit_len      | int      | 指定环参数长度 |
  | **输出参数** | **类型** | **说明**       |
  | 返回值       | string   | 环参数         |

- 接口名称：**join_ring**

- 接口功能说明：环成员加入群

- 参数说明

  | 输入参数     | 类型     | 说明                        |
  | ------------ | -------- | --------------------------- |
  | param_info   | string   | 环参数                      |
  | pos          | string   | 成员在环中的位置，从“0”开始 |
  | **输出参数** | **类型** | **说明**                    |
  | 返回值       | pair     | 公私钥对                    |

- 接口名称：**ring_sig**

- 接口功能说明：环成员加入群

- 参数说明

  | 输入参数         | 类型             | 说明     |
  | ---------------- | ---------------- | -------- |
  | message          | string           | 消息     |
  | public_key_list  | vector\<string\> | 公钥列表 |
  | private_key_info | string           | 私钥     |
  | param_info       | string           | 环参数   |
  | **输出参数**     | **类型**         | **说明** |
  | 返回值           | pair             | 公私钥对 |

- 接口名称：**ring_verify**

- 接口功能说明：环成员加入群

- 参数说明

  | 输入参数     | 类型     | 说明     |
  | ------------ | -------- | -------- |
  | sig          | string   | 签名     |
  | message      | string   | 消息     |
  | param_info   | string   | 环参数   |
  | **输出参数** | **类型** | **说明** |
  | 返回值       | bool     | 验证结果 |
