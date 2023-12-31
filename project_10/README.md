该报告从以下三个方面展开：
# ECDSA概述
椭圆曲线数字签名算法（ECDSA）是使用椭圆曲线密码（ECC）对数字签名算法（DSA）的模拟。与普通的离散对数问题（DLP）和大数分解问题（IFP）不同，椭圆曲线离散对数问题没有亚指数时间的解决方法。因此椭圆曲线密码的单位比特强度要高于其他公钥体制。
数字签名算法（DSA）在联邦信息处理标准FIPS中有详细论述，称为数字签名标准。它的安全性基于素域上的离散对数问题。可以看作是椭圆曲线对先前离散对数问题（DLP）的密码系统的模拟，只是群元素由素域中的元素数换为有限域上的椭圆曲线上的点。椭圆曲线离散对数问题远难于离散对数问题，单位比特强度要远高于传统的离散对数系统。因此在使用较短的密钥的情况下，ECC可以达到于DL系统相同的安全级别。这带来的好处就是计算参数更小，密钥更短，运算速度更快，签名也更加短小。
# ECDSA原理 
签名过程
验证过程
处理过程（详细）
# ECDSA的实践
实施ECDSA时出现的一些问题在曲线和密钥生成或签名生成和验证过程中可能会出现一些漏洞。我们只调查与椭圆曲线的选择有关的问题。在实施过程中出现的一般问题，例如不检查一个点是否是无穷大的点，在这里不涉及。 
第一个漏洞可能是操纵∶建议的安全曲线可能有一个后门不安全因素。
比特币和以太坊使用一个固定的曲线--secp256k1--并且只生成私钥和公钥。根据Safecurves,椭圆曲线secp256k1可以被认为有些“僵硬"，这意味着几乎所有的参数对公众是透明的，因此可以假设不是为了弱点而生成的。 
